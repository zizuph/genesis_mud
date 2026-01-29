/*  Harbour captain of Gont Port
 *  Coded by Amelia 3/22/98
 */

#pragma strict_types

inherit "/d/Earthsea/travellers/std/monster_base";
inherit "/d/Earthsea/lib/width_height";
inherit "/d/Earthsea/lib/remember";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "defs.h"
#include "/d/Earthsea/quest_handler/quest_handler.h"

#define WEATHER_NOTE OBJ + "weather_note"
#define TRAVELLERS_BADGE "/d/Earthsea/travellers/obj/badge"
#define PLAYER_I_GOT_WEATHER_TOUR "_player_i_got_weather_tour"
#define PLAYER_I_GOT_SKUNK_BERRY_TOUR "_player_i_got_skunk_berry_tour"
#define PLAYER_NAME "_player_s_name"
#define TASK_ASK (({"task", "about task", "job", "about job", "help"}))
#define BADGE_ASK (({"badge", "travellers"}))

private string give_skunk_berry_tour();
private string give_weather_worker_tour();
private int reward_skunk_berry_tour(object berry, object player);
private int return_stuff(object ob, object player);


public void
create_traveller_monster()
{
    set_name("skior");
    set_living_name("_skior_");
    add_name("harbour captain");
    add_name("friedh");
    add_name("skior friedh");
    set_adj(({"tanned", "muscular"}));
    add_adj("middle-aged");
    add_name("captain");
    set_race_name("human");
    set_title("Harbour Master");
    set_gender(G_MALE);
    set_long("This man appears to have once "+
        "spent a lot of time working in sun and sea, as you can "+
        "tell from his tan, tattoos and muscles. However, now "+
        "he is a busy official, tending a desk instead of a "+
        "ship.\n");
    add_equipment(({ WEP + "cutlass", ARM + "breeches", ARM + "sash", 
        ARM + "jerkin" }));
    add_prop(OBJ_M_NO_ATTACK, QCTNAME(this_object()) + " looks at you " +
       "strangely, and you feel suddenly embarrassed.\n");
    set_stats(({ 150, 150, 200, 100, 100, 150, 100 }));
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_AWARENESS, 100);
    add_ask(TASK_ASK, VBFC_ME("respond_task_ask"));
    add_ask(BADGE_ASK, VBFC_ME("respond_badge"));
    set_default_answer(QCTNAME(this_object()) + " says: I don't understand "+
        "your question.\n");
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    set_chat_time(90);
    set_act_time(90);
    add_act("emote ruffles through some papers on his desk.");
    add_act("shiver");
    add_chat("hmm");
    add_chat("They say the Lord of Gont was once a pirate himself! "+
        "His family comes from Pendor, you know...");
    add_chat("Too much paperwork...ahh to be back on the deck "+
        "of a ship again!");
    set_height("tall");
    set_width("normal");
}

/*******************************************************************
 *  RESPONSES TO QUESTIONS
 *******************************************************************/

public void
intro_hook(string str)
{
    object tp = present(str, environment(this_object()));

    if(objectp(tp) && !tp->query_npc())
        command("introduce myself to "+ tp->query_real_name());

    return;
}

public string
respond_badge()
{
    object badge, tp = this_player();
    if (QH_QUERY_QUEST_COMPLETED(tp, "weather_worker_tour") &&
	QH_QUERY_QUEST_COMPLETED(tp, "skunk_berry_tour"))
    {
        command("whisper " + lower_case(tp->query_name()) + " " +
	    " Thank you for helping me in the past, you have " +
	    "been a great help. I would gladly vouch for your " +
            "entry to the Travellers.");
        setuid();
        seteuid(getuid());
        badge = clone_object(TRAVELLERS_BADGE);
        badge->add_prop(PLAYER_NAME, tp->query_real_name());
        tp->catch_msg(QCTNAME(this_object()) + " gives you a badge.\n");
	badge->move(tp);
        return "";
    }
    command("whisper " + lower_case(tp->query_name()) + " " +
	"I do not think I know you well enough. Do some chores " +
	" and then we can talk about it.");
    return "";
}

public string
respond_task_ask()
{
    object note, tp = this_player();

    if(QH_QUERY_QUEST_COMPLETED(tp, "weather_worker_tour") &&
        !QH_QUERY_QUEST_COMPLETED(tp, "skunk_berry_tour"))
    {
        return give_skunk_berry_tour();
    }
    else if (QH_QUERY_QUEST_COMPLETED(tp, "skunk_berry_tour"))
    {
        command("ask "+ lower_case(tp->query_name()) + " " +
            "Hmm... I think you have helped me before, but thanks "+
            "just the same!");
        command("smile know");
        return "";
    }
    return give_weather_worker_tour();
}

private string
give_weather_worker_tour()
{   
    object note, tp = this_player();
    if(tp->query_prop(PLAYER_I_GOT_WEATHER_TOUR))
    {
        command("ask "+ lower_case(tp->query_name()) + " "+
            "Did you manage to find her? She is in Ten Alders.");
        command("nod");
        return "";
    }

    tp->add_prop(PLAYER_I_GOT_WEATHER_TOUR, 1);
    command("ask "+ lower_case(tp->query_name()) + " "+
        "Hmm...I have a task for you, if you are brave enough. "+
        "The road to Ten Alders is none too safe these days! But I "+
        "need a message to be delivered to the wise woman there. "+
        "She might be able to help me find a weather worker...one of "+
        "the local ones, not as high-priced as those wizards from the "+
        "Wizard School!");
    command("nod");
    command("ask "+ lower_case(tp->query_name()) + " " +
        "Deliver this to her, and there may be a small reward for "+
        "you!");
    setuid();
    seteuid(getuid());
    note = clone_object(WEATHER_NOTE);
    note->add_prop(PLAYER_NAME, tp->query_real_name());
    tp->catch_msg(QCTNAME(this_object()) + " gives you a note.\n");
    command("wink");
    note->move(tp);

    return "";
}


private string
give_skunk_berry_tour()
{   
    object note, tp = this_player();
    if(tp->query_prop(PLAYER_I_GOT_SKUNK_BERRY_TOUR))
    {
        command("ask "+ lower_case(tp->query_name()) + " "+
            "Did you manage to find something?");
        return "";
    }

    tp->add_prop(PLAYER_I_GOT_SKUNK_BERRY_TOUR, 1);
    command("ask "+ lower_case(tp->query_name()) + " "+
        "Hmm...I have a task for you. I have not been feeling well lately " +
        "and frequently get the chills. I fear that my health is " +
        "deteriorating and would like to have some herbal remedies. " +
        "Find something for me and there may be a small reward for " +
        "you.");
    return "";
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if(interactive(from) && (ob->query_herb_name() == "skunk berries") &&
        from->query_prop(PLAYER_I_GOT_SKUNK_BERRY_TOUR))
    {
        set_alarm(2.0, 0.0, &reward_skunk_berry_tour(ob, from));
        return;
    }
    if(interactive(from))
        set_alarm(2.0, 0.0, &return_stuff(ob, from));

    return;
}

private int
reward_skunk_berry_tour(object berry, object player)
{
    player->remove_prop(PLAYER_I_GOT_SKUNK_BERRY_TOUR);
    command("eat berries");
    command("say Oh I feel much better now!");

    if(!QH_QUERY_QUEST_COMPLETED(player, "skunk_berry_tour"))
    {
        command("thank "+ lower_case(player->query_name()));
        QH_QUEST_COMPLETED(player, "skunk_berry_tour");
        player->remove_prop(PLAYER_I_GOT_SKUNK_BERRY_TOUR);
        player->catch_tell("You feel a little more experienced!\n");
    }

    return 1;
}

private int
return_stuff(object ob, object player)
{
    command("give "+ ob->query_name() + " to "+
        lower_case(player->query_name()));
    command("say No, thank you.");
    return 1;
}
