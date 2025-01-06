
#include <stdlib.h>
#include "raylib.h"
#include "tmx.h"
#include "coll.h"
#include "enemdata.h"
#define ZOMBIES 8

Texture2D *LoadMapTexture(const char *fileName);
void UnloadMapTexture(Texture2D *tex);
void RenderTmxMapToFramebuf(const char *mapFileName, RenderTexture2D *buf);
RenderTexture2D mapFrameBuffer;

int isPlayerEnter(Rectangle R,Vector2 V);
int isPlayerEnterRec(Rectangle R[10],Vector2 V);
int obstclisnup(Vector2 pl);
int obstclisnlft(Vector2 pl);
int obstclisnrght(Vector2 pl);
void updateEnemies(Vector2 player,int k,int wchrec);
void draw(Texture2D enemies[4]);
void guiupdate();
void guidraw(Texture2D guitx[5],Texture2D message);
int conditone(Vector2 nokta);
int condittwo(Vector2 nokta);
int conditthre(Vector2 nokta);
int conditvor(Vector2 nokta);

/*enemie global variables*/
Vector2 *posEn;
Rectangle **situation; 
void copyV();
void copyR();

const int wi = 32;
const int hei = 32;
int counter[ZOMBIES] = {0,0,0,0,0,0,0,0};
int slow[ZOMBIES] = {60,60,60,60,60,60,60,60};
int kil[ZOMBIES] = {0,0,0,0,0,0,0,0};
int stat[ZOMBIES] = {1,1,1,1,1,1,1,1};
int stp[ZOMBIES] = {0,0,0,0,0,0,0,0};
Rectangle pl = {0,0,20,20};
Rectangle nok = {0,0,16,16};
int l,r,up,dow;
int pourcentagVie = 100;

/*gui global variables*/
Rectangle start = {338,172,110,29};
Rectangle cancell = {338,260,110,32};
Rectangle like = {338,216,110,30};
Rectangle leftbuttn = {272,144,16,16};
Rectangle rightbuttn = {512,144,16,16};
Rectangle helpbuttn = {16,16,16,16};
int leftbtnlig = 0;
int rightbtnlig = 0;
int helpbtnlig = 0; 
Rectangle textBox = {336,208,128,48};
int ligh1 = 0;
int ligh2 = 0;
int ligh3 = 0;
char name[9] = "\0";
portrait port = noura;
int letterCount = 0;
int mouseOnText = 0;
scren gamscren = star;
float blackScren = 1.0;
int mnL=0;
int wnL=0;
Rectangle manRe = {240,192,96,96};
Rectangle womenRe = {464,192,96,96};
int ongame = 0;
int helpscre = 0;
float whscr = 0.0;


/*pourcentage de vie texture's rectangle and vector2*/
Rectangle hearrec = {0,0,48,16};
Vector2 hearpos = {0,0};

int main()
{

    int screnHei = 464;
    int screnWidt = 800; 

    int cR,cL,cD,cU,cDor,cWay,cDor1,cDor2,obsl,obsl1,obsl2;
    cR = cL = cD = cU = cDor = cDor1 = cWay = cDor2 = obsl = obsl1 = obsl2 = 0;
    int wichRec,wichdor;
    int visite[5] = {0,0,0,0,0};
    int findKey0,findKey1,findKey2,findKey3,findkeyFreind;
    findKey0 = findKey2 = findKey3 = findKey1 = findkeyFreind = 0;
    int cachkey = 0;
    int opened0,opened1,opened2,opened3;
    opened0 = opened1 = opened2 = opened3 = 0;
    int getKey = 0;

    int ca1,ca21,ca22,ca23,ca24,ca31,ca32,ca33,ca34,ca35,ca36,click1,click2,click;
    int condit1,condit2,condit3,condit4;
    condit1=condit2=condit3=condit4=0;
    int follow = 0;

    InitWindow(screnWidt,screnHei,"BazineGame");
    /*27/06/2023 12:06*/
    Texture2D boden = LoadTexture("booden/topn.png");
    Texture2D cle = LoadTexture("booden/key.png");
    Texture2D remkey0 = LoadTexture("booden/uw.png");
/*    Texture2D remkey1 = LoadTexture("booden/trab.png");
    Texture2D remkey2 = LoadTexture("booden/un.png");*/
    Texture2D port = LoadTexture("booden/portraitt.png");
    Texture2D heart = LoadTexture("GUI/pict/vie.png");
    Texture2D message = LoadTexture("GUI/pict/mess.png");
    Texture2D sandok = LoadTexture("booden/sandk.png");
    Texture2D home = LoadTexture("booden/home.png");
    Texture2D pausee = LoadTexture("booden/pause.png");

    /*loading map - sprite begin*/
    RenderTmxMapToFramebuf("maps/dungen.tmx", &mapFrameBuffer);
    Texture2D sprite = LoadTexture("pictSprites/sprMp1.png");
    Texture2D spriteIdle = LoadTexture("pictSprites/idlplayer.png");
    float laard = sprite.width/5;
    float tool = sprite.height/4;
    Vector2 mawaie = {320,960}; //320,960 928,960 320,576
    Rectangle aham = {laard,0,laard,tool};
    Rectangle ahamidl = {0,0,laard,tool};
    Rectangle sprt = {mawaie.x,mawaie.y,32,32};
    int waiting = 1;
    /*loading map - sprite fin*/
    int nomSpr = 5;
    int law = 0;
    int fl = 0;
    float cond=0.064;
    int count = 0;
    int countidl=0;
    int count1 = 0;
    int vitess = 4;
    /*loading freind begin */
    Texture2D freind = LoadTexture("pictSprites/freind.png");
    Vector2 freindpos = {1016,854};
    Rectangle freinrec = {0,0,32,32};
    int parc = 0;
    int plu = 0;
    float cond2 = 0.096;
    int speed = 1;
    int rjaa = 1;
    int sir = 0;


 
    
    //---------------------------------Enemies loading textures------begin---------------------
    Texture2D enemieWalk = LoadTexture("pictSprites/Walk1.png");
    Texture2D enemieAttack = LoadTexture("pictSprites/Attack.png");
    Texture2D enemieDeath = LoadTexture("pictSprites/Death.png");
    Texture2D enemieIdl = LoadTexture("pictSprites/idle.png");
    Texture2D enem[4] = {enemieWalk,enemieAttack,enemieIdl,enemieDeath};

    posEn = (Vector2*)malloc(ZOMBIES*sizeof(Vector2));
    situation = (Rectangle**)malloc(ZOMBIES*sizeof(Rectangle*));
    for(int i=0;i<ZOMBIES;i++){
      situation[i] = (Rectangle*)malloc(4*sizeof(Rectangle));
    }
    copyV();
    copyR();
    int k = 0;
    //---------------------------------Enemies loading textures---fin------------------------
    //-----------------------------------gui loading texture---------begin-----------------
    Texture2D grap = LoadTexture("GUI/pict/gupli.png");
    Texture2D grap1 = LoadTexture("GUI/pict/guprini.png");
    Texture2D grap2 = LoadTexture("GUI/pict/guNmi.png");
    Texture2D man = LoadTexture("GUI/pict/man.png");
    Texture2D women = LoadTexture("GUI/pict/women.png");
    Texture2D guiTexures[5] = {grap,grap1,grap2,man,women};
    //-----------------------------------gui loading texture---------fin-----------------
    //set camera 
    Camera2D camera = { 0 };
    camera.offset = (Vector2){screnWidt/2.0f,screnHei/2.0f};
    camera.target = (Vector2){320.0f,960.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.2f;

 SetTargetFPS(60);
 while (!WindowShouldClose())
    {
        
//update

guiupdate();

if(ongame){   
      /*-----------------------------------part1 update---------------------------------------------*/
    if(blackScren>0) blackScren-=0.01;
    sprt.x = mawaie.x;
    sprt.y = mawaie.y;
    wichRec = isPlayerEnterRec(dataCol,mawaie);
/*    if(wichRec>=0){*/
        switch(wichRec){
            case 0 :{ visite[0]=1;
                      wichdor= 0;
                    if(CheckCollisionPointRec(keys[0],sprt)&&findKey0<=0&&!getKey){ // zat condition findkey0<=0 bax nxiki collision mra whda safi t9dr dir !findkey0 tahiya b7al b7al
                        findKey0 = 1;
                        getKey = 1; }
            }break;
            case 1 :{ visite[1]=1; 
                      wichdor= 1;
                    if(CheckCollisionPointRec(keys[1],sprt)&&findKey1<=0&&!getKey){ 
                        findKey1 = 1;
                        getKey = 1; }
            }break;
            case 2 :{ visite[2]=1;
                      wichdor= 23; 
                    if(CheckCollisionPointRec(keys[2],sprt)&&findKey2<=0&&!getKey){
                        findKey2 = 1;
                        getKey = 1; }
                    if(CheckCollisionPointRec(keys[3],sprt)&&findKey3<=0&&!getKey){
                        findKey3 = 1;
                        getKey = 1; }
                    if(CheckCollisionPointRec(dataopenDr[1],sprt)&&findkeyFreind){
                     opened1 = 1;
                     getKey = 0;
                    }

            }break;
            case 3 :{ visite[3]=1;
                      if(CheckCollisionPointRec(keys[4],sprt)&&findkeyFreind<=0&&!getKey){
                        findkeyFreind = 1;
                        getKey = 1;
                        cachkey=1;
                      }
             }break; // had lcase mazal madrt 3liha walo had sa3a ghi dayrha tma talmnb3d mli ndkhl enemies zombie 3ada nhawl nzid fiha xihaja
            case 4 :{ visite[4]=1; }break; // had lcase mazal madrt 3liha walo had sa3a ghi dayrha tma talmnb3d mli ndkhl enemies zombie 3ada nhawl nzid fiha xihaja
         }

        switch(wichdor){
            case 0 :{
                 cDor = (IsKeyDown(KEY_UP)&&(mawaie.y>=dataDors[wichdor].y)&&
                        (mawaie.y<=dataDors[wichdor].y+dataDors[wichdor].height)&&
                        (mawaie.x>=dataDors[wichdor].x)&&(mawaie.x<=dataDors[wichdor].x+dataDors[wichdor].width))&&findKey0;

                 if(cDor&&findKey0&&!opened0){
                    opened0 = 1;
                    getKey = 0; }
            }break;
            case 1 :{
                 cDor = (IsKeyDown(KEY_UP)&&(mawaie.y>=dataDors[wichdor].y)&&
                        (mawaie.y<=dataDors[wichdor].y+dataDors[wichdor].height)&&
                        (mawaie.x>=dataDors[wichdor].x)&&(mawaie.x<=dataDors[wichdor].x+dataDors[wichdor].width))&&findkeyFreind;

/*                 if(cDor&&findkeyFreind&&!opened1){
                    opened1 = 1;
                    getKey = 0; }*/
            }break;
            case 23 :{
                 cDor = ((IsKeyDown(KEY_UP)&&(mawaie.y>=dataDors[2].y)&&
                        (mawaie.y<=dataDors[2].y+dataDors[2].height)&&(mawaie.x>=dataDors[2].x)&&
                        (mawaie.x<=dataDors[2].x+dataDors[2].width)) && findKey2 );
                 cDor1 = ((IsKeyDown(KEY_UP)&&(mawaie.y>=dataDors[3].y)&&
                         (mawaie.y<=dataDors[3].y+dataDors[3].height)&&(mawaie.x>=dataDors[3].x)&&
                         (mawaie.x<=dataDors[3].x+dataDors[3].width)) && findKey3 );
                 cDor2 = IsKeyDown(KEY_UP)&&(mawaie.y>=dataDors[4].y)&&
                         (mawaie.y<=dataDors[4].y+dataDors[4].height)&&(mawaie.x>=dataDors[4].x)&&
                         (mawaie.x<=dataDors[4].x+dataDors[4].width);

                  if(cDor&&findKey2&&!opened2){
                    opened2 = 1;
                    getKey = 0; }

                  if(cDor1&&findKey3&&!opened3){
                    opened3 = 1;
                    getKey = 0; }
            }break;
        }
        /*obstacle -table-chairs....*/
        obsl = obstclisnup(mawaie);
        obsl1 = obstclisnlft(mawaie);
        obsl2 = obstclisnrght(mawaie);
        /*logique bach ila dghati 3la bzaf t les buttons mayt7arkx player*/
        ca1 = IsKeyDown(KEY_LEFT)&&IsKeyDown(KEY_RIGHT)&&IsKeyDown(KEY_DOWN)&&IsKeyDown(KEY_UP);
        ca21 = IsKeyDown(KEY_LEFT)&&IsKeyDown(KEY_RIGHT)&&IsKeyDown(KEY_DOWN);
        ca22 = IsKeyDown(KEY_LEFT)&&IsKeyDown(KEY_RIGHT)&&IsKeyDown(KEY_UP);
        ca23 = IsKeyDown(KEY_LEFT)&&IsKeyDown(KEY_UP)&&IsKeyDown(KEY_DOWN);
        ca24 = IsKeyDown(KEY_UP)&&IsKeyDown(KEY_RIGHT)&&IsKeyDown(KEY_DOWN); 
        ca31 = IsKeyDown(KEY_LEFT)&&IsKeyDown(KEY_RIGHT);
        ca32 = IsKeyDown(KEY_LEFT)&&IsKeyDown(KEY_UP);
        ca33 = IsKeyDown(KEY_LEFT)&&IsKeyDown(KEY_DOWN);
        ca34 = IsKeyDown(KEY_UP)&&IsKeyDown(KEY_RIGHT);
        ca35 = IsKeyDown(KEY_DOWN)&&IsKeyDown(KEY_RIGHT);
        ca36 = IsKeyDown(KEY_DOWN)&&IsKeyDown(KEY_UP);
        click1 = ca21||ca22||ca23||ca24;
        click2 = ca31||ca32||ca33||ca34||ca35||ca36;
        click = ca1||click1||click2; 
      /*------------------------------------------------------------------------------------------------------------------------------------------*/
      cR = mawaie.x<=dataCol[wichRec].x+dataCol[wichRec].width; 
      cL = mawaie.x>=dataCol[wichRec].x;
      cD = mawaie.y<=dataCol[wichRec].y+dataCol[wichRec].height;
      cU = mawaie.y>=dataCol[wichRec].y;
      /*cDor = (IsKeyDown(KEY_UP)&&(mawaie.y>=dataDors[wichdor].y)&&(mawaie.y<=dataDors[wichdor].y+dataDors[wichdor].height)&&(mawaie.x>=dataDors[wichdor].x)&&(mawaie.x<=dataDors[wichdor].x+dataDors[wichdor].width));*/
      cWay =( ( (IsKeyDown(KEY_DOWN)&&(mawaie.y>=dataWay[0].y)&&(mawaie.y<=dataWay[0].y+dataWay[0].height)&&(mawaie.x>=dataWay[0].x)&&(mawaie.x<=dataWay[0].x+dataWay[0].width)) ) && visite[0])||
            ( ( (IsKeyDown(KEY_DOWN)&&(mawaie.y>=dataWay[1].y)&&(mawaie.y<=dataWay[1].y+dataWay[1].height)&&(mawaie.x>=dataWay[1].x)&&(mawaie.x<=dataWay[1].x+dataWay[1].width)) ) && visite[3] && findkeyFreind)||
            ( ( (IsKeyDown(KEY_DOWN)&&(mawaie.y>=dataWay[2].y)&&(mawaie.y<=dataWay[2].y+dataWay[2].height)&&(mawaie.x>=dataWay[2].x)&&(mawaie.x<=dataWay[2].x+dataWay[2].width)) ) && visite[2])||
            ( ( (IsKeyDown(KEY_DOWN)&&(mawaie.y>=dataWay[3].y)&&(mawaie.y<=dataWay[3].y+dataWay[3].height)&&(mawaie.x>=dataWay[3].x)&&(mawaie.x<=dataWay[3].x+dataWay[3].width)) ) && visite[2]);


      /*had lcode bach nkhli player istadm bzombie lajah mn ayi jiha  ya3ni ikon tahowa b7al obstacl*/      
            condit1 = conditone(mawaie);
            condit2 = condittwo(mawaie);
            condit3 = conditthre(mawaie);
            condit4 = conditvor(mawaie);            

       /**/     

      if((!click)){
           if( ((IsKeyDown(KEY_RIGHT)) && cR && !obsl1 && !condit1) ){ 
                waiting = 0;
                aham.y = tool;
                mawaie.x+=vitess; 
                camera.target.x+=vitess; 
                law++;
                  if(law*GetFrameTime()>=cond){
                     law=0;
                     count++;
                     count%=nomSpr;
                     aham.x = laard*count;
                   } 
           }
           if( (IsKeyDown(KEY_LEFT) && cL && !obsl2 &&!condit2) ){ 
                waiting = 0;
                aham.y = 0;
                mawaie.x-=vitess;
                camera.target.x-=vitess;
                law++;
                  if(law*GetFrameTime()>=cond){
                     law=0;
                     count++;
                     count%=nomSpr;
                     aham.x= laard*count;
                   }
            }
           if( ((IsKeyDown(KEY_DOWN)&&cD)||cWay)&&!condit3){ 
                waiting = 0; 
                aham.y=tool*3;
                mawaie.y+=vitess;
                camera.target.y+=vitess;      
                law++;
                  if(law*GetFrameTime()>=cond){
                     law=0;
                     count1++;
                     count1%=nomSpr;
                     aham.x = laard*count1;
                  }
            }
           if(((IsKeyDown(KEY_UP)&&cU&&!obsl)||(cDor)||(cDor1)||(cDor2))&&!condit4){
                waiting = 0; 
                aham.y=2*tool;
                mawaie.y-=vitess;
                camera.target.y-=vitess;
                law++;
                  if(law*GetFrameTime()>=cond){
                     law=0;
                     count1++;
                     count1%=nomSpr;
                     aham.x = laard*count1;
                  }
            }
     }/*fin condition !click*/
//}
    
    if((!IsKeyDown(KEY_LEFT))&&(!IsKeyDown(KEY_UP))&&(!IsKeyDown(KEY_DOWN))&&(!IsKeyDown(KEY_RIGHT))) waiting = 1;
    if(waiting){
        ahamidl.y = aham.y;
        law++;
        if(law*GetFrameTime()>=cond*5){
            law = 0;
            countidl++;
            countidl%=nomSpr;
            ahamidl.x = laard*countidl;
        }
    } 

    /*had code ghi bach nkhli dak player mli madaghtx ba9i 3la bouton ihbas f position dyal wa9f maxi matalan iw9f lik ohowa dayr rjlo l9dam b7ala kaytmxa*/
    fl++;
    if(fl>=8&&!IsKeyDown(KEY_UP)&&!IsKeyDown(KEY_DOWN)&&!IsKeyDown(KEY_LEFT)&&!IsKeyDown(KEY_RIGHT)){
        fl=0;
        aham.x = laard;
        if(aham.y>=tool*3) aham.x = 0;   
    }
    /*fin dyal had lcode sghiwar*/
    /*freind begin*/
    if(!follow){

    if((freindpos.x+10<dataCol[1].x+dataCol[1].width)&&rjaa){
        parc++;
        freinrec.x = 0;
        freindpos.x+=speed;
        if(parc*GetFrameTime()>=cond2*2){
            parc=0;
            plu++;
            plu%=4;
            freinrec.y = plu*32;
        }
    }else{
     rjaa = 0;
     sir = 1;}
    if((freindpos.x>dataCol[1].x)&&sir){
        parc++;
        freinrec.x = 32*3;
        freindpos.x-=speed;
        if(parc*GetFrameTime()>=cond2*2){
            parc=0;
            plu++;
            plu%=4;
            freinrec.y = plu*32;
        }
    }else{
        sir = 0;
        rjaa = 1;
    }

   }

    if(visite[1]&&!follow) follow=1;

    //follow player
    
    /*freind end*/
                   
    /*-----------------------------------part2 update--------------------------Enemies-------------------*/
    k++;
    k%=ZOMBIES;
    updateEnemies(mawaie,k,wichRec);

 } //ongame condition end

    hearpos.x = mawaie.x+screnWidt*0.27;
    hearpos.y = mawaie.y-screnHei*0.37;

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(BLACK);
             guidraw(guiTexures,message); //gui
            BeginMode2D(camera);
              if(ongame){

                DrawTextureRec(
                    mapFrameBuffer.texture,                  
                    (Rectangle){0, 0, mapFrameBuffer.texture.width, -mapFrameBuffer.texture.height},
                    (Vector2){0.0, 0.0},
                    WHITE);
                /*----------------player draw-------------------*/

                /*kandir wahd tapie fax kanh7l lbab bax mayb9ax dak lgryaj*/
                if(opened0) DrawTexture(boden,dataopenDr[0].x,dataopenDr[0].y,WHITE); 
                if(opened1) DrawTexture(boden,dataopenDr[1].x,dataopenDr[1].y,WHITE); 
                if(opened2) DrawTexture(boden,dataopenDr[2].x,dataopenDr[2].y,WHITE); 
                if(opened3) DrawTexture(boden,dataopenDr[3].x,dataopenDr[3].y,WHITE); 
                /*kandir xil3iba fog dik lkey mnba3d makatakhdha dik l3iba likandir 3liha katkon hiya 3layx mhtota*/
                if(findKey0) DrawTexture(remkey0,keys[0].x,keys[0].y,WHITE); 
                if(findKey1) DrawTexture(remkey0,keys[1].x,keys[1].y,WHITE); 
                if(findKey2) DrawTexture(remkey0,keys[2].x,keys[2].y,WHITE); 
                if(findKey3) DrawTexture(remkey0,keys[3].x,keys[3].y,WHITE);
                if(findkeyFreind) DrawTexture(sandok,keys[4].x,keys[4].y,WHITE); 
                /*draw key symbole over head of the player lw9t likayl9a fiha lkey*/
                if(getKey)  DrawTexture(cle,mawaie.x+8,mawaie.y-8,WHITE);
               /*draw information de player begin*/

               DrawTexture(port,mawaie.x+screnWidt*0.34,mawaie.y-screnHei*0.38,WHITE); //khsni ndir switch tl portrait 

               DrawText(name,mawaie.x+screnWidt*0.28,mawaie.y-screnHei*0.38,10,WHITE); 
               DrawTextureRec(heart,hearrec,hearpos,WHITE);
               DrawText(TextFormat("%03i %",pourcentagVie),mawaie.x+screnWidt*0.28,mawaie.y-screnHei*0.34,8,WHITE);
               DrawTexture(home,mawaie.x-screnWidt*0.40,mawaie.y-screnHei*0.38,WHITE);
               /*DrawTexture(pausee,mawaie.x,mawaie.y-screnHei*0.38,WHITE);*/

               /*draw information de player fin*/
               /*draw freind begin*/
               DrawTextureRec(freind,freinrec,freindpos,WHITE);
               /*draw player begin*/
               if(waiting) DrawTextureRec(spriteIdle,ahamidl,mawaie,WHITE);   
               else DrawTextureRec(sprite,aham,mawaie,WHITE);
               /*draw player fin*/ 
               /*------------Enemies draw----------begin---------------*/
               draw(enem);
               /*------------Enemies draw----------fin---------------*/

             DrawRectangle(0,765,GetScreenWidth(),GetScreenHeight(),Fade(BLACK,blackScren));
             if(blackScren>0)
                DrawText(TextFormat("Here we go"),280,960,15,WHITE);   
            EndMode2D();
            } 
        EndDrawing();
        //----------------------------------------------------------------------------------
    }   
    UnloadRenderTexture(mapFrameBuffer);
    /*UnloadTexture(Texture2D texture);*/
    CloseWindow();        
    //--------------------------------------------------------------------------------------

    return 0;
}


int isPlayerEnter(Rectangle R,Vector2 V){
    int a,b,c,d;


    a = V.x>=R.x-32;
    b = V.y>=R.y-32;
    c = V.x <= R.x + R.width+32;
    d = V.y <= R.y + R.height+32;
    if(a&&b&&c&&d)
        return 1;
    return 0;
}

int isPlayerEnterRec(Rectangle R[10],Vector2 V){
    int a,b,c,d,i;
    for(i=0;i<10;i++){
    a = V.x>=R[i].x-20;
    b = V.y>=R[i].y-32;
    c = V.x <= R[i].x + R[i].width+20;
    d = V.y <= R[i].y + R[i].height+20;
    if(a&&b&&c&&d)
        return i;
    }
    return -1;

}

void copyV(){
    for(int i=0;i<ZOMBIES;i++)
        posEn[i] = posfl[i];

}

void copyR(){
    for(int i=0;i<ZOMBIES;i++){
        for(int j=0;j<4;j++){
            situation[i][j] = situa[i][j];
        }
    }
}

int obstclisnup(Vector2 pl){
    int a,b,c,d;
    for(int i=0;i<2;i++){
        a = pl.x >= obstacl[i].x;
        b = pl.x <= obstacl[i].x + obstacl[i].width;
        c = pl.y<= obstacl[i].y + obstacl[i].height;
        d = pl.y>= obstacl[i].y;
        if(a&&b&&c&&d)
            return 1; 
    }
    return 0;
}
int obstclisnlft(Vector2 pl){
    int a,b,c,d;
    for(int i=0;i<2;i++){
        a = pl.y >= obstacl[i].y;
        b = pl.y+8 <= obstacl[i].y + obstacl[i].height;
        c = pl.x+7<= obstacl[i].x;
        d = pl.x >= obstacl[i].x + obstacl[i].width;
        if(a&&b&&c&&d)
            return 1; 
    }
    return 0;
}
int obstclisnrght(Vector2 pl){
    int a,b,c,d;
    for(int i=0;i<2;i++){
        a = pl.y >= obstacl[i].y;
        b = pl.y+16 <= obstacl[i].y + obstacl[i].height;
        c = pl.x-8<= obstacl[i].x+obstacl[i].width;
        d = pl.x >=obstacl[i].x + obstacl[i].width;
        if(a&&b&&c&&d)
            return 1; 
    }
    return 0;
}
/*----------------------------------------------------------------------*/

Texture2D *LoadMapTexture(const char *fileName)
{
    Texture2D *tex = (Texture2D *)malloc(sizeof(Texture2D));
    if (tex != NULL) 
    {
        *tex = LoadTexture(fileName);
        TraceLog(LOG_INFO, "TMX texture loaded from %s", fileName);
        return tex;
    }
    return NULL;
}

void UnloadMapTexture(Texture2D *tex)
{
    if (tex != NULL) 
    {
        UnloadTexture(*tex);
        free(tex);
    }
}

void DrawTmxLayer(tmx_map *map, tmx_layer *layer)
{
    unsigned long row, col;
    unsigned int gid;
    unsigned int flip;
    tmx_tile *tile;
    unsigned int tile_width;
    unsigned int tile_height;
    Rectangle sourceRect;
    Rectangle destRect;
    Texture2D *tsTexture; // tileset texture
    float rotation = 0.0;
    Vector2 origin = {0.0, 0.0};

    for (row = 0; row < map->height; row++)
    {
        for (col = 0; col < map->width; col++)
        {
            gid = layer->content.gids[(row * map->width) + col];
            flip = gid & ~TMX_FLIP_BITS_REMOVAL;    // get flip operations from GID
            gid = gid & TMX_FLIP_BITS_REMOVAL;      // remove flip operations from GID to get tile ID
            tile = map->tiles[gid];
            if (tile != NULL)
            {
                // Get tile's texture out of the tileset texture
                if (tile->image != NULL)
                {
                    tsTexture = (Texture2D *)tile->image->resource_image;
                    tile_width = tile->image->width;
                    tile_height = tile->image->height;
                }
                else
                {
                    tsTexture = (Texture2D *)tile->tileset->image->resource_image;
                    tile_width = tile->tileset->tile_width;
                    tile_height = tile->tileset->tile_height;
                }

                sourceRect.x = tile->ul_x;
                sourceRect.y = tile->ul_y;
                sourceRect.width = destRect.width = tile_width;
                sourceRect.height = destRect.height = tile_height;
                destRect.x = col * tile_width;
                destRect.y = row * tile_height;

                // Deal with flips
                origin.x = 0.0;
                origin.y = 0.0;
                rotation = 0.0;
                switch(flip)
                {
                    case TMX_FLIPPED_DIAGONALLY:
                    {
                        sourceRect.height = -1 * sourceRect.height;
                        rotation = 90.0;
                    } break;
                    case TMX_FLIPPED_VERTICALLY:
                    {
                        sourceRect.height = -1 * sourceRect.height;
                    } break;
                    case TMX_FLIPPED_DIAGONALLY + TMX_FLIPPED_VERTICALLY:
                    {
                        rotation = -90.0;
                    } break;
                    case TMX_FLIPPED_HORIZONTALLY:
                    {
                        sourceRect.width = -1 * sourceRect.width;
                    } break;
                    case  TMX_FLIPPED_DIAGONALLY + TMX_FLIPPED_HORIZONTALLY:
                    {
                        rotation = 90.0;
                    } break;
                    case TMX_FLIPPED_HORIZONTALLY + TMX_FLIPPED_VERTICALLY:
                    {
                        rotation = 180.0;
                    } break;
                    case TMX_FLIPPED_DIAGONALLY + TMX_FLIPPED_HORIZONTALLY + TMX_FLIPPED_VERTICALLY:
                    {
                        sourceRect.width = -1 * sourceRect.width;
                        rotation = 90.0;
                    } break;
                    default:
                    {
                        origin.x = 0.0;
                        origin.y = 0.0;
                        rotation = 0.0;
                    } break;
                }

                // Adjust origin to rotate around the center of the tile, 
                // which means destination recangle's origin must be adjusted.
                if (rotation != 0.0)
                {
                    origin.x = tile_width / 2;
                    origin.y = tile_height / 2;
                    destRect.x += tile_width / 2;
                    destRect.y += tile_height / 2;
                }

                // TODO: Take layer opacity into account
                DrawTexturePro(*tsTexture, sourceRect, destRect, origin, rotation, WHITE);
            }
        }
    }
}

void RenderTmxMapToFramebuf(const char *mapFileName, RenderTexture2D *buf)
{
    tmx_layer *layer = NULL;

    // Setting these two function pointers allows TMX lib to load the tileset graphics and
    // set each tile's resource_image property properly.
    tmx_img_load_func = (void *(*)(const char *))LoadMapTexture;
    tmx_img_free_func = (void (*)(void *))UnloadMapTexture;
    tmx_map *mapTmx = tmx_load(mapFileName);
    if (mapTmx == NULL) {
        tmx_perror("tmx_load");
        return;
    }

    // Create a frame buffer
    // TODO: I don't life loading the RenderTexture here and unloading it in main(), but map info is needed to 
    // allocate the buffer of the right size, so either load it here, or separate tmx_load part of the code into
    // a separate function to allow the application code to call LoadRenderTexture between tmx_load and actual
    // drawing of the map.
    *buf = LoadRenderTexture(mapTmx->width * mapTmx->tile_width, mapTmx->height * mapTmx->tile_height);

    BeginTextureMode(*buf); // start rendering into the buffer
        ClearBackground(SKYBLUE);
        // Iterate through TMX layers rendering them into buf
        layer = mapTmx->ly_head;
        while(layer)
        {
            if (layer->visible)
            {
                switch(layer->type)
                {
                    case L_LAYER:
                    {
                        TraceLog(LOG_INFO, "Render TMX layer \"%s\"", layer->name);
                        DrawTmxLayer(mapTmx, layer);
                    } break;

                    // Group, Object and Image layer types are not implemented in this example
                    case L_GROUP:   // deliberate fall-through
                    case L_OBJGR:
                    case L_IMAGE:
                    case L_NONE:
                    default:
                        break;
                }
            }
            layer = layer->next;
        }
    EndTextureMode();   // stop rendering into the buffer

    tmx_map_free(mapTmx);
}




void guiupdate(){
        switch(gamscren){
            case star:{
            ongame = 0;
          if(!helpscre){    
            if(blackScren>0) blackScren-=0.01;  
            if(CheckCollisionPointRec(GetMousePosition(),start)){
               if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                blackScren = 1.0;
                gamscren = menu;
               }
                ligh1 = 1;
            }else ligh1 = 0;
            if(CheckCollisionPointRec(GetMousePosition(),cancell)) ligh2 = 1;
            else ligh2 = 0;
            if(CheckCollisionPointRec(GetMousePosition(),like)){
               if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) OpenURL("https://www.plugtutoerttt.infinityfreeapp.com");
               ligh3 = 1;
            }else ligh3 = 0;
            if(CheckCollisionPointRec(GetMousePosition(),helpbuttn)){
                helpbtnlig = 1;
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                    helpscre = 1;
                    whscr = 0.0;
                }   
            }else helpbtnlig = 0;
          }
          if(!CheckCollisionPointRec(GetMousePosition(),helpbuttn)){
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) helpscre = 0; 
          } 
          if(whscr<0.1) whscr+=0.01;
            }break;
            case menu:{
            ongame = 0;
          if(!helpscre){
            if(blackScren>0) blackScren-=0.01;  
            /*portrait choise begin*/
                if(CheckCollisionPointRec(GetMousePosition(),manRe)){
                    mnL = 1;
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        blackScren = 1.0;
                        port = taoufik;
                        gamscren = namm;
                    }
                }else mnL = 0;
                if(CheckCollisionPointRec(GetMousePosition(),womenRe)){
                    wnL = 1;
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        blackScren = 1;
                        port = noura;
                        gamscren = namm;
                    }
                }else wnL = 0;
              if(CheckCollisionPointRec(GetMousePosition(),helpbuttn)){
                helpbtnlig = 1;
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                  helpscre = 1;
                  whscr = 0.0;  
                }   
              }else helpbtnlig = 0;

            }
          if(!CheckCollisionPointRec(GetMousePosition(),helpbuttn)){
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) helpscre = 0; 
          } 
          if(whscr<0.1) whscr+=0.01;
            /*portrait choise end*/
            //end menu screen

            }break;
            case namm:{
                ongame = 0;
                if(blackScren>0) blackScren-=0.01; 
                if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = 1;
                else mouseOnText = 0;

                if(CheckCollisionPointRec(GetMousePosition(),leftbuttn)){
                    leftbtnlig = 1;
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        blackScren = 1;
                        gamscren = menu;
                    } 
                }else leftbtnlig = 0;
                if(CheckCollisionPointRec(GetMousePosition(),rightbuttn)){
                    rightbtnlig = 1;
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
                        blackScren = 1;
                        gamscren = gam;
                    } 
                }else rightbtnlig = 0;

                if (mouseOnText)
                    {
                        SetMouseCursor(MOUSE_CURSOR_IBEAM);
                        int key = GetCharPressed();
                        while (key > 0)
                        {
                            if ((key >= 32) && (key <= 125) && (letterCount < 7))
                                {
                                    name[letterCount] = (char)key;
                                    name[letterCount+1] = '\0'; 
                                    letterCount++;
                                }
                            key = GetCharPressed(); 
                        }
                    if (IsKeyPressed(KEY_BACKSPACE))
                       {
                          letterCount--;
                          if (letterCount < 0) letterCount = 0;
                          name[letterCount] = '\0';
                       }
                }else SetMouseCursor(MOUSE_CURSOR_DEFAULT);
            }break;
            case gam :{
                ongame = 1;
            }break;
        }
}

void guidraw(Texture2D guitx[5],Texture2D message){
            switch(gamscren){
              case star:{
                DrawTexture(guitx[0],0,0,WHITE);
                    if(ligh1) DrawRectangleRec(start,Fade(DARKBLUE,0.05));
                    if(ligh2) DrawRectangleRec(cancell,Fade(DARKBLUE,0.05));
                    if(ligh3) DrawRectangleRec(like,Fade(DARKBLUE,0.05));
                    if(helpbtnlig) DrawRectangleRec(helpbuttn,Fade(WHITE,0.4));
                    if(helpscre){
                        DrawRectangle(0,0,GetScreenWidth(),GetScreenHeight(),Fade(WHITE,whscr));
                        DrawTexture(message,160,128,WHITE);
                    } 
              }break;
              case menu:{
                DrawTexture(guitx[1],0,0,WHITE);
                DrawTexture(guitx[3],256,208,WHITE);
                DrawTexture(guitx[4],480,208,WHITE);
                DrawRectangleLines(240,192,96,96,WHITE);
                DrawRectangleLines(464,192,96,96,WHITE);
                if(mnL) DrawRectangleRec(manRe,Fade(BLACK,0.3));
                if(wnL) DrawRectangleRec(womenRe,Fade(BLACK,0.3));
                if(helpbtnlig) DrawRectangleRec(helpbuttn,Fade(WHITE,0.4));
                if(helpscre){
                    DrawRectangle(0,0,GetScreenWidth(),GetScreenHeight(),Fade(WHITE,whscr));
                    DrawTexture(message,160,128,WHITE);
                 } 
              }break;
              case namm:{
                DrawTexture(guitx[2],0,0,WHITE);
                if (mouseOnText) 
                    DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height,BLANK);
                else 
                    DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height,BLANK);
                DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 30, BLACK);
                if(leftbtnlig) DrawRectangleRec(leftbuttn,Fade(WHITE,0.4));
                if(rightbtnlig) DrawRectangleRec(rightbuttn,Fade(WHITE,0.4));

              } break; 
            }
            DrawRectangle(0,0,GetScreenWidth(),GetScreenHeight(),Fade(BLACK,blackScren));   
}





void updateEnemies(Vector2 nokta,int k,int wchrec){
            nok.x = nokta.x;
            nok.y = nokta.y;
            pl.x = posEn[k].x;
            pl.y = posEn[k].y;
            if(CheckCollisionRecs(nok,pl)&&IsKeyPressed(KEY_SPACE)) kil[k]+=1;
            
            switch(stat[k]){
                case 1 :{
                if(!wchrec){
                     //condition to attack player begin
                     l = posEn[k].x>=nokta.x+9;
                     r = posEn[k].x+9<=nokta.x;
                     up = (posEn[k].y>=nokta.y+9)&&(posEn[k].x>=nokta.x-10)&&(posEn[k].x<=nokta.x+10);
                     dow = (posEn[k].y+9<=nokta.y)&&(posEn[k].x>=nokta.x-10)&&(posEn[k].x<=nokta.x+10);
                     //condition to attack player fin
                 if(r){
                        stp[k] = 0;
                        situation[k][0].y = hei*2;   
                        posEn[k].x+=2;
                        slow[k]+=10;
                        if(slow[k]*GetFrameTime()>=0.3){
                           slow[k] = 60;
                           counter[k]++;
                           counter[k]%=10;
                           situation[k][0].x = wi*counter[k];
                        }
                  }
                 if(l){
                        stp[k] = 0;
                        situation[k][0].y = hei*3;   
                        posEn[k].x-=2;
                        slow[k]+=10;
                        if(slow[k]*GetFrameTime()>=0.3){
                           slow[k] = 60;
                           counter[k]++;
                           counter[k]%=10;
                           situation[k][0].x = wi*counter[k];
                         }   
                  }
                 if(up){
                        stp[k] = 0;
                        situation[k][0].y = hei;   
                        posEn[k].y-=2;
                        slow[k]+=10;
                        if(slow[k]*GetFrameTime()>=0.3){
                           slow[k] = 60;
                           counter[k]++;
                           counter[k]%=10;
                           situation[k][0].x = wi*counter[k];
                         }   
                  }
                 if(dow){
                        stp[k] = 0;
                        situation[k][0].y = 0;   
                        posEn[k].y+=2;
                        slow[k]+=10;
                        if(slow[k]*GetFrameTime()>=0.3){
                           slow[k] = 60;
                           counter[k]++;
                           counter[k]%=10;
                           situation[k][0].x = wi*counter[k];
                        }   
                  }
                }else{
                        stp[k] = 1;
                        situation[k][3].y = situation[k][0].y;
                        slow[k]+=10;
                        if(slow[k]*GetFrameTime()>=0.4){
                           slow[k] = 60;
                           counter[k]++;
                           counter[k]%=5;
                           situation[k][3].x = wi*counter[k];
                        }  
                }

                if(CheckCollisionRecs(nok,pl)) stat[k] = 2;    
                }break;

                case 2 :{
                 pourcentagVie-=1;   
                 situation[k][1].y = situation[k][0].y;
                 slow[k]+=10;
                 if(slow[k]*GetFrameTime()>=0.4){
                      slow[k] = 60;
                      counter[k]++;
                      counter[k]%=8;
                      situation[k][1].x = wi*counter[k];
                      /*life-=10;*/
                 }
                 if(pourcentagVie<=84&&pourcentagVie>=68) hearrec.x = 48;
                 if(pourcentagVie<68&&pourcentagVie>=52) hearrec.x = 48*2;
                 if(pourcentagVie<52&&pourcentagVie>=36) hearrec.x = 48*3;
                 if(pourcentagVie<36&&pourcentagVie>=20) hearrec.x = 48*4;
                 if(pourcentagVie<20) hearrec.x = 48*5;



                 if(kil[k]>=5){
                    counter[k] = 0;
                    stat[k] = 3;
                 }
                 if(!CheckCollisionRecs(nok,pl)) stat[k] = 1;
                    
                }break;
                case 3 :{
                 situation[k][2].y =situation[k][0].y;
                 if(counter[k]<6){
                      slow[k]+=10;
                      if(slow[k]*GetFrameTime()>=1.6){
                         slow[k] = 60;
                         counter[k]++;
                         counter[k]%=7;
                         situation[k][2].x = wi*counter[k];    
                        }
                 }

                }break;
            }

}

void draw(Texture2D enemies[4]){

            switch(stat[0]){
                case 1:{
                    if(stp[0]) DrawTextureRec(enemies[2],situation[0][3],posEn[0],WHITE);
                    else DrawTextureRec(enemies[0],situation[0][0],posEn[0],WHITE);
                }break;
                case 2:{ DrawTextureRec(enemies[1],situation[0][1],posEn[0],WHITE); }break;
                case 3:{ DrawTextureRec(enemies[3],situation[0][2],posEn[0],WHITE); }break;
                }
            //------------------
            switch(stat[1]){
                case 1:{
                    if(stp[1]) DrawTextureRec(enemies[2],situation[1][3],posEn[1],WHITE);
                    else DrawTextureRec(enemies[0],situation[1][0],posEn[1],WHITE);
                }break;
                case 2:{ DrawTextureRec(enemies[1],situation[1][1],posEn[1],WHITE); }break;
                case 3:{ DrawTextureRec(enemies[3],situation[1][2],posEn[1],WHITE); }break;
                }
            //------------------
            switch(stat[2]){
                case 1:{
                    if(stp[2]) DrawTextureRec(enemies[2],situation[2][3],posEn[2],WHITE);
                    else DrawTextureRec(enemies[0],situation[2][0],posEn[2],WHITE);
                }break;
                case 2:{ DrawTextureRec(enemies[1],situation[2][1],posEn[2],WHITE); }break;
                case 3:{ DrawTextureRec(enemies[3],situation[2][2],posEn[2],WHITE); }break;
                }
            //------------------
            switch(stat[3]){
                case 1:{
                    if(stp[3]) DrawTextureRec(enemies[2],situation[3][3],posEn[3],WHITE);
                    else DrawTextureRec(enemies[0],situation[3][0],posEn[3],WHITE);
                }break;
                case 2:{ DrawTextureRec(enemies[1],situation[3][1],posEn[3],WHITE); }break;
                case 3:{ DrawTextureRec(enemies[3],situation[3][2],posEn[3],WHITE); }break;
                }

            switch(stat[4]){
                case 1:{
                    if(stp[4]) DrawTextureRec(enemies[2],situation[4][3],posEn[4],WHITE);
                    else DrawTextureRec(enemies[0],situation[4][0],posEn[4],WHITE);
                }break;
                case 2:{ DrawTextureRec(enemies[1],situation[4][1],posEn[4],WHITE); }break;
                case 3:{ DrawTextureRec(enemies[3],situation[4][2],posEn[4],WHITE); }break;
                }
            //------------------
            switch(stat[5]){
                case 1:{
                    if(stp[5]) DrawTextureRec(enemies[2],situation[5][3],posEn[5],WHITE);
                    else DrawTextureRec(enemies[0],situation[5][0],posEn[5],WHITE);
                }break;
                case 2:{ DrawTextureRec(enemies[1],situation[5][1],posEn[5],WHITE); }break;
                case 3:{ DrawTextureRec(enemies[3],situation[5][2],posEn[5],WHITE); }break;
                }
            //------------------
            switch(stat[6]){
                case 1:{
                    if(stp[6]) DrawTextureRec(enemies[2],situation[6][3],posEn[6],WHITE);
                    else DrawTextureRec(enemies[0],situation[6][0],posEn[6],WHITE);
                }break;
                case 2:{ DrawTextureRec(enemies[1],situation[6][1],posEn[6],WHITE); }break;
                case 3:{ DrawTextureRec(enemies[3],situation[6][2],posEn[6],WHITE); }break;
                }
            //------------------
            switch(stat[7]){
                case 1:{
                    if(stp[7]) DrawTextureRec(enemies[2],situation[7][3],posEn[7],WHITE);
                    else DrawTextureRec(enemies[0],situation[7][0],posEn[7],WHITE);
                }break;
                case 2:{ DrawTextureRec(enemies[1],situation[7][1],posEn[7],WHITE); }break;
                case 3:{ DrawTextureRec(enemies[3],situation[7][2],posEn[7],WHITE); }break;
                }


}


int conditone(Vector2 nokta){
    for(int k=0;k<ZOMBIES;k++){
        if(IsKeyDown(KEY_RIGHT)&&(nokta.x+16>=posEn[k].x+2)&&(nokta.x<posEn[k].x+16-2)&&(nokta.y+16>=posEn[k].y)&&(nokta.y+8<=posEn[k].y+32))
            return 1;
    }
    return 0;
}

int condittwo(Vector2 nokta){
    for(int k=0;k<ZOMBIES;k++){
        if(IsKeyDown(KEY_LEFT)&&(nokta.x<=posEn[k].x+16+2)&&(nokta.x>posEn[k].x-2)&&(nokta.y+16>=posEn[k].y)&&(nokta.y+8<=posEn[k].y+32))
            return 1;
    }
    return 0;
}

int conditthre(Vector2 nokta){
    for(int k=0;k<ZOMBIES;k++){
        if(IsKeyDown(KEY_DOWN)&&(nokta.y+16>=posEn[k].y-2)&&(nokta.y<posEn[k].y+16+2)&&(nokta.x+16>=posEn[k].x)&&(nokta.x+16<=posEn[k].x+32))
            return 1;
    }
    return 0;
}

int conditvor(Vector2 nokta){
    for(int k=0;k<ZOMBIES;k++){
        if(IsKeyDown(KEY_UP)&&(nokta.y+16<=posEn[k].y+32-2)&&(nokta.y>=posEn[k].y+16+2)&&(nokta.x+16>=posEn[k].x)&&(nokta.x+16<=posEn[k].x+32))
            return 1;
    }
    return 0;
}
