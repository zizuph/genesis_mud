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
#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1

create_creature()
{
    set_name("wolf"); 
    set_race_name("wolf");
    set_short("dark wolf");
    set_adj(({"great", "vicious" }));
    set_long("A great wolf, begotten in ages past.\n");

    /* str, con, dex, int, wis, dis
    */

    set_stats(({ 50, 70, 80, 20, 5, 75}));
    set_hp(10000);

    set_skill(SS_DEFENCE, 60);

    set_attack_unarmed(A_BITE,  50, 65, W_IMPALE, 50, "jaws");
    set_attack_unarmed(A_LCLAW, 40, 30, W_SLASH,  35, "left claw");
    set_attack_unarmed(A_RCLAW, 40, 30, W_SLASH,  35, "right claw");
   
    set_hitloc_unarmed(H_HEAD, ({ 30, 25, 30, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 28, 15, 30, 30 }), 80, "body");
}


