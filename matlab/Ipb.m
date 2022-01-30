clear all;
bitnum = 4; % 选择待处理图像的位深
filename = ['cat',num2str(bitnum),'.bmp']; % 图像路径
%读取文件句柄，图片保存在当前文件夹
bmp = fopen(filename,'rb');

type = fread(bmp,2,'char');
bmpsize = fread(bmp,1,'long');
bfReserved1and2 = fread(bmp,1,'long');
bfOffBits = fread(bmp,1,'long');
biSize = fread(bmp,1,'long');
biWidth = fread(bmp,1,'long');
biHeight = fread(bmp,1,'long');
biPlanes = fread(bmp,1,'short');
biBitCount = fread(bmp,1,'short');
biCompression = fread(bmp,1,'long');  %long 4个字节 short 2个字节
biSizeImage = fread(bmp,1,'long');
biXPelsPerMeter = fread(bmp,1,'long');
biYPelsPerMeter = fread(bmp,1,'long');
biClrUsed = fread(bmp,1,'long');
biClrImportant = fread(bmp,1,'long');

%读入调色板
sizeofColormap = (bfOffBits - 54) / 4;
switch biBitCount
    case 1
        colormap=fread(bmp,sizeofColormap,'long');
    case 4
        colormap=fread(bmp,sizeofColormap,'long');
    case 8
        colormap=fread(bmp,sizeofColormap,'long');
end

fclose(bmp);

%生成包含图像RGB的矩阵
bmp = fopen(filename, 'rb');
[data, count] = fread(bmp);

%取出在data中的RGB信息，然后重新排列矩阵
linenum = floor((biWidth * biBitCount/8 + 3) / 4) * 4;
ex = linenum -biWidth * biBitCount/8;        %每一行的填充字节
img = zeros(linenum, biHeight);
img = reshape(data(bfOffBits+1:end-2), linenum,[]);   %biSizeImage总比linenum*biHeight多2，在最后面
img = flipud(img'); %先转置，然后上下交换

%显示图像（1 4 8 16 24 32位）
switch biBitCount
    case 1
        for i=1:biHeight
            for j=1:8:biWidth
                k=(j-1)*biBitCount/8+1;  %ij代表像素位置，k代表字节位置
                for n=1:8
                    p=bitshift(bitand(2^(8-n),img(i,k)),n-8);                   
                    pp=colormap(p+1,1);
                    R=bitshift(bitand(16711680 , pp) , -16);  %colormap的后3个byte才是颜色字节
                    G=bitshift(bitand(65280 , pp) , -8) ;
                    B=bitshift(bitand(255 , pp) , 0);
                    RGB(i,j+n,1) = R;
                    RGB(i,j+n,2) = G;
                    RGB(i,j+n,3) = B;
                end
            end           
        end
        RGB = uint8(RGB);   %转换成unit格式
        imshow(RGB);        %显示图片
               
    case 4
        for i=1:biHeight
            for j=1:2:biWidth
                k=(j-1)*biBitCount/8+1;
                p1=bitshift( bitand(240 , img(i,k)) ,-4);
                p2=bitand(15,img(i,k));
                pp1=colormap(p1+1,1);
                pp2=colormap(p2+1,1); %数组坐标也+1
                R=bitshift(bitand(16711680 , pp1) , -16);  %colormap的后3个byte才是颜色字节
                G=bitshift(bitand(65280 , pp1) , -8) ;
                B=bitshift(bitand(255 , pp1) , 0);
                RGB(i,j,1) = R;
                RGB(i,j,2) = G;
                RGB(i,j,3) = B;
                R=bitshift(bitand(16711680 , pp2) , -16);  %colormap的后3个byte才是颜色字节
                G=bitshift(bitand(65280 , pp2) , -8) ;
                B=bitshift(bitand(255 , pp2) , 0);
                RGB(i,j+1,1) = R;
                RGB(i,j+1,2) = G;
                RGB(i,j+1,3) = B;
            end
        end
        RGB = uint8(RGB);   %转换成unit格式
        imshow(RGB);        %显示图片
        
    case 8
        for i=1:biHeight
            for j=1:biWidth*biBitCount/8
                p = colormap(img(i,j)+1,1);
                
                %                 R=bitshift(bitand(4278190080 , p) , -24) ;
                %                 G=bitshift(bitand(16711680 , p) , -16) ;
                %                 B=bitshift(bitand(65280 , p) , -8) ;
                
                R=bitshift(bitand(16711680 , p) , -16);  %colormap的后3个byte才是颜色字节
                G=bitshift(bitand(65280 , p) , -8) ;
                B=bitshift(bitand(255 , p) , 0);
                RGB(i,j,1) = R;
                RGB(i,j,2) = G;
                RGB(i,j,3) = B;
            end
        end
        RGB = uint8(RGB);   %转换成unit格式        
        imshow(RGB);        %显示图片
        
    case 16
        for i=1:biHeight  %发现：与c++不同，MATLAB的矩阵序号从1开始
            for j=1:biWidth
                k=(j-1)*biBitCount/8+1;
                p1=img(i,k);
                p2=img(i,k+1);
                pp1=str2num(dec2bin(p1));
                pp2=str2num(dec2bin(p2));
                p=bitshift(pp1,8)+pp2;
                R= bitshift(bitshift( bitand(31744 , p) ,-10),3);
                G=bitshift(bitshift(bitand(992 , p) ,-5),3);
                B= bitshift(bitshift( bitand(31 , p) , 0),3);
                RGB(i,j,1) = R;
                RGB(i,j,2) = G;
                RGB(i,j,3) = B;
            end
        end
        RGB = uint8(RGB);   %转换成unit格式
        imshow(RGB);        %显示图片
        
    case 24
        %分别取出RGB各个分量信息，再合成
        cloB = img(:,1:3:end);
        cloG = img(:,2:3:end);
        cloR = img(:,3:3:end);
        RGB(:,:,1) = cloR;
        RGB(:,:,2) = cloG;
        RGB(:,:,3) = cloB;
        RGB = uint8(RGB);   %转换成unit格式
        imshow(RGB);        %显示图片
        
    case 32
        %分别取出RGB各个分量信息，再合成
        cloB = img(:,1:4:end);
        cloG = img(:,2:4:end);
        cloR = img(:,3:4:end);
        RGB(:,:,1) = cloR;
        RGB(:,:,2) = cloG;
        RGB(:,:,3) = cloB;
        RGB = uint8(RGB);   %转换成unit格式
        imshow(RGB);        %显示图片
end

fclose(bmp);


% bmp = fopen(filename, 'rb');
% fpw=fopen('save.bmp','w');
% bf=fread(bmp,14,'long'); %图像文件头
% bi=fread(bmp,40,'long');  %图像文件头信息
% fwrite(fpw,bf)  %BMP文件头文件
% fwrite(fpw,bi)  %BMP文件头文件信息
% A=[0,0];
% fwrite(fpw,A)
% fwrite(fpw,img)
% fclose(fpw);
% imds1 = imageDatastore('cat_8bit.bmp');
% dataOut = read(imds1);

%存储图像
dataOut=imread(filename);
savefilename = ['save/',filename];
imwrite(dataOut,savefilename,'bmp');

%显示直方图
figure;
f=read(imageDatastore(filename));
if(bitnum<=8) 
    histrange = bitnum;
else
    histrange = 8;
end
bb=zeros(2^histrange,1);
size=size(f);
    for j=1:size(1)
        for k=1:size(2)
            bb(f(j,k,1)+1)=bb(f(j,k,1)+1)+1;
        end
    end
 bar(bb);
 pause(2);