// Briareus - Prior of the kirk at Baile Ashlagh
//            Allows players to 'start here' (temp loc) in abbey for fee
//            Receives gifts from Abbot Semion (kirk in MacDunn) for tour
//            Receives one of the letters in the postmaster tour
//
// Zima    - June 16, 1998
//
// Refactored
// Tapakah, 08/2021
//
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <money.h>
#include "/d/Khalakhor/se_speir/claryn/tabor/obj/honey.h"
#include "defs.h"
inherit  SR_NPC+"monkbase";
 
#define  ROOM_RENTED  "_ba_abbey_rented"
#define  NUM_CANDLES  "_briar_num_candles"
#define  HPOT         "_briar_hpot"
 
void
equip_me ()
{
  vest_me(({"robe","cincture","tonsure","scapular","cope"}));
}
 
void
give_back (object ob, object tp)
{
   string obs = lower_case(ob->query_name());
   command("say I can't accept this from you.");
   if (!command("give "+obs+" to "+lower_case(TPQN)))
     command("drop "+obs);
}

void
create_khalakhor_human ()
{
  ::create_khalakhor_human();
  add_name(({"prior","manach","monk"}));
  add_adj(({"wizened","white-haired"}));
  set_long("He is a wizened white-haired human, impressively dressed in "+
           "the habit of a kirk prior.\n");
 
  set_manach_stats((60+random(60)));
  set_size_descs("short","plump");
  set_act_time(60);
  set_default_answer(defans);
  add_act("emote mumbles a silent prayer.");
  add_act("emote puts his hands together prayerfully.");
  add_act("emote bows his head prayerfully.");
  add_act("emote raises his hands and sings a quiet chant.");
  add_act("emote folds his arms into the sleeves of his robe.");
  add_act("emote nods at you hospitably.");
  add_act("emote chants in an ancient tounge.");
  add_act("emote traces three circles before his face.");
  add_act("emote genuflects on one knee and prays.");
  add_act("emote folds his arms beneath his scapular.");
  remove_prop(NPC_M_NO_ACCEPT_GIVE);
  add_ask(({"job","tour","quest","task","for job","for task",
            "for a job","for a task"}),
          "say I do not have anything for you to do, but you are welcome "+
          "to stay the night.",1);
  add_ask(({"abbot","semion","abbot semion","abbot Semion","Abbot Semion"}),
          "say Semion is Abbot of Kirk Seanchan Tor.",1);
  add_ask(({"kirk seanchan tor","Kirk Seanchan Tor"}),
          "say It is in the city of Port MacDunn.",1);
  add_ask(({"port","macdunn","port macdunn","Port MacDunn","city"}),
          "say Port MacDunn is the village where ships arrive from foreign "+
          "lands. I'm sure you've been there.",1);
  add_ask("to stay the night","@@ask_stay",1);
  add_ask(({"refund","for refund","for a refund"}),"@@ask_refund",1);
  add_ask("kirk","say Yes, our kirk is small but frequently visited.",1);
  add_ask("join","say See Abbott Semion in MacDunn about that.",1);
  add_ask(({"order","sean-rhian"}),
          "say It is an ancient faith, the one we practice.",1);
 
}
 
void
random_surprise ()
{
  string m;
  switch (random(8)) {
  case 0:  m="jump";                                          break;
  case 1:  m="say I think I know who sent these!";            break;
  case 2:  m="say I think I know what is next!";              break;
  case 3:  m="say Oh, how nice!";                             break;
  case 4:  m="say I really didn't expect these this year!";   break;
  case 5:  m="smile";                                         break;
  case 6:  m="say Ah, this was very unexpected, somewhat!";   break;
  default: m="say How nice of you to bring this!";
  }
  command(m);
}

void
remove_gifts ()
{
  object *inv = all_inventory(TO);
  int    i;
  for (i=0; i<sizeof(inv); i++)
    if (inv[i]->id(HM_CANDLE) ||inv[i]->id(HONEYPOT))
      inv[i]->remove_object();
  command("emote puts the candles and the pot of honey away.");
}
 
void
rec_gift (object ob, object tp)
{
  int    numcandles = (tp->query_prop(NUM_CANDLES));
  int    hpot       = (tp->query_prop(HPOT));
  string errmsg     = 0;

  // if the player was not sent/blessed by Semion, don't accept
  if (! tp->query_prop(SEMIONS_BLESSING) ||
      (tp->query_prop(SEMIONS_BLESSING))["name"] != "Honeycombs")
    errmsg="Semion did not send you to deliver this.";
 
  // if player has already been blessed, don't accept
  else if (tp->query_prop(BRIARS_BLESSING))
    errmsg="This is just too much for me!";
 
  // check if given a candle
  else if (ob->id(HM_CANDLE)) {
    if (numcandles<3) {
      numcandles++;
      tp->add_prop(NUM_CANDLES,numcandles);
    }
    else
      errmsg="Ah, this is too much. I don't need any more candles.";
  }
 
  // must be a honeypot then
  else if (!(ob->query_honey()))
    errmsg="This honeypot is empty! I have plenty of empty ones.";
  else if (hpot)
    errmsg="Oh, I really don't need any more honey. Too much "+
      "sweetness is not good.";
  else {
    hpot=1;
    tp->add_prop(HPOT,1);
  }
 
  // if error, return object to player
  if (errmsg) {
    command("say " + errmsg);
    give_back(ob,tp);
    return;
  }
 
  // act surprised! if all gifts given, give blessing
  random_surprise();
  if (numcandles>=3 && hpot)
    if (present(tp,ENV(TO))) {
      command("say Ah, these must be from Abbot Semion. He sends the "+
              "same thing every year.");
      command("say You are very gracious to bring these. Please accept "+
              "my blessing.");
      tp->catch_msg(QCTNAME(TO)+" places his hand on your head and "+
                    " mumbles a short prayer.\n");
      tell_room(ENV(TO),QCTNAME(TO)+" places his hand on the head of "+
                QTNAME(tp)+" and mumbles a short prayer.\n",tp);
      command("say Return to Abbot Semion and give him my thanks.");
      tp->add_prop(BRIARS_BLESSING,1);
      tp->remove_prop(NUM_CANDLES);
      tp->remove_prop(HPOT);
      set_alarm(6.0,0.0,&remove_gifts());
    }
    else {
      command("say Now where did "+HE_SHE(tp)+" go?");
      command("say I can't accept these without blessing the one who "+
              "brought them!");
      command("drop candles");
      command("drop honeypot");
    }
}

int
check_gift (object ob, object from)
{
  if (! living(from))
    return 0;
  if (ob->id(HM_CANDLE) || ob->id(HONEYPOT)) {
    set_alarm(4.0, 0.0, &rec_gift(ob,from));
    return 1;
  }
  set_alarm(4.0, 0.0, &give_back(ob,from)); 
  return 0;
}
 
void enter_inv (object ob, object from)
{
  ::enter_inv();
  if (living(from)) {
    if (check_gift(ob,from))
      return;
  }
}
 
//
// ask_stay - respond to player asking to stay the night
//
string
ask_stay ()
{
  if (TP->query_alignment() < -10) {
    command("emote studies you carefully, peering into your eyes.");
    command("say I sense evil in your heart; thus you may not stay.");
    return  "say Begone with you!";
  }
  if (TP->query_prop(ROOM_RENTED))
    return "say You have already asked to stay and paid my friend.";
  if (!MONEY_ADD(TP,-96))
    return "say Do you not have eight silver coins?";
  TP->add_prop(ROOM_RENTED,1);
  TP->catch_msg("You pay "+QTNAME(TO)+" some money.\n");
  tell_room(ENV(TO),QCTNAME(TP)+" pays "+QTNAME(TO)+" some money.\n",TP);
  command("say Now return to the abbey and read the instructions on "+
          "the card.");
  return "say May you sleep well tonight.";
}
 
string
ask_refund ()
{
  switch ((TP->query_prop(ROOM_RENTED))) {
  case 1:
    command("say You should first try 'start here' in the abbey.");
    return "say If it works, I may not give you a refund.";
  case 2:
    command("say Ah, so sorry about that.");
    MONEY_ADD(TP,96);
    tell_room(ENV(TO),QCTNAME(TO)+" refunds the money.\n");
    TP->catch_msg("Please report the bug on 'start here' "+
                  "in the abbey.\n");
    TP->remove_prop(ROOM_RENTED);
    return "say Please come again though, we should have "+
      "everything fixed soon.";
  default:
    return "say But you have not asked to stay nor have "+
      "you paid!";
  }
}
 
string
defans ()
{
  command("say I am afraid I do not know that, but I'll make a note to "+
          "find out.");
  return "";
}
