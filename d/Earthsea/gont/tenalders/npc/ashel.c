/* bringing back some of the old... Rhyn, nov '02 */

#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/intro";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Earthsea/quest_handler/quest_handler.h"
#include "defs.h"

#define KNIFE "/d/Earthsea/gont/tenalders/wep/carving_knife"

public void
create_earthsea_monster()
{
    set_name("ashel");
    add_name("fisherman");
    set_adj("happy");
    set_race_name("human");
    default_config_npc(40);
    add_prop(OBJ_M_NO_ATTACK, "You feel it would be very "+
      "unwise to attack this man.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "The spell falls "+
        "harmlessly on thin air.\n");
    set_title("the Retired Fisherman and Reformed Convict");
    set_act_time(60);
    set_chat_time(30);
    add_chat("I do miss the sea life, but I can visit the beach " +
        "whenever I please.");
    add_chat("Do not judge me... I served my time. I am a changed man.");
    add_chat("I do feel bad for what I have done. If only that " +
        "old looney Killian would get the picture..");
    add_act("emote beats his hands against his legs rhythmically.");
    add_ask(({"task", "quest", "job", "killian", "emerald", "thief",
        "gem"}),
        "@@ask_task");
    add_ask(({"piccololo", "about piccololo", "piccolo", "about piccolo",
        "drum", "about drum", "about drums", "piccololo drum",
        "piccolo drum", "gut", "about gut", "squeaky gut",
        "little gut", "about squeaky little gut", "squeaky little gut"}),
        "@@ask_drum");
    add_ask(({"plan", "plans", "about plan", "about plans",
        "about the plans", "about the kargs' plans"}),
        "@@ask_plans");
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
}

int
check_visible(object player)
{
    if (!CAN_SEE(this_object(), player) || !this_object()->can_see_in_room())
    {
        command("say Who is there? I can't see you.");
        return 0;
    }
    return 1;
}

public string
ask_task()
{
    object tp = this_player();
    object knife;

    if (!check_visible(tp))
        return "";

    if(tp->query_prop(ASHEL_KNIFE_PROP))
    {
        command("say I have already sent the knife with you!");
        return "";
    }

    if(!QH_QUERY_QUEST_COMPLETED(tp, "karg_eye_quest"))
    {
        command("say I would appreciate it if you would take this " +
            "to Killian.");
        command("say I understand he misses his former occupation, and " +
            "while I do not wish him to know the source of the gift, " +
            "it would do my heart good for it to be returned to him.");
        knife = clone_object(KNIFE);
        knife->move(this_object(), 1);
        command("give knife to " + tp->query_real_name());
        if (environment(knife) == this_object())
        {
            command("say Hmm, I guess I'll have to leave it here for you.");
            command("emote sets the " + knife->short() + " down.");
            knife->move(environment(this_object()), 1);
        }
        tp->add_prop(ASHEL_KNIFE_PROP, 1);
        return "";
    }

    command("say I don't think you can help me today.");

    return "";
}

public string
ask_plans()
{
    if (!check_visible(this_player()))
        return "";
    command("say Plans? What plans?!");
    command("whistle innocently");
    return "";
}

public void
dismiss_ask_drum()
{
    command("say I guess they didn't want to know.");
    command("chuckle .");
}

public void
ask_drum_three(object tp)
{
    if(!tp || !present(tp, environment(this_object())))
    {
        dismiss_ask_drum();
        return;
    }

    command("peer nervously");
    command("say I didn't really mean that. You get the point though!");
}

public void
ask_drum_two(object tp)
{
    if(!tp || !present(tp, environment(this_object())))
    {
        dismiss_ask_drum();
        return;
    }

    command("say Anyways, I was going to tell them how to stretch " +
        "a bird's gut across the proper frame, but that stupid leader " +
        "of theirs figured I would give away their plans. As if I cared " +
        "about those Gontishmen!");
    set_alarm(1.0, 0.0, &ask_drum_three(tp));
}

public string
ask_drum()
{
    object tp = this_player();

    if (!check_visible(tp))
        return "";

    if(!tp->query_prop("__es_bonesman_asked_for_gut__"))
    {
        command("say I used to play the drums in prison. Built " +
            "a few too.");
        command("shrug");
        return "";
    }

    if(QH_QUERY_QUEST_COMPLETED(tp, "bonesmans_drum"))
    {
        command("say You know about the drums, silly!");
        command("smirk");
        return "";
    }

    command("say Ahh... you've been talking to those poor drummers " +
        "that work for the kargs.");
    command("say They're kargs themselves, but they seem different. " +
        "Dumber I guess, if that's possible!");
    set_alarm(2.0, 0.0, &ask_drum_two(tp));
    return "";
}

public void
dismiss_gut(object gut)
{
    command("shrug");
    command("emote disposes of the gut.");
    gut->remove_object();
}

public void
reject_cured_gut(object ob, object tp)
{
    command("say This is already cured!");
    command("emote gives it back.");
    ob->move(tp, 1);
}

public void
reject_already_done(object ob, object tp)
{
    command("say Oh no, I'm not helping you again!");
    command("smirk");
    command("emote gives it back.");
    ob->move(tp, 1);
}

public void
reject_already_given(object ob, object tp)
{
    command("say You already gave me this!");
    command("emote gives it back.");
    ob->move(tp, 1);
}

public void
inform_cure_gut(object gut, object tp)
{
    object to = this_object(), env = environment(to);

    if(!tp || !present(tp, env) || !CAN_SEE(to, tp))
    {
        dismiss_gut(gut);
        return;
    }

    command("say Aha! This gut will work just fine.");
    command("smile");
    command("say Now all I need is a hammer and a little local " +
        "whiskey. I used to use sea water, but the local whiskeys " +
        "are all made from sea water, and the alcohol adds a bit " +
        "of crack to the sound.");
    tp->add_prop("__es_ashel_wants__", ({"hammer", "whiskey"}));
    command("twiddle");
}

public void
finish_curing(object tp)
{
    object gut, to = this_object();

    if(!tp || !present(tp, environment(to)) || !CAN_SEE(to, tp))
    {
        command("say I guess they don't need it anymore.");
        command("shrug");
        return;
    }

    command("emote gives the bird gut a few final taps, then " +
        "steps back to admire his work.");
    command("smile happily");
    command("say Here you go!");

    gut = present("gut", to);

    if(!gut)
    {
        gut = clone_object("/d/Earthsea/gont/beach/obj/gull_gut");
        gut->move(to, 1);
    }

    gut->add_prop("__es_bird_gut_cured__", 1);
    command("give gut to " + tp->query_real_name());
}

public void
continue_curing(object tp)
{
    if(!tp || !present(tp, environment(this_object())))
    {
        command("say I guess they don't need it anymore.");
        command("shrug");
        return;
    }

    command("emote places the bird gut on the table and begins " +
        "flattening it with the hammer.");
    command("whistle busily");
    set_alarm(15.0, 0.0, &finish_curing(tp));
}

public void
begin_curing(object tp)
{
    if(!tp || !present(tp, environment(this_object())))
    {
        command("say I guess they don't need it anymore.");
        return;
    }

    command("emote pours a small amount of whiskey on a " +
        "bird gut and begins rubbing it firmly.");
    set_alarm(8.0, 0.0, &continue_curing(tp));
}

public void
react_whiskey(object ob, object tp)
{
    string *need;

    if(!tp || !present(tp, environment(this_object())))
    {
        command("shrug");
        command("say I guess they don't need it!");
        command("drink all");
        return;
    }

    need = tp->query_prop("__es_ashel_wants__");

    if(!need || member_array("whiskey", need) == -1)
    {
        command("say I don't need that!");
        command("emote gives it back.");
        ob->move(tp, 1);
        return;
    }

    need -= ({ "whiskey" });

    command("say Excellent!");

    if(sizeof(need))
    {
        tp->add_prop("__es_ashel_wants__", need);
        command("say Now all I need is a hammer!");
        return;
    }

    tp->remove_prop("__es_ashel_wants");
    command("say Give me a moment and I'll have your gut ready!");
    set_alarm(2.0, 0.0, &begin_curing(tp));
}

public void
react_hammer(object ob, object tp)
{
    string *need;

    if(!tp || !present(tp, environment(this_object())))
    {
        command("shrug");
        command("say I don't need this stupid thing.");
        command("drop hammer");
        return;
    }

    need = tp->query_prop("__es_ashel_wants__");

    if(!need || member_array("hammer", need) == -1)
    {
        command("say I don't need that!");
        command("emote gives it back.");
        ob->move(tp, 1);
        return;
    }

    need -= ({ "hammer" });

    command("say Fantastic!");

    if(sizeof(need))
    {
        tp->add_prop("__es_ashel_wants__", need);
        command("say Now all I need is some local whiskey!");
        return;
    }

    tp->remove_prop("__es_ashel_wants__");
    command("say Give me a moment and I'll have your gut ready!");
    set_alarm(2.0, 0.0, &begin_curing(tp));
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(!from)
    {
        return;
    }

    if (living(from) && !check_visible(from))
    {
        ob->move(environment(this_object()), 1);
        set_alarm(0.0, 0.0, &command("emote bends over and puts it down."));
        return;
    }

    if(!from->query_prop("__es_bonesman_asked_for_gut__") ||
        (!ob->id("__es_bird_gut__") && !ob->id("hammer") &&
        !ob->id("Old Buzzard rye whiskey")))
    {
        ob->move(from, 1);
        set_alarm(0.0, 0.0, &command("emote gives it back."));
        return;
    }

    if(QH_QUERY_QUEST_COMPLETED(from, "bonesmans_drum"))
    {
        set_alarm(0.0, 0.0, &reject_already_done(ob, from));
        return;
    }

    if(ob->id("Old Buzzard rye whiskey"))
    {
        set_alarm(2.0, 0.0, &react_whiskey(ob, from));
        return;
    }

    if(ob->id("hammer"))
    {
        set_alarm(2.0, 0.0, &react_hammer(ob, from));
        return;
    }

    if(ob->query_prop("__es_bird_gut_cured__"))
    {
        set_alarm(0.0, 0.0, &reject_cured_gut(ob, from));
        return;
    }

    if(from->query_prop("__es_ashel_got_gut__"))
    {
        set_alarm(0.0, 0.0, &reject_already_given(ob, from));
        return;
    }

    set_alarm(2.0, 0.0, &inform_cure_gut(ob, from));
    from->add_prop("__es_ashel_got_gut__", 1);
}
