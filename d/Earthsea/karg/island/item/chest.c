inherit "/std/receptacle";

#include <stdproperties.h>

#include "defs.h"

void create_container()
{
 set_name("chest");
 add_name("_karg_diary_chest_");
 set_adj("large");
 add_adj("metal");
 set_long("This metal chest looks sturdy. Massive lock secures it "+
   "making sure noone will open the chest or try to pick the lock.\n");

 set_no_pick();

 add_prop(OBJ_M_NO_GET,"It's too heavy for you to carry!\n");
 add_prop(OBJ_I_VALUE,1);
 add_prop(CONT_I_IN,1);
 add_prop(CONT_I_RIGID,0);
 add_prop(CONT_I_TRANSP,0);
 add_prop(CONT_I_WEIGHT, 200000);
 add_prop(CONT_I_VOLUME,100000);
 add_prop(CONT_I_MAX_WEIGHT, 220000);
 add_prop(CONT_I_MAX_VOLUME,120000);
 add_prop(CONT_I_CLOSED, 1);
 add_prop(CONT_I_LOCK, 1);

 set_key(TENT_KEY_ID);

 setuid();
 seteuid(getuid());

 clone_object(ISLAND_ITEM+"diary")->move(TO,1);
}


