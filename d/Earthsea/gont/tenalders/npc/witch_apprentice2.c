/*   the witch's helper, Ten Albers
     coded by Amelia, 4/12/97
*/

inherit "/d/Earthsea/std/monster";
inherit "/d/Earthsea/lib/remember";
inherit "/d/Earthsea/lib/width_height";



#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/language.h"
#include "defs.h"
#include "/d/Earthsea/quest_handler/quest_handler.h"


#define TASK_ASK   ({"help", "task", "job",\
"about task", "about job", "quest", "about quest" })

#define WORDS_ASK ({ "magic words", "words",\
"special magic words" })
#define WAX_ASK ({ "wax", "about wax", "honeycomb",\
"about honeycomb", "special ingredient", "ingredient",\
"about special ingredient" })


// prototypes
int reward_honeycomb(object honeycomb, object player);
int thank_player(object ob, object player);
int give_spell(object tp);
int show_react(object tp, object ob);
int herb_properties(string properties, object tp);
int return_stuff(object ob, object player);

void
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
    set_long(BS("A mysterious, dark-eyed girl. She has straight "+
	"black hair down to her waist. She seems very "+
	"intelligent.\n", 70));

    set_stats(({40,40,40,40,40,40}));
    add_prop(OBJ_M_NO_ATTACK, "The girl looks at you "+
      "strangely, and you feel suddenly embarrassed.\n");
    add_prop(OBJ_M_NO_MAGIC_ATTACK, "The girl holds up "+
      "her hand and shouts loudly, Avert!! The spell "+
      "falls harmlessly on empty air.\n");
    set_act_time(60);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    add_ask(TASK_ASK, VBFC_ME("respond_task_ask"));
    add_ask(WAX_ASK, VBFC_ME("respond_wax_ask"));
    set_default_answer(TO->query_name() + " smiles mysteriously.\n");
    set_chat_time(90);
    add_chat("There is so much to learn about herbs and spells.");
    add_act("smile innocently");
    add_act("emote examines a dried flower closely.");
    add_act("smile softly");
    add_chat("How may I help you?");
    add_act("emote looks in a small mirror and "+
      "applies some rose pomade to her lips.");
    add_act("emote takes up a flower and inhales its fragrance.");

}

void
show_hook(object ob)
{
    object tp = this_player();

    command("whisper " + tp->query_real_name() +
      " Most interesting! Let me take a closer look.");
    set_alarm(5.0, 0.0, &show_react(tp, ob));
    return;
}

int
show_react(object tp, object ob)
{
    if (ob->query_herb_name())
    {
	command("whisper "+ tp->query_real_name() + " "+
	  "Do you know what this is? It is "+ 
	  LANG_ADDART(ob->query_herb_name()) +
	  ". It has some interesting properties.");
	command("emote closes her eyes and concentrates for a moment.");
	if (ob->query_id_long())
	    set_alarm(5.0, 0.0, &herb_properties(ob->query_id_long(), tp));
	return 1;
    }
    command("say Well, I am not in that kind of business, you know. "+
      "I can only tell you something more if you show me an herb.");
    command("emote looks a little insulted.");
    command("peer "+ tp->query_real_name());
    return 1;
}

int
herb_properties(string properties, object tp)
{
    command("whisper "+ tp->query_real_name() + " "+
      "This herb has the following unique properties:\n"+
      "\n" + properties);
    command("smile helpfully");
    return 1;
}



string
respond_task_ask()
{
    object tp = this_player();

    if (tp->query_prop(GETTING_I_THE_WAX))
    {
	command("whisper "+ lower_case(tp->query_name()) + " "+
	  "Did you find the honeycomb yet? If so, please give it "+
	  "to me.");
	command("smile");
	return "";
    }

    tp->add_prop(GETTING_I_THE_WAX, 1);
    command("whisper " + lower_case(tp->query_name()) + " "+
      "I need a special ingredient for my rose pomade.");
    command("whisper "+ lower_case(tp->query_name()) + " "+
      "If you can bring this ingredient to me, I may be able to "+
      "give you a nice reward.");
    command("wink");
    command("smile sweetly");
    return "";
}


string
respond_wax_ask()
{
    object tp = this_player();

    command("hmm");
    command("whisper "+ lower_case(tp->query_name()) + " "+
      "I need a piece of honeycomb made by clover honey bees. "+
      "The sweet wax makes the lips very smooth and soft, "+
      "following my special formula.");
    command("emote pouts prettily with her luscious "+
      "rose-tinted lips."); 
    command("whisper " + lower_case(tp->query_name()) + " "+
      "If you have it already, please give it to me.");
    return "";
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if ((interactive(from)) && ob->query_the_honeycomb())
    {
	set_alarm(2.0, -1.0, &thank_player(ob,from));
	return;
    }

    if ((interactive(from)) && !ob->query_the_honeycomb())
    {
	set_alarm(2.0, -1.0, &return_stuff(ob, from));
	return;
    }


}

int
thank_player(object ob, object player)
{
    command("thank "+ lower_case(player->query_name()));
    if (player->query_prop(GETTING_I_THE_WAX))
	set_alarm(2.0, -1.0, &reward_honeycomb(ob, player));
    return 1;
}

int
reward_honeycomb(object honeycomb, object player)
{
    player->remove_prop(GETTING_I_THE_WAX);


    // don't reward a second time
    // allow player to do over tho, in case they didn't get spell

    if (!QH_QUERY_QUEST_COMPLETED(player, "honeycomb_quest"))
    {
	player->catch_msg("You feel more experienced!\n");
	QH_QUEST_COMPLETED(player, "honeycomb_quest");
    }


    honeycomb->remove_object();
    command("whisper "+ lower_case(player->query_name()) + " "+
      "I know some special Words, I think it is a spell! "+
      "I don't know what it is used for though, but I heard the "+
      "witch shout this at a goat once!");
    command("emote checks around for eavesdroppers.");
    player->remove_prop(GETTING_I_THE_WAX);
    set_alarm(5.0, -1.0, &give_spell(player));
    return 1;
}

int
give_spell(object tp)
{
    command("emote looks very mysterious.");
    command("whisper " + lower_case(tp->query_name()) + " "+
      "The words are these:\n\n"+
      GOAT_SPELL + "\n\n");
    command("whisper "+ lower_case(tp->query_name()) + " " +
      "Perhaps these words will be useful to you.");
    command("say Good luck!");
    command("smile");
    command("wave");
    return 1;
}

int
return_stuff(object ob, object player)
{
    command("hmm");
    command("say No thank you.");
    command("say If you wish assistance with an herb, "+
      "you can show it to me.");
    command("emote returns " + LANG_THESHORT(ob) + ".");

    if (ob->move(player))
    {
	ob->move(environment(TO));
	return 1;
    }
    return 1;
}

