/* 
 * /d/Kalad/common/noble/npc/brutal_guard2.c
 * Purpose    : The brutal guard of the house of Alexander, guards prisoner
 * Located    : /d/Kalad/common/noble/alexander/
 * Created By : Sarr ??.??.95
 * Modified By: Fysix, 02-98, recoded
 */ 

inherit "/d/Kalad/std/monster";

#include "default.h"
#include <money.h>

// Variables
string house_name;
string color_name;

string
*ran_adj()
{
    return ({
        ({"muscular","beady-eyed"}),
        ({"mean","stone-faced"}),
        ({"fierce","black-skinned"}),
        ({"nasty","shifty-eyed"}),
        ({"proud","big-nosed"}),
        })[random(5)];
}

void
create_kalad_monster()
{
    string *str = ran_adj();

    set_name("guard");
    set_adj("brutal");
    set_race_name("human");
    set_short("brutal guard of the House of @@query_house_name@@");
    set_long("This guard's job is to protect the house of his Lord. He "+
        "seems quite capable of doing that, as he is very well paid and "+
        "very well trained.\n");
    set_alignment(400);
    set_knight_prestige(-100);
    set_stats(({110,110,100,60,60,100}));

    set_skill(SS_WEP_SWORD,100);
    set_skill(SS_WEP_CLUB,100);
    set_skill(SS_DEFENSE,100);
    set_skill(SS_AWARENESS,50);
    set_skill(SS_PARRY,100);

    set_act_time(5);
    add_act("beat bloodied goblin");
    add_act("slap bloodied goblin");
    add_act("growl");
    add_act("spit goblin");
    add_act("say Get out of here!");

    add_speak("Don't cause trouble.\n");
    add_speak("If you want to leave the room, just knock on the door.\n");

    add_ask(({"help","goblin","job","task"}),"The "+short()+" says: "+
        "Yes, we need help in finding this item that this wretched "+
        "Red Fang goblin stole.\n");
    add_ask("item","It is a map...if you can return it to Lord Alexander, "+
        "He will reward you greatly. This goblin was captured somewhere in the "+
        "High-Lord's castle, so we assume he hid it there somehwere.\n");
    add_ask("key","Key? What key? You found a key? Let me see it...\n");
    set_default_answer("The "+short()+" says: I don't know what you mean.\n");

    set_cact_time(3);
    add_cact("shout Fool! You will die now!");

    add_prop(LIVE_I_NEVERKNOWN,1);

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

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (MASTER_OB(ob) == (NOBLE + "obj/free_goblin_key"))
        set_alarm(3.0, 0.0, "react_key", from, ob);
}

void
react_key(object ob, object key)
{
    if(ob->query_race_name() != "human")
        command("drop " + key->query_name());
    else
        {
        command("say Yes, I remember seing a chest that might fit this key.");
        command("say Only, it belongs to this goblin in the pub...hmmm.");
        command("say Well, you have my permission to arrest him in the "+
            "name of Lord Alexander.");
        ob->add_prop("_kalad_permission_arrest",1);
        command("give key to "+lower_case(ob->query_name()));
    }
}

void
init_living()
{
    ::init_living();
    if (interactive(TP) && TP->query_race_name() != "human")
        set_alarm(3.0,0.0,"kill_demi",TP);
}

void
kill_demi(object ob)
{
    command("say Get out of here you foul scum!");
    command("kill "+lower_case(ob->query_name()));
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

