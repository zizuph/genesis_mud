inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";

#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <poison_types.h>

#define A_BITE  0
#define H_BODY 0
#define MAX_BITES 6
#define TO        this_object()
#define TP      this_player()

int no_bites;
void wiggle(object ob);
void attack_other_snakes();

create_creature() {

    if (!IS_CLONE) return;
    set_name("snake");
    set_race_name("snake"); 
    set_adj("dangerous");
    add_adj("black");

    set_long("The snake looks ready to use its fangs.\n");

    set_gender(G_NEUTER);
    set_stats(({ 30 + random(3), 50 + random(3), 50 + random(3), 1, 1, 99})); 

    set_skill(SS_DEFENCE, 20);
    set_skill(SS_AWARENESS, 25);
    set_hp(9999);
    set_mana(9999);
    set_fatigue(9999);

    add_item("fangs", "They look very sharp, you better stay away.\n");

    set_act_time(20 + random(20));
    add_act("@@curl");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_QUICKNESS, 100);
    add_prop(CONT_I_WEIGHT, 3000);
    add_prop(CONT_I_MAX_WEIGHT, 3500);
    add_prop(CONT_I_VOLUME, 1100);
    add_prop(CONT_I_MAX_VOLUME, 1500);
    add_prop(OBJ_I_NO_INS, 1);
    add_prop(OBJ_M_NO_GET, "@@try_to_get_me");

    /* Wep_type,   to_hit,   pen,   Dam_type,   %usage,   attack_desc */
    set_attack_unarmed(A_BITE,   35, 53, W_IMPALE, 100, "fangs");

    /* Hit_loc,   *Ac (impale/slash/bludgeon),   %hit,   hit_desc */
    set_hitloc_unarmed(H_BODY, ({  15,  15, 6 }), 100, "body");

    no_bites = 0;
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
    int p_str, dam;
    object poison;

    if(aid==A_BITE) {
        tell_object(enemy, "The snake's fangs bite deep!\n");
        
        if (no_bites < MAX_BITES) {
        poison = clone_object("/std/poison_effect");
        if(poison) {
            p_str = (65 + random(10))/(no_bites + 1);
            if (p_str <= 0) p_str = 1;
            poison->move(enemy);
            poison->set_time(700 + random(300));
            poison->set_interval(40+random(5));
            poison->set_strength(p_str);
            dam = 200 + random(100);
            poison->set_damage(({POISON_HP, dam, POISON_STAT, SS_CON }));
            poison->start_poison();
        }
        no_bites++;
        }
    }
    return 0;
}

void
wiggle(object ob)
{
    if (!ob || !CAN_SEE(TO, ob)) return;
    ob->catch_msg("The "+short()+" is ready to attack you!\n");
    tell_room(environment(TO), "The "+short()+" looks ready to "+
        "attack "+QTNAME(ob)+".\n", ({TO, ob}));
    if (ob->query_wiz_level() == 0) TO->attack_object(ob);
    return;
}

string
curl()
{
    int i;

    i = random(3);
    if (i==0)
        tell_room(environment(TO), "The "+short()+" stares intently at " +
            "you.\n");
    if (i==1)
        tell_room(environment(TO), "The "+short()+" watches "+
            "carefully all your movements.\n");
    if (i==2)
        tell_room(environment(TO), "The "+short()+" seems to "+
            "guard the stone wheel.\n");
    return "";
}


string
try_to_get_me()
{
    TO->attack_object(TP);
    return capitalize(short()) + " doesn't like to be taken!\n";
}

void
attack_other_snakes()
{
    object *all;
    int i;

    all = all_inventory(environment(TO));
    for(i=0; i<sizeof(all); i++) {
        if (MASTER_OB(all[i]) == MASTER && all[i] != TO) {
            tell_room(environment(TO), "One "+short()+" goes crazy and "+
                      "attacks another "+short()+".\n");
            TO->attack_object(all[i]);
            break;
        }
    }
}
