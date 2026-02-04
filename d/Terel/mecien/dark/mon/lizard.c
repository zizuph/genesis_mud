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
#define H_TAIL 2

create_creature()
{
   set_name("lizard"); 
   set_race_name("lizard");
   set_short("shadow lizard");
   set_adj("shadow");
   set_long("A shadow beast, in the form of a black reptile. It\n"
      +"seems to be a creature spawned of demons. Though it seems\n"
      +"of such nature, it is real enough. It has sharp teeth and\n"
      +"looks horribly vicious and malevolent.\n");
   set_alignment(-112);
  set_gender(2);
   
   /* str, con, dex, int, wis, dis
   */
   set_stats(({ 34, 36, 54, 5, 5, 30}));
   set_hp(6000);
   
   set_skill(SS_DEFENCE, 15);
   /*    set_random_move(60); */
   set_aggressive(1);
   
   set_attack_unarmed(A_BITE,  52, 38, W_IMPALE, 100, "teeth");
   
   set_hitloc_unarmed(H_HEAD, 25, 20, "head");
   set_hitloc_unarmed(H_BODY, 40, 60, "abdomen");
   set_hitloc_unarmed(H_TAIL, 30, 20, "tail");
}


