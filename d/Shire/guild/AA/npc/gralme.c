/*
 * Varian - May, 2017
 *
 * Scribe for the AA racks
 */

inherit "/std/monster";
inherit "/d/Shire/common/auto_teaming";
inherit "/d/Gondor/common/lib/friend_or_foe.c";

#include "../guild.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define ARM "/d/Shire/guild/AA/obj/"

int alarm_id;

string *helmets = ({ARM + "scribehat"});
string *body = ({ARM + "scribevest" });

create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("gralme");
    set_race_name("goblin");
    set_adj("squint-eyed","slight");
    set_title("the Scribe of Angmar's Army");
    set_stats(({80, 100, 120, 130, 130, 90}), 20);
    set_alignment(-1000);

    set_gender(G_FEMALE);

    set_chat_time(14);
    
    add_chat("Move out of the way, I can't see!");
    add_chat("Work, work, work! Never a break, not for poor Gralme.");
    add_chat("Why can't they afford better writing materials for me?");
    add_chat("When am I going to get a break? It seems like I've been " +
        "here forever!");
    add_chat("This room was really not designed for more than one " +
        "person! Hurry up doing what you need to do and then get out!");
    add_chat("I'm trying to work and people keep barging in here!");
    add_chat("All I said was that I wanted to get a little closer to " +
        "that cute Captain and they throw me in this tiny room!");
    add_chat("Why can't they find someone else to do this?");
    add_chat("They told me it was join the army or live life in a " +
        "prison cell. How is this any different?");
    add_chat("I need a drink!");
    add_chat("I hate these books!");

    add_ask(({"task","tasks","help","quest"}),VBFC_ME("ask_task"));
    add_ask(({"book","books","writing"}),VBFC_ME("ask_book"));
    add_ask(({"work","job","working"}),VBFC_ME("ask_work"));
    add_ask(({"room","office","window","windows"}),VBFC_ME("ask_room"));
    add_ask(({"captain","cute"}),VBFC_ME("ask_captain"));
    add_ask(({"drink","alcohol"}),VBFC_ME("ask_drink"));

    set_default_answer(VBFC_ME("default_answer"));

    add_prop(LIVE_I_SEE_DARK,4);
    add_prop(NPC_I_NO_FEAR,1);

    set_act_time(16);

    add_act("emote scratches her chin in thoughtful contemplation before " +
        "scribbling an entry into one of the books.");
    add_act("emote does her best to try and look around you to see " +
        "through the window so she can do her job.");
    add_act("emote frowns momentarily before writing an entry into one " +
        "of the books.");
    add_act("emote scowls in frustration as it is obvious there is not " +
        "really enough room for more than one person in here.");
    add_act("read used book");
    add_act("read massive book");
    add_act("brood");
    add_act("cough");
    add_act("frown");
    add_act("pout");
    add_act("worry");

    equip(({ 
        one_of_list(helmets),
        one_of_list(body),
    }));

}

string
ask_task()
{
    command("say What are you talking about?");
    command("grumble");
    command("say I'm just stuck in here, locked up like a dog, supposedly " +
        "doing IMPORTANT things for the Captain. Hah! What a joke!");
    command("sulk");
    return "";
}

string
ask_book()
{
    command("say Are you blind? The books are right there! Read them if " +
        "you want, I would rather burn them myself.");
    command("emote sighs deeply before giving one of the books a swift kick.");
    return "";
}

string
ask_work()
{
    command("say Well, I'm stuck in here with this desk, these books and " +
        "a bunch of crappy charcoal. What do you THINK my job is?");
    return "";
}

string
ask_room()
{
    command("say This room is too small! Every time someone enters my " +
        "office I feel like I'm being squashed! Nope, no respect for " +
        "poor Gralme!");
    return "";
}

string
ask_captain()
{
    command("say What? Where did you hear that??? Sheesh, you tell ONE " +
        "person that you think the Captain has a cute butt and suddenly " +
        "the whole world never lets you forget it!");
    return "";
}

string
ask_drink()
{
    command("say Yeah, I could REALLY use a drink! Think you could sneak " +
        "one in here for me?");
    return "";
}


public string
default_answer()
{
   string  answer = one_of_list( ({
        "I don't know, and more importantly, I don't care!",
        "Please stop with the questions, I'm working okay?",
        "Stop bothering me! I'm serious now!",
        "What kind of person asks a question like that!",
        "You talk too much!",
        "Go away now!" }) );
    command("emote frowns at you with intense frustration.");
    command("say " + answer);
    return "";
}

void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
}