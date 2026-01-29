#pragma save_binary

inherit "/std/food";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h> 
#include "numbers.h" 

create_food()
{
  int num;
  set_name("bone");
  set_adj("yellowed");
  set_amount(2);
  switch("@@ran_num@@")
  {
    case 0:
      add_adj("thigh");
      set_short("yellowed thigh bone");
      set_long("This "+short()+" has been thoroughly gnawed on "+
        "and is cracked at one end.\n");
      num = 0;
    case 1:
      add_adj("dry");
      add_adj("brittle");
      add_adj("rib");
      set_short("brittle rib bone");
      set_long("This is a dry, "+short()+".\n");
      num = 1;
    case 2:
      add_adj("shin");
      add_adj("reeking");
      set_short("reeking shin bone");
      set_long("This "+short()+" hasn't been cleaned off yet.\n");
      num = 2;
  }
  add_prop(OBJ_I_VOLUME,50+num*2);
  add_prop(OBJ_I_WEIGHT,100-2*num); 
  add_prop(OBJ_I_VALUE,9-4*num);
}