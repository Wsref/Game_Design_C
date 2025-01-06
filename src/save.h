/*

      cR = mawaie.x<=dataCol[0].x+dataCol[0].width; 
      cL = mawaie.x>=dataCol[0].x;
      cD = mawaie.y<=dataCol[0].y+dataCol[0].height;
      cU = mawaie.y>=dataCol[0].y;
      cDor = (IsKeyDown(KEY_UP)&&(mawaie.y<=dataCol[0].y)&&(mawaie.x>=dataDors[0].x)&&(mawaie.x<=dataDors[0].x+dataDors[0].width));
      

      
      if( ((IsKeyDown(KEY_RIGHT)) && cR)||( (IsKeyDown(KEY_RIGHT)) && (!isPlayerEnter(dataCol[0],mawaie)) ) ){ 
            aham.y = tool;

             law++;
             if(law>=cond){
                 law=0;
                count++;
                count%=nomSpr;
                aham.x = laard*count;
                mawaie.x+=laard; 
                camera.target.x+=laard; 
            } 

        }

       if( (IsKeyDown(KEY_LEFT)&&cL) ||( (IsKeyDown(KEY_LEFT)) && (!isPlayerEnter(dataCol[0],mawaie)) ) ){ 
            aham.y = 0;

            law++;
            if(law>=cond){
                law=0;
                count++;
                count%=nomSpr;
                aham.x= laard*count;
                mawaie.x-=laard;
                camera.target.x-=laard;
            }
            
       }
       if( (IsKeyDown(KEY_DOWN)&&cD) ||( (IsKeyDown(KEY_DOWN)) && (!isPlayerEnter(dataCol[0],mawaie)) ) ){  
            aham.y=tool*3;
            law++;
            if(law>=cond){
                law=0;
                count1++;
                count1%=nomSpr;
                aham.x = laard*count1;
                mawaie.y+=tool;
                camera.target.y+=laard;      
            }

       }

       if((IsKeyDown(KEY_UP)&&cU)||(cDor)||((IsKeyDown(KEY_UP))&&(!isPlayerEnter(dataCol[0],mawaie)))){ 
            aham.y=2*tool;
            law++;
            if(law>=cond){
                law=0;
                count1++;
                count1%=nomSpr;
                aham.x = laard*count1;
                mawaie.y-=tool;
                camera.target.y-=laard;
            }
       }

*/