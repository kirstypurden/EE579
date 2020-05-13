image = zeros(500);
image2 = zeros(500);
image3 = zeros(500);

%image = imread('Circles.jpg');
%image = im2bw(image, 0.5);
%image = ~image;

circles = circleMatrix(30);
circleDim =size(circles,1) - 1;

image(50:50+circleDim, 50:50+circleDim) = circles;
image(300:300+circleDim, 90:90+circleDim) = circles;
image(60:60+circleDim, 400:400+circleDim) = circles;
image = imfill(image);
[distMap, distImage] = distanceMap(image);

image2(90:90+circleDim, 30:30+circleDim) = circles;
image2(300:300+circleDim, 290:290+circleDim) = circles;
image2(360:360+circleDim, 420:420+circleDim) = circles;
image2 = imfill(image2);
[distMap2, distImage2] = distanceMap(image2);


image3(150:150+circleDim, 40:40+circleDim) = circles;
image3(400:400+circleDim, 190:190+circleDim) = circles;
image3(160:160+circleDim, 400:400+circleDim) = circles;
image3 = imfill(image3);
[distMap3, distImage3] = distanceMap(image3);

image = repmat(image,[1,1,3]);
image(240:260,240:260,2:3) = 1;
imageWithDistance = image;
imageWithDistance(:,:,1) = imageWithDistance(:,:,1) + distImage;

image2 = repmat(image2,[1,1,3]);
image2(240:260,240:260,2:3) = 1;
imageWithDistance2 = image2;
imageWithDistance2(:,:,1) = imageWithDistance2(:,:,1) + distImage2;

image3 = repmat(image3,[1,1,3]);
image3(240:260,240:260,2:3) = 1;
imageWithDistance3 = image3;
imageWithDistance3(:,:,1) = imageWithDistance3(:,:,1) + distImage3;

figure(1);
subplot(3,4,1);
imshow(image);
title('Skittle Layout 1');
subplot(3,4,2);
imshow(imageWithDistance);
title('Distance Simulation');
subplot(3,4,3);
plot(distMap);
title('Distance Map');
xlabel('Angle (°)');
ylabel('Distance (cm)');
subplot(3,4,4);
plot(diff(distMap));
title('Distance Map Derivative');
xlabel('Angle (°)');
ylabel("F'(X)");

subplot(3,4,5);
imshow(image2);
title('Skittle Layout 2');
subplot(3,4,6);
imshow(imageWithDistance2);
subplot(3,4,7);
plot(distMap2);
xlabel('Angle (°)');
ylabel('Distance (cm)');
subplot(3,4,8);
plot(diff(distMap2));
xlabel('Angle (°)');
ylabel("F'(X)");

subplot(3,4,9);
imshow(image3);
title('Skittle Layout 3');
subplot(3,4,10);
imshow(imageWithDistance3);
subplot(3,4,11);
plot(distMap3);
xlabel('Angle (°)');
ylabel('Distance (cm)');
subplot(3,4,12);
plot(diff(distMap3));
xlabel('Angle (°)');
ylabel("F'(X)");


figure(2)
imshow(distImage);
 
figure(3);
plot(distMap);
 
figure(4);
plot(diff(distMap));

figure(5);
plot(diff(diff(distMap)));


function [distMap, distImage] = distanceMap(image)

    [Y, X] = size(image);
    centreX = round(X/2);
    centreY = round(Y/2);

    distImage = zeros(size(image));

    distMap = zeros(1,360);

    for deg=1:360
        pointFound = false;
        verDist=0;
        horDist=0;
        ajDist=0;
        opDist=0;

        while ~pointFound
            if deg == 0 | deg == 180 | deg == 360    % Vertical line
                ajDist = ajDist + 1;
            %elseif deg == 90 | deg == 270    % Horizontal line
            %    opDist = opDist + 1;

            else
                if deg > 270
                    quadDeg = deg - 270; % Local quadrant angle
                elseif deg >180
                    quadDeg = deg - 180;
                elseif deg > 90
                    quadDeg = deg - 90;
                else
                    quadDeg = deg;
                end

                if quadDeg <= 45
                    ajDist=ajDist+1;
                    opDist=round(ajDist*tan(deg2rad(quadDeg)));
                else
                    opDist=opDist+1;
                    ajDist=round(opDist/tan(deg2rad(quadDeg)));
                end
            end

            if deg <= 90
                pointX = centreX+opDist;
                pointY = centreY-ajDist; % (pixel 1 at top of image)
            elseif deg <= 180
                pointX = centreX+opDist;
                pointY = centreY+ajDist;
            elseif deg <= 270
                pointX = centreX-opDist;
                pointY = centreY+ajDist;
            else
                pointX = centreX-opDist;
                pointY = centreY-ajDist;
            end

            %If image edge found
            if pointX <= 1 | pointX >= X | pointY <=1 | pointY >= Y
                pointFound = true;
                % Ensure point does not exceed image bounds
                if pointX < 1
                    pointX = 1;
                end
                if pointY < 1
                    pointY = 1;
                end
                if pointX > X
                    pointX = X;
                end
                if pointY > Y
                    pointY = Y;
                end
            elseif image(pointY, pointX) == 1       % (rows, cols : Y, X)
                pointFound = true;  
            end

            if pointFound == true
                dis = sqrt(ajDist*ajDist + opDist*opDist);
                distMap(deg) = dis;

                %deg
                %dis
                %pointX
                %pointY
                %ajDist
                %opDist
                
                % Plot 9x9 square around point
                for x=-5:5
                    for y=-5:5
                        if pointX+x <= X & pointX+x >= 1 & pointY+y <= Y & pointY+y >= 1
                            distImage(pointY+y, pointX+x) = 1;
                        end
                    end
                end
            end
        end
    end
end
    
   
 