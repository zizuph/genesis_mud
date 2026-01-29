/*
 * This is the blacksmith Bubba in Gelan, he can repair armour and weapons, 
 * make polearms and make armours.
 *
 * Adapted and modified from code in Krynn and Gondor for Gelan 
 * by Maniac, 7.94
 * Given an overhaul by Maniac 26/6/95
 * Mending of broken weapons taken out by Maniac 30/6/95
 * Ask for forging of magical shield for polymorph quest added  Maniac 7/9/95
 * Typo removed, Maniac, 1.12.96
 * NPC_M_NO_ACCEPT_GIVE added as 1 Maniac
 * triggers taken out, 31/5/96, Maniac
 * Added acceptance of glass and sheet for Thalassian Staff Quest, removed
 *   the NPC_M_NO_ACCEPT_GIVE prop, but added the appropriate message to
 *   the enter_inv routine so players wouldn't get confused, Jaacar, 5/09/03
 */

#pragma save_binary

inherit "/std/monster";
inherit "/lib/trade";
inherit "/std/act/action";
#include "monster.h"
inherit STD_AIDED; 

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>
#include <const.h>
#include <money.h>
#include <cmdparse.h>
#include <language.h>

#include POLYMORPH_QUEST

#define LIVE_I_GOT_SHEET        "_live_i_got_sheet"
#define LIVE_I_WAS_GIVEN_SHEET  "_live_i_was_given_sheet"
#define LIVE_I_WAS_GIVEN_GLASS  "_live_i_was_given_glass"

#define ENV environment
#define LOW(x) lower_case(x)
#define CAP(x) capitalize(x)
#define HELP_DIR GELAN_TEXTS

#define AWAITING_CUSTOMER 0
#define POLEARM_MAKING 1
#define ARMOUR_MAKING 3

#define NOTHING 0
#define CONFIRMATION 1
#define CARRYING_OUT 2

int state; /* Current state of the blacksmith e.g. AWAITING_CUSTOMER */
int stage; /* Current stage of blacksmith in stage e.g. CARRYING_OUT */

string *known = ({ });

string customer; /* The current customer being worked for */
string working_on; /* Descr of the object being worked on */
int price; /* price on copper of the thing currently being worked on */
string *polearm_order = ({ });
string *armour_order = ({ });
object finished_item;

int confirmation_alarm;

string query_npc_address_name(object player, string t);
void finish_work();
void end_waiting();
void say_busy(object player);

#include "make_polearm.h"
#include "make_armour.h"

#include "make_polearm.c"
#include "make_armour.c"
#include "repairs.c"
#include "help.c"


mixed *fixing;
int testing;


/* Arm this npc */
void
get_armed() 
{
  object wep;
  seteuid(getuid(this_object()));
  wep = clone_object(GELAN_WEAPONS + "smithhammer");
  wep->move(this_object());
  command("wield hammer");
}


/* Address player according to whether player has introd before */
string
query_npc_address_name(object player, string t)
{
    string s;

    if (member_array(player->query_real_name(), known) > -1)
        s = player->query_name();
    else 
        s = t + player->query_nonmet_name(); 

    return s;
}


/* Clear customer details */
void
clear_customer()
{
    customer = "";
    armour_order = ({});
    polearm_order = ({});
    working_on = "";
    price = 0;
    state = AWAITING_CUSTOMER;
    stage = NOTHING;
}


/* End waiting for a confirmation/cancellation */
void
end_waiting()
{
    remove_alarm(confirmation_alarm);
    confirmation_alarm = 0;
    clear_customer();
    command("rolleyes");
    command("say Ok, next please.");
}


void
player_left(string player_name)
{
   if ((player_name == customer) && (stage == CONFIRMATION)) 
       end_waiting();
}


/* Blacksmith tells someone that he's busy right now */
void
say_busy(object player)
{
    if (!living(player))
        return;
    command("say I'm busy at the moment, " + 
            query_npc_address_name(player, "") +
            ", can't you tell that just by looking at me?");
}



/* Bubba's long description, describes what he's currently doing */
string
bubba_long()
{
  string str =
    "This is Bubba Hammerhead the master blacksmith of Gelan, a " +
    "middle aged but very strong man who learned some of his craft over "+
    "many years from the great smiths of Gondor and Krynn. He is currently ";  

    switch (state) {
        case AWAITING_CUSTOMER : str += "awaiting customers.";
                                 break;
        case POLEARM_MAKING : { 
             switch (stage) {
                 case CONFIRMATION : str += ("awaiting confirmation "+
                                         "for an order for " + 
                                         working_on + ".");
                                     break;
                 case CARRYING_OUT : str += ("working, seeing to an " +
                                            "order for " + working_on + 
                                            ".");
                                     break;
                 default : str += "looking extremely confused.";
                 break;
             }
             break;
        }
        case ARMOUR_MAKING : { 
             switch (stage) {
                 case CONFIRMATION : str += ("awaiting confirmation "+
                                         "for an order for " + 
                                         working_on + ".");
                                     break;
                 case CARRYING_OUT : str += ("working, seeing to an " +
                                            "order for " + working_on + 
                                            ".");
                                     break;
                 default : str += "looking extremely confused.";
                 break;
             }
             break;
        }
    }
    return (str + "\n");
}



/* Cancel an order */
int
do_cancel()
{
   object tp = this_player();

   tell_room(environment(this_object()), QCTNAME(tp) + " asks " +
        QTNAME(this_object()) + " to cancel the current order.\n", tp);
   tp->catch_msg("You ask " + QTNAME(this_object()) + " to cancel " +
                 "the current order.\n");

   if (state == AWAITING_CUSTOMER) {
       command("say There is currently nothing _too_ cancel, " +
               query_npc_address_name(tp, "") + "!!");
       return 1;
   }

   if (tp->query_real_name() == customer) {
       if (stage == CONFIRMATION) {
           end_waiting();
           return 1;
       }
       if (stage == CARRYING_OUT) {
           command("say Too late to cancel now, " +
                   query_npc_address_name(tp, "") + ", I don't " +
                   "give refunds!");
           command("snicker");
           return 1;
       }
       else {
           command("confused");
           end_waiting();
           return 1;
       }
   }

   command("say _You_ haven't got anything to cancel at the moment, " +
           query_npc_address_name(tp, "") + ".");
   return 1;
}




/* Pay for an order, thereby confirming it */
int
do_pay(string str)
{
    object tp, jewel, brew;
    int *money_arr;
    string pay_type, get_type, coin_pay_text, coin_get_text;


    tp = this_player();
    if (!str) 
        str = ""; 

    tell_room(environment(this_object()), QCTNAME(tp) + " offers to " +
            "pay " + QTNAME(this_object()) + " for an order.\n", tp);
    tp->catch_msg("You offer to pay " + QTNAME(this_object()) + " for " +
                "an order.\n");

    if (state == AWAITING_CUSTOMER) {
        command("say What order, " + query_npc_address_name(tp, "") +
               ", there aren't any orders being considered at the moment!");
        return 1;
    }

    if ((tp->query_real_name() == customer) && 
        (sizeof(armour_order)) &&
        (armour_order[2] == "magical")) {
        jewel = present(JEWEL_NAME, tp);
        brew = present(BREW_NAME, tp);
        if (!objectp(jewel) || !objectp(brew))  {
            command("say I'd like to help you, but the necessary items " +
                    "no longer seem to be in your possession!");
            return 1;
        }
    }

    if (tp->query_real_name() == customer) {
       if (stage == CONFIRMATION) {
           if (sscanf(str, "with %s and get %s",pay_type,get_type) != 2) {
               get_type = "";
               if (sscanf(str, "with %s", pay_type) != 1)
                   pay_type = "";
           }
           if (pay_type != "")
               if (member_array(pay_type, MONEY_TYPES) < 0) {
                   command("say I don't accept those " + pay_type +
                           " coins, " + query_npc_address_name(tp, "") +
                           ".");
                   return 1;
               }
           if (get_type != "")
               if (member_array(get_type, MONEY_TYPES) < 0) {
                   command("say " + capitalize(get_type) + " coins? " +
                           "Never heard of those!");
                   return 1;
               }
          /* Try to take the money */
          if (sizeof(money_arr = pay(price, tp, pay_type, 0, 0, get_type))
                     == 1) {
              if (money_arr[0] == 1)  {
                  command("say I think that the order is a bit " +
                          "more expensive, " +
                          query_npc_address_name(tp, "") + ".");
                  return 1;
              }
              else if (money_arr[0] == 2)  {
                  command("say You do not have any " + pay_type +
                          " coins, " + query_npc_address_name(tp, "") +
                          ".");
                  return 1;
              }
              else {
                  command("say I think that the order is a " +
                          "bit too expensive for you, " +
                           query_npc_address_name(tp, "") + ".");
                  end_waiting();
                  return 1;
              }
          }
          coin_pay_text = text(exclude_array(money_arr,
                               sizeof(MONEY_TYPES),
                               sizeof(MONEY_TYPES)*2-1));
          coin_get_text = text(exclude_array(money_arr, 0,
                              sizeof(MONEY_TYPES)-1));
          tp->catch_msg("You pay " + QTNAME(this_object())+" "+
                        coin_pay_text+".\n");
          say(QCTNAME(tp)+" pays "+QTNAME(this_object())+" "+
              coin_pay_text+ ".\n");

          if (coin_get_text) {
              tp->catch_msg("You get " + coin_get_text +
                            " in return.\n");
              say(QCTNAME(tp) + " gets " + coin_get_text +
                  " in return.\n");
          }
          command("say Thank you, " + query_npc_address_name(tp, "") +
                  ", I'll begin work now!");

          remove_alarm(confirmation_alarm);
          confirmation_alarm = 0;

          /* Create the item (armour or polearm) leaves it assigned
             finished_item global object variable */
          if (sizeof(armour_order)) {
              state = ARMOUR_MAKING;
              stage = CARRYING_OUT;
              make_the_armour(armour_order[0], armour_order[1],
                              armour_order[2]);
              if (objectp(jewel) && objectp(brew)) {
                  command("emote takes the " + brew->short() + " and the " +
                          jewel->short() + ".");
                  jewel->remove_object();
                  brew->remove_object();
              }
              set_alarmv(4.0, 0.0, "working_armour", ({1}));
              if (!random(4))
                  command("say Watch me go!");
              return 1;
          }
          else if (sizeof(polearm_order)) {
              state = POLEARM_MAKING;
              stage = CARRYING_OUT;
              make_the_polearm(polearm_order[0], polearm_order[1],
                               polearm_order[2], polearm_order[3]);
              set_alarmv(4.0, 0.0, "working_polearm", ({1}));
              if (!random(4))
                  command("say Watch me go!");
              return 1;
          }
          else {
              command("confused");
              end_waiting();
              return 1;
          }
       }
       else if (stage == CARRYING_OUT) {
          command("say But you've already paid, " +
                  query_npc_address_name(tp, "") + "!");
          command("poke " + customer);
          return 1;
       }
       else {
          command("confused");
          end_waiting();
          return 1;
       }
   }
   command("say There's nothing for you to pay for at the moment, " +
           query_npc_address_name(tp, "") + ".");
   return 1;
}


/* Finish work on an item he's been making, stack it on rack */
void
finish_work()
{
    object cs;

    if (!finished_item) {
        command("shout Damn! I lost what I was working on!");
        command("scream");
        clear_customer();
        return;
    }

    command("emote completes his work on the " + 
             finished_item->short() + ".");
    finished_item->update_prop_settings();
    command("emote puts the " + finished_item->short() + 
            " on the rack ready for collection.");
    environment(this_object())->rack_for_collection(customer, finished_item);

    if (!(cs = find_living(customer)))
        return; 

    if (!present(cs, environment(this_object()))) 
        cs->catch_msg("Gamalus's voice sounds through your mind:\n" +
                      "Bubba's finished the " + finished_item->short() + 
                      " now; please stop by to collect your new item!\n");
    else {
        cs->catch_msg("You may now collect your new " + 
                      finished_item->short() + "!\n");
        if (sizeof(armour_order) && (armour_order[2] == "magical")) 
            command("say The enchantment will last only for a short " +
                    "time, so you had best put it to use as quickly as " +
                    "possible. May the shield protect you well! " +
                    "Good luck!");
    }
    clear_customer();
}



/* Reply to polymorph quest ask */
string
reply_help(string str)
{
    object tp = this_player();
    object jewel, brew;

    if (tp->test_bit(PQ_DOM, PQ_GROUP, PQ_BIT)) {
         return "ponder wasting one's time.";
    }

    if (present(CORPSE_NAME, tp))
        return ("say I see that you have the polymorph's corpse on you! " +
                "What would you need a magical shield for now?"); 
 
    if (present(SHIELD_NAME, tp))
        return ("say You've got a magical shield already, what on " +
                "earth are you after now?");

    if (tp->query_prop(LIVE_I_FOUGHT_CALIA_PQ_DEMON)) {
        jewel = present(JEWEL_NAME, tp);
        brew = present(BREW_NAME, tp);
        if (!objectp(jewel) || !objectp(brew)) 
            return ("say Ah, you want a magical shield. I'd like to help " +
                    "you, but I don't think you have the necessary items " +
                    "for me to make one.");
        else
            return ("say Ah, you want a magical shield. I can make you one, " +
               "as you appear have the necessary items to make a particular " +
               "type. Please do <aorder magical shield> to proceed."); 
    }

    return ("peer " + tp->query_real_name());
}


void
create_monster()
{
  if (!IS_CLONE)
    return;

  set_name("bubba");
  add_name("blacksmith");
  add_name("smith");
  set_race_name("human");
  set_title("Hammerhead the Master Blacksmith");
  set_adj(({"stocky","grim"}));

  set_long("@@bubba_long");

  set_gender(G_MALE);
  set_alignment(100);
  add_prop(NPC_I_NO_RUN_AWAY, 1);
  add_prop(NPC_M_NO_ACCEPT_GIVE, 0); 
  default_config_npc(random(5)+55);
  set_base_stat(SS_CON,random(6)+56);
  set_base_stat(SS_STR,random(6)+88);

  set_hp(10000);
  set_skill(SS_WEP_CLUB, random(5)+66);
  set_skill(SS_DEFENCE, random(5)+66);
  set_skill(SS_AWARENESS, random(10) + 50);

  set_tell_active(1);
  set_chat_time(8);

  add_chat("I am a master of my craft you know.");
  add_chat("I love the smell of melting iron in the morning.");
  add_chat("Nothing like thrashing heavy metal to take out your " +
           "frustrations.");

  config_default_trade();

  set_alarm(1.0, 0.0, get_armed);

  add_ask(({"help", "magical shield", "shield", "for help"}),
            VBFC_ME("reply_help"), 1);
  add_ask( ({ "amjal" }),
            "@@reply_academic", 1);
}


void
add_introduced(string who)
{
  if (member_array(who, known) > -1)
      return;
  known += ({ who });
  set_alarm(1.0, 0.0, &command("introduce me"));
  set_alarm(2.0, 0.0, &command("say Greetings, " + capitalize(who) + "."));
}


void
do_bow(object actor)
{
    if (objectp(actor))
        command("bow " + actor->query_real_name());
    else
        command("bow");
}


void
emote_hook(string emote, object actor, string adverb)
{
    if ((emote == "bow") || (emote == "curtsey"))
        set_alarm(1.0, 0.0, &do_bow(actor));
}


void
accept_sheet(object sheet, object tp)
{
    object mirror;
    string name;

    name = tp->query_real_name();

    command("smile");
    command("emote says: Yes, I can do something with this!");
    sheet->add_prop(OBJ_M_NO_STEAL,1);
    if (tp->query_prop(LIVE_I_WAS_GIVEN_GLASS))
    {
        mirror = clone_object(GELAN_OBJECTS+"mirrored_glass");
        mirror->move(TO);
        command("emote says: Excellent, I shall get to work.");
        command("emote lays the sheet of silver out on the anvil.");
        command("emote lays the glass on top of the silver.");
        command("emote cuts both the silver and the glass to the same "+
            "size.");
        command("emote uses some type of special glue to stick the glass "+
            "down onto the silver.");
        command("emote wipes off all of the finger prints from the newly "+
            "formed piece of mirrored glass.");
        command("emote looks at himself in the mirrored glass briefly.");
        command("smile handsomely");
        command("emote says: Here you are.");
        command("give mirror to "+name);
        tp->remove_prop(LIVE_I_WAS_GIVEN_GLASS);
        tp->remove_prop(LIVE_I_WAS_GIVEN_SHEET);
        return;
    }
    command("emote says: This will do just fine.");
    command("emote says: Now if I only had a sheet of glass. Perhaps the "+
        "glass blower in Argos could make you one?");
    tp->add_prop(LIVE_I_WAS_GIVEN_SHEET,1);
    tp->remove_prop(LIVE_I_GOT_SHEET);
}

void
accept_glass(object glass, object tp)
{
    object mirror;
    string name;

    name = tp->query_real_name();

    command("smile");
    command("emote says: Yes, I can do something with this!");
    glass->add_prop(OBJ_M_NO_STEAL,1);
    if (tp->query_prop(LIVE_I_WAS_GIVEN_SHEET))
    {
        mirror = clone_object(GELAN_OBJECTS+"mirrored_glass");
        mirror->move(TO);
        command("emote says: Excellent, I shall get to work.");
        command("emote lays the sheet of silver out on the anvil.");
        command("emote lays the glass on top of the silver.");
        command("emote cuts both the silver and the glass to the same "+
            "size.");
        command("emote uses some type of special glue to stick the glass "+
            "down onto the silver.");
        command("emote wipes off all of the finger prints from the newly "+
            "formed piece of mirrored glass.");
        command("emote looks at himself in the mirrored glass briefly.");
        command("smile handsomely");
        command("emote says: Here you are.");
        command("give mirror to "+name);
        tp->remove_prop(LIVE_I_WAS_GIVEN_GLASS);
        tp->remove_prop(LIVE_I_WAS_GIVEN_SHEET);
        return;
    }
    command("emote says: This will do just fine.");
    command("emote says: Now if I only had a sheet of silver...");
    tp->add_prop(LIVE_I_WAS_GIVEN_GLASS,1);
    tp->remove_prop(LIVE_I_GOT_SHEET);
}

void
drop_stuff(object ob)
{
     if (!objectp(ob))
         return;

     command("emote looks curiously at " + LANG_THESHORT(ob) + "."); 
     command("shrug");
     command("emote says: What would I want this for?");
     command("emote says: I don't work that way, read the help files!");
     command("drop " + OB_NAME(ob));
}

void
do_smile()
{
    command("smile");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from); 

    if (ob->id("_sheet_of_silver_"))  
        set_alarm(1.0, 0.0, &accept_sheet(ob,from));

    else if (ob->id("_sheet_of_glass_"))  
        set_alarm(1.0, 0.0, &accept_glass(ob,from));

    else if (ob->id("_sheet_of_mirrored_glass_"))
        set_alarm(1.0, 0.0, &do_smile());

    else if (ob->id("hammer"))
        set_alarm(1.0, 0.0, &do_smile());

    else 
        set_alarm(1.0, 0.0, &drop_stuff(ob));
}


query_knight_prestige() { return -5; }

void 
init_living()
{
  ::init_living();
  add_action(do_help,"help");

  /* armour order */
  add_action(do_armour_order,"aorder");

  /* polearm order */
  add_action(do_polearm_order,"porder");

  /* Any order */
  add_action(do_pay,"pay");
  add_action(do_cancel, "cancel");

  /* weapon repair */
  add_action(do_w_fix,"sharpen");
  add_action(do_w_fix,"wax");
  add_action(do_w_cost,"wcost");

  /* armour repair */
  add_action(do_a_fix, "fix");
  add_action(do_a_cost, "acost");
}

// Defines for Academics
#define ACADEMIC_MANAGER     "/d/Calia/guilds/academics/lib/academy_manager"
#define IS_ACADEMIC(x)       ACADEMIC_MANAGER->query_is_member(x)
#define TASK_FOUR_GIVEN       "_academic_task_four_given"

public string
reply_academic()
{
    object player = this_player();
    // Academics who are working on their second task should get a proper
    // respons. Everyone else should get the default response
    if (ACADEMIC_MANAGER->query_completed_task_4(player))
    {
        command("say You're getting along well along in your studies, I hope. "
            + "I hear that training device I gave you was helpful.");
        return 0;
    }
    else if (!IS_ACADEMIC(player)
             || !player->query_prop(TASK_FOUR_GIVEN))
    {
        say_busy(player);
        return 0;
    }
    
    if (!present("academic_resistance_contraption", player))
    {
        command("say Amjal sent you? I guess I promised him I would help.");
        command("say I don't get what he keeps doing with all these plates "
            + "though.");
        command("emote takes three small pieces of junk metal and piles "
            + "them near the forge.");
        command("emote hammers the pieces into three "
            + "even-sized plates, one after another.");
        command("emote grabs a discarded polearm and attaches the plates "
            + "with a few pins.");
        object contraption = clone_object("/d/Calia/guilds/academics/objs/task_4_contraption");
        contraption->set_owner_name(player->query_real_name());
        contraption->set_state(1);
        contraption->move(player, 1);
        player->catch_msg(QCTNAME(this_object()) + " gives you a contraption.\n");
        command("say Here you go. Give this to Amjal.");
    }
    else
    {
        command("say You already have a contraption! Go on, give it to Amjal already.");
    }
    
    return 0;
}
