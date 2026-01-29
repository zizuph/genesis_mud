inherit "/std/monster";
 
#include "/d/Emerald/defs.h"
 
 
#include <filter_funs.h>
#include <wa_types.h>
 
 
 
void
create_monster()
{
    set_race_name("wight");
    set_short("evil wight");
    set_adj("evil");
    set_long( "A dark, human sized shadowy figure with piercing" +
        " red eyes, this creature looks about a match for anyone.\n" );
 
    add_prop(CONT_I_WEIGHT,60000);
    add_prop(CONT_I_HEIGHT,20000);
    add_prop(LIVE_I_NEVERKNOWN,1);
 
    set_gender(2);
    set_alignment(-500);
 
    set_stats(({120,120,120,150,100,100}));
    set_hp(20000);
    set_mana(1500);
 
    set_all_attack_unarmed(35,30);
 
    set_skill(SS_BLIND_COMBAT,70);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_AWARENESS,70);
}
 
 
 
 
 
static void
tell_watcher(string str, object enemy)
{
    object me, *ob;
    int i;
 
    me = this_object();
    ob = FILTER_LIVE (all_inventory(environment(me))) - ({me});
    ob -= ({ enemy });
    for (i=0 ;i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}
 
 
 
 
int
special_attack(object enemy)
{
    object me;
    mixed hitresult;
    int strloss,tim;
    string how;
 
    me = this_object();
 
    if(random(10))
        return 0;
 
    hitresult = enemy->hit_me(30, W_NO_DT, me, -1);
 
    strloss = random(4) + 1;
    tim = random(2) + 3;
    enemy->add_tmp_stat(SS_STR,-strloss,tim);
    me->add_tmp_stat(SS_STR,strloss,tim);
 
    me->catch_msg("You touch your opponent, and feel strength flow from " +
        enemy->query_possessive() + " body into your own.\n");
 
    enemy->catch_msg(QCTNAME(me) + " touches you, and you feel your strength " +
        "being sapped away.\n");
 
    tell_watcher(QCTNAME(me) + " touches " + QTNAME(enemy) + " and " +
        enemy->query_pronoun() + " looks visibly shaken.\n",enemy);
 
    if (enemy->query_base_stat(SS_STR) <= 25)
        enemy->catch_msg("You now feel extremely weak, and fear that "+
            "you will pass out or even die soon.\n");
 
    if(enemy->query_base_stat(SS_STR) <= 0)
    {
        enemy->catch_msg("You feel the last of your strength being drained "+
            "from your body as you fall\nto the floor\n");
        enemy->set_hp(0);
        enemy->do_die(me);
    }
 
    if (enemy->query_hp() <= 0)
        enemy->do_die(me);
 
    return 1;
}
