inherit "/d/Gondor/common/dunedain/npc/npc_dunadan";
inherit "/lib/trade";

#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/lebennin/thornlin/locals.h")
#include "/d/Gondor/lebennin/thornlin/ox_quest.h")

#define PRICE_TO_MAKE_HORN	144

int     msg_id;
object  working_on;

void
create_dunadan()
{
    set_name("thavron");
    set_title("Master Carpenter");
    set_dunedain_house("Thalion");
    add_name(({"carpenter", "man"}));
    set_race_name("human"); 
    set_adj(({"proud", "dark-haired"}));
    set_long(BSN("This is a member of the carpenters' guild. "
      + "His eyes are keen; it looks like he would be able to "
      + "craft very precise work."));

    set_stats(({35+random(10),35+random(10),35+random(10),
          35+random(10),35+random(10),35+random(30)}));

    set_alignment(200);
    set_skill(SS_WEP_KNIFE,80 + random(20));
    set_skill(SS_DEFENCE,20 + random(20));
    set_skill(SS_AWARENESS,20 + random(20));
    set_chat_time(20);
    add_chat("Business is slow nowadays.");
    add_chat("I mostly do work for the Steward's household now.");
    add_chat("I sure could use some extra coins, wood is expensive.");
    add_chat("They should get craftsmen to do some work on the walls.");
    add_chat("Not much left to do, do you have any ideas?");

    set_default_answer(VBFC_ME("default_answer"));
    add_ask(({"horn", "about horn", }), VBFC_ME("ask_horn"));
    add_ask(({"help", }), VBFC_ME("ask_help"));
    add_ask(({"work", }), VBFC_ME("ask_work"));

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    /* need this since we want to trade: */
    config_default_trade();
}

/* solamnian prestige */
int     query_knight_prestige() {return (-5);}

void
return_object(object ob, object who)
{
    if (ob->id("coin") || ob->id("coins"))
    {
        command("gasp");
        command("say Why, thank you, my dear "
          + (who->query_gender() ? "Lady" : "Sir") + "!");
        command("thank "+who->query_real_name());
        command("say It will help my family!");
        command("smile");
        return;
    }

    if (objectp(who) && present(who, ENV(TO)))
    {
        command("give "+ob->query_name()+" to "+who->query_real_name());
        command("say What was that for?");
    }
    else
    {
        command("drop "+ob->query_name());
        command("say Oh! So no one else wants it? So what should I do with it?");
    }
}

void
return_horn(object horn, object who)
{
    remove_alarm(msg_id);
    msg_id = 0;

    if (!objectp(who) || !present(who, ENV(TO)))
    {
        command("sigh");
        command("say What shall I do with this horn now?");
        command("drop horn");
        working_on = 0;
        return;
    }

    horn->remove_object();

    command("emote does some work on the horn.");
    command("emote moves his hands quickly over the horn while he works on it.");
    command("emote finishes his work on the horn.");
    FIX_EUID
    horn = clone_object(THORNLIN_OX_HUNTING_HORN_FILE);
    horn->move(TO);
    command("say Here is a fine hunting horn!");
    command("give horn to "+who->query_real_name());
    if (ENV(horn) == TO)
    {
        command("say Oops, you cannot carry it!");
        command("say I'll just put it here then.");
        command("drop horn");
    }
    command("smile");
    return;
}

void
make_hhorn(object horn, object who)
{
    int    *arr,
            ms = sizeof(MONEY_TYPES);

    if (!objectp(who) || !present(who, ENV(TO)))
    {
        command("shrug");
        set_alarm(2.0, 0.0, &return_object(horn, who));
        return;
    }

    if (objectp(working_on))
    {
        command("say I would like to help you, "
          + "but, alas, I am busy right now!");
        command("say Perhaps you can come back later?");
        set_alarm(2.0, 0.0, &return_object(horn, who));
        return;
    }

    if (!can_pay(PRICE_TO_MAKE_HORN, who))
    {
        command("say I would love to do this Araw horn for you!");
        command("say But it would cost you "+PRICE_TO_MAKE_HORN/12+
                " silver coins.");
        command("say And you do not seem to be able to afford that!");
        set_alarm(2.0, 0.0, &return_object(horn, who));
        return;
    }

    command("say I will make this horn into a hunting horn for you, my dear "
          + (who->query_gender() ? "Lady" : "Sir") + "!");
    command("say But I would like to ask for just "+PRICE_TO_MAKE_HORN/12+
            " silver coins.");

    arr = pay(PRICE_TO_MAKE_HORN, who);
    write("You pay "+text(arr) + (strlen(text(arr[ms..])) ? 
        " and receive "+text(arr[ms..])+" in return" : "") + ".\n");
    say(QCTNAME(who)+" pays "+QTNAME(TO)+".\n");

    working_on = horn;

    set_alarm(40.0 + 40.0*rnd(), 0.0, &return_horn(horn, who));

    command("emote starts working the "+horn->short()+".");
    if (!msg_id || !sizeof(get_alarm(msg_id)))
        msg_id = set_alarm(5.0, 10.0, &command("emote is busy working a "+ 
                                              "hunting horn.")); }

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob) || !objectp(from) || !interactive(from))
        return;

    if (!ob->id(THORNLIN_OX_HORN))
    {
        set_alarm(2.0, 0.0, &return_object(ob, from));
        return;
    }
    set_alarm(2.0, 0.0, &make_hhorn(ob, from));
}

int
no_reply()
{
    if (objectp(query_attack()))
        return 1;

    if (!CAN_SEE_IN_ROOM(TO) || !CAN_SEE(TO, TP))
    {
        command("confused");
        command("say Who is talking to me?");
        return 1;
    }
    return 0;
}

string
default_answer()
{
    if (no_reply())
        return "";

    command("peer "+TP->query_real_name());
    command("say I'm afraid I don't know what you are talking about.");
    command("shrug");
    return "";
}

string
ask_horn()
{
    if (no_reply())
        return "";

    command("say What do you want to know about a horn?");
    command("say Give me the horn, if you have one, and I can tell you if it is any good.");
    command("smile");
    command("say I've made several excellent hunting horns for the Steward's household!");
    return "";
}

string
ask_help()
{
    if (no_reply())
        return "";

    command("say Do you want to help me or do you need help?");
    command("peer "+TP->query_real_name());
    return "";
}

string
ask_work()
{
    if (no_reply())
        return "";

    command("say I work as a carpenter.");
    command("say Most of my work is done for the household of the Steward.");
    command("say Alas, there is little work for a carpenter in the city in recent times!");
    command("say But sometimes I can find some little tasks to make some extra money.");
    command("say I'm a little skilled in many different crafts.");

    return "";
}
