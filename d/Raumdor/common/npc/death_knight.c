/* Originally By Sarr */
/*
 * Created and added by Nerull 2/5-09.
 * Removed extra hp buffer, and special functions, making the
 * npc alot easier to kill. 1/7-10
 * Magical resistchecks added to special attacks added 13/7-10.  -Nerull
 * Randomized special attacks 13/7-10.  - Nerull
 *
 */
/* 2018-02-26 Malus: Replaced specials with new implementation */

#include "defs.h"
inherit STD_UNDEAD;
inherit "/d/Genesis/specials/resist.c";
inherit "/lib/unique.c";

void
create_monster()
{
    ::create_monster();
    set_name("knight");
    set_adj("death");
    add_adj("terrifying");
    set_short("terrifying death knight");
    set_race_name("human");
    set_long(
      "A skeletal figure clad in all in black. His arms, legs, head, and " +
      "feet are armoured. You see nothing but darkness through the eye slits " +
      "in his helm. He is tall, menacing and terrible.\n");

    set_stats(STAT_ARRAY(180));

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_WEP_KNIFE, 100);
    set_skill(SS_WEP_AXE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BASHSTUN, 100);
    set_skill(SS_WHIRLWIND, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_2H_COMBAT, 100);

    set_cact_time(8);
    add_cact("klaugh");
	add_cact("emote rasps: Khiraa!");
	add_cact("emote rasps: The Nameless One shall have your soul!");
    add_cact("emote rasps: You shall die!");

    add_prop(NPC_I_NO_UNARMED, 1);
    add_prop(LIVE_I_UNDEAD, 100);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_all_hitloc_unarmed(31);

    equip(({
      clone_unique("/d/Raumdor/magical_armours/skullplate", 7,
        "/d/Raumdor/common/arm/gfplate2"),
      COMMON_ARM_DIR + "gboots", COMMON_ARM_DIR + "ggloves",
      COMMON_ARM_DIR + "dmrobe", COMMON_ARM_DIR + "dmhelm",
      clone_unique(COMMON_ARM_DIR + "kbbracers", 40, COMMON_ARM_DIR + "rcbracers"), 
      COMMON_WEP_DIR + "kblsword",
      COMMON_WEP_DIR + "kbsword",
    }));
    MONEY_MAKE_GC(random(13))->move(TO, 1);

    add_cmdsoul(SOULS_DIR + "death_knight");
    update_hooks();

    set_exp_factor(125);
}

int
special_attack(object enemy)
{
    int roll = random(8);

    switch (random(8))
    {
        case 0:
            command("$whirlwind");
            break;
        case 1:
            command("$bash");
            break;
        case 2:
            command("$emote hisses something incomprehensible.");
            set_alarm(1.0, 0.0, "burn", enemy);
            break;
        case 3:
            command("$emote hisses something incomprehensible.");
            set_alarm(1.0, 0.0, "death", enemy);
            break;
        default:
    }
    return 0;
}

void
burn(object enemy)
{
    string str;

    int res1;

    res1 =
      combine_resistances(enemy, ({MAGIC_I_RES_MAGIC, MAGIC_I_RES_FIRE}));

    mixed *hr;
    if (!present(enemy, E(TO)))
        return;
    add_mana(-10);
    enemy->catch_msg(QCTNAME(TO) +
                     " waves its hand through the air, and suddenly a " +
                     "flaming ball of fire appears and slams into you!\n");
    tell_room(E(enemy),
      QCTNAME(TO) +
        " waves its hand through the air, and suddenly a flaming ball of " +
        "fire appears and slams into " +
        QTNAME(enemy) + "!\n",
      enemy);

    // Messages when the fireball is resisted.
    if (res1 > random(100))
    {
        enemy->catch_msg(
          "You resist the effects of the ball of fire entirely!\n");

        tell_room(E(enemy),
          QTNAME(enemy) +
            " resists the effects of the ball of fire entirely!\n",
          enemy);

        return;
    }

    hr = enemy->hit_me(random(200) + 200, MAGIC_DT, TO, -1);
    switch (hr[0])
    {
        case 0..10:
            str = "burnt a little bit";
            break;
        case 11..20:
            str = "burnt";
            break;
        case 21..30:
            str = "seared";
            break;
        case 31..50:
            str = "burnt badly";
            break;
        case 51..70:
            str = "seared badly";
            break;
        default:
            str = "burnt to a crisp";
    }
    enemy->catch_msg("You are " + str + "!\n");

    CHECK_DEAD(enemy, TO);
}

void
death(object enemy)
{
    string str;

    int res2;

    res2 =
      combine_resistances(enemy, ({MAGIC_I_RES_MAGIC, MAGIC_I_RES_DEATH}));

    mixed *hr;
    if (!present(enemy, E(TO)))
        return;
    add_mana(-10);
    enemy->catch_msg(
      QCTNAME(TO) + " points an armoured hand at you and utters: Die.\n");
    tell_room(E(enemy),
      QCTNAME(TO) + " points an armoured hand at " + QTNAME(enemy) +
        " and utters: Die.\n",
      enemy);

    // Messages when the fireball is resisted.
    if (res2 > random(100))
    {
        enemy->catch_msg("You resist the effect of the spell entirely!\n");

        tell_room(E(enemy),
          QTNAME(enemy) + " resists the effect of the spell entirely!\n",
          enemy);

        return;
    }

    hr = enemy->hit_me(random(200) + 200, MAGIC_DT, TO, -1);
    switch (hr[0])
    {
        case 0..10:
            str = "slightly";
            break;
        case 11..20:
            str = "solidly";
            break;
        case 21..30:
            str = "with solid force";
            break;
        case 31..50:
            str = "with crushing force";
            break;
        case 51..70:
            str = "with lethal force";
            break;
        default:
            str = "with awsome force";
    }
    enemy->catch_msg(
      "A black beam shoots out of its hand and strikes you " + str + "!\n");
    tell_room(E(enemy),
      "A black beam shoots out of its hand and strikes " + HIM(enemy) + " " +
        str + "!\n",
      enemy);

    CHECK_DEAD(enemy, TO);
}
