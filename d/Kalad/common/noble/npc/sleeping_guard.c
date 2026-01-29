/*
    sleeping_guard.c
    
    Code by Sarr,
    Recoded by Fysix, March 1998
 */
#pragma strict_types

inherit "/d/Kalad/std/monster";

#include "default.h"
#include <money.h>

int key_here;
string house_name;
string color_name;

void
set_key_here()
{
    key_here = 1;
}

void
create_kalad_monster()
{
    string *str = ({
        ({"muscular","beady-eyed"}),
        ({"mean","stone-faced"}),
        ({"fierce","black-skinned"}),
        ({"nasty","shifty-eyed"}),
        ({"proud","big-nosed"}),
        })[random(5)];

    set_name("guard");
    set_adj("sleeping");
    set_race_name("human");
    set_short("sleeping guard of the house of @@query_house_name@@");
    set_long("@@my_long@@");
    set_alignment(400);
    set_knight_prestige(-100);
    add_speak("Don't cause trouble.\n");

    set_stats(({110,110,100,60,60,100}));
    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_WEP_CLUB,100);
    set_skill(SS_DEFENSE,100);
    set_skill(SS_AWARENESS,1);
    set_skill(SS_PARRY,100);

    set_act_time(5);
    add_act("snore");
    set_cact_time(3);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(OBJ_M_NO_ATTACK,"He looks so peaceful, you don't think "+
        "you need to do that.\n");
    set_key_here();

    add_equipment(({
        NOBLE + "wep/" + ({"spiked_mace", "morning_star",
        "steel_broadsword"})[random(3)],
        NOBLE + "arm/os_helm",
        NOBLE + "arm/os_breastplate",
        NOBLE + "arm/os_bracers",
        NOBLE + "arm/os_greaves",
        NOBLE + "arm/sl_boots",
        NOBLE + "arm/house_cloak",
        }));

    MONEY_MAKE_SC(random(35))->move(TO);
}

int
do_take(string str)
{
    string verb;
    object guard;

    verb = query_verb();
    NF(CAP(verb)+" what from what");
    if(str != "key from belt")
        return 0;

    NF("You see no key there.\n");
    if (key_here == 0)
        return 0;

    guard = present("guard", ENV(TO));
    if (guard && guard != TO)
    {
        guard->command("say Hey! What do you think you're doing!");
        guard->command("say I see you doing that!");
        write("You didn't get the key.\n");
        return 1;
    }
    else
    {
        write("You gently remove the key from the belt.\n");
        say(QCTNAME(TP)+" takes a key from the "+short()+"'s belt.\n");
        key_here = 0;
        seteuid(getuid());
        clone_object(NOBLE + "obj/chain_key")->move(TP, 1);
        return 1;
    }

    return 0;
}

string
my_long()
{
    if(key_here)
        return "This guard's job is to protect the house of his Lord. He "+
    "doesn't seem to be doing a good job since he is sleeping.\nA dirty "+
    "key hangs from his belt.\n";
    else
        return "This guard's job is to protect the house of his Lord. He "+
    "doesn't seem to be doing a good job since he is sleeping.\n";
}

void
init_living()
{
    ::init_living();
    add_action(do_take, "take");
    add_action(do_take, "get");
    add_action(do_take, "remove");
}

void
set_house_name(string str)
{
object ob;

    ob = present("cloak");
    ob->set_house_name(str);
    house_name = str;
}

void
set_color_name(string str)
{
object ob;

    ob = present("cloak");
    ob->set_color_name(str);
    color_name = str;
}

string
query_house_name()
{
    return house_name;
}

string
query_color_name()
{
    return color_name;
}

