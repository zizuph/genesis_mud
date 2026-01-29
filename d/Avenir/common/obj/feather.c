// /d/Avenir/common/obj/feather.c  
// This is an object cloned by bazaar/intr/apothstore.c
// It may be used for magical (spellcasting) purposes.
// It produces random feathers and adjectives.
// Lilith Feb 1997

inherit "/std/object";
#include "/d/Avenir/common/common.h"

string metl;
string randmetl();
void set_metl(string str) {    metl = str;    }

void
init_the_feather()
{
    if (!metl) metl = randmetl();

    set_short(""+ metl + " feather");
    set_long("This is a "+ metl +" feather from an unknown creature "+
        "that is most likely a bird.\n");
    add_name(metl +" feather");
    set_adj(({ metl }));

    return;        
}

/*************** Creation ************/
void
create_object()
{
   init_the_feather();
   add_name(({"_magical_ingredient"}));
   set_name("feather");

   add_prop(OBJ_I_VOLUME, 10);   
   add_prop(OBJ_I_WEIGHT, 1);   
   add_prop(OBJ_I_VALUE, 10 + (random(100)));
}             

string
randmetl()
{
    string str;

    switch(random(9))
    {   
        case 0: str="blue";        break;
        case 1: str="green";       break;
        case 2: str="blue-green";  break;
        case 3: str="black";       break;
        case 4: str="speckled";    break;
        case 5: str="brown";       break;
        case 6: str="pink";        break;
        case 7: str="white";       break;
        case 8: str="gray";        break;
    }
    return str;                                                                               
}


string 
query_recover()
{
    string rec;
    rec = MASTER + ":";
 
    rec += "#metl#" + metl;

    return rec;
}


void init_recover(string arg)
{
    string dummy;
    int i_check;

    sscanf(arg, "%s#metl#%s#%s", dummy, metl, dummy);

    init_the_feather();

    return;
}
