/*
 *  /d/Emerald/telberin/mercantile/npc/store_owner.c
 *
 *  This is the shopkeeper for the General Store of Telberin.
 *
 *  Copyright (c) July 2003, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/telberin/npc/telberin_elf";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"


/* 
 * Function name:        create_telberin_elf
 * Description  :        set up the npc
 */
public void
create_telberin_elf() 
{
    set_living_name("hendi");
    set_name("hendi");
    add_name( ({ "owner", "shopkeeper", "shopowner",
                 "store owner", "dealer" }) );
    set_adj( ({ "large", "kind-eyed" }) );

    set_title("Assant, Owner of the General Store of Telberin");

    set_short("large, kind-eyed elf");
    set_long("This elf looks more friendly than most. His kind"
      + " eyes twinkle with warmth as he goes about the business"
      + " of tending his store.\n");

    config_elf(70); /* Not much of a fighter. */

    set_skill(SS_WEP_SWORD, random(10)+40);
    set_skill(SS_DEFENCE,   random(10)+30);
    set_skill(SS_PARRY,     random(10)+20);
    set_skill(SS_AWARENESS, random(10)+90);
    set_skill(SS_TRADING,   90);

    set_alignment(50 + random(400));

    set_act_time(20);
    add_act("emote strolls around the shop, smiling to himself.");
    add_act("emote counts a few of the items in one corner of the"
      + " shop and then returns smiling to the counter.");
    add_act("emote whistles a merry tune.");
    add_act("emote stares contentedly around the room.");
    add_act("emote dozes off for a second, and then comes awake"
      + " again with a start.");

    set_cact_time(10);
    add_cact("emote tries desparately to avoid your attacks.");
    add_cact("emote peers at you in surprise and outrage.");
    add_cact("shout I need assistance! Some fool has attacked me!");
    add_cact("emote shrieks: This is no way to behave! Leave this"
      + " city at once!");

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    set_job_response("Oh, I sell things people need, I suppose!");
}

varargs void
do_bow(object tp = TP)
{
    if (objectp(tp))
        command("salute " + TP->query_real_name());
    command("say Hello, good adventurer!");
    command("say Perhaps I have something here you might need?");
}


public void
emote_hook(string emote, object actor, string adverb = 0)
{
    if (!interactive(actor))
        return;

    switch(emote)
    {
    case "bow":
        set_alarm(2.0, 0.0, &do_bow(TP));
        break;
    case "smile":
        set_alarm(2.0, 0.0, &command("smile at " + actor->query_real_name()));
        break;
    case "sigh":
        set_alarm(2.0, 0.0, &command("comfort " + actor->query_real_name()));
        break;
    case "wave":
        if (!strlen(adverb) || (adverb == "happily"))
            adverb = "goodbye";
        set_alarm(2.0, 0.0, &command("wave "+adverb+" to "
          + actor->query_real_name()));
        break;
    }
}


string
default_answer()
{
    command("peer "+TP->query_real_name());
    command("say I'm sorry, but I don't know what you're talking about.");

    return "";
}


void
return_object(object obj, object to)
{
    string  name = to->query_real_name(),
            obname = OB_NAME(obj);

    if (obj->id("coin"))
    {
        command("say Well now ...");
        command("say Awfully kind of you to tip!");
        command("beam");
        return;
    }

    command("say Thanks, but I don't think I need that.");
    command("give " + obname + " to " + OB_NAME(to));
    if (ENV(obj) == TO)
    {
       command("drop " + obname);
    }
}


/*
 * Function name:        introduce
 * Description  :        create a delay between intro and reaction
 * Arguments    :        object who - the player
 */
public void
introduce(object who)
{
    set_alarm(itof(2 + random(5)), 0.0, &react_intro(who));
} /* introduce */


/*
 * Function name:        react_intro
 * Description  :        the npc introduces himself
 * Arguments    :        tp - the player
 */
void
react_intro(object tp)
{
    if (!present(tp, environment(this_object())))
    {
        command("say Yes, what's that? Who's there?");
        return;
    }

    command("introduce me");
} /* react_intro */


void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!objectp(from) || !objectp(obj) || !living(from))
        return;

    set_alarm(0.5, 0.0, &return_object(obj, from));
}
