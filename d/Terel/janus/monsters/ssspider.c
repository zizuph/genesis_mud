/*
   /doc/examples/poison/spider.c
   A demonstration of poison use in monsters.   The example is a spider
   which has paralysis venom only -- the venom will fatigue, not kill.
   Quis, 920620
   Hehe not anymore with my version of this spider
   Janus 921104
*/
inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <poison_types.h>

#define A_BITE  0

#define H_BODY 0
#define H_LEGS 1
#define H_EYES 2
#define H_HEAD 3

create_creature() {

     if (!IS_CLONE)return;
    set_name(({"spider"}));
    set_short("spider");
    set_long(break_string("A small brown hairy spider. For its small "+
     "size it has quite big mandibles. \n",70));
    set_adj(({"brown","hairy"}));
    set_race_name("spider");
    set_alignment(-35);
    set_stats(({3,15,8,3,3,3}));
    set_hp(64);
    set_gender(1);
    set_skill(SS_CLIMB,random(25)+70);
    set_skill(SS_DEFENCE,random(15)+5);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(CONT_I_MAX_WEIGHT, 400);
    add_prop(CONT_I_MAX_VOLUME, 400);
    set_whimpy(1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(OBJ_I_NO_INS, 1);
    /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_BITE,   10, 5, W_IMPALE, 100, "jaws");
    /* Hit_loc,   *Ac (impale/slash/bludgeon),   %hit,   hit_desc */
    set_hitloc_unarmed(H_BODY, ({  3,  3, 2 }), 60, "body");
    set_hitloc_unarmed(H_EYES,({ 1, 1, 1 }), 10, "eyes");
    set_hitloc_unarmed(H_HEAD,({ 2, 2, 1 }), 15, "head");
    set_hitloc_unarmed(H_LEGS,({ 3, 3, 3 }), 15, "legs");
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

    if(aid==A_BITE) {
        write("Your fangs bite deep!\n");
        tell_object(enemy, "The spider's fangs bite deep!\n");
        
        poison = clone_object("/std/poison_effect");
        if(poison) {
            poison->move(enemy);
            poison->set_time(500);
            poison->set_interval(200);
            poison->set_strength(200);
            poison->set_damage(({POISON_FATIGUE, 1, POISON_STAT, SS_CON }));
            poison->start_poison();

        }
    }

    return 0;
}
