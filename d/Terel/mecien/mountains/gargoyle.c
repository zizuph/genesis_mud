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
#define A_CLAW 1
#define A_HORN 2
#define A_TAIL 3

#define H_HEAD 0
#define H_BODY 1
#define H_WING 2


create_creature()
{
    set_name("gargoyle"); 
    set_race_name("gargoyle");
    set_short("gargoyle");
    set_adj(({"large", "hideous" }));
    set_long("The visage of a nightmare, a dark demonic winged creature.\n");

    /* str, con, dex, int, wis, dis
    */
    set_stats(({ 33, 33, 50, 5, 5, 22}));
    set_hp(5000);
    set_aggressive(1);
    set_attack_chance(50);

    set_skill(SS_DEFENCE, 40);
    set_random_move(50);
    set_m_out("flies off");
    set_m_in("descends from the sky");

    set_attack_unarmed(A_BITE,  25, 25, W_IMPALE, 40, "bite");
    set_attack_unarmed(A_CLAW,  40, 20, W_SLASH, 40, "claws");
    set_attack_unarmed(A_HORN,  35, 15, W_IMPALE, 20, "horns");
    set_attack_unarmed(A_TAIL,  50, 30, W_IMPALE, 20, "tail");

    set_hitloc_unarmed(H_HEAD, ({ 40, 40, 40, 5 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 30, 35, 25, 5 }), 60, "body");
    set_hitloc_unarmed(H_WING, ({ 15, 15, 10, 5 }), 20, "wing");
}


