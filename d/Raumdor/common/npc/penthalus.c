/* Death mage, Sarr */
/*
 * Modification log:
 *
 *  - May 2013, Gorboth:
 *      Changed to use clone_unique for powerful resistance robe with
 *      a limit of 7 copies in the game.
 */
/* 2017-11-02 Malus: Modify special to account for silencing effects and
 * magic resistance, along with general cleanup. */
#include "defs.h"
inherit "/d/Raumdor/std/monster";
inherit "/d/Raumdor/lib/intro";
inherit "/lib/unique";
void
create_monster()
{
    ::create_monster();
    set_name("penthalus");
    set_adj("pale");
    add_adj("sinister");
    set_race_name("necromancer");
    set_short("pale sinister necromancer");
    set_stats(({60, 100, 90, 110, 120, 100}));
    set_alignment(-200);
    set_long(
      "This is one radiates an aura of wickedness. Under his black hood, you " +
      "see a deathly white pale face, twisted into an expression of utter " +
      "hatred. His bony white hands clutch his scimitar as he studies " +
      "you.\n");
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_KNIFE, 50);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_PARRY, 90);
    set_title("the Rogue Necromancer of the Khiraa");
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(LIVE_I_SEE_INVIS, 6);
    add_prop(UNDEAD_I_NO_AUTO, 1);
    set_act_time(12);
    add_act("say The Power is mine!");
    add_act("say Only those most gifted and brave may practice the Art.");
    add_act(
      "say Oh my children do love to feast, and how they feast! 'Tis so " +
      "beautiful!");
    set_cact_time(12);
    add_cact("say Thou shalt die foul light-bringer!");
    add_cact("say Prepare to meet the nameless once, fool!");
    add_cact("emote hisses.");
    add_ask("scripture", "@@pen_react@@", 1);

    equip(({
      clone_unique(
        COMMON_ARM_DIR + "pen_robe", 7, COMMON_ARM_DIR + "dmrobe", 1, 66),
      COMMON_WEP_DIR + "scimitar", COMMON_ARM_DIR + "pen_vest",
      clone_unique("/d/Raumdor/magical_misc/bloodstone_medallion.c", 7,
        COMMON_WEP_DIR + "kbdagger", 0, 25),
    }));
}

string
pen_react()
{
    set_alarm(2.0, 0.0, "pen_react2", TP);
    return "grin";
}

void
pen_react2(object ob)
{
    command("emote hisses: So you seek the holy scripture, eh?");
    set_alarm(4.0, 0.0, "pen_react3", ob);
}

void
pen_react3(object ob)
{
    command("emote hisses: Well you aren't getting it!!");
    command("laugh evil");
    command("kill " + lower_case(ob->query_name()));
}

int
do_die(object ob)
{
    command("laugh evil");
    command(
      "emote hisses: You are too late! The scripture is well-hidden in the " +
      "forest! You will never find it!");
    command("emote gurgles blood then finally dies.");

    log_file("necro_killed",
      " --- " + capitalize(ob->query_real_name()) +
        " (Avg:" + ob->query_average_stat() + "), (Str:" + ob->query_stat(0) +
        "), (Dex:" + ob->query_stat(1) + "), (Con:" + ob->query_stat(2) +
        "), (Int:" + ob->query_stat(3) + "), (Wis:" + ob->query_stat(4) +
        "), (Dis:" + ob->query_stat(5) + "), (Race:" + ob->query_stat(6) +
        ") (Occ:" + ob->query_stat(7) + "), (Lay:" + ob->query_stat(8) +
        "), (Craft:" + ob->query_stat(9) + "), (Qxp:" +
        ob->query_exp_quest() + "), (Cxp:" + ob->query_exp_combat() +
        "), (Gxp:" + ob->query_exp_general() +
        "), (Hp max:" + ob->query_max_hp() + "),(Hp left:" + ob->query_hp() +
        ") killed Necromancer at " + extract(ctime(time())) + ".\n");

    ::do_die(ob);
}

int
special_attack(object enemy)
{
    int    intensity = 120;
    string impact    = "drained of life";
    object servant;
    if (random(8))
        return 0;
    if (!random(5))
    {
        if (query_prop(LIVE_M_MOUTH_BLOCKED))
        {
            tell_room(E(TO),
              QCTNAME(TO) +
                " flings his hands in the air and motions as though trying " +
                "speak, but nothing comes out.\n");
            command("scowl .");
            return 1;
        }
        servant = clone_object(one_of_list(({COMMON_NPC_DIR + "wraith",
          COMMON_NPC_DIR + "lzombie", COMMON_NPC_DIR + "gskeleton"})));
        tell_room(E(TO),
          QCTNAME(TO) +
            " flings his hands in the air chanting strange magical words.\n");
        servant->move_living("X", E(TO));
        return 1;
    }

    intensity -= intensity * enemy->query_magic_res(MAGIC_I_RES_MAGIC) / 100;
    tell_room(E(TO),
      QCTNAME(TO) + " grins wickedly as a beam of black light strikes " +
        QCTNAME(enemy) + " in the chest!\n",
      enemy);
    enemy->catch_msg(
      QCTNAME(TO) +
      " grins wickedly as a beam of black light strikes you in the chest!\n");

    if (intensity <= 0)
        impact = "unaffected";
    else if (intensity < 30)
        impact = "slightly " + impact;
    else if (intensity < 60)
        impact = "somewhat " + impact;
    else if (intensity >= 90)
        impact = "considerably " + impact;
    tell_room(E(TO), QCTNAME(enemy) + " seems " + impact + "!\n", enemy);
    enemy->catch_msg("You feel " + impact + "!\n");
    if (intensity > 0)
    {
        tell_room(E(TO), QCTNAME(TO) + " seems restored!\n");
        TO->heal_hp(intensity);
        enemy->heal_hp(-intensity);
        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(TO);
        }
    }
    return 1;
}
