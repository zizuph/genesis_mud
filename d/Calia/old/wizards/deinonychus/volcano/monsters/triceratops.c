/* A triceratops (dinosaur) */
/* This monster's used in the t-rex-tooth quest */
/* When t-rex's kills this dinosaur then a tooth of him sticks in this */
/* monster. The player can take the tooth without fighting */

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";

#include <wa_types.h>
#include <ss_types.h>

/*
 * Define some attack and hitloc id's
*/
#define A_MHORN 0
#define A_LHORN 1
#define A_RHORN 2

#define H_HEAD 0
#define H_BACK 1
#define H_LEGS 2

void 
create_creature()
{
    set_name("snoopy");
    set_living_name("snoopy");
    set_race_name("triceratops");
    set_adj("mean");
    set_gender(2);
    set_long(break_string("This reptile is one of the most hated enemies of "
        + "tyronnosaurs rex.\n",70));
    enable_commands();

    set_stats(({200,200,200,20,20,200}));
   
    set_hp(query_max_hp());
    set_mana(query_max_mana());
    set_exp_combat(20000000);
    
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);

    set_attack_unarmed(A_MHORN, 20, 20, W_IMPALE, 20, "middle horn");
    set_attack_unarmed(A_LHORN, 50, 50, W_IMPALE, 50, "left horn");
    set_attack_unarmed(A_RHORN, 50, 50, W_IMPALE, 50, "right horn");

    set_hitloc_unarmed(H_HEAD, ({40,40,40,40}), 100, "head");
    set_hitloc_unarmed(H_BACK, ({20,20,20,20}), 50, "back");
    set_hitloc_unarmed(H_LEGS, ({20,20,20,20}), 50, "legs");
}

