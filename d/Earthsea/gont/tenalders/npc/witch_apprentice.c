/*   the witch's helper, Ten Albers
     coded by Amelia, 4/12/97
*/

#pragma strict_types

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/intro";
inherit "/d/Earthsea/lib/width_height";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>
#include <composite.h>
#include "defs.h"
#include "/d/Earthsea/quest_handler/quest_handler.h"

#define TASK_ASK   ({"help", "task", "job", \
    "about task", "about job", "quest", "about quest" })
#define WORDS_ASK ({ "magic words", "words", \
    "special magic words" })
#define WAX_ASK ({ "wax", "about wax", "honeycomb", \
    "about honeycomb", "special ingredient", "ingredient", \
    "about special ingredient" })
#define HERB_SAVE "/d/Earthsea/gont/tenalders/npc/herb_save"

public void
create_earthsea_monster()
{
    set_name("ariel");
    add_name("girl");
    set_gender(G_FEMALE);
    add_adj(({"mysterious", "dark-eyed"}));
    set_living_name("_witch_apprentice_");
    set_race_name("human");
    set_appearance_offset(-50);
    set_height("short");
    set_width("skinny");
    set_long("A mysterious, dark-eyed girl. She has straight " +
        "black hair down to her waist. She seems very " +
        "intelligent.\n");
    default_config_npc(40);
    add_prop(OBJ_M_NO_ATTACK, "The girl looks at you " +
        "strangely, and you feel suddenly embarrassed.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "The girl holds up " +
        "her hand and shouts loudly, Avert!! The spell " +
        "falls harmlessly on empty air.\n");
    set_act_time(60);
    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    add_ask(TASK_ASK, VBFC_ME("respond_task_ask"));
    add_ask(WAX_ASK, VBFC_ME("respond_wax_ask"));
    add_ask(WORDS_ASK, VBFC_ME("respond_spell_words"));
    set_default_answer(query_name() + " smiles mysteriously.\n");
    set_chat_time(90);
    add_chat("There is so much to learn about herbs and spells.");
    add_act("smile innocently");
    add_act("emote examines a dried flower closely.");
    add_act("smile softly");
    add_chat("How may I help you?");
    add_act("emote looks in a small mirror and " +
        "applies some rose pomade to her lips.");
    add_act("emote takes up a flower and inhales its fragrance.");
    set_skill(SS_HERBALISM,96);
}

public void
init_living()
{
  //    init_herbalist();
    ::init_living();
}

public string
respond_task_ask()
{
    object tp = this_player();
    string name = tp->query_real_name();

    if(QH_QUERY_QUEST_COMPLETED(tp, "honeycomb_quest"))
    {
        command("whisper " + name + " " +
            "Thank you but no.. You've helped me far to much already. " +
            "I wouldn't dream of imposing on you any further.\n");
        return "";
    }

    if(tp->query_prop(GETTING_I_THE_WAX))
    {
        command("whisper " + name + " " +
            "Did you find the honeycomb yet? If so, please give it " +
            "to me.");
        command("smile");
        return "";
    }

    tp->add_prop(GETTING_I_THE_WAX, 1);
    command("whisper " + name + " " +
        "I need a special ingredient for my rose pomade.");
    command("whisper " + name + " " +
        "If you can bring this ingredient to me, I may be able to " +
        "give you a nice reward.");
    command("wink");
    command("smile sweetly");
    return "";
}

public string
respond_wax_ask()
{
    object tp = this_player();
    string name = tp->query_real_name();

    if(!tp->query_prop(GETTING_I_THE_WAX))
    {
        command("whisper " + name + " I might need some of that, " +
            "if you ask me for a task.");
        command("wink mysteriously " + name);
        return "";
    }

    command("hmm");
    command("whisper " + name + " " +
        "I need a piece of honeycomb made by clover honey bees. " +
        "The sweet wax makes the lips very smooth and soft, " +
        "following my special formula.");
    command("emote pouts prettily with her luscious " +
        "rose-tinted lips.");
    command("whisper " + name + " " +
        "If you have it already, please give it to me.");
    return "";
}

public string
respond_spell_words()
{
    object tp = this_player();

    if(QH_QUERY_QUEST_COMPLETED(tp, "honeycomb_quest"))
    {
        command("eyebrow");
        tp->catch_msg(QCTNAME(this_object()) + " whispers: You forgot them " +
            "already? Okay, the words were:\n\n\t\t" + GOAT_SPELL + "\n\n");

        tp->add_prop(GOT_GOAT_QUEST, 1);  

        command("say Good luck!");
        command("smile");
        command("wave");
        return "";
    }

    command("smile .");
    command("whisper " + tp->query_real_name() + " " +
        "I wont share my craft with anyone who hasn't proven themselves " +
        "useful to me first. Perhaps if you ask nicely, I'll offer a task for you to do.");
    return "";
}

public void
give_spell(object tp)
{
    command("emote looks very mysterious.");
    tp->catch_msg(QCTNAME(this_object()) + " whispers: The words are these:\n\n" +
        GOAT_SPELL + "\n\n");
    tp->add_prop(GOT_GOAT_QUEST, 1);  
    command("whisper " + tp->query_real_name() + " " +
        "Perhaps these words will be useful to you.");
    command("say Good luck!");
    command("smile");
    command("wave");
}

public void
reward_honeycomb(object honeycomb, object player)
{
    player->remove_prop(GETTING_I_THE_WAX);
    honeycomb->remove_object();
    command("whisper " + player->query_real_name() + " " +
        "I know some special Words, I think it is a spell! " +
        "I don't know what it is used for though, but I heard the " +
        "witch shout this at a goat once!");
    command("emote checks around for eavesdroppers.");

    // don't reward a second time
    // allow player to do over tho, in case they didn't get spell
    if(!QH_QUERY_QUEST_COMPLETED(player, "honeycomb_quest"))
    {
        player->catch_tell("You feel more experienced!\n");
        QH_QUEST_COMPLETED(player, "honeycomb_quest");
    }

    set_alarm(5.0, 0.0, &give_spell(player));
}

public void
thank_player(object ob, object player)
{
    command("thank " + player->query_real_name());

    if(player->query_prop(GETTING_I_THE_WAX))
        set_alarm(2.0, 0.0, &reward_honeycomb(ob, player));
}

public void
return_stuff(object ob, object player)
{
    command("hmm");
    command("say No thank you.");
    command("say If you wish assistance with an herb, " +
        "you can show it to me.");
    command("emote returns " + LANG_THESHORT(ob) + ".");

    if(ob->move(player))
    {
        ob->move(environment(this_object()));
    }
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if((interactive(from)) && ob->query_the_honeycomb())
    {
        set_alarm(2.0, 0.0, &thank_player(ob, from));
        return;
    }

    if((interactive(from)) && !ob->query_the_honeycomb())
    {
        set_alarm(2.0, 0.0, &return_stuff(ob, from));
        return;
    }
}

public void
show_hook(object ob)
{
    if(!function_exists("create_herb", ob))
        return;

    if(ob->query_id_diff() > query_skill(SS_HERBALISM))
    {
        command("hmm");
        command("say It is called a " + ob->query_herb_name() +
            ", but I am afraid I do not know anything about this herb.");
        return;
    }

    if(random(2))
    {
        command("say Ahhh yes, I know of this... it is known as " +
            ob->query_herb_name());
        command("say " + ob->query_id_long());
    } else {
        command("brighten");
        set_alarm(2.0, 0.0, &command("say Oh! That is known as " +
            ob->query_herb_name() + ". " + ob->query_id_long()));
    }
}
