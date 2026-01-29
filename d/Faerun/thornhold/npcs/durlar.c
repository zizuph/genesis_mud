/*
* Durlar Stoneshaft of Thornhold, by Twire June, 2016
*/
inherit "std/monster";

#include <const.h>   // for G_MALE
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

//   Protoypes
int return_sigh(string who);
int return_smile(string who);
void return_introduce();
void greet(object ob);

object loupe;

public void
init_size()
{
	set_size_descs("short", "fat");
}

void
create_monster()
{
   if (!IS_CLONE) return;
   set_name("durlar");
   add_name(({"stoneshaft", "provisoner", "Durlar", "shopkeeper"}));
   set_living_name("durlar");
   set_title("Stoneshaft the Chief Provisoner of Thornhold");
   set_race_name("dwarf"); 
   set_gender(G_MALE);
   set_adj(({"stout","broad-nosed"}));
   set_long("@@my_long");
   default_config_npc(30);
   set_base_stat(SS_CON, 100);
   set_base_stat(SS_STR, 100);
   set_base_stat(SS_DEX, 50);
   
   set_skill(SS_UNARM_COMBAT,20);
   set_skill(SS_DEFENCE,80);
   set_pick_up(75);
   
   set_aggressive(0);
   set_attack_chance(0);
   
   add_prop(CONT_I_WEIGHT, 80000);   /* 80 Kg  */
   add_prop(CONT_I_VOLUME, 80000);   /* 80 Ltr */
   
   set_act_time(20);
   set_chat_time(30);
   add_act("grumble");
   add_act("emote pushes a stepstool to a nearby stack to take inventory.");
   add_act("emote tucks an item into one of the pockets of his apron.");
   add_act("emote opens up a ledger book and reviews its contents.");
   add_act("emote steps into the storehouse briefly to retrieve an item.");
   add_chat("The next caravan should be arriving soon.");
   add_chat("A lot of adventurers have been stopping by lately.");
   add_chat("I'll need to order some more lamp-oil from Waterdeep soon.");
   add_chat("Ye best be well-supplied if ye plan to travel High Road.");
   add_chat("I carry basic provisons only. Fer tack, visit the farrier.");
   set_alarm(0.0, 0.0, init_size);
   
   add_ask( ({ "tin", "spice", "snuff", "box" }), 
   VBFC_ME("explain_tin"));
   
   add_ask( ({ "durana", "Durana" }), 
   VBFC_ME("explain_durana"));
}


init_living() 
{
   ::init_living();
   if (interactive(this_player()))
   {
      set_alarm(1.0,0.0,&greet(this_player()));
   }
}

explain_tin()
{
    command("say Oh that spice tin belonged to Saerlyn? Shoot! I had " +
            "no idea. I found it the other day, and thought it would make " + 
            "a nice gift for Lady Durana.");
}

explain_durana()
{
    command("say Durana is the Matron of Thornhold. You can usually find " +
            "her overseeing fortress affairs from the battlements.");
}
void
greet(object ob)
{
   if (!CAN_SEE(this_object(), ob) || ob->query_wiz_level()) return;
   command("say Hi there " + ob->query_nonmet_name() + ". In need of " +
      "any supplies?");
}

string
my_long() 
{
   if (notmet_me(this_player())) this_player()->add_introduced("durlar");
   return "Durlar Stoneshaft is the chief provisoner of " +
      "Thornhold. He is stout and broad-faced, and wears a thick " +
      "leather apron with pockets. He is currently holding a ledger " +
      "his left hand.\n";
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
return_sigh(string who)
{
   if (!who) return 0;
   who = lower_case(who);
   if (random(3)) return 0;
   command("say Are ye gonna buy something or nay?");
   return 1;
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
      case "sigh":
      set_alarm(3.0,0.0,&return_sigh(name));
      break;
      case "smile":
      set_alarm(3.0,0.0,&return_smile(name));
      break;
   }
}
