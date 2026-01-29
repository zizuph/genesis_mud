/* A pteranodon (flying dinosaur) */

inherit "/std/creature";
inherit "/std/combat/unarmed";

/* inherit "/std/act/domove";
   inherit "/std/act/action";
*/

#include <wa_types.h>
#include <ss_types.h>

#include "monsters.h"

/*
 * Define some attack and hitloc id's
*/
#define A_BITE 0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_LWING 1
#define H_RWING 2

void 
create_creature()
{
    set_name("egghead");
    set_race_name("pteranodon");
    set_adj("huge");
    set_long("@@long");
    set_m_in("flies in");
    set_m_out("flies");

    set_stats(({150,500,150,40,40,150}));
   
    set_hp(query_max_hp());
    set_mana(query_max_mana());
    set_fatigue(query_max_fatigue());
    set_exp_combat(10000000);
    
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);

    set_attack_unarmed(A_BITE, 50, 50, W_IMPALE, 50, "beak");
    set_attack_unarmed(A_LCLAW, 30, 30, W_SLASH, 30, "left claw");
    set_attack_unarmed(A_RCLAW, 40, 40, W_SLASH, 40, "right claw");

    set_hitloc_unarmed(H_HEAD, ({40,40,40,40}), 40, "head");
    set_hitloc_unarmed(H_LWING, ({20,20,20,20}), 20, "left wing");
    set_hitloc_unarmed(H_RWING, ({20,20,20,20}), 20, "right wing");

}

/*
 * Function name: long
 * Description:   describes the pteranodon depending if it still's got the egg
 * Arguments:     none
 * Returns:       long description
 */

string
long()
{
    if (present("egg", TO))
        return "This reptile is sitting on it's egg and guards it carefully.\n";
    else
        return "It looks very sad because someone has stolen its egg.\n";
}

/*****************************************************************************/

/*
 * Function name: fly
 * Description:   This function's called when someone throws the stick on
                  the top of the volcano and causes the pteranodon to fly.
 * Arguments:     none
 * Returns:       nothing
 */

void
fly()
{
    object egg; 
   
    if (egg = present("egg",TO)) {
        egg->move(environment(TO));
        call_out("come_back",10,1);
    }
    else 
        call_out("come_back",10,0);
    TO->move_living("into the sky", TRACK + "sky");
    return;
}

void
come_back(int has_had_egg)
{
    object egg;
    
    TO->move_living("back to the top of the volcano.\n", TRACK + "top");
    if (has_had_egg){
        egg = present("egg",environment(TO));
        
        if (egg){
            egg->move(TO);
            tell_room(environment(TO), "The pteranodon sits on the egg again.\n");
        }
        else
            tell_room(environment(TO), BS("The pteranodon's looking for its "
                + "egg and gets very sad because it didn't find it.\n"));
        
    }
    return;
}

