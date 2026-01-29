/***********************************************************
 *   Responses of herb witch to add_asks, and other 
 *   auxiliary functions for the herb_witch
 *   Coded by Amelia ( 9/13/97)
 ***********************************************************/


#include <macros.h>
#include "../quest.h"
#include "/d/Earthsea/quest_handler/quest_handler.h"

#define WITCH_GARDEN "/d/Earthsea/gont/tenalders/village/witch_garden_3"
#define ROOF "/d/Earthsea/gont/tenalders/village/witch_roof"

#define GOAT_ASK  ({"goat", "about goat", \
    "goat on roof", "goats", "about goat on roof", \
    "about the goat on the roof"})
#define SHELL_ASK ({"shell", "shells", "about shell", \
    "something", "collection", "about something", \
    "seashell", "about seashell"})
#define SKILLS_ASK ({"skills", "about skills" })
#define WIZARD_ASK ({"wizard", "about wizard", \
    "about wizards", "about wizards of Gont"})
#define TASK_ASK ({"task", "about task", "about tasks", \
    "quest", "for quest", "about quest", "tasks", "quests", \
    "about quests", "help", "about help", "job", \
    "about job", "for a job"})
#define KITTY_ASK ({ "cat", "little cat", "black cat", "kitty" })
#define LUCKY_ITEMS ({"lucky items", "items", \
    "about lucky items", "about items", "charms", \
    "about lucky charms" })
#define PARCHMENT_ASK ({"about parchment", "parchment", \
    "Ogion", "ogion", "about Ogion" })
#define PUPIL_ASK ({"pupil", "about pupil", "Ogion's pupil", \
    "Raskalion", "raskalion", "former pupil" })

#define GOT_CLOVER "_player_i_got_lucky_clover_"
#define GOT_HORSESHOE "_player_i_got_lucky_horseshoe_"
#define GOT_FOOT "_player_i_got_lucky_rabbits_foot_"
#define LUCKY_COUNT "_player_i_lucky_items_count_"
#define PLAYER_NAME "_player_s_name"
#define PLAYER_I_GOT_WEATHER_TOUR "_player_i_got_weather_tour"

public string
skills_response()
{
    this_object()->command("smile");
    return "If you wish to learn skills here do <learn> or "+
    "<improve> to see what skills you can train.\n";
}

public string
respond_shell_ask()
{
    object tp = this_player();

    if(tp->query_prop(PLAYER_I_GOT_SHELL_QUEST))
    {
        command("ask " + tp->query_real_name() + " " +
            "Well, I very much like seashells, especially the blue ones. " +
            "If you bring me one, I shall give you a little reward.");
    }

    command("ask " + tp->query_real_name() + " " + 
        "I have a collection of seashells and pretty crystals. " +
        "They have a magic of their own...");
    command("smile mysteriously");

    return "";
}

public string
kitty_response()
{
    command("ask " + this_player()->query_real_name() + " "+
        "I have a little black cat, who is very dear to me. "+
        "She especially likes cream.");
    command("smile");

    return "";
}

public string
pupil_response()
{
    object tp = this_player();
    string name = tp->query_real_name();

    if(!tp->query_prop(GOT_PARCHMENT_QUEST))
    {
        command("ask " + name + " " +
            "Why do you ask?");
        command("peer " + name);
        return "";
    }

    command("ask " + name + " " +
        "This pupil was someone who wanted to be a wizard, " +
        "but had no patience to learn, so he flunked out " +
        "of Wizard School!");
    command("whisper " + name + " " +
        "You can't learn magic by cheating ... it turns the magic " +
        "all wrong!");
    command("shake");
    command("whisper " + name + " " +
        "His name is Raskalion! It is rumoured that his hut is " +
        "northeast of Ten Alders, in the forest!");

    return "";
}

public string
parchment_response()
{
    command("ask " + this_player()->query_real_name() + " " +
        "This is a very secret magical parchment! Do not " +
        "discuss it with anyone!!");
    command("frown");

    return "";
}

string
return_lucky_items()
{
    object tp = this_player();
    string name = tp->query_real_name();

    if(!tp->query_prop(GOT_LUCKY_QUEST))
    {
        command("hmm");
        command("ask " + name + " " +
            "Some items are lucky, and some are not ... It takes a " +
            "bit of wisdom to know the difference!");
        command("smile knowingly");
        return "";
    }

    command("ask " + name + " " +
        "I have three lucky charms in mind: one is green, one is " +
        "furry, and one is made of cold iron!");
    command("nod wisely");
    command("ask " + name + " " +
        "The rest you must discover for yourself.");

    return "";
}

public string
goat_respond()
{
    command("say There is a goat that loves to get at " +
        "my herb garden on the roof. He is such a nuisance!");
    command("shake");

    return "";
}

public void
give_shell_quest(object tp)
{
    tp->add_prop(PLAYER_I_GOT_SHELL_QUEST, 1);
    command("ask " + tp->query_real_name() + " " +
        "If you would like to do something for me, you " +
        "can bring me something for my collection.");
    command("smile");
}

public void
give_kitty_quest(object tp)
{
    string name = tp->query_real_name();

    if(tp->query_prop(GOT_KITTY_QUEST))
    {
        command("ask " + name + " " +
            "Did you feed my kitty yet? She is very hungry!");
        command("peer " + name);
        return;
    }

    tp->add_prop(GOT_KITTY_QUEST, 1);
    command("ask " + name + " "+
        "My little black cat is hungry and needs to be fed.");
    command("smile");
}

public void
parchment_2(object tp)
{
    string name = tp->query_real_name();

    command("whisper " + name + " " +
        "If you can find the parchment and bring it to me, so I can " +
        "return it to Ogion, I will give you a nice reward!");
    command("emote puts her finger to her lips and goes Shhh!");
    command("whisper " + name + " " +
        "Be careful, you may have to steal it!");
    command("sigh");
    command("think what a world, what a world ...");
}

public void
give_parchment_quest(object tp)
{
    string name = tp->query_real_name();

    tp->add_prop(GOT_PARCHMENT_QUEST, 1);
    command("ask " + name + " " +
        "It has come to my ears that there is a secret parchment " +
        "which was stolen from one of the lore books of the great " +
        "mage Ogion by one of his former pupils!");
    command("shake");
    command("ask " + name + " " +
        "This pupil was a very bad egg.");
    set_alarm(2.0, 0.0, &parchment_2(tp));
}

public void
give_lucky_items_quest(object tp)
{
    string name = tp->query_real_name();

    if(tp->query_prop(GOT_LUCKY_QUEST))
    {
        command("ask " + name + " " +
            "Have you found the items yet? If you have, please give " +
            "them to me.");
        command("smile greedily");
        return;
    }

    tp->add_prop(GOT_LUCKY_QUEST, 1);
    tp->add_prop(LUCKY_COUNT, 0);
    command("hmm");
    command("ask " + name + " " +
        "Bring to me three lucky items, and you will get " +
        "a nice reward!");
    command("wink " + name);
}

public void
look_out()
{
    command("emote hangs out the window, and shakes her fist.");
    tell_room(WITCH_GARDEN, "You see a motherly middle-aged woman " +
        "suddenly poke her nose out the kitchen window. She " +
        "shakes her fist angrily in the direction of the roof.\n");
    command("say It's after my herbs!");
    command("grumble");
    command("say Trust a goat to spoil anything ... ");
    command("ask " + this_player()->query_real_name() + " " +
        "Please find him and get him off the roof! But don't " +
        "harm him though!\n");
}

public void
goat_react()
{
    object roof = find_object(ROOF);

    if(objectp(roof) && present("goat", roof))
    {
        command("emote takes her broom and bangs the handle "+
            "against the roof.");
        command("say That goat is on the roof again!");
        set_alarm(2.0, 0.0, &look_out());
    }
}

public void
give_goat_quest(object tp)
{
    string name = tp->query_real_name();

    if(tp->query_prop(GOT_GOAT_QUEST))
    {
        command("ask " + name + " " +
            "Please get that goat off the roof!");
        command("wave " + name);
        return;
    }

    tp->add_prop(GOT_GOAT_QUEST, 1);
    command("say There is this pesky goat that hangs around "+
        "my garden.");
    command("rolleyes");
    command("say He is such a nuisance!");
    set_alarm(2.0, 0.0, &goat_react());
}

public string
return_task_ask()
{
    object tp = this_player(), roof = find_object(ROOF);

    if(!QH_QUERY_QUEST_COMPLETED(tp, "shell_quest"))
    {
        give_shell_quest(tp);
        return "";
    }

    if(!QH_QUERY_QUEST_COMPLETED(tp, "cat_quest"))
    {
        give_kitty_quest(tp);
        return "";
    }

    if(!QH_QUERY_QUEST_COMPLETED(tp, "lucky_quest"))
    {
        give_lucky_items_quest(tp);
        return "";
    }

    if(!QH_QUERY_QUEST_COMPLETED(tp, "parchment_quest"))
    {
        give_parchment_quest(tp);
        return "";
    }

    if(!QH_QUERY_QUEST_COMPLETED(tp, "goat_quest"))
    {
        if((objectp(roof)) && present("goat", roof))
        {
            give_goat_quest(tp);
            return "";
        }
    }

    command("hmm");
    command("ask " + tp->query_real_name() + " " +
        "I have no more jobs for you at this time. Ask again another " +
        "day!");
    command("smile");

    return "";
}

public void
reward_shell_quest(object shell, object tp)
{
    command("say Oh, how lovely! and my favourite colour, too!");
    shell->remove_object();
    command("thank "+ tp->query_real_name());
    command("emote appreciates the beauty of the seashell, "+
        "then puts it away.");

    if((!QH_QUERY_QUEST_COMPLETED(tp, "shell_quest")) &&
        (tp->query_prop(PLAYER_I_GOT_SHELL_QUEST)))
    {
        QH_QUEST_COMPLETED(tp, "shell_quest");
        tp->remove_prop(PLAYER_I_GOT_SHELL_QUEST);
        tp->catch_tell("You feel a little more experienced!\n");
    }
}

public void
reward_parchment_quest(object parchment, object tp)
{
    parchment->remove_object();
    tp->remove_prop(GOT_PARCHMENT_QUEST);
    QH_QUEST_COMPLETED(tp, "parchment_quest");
    command("thank " + tp->query_real_name());
    command("smile gratefully");
    command("say Ogion will be most happy to have this returned!");
    tp->catch_tell("You feel more experienced.\n");
}

public void
kick_out_player(object ob, object from)
{
    //if player gets possession of the parchment, before getting
    //the quest from Aunty, she gets mad and throws him out
    if(!present(from, environment(this_object())))
	return;

    command("peer " + from->query_real_name());
    command("shout Hey! where did you get this!!");
    command("shout Thief, get out!!");
    from->catch_tell("The witch grabs you and throws you out " +
        "the window!!\n");
    tell_room(environment(this_object()), "The witch grabs " + QTNAME(from) +
        " and throws " + from->query_objective() + " out the window!\n",
        ({from}));
    from->move_living("out the window.", WITCH_GARDEN, 1);
}

public void
reward_masters_note(object note, object player)
{
    string name = player->query_real_name();

    command("emote opens and reads the note.");
    command("hmm");

    player->remove_prop(PLAYER_I_GOT_WEATHER_TOUR);

    if(note->query_prop(PLAYER_NAME) == name)
    {
        if(!QH_QUERY_QUEST_COMPLETED(player, "weather_worker_tour"))
        {
            QH_QUEST_COMPLETED(player, "weather_worker_tour");
            player->catch_tell("You feel a little more experienced!\n");
        }

        command("thank " + name);
        command("say I will have to see what I can do for " +
            "my old friend, the harbour master.");
        command("smile mysteriously");
        note->remove_object();
        return;
    }

    note->remove_object();
    command("peer " + name);
    command("say Where did you get this?");
}

public void
reward_player(object tp)
{
    string name = tp->query_real_name();

    if(!tp->query_prop(GOT_LUCKY_QUEST))
        return;

    command("ask " + name + " " +
        "Congratulations! You found all the lucky items.");
    command("smile " + name);
    tp->remove_prop(LUCKY_COUNT);
    tp->remove_prop(GOT_HORSESHOE);
    tp->remove_prop(GOT_CLOVER);
    tp->remove_prop(GOT_FOOT);
    tp->remove_prop(GOT_LUCKY_QUEST);
    tp->catch_tell("Suddenly you feel wiser and more experienced.\n" +
        "Today is your lucky day!\n");
    QH_QUEST_COMPLETED(tp, "lucky_quest");
}

public void
give_back_extra(object item, object tp)
{
    string name = tp->query_real_name();

    command("give " + item->query_name() + " to " + name);
    command("ask " + name +
        " You already gave me one of these. Too many will spoil the " +
        "brew!");
    command("smile kindly");
}

public void
check_lucky_items(object item, object tp)
{
    object to = this_object();
    int count = tp->query_prop(LUCKY_COUNT);
    string name = tp->query_real_name();

    if(item->query_lucky_clover())
    {
        if(tp->query_prop(GOT_CLOVER))
        {
            give_back_extra(item, tp);
            return;
        }

        command("ask " + name + " " +
            "Amazing, you found the lucky four-leaf clover!");
        command("emote tosses the " + item->query_short() +
            " into the kettle and stirs vigorously.");
        tell_room(environment(to), "The brew blasts out a " +
            "hot geyser of steam!\n");
        command("grin");
        tp->add_prop(GOT_CLOVER, 1);
        count++;
        tp->add_prop(LUCKY_COUNT, count);
        item->remove_object();

        if(tp->query_prop(LUCKY_COUNT) == 3)
        {
            reward_player(tp);
        }

        return;
    } else if(item->query_lucky_foot()) {
        if(tp->query_prop(GOT_FOOT))
        {
            give_back_extra(item, tp);
            return;
        }

        command("ask " + name + " " +
            "Ahh! I see you found a nice rabbit's foot!");
        command("emote suddenly throws the rabbit's foot into the " +
            "brew!");
        tell_room(environment(to), "Flames leap up from under the " +
            "kettle!\n");
        command("cackle");
        tp->add_prop(GOT_FOOT, 1);
        count++;
        tp->add_prop(LUCKY_COUNT, count);
        item->remove_object();

        if(tp->query_prop(LUCKY_COUNT) == 3)
        {
            reward_player(tp);
        }

        return;
    } else if(item->query_lucky_horseshoe()) {
        if(tp->query_prop(GOT_HORSESHOE))
        {
            give_back_extra(item, tp);
            return;
        }

        command("ask " + name + " " +
            "The lucky horseshoe! Wonderful!");
        command("emote does a little dance.");
        command("emote tosses the " + item->query_short() + 
            " into the kettle.");
        tell_room(environment(to), "A blast of black smoke erupts " +
            "from the fire!\n");
        tp->command("cough");
        count++;
        tp->add_prop(LUCKY_COUNT, count);
        tp->add_prop(GOT_HORSESHOE, 1);
        item->remove_object();

        if(tp->query_prop(LUCKY_COUNT) == 3)
        {
            reward_player(tp);
        }

        return;
    }

    command("give " + item->query_name() + " to " +
        name);
    command("say Hmm ... this is not what I had in mind!");
}

public void
give_it_back(object item, object tp)
{
    command("say Hmm ... I really don't want this now.");
    command("give " + item->query_name() + " " +
      "to " + tp->query_real_name());
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(!interactive(from))
        return;

    if((from->query_prop(PLAYER_I_GOT_SHELL_QUEST)) &&
        (ob->query_color()) &&
        (ob->query_name() == "seashell"))
    {
        set_alarm(2.0, 0.0, &reward_shell_quest(ob, from));
    } else if((from->query_prop(PLAYER_I_FOUND_PARCHMENT)) &&
        (from->query_prop(GOT_PARCHMENT_QUEST)) &&
        (ob->query_the_parchment()))
    {
        set_alarm(2.0, 0.0, &reward_parchment_quest(ob, from));
    } else if((ob->query_the_parchment())) {
        set_alarm(2.0, 0.0, &kick_out_player(ob, from));
    } else if((ob->query_masters_note())) {
        set_alarm(2.0, 0.0, &reward_masters_note(ob, from));
    } else if((from->query_prop(GOT_LUCKY_QUEST))) {
        set_alarm(2.0, 0.0, &check_lucky_items(ob, from));
    } else {
        set_alarm(2.0, 0.0, &give_it_back(ob, from));
    }
}
