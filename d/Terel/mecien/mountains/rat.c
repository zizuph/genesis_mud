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
    set_name("rat"); 
    set_race_name("rat");
    set_short("giant rat");
    set_adj(({"nasty", "foul" }));
    set_long("This nasty rat is very large and could carry disease.\n");

    /* str, con, dex, int, wis, dis
    */
    set_stats(({ 5, 20, 30, 1, 1, 15}));
    set_hp(2000);

    set_skill(SS_DEFENCE, 15);
/*    set_random_move(60); */
    set_aggressive(1);

    set_attack_unarmed(A_BITE,  25, 25, W_IMPALE, 100, "teeth");
   
    set_hitloc_unarmed(H_HEAD, ({ 8, 5, 4, 5 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 8, 8, 6, 5 }), 80, "body");
}


