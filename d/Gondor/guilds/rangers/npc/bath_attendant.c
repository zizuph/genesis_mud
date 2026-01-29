/*
 * /d/Gondor/common/guild/north/npc/bath_attendant.c
 *
 * Modification history:
 * 28-Feb-98, Gnadnar: vary gender (only fair to have a
 *    cute dude handing out towels some of the time) and
 *    conform to domain.rules.
 * 15-Jul-01, Alto: change inheritance for new rangers theme
 */
inherit "/d/Gondor/std/monster.c";
inherit "/d/Gondor/common/lib/logkill.c";
inherit "/d/Gondor/common/lib/make_money.c";

#include <const.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "../rangers.h"
#include "/d/Gondor/defs.h"

#define RON_I_HAVE_BATHED  "_RoN_i_have_bathed"
#define WET                 "i_am_wet"
#define BATHING             "i_am_bathing"
#define GOT_SOAP            "got_extra_soap"

public void   create_gondor_monster();
public string ask_towel();
public string ask_soap();
public string ask_water();
public string ask_bath();
public void   give_towel(object tp);
public void   give_soap(object tp);


/*
 * Function name: create_gondor_monster
 * Description  : set up the bath attendant
 */
public void
create_gondor_monster()
{
    if (random(2))
    {
        set_name("lanforn");
        set_title("the bath attendant for the Rangers of the North");
        set_living_name("_lanforn_");
        add_name(({ "bath attendant", "attendant", "man" }));
        set_race_name("human");
        set_adj(({"young", "shy"}));
        set_gender(G_MALE);
   
        set_long("This young man is here to help the Rangers who have " +
            "come for a bath. He takes care of warming up enough " +
            "hot water, bringing in fresh towels, and anything else " +
            "required for a nice bath. You may ask him about bathing " +
            "if you need instructions.\n");
    }
    else
    {
        set_name("liniel");
        set_title("the bath attendant for the Rangers of the North");
        set_living_name("_liniel_");
        add_name(({ "bath attendant", "attendant", "woman" }));
        set_race_name("human");
        set_adj(({"young", "shy"}));
        set_gender(G_FEMALE);
   
        set_long("This young woman is here to help the Rangers who have " +
            "come for a bath. She takes care of warming up enough " +
            "hot water, bringing in fresh towels, and anything else " +
            "required for a nice bath. You may ask her about bathing " +
            "if you need instructions.\n");
    }

    set_intro(3.0);
    Equipment = ({ (MINAS_DIR + "obj/mtunic") });
    set_stats(({30, 57, 48, 37, 40, 49}));
    get_money();
    set_skill(SS_DEFENSE,      29 + random(50));
    set_skill(SS_UNARM_COMBAT, 30 + random(42));
    set_skill(SS_AWARENESS,    30 + random(19));
    set_alignment(500);
    add_prop(CONT_I_HEIGHT, 180); /* normal */
    add_prop(CONT_I_WEIGHT, 63000); /* lean */
   
    set_chat_time(6);
    add_chat("How warm would you like your bath water?");
    add_chat("Would you be needing any more soap, friend Ranger?");
    add_chat("I can never keep enough fresh towels on hand, it seems.");
    add_chat("Don't forget your belongings -- you put them in the stand.");
    add_chat("Where have you been scouting lately?");
    add_chat("Have you ever been to Rivendell? I have.");
    add_chat("Have you ever been near Bree? Now there's a scary place.");
    add_chat("What's the harm in a little bath water? Don't be afraid.");
    add_chat("The fire needs more wood, I think.");
   
    set_act_time(5);
    add_act("emote stokes the fire up some more.");
    add_act("tap");
    add_act("ponder where the clean towels are.");
    add_act("emote starts heating another pot of water.");
    add_act("emote gathers some towels from the hamper and takes them " +
        "for cleaning.");
   
    add_ask(({"for bath", "help", "bathing", "baths", "about bath",
        "bath", "about bathing"}), ask_bath); 
    add_ask(({"towel", "for towel", "about towel"}), ask_towel);
    add_ask(({"soap", "more soap", "for more soap", "for soap",
        "about soap"}), ask_soap);
    add_ask(({"water", "extra water", "for extra water", "for water",
        "more water", "for more water"}), ask_water); 
    set_default_answer("say I'm very sorry, but I don't understand " +
        "your question.");
   
}

/*
 * Function name: ask_towel
 * Description  : respond to request for towel
 * Returns      : null str (response given via command())
 */
public string
ask_towel()
{
    object tp = TP;
   
    if (objectp(present("towel", tp)))
    {
        command("say No, no, you already have a towel!");
        command("smile shy");
    }
    else if (tp->query_prop(BATHING))
    {
        command("say Leave the tub first, then I will give you a towel.");
    }
    else if (!tp->query_prop(WET))
    {
        command("say But you don't need a towel -- you are quite dry.");
    }
    else
    {
        give_towel(tp);
    }
    return "";
}


/*
 * Function name: ask_soap
 * Description  : respond to request for soap
 * Returns      : null str (response given via command())
 */
public string
ask_soap()
{
    int day = CLOCK->query_day();
    object tp = TP;
   
    if (objectp(present("soap", tp)))
    {
        command("say No, no, you already have some soap!");
        command("smile shy");
    }
    else if (!tp->query_prop(BATHING))
    {
        if (!tp->query_prop(RON_I_HAVE_BATHED))
        {
            command("say You should enter the tub first; you wouldn't want " +
                "to bathe dry, would you?");
            if (tp->query_gender() != query_gender())
            {
                command("say I will look away.");
                command("blush");
                write(TO->query_The_name(tp) + " turns " + POSSESSIVE(TO) +
                    " back on you so you can get undressed.\n");
                say(QCTNAME(TO) + " turns " + POSSESSIVE(TO) +
                    " back on " + QTNAME(tp) + ".\n");
            }
        }
        else
        {
            command("say You've already dried off; surely you don't " +
                "need more soap now.");
        }
    }
    else
    {
        give_soap(tp);
    }
    return "";
}

/*
 * Function name: ask_water
 * Description  : respond to request for water
 * Returns      : null str (response given via command())
 */
public string
ask_water()
{
    object tp = TP;
    if (!tp->query_prop(BATHING) )
    {
        command("say Well, undress and get into a tub, and I'll bring " +
            "you water.");
        command("smile " + OB_NAME(tp));
    }
    else if (tp->query_prop(BATHING))
    {
        command("say You want more water? Just wait a second.");
        command("emote fetches a pot that was heating over the fire.");
        say(QCTNAME(TO) + " pours the hot water slowly over " + QTNAME(tp) +
            ", who gives a yelp in surprise.\n", tp);
        write(TO->query_The_name(tp) + " pours the hot water over you, " +
            "and you yelp in surprise at how hot it is.\n");
        command("giggle");
    }
    return "";
}

/*
 * Function name: ask_bath
 * Description  : respond to request for bath
 * Returns      : null str (response given via command())
 */
public string 
ask_bath()
{
    object tp = TP;
    if (tp->query_prop(BATHING))
    {
        command("say Well, you seem to have the hang of it...");
        command("say When you've finished bathing, you can stand up, ");
        command("say And I'll bring you a towel, or you can splash "); 
        command("say as long as you like, I'll keep the water hot.");
        command("smile kind");
    }
    else if (tp->query_prop(WET))
    {
        command("say You should dry yourself, silly.");
        command("smile merrily");
        if (!present("towel", tp))
        {
            command("say Here, I'll get you a towel.");
            give_towel(tp);
        }
    }
    else if (tp->query_prop(RON_I_HAVE_BATHED))
    {
        command("say You've already bathed, I believe.");
    }
    else
    {
        command("say It's really quite simple -- just enter a tub. " +
            "Then I'll bring over the hot water and soap and " +
            "you can get to washing yourself.");
        command("smile encouragingly");
    }
    return "";
}

/*
 * Function name: give_towel
 * Description  : give someone a towel
 * Arguments    : object tp -- the recipient
 */
public void
give_towel(object tp)
{
    object to = TO, env = ENV(to), towel;

    set_this_player(tp);

    write(to->query_The_name(tp) + " gives you a plush towel.\n");
    tell_room(env, QCTNAME(to) + " gives " + QTNAME(tp) +
        " a plush towel.\n", tp);
    FIX_EUID;
    towel = clone_object(RANGERS_OBJ + "towel");
    if (towel->move(tp))
    {
        write("Oops! You dropped it.\n");
        tell_room(env, QCTNAME(tp) + " drops a towel.\n", tp);

        if (towel->move(env))
            towel->move(env, 1);
    }
}

/*
 * Function name: give_soap
 * Description  : give someone a soap
 * Arguments    : object tp -- the recipient
 */
public void
give_soap(object tp)
{
    object to = TO, env = ENV(to), soap;

    set_this_player(tp);

    write(to->query_The_name(tp) + " gives you a bar of soap.\n");
    tell_room(env, QCTNAME(to) + " gives " + QTNAME(tp) +
        " a bar of soap.\n", tp);
    FIX_EUID;
    soap = clone_object(RANGERS_OBJ + "soap");
    if (soap->move(tp))
    {
        write("Oops! You dropped it.\n");
        tell_room(env, QCTNAME(tp) + " drops a bar of soap.\n", tp);

        if (soap->move(env))
            soap->move(env, 1);
    }
}
