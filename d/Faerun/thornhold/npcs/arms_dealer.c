/*
* Willem Stromgbrow Traveling Arms Dealer by Twire June, 2016
*/
inherit "std/monster";
inherit "/d/Faerun/thornhold/std/shop";

#include <const.h>   // for G_MALE
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "../defs.h"

#define  STORE_ROOM          ROOM_DIR + "arm_stock"

//   Protoypes
int return_smile(string who);
void return_introduce();
void greet(object ob);

void
create_monster() 
{
    if (!IS_CLONE) return;
    set_name("willem");
    add_name(({"strongbow", "arms", "Willem", "merchant"}));
    set_living_name("willem");
    set_title("Strongbrow of Baldur's Gate, the Arms Dealer");
    set_race_name("human"); 
    set_gender(G_MALE);
    set_adj(({"muscular", "bald"}));
    set_long("@@my_long");
    default_config_npc(30);
    set_base_stat(SS_CON, 110);
    set_base_stat(SS_STR, 110);
    set_base_stat(SS_DEX, 80);
    set_base_stat(SS_INT, 80);
    set_base_stat(SS_WIS, 90);
   
    set_skill(SS_UNARM_COMBAT,20);
    set_skill(SS_DEFENCE,80);
    set_pick_up(75);
   
    set_aggressive(0);
    set_attack_chance(0);
   
    add_prop(CONT_I_WEIGHT, 80000);   /* 80 Kg  */
    add_prop(CONT_I_VOLUME, 80000);   /* 80 Ltr */
   
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
   
    set_act_time(35);
    set_chat_time(35);
    add_act("nod stoic");
    add_act("emote polishes one of the swords on display.");
    add_act("emote pushes a heavy crate full of weapons to one side.");
    add_act("emote packs some recent weapon purchases into a crate.");
    add_act("emote shows a steel battleaxe to a passing dwarven guard.");
    add_chat("I wouldn't travel High Road unarmed if I were you.");
    add_chat("Arms! Arms for sale!");
    add_chat("I will buy any weapons you are no longer using.");
    add_chat("The dwarves of Clan Stoneshaft are among my best customers.");
    add_chat("For high quality custom weapons, I advise a trip to Baldur's " +
             "Gate, but it's much more practical to get to Waterdeep. There " +
             "are fine smiths there, as well.");
            
    add_ask( ({ "problem", "quest", "job", "task", "item" }),
                VBFC_ME("explain_problem"));
 
    add_ask( ({ "truesteel", "ingot"}),
                VBFC_ME("explain_ingot"));

    setup_shop();
    set_store_room(STORE_ROOM);
    set_shop_name("the travelling arms dealer");
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
    if (!weapon_filter(x))
    {
        if (armour_filter(x))
        {
            return "The shopkeeper says: You'll have to take that "
              + x->short() + " to the Armourer. I only trade in"
              + " weapons.\n";
        }
        else
        {
            return "The shopkeeper says: You'll have to take that " 
              + x->short() + " to the General Store through the"
              + " door to the south. I only trade in weapons.\n";
        }
    }
    return 0;
}


public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!living(from))
        return;

    if (obj->id("_thq_ingot"))
    {
        if(!QUEST_MASTER->check_ingot(from))
        {
            command("say By Gond's grace, you found a cold iron ingot!");
            command("emote tosses the ingot into his stock."); 
            command("say You say you found this in Bodric's workshop?");
            command("emote nods."); 
            command("say I'll be sure he's compensated then. Thanks again!");
            QUEST_MASTER->award_ingot(from);
        }
        else
        {
            command("say Another ingot! Thanks!");
        }
        obj->remove_object();
    }
    else
    {
        command("say Hmm Not sure what I'd do with that.");
        obj->move(from);
    }
}

explain_problem()
{
   if (interactive(this_player()))
   {
        if (QUEST_MASTER->check_ingot(this_player()))
        {
            command("say Thanks for your help earlier. May Gond bless "+
                    "all your endeavours.");
        }
        else
        {
            command("emote raises an eyebrow appraisingly.");
            command("say Well, I'm not sure if you can help me, but I know a " +
                    "swordsmith in Amphail who will only trade a blade I need " +
                    "in exchange for a pure cold iron ingot.");
            command("say If I'm not able to deliver, it's going to disrupt " +
                    "my transactions for three or four tendays at least!");
        }
    }
}

explain_ingot()
{
    command("say I know it's a longshot, but if you happen to find a " +
            "cold iron ingot, I'll pay seven gold dragons for it!");
}

void
greet(object ob)
{
   if (!CAN_SEE(this_object(), ob) || ob->query_wiz_level()) return;
   command("say Can I interest you in a weapon, "
   + ob->query_nonmet_name() + "?");
}

my_long()
{
   if (notmet_me(this_player())) this_player()->add_introduced("willem");
   return "This arms dealer is bald and strong. \n" +
          "He wears a oil-stained leather apron. \n";
}

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
