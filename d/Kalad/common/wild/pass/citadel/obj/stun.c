/* by korat 
 * september 1996
 * 
 * This paralyze is cloned when a ogre punches a player
 * in the face. The ogres are found in 
 * /d/Kalad/common/wild/pass/citadel/npc
 *
*/
inherit "/std/paralyze";
#include "/d/Kalad/defs.h"

void
create_paralyze()
{
   set_name("stun");
   set_long("A paralyze.\n");
   add_prop(OBJ_I_WEIGHT, 1);
   add_prop(OBJ_I_VOLUME, 1);
   add_prop(OBJ_M_NO_SELL,1);
   add_prop(OBJ_I_INVIS, 99);
   add_prop(OBJ_I_NO_DROP,1);
   set_remove_time(15);
   set_stop_verb("slutt");
   set_fail_message("You are too dazed to do anything!\n");
   set_stop_message("You manage to regain control of yourself.\n");
}

