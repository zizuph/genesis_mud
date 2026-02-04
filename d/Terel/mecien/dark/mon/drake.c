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
inherit "/std/act/attack"; /* Added here y nick to make this file load */

#include <wa_types.h>
#include <ss_types.h>

/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2
#define A_TAIL  3
#define A_HORN  4

#define H_HEAD 0
#define H_BODY 1

create_creature()
{
    set_name("drake"); 
    set_race_name("drake");
    set_short("cave drake");
    set_adj(({"evil", "cave" }));
  set_long("A massive cave drake. These smaller dragons inhabit\n"
  +"dark caverns, seeking refuge from light. They devour beings\n"
 +"very quickly with their massive jaws. They are evil creatures\n"
 +"and possess great intelligence.\n");

    /* str, con, dex, int, wis, dis
    */
    set_stats(({ 100, 126, 140, 95, 90, 100}));

    set_skill(SS_DEFENCE, 80);
    set_alignment(-400);
    set_fatigue(9000);
    set_hp(40000);

    set_attack_unarmed(A_BITE,  90, 60, W_IMPALE, 60, "jaws");
    set_attack_unarmed(A_LCLAW, 50, 35, W_SLASH,  40, "left claw");
    set_attack_unarmed(A_RCLAW, 55, 40, W_SLASH,  45, "right claw");
    set_attack_unarmed(A_TAIL, 80, 50, W_BLUDGEON,  25, "tail");
    set_attack_unarmed(A_HORN, 60, 40, W_IMPALE,  15, "horn");
   
    set_hitloc_unarmed(H_HEAD, ({ 70 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 82 }), 80, "body");
}


