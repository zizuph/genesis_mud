inherit "/std/monster";
inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <poison_types.h>
#include "/d/Shire/common/monster/defs.h"

/* Invent some attack/hitlocation numbers, for ourselves */
#define ATT_BITE    0

#define HIT_BODY     0

create_creature()
{
   set_name("bat");
   add_adj(({"scary","vampire"}));
   set_pname("bats");
   set_living_name("_moria_bat_");
   set_race_name("bat");

   set_long("This is one of the most frightening bats you "+
	    "have ever seen. It looks at you with clear hunger "+
	    "for your blood.\n");
   add_prop(LIVE_I_NEVERKNOWN, 1);
   default_config_mobile(20);
   set_all_hitloc_unarmed(30);
   set_gender(G_NEUTER);
   set_stats(({20,60,10,10,10,55}));
   set_alignment(-100);
   
   add_exp_combat(10);
   
   set_skill(SS_DEFENCE, 90);
   set_skill(SS_UNARM_COMBAT, 90);
   set_act_time(10);
   add_act("scream");
   add_act("emote flaps its leathery wings.");
   set_attack_unarmed(ATT_BITE,  40, 40,W_IMPALE, 100, "teeth");
   
   add_prop(CONT_I_WEIGHT, 1000);   /* 0.005 Kg  */
   add_prop(CONT_I_VOLUME, 2000);   /* 0.010 Ltr */
}

/*
 * Function name: cr_did_hit
 * Description:   This function is called from the combat object to give
 *                appropriate messages.  We shall remain content to let 
 *                the default messages be sent, but we will give poison 
 *                to the hit creature.
 * Arguments:     aid:   The attack id
 *                hdesc: The hitlocation description.
 *                phurt: The %hurt made on the enemy
 *                enemy: The enemy who got hit
 *                dt:    The current damagetype
 *                phit:  The %success that we made with our weapon
 *                       If this is negative, it indicates fail
 */

int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
    object poison;
    int num_doses;

    if (aid==ATT_BITE) {
        tell_object(enemy, "The bat bites deeply!\n");
        
	num_doses = sizeof(filter(all_inventory(enemy), "bat_poison", TO));
	if (random(5) || random(num_doses))
	    return 0;

        poison = clone_object("/std/poison_effect");
        if (poison) {
            poison->move(enemy);
	    poison->set_poison_type("vampirebat");
            poison->set_time(200);
            poison->set_interval(50);
            poison->set_strength(75);
            poison->set_damage(({POISON_HP, 44, POISON_STAT, SS_CON }));
            poison->start_poison();
        }
    }

    return 0;
}

int
bat_poison(object what)
{
    return what->query_poison_type() == "vampirebat";
}
