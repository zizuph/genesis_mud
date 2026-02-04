/*
/doc/examples/mobiles/tiger2.c

JnA 920111

A sample creature 

This creature uses no tools for fighting. 
It inherits the routines for unarmed combat.

This is a rather tough beast. You need on average 30 or more in your
stats to handle it. You also need wc30 weapon with skills to match.

*/

inherit "/std/creature";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>

/*
* Define some attack and hitloc id's (only for our own benefit)
*/
#define A_BITE 0

#define H_HEAD 0
#define H_BODY 1

create_creature()
{
   set_name("demon hound"); 
   add_name("hound");
   add_name("demon");
   set_race_name("demon hound");
   set_aggressive(1);
   set_short("demon hound");
   set_adj(({"abyssmal", "mean" }));
   set_long("This beast, black with red eyes, is the stuff of demons.\n");
   
   /* str, con, dex, int, wis, dis
   */
   set_stats(({ 40, 40, 105, 10, 10, 50}));
   set_hp(20000);
   
   set_skill(SS_DEFENCE, 75);
   
   set_attack_unarmed(A_BITE,  80, 60, W_IMPALE, 100, "jaws");
   
   set_hitloc_unarmed(H_HEAD, ({ 80, 50, 40, 45 }), 20, "head");
   set_hitloc_unarmed(H_BODY, ({ 80, 70, 60, 45 }), 80, "body");
}


