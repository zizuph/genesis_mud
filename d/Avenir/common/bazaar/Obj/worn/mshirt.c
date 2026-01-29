// -*-C++-*-
// file name: shirt /d/Avenir/common/bazaar/Obj/worn/mshirt.c
// creator(s):       Lilith, April 1997
// last update:      
// purpose:          shirt for men's clothing shop
// note:
// bug(s):
// to-do:    

#pragma save_binary
inherit "/d/Avenir/inherit/cloth_arm";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

string color, type;
string randsize();
string randtnt();

void set_color(string str)  {    color = str;    }
void set_type(string str)   {    type = str;     }

void init_the_shirt()
{
    if (!color) color = randtnt();
    if (!type) type = randsize();
    set_adj(({color, type, "silk", "lace"}));
    set_short(""+ type +" "+ color +" silk shirt");
    return;    
}

void
create_armour()
{
    init_the_shirt();
    set_name("shirt");
    add_pname(({"clothes", "clothing"}));
    add_adj(({"custom", "sybarun"}));
    set_long("This "+ type + " shirt is made of highest-quality "+ 
           color +" silk. The neckline is cut low and laced up "+
           "with a silken thong. There is an abundance of lace at "+
           "the cuffs of the full sleeves. The shirt is loose "+
           "and flowing, allowing unrestrained movement "+
	   "while supplying absolute luxurious comfort.\n");
    set_ac(1 + random(3)); 
    set_at(A_BODY);
    set_keep(1);  
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(HEAP_S_UNIQUE_ID, "shirt_" + color + "_" + type);
}

string
randtnt()
{
   string str;

   switch(random(5))
   {   
      case 0: str="blue";    break;
      case 1: str="black";   break;
      case 2: str="red";     break;
      case 3: str="white";   break;
      case 4: str="cream";   break;
      case 5: str="yellow";  break;
   }
   return str;                                                                               
}

string
randsize()
{
   string str;

   switch(random(4))
   {   
      case 0: str="flowing";         break;
      case 1: str="full-sleeved";    break;
      case 2: str="lace-cuffed";     break;
      case 3: str="flowing";          break;
   }
   return str;                                                                               
}

string 
query_recover()
{
    string rec;
    rec = MASTER + ":";
 
    rec += "#type#" + type;
    rec += "#color#" + color;

    rec += query_arm_recover();
    return rec;
}

void 
init_recover(string arg)
{
    string dummy;
    int i_check;

    sscanf(arg, "%s#type#%s#%s", dummy, type, dummy);
    sscanf(arg, "%s#color#%s#%s", dummy, color, dummy);

    init_arm_recover(arg);

    init_the_shirt();

    return;
}


