/*
 * Notable spear wielded by Goblin Lord
 * Finwe, November 2004
 */

#pragma save_binary

inherit "/std/weapon";
inherit "/lib/keep";

#include <stdproperties.h>
#include <filter_funs.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"

#define WEAPON_HIT 22
#define WEAPON_PEN 25

int spear_is_in_both;
string more_descr = "It was made from a long pole with a sharp blade " +
    "attached to the top.";
void create_weapon()
{
    spear_is_in_both = 0;

    set_name("spear");
    add_name("_shire_plain_spear_");
    set_adj("plain");
    set_short("plain spear");
    set_long("@@query_long");
    add_item(({"blade", "spear head", "deadly spear head", "deadly blade"}),
        "The blade is about an arm's length. It was forged of steel and round. The spear head is attached firmly to the pole.\n");
    add_item(({"handle", "pole", "long pole"}),
        "The pole is forged from steel. It is long and smooth, and polished to a dull, rough finish. On top of the pole is a deadly looking spear head.\n");  

    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);

    set_wt(W_POLEARM);
    set_dt(W_SLASH|W_IMPALE);

    set_hands(W_ANYH);
    set_wf(this_object());

    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_WEIGHT,  2000); /* 5 kg */
    add_prop(OBJ_I_VOLUME,  2500); /* 2.5 litres */
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(WEAPON_HIT, WEAPON_PEN) +
      (90+random(21)) / 100);
    set_likely_dull(1);
    set_likely_break(1);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1); /* it is magic */
    add_prop(MAGIC_AM_MAGIC,({ 10, "enchantment" }));
    add_prop(MAGIC_AM_ID_INFO,({"This spear appears special.\n",1,
    "Its effectiveness is dependent on many factors.\n",25,
    "It works best when wielded in both hands.\n",66 }));
    set_keep();
}

string query_long()
{
    if(!query_wielded())
        return "This is a plain spear. " + more_descr + " It is ancient and left over from another age. \n";

    if(!spear_is_in_both)
    return "This is a plain spear. " + more_descr + " If wielded properly, it can be a deadly weapon.\n";
    
    return "This is a notable spear. " + more_descr + " It seems to become an extention of your arms and will do damage to your enemies.\n";
}

void init()
{
    ::init();
    add_action("wield_spear", "wield");
}

int wield_spear(string arg)
{
    mixed err;

    if (parse_command(arg, TO, " [the] %o 'in' [the] 'both' 'hands' ") ||
      ENV(TO)->query_is_goblin_lord())
    {
    spear_is_in_both = 1;
    set_hit((2*WEAPON_HIT));
    set_pen((2*WEAPON_PEN));
    set_hands(W_BOTH);
    set_short("notable spear");
    remove_adj("plain");
    set_adj("notable");
    err = wield_me();
    TP->update_weapon(TO);
    if(err == 1) return 1;
    err = implode(explode(err,"notable"),"plain");
    write(err);
    spear_is_in_both = 0;
    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_hands(W_ANYH);
    remove_adj("notable");
    set_adj("plain");
    set_short("plain spear");
    TP->update_weapon(TO);
    return 1;
    }
    return 0;
}

void leave_env(object from, object to)
{
    spear_is_in_both = 0;
    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_hands(W_ANYH);
    remove_adj("notable");
    set_adj("plain");
    set_short("plain spear");
    ::leave_env(from, to);
}

void unwield()
{
    if (query_wielded()->query_is_goblin_lord())
    return 0;

    spear_is_in_both = 0;
    set_hit(WEAPON_HIT);
    set_pen(WEAPON_PEN);
    set_hands(W_ANYH);
    remove_adj("notable");
    set_adj("plain");
    set_alarm(0.0, 0.0, "set_short", "plain spear");
    return;
}

int try_hit(object enemy)
{
    int skill, stat, skill_e, stat_e, pen, perf, pdam;
    mixed *hitresult;
    object me, enmy;
    string text, ptext;

    me = query_wielded();
    enmy = me->query_enemy();
    skill = me->query_skill(SS_WEP_POLEARM);
    stat = me->query_stat(SS_STR);
    skill_e = enemy->query_skill(SS_DEFENCE);
    stat_e = enemy->query_stat(SS_DEX);

    // We want to cap the stat at around 100 if the stats get too
    // high (above 110)
    if (stat > 110)
        stat = 90 + random(20);
    if (stat_e > 110)
        stat_e = 90 + random(20);

    if(!spear_is_in_both)
    {
    if(random(100) < (skill/2)) return 1;
   if(!enmy) return 0;
    me->catch_msg("You try to hit "+QTNAME(enemy)+" with your " + short() + ", but you suddenly slip and miss with it.\n");
    enemy->catch_msg(QCTNAME(me)+" tries to hit you with "+
      HIS_HER(me) +  " " + short() + ", but it suddenly slips in " + HIS_HER(me) + " hand and misses you.\n");
    me->tell_watcher(QCTNAME(me)+" tries to hit "+QTNAME(enemy)+" with "+
      me->query_possessive()+" " + short() + ", but it slips "+
      "in "+me->query_possessive()+" hand and misses.\n", enemy);
    return 0;
    }

    if ((random(100) < (skill/2)) &&
      (random(skill+stat) > random(skill_e+stat_e)))
    {
    pen = F_PENMOD(40+random(stat/4), skill);
    hitresult = enemy->hit_me(pen, W_IMPALE, me, -1);
    perf = hitresult[2] * 100 / pen;
    pdam = hitresult[0];

    ptext = "a weak";
    if (perf > 15)
        ptext = "a nice";
    if (perf > 30)
        ptext = "a decent";
    if (perf > 45)
        ptext = "a great";
    if (perf > 60)
        ptext = "a wonderful";
    if (perf > 75)
        ptext = "an excellent";
    if (perf > 90)
        ptext = "a deadly";

    text = "unfazed";
    if (pdam > 0)
        text = "annoyed";
    if (pdam > 2)
        text = "bruised";
    if (pdam > 5)
        text = "nicked";
    if (pdam > 10)
        text = "cut";
    if (pdam > 17)
        text = "hurt";
    if (pdam > 25)
        text = "very hurt";
    if (pdam > 35)
        text = "crushed";
    if (pdam > 50)
        text = "pulverized";
    if (pdam > 70)
        text = "doomed";
    if (pdam > 90)
        text = "destroyed";

    me->catch_msg("You leap into the air and do " + ptext + 
        " hit on "+QTNAME(enemy)+" with your " + short() + 
        ". " + capitalize(enemy->query_pronoun()) + " seems to be " + 
        text + ".\n");
    enemy->catch_msg(QCTNAME(me) + " leaps into the air and does " + ptext + 
        " hit on you with " + me->query_possessive() + " " + short() + 
        ". You are "+text+".\n");
    me->tell_watcher(QCTNAME(me) + " leaps into the air and does " + ptext + 
        " hit on " + QTNAME(enemy) + " with " + me->query_possessive() + 
        " " + short() + ". " + capitalize(enemy->query_pronoun()) + 
        " seems to be " + text + ".\n", enemy);
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(me);
        return 0;
    }
    }
    return 1; /* Try hit */
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + query_keep_recover();
}

void
init_recover(string arg)
{
    init_wep_recover(arg);
    init_keep_recover(arg);
}
