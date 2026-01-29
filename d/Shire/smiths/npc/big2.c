   /* Bigerin Smallburrow - the tanner of the Smiths Guild */
/* 09-Sep-99  Updated by Kesor
              - disable making many leathers from one skin.
              - stop dropping things, try to give it first instead.
              - skins are leftovers - better checking (help of Mercade)
   12-Sep-99  Updated by Kesor
              - when given 10 skins will no longer return only one
              - will not eat up skins as he has been before
              - removed references to this_player() inside alarms
   14-Jun-01  Updated by Finwe
              - added tanning messages

Some skins:
    /d/Gondor/common/obj/rabbitpelt
    /d/Khalakhor/common/obj/leftover/skin.c
*/

#pragma save_binary;

inherit "/sys/global/money";
inherit "/std/monster";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "smiths.h"

#define NECKLACE SMITHSDIR_OBJ+"npc_neck"

void give_leather(object buyer, object hide);

void wield_me();
void tell1(object player);
void tell2(object player);
void tell3(object player);
void tell4(object player);
void tell5(object player);
void tell6(object player);
void tell7(object player);
void tell8(object player);

int give(object newitem, object towho);
int pay(string str);
int refuse(string str);
int check_leather(object newitem);
int give_back(object towho, object obj);

object item, giver;
// There are bugs when putting skin's adj to be as leather adjs...
string leather_type;
int busy=0,ready=0;

void
create_monster()
{
   if (!IS_CLONE)
      return;

   set_name(({"bigerin","smiths_guild_tanner"}));
   set_title("tanner of the Smiths Guild");
   set_race_name("hobbit");
   set_adj("merry");
   set_adj("broad");
   set_long("Bigerin Smallburrow is the one who makes the leather for"+
      " members of the Smiths Guild.\n");

             /* STR  DEX CON INT WIS DIS */
   set_stats(({ 70, 90, 70, 50, 50, 70 })); 

   set_default_answer(QCTNAME(TO)+" tells you: Sorry, I don't know "+
      "anything other than leather and skins. Ask me about those, and I will "+
      "be happy to answer you.\n");
   add_ask(({"leather","skin","hide", "pelt", "fur"}),
      QCTNAME(TO)+" tells you: Yes, I can make leather"+
      " from hides and skins. I do it very well.\n");

   set_alignment(250);
   set_skill(SS_UNARM_COMBAT,80);
   set_skill(SS_DEFENCE,80);

   remove_prop(NPC_M_NO_ACCEPT_GIVE);

   set_alarm(2.0, 0.0, &wield_me());
}

void
init_living()
{
   ::init_living();
   add_action("pay", "pay");
   add_action("refuse", "refuse");
}

void
enter_inv(object obj,object from)
{
   ::enter_inv(obj,from);

   if (!busy)
       giver=from;

   set_alarm(2.0, 0.0, &give(obj,from));
}

void
set_ready() {
   ready=1;
}

void
wield_me() {
   object neck;

   seteuid(getuid(this_object()));

   neck = clone_object(NECKLACE);
   neck->set_short("copper necklace");
   neck->set_adj("copper");
   neck->move(this_object());
   command("wear necklace");
   set_alarm(3.0, 0.0, set_ready);
}

int
add_introduced(string name) 
{
   set_alarm(1.0, 0.0, &command("introduce me to " + name));
   return 1;
}

/* Bigerin is payed for making leather
*/

int
pay(string str) {
   object ob;

   if ((giver!=TP) || (!busy)) {
      command("say to "+TP->query_name()+
      " I am not currently dealing with you.");
      return 1;
   }
   if (giver->query_prop("_gave_skin_to_bigerin")) {
      command("say to "+giver->query_name()+
      " You already paid me to do something. Please wait.");
      return 1;
   }

   if (str=="bigerin") {
      if (!take_money(giver,TANNING_COST)) {
         command("say to "+giver->query_name()+" tells you: "+
            "You don't have enough money to pay me. Come back when you "+
            "have earned some more, or <refuse bigerin> to get your "+
            "skin back.\n");
         return 1;
      }
      else
      {
         command("say Let me see what I can do with it...");
         giver->add_prop("_gave_skin_to_bigerin",1);
        command("emote lays out his tools for tanning.");
        set_alarm(2.0,0.0,&tell1(TP));
//         set_alarm(30.0, 0.0, "give_leather", giver, item);
         return 1;
      }
   }
}

void
give_leather(object buyer, object item) {
   object ob;

   seteuid(getuid(this_object()));

   item->remove_object();
   ob=clone_object(SMITHSDIR_OBJ+ "sm_leath");
   ob->add_adj(leather_type);

   command("say to "+buyer->query_name()+" Here is the leather. "+
       "It has been a pleasure dealing with you.");
   if (give_back(buyer,ob))
   {
      command("say to "+buyer->query_name()+
      " Oops, it seems you cannot carry the leather.");
      command("say I will drop it on the floor.");
      command("drop "+ob->query_name());
   }

   buyer->remove_prop("_gave_skin_to_bigerin");
   busy=0;
}

int
refuse(string str) {
   notify_fail("Refuse whom?\n");

   if (str!="bigerin") return 0;

   if ((giver!=TP) || (!busy)) {
      command("say to "+TP->query_name()+" But you are not dealing "+
      "with me at the moment!");
      return 1;
   }

   command("say to "+TP->query_name()+" That's too bad but I can't "+
       "do anything about it.");
   if (give_back(giver,item))   {
       command("drop"+item->query_name());
   }
   busy=0;
   return 1;
}

int
give(object newitem, object towho) {
   string name;
   int result;

   if (busy) {
      command("say to "+towho->query_name()+" I am already working on "+
         "something, so you will have to wait.");
      if (give_back(towho,newitem)) {
          command("drop "+newitem->query_name());
      }
      return 1;
   }

   if (!ready) {
      return 1;
   }

   if (check_leather(newitem)) {
      command("say to "+towho->query_name()+" Ahh I see that you have "+
      "work for me....");
      command("say to "+towho->query_name()+" It will cost you "+
      TANNING_COST+" copper coins to get something useful from this.");
      command("say to "+towho->query_name()+" Just <pay bigerin> to pay me "+
      "or <refuse bigerin> to have me return your item to you.");
      item=newitem;
      busy=1;
   }
   else {
      command("say I don't really see what I should do with this.");
      if (give_back(towho,newitem)) {
          command("drop "+newitem->query_name());
          
      }
   }
}

int
check_leather(object newitem)
{

  // This doesn't yet work for all objects!
  //   if (!strlen(function_exists("leftover_init", newitem)))
    /* This object is NOT a leftover. It's probably not a skin */
  //        return 0;
 
   if (member_array("skin", newitem->query_names()) > -1 || 
       member_array("hide", newitem->query_names()) > -1 ||
       member_array("pelt", newitem->query_names()) > -1 ||
       member_array("fur", newitem->query_names()) > -1)
   {
        if (strlen(function_exists("quer_race", newitem)))
           leather_type = newitem->query_race();
        else
           leather_type = "soft";
        return 1;
   }
   else
       return 0;
}

int
give_back(object towho, object obj)
{
    int success;

    if (!(success = obj->move(towho)))
    {
        towho->catch_msg("Bigerin gives some leather to you.\n");
        say("Bigerin gives some leather to "+QNAME(towho)+".\n");
    }
    else
        return success;
}




void
tell1(object player) 
{

   player->catch_msg("Bigerin begins by washing the pelt in " +
    "fresh water several times.\n");
   set_alarm(7.0,0.0,&tell2(TP));

   }

void
tell2(object player)
{
   player->catch_msg("Next he salts the hide thoroughy\n");
   set_alarm(5.0,0.0,&tell3(TP));
}

void
tell3(object player) 
{
   player->catch_msg("Afterwards, the tanner scraps the skin clean.\n");
   set_alarm(6.0,0.0,&tell4(TP));
}

void
tell4(object player) 
{
    if (player && (ENV(player) != TO))
        return;
    player->catch_msg("Biberin next washes the skin thoroughly " +
        "to remove the salt.\n");
    set_alarm(6.0,0.0,&tell5(player));
}

void
tell5(object player) 
{
    if (player && (ENV(player) != TO))
        return;
    player->catch_msg("When the second wash is done, he soaks " +
        "the skin in a tanning solution.\n");
    set_alarm(10.0,0.0,&tell6(player));
}

void
tell6(object player) 
{
    if (player && (ENV(player) != TO))
        return;
    player->catch_msg("The tanner stretches the skin out on a " +
        "frame and begins scrapping the fur off the skin.\n");
    set_alarm(5.0,0.0,&tell7(player));
}

void
tell7(object player) 
{
    if (player && (ENV(player) != TO))
        return;
    player->catch_msg("After scraping the fur off, Bigern " +
        "begins to stretch and pull the skin, breaking it down " +
        "in the process and making it pliable.\n");
    set_alarm(5.0,0.0,&tell8(player));
}

void
tell8(object player) 
{
    if (player && (ENV(player) != TO))
        return;
    player->catch_msg("After scraping the fur off, Bigern " +
        "begins to stretch and pull the skin, breaking it down " +
        "in the process and making it pliable.\n");
    set_alarm(6.0, 0.0, "give_leather", giver, item);
}
