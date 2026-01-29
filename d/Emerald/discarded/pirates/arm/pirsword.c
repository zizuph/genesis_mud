/* This weapon is cloned by /d/Emerald/pirates/npc/pirate1 
* and pirate2
*/

inherit "/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"


void
create_weapon()
{
   set_name("sword");
   set_short("short sword");
   set_long("It is a standard short sword.  It has been "+
      "well used, but poorly maintained.\n");
   set_adj(({"old","short"}));
   
   set_hit(18);
   set_pen(15);
   
   set_wt(W_SWORD);
   set_dt(W_IMPALE);
   
   set_hands(W_ANYH);
   
   set_corroded(1);
   
   add_prop(OBJ_I_VOLUME,750);
   add_prop(OBJ_I_WEIGHT,6000);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(18,15) + random(90) - 45);
}
