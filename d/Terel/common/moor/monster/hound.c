// creator: ?????
// Modified by Lilith Dec 2021-Jan 2022
//    moved to /d/Terel/common/moor from Sorgums dir.
//    made some updates to desc and props.

inherit "/std/creature";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

/*
* Define some attack and hitloc id's (only for our own benefit)
*/
#define A_BITE 0

#define H_HEAD 0
#define H_BODY 1

void
create_creature()
{
   set_name("hellhound"); 
   add_name(({"hound", "demon"}));
   set_race_name("hound");
   set_short("hellhound");
   set_adj(({"abyssmal", "mean", "hell" }));
   set_long("This beast, black with red eyes, is the stuff of nightmares.\n");

   set_aggressive(1);
   set_attack_chance(90);   
   set_random_move(10);
   set_restrain_path("/d/Terel/common/moor/");
   set_monster_home("/d/Terel/common/moor/tomb/grime_river");
   
   /* str, con, dex, int, wis, dis
   */
   set_stats(({ 40, 40, 105, 10, 10, 50}));

   set_skill(SS_ACROBAT, 75);   
   set_skill(SS_DEFENCE, 75);
   set_skill(SS_UNARM_COMBAT, 75);  
  
   set_attack_unarmed(A_BITE,  80, 60, W_IMPALE, 100, "jaws");
   
   set_hitloc_unarmed(H_HEAD, ({ 80, 50, 40, 45 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 80, 70, 60, 45 }), 80, "body");
   
   	add_prop(LIVE_I_NO_GENDER_DESC, 1);
	add_prop(NPC_I_NO_FEAR,      1);
    add_prop(NPC_I_NO_LOOKS,     1);
    add_prop(NPC_I_NO_RUN_AWAY,  1);
    add_prop(LIVE_I_SEE_DARK,    1);
    add_prop(LIVE_I_QUICKNESS, 100);

}


