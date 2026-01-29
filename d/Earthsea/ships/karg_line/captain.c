/*
* Coded by Ged 6/10/2001
*/

#pragma strict_types

inherit "/d/Genesis/ship/captain";
inherit "/lib/trade";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <money.h>
#include "/sys/filter_funs.h"
#include "defs.h"
inherit REMEMBER;

#define NUM sizeof(MONEY_TYPES)
#define ENV(xx) environment(xx)
#define TICKET KARG_LINE + "ticket"


object ship;

void
set_ship(object s)
{
    ship=s;
}

void
create_captain()
{
    set_name("stam");
    add_name("captain");
    set_adj("small");
    add_adj("sneaky");
    set_race_name("human");
    set_ticket(TICKET);

    clone_object("/d/Earthsea/tricksters/obj/trick_shadow")->
      add_trick_shadow(TO);

    add_prop(OBJ_M_NO_ATTACK, "You feel this man is "+
      "protected by the gods of Earthsea.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "The spell falls "+
      "harmlessly on thin air.\n");
    add_prop(LIVE_I_NEVERKNOWN,1);

    set_chat_time(45);
    add_chat("It's dangerous on the island.");
    add_chat("They have patrol in the forest");
    add_chat("You can sneak into the tent when they on patrol");

    set_living_name("_GONT_KARG_CAPTAIN_");
    default_config_npc(60);

    heal_hp(10000);
    set_hp(50000);

    set_alignment(-500);

    config_default_trade();

    setuid();
    seteuid(getuid());

    trig_new("%w 'introduces' %s", "react_introduce");

    set_hp(50000);
}


void
intro_hook(string str)
{
    command("tlaugh "+this_player()->query_real_name());
    command("say So what??");
}
void
add_introduced(string str)
{
    object tp;

    ::add_introduced(str);
    if (stringp(str))
        if (tp = present(str, environment(this_object())) &&
          interactive(tp))
        {
            set_alarm(1.0, -1.0, &intro_hook(str));
        }
    return;
}

void
init_living()
{
    add_action("buy", "buy");
}

int
buy(string str)
{
    object tp = this_player();
    object buy_ob;
    string what, for_c, get_c, change;
    int *result, m_res, price;

    price = 100;

    if (!str)
    {
        notify_fail("Buy what?\n");
        return 0;
    }

    if(tp->query_average_stat()< 25)
    {
        command("say to "+ tp->query_real_name() + " "+
          "It is too dangerous for you out there! I cannot let you in.");
        command("emote tgrin.");

        return 1;
    }
    if (sscanf(str, "%s with %s and get %s", what, for_c, get_c) != 3)
        if (sscanf(str, "%s with %s", what, for_c) != 2)
            what = str;
    if (what != "ticket")
    {
        notify_fail("I have no such thing for sale.\n");
        return 0;
    }


    buy_ob = clone_object(TICKET);
    if (!objectp(buy_ob))
    {
        notify_fail("I seem to be out of tickets.\n");
        return 0;
    }


    price = buy_ob->query_prop(OBJ_I_VALUE);



    result=pay(price,tp,for_c,0,0,get_c);
    if (sizeof(result)==1) {
        buy_ob->remove_object();
        return 0;
    }
    if (buy_ob->move(tp))
    {
        write("You drop the " + buy_ob->short() + " on the ground.\n");
        say(QCTNAME(tp) + " drops one " + buy_ob->short() +
          " on the ground.\n");
        buy_ob->move(environment(tp));
    }
    else {
        write("You get your " + buy_ob->short() + ".\n");
        say(QCTNAME(tp) + " buys a " + buy_ob->short() + ".\n");
    }
    write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
    if (change)
        write("You get " + change + " as change.\n");

    return 1;
}

