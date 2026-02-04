/*
 * Sawoq, the wicked sorcerer.
 *
 * Coded by Mortricia 960630.
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <language.h>
#include <std.h>

#include "/d/Terel/LoD/dungeon/quest.h"

#define ALIGN           -480
#define SPELL_DELAY     15
#define PEACE_DELAY     5

#define OBJ_DIR         LOD_DIR + "obj/"
#define WEP_DIR         LOD_DIR + "weapon/"
#define ARM_DIR         LOD_DIR + "armour/"

#define GOBLET          (OBJ_DIR + "goblet")

public void my_attack(object enemy, int wc_pen);

int prop_check = 0, pid = 0, invis = 0;

public string*
query_object_list()
{
    return ({WEP_DIR + "staff", ARM_DIR + "robe", GOBLET});
}

public void
create_monster()
{
    ::create_monster();
    
    set_name("sawoq");
    add_name("sorcerer");
    set_title("the Wicked Sorcerer");
    set_long("It is a tall man. He has no hair on his head.\n");

    set_adj(({"tall", "bald"}));
    set_race_name("human");
    set_gender(MALE);

    set_stats(({113, 148, 105, 180, 177, 150}));
    SET_MAX_HP;
    SET_MAX_MANA;
    set_alignment(ALIGN);
    set_all_hitloc_unarmed(40);
    set_all_attack_unarmed(20, 55);
    set_skill(SS_DEFENCE,       90);
    set_skill(SS_WEP_KNIFE,     95);
    set_skill(SS_PARRY,         70);
    set_skill(SS_BLIND_COMBAT,  70);
    set_skill(SS_UNARM_COMBAT,  40);
    set_skill(SS_AWARENESS,     95);
    set_skill(SS_SPELLCRAFT,    95);
    set_skill(SS_ELEMENT_DEATH, 80 + random(10));
    set_skill(SS_ELEMENT_LIFE,  80 + random(10));

    add_prop(OBJ_I_RES_FIRE,     25);
    add_prop(OBJ_I_RES_MAGIC,    11);
    add_prop(OBJ_I_RES_DEATH,    25);
    add_prop(OBJ_I_RES_POISON,   11);
    add_prop(OBJ_I_RES_IDENTIFY, 35);

    add_prop(LIVE_I_SEE_DARK,   80);
    add_prop(LIVE_I_QUICKNESS,  90);
    add_prop(LIVE_I_SEE_INVIS,  50);
    
    add_prop(CONT_I_WEIGHT,     80000);
    add_prop(CONT_I_VOLUME,     80000);
    add_prop(CONT_I_HEIGHT,     190);
    add_prop(CONT_I_MAX_WEIGHT, 109000);
    add_prop(CONT_I_MAX_VOLUME, 109000);
    add_prop(LIVE_I_NO_CORPSE,  1);
    
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    
    enable_intro();
    
    set_act_time(75);
    add_act("grin wickedly");
    add_act("@@drink_from_goblet");
    
    set_alarm(1.0, -1.0, "set_spell_prop", TO);
    prop_check = 1;
}

public string
drink_from_goblet()
{
    object goblet = present(DQ_GOBLET);
    
    if (query_hp() < query_max_hp() && goblet)
    {
        goblet->fill_it_with_water(TO);
        command("drink water from goblet");
    }
    
    return "smile wickedly";
}

public void
healing()
{
    object staff = present("staff");
    int heal, h = query_max_hp() - query_hp();
    
    if (!staff || !h)
        return;
        
    command("kiss staff");
    heal = 250 + random(150);
    if (heal > h)
        heal = h;
    
    heal_hp(heal);
}

public void
set_spell_prop(object ob)
{
    prop_check = 0;
    if (query_prop(LIVE_O_SPELL_ATTACK) != ob)
        add_prop(LIVE_O_SPELL_ATTACK, ob);
    prop_check = 1;
}

public void
delay_set_spell_prop(object me)
{
    set_alarm(itof(2+random(SPELL_DELAY)), -1.0, &set_spell_prop(me));
}

public void
go_vis(object victim)
{
    add_prop(OBJ_I_INVIS, 0);
    invis = 0;
    my_attack(victim, 75);
}

public void
go_invis(object victim, int time)
{
    command("wave wickedly");
    add_prop(OBJ_I_INVIS, 30 + random(10));
    invis = set_alarm(itof(time), 0.0, &go_vis(victim));
}

public void
unstun(object who)
{
    if (who) {
        who->remove_stun();
        who->catch_msg("You are able to concentrate again.\n");
    }
}

public void
stun(object who)
{
    if (!who)
        return;
    
    command("cackle wickedly");
    who->add_stun();
    who->catch_msg("You lose your concentration for the moment and " +
                   "cannot pursue the fighting properly.\n");
    tell_room(ENV(who), QCTNAME(who) + " looks dizzy.\n", who);
    set_alarm(itof(4 + random(7)), 0.0, &unstun(who));
}

public void
spell_attack(object me, object victim)
{
    switch (random(5))
    {
        case 0:
            my_attack(victim, 70 + random(31));
            break;
        case 1:
            my_attack(victim, 40 + random(31));
            break;
        case 2:
            if (!victim->query_prop(LIVE_I_STUNNED))
            {
                stun(victim);
                break;
            }
        case 3:
            if (!invis)
            {
                go_invis(victim, 10 + random(20));
                break;
            }
        case 4:
            healing();
            break;
    }
    delay_set_spell_prop(me);
}

public void
drop_ob(object ob)
{
    if (!ob)
        return;
        
    command("drop " + ob->query_name());
}

public void
enter_inv(object ob, object old)
{        
    ::enter_inv(ob, old);
    
    if (!old || !living(old) || !CAN_SEE(TO, ob))
        return;
    
    set_alarm(2.0, -1.0, &drop_ob(ob));
}

public void
my_attack(object enemy, int wc_pen)
{
    mixed *hres;
    string how;
    int dam;
    object staff = present("staff");
   
    if (!enemy || environment(enemy) != ETO || !staff) return;
    
    command("point staff at " + enemy->query_real_name());
    
    if (wc_pen < 5)
        dam = 5;
    else if (wc_pen > 100)
        dam = 100;
    else
        dam = wc_pen;

    hres = enemy->hit_me(dam, MAGIC_DT, TO, -1);
    how = "seem unaffected";
    if (hres[0] >  0) how = "get an uncomfortable feeling";
    if (hres[0] >  5) how = "get a slight pain";
    if (hres[0] > 10) how = "feel an aching pain";
    if (hres[0] > 25) how = "feel an intense pain";
    if (hres[0] > 40) how = "feel a terrible pain";
    if (hres[0] > 75) how = "get an unbearable pain";
   
    enemy->catch_msg("You " + how + " as " + QTNAME(TO) +
                     " touches you with " + query_possessive() + " " +
                     staff->short() + ".\n");
    tell_room(ETO, QCTNAME(enemy) + " seems to " + how + " as " + QTNAME(TO) +
                   " touches " + enemy->query_objective() + " with " +
                   query_possessive() + " " + staff->short() + ".\n",
                   ({TO, enemy}));
    
    if (hres[0] > 30)
    {
        tell_room(environment(enemy),
                  QCTNAME(enemy) + " trembles of fear and pain.\n",
                  ({TO, enemy}));
        enemy->add_panic(hres[0]/2);
    }
   
    if (enemy->query_hp() <= 0)
        enemy->do_die(TO);
}

public int
query_knight_prestige()
{
    return 153;
}

/*
 * Function name: remove_prop_live_o_spell_attack
 * Description:   To prevent unauthorized removal of LIVE_O_SPELL_ATTACK.
 *                Since Sawoq is dependent on his spell attacks, we don't
 *                want any removal or change of this property
 * Arguments:     -
 * Returns:       1 / 0.
 */
public nomask int
remove_prop_live_o_spell_attack()
{
    if (prop_check) return 1;
    return 0;
}

/*
 * Function name: add_prop_live_o_spell_attack
 * Description:   To prevent unauthorized changing of LIVE_O_SPELL_ATTACK.
 *                Since Sawoq is dependent on his spell attacks, we don't
 *                want any removal or change of this property
 * Arguments:     -
 * Returns:       1 / 0.
 */
public nomask int
add_prop_live_o_spell_attack()
{
    if (prop_check) return 1;
    return 0;
}

/*
 * Function name: add_prop_live_i_attack_delay
 * Description:   To prevent changing of LIVE_I_ATTACK_DELAY.
 *                Since Sawoq is dependent on his spell attacks, we don't
 *                want any extra delay of special_attack
 * Arguments:     -
 * Returns:       1 / 0.
 */
public nomask int
add_prop_live_i_attack_delay()
{
    if (prop_check) return 1;
    return 0;
}

public nomask int
remove_prop_live_i_attack_delay()
{
    if (prop_check) return 1;
    return 0;
}

/*
 * Function name: add_prop_live_i_quickness
 * Description:   To prevent changing of LIVE_I_QUICKNESS.
 *                Since Sawoq is dependent on his spell attacks, we don't
 *                want any extra delay of special_attack
 * Arguments:     -
 * Returns:       1 / 0.
 */
public nomask int
add_prop_live_i_quickness()
{
    if (prop_check) return 1;
    return 0;
}

public nomask int
remove_prop_live_i_quickness()
{
    if (prop_check) return 1;
    return 0;
}

public nomask int
add_prop_live_i_stunned()
{
    if (prop_check) return 1;
    return 0;
}

public nomask int
remove_prop_live_i_stunned()
{
    if (prop_check) return 1;
    return 0;
}

public nomask void
peace_attack(object who, object *pend_enemies)
{
    int i;
    
    pid = 0;
    if (query_hp() <= 0) return;

    tell_room(ETO, QCTNAME(TO) + " looks a bit confused for a while.\n", TO);

    for (i=0; i<sizeof(pend_enemies); i++)
        if (pend_enemies[i] && present(pend_enemies[i], ETO))
            command("kill " + pend_enemies[i]->query_real_name());

    if (who && present(who, ETO))
        command("kill " + who->query_real_name());
}

public void
stop_fight(mixed elist)
{
    if (!SECURITY->query_wiz_level(TP->query_real_name())
        && TP != TO && !pid)
        pid = set_alarm(itof(PEACE_DELAY+random(5)), -1.0,
                  &peace_attack(TP, query_my_enemies()));
    
    ::stop_fight(elist);
}

public void
notify_spell_enemy_gone(object enemy)
{
    set_alarm(itof(2+random(SPELL_DELAY)), -1.0, &set_spell_prop(TO));    
}

public int
query_see_special_msg()
{
    return 1;
}

public void
do_die(object killer)
{
    if (query_hp() > 0)
        return;
        
    if (invis)
        go_vis(0);
    
    command("sigh");
    
    ::do_die(killer);
}
