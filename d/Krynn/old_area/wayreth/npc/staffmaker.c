/*
 * This is the staff-maker of Wayreth, based on Bubba in Gelan
 *
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 *
 */

#pragma save_binary

inherit "/std/monster";
inherit "/lib/trade";
inherit "/std/act/action";

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#include <wa_types.h>
#include <const.h>
#include <money.h>
#include <cmdparse.h>
#include <language.h>

#define ENV environment
#define LOW(x) lower_case(x)
#define CAP(x) capitalize(x)

#define AWAITING_CUSTOMER 0
#define STAFF_MAKING 1

#define NOTHING 0
#define CONFIRMATION 1
#define CARRYING_OUT 2

int state; /* Current state of the blacksmith e.g. AWAITING_CUSTOMER */
int stage; /* Current stage of blacksmith in stage e.g. CARRYING_OUT */

string *known = ({ });

string customer; /* The current customer being worked for */
string working_on; /* Descr of the object being worked on */
int price; /* price on copper of the thing currently being worked on */
string *staff_request = ({ });
object finished_item;

int confirmation_alarm;

string query_npc_address_name(object player, string t);
void finish_work();
void end_waiting();
void say_busy(object player);

#include "staffs/make_staff.h"
#include "staffs/make_staff.c"

mixed *fixing;
int testing;

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
    staff_request = ({});
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
    "This is Keshir, a Kagonesti elf who has been in the employ of the " +
    "tower for years as a maker of staves for the members.";  

    switch (state) {
        case AWAITING_CUSTOMER : str += "awaiting requests.";
                                 break;
        case STAFF_MAKING : { 
             switch (stage) {
                 case CONFIRMATION : str += ("awaiting confirmation "+
                                         "for a request for " + 
                                         working_on + ".");
                                     break;
                 case CARRYING_OUT : str += ("working, seeing to a " +
                                            "request for " + working_on + 
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



/* Cancel an request */
int
do_cancel()
{
   object tp = this_player();

   tell_room(environment(this_object()), QCTNAME(tp) + " asks " +
        QTNAME(this_object()) + " to cancel the current request.\n", tp);
   tp->catch_msg("You ask " + QTNAME(this_object()) + " to cancel " +
                 "the current request.\n");

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




/* Pay for an request, thereby confirming it */
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
            "pay " + QTNAME(this_object()) + " for an request.\n", tp);
    tp->catch_msg("You offer to pay " + QTNAME(this_object()) + " for " +
                "an request.\n");

    if (state == AWAITING_CUSTOMER) {
        command("say What request, " + query_npc_address_name(tp, "") +
               ", there aren't any requests being considered at the moment!");
        return 1;
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
                  command("say I think that the request is a bit " +
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
                  command("say I think that the request is a " +
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

          /* Create the item (armour or staff) leaves it assigned
             finished_item global object variable */
          if (sizeof(staff_request)) {
              state = STAFF_MAKING;
              stage = CARRYING_OUT;
              make_the_staff(staff_request[0], staff_request[1],
                               staff_request[2], staff_request[3]);
              set_alarmv(4.0, 0.0, "working_staff", ({1}));
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
    }
    clear_customer();
}

void
create_monster()
{
  if (!IS_CLONE)
    return;

  set_name("keshir");
  set_race_name("elf");
  set_living_name("keshir");
  set_title("Master Staffmaker of Wayreth");
  set_adj(({"muscled","lithe"}));

  set_long("@@keshir_long");

  set_gender(G_MALE);
  add_prop(NPC_I_NO_RUN_AWAY, 1);
  add_prop(NPC_M_NO_ACCEPT_GIVE, 
    " points to the sign!\n");
  add_prop(OBJ_M_NO_ATTACK, "This is not allowed in the tower!");
  default_config_npc(random(5)+55);
  set_base_stat(SS_CON,random(6)+56);
  set_base_stat(SS_STR,random(6)+88);

  set_hp(10000);
  set_skill(SS_WEP_CLUB, random(5)+66);
  set_skill(SS_DEFENCE, random(5)+66);
  set_skill(SS_AWARENESS, random(10) + 50);

  set_tell_active(1);
  set_chat_time(8);

  add_chat("Several of the Masters and full mages have their own "+
	"personal staffs stored here.");
  add_chat("I can give only generic staves to apprentices.");

  config_default_trade();
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


query_knight_prestige() { return -5; }

void 
init_living()
{
  ::init_living();
  /* staff request */
  add_action(do_staff_request,"request");

  /* Any request */
  add_action(do_pay,"pay");
  add_action(do_cancel, "cancel");
}
