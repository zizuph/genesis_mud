/* aldarion 95.07.09 */

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
#include "/d/Kalad/defs.h"

#define A_FANGS 0

#define H_THORAX 0
#define H_ABDOMEN 1
#define H_LEGS 2

create_creature()
{
    if(!IS_CLONE)
        return;

    set_name("Spider");
    set_race_name("spider");
    set_adj( ({"black", "hairy"}) );
    set_long("\n");

    set_gender(G_FEMALE);    /* G_MALE G_FEMALE G_NEUTER */
    set_alignment(0);
    set_aggressive(0);
    
    /* str dex con int wis dis */
    set_stats( ({100, 120, 100, 10, 10, 20}) );
    set_hp(query_max_hp());
    set_mana(query_max_mana());

    /* attack: att_id, wchit, wcpen, damage_type, %use, desc */

    set_attack_unarmed(A_FANGS, 40, 40, W_IMPALE, 100, "sharp fangs");

    /* hitloc: hit_id, ac, %hit, desc */

    set_hitloc_unarmed(H_THORAX, ({20, 25, 25}), 15, "thorax");
    set_hitloc_unarmed(H_ABDOMEN, ({70, 70, 40}), 65, "abdomen");
    set_hitloc_unarmed(H_LEGS, ({10, 30, 20}), 20, "legs");

    /* add_leftover("pathname", "organ", no., vbfc, hard, cut); */

    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_BLIND_COMBAT, 80);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_DEFENCE, 60);

    add_prop(LIVE_I_QUICKNESS, 300);
    add_prop(LIVE_I_NEVERKNOWN, 1);

    add_prop(OBJ_I_WEIGHT, 30000); /* grams */
    add_prop(OBJ_I_VOLUME, 25000); /* ml */
}

/*
 * Function name: tell_watcher
 * Description:   send the string from the fight to people that want them
 * Arguments:     the string to send
 * Returns:       void
 */

static void
tell_watcher(string str, object enemy)
{
    object me, *ob;
    int i;

    me = TO;
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}



/*
 * Function name: special attack
 * Description:   redefines the special_attack func which is called from within
 *                the combat system
 * Arguments:     enemy: my enemy
 * Returns:       0: continue with attack
 *                1: no additional ordinary attack
 */

int
special_attack(object enemy)
{
    object me;
    mixed* hitresult;
    string how;

    me = TO;
    if(random(10))
        return 0;   /* no special attack, continue with ordinary attack */

/*
 * hit_me(int wcpen, int damage_type, object attacker, int attack_id)
 *  attacker = me, attack_id = -1 for special attack
 *  damage_type = MAGIC_DT if ac will not help against this attack
 *  hitresult[0] gives the % hurt
 */

    hitresult = enemy->hit_me(5, W_IMPALE, me, -1);

    me->catch_msg("You sink your fangs into " + enemy->query_name() + ".\n");

    enemy->catch_msg(QCTNAME(me) + " sinks " + me->query_possessive()
        +" fangs deep into you.\n");

    tell_watcher(QCTNAME(me) + " sinks " + me->query_possessive()
        +" fangs deep into " + QTNAME(enemy) + ".\n", enemy);

    if(enemy->query_hp() <= 0)
        enemy->do_die(me);

    clone_object(FARM(obj/s_egg))->move(enemy);

    return 1;   /* we've had our special attack, => no ordinary attack */
}


