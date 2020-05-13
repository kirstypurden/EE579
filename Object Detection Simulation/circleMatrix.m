function array = circleMatrix(r)
    array = zeros(2*r+1, 2*r+1);

    centre = r+1;
    
    for x=1:2*r:2*r+1       
        for y=1:2*r+1
            opp = x-centre;
            adj = y-centre;
            angle = atan(opp/adj);
            
            circleX = centre - round(r*sin(angle));
            
            if y < centre
                circleY = centre - round(r*cos(angle));
            else
                circleY = centre + round(r*cos(angle));
            end
            
            
            
            array(circleX, circleY) = 1;
        end
    end
    
    for x=1:2*r+1       
        for y=1:2*r:2*r+1
            opp = x-centre;
            adj = y-centre;
            angle = atan(opp/adj);
            
            circleX = centre - round(r*sin(angle));
         
            if y < centre
                circleY = centre - round(r*cos(angle));
            else
                circleY = centre + round(r*cos(angle));
            end
            
            array(circleX, circleY) = 1;
        end
    end
   
end



