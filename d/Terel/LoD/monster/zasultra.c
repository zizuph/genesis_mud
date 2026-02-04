/*
 * Zasultra, the evil demoness.
 *
 * Coded by Mortricia 960406.
 */

#include "/d/Terel/include/Terel.h"
inherit STDMONSTER;

#include <ss_types.h>
#include <wa_types.h>
#include <money.h>
#include <language.h>

#define ALIGN           -780
#define SPELL_DELAY     23
#define PEACE_DELAY     5
#define PARA_OBJ        "/std/paralyze"
#define PARA_TIME       15
#define NO_EXAS         "_zasultra_i_no_exas"

#define OBJ_DIR         LOD_DIR + "obj/"
#define ARM_DIR         LOD_DIR + "armour/"
#define WEP_DIR         LOD_DIR + "weapon/"

#define MAD_OBJ         OBJ_DIR + "madness"

public int para_mad_obj(object who);
public varargs void paralyze_enemy(object foe);
public void madness();
public void my_attack(object enemy, int wc_pen);
public void z_attack(object who);

int prop_check=0;

public string*
query_object_list()
{
    return ({OBJ_DIR + "necklace",
             ARM_DIR + "z_cloak",
             WEP_DIR + "z_knife"});
}

public void
z_attack(object who)
{
    if (!who || environment(who) != ETO) return;
    
    if (member_array(who, query_my_enemies()) >= 0) {
        my_attack(who, 53);
        return;
    }
    
    if (query_attack()) return;
        
    command("whisper " + who->query_real_name() +
            " I hate nosy people like you.");
    command("kill " + who->query_real_name());
    set_alarm(1.0, -1.0, &my_attack(who, 33));
}

public string
my_long()
{
    int n = TP->query_prop(NO_EXAS);
    string desc;
    
    if (n == 0) {
        desc = "At a first look she seems to be young and beautiful, but " +
               "you get the feeling that she doesn't like that you take " +
               "a good look of her.";
    } else if (n == 1) {
        desc = "She is not as young as you first thought. In fact, the more " +
               "you stare at her the older she looks. Also, her beauty seems " +
               "diminish in the same way. You feel very uneasy looking at her.";
    } else {
        desc = "She looks old, wicked and very dangerous. She now return " +
               "your stares with a fierce hatred. You better beware!";
        set_alarm(4.0, -1.0, &z_attack(TP));
    }
    
    if (ETP == ETO) {
        TP->add_prop(NO_EXAS, n + 1);
    }
    return desc;
}

public void
create_monster()
{
    set_name("zasultra");
    add_name("demoness");
    set_living_name("zasultra");
    set_title("the Evil Demoness");
    set_long("She is a tall black-haired black-eyed woman. @@my_long@@\n");

    set_adj(({"black-haired", "black-eyed"}));
    set_race_name("human");
    set_gender(FEMALE);

    set_stats(({103, 148, 105, 150, 157, 130}));
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
    set_skill(SS_AWARENESS,     92);
    set_skill(SS_SPELLCRAFT,    95);
    set_skill(SS_ELEMENT_DEATH, 75 + random(10));
    set_skill(SS_ELEMENT_LIFE,  75 + random(10));

    add_prop(OBJ_I_RES_FIRE,     25);
    add_prop(OBJ_I_RES_MAGIC,    11);
    add_prop(OBJ_I_RES_DEATH,    25);
    add_prop(OBJ_I_RES_POISON,   11);
    add_prop(OBJ_I_RES_IDENTIFY, 35);

    add_prop(LIVE_I_SEE_DARK,   70);
    add_prop(LIVE_I_QUICKNESS,  80);
    
    add_prop(CONT_I_WEIGHT,     60000);
    add_prop(CONT_I_VOLUME,     60000);
    add_prop(CONT_I_HEIGHT,     200);
    add_prop(CONT_I_MAX_WEIGHT, 99000);
    add_prop(CONT_I_MAX_VOLUME, 99000);
    add_prop(LIVE_I_NO_CORPSE,  1);
    
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    
    enable_intro();
    
    set_act_time(300);
    add_act("kiss necklace");

    MONEY_MAKE_PC(1+random(2))->move(TO);
    
    set_alarm(1.0, -1.0, "set_spell_prop", TO);
    prop_check = 1;
}

public void
healing()
{
    command("emote touches her forehead while closing her eyes.");
    heal_hp(100 + random(50));
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
spell_attack(object me, object victim)
{
    switch (random(5))
    {
        case 0:
            command("point " + victim->query_real_name());
            my_attack(victim, 40 + random(50));
            break;
        case 1:
            if (random(7))
                paralyze_enemy(victim);
            else
                madness();
            break;
        case 2:
            command("zarphus");
            return;
        case 3:
            command("zargmon");
            return;
        case 4:
            healing();
            break;
    }
    delay_set_spell_prop(me);
}

/*
 * Function name: add_introduced
 * Description  : Whenever someone is introduced to me (CC), this function
 *                is called in me to tell me that 'name' (BB) is being
 *                introduced to me. The living that does the introduction
 *                (AA) is available though this_player().
 * Arguments    : string name - the [lower case] name of the living that
 *                              is being introduced to me. (BB)
 */
public void
add_introduced(string name)
{
    /* In players, this function makes sure that 'name' appears on your
     * 'introduced' list and then you may later 'remember' him/her. In
     * NPC's you may for instance use it to return the honour by
     * introducing yourself. Note that we don't necessarily have to use
     * an alarm since this function is called _after_ all messages from
     * the original introduction have been printed.
     */

    object who;

    if (!(TO->query_prop(LIVE_I_INTRO_ENABLED))) {
        return;
    }
    
    if ((who = present(name, ETO)) == 0) {
        return;
    }

    if (!who || (ETO != ENV(who))) {
        return;
    }

    if (who->query_alignment() > ALIGN/2) {
        set_alarm(4.0, -1.0, &z_attack(who));
        return;
    }
    
    if (!(who->query_met(TO))) {
        introduce_me(who);
    }
}

public void
drop_ob(object ob)
{
    ob->move(ETO);
    tell_room(ETO, QCTNAME(TO)+" drops "+LANG_ASHORT(ob)+".\n", TO);
}

public void
enter_inv(object ob, object old)
{
    ::enter_inv(ob, old);
    
    if (!old || !living(old)) return;
    
    if (!CAN_SEE(TO, ob)) return;
    
    set_alarm(2.0, -1.0, &drop_ob(ob));
}

public void
my_attack(object enemy, int wc_pen)
{
    mixed *hres;
    string how;
    int dam;
   
    if (!enemy || environment(enemy) != ETO) return;
    
    if (wc_pen < 5)
        dam = 5;
    else if (wc_pen > 100)
        dam = 100;
    else
        dam = wc_pen;

    hres = enemy->hit_me(dam, MAGIC_DT, TO, -1);
    how = "seem unaffected";
    if (hres[0] >  0) how = "get a slight ache in your heart";
    if (hres[0] >  5) how = "get an ache in your heart";
    if (hres[0] > 10) how = "feel an aching pain in your heart";
    if (hres[0] > 25) how = "feel an intense pain in your heart";
    if (hres[0] > 40) how = "feel a terrible pain in your heart";
    if (hres[0] > 75) how = "get an unbearable pain in your heart";
   
    enemy->catch_msg("You "+how+" as "+QTNAME(TO)+" points at you.\n");
    if (hres[0] > 30) {
        tell_room(environment(enemy),
                  QCTNAME(enemy) + " trembles of fear and pain.\n",
                  ({TO, enemy}));
        enemy->add_panic(hres[0]/2);
    }
   
    if (enemy->query_hp() <= 0) enemy->do_die(TO);
}

public void
do_die(object killer)
{    
    if (query_hp() > 0) return;
    
    command("sigh");
    command("drop all");
    
    ::do_die(killer);
}

public int
query_knight_prestige()
{
    return 103;
}

public void
madness()
{
    int i;
    object *e, mad, mad_obj;
    
    e = query_my_enemies();
    
    mad = e[random(sizeof(e))];
    
    if (para_mad_obj(mad)) {
        command("point " + mad->query_real_name());
        my_attack(mad, 33 + random(15));
        return;
    }
    
    e -= ({ mad });
    
    FIX_EUID;
    mad_obj = clone_object(MAD_OBJ);
    mad_obj->set_duration(20 + random(query_stat(SS_WIS)));
    mad_obj->set_friends(e);
    mad_obj->set_caster(TO);
    
    tell_room(ETO, QCTNAME(TO) + " makes a sign in the air while staring at " +
              QTNAME(mad) + ".\n", ({TO, mad}));
    mad->catch_msg(QCTNAME(TO) +
                   " makes a sign in the air while staring at you.\n");
    
    mad->stop_fight(TO);
    TO->stop_fight(mad);
    mad_obj->move(mad);    
}

public varargs void
paralyze_enemy(object foe=0)
{
    int time;
    object *enemies, enemy, para;

    if (!foe) {
        enemies = query_my_enemies();
        if (sizeof(enemies) == 0) return;
        enemy = enemies[random(sizeof(enemies))];
    } else {
        enemy = foe;
    }

    if (para_mad_obj(enemy)) {
        command("point " + enemy->query_real_name());
        my_attack(enemy, 33 + random(15));
        return;
    }
    time  = PARA_TIME + random(10) + query_stat(SS_INT);
    time -= enemy->query_stat(SS_INT);
    time -= random(enemy->query_magic_res(MAGIC_I_RES_DEATH));
    if (time <= 10) time = 10;
    
    time = 5 + random(time);

    command("stare at " + enemy->query_real_name());

    seteuid(getuid());
    para = clone_object(PARA_OBJ);
    para->set_no_show();
    para->add_prop(OBJ_M_NO_DROP, 1);
    para->set_stop_verb("");
    para->set_remove_time(time);
    para->set_stop_object(0);
    para->set_stop_message("You stop being paralyzed.\n");
    para->set_fail_message("You are still paralyzed.\n");
    para->move(enemy);
    
    enemy->catch_msg(QCTNAME(TO) +
                     "'s hateful stare paralyzes you!\n");
    tell_room(ETO, QCTNAME(enemy) + " becomes paralyzed when " +
              QTNAME(TO) + " stares at " + enemy->query_objective() + ".\n",
              ({enemy, TO}));
}

/*
 * Function name: remove_prop_live_o_spell_attack
 * Description:   To prevent unauthorized removal of LIVE_O_SPELL_ATTACK.
 *                Since Mergula is dependent on his spell attacks, we don't
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
 *                Since Mergula is dependent on his spell attacks, we don't
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
 *                Since Mergula is dependent on his spell attacks, we don't
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
 *                Since Mergula is dependent on his spell attacks, we don't
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

public nomask void
peace_attack(object who, object *pend_enemies)
{
    int i;
    
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
    if (TP->query_wiz_level() || TP == TO) {
        ::stop_fight(elist);
        return;
    }
    set_alarm(itof(PEACE_DELAY+random(5)), -1.0,
              &peace_attack(TP, query_my_enemies()));
    
    ::stop_fight(elist);
}

public void
notify_spell_enemy_gone(object enemy)
{
    set_alarm(itof(2+random(SPELL_DELAY)), -1.0, "set_spell_prop", TO);    
}

public int
para_mad_obj(object who)
{
    object *all;
    int i;
    
    all = all_inventory(who);
    
    for (i=0; i<sizeof(all); i++) {
        if (MASTER_OB(all[i]) == PARA_OBJ) return 1;
        if (MASTER_OB(all[i]) == MAD_OBJ) return 1;
    }
    
    return 0;
}

public int
query_see_special_msg()
{
    return 1;
}
