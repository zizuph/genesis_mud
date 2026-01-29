//-*-C++-*-
// sandals      /d/Avenir/common/holm/obj/sandals.c
// creator(s):  Lilith 06 April 1997
// revised:
// purpose:     Something for priests to wear
// note:         
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/armour";

#include "../holm.h"
#include <wa_types.h>

string color, type;
string randsize();
string randtnt();

void set_color(string str){    color = str;   }
void set_type(string str){    type = str;    }

void init_the_sandals()
{
    if (!color) color = randtnt();
    if (!type) type = randsize();

    set_short("pair of "+ color +" "+ type +" sandals");
    set_long("A simple pair of sandals, made of "+ type +". They "+
        "look very comfortable and utilitarian, and are "+ color +
        " in color.\n");
    set_adj(({color, type}));
    return;        
}

void
create_armour()
{
   init_the_sandals();
   set_name("sandals");
   add_name(({"pair of sandals", "shoes"}));
   add_pname(({"clothes", "clothing"}));
   set_ac(random(3) + 2);
   set_at(A_FEET);

   add_prop(HEAP_S_UNIQUE_ID, "sandals_" + color + "_" + type);
   add_prop(OBJ_I_VOLUME, 1000);   /* volume 1 litres */
}             
string
randtnt()
{
   string str;

   switch(random(7))
   {   
      case 0: str="yellow";    break;
      case 1: str="green";   break;
      case 2: str="red";     break;
      case 3: str="brown";  break;
      case 4: str="black";   break;
      case 5: str="gray";   break;
      case 6: str="white";   break;
   }
   return str;                                                                               
}

string
randsize()
{
   string str;

   switch(random(4))
   {   

      case 0: str="cork";         break;
      case 1: str="leather";        break;
      case 2: str="hemp";          break;
      case 3: str="gum";          break;
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

    init_the_sandals();

    return;
}



