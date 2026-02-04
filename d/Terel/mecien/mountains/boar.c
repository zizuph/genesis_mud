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
#define A_TUSKS  0
#define A_HOOVES 1

#define H_HEAD 0
#define H_BODY 1

create_creature()
{
    set_name("boar"); 
    set_race_name("giant");
    set_short("giant boar");
    set_adj(({"monstrous", "mean" }));
    set_long("A monstrous boar, it looks mean.\n");

    /* str, con, dex, int, wis, dis
    */
    set_stats(({ 40, 40, 40, 10, 10, 20}));
    set_hp(8000);

    set_skill(SS_DEFENCE, 30);

    set_attack_unarmed(A_TUSKS,  60, 40, W_IMPALE, 80, "tusks");
    set_attack_unarmed(A_HOOVES, 20, 20, W_SLASH,  20, "hooves");
   
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 80, "body");
}


