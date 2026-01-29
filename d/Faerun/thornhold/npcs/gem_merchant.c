/*
* Galena Glimmergem, Traveling Gem Merchant by Twire June, 2016
*/
inherit "std/monster";
inherit "/d/Faerun/thornhold/std/shop";


#include <const.h>   // for G_MALE
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "../defs.h"

#define  STORE_ROOM          ROOM_DIR + "gems_stock"

//   Protoypes
int return_smile(string who);
void return_introduce();
void greet(object ob);

void
create_monster() {
   if (!IS_CLONE) return;
   set_name("galena");
   add_name(({"glimmergem", "gem", "Galena", "merchant"}));
   set_living_name("saerlyn");
   set_title("Glimmergem of Blingdenstone, Stonetrader");
   set_race_name("svirfneblin"); 
   set_gender(G_FEMALE);
   set_adj(({"grey-skinned","indigo-eyed"}));
   set_long("@@my_long");
   default_config_npc(30);
   set_base_stat(SS_CON, 90);
   set_base_stat(SS_STR, 90);
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
   
   remove_prop(LIVE_M_NO_ACCEPT_GIVE);

   set_act_time(35);
   set_chat_time(45);
   add_act("nod stoic");
   add_act("emote sorts a variety of gems by color on a nearby display.");
   add_act("emote holds a ruby up to the light to examine it.");
   add_act("emote polishes a variety of agates.");
   add_act("emote secures some diamonds in a sturdy lock-box.");
   add_chat("My kin are working hard to restore Blingdenstone to its " +
            "former glory.");
   add_chat("Gems! Gems for sale!");
   add_chat("Secure your wealth in precious and semi-precious stones!");
   add_chat("If you find any gems on your travels, I'm your buyer.");
   add_chat("Some gems have powerful arcane and alchemical " +
            "properties.");
            
   add_ask( ({ "problem", "quest", "job", "task", "item", "missing" }),
   VBFC_ME("explain_problem"));
 
   add_ask( ({ "crosses", "noughts", "game", "bet"}),
   VBFC_ME("explain_game"));
   
   add_ask( ({ "brigid", "Brigid" }),
   VBFC_ME("explain_brigid"));
   
   add_ask( ({ "loupe" }),
   VBFC_ME("explain_loupe"));
   
    setup_shop();
    set_store_room(STORE_ROOM);
    set_shop_name("the travelling gem dealer");
    set_money_greed_sell(90);
    set_money_greed_buy(90);
    set_keeper(this_object());
}

init_living() 
{
   ::init_living();
   ::init_shop();
   if (interactive(this_player()))
   {
      set_alarm(1.0,0.0,&greet(this_player()));
   }
}

public void
print_message(string str)
{
    keeper->command("say " + str);
}
int
do_buy(string args)
{
  if (check_keeper()) return ::do_buy(args);
  return 0;
}
int
do_value(string args)
{
  if (check_keeper()) return ::do_value(args);
  return 0;
}
int
do_sell(string args)
{
  if (check_keeper()) return ::do_sell(args);
  return 0;
}
mixed
shop_hook_filter_sell(object x)
{
    if (!x->query_gem())
    {
        return "The shopkeeper says: You'll have to take that "
          + x->short() + " to someone else. I only trade in"
          + " gems.\n";
    }
    return 0;
}

void
explain_problem()
{
   if (interactive(this_player()))
   {
       if (QUEST_MASTER->check_loupe(this_player()))
       {
            command("say Thank you again for your help. I've learned my "+
                    "lesson and won't be gambling again!");
       }
       else
       {
            command("say As it so happens, I am missing a very important item!");
            command("emote sighs in embarassment.");
            command("say I fear it's my own fault, though. I lost my jeweler's " +
                    "loupe in a bet on a game of noughts and crosses!");
       }
   }
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!living(from))
        return;

    if (obj->id("_thq_loupe"))
    {
        if(!QUEST_MASTER->check_loupe(from))
        {
            command("say My jeweler's loupe!");
            command("emote clasps the loupe tightly in her hands."); 
            command("say Blessings of Baravar upon you, my friend. You've no " +
                    "idea how essential this tool is to my profession.");
            command("say Please take this as a token of my gratitutde!");
            QUEST_MASTER->award_loupe(from);
        }
        else
        {
            command("say Another loupe! Thanks!");
        }
        obj->remove_object();
    }
    else
    {
        command("say Hmm Not sure what I'd do with that.");
        obj->move(from);
    }
}

explain_game()
{
    command("say Noughts and crosses is a simple game, but be careful " +
            "if you play against Brigid. She's surprisingly clever!");
}

explain_loupe()
{
    command("say My loupe is a lens that allows me to inspect and appraise " +
            "gems. I was foolish to gamble it away, but Brigid had a star " +
            "ruby up for ante, and my greed got the best of me.");
}

explain_brigid()
{
    command("say Brigid is the daughter of the alemistress. You can " +
            "find her in the Thornhold Alehouse playing noughts and " +
            "crosses almost any hour of the day or night.");
}


void
greet(object ob)
{
   if (!CAN_SEE(this_object(), ob) || ob->query_wiz_level()) return;
   command("say Care to sell or buy any gems, " + 
   ob->query_nonmet_name() + "?");
}

my_long() 
{
   if (notmet_me(this_player())) this_player()->add_introduced("galena");
   return "The gem merchant is a svirfneblin, or deep gnome as known in " +
      "realms beyond. She has grey skin and indigo eyes. She is wearing " +
      "overalls with many pockets stuffed with gemstones. \n" +
      "She is short and lean for a svirfneblin. \n";
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
