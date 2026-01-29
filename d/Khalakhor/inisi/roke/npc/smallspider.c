/*
 * smallspider.c
 *
 * Used in wild/monk_occtrain1.c
 *
 * Created during the Roke cleanup by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include "defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <money.h>
#include <wa_types.h>
#include <const.h>

int alarmid;

void
create_creature()
{
    int i;
    string type;

    set_name("spider");
    add_name("_small_nasty_spider_");
    set_race_name("spider");
    set_short("small spider");
    set_long("A small nasty spider.\n");
    set_adj("small");
    set_gender(G_NEUTER);

    NEVERKNOWN;
    add_prop(LIVE_I_NO_CORPSE, 1);

    set_attack_unarmed(0, 3, 3, W_IMPALE, 52, "tiny jaws");
    set_attack_unarmed(1, 2, 2, W_BLUDGEON, 6, "front left leg");
    set_attack_unarmed(2, 2, 2, W_BLUDGEON, 6, "front right leg");
    set_attack_unarmed(3, 2, 2, W_BLUDGEON, 6, "second left leg");
    set_attack_unarmed(4, 2, 2, W_BLUDGEON, 6, "second right leg");
    set_attack_unarmed(5, 2, 2, W_BLUDGEON, 6, "third left leg");
    set_attack_unarmed(6, 2, 2, W_BLUDGEON, 6, "third right leg");
    set_attack_unarmed(7, 2, 2, W_BLUDGEON, 6, "back left leg");
    set_attack_unarmed(8, 2, 2, W_BLUDGEON, 6, "back right leg");

    set_hitloc_unarmed(0, ({1}), 20, "head");
    set_hitloc_unarmed(1, ({1}), 80, "body");

    set_base_stat(SS_STR, 5);
    set_base_stat(SS_DEX, 4);
    set_base_stat(SS_CON, 2);
    set_base_stat(SS_INT, 2);
    set_base_stat(SS_WIS, 4);
    set_base_stat(SS_DIS, 5);
}

void
init_living()
{
    ::init_living();

    add_action("kill", "kill");
    add_action("brush", "brush");
}

int
kill(string str)
{
    object *spiders;
    float chance;

    if (str != "spider" && str != "spiders")
        return 0;

    if (environment() != TP)
        return 0;

    if (objectp(present("spider", environment(TP))))
        return 0;

    write("You find it hard to kill a spider that is crawling " +
          "on you. Maybe you can brush it off?\n");
    return 1;
}

void
kill_the_annoying_player(object pl)
{
    tell_room(environment(),
              QCTNAME(this_object()) + " attacks " + QTNAME(pl) + ".\n",
              ({ pl }) );
    tell_object(pl, query_The_name(pl) + " attacks you!\n");

    attack_object(pl);
}

int
brush(string str)
{
    object *spiders;
    float chance;

    if (environment() != TP)
        return 0;

    if (str != "spider" && str != "spider off"  && str != "off spider")
    {
        notify_fail("Brush what?\n");
        return 0;
    }

    // Easier to find one to brush if there are many
    spiders = filter(all_inventory(TP), &->id("_small_nasty_spider_"));
    chance = pow(0.6, itof(sizeof(spiders)));
    if (random(100) < ftoi(chance * 100.0))
    {
        if (sizeof(spiders) > 1)
            write("You don't seem to reach any of the spiders.\n");
        else
            write("You don't seem to reach the spider.\n");
        return 1;
    }

    write("You manage to reach the spider and brush it of you.\n");
    say(QCTNAME(TP) + " brushes of a small spider.\n");

    move(environment(TP), 1);
    set_alarm(1.0, 0.0, &kill_the_annoying_player(TP));
    return 1;
}

void
harass_living()
{
    switch (random(4))
    {
      case 0:
        break;
      case 1:
        environment()->catch_msg("You feel a small spider crawling on you.\n");
        break;
      case 2:
        environment()->catch_msg("A small spider sneaks into your shirt.\n");
        environment()->command("shiver");
        break;
      case 3:
        environment()->catch_msg("A small spider bites you.\n");
        //MUPP, poison from the bite?
        //Note: Be sure the poison can be cured by the herb Ungolestel.
        break;
    }

    alarmid = set_alarm(itof(2 + random(14)), 0.0, &harass_living());
}

void
enter_env(object to, object from)
{
    if (living(to))
    {
        add_prop(OBJ_I_INVIS, 1);
        add_prop(OBJ_I_NO_GIVE, 1);
        add_prop(OBJ_I_NO_DROP, 1);
        add_prop(OBJ_I_NO_STEAL, 1);
        set_no_show();
        if (alarmid) remove_alarm(alarmid);
        alarmid = set_alarm(itof(2 + random(10)), 0.0, &harass_living());
        return;
    }
    
    add_prop(OBJ_I_INVIS, 0);
    add_prop(OBJ_I_NO_GIVE, 0);
    add_prop(OBJ_I_NO_DROP, 0);
    add_prop(OBJ_I_NO_STEAL, 0);
    unset_no_show();
    set_no_show_composite(0);
    remove_alarm(alarmid);
    alarmid = 0;

    ::enter_env(to, from);
}
