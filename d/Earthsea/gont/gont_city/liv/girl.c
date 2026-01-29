/*  Little girl who lost her teddy bear
     coded by Amelia, 4/12/97
*/

#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/width_height";
inherit "/d/Earthsea/lib/remember";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Earthsea/quest_handler/quest_handler.h"

#define TASK_ASK   ({"help", "task", "job",\
    "about task", "about job", "quest", "about quest" })
#define BEAR_ASK ({"bear", "about bear", "teddy bear",\
    "about teddy bear"})
#define MONSTER_ASK ({"monster", "about monster", "thief"})
#define PLAYER_I_GOT_BEAR_QUEST "_player_i_got_bear_quest"

public void
create_earthsea_monster()
{
    set_name("kerru");
    add_name("girl");
    set_race_name("human");
    set_gender(G_FEMALE);
    set_height("very short");
    set_width("skinny");
    set_adj(({"small", "dimpled", "curly-haired"}));
    set_living_name("_kerru_");
    set_long("A dimpled curly-haired little girl. "+
        "She looks to be about four years old.\n");
    set_stats(({40,40,40,40,40,40}));
    add_prop(OBJ_M_NO_ATTACK, "The girl looks at you "+
        "strangely, and you feel suddenly embarrassed.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "The girl holds up "+
        "her hand and shouts loudly, Avert!! The spell "+
        "falls harmlessly on empty air.\n");
    set_act_time(60);
    add_ask(TASK_ASK, VBFC_ME("respond_task_ask"));
    add_ask(BEAR_ASK, VBFC_ME("respond_bear_ask"));
    add_ask(MONSTER_ASK, VBFC_ME("respond_monster_ask"));
    set_default_answer(QCTNAME(this_object()) +
        " says: I don't know that. You will have to go ask " +
        "my mother!\n");
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    set_chat_time(90);
    add_act("sniff");
    add_act("smile childishly");
}

public string
respond_monster_ask()
{
    command("say It was a big green monster!");
    command("cry");
    return "";
}

public string
respond_bear_ask()
{
    command("say My teddy bear got stolen!");
    command("say A monster stole him while I was asleep!");
    command("sniff");
    return "";
}

public string
respond_task_ask()
{
    object tp = this_player();

    if(QH_QUERY_QUEST_COMPLETED(tp, "teddy_bear_quest"))
    {
        command("ask " + lower_case(tp->query_name()) + " " +
            "You already helped me before!");
        return "";
    }

    tp->add_prop(PLAYER_I_GOT_BEAR_QUEST, 1);
    command("sniff");
    command("whisper "+ lower_case(tp->query_name()) +
        " Someone stole my teddy bear! Can you find it for me?");
    command("emote looks at you with sad eyes.");

    return "";
}

public void
reward_teddy_bear(object bear, object player)
{
    if(!player->query_prop(PLAYER_I_GOT_BEAR_QUEST))
    {
        command("say Did you steal my bear?");
        command("pout");
        return;
    }

    player->remove_prop(PLAYER_I_GOT_BEAR_QUEST);
    command("hug bear");
    command("thank "+ lower_case(player->query_name()));

    if(!QH_QUERY_QUEST_COMPLETED(player, "teddy_bear_quest"))
    {
        QH_QUEST_COMPLETED(player, "teddy_bear_quest");
        player->catch_tell("You feel more experienced!\n");
    }

    command("emote happily skips around.");
    bear->remove_object();
}

public void
return_stuff(object ob, object player)
{
    command("say Hmm ... This is not what I wanted!");
    command("give " + ob->query_name() + " to " +
        lower_case(player->query_name()));
    command("sniff");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(!interactive(from))
        return;

    if(ob->query_kerrus_bear())
    {
        set_alarm(2.0, 0.0, &reward_teddy_bear(ob, from));
    } else {
        set_alarm(2.0, 0.0, &return_stuff(ob, from));
    }
}
