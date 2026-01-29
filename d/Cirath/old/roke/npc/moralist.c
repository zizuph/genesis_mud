/*
 * moralist.c
 *
 * Used in nyreese/red_r3.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/follower";

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

static string *harrassed;

string
query_victims()
{
    int i;
    string s;

    s = "";

    if (!sizeof(harrassed))
        return " No one so far.\n";

    for (i = 0; i < sizeof(harrassed); i++)
        s += capitalize(harrassed[i]) + "\n";
    return s;
}

void
create_follower()
{
    set_name("joseph");
    add_name("moralist");
    set_adj("fanatic");
    set_living_name("moralist");
    set_race_name("moralist");
    set_title("the fanatic moralist");

    default_config_npc(80);

    set_skill(SS_UNARM_COMBAT, 50);
    add_notify_meet_interactive("apa");

    harrassed = ({});

    set_act_time(5);
    add_act("say You know, you shouldn't be drinking that much!");
    add_act("emote points at you.");
    add_act("scream Fornicator!!!");
    add_act("disagree");

    set_follow_on_ships(1);

    trig_new("%s 'wields' %s", "react_wield");
    trig_new("%s 'stops' 'wielding' %s", "react_unwield");
    trig_new("%s 'wears' %s", "react_wear");
    trig_new("%s 'drinks' %s", "react_drink");
    trig_new("%s 'beer' / 'beer.\n' %s", "react_beer");
    trig_new("%s 'sells' %s", "react_sell");
    trig_new("%s 'sold' %s", "react_sell");
    trig_new("%s 'died.\n' %s", "react_death");
    trig_new("%s 'attacks' 'you!\n' %s", "react_attacked");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
}

int
query_knight_prestige()
{
    return -1;
}

void
attkd(object tp)
{
    command("shout HELP! I'm being murdered by " + tp->query_real_name() +
            ".\n");
    command("kick " + tp->query_real_name());
    this_object()->hse();
    run_away();
    command("north");
    command("north");
    command("east");
    command("south");
    command("south");
    command("south");
    command("west");
    set_alarm(1.0, 0.0, &command("shout HELP!!!"));
    set_alarm(2.0, 0.0, &command("shout MURDER!!!"));
    set_alarm(3.0, 0.0,
                                 &command("say It's a good thing I escaped that evil " +
                                 tp->query_real_name() + "!"));
}

void
react_attacked(string s, string ss)
{
    set_alarm(1.0, 0.0, &attkd(TP));
}


void
react_death(string s, string ss)
{
    command("scream");
    command("shout OH MY GOD!!! YOU KILLED HIM!!!");
    command("puke");
    command("panic");
    command("cry");
    command("emote mumbles a prayer.");
}

void
react_wear(string s, string ss)
{
    command("say So, we got new clothes, do we?");
}

void
react_unwield(string s, string ss)
{
    command("say Good! One shall not kill others! Now give me that weapon!");
}

void
react_wield(string s, string ss)
{
    command("say Thou shalt not kill.");
    command("say May God have mercy upon your soul.");
}

void
react_sell(string s, string ss)
{
    command("say Donate money to the poor children!");
}

void
react_french()
{
    command("gasp");
    command("say Doing that in public!!! You immoral creature!");
}

void
react_beer(string s, string ss)
{
    command("say You know, beer is bad for your health!");
}

void
react_drink(string s, string ss)
{
    command("say Drinking is bad for your liver!");
}

void
hse()
{
    harrassed += ({followee});
    followee = "";
}

void
arrive_fun(string s)
{
    if (!stringp(followee) || followee == "")
    {
        if (member_array(capitalize(s), harrassed) < 0)
        {
            follow(s);
            set_alarm(600.0, 0.0, hse);
        }
    }
}

void
apa()
{
    arrive_fun(this_player()->query_real_name());
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!from)
        return;

    if (!living(from))
        return;

    if (function_exists("set_pen", ob) == "/std/weapon")
        if (capitalize(from->query_real_name()) == followee)
        {
            set_alarm(1.0, 0.0,
                      &command("say Thank you! Now I can leave you to your own, knowing"));
            set_alarm(2.0, 0.0,
                      &command("say that you won't hurt anyone!"));
            hse();
        }

    if (function_exists("set_alco_amount", ob) == "/std/drink")
    {
        set_alarm(1.0, 0.0, &command("drink all"));
        set_alarm(2.0, 0.0,
                  &command("say Hey... Why haven't I tried this before?"));
        set_alarm(3.0, 0.0, &command("emote leaves for the closest bar."));
        set_alarm(4.0, 0.0, remove_object);
    }
}

public void
emote_hook(string emote, object actor, string adverb = 0)
{
    if (emote == "french")
        react_french();
}
