/* Creature: Oak Tree
* Purpose: Mainly to provide quest
* info to players - will fight if attacked.
   * Author: Alisande
* Date: 10/27/94

*/

inherit "std/creature";
inherit "/std/combat/unarmed"; /* this accesses unarmed routines */
inherit "/std/act/action"; /* Note that the /std/act/domove is NOT */
/*included -- this IS a tree. */

#include "/sys/ss_types.h";
#include "/sys/wa_types.h";

/* Define attack and hitloc id's (to make life easier later) */
   
#define A_LBRANCH 0
#define A_RBRANCH 1

#define H_LBRANCH 0
#define H_RBRANCH 1
#define H_TRUNK   2

create_creature()
{
   set_name("tree");
   set_race_name("tree");
   set_short("oak tree");
   set_long("This tree is patiently watching the passage of time.\n");
   set_stats(({ 100, 100, 0, 80, 150, 75}));
   set_hp(query_max_hp());
   set_skill(SS_DEFENCE, 20);
   
   set_attack_unarmed(A_LBRANCH, 40, 20, W_SLASH, 30, "left branch");
   set_attack_unarmed(A_RBRANCH, 40, 20, W_SLASH, 30, "right branch");
   
   set_hitloc_unarmed(H_LBRANCH, ({ 15, 25, 20, 20}), 20, "left branch");
   set_hitloc_unarmed(H_RBRANCH, ({ 15, 25, 20, 20}), 20, "right branch");
   set_hitloc_unarmed(H_TRUNK, ({ 10, 15, 30, 20}), 20, "trunk");
   
   set_act_time(15);
   int z;
   
z = this_player()->query_skill(SS_AWARENESS);
   
   switch(z)
   {
      case (z < 25):break;
      default: set_chat_time(random(15));break;
   }
   
   add_act("emote rustles its leaves in consternation.\n");
   add_act("emote sways in the slight breeze, the wind whispering " +
      "through its branches.\n");
   add_chat("This war has gone on far too long.\n");
   add_chat("The Great Oak is most unhappy with the elms for starting the war.\n");
   add_chat("If only the other trees would realize that we were MEANT to rule.....\n");
   
}
