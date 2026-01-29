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
    set_name("tiger"); 
    set_race_name("tiger");
    set_short("white tiger");
    set_adj(({"white", "vicious" }));
    set_long("It looks rather vicious!\n");

    /* str, con, dex, int, wis, dis
    */
    set_stats(({ 90, 30, 80, 20, 5, 75}));

    set_skill(SS_DEFENCE, 30);
    set_skill(SS_SWIM, 80);

    set_attack_unarmed(A_BITE,  20, 30, W_IMPALE, 40, "jaws");
    set_attack_unarmed(A_LCLAW, 40, 20, W_SLASH,  30, "left paw");
    set_attack_unarmed(A_RCLAW, 40, 20, W_SLASH,  30, "right paw");
   
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30 }), 80, "body");
}


