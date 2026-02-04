inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <poison_types.h>
#include <money.h>

#define A_BITE  0
#define A_TAIL 1
#define A_CLAW 2

#define H_BODY 0
#define TO this_object()


create_creature() {

    if (!IS_CLONE)
	return;
    set_name("wyvern");
    set_race_name("wyvern"); 
    set_adj("foul");
   add_adj("shadowy");


   set_aggressive(1);

   set_act_time(10);
   add_act("growl");
   add_act("@@thrash");
    set_gender(G_NEUTER);
  set_stats(({ 85 + random(30), 120 + random(50), 90 + random(40), 
       23, 44, 54}));
                  /* str, dex, con, int, wis, dis */

    set_skill(SS_DEFENCE, 88);
   set_hp(99999);
    set_mana(99999);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_NO_INS, 1);

   set_alignment(-686);

    /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_BITE,   86, 81, W_IMPALE, 50, "jaws");
   set_attack_unarmed(A_TAIL, 75, 60, W_IMPALE, 80, "barbed tail");
   set_attack_unarmed(A_CLAW, 44, 48, W_SLASH, 35, "claws");

    /* Hit_loc,   *Ac (impale/slash/bludgeon),   %hit,   hit_desc */
    set_hitloc_unarmed(H_BODY, ({  75,  75, 45 }), 100, "body");

    MONEY_MOVE(random(10), "gold", 0, this_object());
MONEY_MOVE(random(20), "silver", 0, this_object());
}

thrash(){
tell_room(environment(this_object()), QCTNAME(this_object()) + " thrashes about wildly.\n");
return 1;
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

/* I believe the spider poisons the player each bite. it should of course
 * be harder to poison the player again and again, Nick */

    if(aid==A_TAIL) {
   TO->catch_msg("Your tail pierces deep in your victim!\n");
       tell_object(enemy, "The wyvern's tail pierces you with its stinger.\n");
        
        poison = clone_object("/std/poison_effect");
        if(poison) {
            poison->move(enemy);
            poison->set_time(2000);
            poison->set_interval(50);
            poison->set_strength(72);
            poison->set_damage(({POISON_HP, 100, POISON_STAT, SS_CON }));
            poison->start_poison();

        }
    }

    return 0;
}
