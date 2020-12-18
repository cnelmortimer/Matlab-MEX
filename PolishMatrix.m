function outMatrix = PolishMatrix(matrix, scope)
    [rows, cols] = size(matrix);
    outMatrix = zeros(rows, cols);
    
    lenBuffer = (2*scope + 1)^2;
    buffer = zeros(lenBuffer, 1);
        
    for i=1:1:cols
       for j=1:1:rows
           buffer = buffer*0;
           inBuffer = 0;           
           for k=(i-scope):1:(i+scope)
               focusK = k;
               if(k<1)
                   focusK=1;
               elseif(k>cols)
                   focusK = cols;
               end
               for m=(j-scope):1:(j+scope)
                   focusM = m;
                   if(m<1)
                       focusM=1;
                   elseif(m>rows)
                       focusM = rows;
                   end
                   inBuffer = inBuffer + 1;
                   buffer(inBuffer) = matrix(focusM, focusK);
               end
           end
           outMatrix(j, i) = median(buffer); % Median filter
       end
    end    
end
