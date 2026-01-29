/*
    castle_captain.c
    
    Code by Sarr,
    recoded by Fysix, Feb 1998
 */

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/special";
inherit "/d/Kalad/lib/assist";

#include "default.h"
#include <money.h>

int more_aid;

object
unique_item(string name, string alter, int num)
{
    if(objectp(find_object(name)))
        if(num < sizeof(object_clones(find_object(name))))
            return clone_object(alter);
        else
            return clone_object(name);
    else
        return clone_object(name);
}

void
create_kalad_monster()
{
    set_name("guard captain");
    add_name("captain");
    set_adj("elite");
    set_race_name("human");
    set_short("captain of the elite guards of the High-Lord");
    set_long("This is the captain of the High-Lord's guards. "+
        "He towers over you in his armour. He has a red beard, and "+
        "his black eyes glare at you with danger.\n");
    set_alignment(500);
    set_knight_prestige(-300);
    add_speak("Don't cause trouble.\n");
    set_stats(({120,120,130,100,100,100}));

    set_skill(SS_WEP_AXE,100);
    set_skill(SS_DEFENSE,100);
    set_skill(SS_AWARENESS,50);
    set_skill(SS_PARRY,100);

    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(LIVE_I_SEE_DARK, 2);
    // I'm a Kabal citizen and will get help from guards
    add_prop(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);
    
    // I'll help Kabal citizens myself
    add_friend(LIVE_I_KABAL_NPC_TYPE, KABAL_CITIZEN);

    set_act_time(3);
    add_act("scratch chin");
    add_act("emote stares straight ahead.");
    add_act("say Watch yourself, stranger...");
    add_act("say This is the High-Lord's castle.");
    add_act("emote checks on his weapons.");
    add_act("emote checks on his armours.");
    set_cact_time(5);
    add_cact("say I shall protect my High-Lord!");
    add_cact("shout Fool! You will die now!");
    add_prop(LIVE_I_NEVERKNOWN,1);

    unique_item(NOBLE + "wep/fire_axe",
        NOBLE + "wep/other_axe", 4)->move(TO, 1);
    add_equipment(({
        NOBLE + "arm/os_helm",
        NOBLE + "arm/mithril_chainmail",
        NOBLE + "arm/os_greaves",
        NOBLE + "arm/sl_boots",
        }));
    MONEY_MAKE_GC(random(35))->move(TO);

    // Configure our special attack with random hitlocation
    set_default_special(10, W_BLUDGEON, 90, 300, A_BODY);
}

// Watch for friends as soon as we move to a new room
void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    watch_friends();
}

void
bring_aid(object enemy)
{
    object trops;
    int i;
    
    seteuid(getuid());
    for (i = 0; i < 3; i++)
    {
        trops = clone_object(NOBLE + "npc/castle_guard");
        trops->move_living("xxx", ENV(TO));
        trops->command("$kill " + OB_NAME(enemy));
    }
    enemy->attack_object(trops);

    command("say Get 'em, boys!");
}

// Special has random weapon penetration
int
query_special_wcpen()
{
    return 400 + random(300);
}

// Bring in guards if I'm hurt too much
int
special_attack(object enemy)
{
    if (query_hp() < 900 && more_aid == 0)
    {
        command("shout Argh! This bloody fool is hardy for sure! Bring "+
            "in more guards!");
        tell_room(ENV(TO),"The sounds of loud footsteps can be heard " +
            "nearby.\n");
        set_alarm(10.0, 0.0, &bring_aid(enemy));
        more_aid = 1;
    }

    return ::special_attack(enemy);
}

// Give messages
void
special_did_hit(object enemy, string hdesc, int hitloc_id, int phurt,
   int damage_type, int damage)
{
    enemy->catch_msg(QCTNAME(TO) + " slams his foot into your " +
        "chest!\n");
    tell_room(ENV(TO), QCTNAME(TO) + " slams his foot into "
        + QTNAME(enemy) + "'s chest!\n", enemy);
    enemy->catch_tell("You can hear bones break.\n");
}

void
attacked_by(object ob)
{
    object guard;

    ::attacked_by(ob);
    guard = present("guard", ENV(TO));
    if (guard)
    {
        command("say Get him, guards!");
        set_alarm(3.0, 0.0, "guard_attack", ob, guard);
    }
    else
    {
        command("say Ok...I guess it's just you and me now! Prepare to "+
            "DIE!");
    }
}

void
guard_attack(object enemy, object guard)
{
    if (objectp(guard) && ENV(enemy) == ENV(TO))
    {
        guard->command("emote moves in front of you, " +
            "forcing you to attack him.");
        enemy->attack_object(guard);
    }
}
