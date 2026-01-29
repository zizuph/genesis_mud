/* this weapon is cloned by /d/Emerald/caverns/npc/pguard.c
*/

inherit "/std/weapon";

#include "/sys/stdproperties.h"
#include "/sys/wa_types.h"
#include "/sys/formulas.h"
#include "/sys/macros.h"


void
create_weapon()
{
   
   if(!IS_CLONE)
      return;
   
   set_name("sword");
   set_adj("long");
   add_name("longsword");
   set_short("longsword");
   set_long(break_string("This sword looks well forged. It should "+
         "last quite a while in combat.\n",74));
   
   set_hit(23);
   set_pen(18);
   
   set_wt(W_SWORD);
   set_dt(W_IMPALE);
   
   set_hands(W_ANYH);
   
   
   add_prop(OBJ_I_VOLUME,1250);
   add_prop(OBJ_I_WEIGHT,9000);
   add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(18,15) + random(200));
}

string
query_recover()
{
   return "/d/Emerald/obj/general/l_sword" + ":" + query_wep_recover();
}

void
init_recover(string arg)
{
   init_wep_recover(arg);
}
