/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
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
#include <stdproperties.h>

#include <ss_types.h>

/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE 0

#define H_HEAD 0
#define H_BODY 1

query_m_out(){
return "flies";
}

query_m_in(){
return "descends from the sky.";
}

create_creature()
{
    set_name("raven"); 
    set_race_name("raven");
    set_short("raven");
  set_adj("large");
   add_adj("black");
    set_long("A mysterious and haunting bird, black as night.\n");

    /* str, con, dex, int, wis, dis
    */
    set_stats(({ 5, 20, 20, 5, 5, 3}));
    set_hp(2000);

    set_skill(SS_DEFENCE, 40);
    set_random_move(10);

   set_alignment(100);
   set_gender(2);
    add_prop(NPC_I_NO_LOOKS, 1);
   
  enable_commands();
    set_follow("mecien");

    set_attack_unarmed(A_BITE,  25, 25, W_IMPALE, 100, "beak");
   
    set_hitloc_unarmed(H_HEAD, ({ 15, 15, 15, 5 }), 20, "wing");
    set_hitloc_unarmed(H_BODY, ({ 15, 15, 15, 5 }), 80, "body");
}


