/* coded 27/4 1993 */

#include "/sys/stdproperties.h" /* I've looked through lots of examples. */
#pragma save_binary

inherit "/std/weapon";          /* It seems all weapons start with these */
inherit "/lib/keep";
#include "/sys/wa_types.h"      /* so why should mine be different?      */
   
void
create_weapon()
{
  /* Set name, short description and long description */
  set_name("sword");
  set_pname("swords");
  set_short("gateguard's sword");
  set_pshort("gateguard's swords");
  set_long(break_string("It's a large sword, which is obviously elven "
			+ "made. \n",70));
  
  set_adj("guard");
  set_adj("gateguard");
  set_adj("gateguard's");
  set_adj("guard's");
  
  /* Set 'to hit' and 'penetration' values */
  set_hit(25);
   set_pen(27);
  
  /* Set weapon type & damage type */
  set_wt(W_SWORD); /* It's a type of sword */
  set_dt(W_SLASH); /* It's a slashing sword */
  
  
  /* Set physical attributes */
  add_prop(OBJ_I_WEIGHT, 15000); /* sword weights 15 kg. */
  add_prop(OBJ_I_VOLUME, 5000); /* sword takes up 5 l */
}

string query_recover()
{
  return "/d/Rhovanion/common/weapons/gsword.c" + ":" +
    query_wep_recover();
}

void init_recover(string arg)
{
  init_wep_recover(arg);
}
