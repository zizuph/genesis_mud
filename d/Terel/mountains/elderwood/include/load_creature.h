#define MONSTER_DIR      "/d/Terel/mountains/elderwood/monster/"


string *birds   = ({"bird","falcon"}),
       *small   = ({"rodent","squirrel","rabbit","pfox","hare","ferret"}),
       *large   = ({"deer","caribou","moose","mbear"});



check_critter()
{
    object *critter;
    int i,flag;

    critter = TO->query_prop("forest_creatures");
    flag = 0;
    for (i=0; i<sizeof(critter); i++)
        if (creature[i]->query_prop("forest_creatures"))
            {flag++; break;}
    if (flag) return 0;

}



void
load_creature()
{
    seteuid(getuid(this_object()));     
  
       switch(random(3)) 
       {
         case 0 :  clone_object(MONSTER_DIR + birds[random(sizeof(birds))])->move(TO);
                    break;
         case 1 :  clone_object(MONSTER_DIR + small[random(sizeof(small))])->move(TO);
                    break;
        case 2 :  large=clone_object(MONSTER_DIR + large[random(sizeof(large))])->move(TO);
                      break;
       }
       return;
}

 
