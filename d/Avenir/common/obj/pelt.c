// /d/Avenir/common/obj/pelt.c  
// This is an object cloned by bazaar/intr/apothstore.c
// It may be used for magical (spellcasting) purposes.
// It produces nine random pelt/skin types and adjectives.
// Lilith Feb 1997
// Lilith Jun 2004: added name that smiths code checks for.

inherit "/std/object";
#include "/d/Avenir/common/common.h"

string metl, type;
string randtype();
string randmetl();

void set_metl(string str) {    metl = str;    }
void set_type(string str) {    type = str;    }

void
init_the_pelt()
{
    if (!metl) metl = randmetl();
    if (!type) type = randtype();

    set_short(""+ metl + " " + type + " pelt");
    set_long("This is the "+ metl +" pelt of a "+ type +".\n");
    add_name(type +" pelt");
    add_name(type +" skin");
    set_adj(({ metl, type }));

    return;        
}

/*************** Creation ************/
void
create_object()
{
   init_the_pelt();
   add_name(({"smiths_leather","_magical_ingredient", "skin"}));
   set_name("pelt");

   add_prop(OBJ_I_VOLUME, 100);   
   add_prop(OBJ_I_WEIGHT, 100);   
   add_prop(OBJ_I_VALUE, 100 + (random(100)));
}             

string
randmetl()
{
    string str;

    switch(random(6))
    {   
        case 0: str="rancid";    break;
        case 1: str="dusty";      break;
        case 2: str="wizened";    break;
        case 3: str="dry";        break;
        case 4: str="stinky";     break;
        case 5: str="oily";       break;
    }
    return str;                                                                               
}

string
randtype()
{
    string str;

    switch(random(8))
    {   
        case 0: str="wolf";      break;
        case 1: str="cat";       break;
        case 2: str="bear";      break;
        case 3: str="rat";       break;
        case 4: str="mouse";     break;
        case 5: str="bicorn";    break;
        case 6: str="rabbit";    break;
        case 7: str="deer";      break;
    }
    return str;                                                                               
}

string 
query_recover()
{
    string rec;
    rec = MASTER + ":";
 
    rec += "#type#" + type;
    rec += "#metl#" + metl;

    return rec;
}


void init_recover(string arg)
{
    string dummy;
    int i_check;

    sscanf(arg, "%s#type#%s#%s", dummy, type, dummy);
    sscanf(arg, "%s#metl#%s#%s", dummy, metl, dummy);

    init_the_pelt();

    return;
}
