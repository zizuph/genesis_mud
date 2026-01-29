/*
* Saerlyn Whisperwind, Traveling Spice Merchant by Twire June, 2016
*/
#pragma strict_types
#pragma save_binary

#include "/d/Faerun/defs.h"
#include <const.h>   // for G_MALE
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "../defs.h"

inherit "/std/monster";
inherit "/d/Faerun/lib/herbalist.c";

// This path is where the herbs are saved
#define HERB_SAVE   "/d/Faerun/thornhold/data/herb_save"
#define LOW(s)      lower_case(s)

//   Protoypes
int return_smile(string who);
void return_introduce();
void greet(object ob);

void
create_monster() {
   if (!IS_CLONE) return;
   set_name("saerlyn");
   add_name(({"whisperkind", "spice", "Saerlyn", "merchant"}));
   set_living_name("saerlyn");
   set_title("Whisperwind of Harrowdale, Purveyor of Spices");
   set_race_name("elf"); 
   set_gender(G_FEMALE);
   set_adj(({"dusky","travel-worn"}));
   set_long("@@my_long");
   default_config_npc(30);
   set_base_stat(SS_CON, 100);
   set_base_stat(SS_STR, 100);
   set_base_stat(SS_DEX, 100);
   set_base_stat(SS_INT, 100);
   set_base_stat(SS_WIS, 100);
   
   set_skill(SS_UNARM_COMBAT,20);
   set_skill(SS_DEFENCE,80);
   set_pick_up(75);
   
   set_aggressive(0);
   set_attack_chance(0);
   
   add_prop(CONT_I_WEIGHT, 80000);   /* 80 Kg  */
   add_prop(CONT_I_VOLUME, 80000);   /* 80 Ltr */
   
   set_act_time(24);
   set_chat_time(24);
   add_act("stretch");
   add_act("emote taps a portion of fragrant brown powder into a tiny jar.");
   add_act("emote lays some freshly-picked herbs to dry on a nearby crate.");
   add_act("emote checks the contents of one of her herb pouches.");
   add_act("emote seals some white aromatic bulbs into a large herb jar.");
   add_chat("If you're a skilled herbalist, you can find herbs in Faerun " +
            "that can not found in any other realm.");
   add_chat("I trade in herbs found throughout the Sword Coast and beyond!");
   add_chat("Herbs have culintary, arcane, and medicinal uses.");
   add_chat("I can also assist in identifying herbs, if you wish.");
   add_chat("Always make sure you are well-supplied with a variety of " +
            "herbs before embarking on an adventure.");

   set_act_time(4);
   add_act("@@announce_selling");
   
   add_ask(({"herbs","herb"}), VBFC_ME("ask_herbs"));
   add_ask(({"herblore","lore"}), VBFC_ME("ask_lore"));
   add_ask( ({ "problem", "quest", "job", "task", "item", "missing" }), VBFC_ME("explain_problem"));
   add_ask( ({ "spice", "tin", "favourite" }), VBFC_ME("explain_spice"));
   add_ask( ({ "durlar", "Durlar" }), VBFC_ME("explain_durlar"));
   
   set_default_answer(VBFC_ME("default_answer"));
   
   set_max_herbs_kept(250);
   set_herbalist_id_herbs();
   configure_herbalist(HERB_SAVE);            
}

void
init_living()
{
   init_herbalist();
   ::init_living();
   if (interactive(this_player()))
   {
      set_alarm(1.0,0.0,&greet(this_player()));
   }
}

void
explain_problem()
{
   if (interactive(this_player()))
   {
       if (QUEST_MASTER->check_thimble(this_player()))
       {
            command("say Thanks for helping earlier with my problem. If you " +
                    "ever need any herbs identified, I'm happy to do so for " + 
                    "you, my friend!");
       }
       else
       {
            command("say Well, it's just a small thing, but I'm missing my " +
                    "very favourite spice tin!");
       }
   }
}

void
explain_spice()
{
    command("say It's such a pretty tin, really, of gleaming silver. " +
            "I last remember seeing it a tenday ago when I was trading " +
            "with Durlar for some provisions. Maybe he's seen it?");
}

void
explain_durlar()
{
    command("emote laughs in amusement.");
    command("say Durlar is the Thornhold provisioner! He's just to " +
            "the north. I'd check with him myself but I'm expecting " +
            "an important customer any minute.");
}

void
greet(object ob)
{
   if (!CAN_SEE(this_object(), ob) || ob->query_wiz_level()) return;
   command("say Can I interest you in some herbs, " + 
   ob->query_nonmet_name() + "?");
}

string
my_long() 
{
   if (notmet_me(this_player())) this_player()->add_introduced("saerlyn");
   return "The herbalist is a copper elf, or wood elf as known in  " +
      "realms beyond. She has dusky, copper skin, and has an abundance " +
      "of pouches attached to her belt and cloak. \n";
}

int
return_smile(string who)
{
	object ob;
   
	ob = present(who, environment());
   
	if (!ob) 
		return 0;
	   
	switch (random(4))
	{
	case 0: 
		command("smile"); 
		return 1;
	case 1: 
		command("smile " + who); 
		return 1;
	case 2: 
		if (notmet_me(ob)) 
		{
			command("introduce myself to " + who);
			return 1; 
		}
		break;
	default:
		break;
	}
	
    return 0;
}

int
add_introduced(string who)
{
   object ob;
   
   if (!who) return 0;
   who = lower_case(who);
   ob = present(who, environment());
   if (!ob) return 0;
   if (!CAN_SEE(this_object(), ob)) return 0;
   if (!notmet_me(ob)) return 0;
   if (!random(20)) return 0;
   set_alarm(itof(random(9)),0.0,&return_introduce());
   return 1;
}

void
enter_inv(object herb, object from)
{
    ::enter_inv(herb, from);
    if (!living(from))
        return;

    if (herb->id("_thq_spice_tin"))
    {
        if(!QUEST_MASTER->check_spice(from))
        {
            command("say My spice tin! Oh wonderful!");
            command("emote inspects the spice tin carefully"); 
            command("say Goodness, how did it get so dirty?");
            command("emote wipes the silver spice tin clean with her frock."); 
            command("say No matter. I'm just glad to have it back. Thank you!");
            QUEST_MASTER->award_spice(from);
        }
        else
        {
            command("say Hmm looks just like my spice tin.");
            command("emote inspects the spice tin carefully"); 
            command("say Couldn't hurt to have a spare");
        }
        herb->remove_object();
    }
    else
    {
        init_herbalist_identify(herb,from);
    }
    
}

void
return_introduce()
{
   command("introduce myself");
}

void
emote_hook(string emote,object actor,string averb = 0)
{
   string name = actor->query_real_name();
   
   switch(emote)
   {
      case "smile":
      set_alarm(3.0,0.0,&return_smile(name));
      break;
   }
}

string
ask_herbs()
{
    command("say Herbs are bits of plants that have useful properties. " +
    "If you are unskilled, don't test the herb on yourself, test it " +
    "on someone else until you're sure of its properties.");
    return "";
}

string
ask_lore()
{
    command("say Herbs are found everywhere, and in the most unlikely " +
    "places sometimes. They can cure illneses, improve you senses, and " +
    "even kill you when used by the unskilled. If you have an herb you " +
    "need identified, I can help you out.");
    return "";
}

string
default_answer()
{
    command("say I don't know what you are talking about!");
    return "";
}
