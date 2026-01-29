/**********************************************************************
 * - kei.c                                                          - *
 * - smith based on the bonesmith in tyr                            - *
 * - Created by Damaris@Genesis 02/2005                             - *
 **********************************************************************/

#pragma strict_types
inherit "/d/Genesis/lib/craftsman.c";
inherit "/std/monster.c";

#include <cmdparse.h>
#include <files.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "kei.h"

#define STATUS_IN_PROGRESS 0
#define STATUS_CONFIGURED  1
#define STATUS_COMPLETED   2

#define ORDER_STATUS           0
#define ORDER_OWNER            1
#define ORDER_ATTRS            2
#define ORDER_SELECTIONS       3
#define ORDER_FILE             4
#define ORDER_TIME             5
#define ORDER_COMPLETION_TIME  6
#define ORDER_COST             7
#define ORDER_HOLD             8
#define ORDER_TIMEOUT          9

#define DONATION_HANDS  0
#define DONATION_HIT    1
#define DONATION_PEN    2
#define DONATION_USED   3

#define DLY_EMOTE(t, s) set_alarm(t, 0.0, &command("emote " + s))
#define DLY_TELLR(t, s) set_alarm(t, 0.0, &tell_room(ENV(TP), s + "\n"))

/* Prototypes */
void        arm_me();
int         report_cost(string str);
int         report_kei_status();
int         check_donation(string who);
int         take_payment(object cust, int cost);
int         do_wax(string str);
int         do_sharpen(string str);
int         do_mend(string str);
static int  do_repair_cost(object item, object tp);
int         do_fix(object item, object tp, string verb);
varargs int do_remind(string str);
int         do_help(string topic);
int         calc_wax_value(object item);
int         calc_sharpen_value(object item);
int         calc_mend_value(object item);
void        fix_wax(object item);
void        fix_sharpen(object item);
void        fix_mend(object item);
void        return_object(object obj, object to);
void        reset_smith();
void        timeout_smith();
void        manufacture_obs_wep(string weapon);
void        manufacture_std_wep(string weapon, string material);
void        manufacture_armour(string type, string material);
void        destroy_magic_item(object item);
void        destroy_std_item(object item);
string      create_engraving(object who);
int         distort(int price);
mixed       neat_value(int *arr);
string      format_str_list(string *arr, string conjunction);



/* Global variables */
int Status = 0;   /* Status of Kei */
                  /* 0 - Not doing anything */
                  /* 1 - Taking an order */
                  /* 2 - Making an item for a customer */
                  /* 3 - Destroying an item */
                  
/* The alarm id of the active timeout_smith alarm */
int Timeout_alarm;

/* Current customer */
object Customer;

/* A list by player name, of what they donated */
mapping Donation_map = ([]);

public void
create_monster()
{
   craftsman_set_sold_item_names(({ "armour", "armor", "weapon" }));
   craftsman_set_max_total_orders(1);

   set_name("kei");
   set_living_name("kei");

   add_name(({"smith", "blacksmith", "weapon smith", "weapon maker",
              "master smith", "stone smith"}));

   set_race_name("human");

   set_adj(({"strong", "capable"}));

   set_title("the Master Smith of SaMorgan");

   set_long("This strong capable male human is the Master "+
     "Blacksmith of SaMorgan.\n"+
     "He has piercing black eyes.\n"+
     "His head is clean shaven.\n"+
     "He has smooth ebony skin.\n"+
     "His chest is bare.\n"+
     "He has a tattoo of a flaming dragon with claws that "+
     "appear to be embedded in his chest.\n"+
     "He has special slave markings along his back from ages past.\n"+
     "He has small beads of persperation along his dark brow.\n");

   default_config_npc(85);

   remove_prop(NPC_M_NO_ACCEPT_GIVE);
   remove_prop(LIVE_I_NEVERKNOWN);

   set_alignment(250);

   set_tell_active(1);

   config_default_trade();
   set_money_give_max(1000);
   arm_me();
   //set_act_time(4);
   //add_act("emote grabs a broom and starts to sweep the floor.");
}
void
arm_me()
{
    clone_object(SA_SMITH + "kei_apron")->move(TO);
    clone_object(SA_SMITH + "kei_pants")->move(TO);
    command("wear all");
}

public void
init_living()
{
   ::init_living();
   craftsman_init();
   add_action(do_help,     "help");
   add_action(do_remind,   "buy");
   add_action(do_remind,   "sell");
   add_action(do_remind,   "value");
   add_action(do_remind,   "list");
   add_action(report_cost, "cost");
   add_action(do_wax,      "wax");
   add_action(do_sharpen,  "sharpen");
   add_action(do_mend,     "mend");
   add_action(do_mend,     "fix");
}
/* -------------------------------------------------------------- */
/* This feels bad, I would rather use a hook for this.            */
/* But in that case people others could start ordering            */
/* while he was destroying an item. */
public int
craftsman_purchase(string str)
{
   if(report_kei_status())
   {
      say(QCTNAME(TP) + " starts to exchange words with " + QTNAME(TO) + ".\n");
      add_prop(NPC_M_NO_ACCEPT_GIVE, " is busy with a customer.\n");
      Status = 1;
      return ::craftsman_purchase(str);
   }
   else
      return 0;
}

public int
craftsman_purchase_syntax_failure_hook(string str)
{
    reset_smith();
    return ::craftsman_purchase_syntax_failure_hook(str);
}

public int
craftsman_purchase_exceeded_max_total_orders_hook(string str)
{
    reset_smith();
    return ::craftsman_purchase_exceeded_max_total_orders_hook(str);
}

public int
craftsman_purchase_exceeded_max_user_orders_hook(string str)
{
    reset_smith();
    return ::craftsman_purchase_exceeded_max_user_orders_hook(str);
}

public void
craftsman_config_attributes(int id, int pos)
{
   mixed *order = m_orders[id];
   say(QCTNAME(TP) + " exchanges some words with " + QTNAME(TO) + ".\n");
	if (pos < sizeof(order[ORDER_ATTRS]))
	{
	   string attr_nm = order[ORDER_ATTRS][pos][0];
	   mixed attrs = order[ORDER_ATTRS][pos][1];
	   mapping attr_map = order[ORDER_SELECTIONS];
      
	   if(attr_map["material"] == "obsidian" && craftsman_query_item_file(id) != TENT_OBS_WEP_FILE)
	   {
         craftsman_set_item_file(id, TENT_OBS_WEP_FILE);
         craftsman_add_attribute(id, "finish", FINISH_TYPES);
         craftsman_add_attribute(id, "stone", OBS_TYPES);
	    }

	   if(attr_map["material"] == "black steel")
	   {
	     if(!check_donation(TP->query_name()))
		{
		  remove_prop(NPC_M_NO_ACCEPT_GIVE);
		  command("grumble");
		  DLY_EMOTE(1.0, "says: This is Athas my friend, "+
		    "if you want me to make you a metal weapon you "+
		    "will have to bring me something of value first.");
		  DLY_EMOTE(1.5, "says: And I do not mean just any "+
		    "old weapon you can find on the ground.");
		  craftsman_set_attribute("~q", id, pos);
		  return;
		}
	   }
	    
	    if ((attr_nm == "hands") && (attr_map["type"] == "knife"))
	    {
	        craftsman_set_attribute("one-handed", id, pos);
	        return;
	    }
	    if ((attr_nm == "hands") && (attr_map["type"] == "halberd"))
	    {
	        craftsman_set_attribute("two-handed", id, pos);
	        return;
	    }
	}
   ::craftsman_config_attributes(id, pos);
}
int
check_donation(string who)
{
   if(Donation_map[who])
   {
      int i = 0,
          temp = 0;
      for(i=0; i < sizeof(Donation_map[who]); i++)
         temp += Donation_map[who][i][DONATION_USED];
      if(temp < sizeof(Donation_map[who]))
         return 1;
      else
         return 0;
   }
   else
      return 0;
}
public void
craftsman_configure_item(object item, mapping attrs, int id)
{
    mixed *order = m_orders[id];
    object who = find_player(order[ORDER_OWNER]);
    string who_name = who->query_name();
    
    item->set_adj(attrs["material"]);
    item->set_name(attrs["type"]);

    if (attrs["_id"] == "weapon" && attrs["material"] == "obsidian")
    {
    item->config_weapon(attrs["type"], 
                        attrs["finish"],
                        attrs["stone"], 
                        attrs["hands"]);
                        
      item->set_engraving(create_engraving(who));
    }
    else if (attrs["_id"] == "weapon" && attrs["material"] == "black steel")
    {
	    int hit = Donation_map[who_name][0][DONATION_HIT],
	        pen = Donation_map[who_name][0][DONATION_PEN],
	        hands = Donation_map[who_name][0][DONATION_HANDS];


	    hit = ftoi(itof(hit) * 0.9);
	    pen = ftoi(itof(pen) * 0.9);
	    
	    if(hands == 1536 && attrs["hands"] == "one-handed")
	    {
         hit -= 5;
         pen -= 5;
	    }
	    else if (hands != 1536 && attrs["hands"] == "two-handed")
	    {
	      hit += 5;
         pen += 5;
	    }
	    item->config_weapon(attrs["type"], 
	                        attrs["material"], 
	                        attrs["hands"]);
	    if(attrs["type"] == "knife")
           {
	            hit -= 5;
               pen -= 5;
           }
	    item->set_hit(hit);
	    item->set_pen(pen);
	    item->set_engraving(create_engraving(who));
    }
    else if (attrs["_id"] == "weapon")
    {
    item->config_weapon(attrs["type"], 
                        attrs["material"], 
                        attrs["hands"]);
    item->set_engraving(create_engraving(who));
    item->set_engraving(create_engraving(who));
    }
    else if (attrs["_id"] == "armour")
    {
    item->config_armour(attrs["type"], 
                        attrs["material"], 
                        attrs["construction"]);
    item->set_engraving(create_engraving(who));
    }
    craftsman_set_item_cost(id, item->query_value());
    craftsman_notify_cost_hook(id);
}

public void
craftsman_abort_hook()
{
    say("It looks like the conversation has ended.\n");
    write("Your order has been canceled.\n");
    reset_smith();
}

/* This is bad, I would rather use a hook, but the hook */
/* comes too late, after the time has been established. */
public int
craftsman_completed_config(int id)
{
    mixed *order = m_orders[id];
    mapping attr_map = order[ORDER_SELECTIONS];
    
    if (attr_map["_id"] == "weapon" && attr_map["material"] == "obsidian")
    {
      craftsman_set_time_to_complete(id, 85);
    }
    
    if (attr_map["_id"] == "weapon" && attr_map["material"] == "black steel")
    {
      craftsman_set_time_to_complete(id, 92);
    }
    
   ::craftsman_completed_config(id);
}

public void
craftsman_config_completed_hook(int id)
{
    mixed *order = m_orders[id];
    mapping attr_map = order[ORDER_SELECTIONS];
   Status = 2;
   say(QCTNAME(TP) + " finishes " + HIS_HER(TP) + " conversation "+
     "with " + QTNAME(TO) + ".\n");
    if (attr_map["_id"] == "weapon" && attr_map["material"] == "obsidian")
      manufacture_obs_wep(attr_map["type"]);
    else if (attr_map["_id"] == "weapon")
      manufacture_std_wep(attr_map["type"], attr_map["material"]);
    else if (attr_map["_id"] == "armour")
      manufacture_armour(attr_map["type"], attr_map["material"]);
   ::craftsman_config_completed_hook(id);
}

public void
craftsman_completed_order_hook(int id, string owner)
{
   int i = 0;
   object who;

   if ((who = find_player(owner)) && craftsman_query_object_present(who))
   {
       who->catch_tell("Your order has been completed.\n");
       who->catch_tell("Use 'check order' to collect your items.\n");
   }
   owner = CAP(owner);
   for( i = (sizeof(Donation_map[owner]) - 1); i > -1 ; i-- )
   {
      if(Donation_map[owner][i][DONATION_USED] == 0)
      {
         Donation_map[owner][i][DONATION_USED] = 1;
         break;
      }
   }
   reset_smith();
}

public void
craftsman_configure_order(int id, string str)
{
   if (str == "armour" || str == "armor")
   {
      craftsman_set_item_file(id, TENT_ARM_FILE);
      craftsman_add_selection(id, "_id", "armour");
      craftsman_add_attribute(id, "type", m_indices(ARM_MAP));
      craftsman_add_attribute(id, "material", m_indices(MAT_MAP));
      craftsman_add_attribute(id, "construction", m_indices(CON_MAP));
      craftsman_set_time_to_complete(id, 65);
   }
   else if (str == "weapon")
   {
      craftsman_set_item_file(id, TENT_STD_WEP_FILE);
      craftsman_add_selection(id, "_id", "weapon");
      craftsman_add_attribute(id, "type", m_indices(WEP_NAME));
      craftsman_add_attribute(id, "material", WEP_MATERIAL);
      craftsman_add_attribute(id, "hands", WEP_HANDS);
      craftsman_set_time_to_complete(id, 65);
   }
}
public void
craftsman_cancel_order_hook(int id)
{
   mixed *current_alarms = get_all_alarms();
   int i;
   for(i=0; i < sizeof(current_alarms); i++)
   {
      remove_alarm(current_alarms[i][0]);
   }
   DLY_EMOTE(1.0, "stops working, lays down his tools and returns what " +
                  "he was working on to the racks.");
   DLY_EMOTE(1.5, "glances at you, he looks rather annoyed.");
   reset_smith();
   ::craftsman_cancel_order_hook(id);
}

public void
craftsman_check_receive_order_hook(object ob, int id)
{
   mixed *order = m_orders[id];
   object who = find_player(order[ORDER_OWNER]);
   string who_name = who->query_name();
   string log_txt = "";

   if (order[ORDER_SELECTIONS]["_id"] == "armour")
   {
      log_txt = sprintf("%-10s", TP->query_name()) + ob->query_short() + " ";
      log_txt += ob->query_ac() + " " + ctime(time()) + "\n";
      log_file("kei_creations", log_txt, -1);
   }
   else
   {
      log_txt = sprintf("%-10s", TP->query_name()) + ob->query_short() + " ";
      log_txt += ob->query_hit() + " " + ob->query_pen() + " ";
      log_txt += (ob->query_hands() == 1536 ? "2H " : "1H ") + ctime(time()) + "\n";
      log_file("kei_creations", log_txt, -1);
   }
   
   if(sizeof(Donation_map[who_name]) > 1)
   {
      int temp = (sizeof(Donation_map[who_name]) - 2);
      Donation_map[who_name] = Donation_map[who_name][0..temp];
   }
   else
   Donation_map = m_delete(Donation_map, who_name);

   ::craftsman_check_receive_order_hook(ob, id);
}

public void
craftsman_timeout_hook(int id)
{
   reset_smith();
   write("You have wasted enough of my time.\n");
}

/* -------------------------------------------------------------- */

int
take_payment(object cust, int cost)
{
int   *money_arr;
string coin_pay_text,
       coin_get_text;
     /* Try to take the money */
   if (sizeof(money_arr = pay(cost, cust, "", 0, 0, "")) == 1)
   {
      return 0;
   }
   else
   {
      coin_pay_text = text(exclude_array(money_arr, sizeof(MONEY_TYPES), 
                   sizeof(MONEY_TYPES)*2-1));
      coin_get_text = text(exclude_array(money_arr, 0, sizeof(MONEY_TYPES)-1));
      cust->catch_msg("You pay "+coin_pay_text+" to "+
        "" + QTNAME(this_object()) + ".\n");
      if (coin_get_text)
         write("You get " + coin_get_text + " in return.\n");
      return 1;
   }
}

int
report_kei_status()
{
   switch(Status)
   {
      case 0:
         return 1;
         break;
      case 1:
         notify_fail("Kei is taking an order now, please wait.\n");
         return 0;
         break;
      case 2:
         notify_fail("Kei is making an item for a customer now, " +
                     "please wait.\n");
         return 0;
         break;
      case 3:
         notify_fail("As soon as finishes what he is working on, he will " +
                     "deal with you.\n");
         return 0;
         break;
      default:
         notify_fail("Kei does not seem to know what he is doing. " +
                     "Please make a bug report.\n");
         return 0;
    }
}

int report_cost(string str)
{
   object *item;

   if(report_kei_status())
   {
      if (!strlen(str))
      {
         command("say You want to know the repair cost for which item?\n");
         return 1;
      }
      
      if (!parse_command(str, all_inventory(TP),
         "[for] [to] /  [wax] [sharpen] [waxing] [sharpening] / [of] [a] [the] %i", item))
      {
         command("say You want to know the cost to mend what?");
         return 1;
      }
      
      item = NORMAL_ACCESS(item, 0 , 0);
      
      if (sizeof(item) > 1)
      {
         command("say Please be more specific! Which item do you mean?");
         return 1;
      }
      
      if (sizeof(item) == 0)
      {
         command("say You do not have such a weapon.");
         return 1;
      }
      
      do_repair_cost(item[0], TP);
      return 1;
   }
   return 0;
}

int
do_wax(string str)
{
   object *item;

   if(report_kei_status())
   {
      if (!strlen(str))
      {
         do_help("wax");
         return 1;
      }
      
      if (!parse_command(str, all_inventory(TP), "[my] [the] %i", item))
      {
         command("say Wax what?");
         return 1;
      }
      
      item = NORMAL_ACCESS(item, 0 , 0);
      
      if (sizeof(item) > 1)
      {
         command("say Please be more specific! Which item do you mean?");
         return 1;
      }
      
      if (sizeof(item) == 0)
      {
         command("say You do not have such a weapon.");
         return 1;
      }
      
      do_fix(item[0], TP, "wax");
      return 1;
   }
   return 0;
}

int
do_sharpen(string str)
{
   object *item;

   if(report_kei_status())
   {
      if (!strlen(str))
      {
         do_help("sharpen");
         return 1;
      }
      
      if (!parse_command(str, all_inventory(TP), "[my] [the] %i", item))
      {
         command("say Sharpen what?");
         return 1;
      }
      
      item = NORMAL_ACCESS(item, 0 , 0);
      
      if (sizeof(item) > 1)
      {
         command("say Please be more specific! Which item do you mean?");
         return 1;
      }
      
      if (sizeof(item) == 0)
      {
         command("say You do not have such a weapon.");
         return 1;
      }
      
      do_fix(item[0], TP, "sharpen");
      return 1;
   }
   return 0;
}

int
do_mend(string str)
{
   object *item;

   if(report_kei_status())
   {
      if (!strlen(str))
      {
         do_help("mend");
         return 1;
      }
      
      if (!parse_command(str, all_inventory(TP), "[my] [the] %i", item))
      {
         command("say Mend what?");
         return 1;
      }
      
      item = NORMAL_ACCESS(item, 0 , 0);
      
      if (sizeof(item) > 1)
      {
         command("say Please be more specific! Which item do you mean?");
         return 1;
      }
      
      if (sizeof(item) == 0)
      {
         command("say You do not have such an item.");
         return 1;
      }
      
      do_fix(item[0], TP, "mend");
      return 1;
   }
   return 0;
}

/*
 * Function name: catch_question
 * Description: This function is called in each living being someone asks a
 * question to.
 * Arguments: question - The question as put
 */
public void
catch_question(string question)
{
   if(report_kei_status())
   {
      switch(question)
      {
         case "iron":
         case "black steel":
         case "enchantment":
         case "information":
         case "vessel":
         case "about steel":
         case "about black steel":
            command("say The great King Kalak has granted me special favor "+
              "to manufacture weapons made of black steel from his mines.");
            command("say And for this great kindness he demands not just "+
              "simple coins but something of much greater value.");
            command("say Kalak demands the powers of enchantment themselves "+
              "and has given me the task to collect them for him in exchange "+
              "for my services in this shop.");
            command("say So, if it is an steel weapon you want, you must "+
              "first return to me a vessel of this enchantment.");
            break;
         default:
            do_help("kei");
      }
   }
}

/*
 *
 * Function name:    do_repair_cost
 * Description:      Calls the cost calculation code to sharpen or
 *                   wax a weapon or mend an armour item and then
 *                   reports results to the player. It will also
 *                   report if the item in question is not an armour
 *                   or a weapon.
 * Arguments:        item - the item in question
 *                   tp - the player requesting the estimate
 * Returns:          1 - the item was a weapon or armour and the cost 
 *                       was successfully estimated.
 *                   0 - The item was not a weapon or armour so no estimate
 *                       was generated.
 *
 */
static int
do_repair_cost(object item, object tp)
{
int v1, // these 3 vars hold the actual cost
    v2, // to perfrom various actions
    v3; // and are used for some simple tests

string   it,        // a proper way to refer to the item
         what = ""; // the actions we price out

   if (function_exists("create_object", item) == WEAPON_OBJECT)
      /* if the item is a weapon we calc the cost of sharpening and 
      waxing here. */
   {
      if (item->query_prop(OBJ_I_BROKEN))
      {
         command("say But that " + item->short() + " is broken!");
         command("say Why don't you buy a new one?");
         return 1;
      }

      v1 = calc_sharpen_value(item);
      v2 = calc_wax_value(item);

      it = "that " + item->short();

      if (v1 > -1)
      {
         command("say Sharpening "+it+" would cost about "
         + distort(v1) + " coppers.");
         what = "sharpen";
      }
      if (v2 > -1)
      {
         command("say Waxing "+it+" would cost about "
         + distort(v2) + " coppers.");
         if (strlen(what))
            what += " or ";
         what += "wax";
      }


      if (v1 == -1 && v2 == -1)
         command("say "+capitalize(it)+" needs neither sharpening nor waxing!");
      else
         command("say If you want me to "+what+" the item, use '" +
                 what + " <item>'.");

      return 1;
   }
   else if (function_exists("create_object", item) == ARMOUR_OBJECT)
            /* otherwise we check to see if its armour and if so calc */
            /*the cost to mend*/
   {
      v3 = calc_mend_value(item);
      it = "that " + item->short();

      if (v3 > -1)
      {
         command("say Mending "+it+" would cost about "
         + distort(v3) + " coppers.");
         command("say If you want me to mend the item, use 'mend <item>'."); 
      }
      else
      {
         command("say "+capitalize(it)+" does not need mending!");
      }
      return 1;
   }

   /* must not bet a weapon or an armour */
   command("say That is not a weapon or a piece of armour!");
   return 1;
}

/*
 *
 * Function name:    do_fix
 * Description:      Here is where the repair gets performed.
 *                   This will handle all the payment issues and
 *                   reports results to the player. It calls several
 *                   smaller functions to actually effect the repair
 *                   to the item. It also handles the checks to make
 *                   sure the item is capable of being repaired.
 * Arguments:        item - the item in question
 *                   tp - the player requesting the repair
 *                   verb - what type of repair has been requested.
 *                          used several times to determine which
 *                          support function to call.
 * Returns:          1 - the item was a weapon or armour and may or may
 *                       not have been repaired.
 *                   0 - The item was not a weapon or armour or was
 *                       not able to be repaired.
 *
 */
int
do_fix(object item, object tp, string verb)
{
int int_str,
    value,
   *money_arr;
   
string item_name,
       coin_pay_text,
       coin_get_text;

   if (function_exists("create_object", item) != WEAPON_OBJECT &&
       function_exists("create_object", item) != ARMOUR_OBJECT)
   {
         command("say That "+item->short()+" is nothing I can work on!");
         return 0;
   }

   /* Talk about tricky code! ;-)
    * Here is an example where the verb variable is used to call the 
    * proper support function.
    */

   value = call_other(this_object(), "calc_"+verb+"_value", item);

   if (value == -1)
   {
      command("say I cannot " + verb + " that any further.");
      return 0;
   }

   /* Try to take the money */
   if (take_payment(tp, value))
   {
      value = call_other(this_object(), "fix_"+verb, item);
      tp->catch_msg("You give the "+item->short()+" to "+
        ""+QTNAME(this_object())+".\n");
      say(QCTNAME(tp) + " gives " + tp->query_possessive() + " "+
        "" + item->short() +
            " to " + QTNAME(this_object()) + ".\n");
      command("emote "+ verb + ((verb == "wax") ? "es" : "s") + " the "
              + item->short() + ".");
      command("emote returns the " + item->short() + " back.");
   return 1;
   }
   else
   {
      command("emote chuckles.");
      command("say I think that "+item->short()+" is a bit too expensive " +
              "for you.\n");
      return 1;
   }
}

/*
 *
 * Function name: calc_wax_value
 * Description:   Calculates the actual price for waxing a weapon.
 * Arguments:     item - the item in question
 * Returns:       -1 the item could not be repaired
 *              > -1 the cost to repair the item
 *
 */
int
calc_wax_value(object item)
{
   if (item->query_prop(OBJ_I_BROKEN))
      return -1;

   if (!F_LEGAL_WEAPON_REPAIR_CORR(item->query_repair_corr()+1,
         item->query_corroded()))
      return -1;
         
   return (item->query_prop(OBJ_I_VALUE) * WAX_COST) / 100;
}


/*
 *
 * Function name: calc_sharpen_value
 * Description:   Calculates the actual price for sharpening a weapon.
 * Arguments:     item - the item in question
 * Returns:       -1 the item could not be repaired
 *              > -1 the cost to repair the item
 *
 */
int
calc_sharpen_value(object item)
{
   if (item->query_prop(OBJ_I_BROKEN))
   return -1;

   if (!F_LEGAL_WEAPON_REPAIR_DULL(item->query_repair_dull()+1,
       item->query_dull()))
      return -1;
      
return (item->query_prop(OBJ_I_VALUE) * SHARPEN_COST) / 100;
}

/*
 *
 * Function name: calc_mend_value
 * Description:   Calculates the actual price for mending an armour.
 * Arguments:     item - the item in question
 * Returns:       -1 the item could not be repaired
 *              > -1 the cost to repair the item
 *
 */
int
calc_mend_value(object item)
{
   if (item->query_prop(OBJ_I_BROKEN))
      return -1;

   if (!F_LEGAL_ARMOUR_REPAIR(item->query_repair()+1,
         item->query_condition()))
      return -1;
      
   return (item->query_prop(OBJ_I_VALUE) * MEND_COST) / 100;
}

/*
 * Function name: do_remind
 * Description:   Just used to remind the player we are not a store
 * Returns:       1
 * Arguments:     str - command line args
 */
varargs int
do_remind(string str)
{
   command("say What do I look like, a common merchant?");
   command("say Try the shop next door.");
   return 1;
}
/* -------------------------------------------------------------- */

void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);

   if (!objectp(ob) || !objectp(from) || !living(from))
      return;

   if (function_exists("create_object", ob) != WEAPON_OBJECT)
   {
      set_alarm(0.5, 0.0, &return_object(ob, from));
      return;
   } 
   
   Status = 3;
   if (ob->query_prop(OBJ_I_IS_MAGIC_WEAPON) != 0 && ob->query_prop(OBJ_I_BROKEN) == 0)
   {
      string doner = from->query_name();
      if(m_sizeof(Donation_map))
      {
         if(Donation_map[doner])
         {
            Donation_map[doner] += ({ ({ob->query_hands(), ob->query_hit(), ob->query_pen(), 0 }) });
         }
         else
         {
            Donation_map[doner] = ({ ({ob->query_hands(), ob->query_hit(), ob->query_pen(), 0 }) });
         }
      }
      else
      {
         Donation_map[doner] = ({ ({ob->query_hands(), ob->query_hit(), ob->query_pen(), 0 }) });
      }

      add_prop(NPC_M_NO_ACCEPT_GIVE, " is busy with other things.\n");
      DLY_EMOTE(1.0, "says: Ahh! Very good!");
      DLY_EMOTE(1.5, "says: I shall remember that you gave me the "+
        "materials I seek.");
      DLY_EMOTE(1.7, "says: In the mean time I will make sure this "+
        "goes where it can be of use.");
      set_alarm(2.0, 0.0, &destroy_magic_item(ob));
      return;
   }

   DLY_EMOTE(1.0, "mumbles: I hope you don't think this "+
     "" + ob->query_name() + " will be good enough to get me to make "+
     "you a metal weapon.");
   set_alarm(2.0, 0.0, &destroy_std_item(ob));
}
/* -------------------------------------------------------------- */

/*
 *
 * Function name: return_object
 * Description:   Keep any money and give the rest back :)
 * Arguments:     ob - the item in question
 *                to - person to return item to.
 * Returns:       nothing
 *
 */
void
return_object(object obj, object to)
{
   if (obj->id("coin"))
   {
      command("say Why, thank you!");
      command("say I always appreciate a little tip!");
      command("snicker");
      return;
   }

   if (!living(to)) 
   {
      command("say I wonder where this "+obj->query_name()+
      " came from. I'll drop it here.");
   }
   else 
   {
      command("say Here is your "+obj->short()+
               ", "+to->query_nonmet_name()+"!"); 
   }

   command("give "+obj->query_name()+" to " + to->query_real_name());

   if (environment(obj) == this_object()) 
   {
      command("drop "+obj->query_name());
   }
}

public void
add_introduced(string name)
{
   object who;

   if (!objectp(who = find_player(name)))
      return;

   if (who->query_met(query_name()))
      return;
      
   set_alarm(2.0 + 5.0 * rnd(), 0.0, &command("present me to " + name));
}

public void
emote_hook(string emote, object actor, string adverb = 0)
{
   switch (emote)
   {
      case "bow":
         add_introduced(this_player()->query_real_name());
         break;
      default:
         break;
   }
}

int
do_help(string topic)
{
   string help_str = "";
   
   switch(topic)
   {
      case "kei":
      case "dwarf":
      case "smith":
      case "blacksmith":
         help_str = "\n" +
         "     'help kei'   -  This message.\n"+
         "     'help sharpening'  -  How to get a weapon sharpened.\n"+
         "     'help waxing'      -  How to get a weapon waxed.\n"+
         "     'help mending'     -  How to get armour mended.\n"+
         "     'help ordering'    -  How to order a weapon or armour.\n" +
         "     'help weapons'     -  Information about the weapons you can "+
           "order.\n"+
         "     'help obsidian'    -  Information about ordering obsidian "+
           "weapons.\n"+
         "     'help armours'     -  Information about what armours you "+
           "can order.\n"+
         "     'help recycle'     -  Information about unwanted and "+
           "broken items.\n"+
         "     'help pay'         -  Information about how to pay for "+
           "orders.\n\n";
         break;
      case "sharpen":
      case "sharpening":
         help_str = "\n" +
         "  Use the command 'sharpen <weapon>'\n"+
         "  Examples:\n"+
         "     'sharpen axe'\n"+
         "     'sharpen second sword'\n"+
         "     'sharpen obsidian halberd'\n"+
         "  Payment will automatically be taken if you can afford it.\n"+
         "  Use 'cost <item>' to see the cost of sharpening and mending.\n\n";
         break;
      case "wax":
      case "waxing":
         help_str = "\n" +
         "  Use the command 'wax <weapon>'\n"+
         "  Examples:\n" +
         "     'wax axe'\n"+
         "     'wax second sword'\n"+
         "     'wax obsidian halberd'\n"+
         "  Payment will automatically be taken if you can afford it.\n"+
         "  Use 'cost <item>' to see the cost of waxing and mending.\n\n";
         break;
      case "mend":
      case "mending":
         help_str = "\n"+
         "  Use the command 'mend <armour>'\n"+
         "  Examples:\n"+
         "     'mend helmet'\n"+
         "     'mend ancient breastplate'\n"+
         "     'mend third armour'\n"+
         "  Payment will automatically be taken if you can afford it.\n"+
         "  Use 'cost <item>' to see the cost of sharpening and mending.\n\n";
         break;
      case "order":
      case "ordering":
         help_str = "\n"+
         "  You can order weapons or armours.\n"+
         "  To begin the ordering process type 'order weapon' or "+
           "'order armour'\n"+
         "  To pick up a completed weapon use 'check order'\n\n"+
         "  You will be asked to enter your choices for how the weapon or\n"+
         "  armour is to be made.\n\n"+
         "  Your choices for armour types are:\n"+
         "     " + format_str_list(m_indices(ARM_MAP), "and") + "\n\n"+
         "  Your choices for armour materials are:\n"+
         "     " + format_str_list(m_indices(MAT_MAP), "and") + "\n\n"+
         "  Your choices for armour construction are:\n"+
         "     " + format_str_list(m_indices(CON_MAP), "and") + "\n\n"+
         "  Your choices for weapon types are:\n"+
         "     " + format_str_list(m_indices(WEP_NAME), "and") + "\n\n"+
         "  Your choices for weapon materials are:\n"+
         "     " + format_str_list(WEP_MATERIAL, "and") + "\n\n"+
         "  Obsidian comes in these varieties:\n"+
         "     " + format_str_list(OBS_TYPES, "and") + "\n\n"+
         "  Obsidian weapons can be finished in these ways:\n"+
         "     " + format_str_list(FINISH_TYPES, "or") + "\n\n"+
         "  Your choice of hands is 'one-handed' or 'two-handed'.\n\n"+
         "  After you place an order it will be repeated back to you "+
           "with a cost\n"+
           "and the smith will start work on the item.\n"+
         "  You can type 'cancel order' at anytime before you pick up "+
           "the item.\n"+
         "  You can type 'help weapons', 'help armours', and "+
           "'help obsidian' for\n"+
         "  more details about your options.\n\n";
         break;
      case "weapon":
      case "weapons":
      case "axe":
      case "battleaxe":
      case "sword":
      case "swords":
      case "halberd":
      case "polearm":
      case "polearms":
      case "club":
      case "clubs":
      case "knife":
      case "dagger":
         help_str = "\n"+
         "  You can order weapons or armours.\n"+
         "  To begin the ordering process type 'order weapon' or "+
           "'order armour'\n"+
         "  You will then be asked to enter your choices for how "+
           "the weapon or\n"+
         "  armour is to be made.\n"+
         "  Your choices for weapon types are:\n"+
         "     " + format_str_list(m_indices(WEP_NAME), "and") + "\n\n"+
         "  Your choices for weapon materials are:\n"+
         "     " + format_str_list(WEP_MATERIAL, "and") + "\n\n"      +
         "  Obsidian stone types can be seen in the display case on "+
           "the wall!\n\n"+
         "  Obsidian weapons can be finished is these ways:\n"+
         "     " + format_str_list(FINISH_TYPES, "or") + "\n\n"+
         "  If you want an obsidian weapon use 'help obsidian' to "+
           "find out\n"+
         "  more options and special requirements for obsidian weapons.\n\n"+
         "  Your choice of hands is always 'one-handed' or 'two-handed'.\n\n";
         break;
      case "obsidian":
         help_str = "\n" +
         "  Obsidian is a dark and mysterious stone used in Athas for\n"+
         "  thousands of years in place of metal. Over that time the \n"+
         "  smiths of Athas have learned ways to make obsidian weapons \n"+
         "  many times more dangerous than weapons made of metal.\n\n"+
         "  Obsidian comes in many varieties, each with its own unique \n"+
         "  properties.\n\n"+
         "  Examine the display case on the wall to see which \n"+
         "  varieties are used in this blacksmith shop.\n\n"+
         "  Obsidian can also be finished in several ways, although the \n"+
         "  finish is only decorative and has no effect on effectiveness.\n"+
         "  Your choice of finishes are:\n"+
         "  " + format_str_list(FINISH_TYPES, "or") + ".\n\n";
         break;
      case "armour":
      case "armours":
         help_str = "\n" +
         "  You choices of armour types are:\n"+
         "     " + format_str_list(m_indices(ARM_MAP), "and") + ".\n\n"+
         "  Armours can be made of different materials, each with their own \n"+
         "  qualities. Your choices of materials are:\n"+
         "     " + format_str_list(m_indices(MAT_MAP), "and") + ".\n\n"+
         "  Each piece of armour can be constructed in several ways, each \n"+
         "  method will affect the protection afforded by the armour.\n"+
         "  Your choices of construction are:\n"+
         "     " + format_str_list(m_indices(CON_MAP), "and") + ".\n\n"+
         "  Use 'order armour' to place an order.\n";
         break;
      case "recycle":
      case "destroy":
      case "reuse":
         help_str = "\n"+
         "  All materials are generally scarce in Athas. As such, this "+
           "smith will\n"+
         "  collect any broken or unwanted items and make sure they "+
           "are properly\n"+
         "  destroyed and reused. Just give him an item you no longer "+
           "want.\n"+
         "  Be warned: Any item you give me will be destroyed and you "+
           "will not\n"+
         "  be able to get it back!\n\n";
         break;
      case "pay":
      case "payment":
         help_str = "\n" +
         "  After ordering an item, you will be given a short description "+
           "of what\n"+
         "  you have ordered along with the price. When you order is "+
           "complete \n"+
         "  just type 'check order' and you will pay for the item and "+
           "have it \n"+
         "  given to you.\n\n"                    +
         "  You do not have the option of paying with certain coin "+
           "types, you\n"+
         "  always pay with your smallest coins first!\n\n"  +
         "  Paying for sharpening, waxing or mending is done immediately "+
           "if you\n"+
         "  can afford the price.\n\n"+
         "  Use 'cost <item>' to see the cost of sharpening and mending.\n\n";

   }
   if(help_str == "")
      return 0;
   write(help_str);
   return 1;
}

/*
 *
 * Function name: fix_wax
 * Description:   Actually performs the repair to the item.
 * Arguments:     item - the item in question
 * Returns:       nothing
 *
 */
void
fix_wax(object item)
{
   string log_txt = "";
   log_txt = sprintf("%-10s", TP->query_name()) + " waxed a "+
     "" + item->query_name() + " " +
             ctime(time()) + "\n";
   log_file("kei_repairs", log_txt, -1);
   item->set_repair_corr(item->query_repair_corr() + 1);
}

/*
 *
 * Function name: fix_sharpen
 * Description:   Actually performs the repair to the item.
 * Arguments:     item - the item in question
 * Returns:       nothing
 *
 */
void
fix_sharpen(object item)
{
   string log_txt = "";
   log_txt = sprintf("%-10s", TP->query_name()) + " sharpened a "+
     "" + item->query_name() + " " +
             ctime(time()) + "\n";
   log_file("kei_repairs", log_txt, -1);
   item->set_repair_dull(item->query_repair_dull() + 1);
}

/*
 *
 * Function name: fix_mend
 * Description: Actually performs the repair to the item.
 * Arguments: item - the item in question
 * Returns: nothing
 *
 */
void
fix_mend(object item)
{
   string log_txt = "";
   log_txt = sprintf("%-10s", TP->query_name()) + " mended a "+
     "" + item->query_name() + " " +
             ctime(time()) + "\n";
   log_file("kei_repairs", log_txt, -1);
   item->set_repair(item->query_repair() + 1);
}

/*
 *
 * Function name: reset_smith
 * Description:   Resets Kei status so he can do more work
 * Arguments:     none
 * Returns:       nothing
 *
 */
void
reset_smith()
{
   Status = 0;
   remove_prop(NPC_M_NO_ACCEPT_GIVE);
}

void
timeout_smith()
{
   if(Status == 1)
   {
      craftsman_abort_hook();
      command("say You have wasted enough of my time, if you want "+
        "something you'll have to order it again.");
   }
   reset_smith();
}

void
manufacture_armour(string type, string material)
{
   switch(type)
   {
      case "chestplate":
      case "helm":
      case "greaves":
      case "bracers":
         say(QCTNAME(TO) + " stares at " + QTNAME(TP) + " carefully judging "+
           "" + HIS_HER(TO) + " size.\n");
         DLY_EMOTE(25.0, "turns around and selects some pieces of "+
           "" + material + " from the racks in the rear of the shop, "+
           "laying them on the bench.");
         DLY_EMOTE(30.0, "reaches down and grabs some think, wide jozhal "+
           "hide strips from under the bench and tosses them on the table.");
         DLY_EMOTE(35.0, "gives you one more quick glance and arranges "+
           "the pieces of " + material + " face down on the table with "+
           "the first sides of each part to be joined spaced fairly close "+
           "together.");
         DLY_EMOTE(40.0, "measures and cuts the straps for the armour, "+
           "turning the parts and spacing them as he goes.");
         DLY_EMOTE(45.0, "drills some pilot holes he will use to attach "+
           "the strapping.");
         DLY_EMOTE(50.0, "grabs a hammer and some steel pins and starts "+
           "to fasten the parts together. Using no less than five pins for "+
           "each attachment, this is going to be a well made piece of armour.");
         DLY_TELLR(55.0, "Carefully mushrooming the head of each pin, "+
           "he starts to finish up the " + type + ".");
         DLY_EMOTE(60.0, "lays down his tools, looks over the " + type + ", "+
           "and checks the movement and trim.");
      break;
      case "gauntlets":
      case "boots":
         say(QCTNAME(TO) + " leans over the counter and glances at " + 
                           QTNAME(TP) + "'s " +
                           (type == "gauntlets" ? "hands" : "feet") + ".\n");
         DLY_EMOTE(20.0, "takes a pair of leather " + type + " from the "+
           "racks in the rear of the shop and sets them on the bench.");
         DLY_EMOTE(25.0, "also grabs a couple of handfuls of "+
           "" + material + " pieces from the racks.");
         DLY_EMOTE(30.0, "sits down and starts the process of attaching "+
           "the pieces of " + material + " to the leather "+ type + ", "+
           "stopping to shape each one so they fit perfectly together.");
         DLY_TELLR(40.0, "As he finishes up the first of the pair, he bends "+
           "it back and fourth, checking the freedom of movement.");
         DLY_TELLR(45.0, "After trimming a few of the pieces in place, he is "+
           "satisfied, sets it aside and begins work on the second of the "+
           "pair.");
         DLY_EMOTE(55.0, "gives the last piece a final inspection and "+
           "finishes up the " + type + ".");
         
      break;
      default:
         DLY_EMOTE(15.0, "starts to work on the item, it looks like it "+
           "will take a while.");
         DLY_EMOTE(25.0, "continues to work on the item, it looks like "+
           "it will still take a while.");
         DLY_EMOTE(35.0, "continues to work on the item, it looks like "+
           "he will be done shortly.");
         DLY_EMOTE(45.0, "continues to work on the item, it looks like "+
           "he will be done soon.");
         DLY_EMOTE(55.0, "continues to work on the item, it looks like "+
           "he is very close to being done.");
         DLY_EMOTE(60.0, "continues to work on the item, it looks like "+
           "he is finished.");
   }
}

void
manufacture_obs_wep(string weapon)
{
   DLY_EMOTE(5.0, "turns around and takes a block of obsidian rom a stack "+
     "in the corner.");
   DLY_EMOTE(10.0, "sets the block on the edge of his work bench and picks "+
     "up a large hammer.");
   switch(weapon)
   {
   case "axe":
      DLY_EMOTE(15.0, "hits the block with a perfect stroke and fractures "+
        "the face of the block.");
      DLY_EMOTE(20.0, "flips the block of obsidian over and raises his "+
        "hammer to strike the block again.");
      DLY_EMOTE(25.0, "hits the block perfectly a second time.");
      DLY_EMOTE(30.0, "grins as he admires his handy work.");
      DLY_EMOTE(35.0, "takes a short, wide piece of mekillot gut from a "+
        "pail on floor and lays it in the channel chipped into the back "+
        "of the axe head.");   
      DLY_EMOTE(40.0, "takes an oak and bone handle from a rack.");  
      DLY_EMOTE(45.0, "lays the axe handle into the groove in the back of "+
        "axe head.");
      DLY_EMOTE(50.0, "pulls a long thin strip of mekillot gut from the pail.");
      DLY_EMOTE(55.0, "begins wrapping the axe head and the handle with "+
        "the gut strip, pulling it tighter and tighter as he works his "+
        "way up and down the back of the axe head.");
      DLY_EMOTE(60.0, "holds the head of the axe over the coals of his "+
        "forge fire, drying the strips of mekillot gut.");
      DLY_EMOTE(65.0, "spins the axe with blinding speed in one hand, "+
        "checking it for balance, a smile spreads across his face.");
      DLY_EMOTE(70.0, "clamps the axe in a wooden vise, pulls a carving "+
        "tool from his apron and starts to engrave the handle.");
      DLY_EMOTE(75.0, "takes the axe from the vise and brushes off the "+
        "handle.");
      break;
   case "sword":
      DLY_EMOTE(15.0, "lays the long, narrow block of obsidian on the bench.");
      DLY_EMOTE(18.0, "begins knapping flakes of obsidian from the block, "+
        "working his way up to the end of the block.");
      DLY_EMOTE(25.0, "flips the block over and begins chipping stone away "+
        "working back down the blade toward the hilt.");
      DLY_EMOTE(30.0, "gets to the hilt of the weapon and you can see he "+
        "has formed a savage edge on the front of the blade.");
      DLY_EMOTE(35.0, "turns the block around and starts to chip away at "+
        "back side of the blade.");
      DLY_EMOTE(40.0, "quickly gets to the tip of the blade, shards of "+
        "glass regularly hitting a growing pile of debris on the floor.");
      DLY_EMOTE(45.0, "flips the blade and starts working back down to "+
        "the hilt of the sword.");
      DLY_EMOTE(50.0, "finishes the blade of the sword and starts to form "+
        "the hilt, taking expert swings and rounding the end of the block.");
      DLY_EMOTE(55.0, "puts down the hammer and gets a long strip of "+
        "mekillot hide from under the bench.");
      DLY_EMOTE(60.0, "starts wrapping the rough handle of the sword with "+
        "the leather, working up and down the rough stone he covers "  +
                      "the handle giving it a strong and sure grip.");
      DLY_EMOTE(65.0, "clamps the sword in a wooden vise and pulls an "+
        "engraving tool from his apron and starts to engrave the handle "+
        "of the sword.");
      DLY_EMOTE(70.0, "finishes the engraving work and while sliding the "+
        "tool back into his apron he takes the sword from the vise and "+
        "blows the obsidian dust from the handle.");
      break;
   case "halberd":
      DLY_EMOTE(17.0, "studies the block carefully, determining the best "+
        "side to make the front of the blade.");
      DLY_EMOTE(25.0, "finally starts chipping away at the obsidian, "+
        "working  his way up the blade, knapping shards of obsidian off "+
        "as he goes.");
      DLY_EMOTE(30.0, "flips the block over and begins to chip away at "+
        "the other side of the blade.");
      DLY_EMOTE(35.0, "finishes forming the halberd's blade and begins "+
        "to narrow the obsidian at the base so it can be attached to "+
        "the handle.");
      DLY_EMOTE(40.0, "strikes the stone with sure and skilled strokes, "+
        "creating a long, flat tongue of obsidian that will be fitted "+
        "into the haft of the weapon.");
      DLY_EMOTE(45.0, "sets down his hammer and turns to get long, thick "+
        "bone handle from the pile leaning against the obsidian rack.");
      DLY_EMOTE(50.0, "glances at the weapon head he just created and "+
        "picks up a bone cutting saw.");
      DLY_EMOTE(55.0, "saws a deep notch into the top of the weapons "+
        "haft and picks up the obsidian blade from the table.");
      DLY_EMOTE(60.0, "forces the blade into the notch at the top of "+
        "the handle with some effort.");
      DLY_EMOTE(65.0, "takes a long, wide strip of mekillot gut from "+
        "a pail and the floor and starts wrapping the top of handle with "+
        "it, binding the head to the haft.");
      DLY_EMOTE(70.0, "takes a strip of hide from under the bench and "+
        "starts to wrap it around the main part of the weapon's handle, "+
        "pulling it tight as he works his way along the haft.");
      DLY_EMOTE(75.0, "finally picks up a carving tool from the bench "+
        "and engraves the handle of the weapon.");
      break;
   case "club":
      DLY_EMOTE(15.0, "reaches down and grabs a tool from under the "+
        "bench that you do not recognize, it has the look of a chisel, but "+
        "with a curved, U shaped blade.");
      DLY_EMOTE(20.0, "grabs the long block of obsidian and looks it "+
        "over carefully, finally putting the larger, somewhat rounded end "+
        "on the table and resting the other on his shoulder.");
      DLY_EMOTE(25.0, "lays his chisel-like tool on the obsidian and using "+
        "the hammer starts to chip a channel down toward the end of the "+
        "block.");
      DLY_EMOTE(30.0, "works down the block, starting back up in the "+
        "middle after a full pass down the stone, each time widening "+
        "and deepening a channel in the block.");
      DLY_EMOTE(35.0, "rotates the stone a quarter turn and starts to dig "+
        "another channel in the obsidian.");
      DLY_EMOTE(40.0, "finishes making a wide channel after a few passes, "+
        "gives the block another quarter turn, and starts in on the next "+
        "side.");
      DLY_EMOTE(45.0, "is by now working quickly and gives the block "+
        "another turn to carve the last channel.");
      DLY_EMOTE(50.0, "completes the last channel and you realize that he "+
        "has just given this club four very sharp and jagged edges.");
      DLY_EMOTE(55.0, "lays down his chisel, takes the stone off his "+
        "shoulder and starts to strike the very end of the block, knocking "+
        "off the rough corners and rounding out the head of the club a "+
        "little.");
      DLY_EMOTE(60.0, "spins the block around on his bench and looks over "+
        "the untouched end of the block.");
      DLY_EMOTE(65.0, "starts furiously chipping away at the obsidian and "+
        "in no time gives the club a surprisingly well tapered and not "+
        "too jagged handle.");
      DLY_EMOTE(70.0, "grabs a long strip of mekillot hide and starts to "+
        "wrap the handle, pulling the leather tighter as he works his way "+
        "back and forth on the handle to cover the sharp edges of the "+
        "obsidian.");
      DLY_EMOTE(75.0, "finally picks up a carving tool from the bench and "+
        "engraves the handle of the weapon.");
      break;
   case "knife":
      DLY_EMOTE(15.0, "picks up the piece of obsidian from the bench and "+
        "holding it in one hand, braces it against his waist.");
      DLY_EMOTE(22.0, "smirks a little as he puts down the large hammer "+
        "and grabs a smaller one from the bench.");
      DLY_EMOTE(29.0, "starts knapping the obsidian, chipping off small "+
        "shards and begins to form the front edge of the knife.");
      DLY_EMOTE(36.0, "works carefully, flipping the stone and twisting "+
        "his hand around to work both sides of the knife.");
      DLY_EMOTE(43.0, "finishes the front edge of the blade and begins "+
        "to work on the back edge of knife.");
      DLY_EMOTE(50.0, "keeps knapping more and more stone, making it "+
        "smaller and forming the final blade of the knife.");
      DLY_EMOTE(57.0, "finishes up the blade and begins to tapper the "+
        "handle.");
      DLY_EMOTE(64.0, "grabs a long strip of mekillot hide and starts to "+
        "wrap the handle, pulling the leather tighter as he works his way "+
        "up and down to cover the sharp edges of the obsidian.");
      DLY_EMOTE(70.0, "finally picks up a carving tool from the bench "+
        "and engraves the handle of the weapon.");
      break;
   default:
      DLY_EMOTE(15.0, "starts to work on the weapon, it looks like it "+
        "will take a while.");
      DLY_EMOTE(25.0, "continues to work on the weapon, it looks like "+
        "it will take a while.");
      DLY_EMOTE(35.0, "continues to work on the weapon, it looks like "+
        "it will take a while.");
      DLY_EMOTE(45.0, "continues to work on the weapon, it looks like "+
        "he will be done in a while.");
      DLY_EMOTE(55.0, "continues to work on the weapon, it looks like "+
        "he will be done soon.");
      DLY_EMOTE(65.0, "continues to work on the weapon, it looks like "+
        "he is very close to being done.");
      DLY_EMOTE(70.0, "continues to work on the weapon, it looks like "+
        "he is finished.");
   }
}

void
manufacture_std_wep(string weapon, string material)
{
   switch(material)
   {
      string item = material + " " + weapon;
      case "black steel":
   DLY_TELLR(5.0, "A massive male half-giant steps out of the shadows.");

   DLY_TELLR(10.0, "The half-giant grabs two iron handles sticking out "+
     "of the floor in the rear of the shop and with a groan, lifts a "+
     "huge stone block to reveal the door to a vault.");

   DLY_EMOTE(15.0, "disappears down a set of carved stone steps and "+
     "returns with something.");

   switch(weapon)
   {
      case "axe":
      DLY_TELLR(16.5, "It is a thin and moderately size axe head, with a "+
        "blade face about the size of a half-giant's hand. At the back of "+
        "the blade the metal has been formed into a channel for a handle "+
        "to be attached.");
      break;
      case "halberd":
      DLY_TELLR(16.5, "It looks like an axe head, but with a longer, "+
        "narrower blade, the ends of which curve backward. At the back "+
        "of the blade the metal has been formed into a channel for a "+
        "handle to be attached.");
      break;
      case "club":
      DLY_TELLR(16.5, "It is a short and narrow club, not much bigger "+
        "at the head than the handle. The handle is formed from the same "+
        "piece of metal, pounded a little less round than the shaft and head.");
      break;
      case "knife":
      DLY_TELLR(16.5, "It is a rather long knife, with the tip curved "+
        "up slightly at the end. The base of the knife ends with a "+
        "squared off tang that will form the handle.");
      break;
      case "sword":
      DLY_TELLR(16.5, "It is a moderate length sword blade, thin with "+
        "a cutting edge on each side and very little taper to the point. "+
        "The base of the blade ends with a squared off tang that will "+
        "form the handle.");
      break;
   }

   DLY_TELLR(18.0, "The half-giant returns the block of stone and "+
     "disappears into the rear of the shop.");

   if(weapon == "club")
   {
   DLY_EMOTE(20.0, "walks over to a grinding wheel and sits down.");
   DLY_EMOTE(25.0, "places his feet on the pedals that drive the wheel "+
     "and starts to spin the wheel.");
   DLY_EMOTE(30.0, "runs the head of the club back and fourth on the "+
     "wheel, turning it constantly to perfectly round the head.");
   DLY_EMOTE(35.0, "changes his grip on the club and moves down to work "+
     "on the short area of taper between the head and grip.");
   DLY_EMOTE(40.0, "finishes his work at the wheel and stands up.");
   DLY_EMOTE(45.0, "picks up a large finishing stone, well worn in the "+
     "middle from years of use.");
   DLY_TELLR(50.0, "Laying the club on the bench he starts to run the "+
     "stone up and down the length of the weapon.");
   DLY_TELLR(55.0, "After a short time the metal is smoothed to a sinister "+
     "looking mat finish.");
   DLY_EMOTE(60.0, "grabs a thick cloth and wipes down the weapon.");
   }
   else
   {
   DLY_EMOTE(20.0, "places the " + weapon + " in the hot coals of the "+
     "forge and pumps the bellows to heat the fire.");
   DLY_EMOTE(25.0, "picks up a pair of tongs.");
   DLY_EMOTE(30.0, "turns the " + weapon + " in the fire with the tongs, "+
     "heating it evenly and thoroughly.");
   DLY_TELLR(35.0, "Glowing deep red, Kei takes the " + weapon + " from "+
     "the coals and lays it on the anvil.");
   DLY_TELLR(40.0, "Picking up a large hammer, Kei starts to pound and "+
     "thin the blade.");
   DLY_TELLR(45.0, "With careful and precise strokes Kei starts "+
     "to give the final edge to the " + weapon + ".");
   DLY_TELLR(50.0, "Finishing up the blade, Kei lays down his "+
     "hammer and picks up a fine grain polishing stone.");
   DLY_EMOTE(55.0, "sits down at the work bench, braces the blade against "+
     "the table and starts to run the stone over the blade.");
   DLY_TELLR(60.0, "Working carefully and deliberately, Kei hones the "+
     "edge to a razor's sharpness.");
   }
   switch(weapon)
   {
      case "axe":
      DLY_EMOTE(64.0, "takes a solid wood handle from the rack in the back "+
        "of the shop and fits it into the rear of the axe head.");
      DLY_TELLR(68.0, "And then with a hammer, he drives two steel pins "+
        "through both the metal and the handle.");
      DLY_TELLR(72.0, "Finally, he wraps the head and the handle with "+
        "mekillot gut, which will shrink as it dries and permanently bond "+
        "the head to the handle.");
      
      break;
      case "halberd":
      DLY_EMOTE(64.0, "takes a solid wood handle from the rack in the back "+
        "of the shop and fits it into the rear of the blade.");
      DLY_TELLR(68.0, "And then with a hammer, he drives two steel pins "+
        "through both the metal and the handle.");
      DLY_TELLR(72.0, "Finally, he wraps the head and the handle with "+
        "mekillot gut, which will shrink as it dries and permanently bond "+
        "the head to the handle.");
      break;
      case "club":
      DLY_EMOTE(64.0, "pulls a long, wide strip of mekillot hide from "+
        "under the bench and wets it in a pail.");
      DLY_EMOTE(68.0, "tightly wraps the handle with the leathery hide.");
      DLY_TELLR(72.0, "Holds the handle over the coals for a moment, to "+
        "dry and harden the leather grip.");
      break;
      case "knife":
      DLY_EMOTE(64.0, "takes two small pieces of wood from under the bench.");
      DLY_EMOTE(68.0, "fits the small blocks on either side of the tang and "+
        "secures them with two steel pins.");
      DLY_EMOTE(72.0, "steps over to the wheel and quickly grinds the pins "+
        "flush with the wooden handle.");
      break;
      case "sword":
      DLY_EMOTE(64.0, "takes two small pieces of wood from under the bench, "+
        "places them on either side of the tang and secures them with two "+
        "steel pins.");
      DLY_EMOTE(68.0, "takes a long, thin strip of mekillot hide from "+
        "under the bench and dampens it in a pail.");
      DLY_EMOTE(70.0, "wraps the handle, tapering the leather at the top and "+
        "bottom, forming a sure, comfortable grip.");
      
      break;
   }   
   DLY_EMOTE(75.0, "locks the " + weapon + " into a vise mounted on the "+
     "bench, pulling an engraving tool from his apron.");
   DLY_EMOTE(80.0, "starts to carve something into the handle.");
   DLY_EMOTE(85.0, "finishes the engraving, takes the " + weapon + " from "+
     "the vise and brushes off the handle.");
      break;
      default:
   DLY_EMOTE(5.0, "turns around and grabs a roughly finished "+
     "" + material + " " + weapon + " from a rack.");
   DLY_EMOTE(15.0, "sits down at a grinding wheel and begins giving "+
     "the " + weapon + " a finished shape.");
   if(weapon != "club")
   {
      DLY_EMOTE(25.0, "bends close to the wheel and starts to work on the "+
        "blade's final edge.");
      DLY_EMOTE(35.0, "slowly works the blade back and forth along the wheel "+
        "honing the edge.");
   }
   else
   {
      DLY_EMOTE(25.0, "turns the club constantly on the wheel, rounding "+
        "and shaping the head.");
      DLY_EMOTE(35.0, "leans hard into the grinding wheel as he tapers "+
        "to form a handle for the club.");
   }
      DLY_EMOTE(45.0, "stands up and locks the " + weapon + " into a vise "+
        "mounted on the bench, pulling an engraving tool from his apron.");
      DLY_EMOTE(50.0, "starts to carve something into the handle.");
      DLY_EMOTE(55.0, "finishes the engraving and takes the " + weapon + " "+
        "from the vise and brushes off the handle.");
   }
}

void
destroy_magic_item(object item)
{
   string thing = item->short(),
   log_txt = sprintf("%-10s", TP->query_name()) + thing + " ";
   log_txt += item->query_hit() + " " + item->query_pen() + " ";
   log_txt += (item->query_hands() == 1536 ? "2H " : "1H ") + ctime(time()) + "\n";
   log_file("kei_donations", log_txt, -1);
   
   if (item->remove_object())
   {
      DLY_EMOTE(3.0, "reaches into his apron and pulls out a small stone orb.");
      DLY_EMOTE(6.0, "grasps the " + thing + " in one hand and the small "+
        "orb in the other.");
      DLY_EMOTE(9.0, "closes his eyes and tightens his grip on both for "+
        "a moment, the orb pulses in his hand.");
      DLY_EMOTE(12.0, "opens his eyes, turns and tosses the " + thing + " on "+
        "a pile of scrap material and slides the orb back in his apron.");
      set_alarm(15.0, 0.0,
      &command("say Don't worry that " + thing + " will be properly "+
        "recycled, if not here, then somewhere else in the realms."));
      set_alarm(20.0, 0.0, "reset_smith");
   }
}

void
destroy_std_item(object item)
{
   string thing = item->short();
   int broken = item->query_prop(OBJ_I_BROKEN);
   if (item->remove_object())
   {
      DLY_EMOTE(3.0, "studies the " + thing + " very closely");
      if(broken)
      {
         set_alarm(9.0, 0.0,
         &command("say This thing is broken!"));
      }
      else
      {
         set_alarm(6.0, 0.0, &command("hmm"));
         set_alarm(9.0, 0.0,
         &command("say Nothing very special about this " + thing + "."));
      }
      set_alarm(12.0, 0.0,
      &command("say Either way, anything can be reused here in Athas."));
      DLY_EMOTE(14.0, "turns and tosses the " + thing + " on a pile of " +
               "old weapons and armours.");
      set_alarm(15.0, 0.0,
      &command("say Don't worry that " + thing + " will be properly " +
               "recycled, if not here, then somewhere else in the realms."));
   }
   set_alarm(17.0, 0.0, "reset_smith");
}

string
create_engraving(object who)
{
   string eng_text = "";
   
   eng_text += capitalize(who->query_real_name());
   
   if(who->query_guild_title_occ())
   {
      eng_text += ", " + who->query_guild_title_occ();
      eng_text += ".\n";
   }
   else
      eng_text += ".\n";
   return eng_text;
}

/*
 *
 * Function name: distort
 * Description: Checks trading and then changes the price
 * a slightly random about based on trading skill.
 * Arguments: price - the actual price of the repair
 * Returns: the new distorted price.
 *
 */
int
distort(int price)
{
   int trading;
   trading = this_player()->query_skill(SS_TRADING);
   if (trading > 100)
      trading = 100;
   if (trading < 0)
      trading = 0;

   return F_RANGE_RANDOM(price, 30, 2, trading);
}

mixed
neat_value(int *arr)
{
    int     i,
            num = sizeof(query_money_types());
    string  temp;

     if (sizeof(arr) < num)  /* invalid array */
         return;

    temp = "";
    for (i = num - 1; i >= 0; i--)
    {
        if (arr[i] > 0)
            temp += sprintf("%2d %2s ", arr[i], MONEY_TYPE[i]);
        else
            temp += "      ";
    }
    return temp;
}

string
format_str_list(string *arr, string conjunction)
{
   string tempstr = "";
   
   int arr_size = sizeof(arr),
       i = 0;
       
   if(arr_size == 1)
      return arr[0];
      
   for(i=0; i < arr_size - 1; i++)
   {
      tempstr += arr[i];
      tempstr += ", ";
   }
   tempstr += conjunction + " " + arr[arr_size-1];
   return tempstr;
}
