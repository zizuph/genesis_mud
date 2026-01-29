/*
  A large bear, apt to be found in the more rugged regions of higher
  elevation in Emerald.
  Code (c) 1999 to Damian Horton, BKA Casimir.
*/

inherit "/std/creature.c";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */
inherit "/std/act/domove"; /* Include this if you want the creature to move */
inherit "/std/act/action"; /* Include this if you want your creature to act */

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <stdproperties.h>
/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1
#define H_RARM 2
#define H_LARM 3

create_creature()
{ 
  set_race_name("bear");
  set_short("huge brown mountain bear");
  set_adj(({"huge", "brown","mountain" }));
  set_long("This is a great big bear, brown in color, and immense in size. "+
	   "It stands fully six feet tall at the shoulders yet moves with "+
	   "a threatening grace. Its powerful arms sport claws which look "+
	   "capable of tearing through steel, and its maw is lined with "+
	   "nasty looking teeth.\n");
   
  // str, con, dex, int, wis, dis
    
  set_stats(({ 135 + random(20), 55+random(20), 135+random(20),
		 5+random(10), random(10), random(110+random(25))}));
    
  set_skill(SS_DEFENCE, 50+random(10));
  set_skill(SS_UNARM_COMBAT,70+random(10)); //Natural ability.
  set_skill(SS_AWARENESS, 55);
  set_skill(SS_BLIND_COMBAT, 40+random(10));
  set_alignment(0);

  // Attacks players 50% of the time - this wont work presently
  //  set_aggressive(&random(2));

  set_attack_unarmed(A_BITE,  20, 30, W_IMPALE, 50, "jaws");
  set_attack_unarmed(A_LCLAW, 24, 24, W_SLASH | W_BLUDGEON,  75, "left paw");
  set_attack_unarmed(A_RCLAW, 24, 24, W_SLASH | W_BLUDGEON,  75, "right paw");
  
  set_hitloc_unarmed(H_HEAD, 8, 15, "head");
  set_hitloc_unarmed(H_RARM, 8, 10, "right arm");
  set_hitloc_unarmed(H_LARM , 8, 10, "left arm");
  set_hitloc_unarmed(H_BODY, 8, 65, "body");

  set_appearance(25);
  add_prop(CONT_I_HEIGHT,180+random(30));
  add_prop(CONT_I_WEIGHT,400000+random(100000));
  add_prop(CONT_I_VOLUME,400000+random(100000));
 
  add_prop(LIVE_I_NEVERKNOWN, 1);
  add_prop(LIVE_M_NO_ACCEPT_GIVE, 1);
}






