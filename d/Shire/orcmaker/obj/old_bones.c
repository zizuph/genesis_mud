#pragma save_binary

inherit "/std/object";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h> 

create_object()
{
  int num = random(3);
  set_name("bone");
  set_adj("yellowed");
  switch(num) 
  {
    case 0:
      add_adj("thigh");
      set_short("yellowed thigh bone");
      set_long("This "+short()+" has been thoroughly gnawed on "+
        "and is cracked at one end.\n");
    case 1:
      add_adj("dry");
      add_adj("brittle");
      add_adj("rib");
      set_short("brittle rib bone");
      set_long("This is a dry, "+short()+".\n");
    case 2:
      add_adj("shin");
      add_adj("reeking");
      set_short("reeking shin bone");
      set_long("This "+short()+" hasn't been cleaned off yet.\n");
  }
  add_prop(OBJ_I_VOLUME,50+num*2);
  add_prop(OBJ_I_WEIGHT,100-2*num); 
  add_prop(OBJ_I_VALUE,9-4*num);
}