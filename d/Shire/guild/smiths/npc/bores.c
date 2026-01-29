/* Bores Smithman - High Master Smith */

/*
 *
 * Had to hack the file for Mercade's "unworn" implementation
 *  - will be back to fix properly - Jaypeg May 00
 * Added age check to buy iron bars. player must be wanderer to join.
 * Really small players cause errors when forging necklace.
 * -- Finwe, July 2004
 *
 * Palmer 16-July-2006
 *  Converted to Craft slot. Players who were already in a craft slot
 *  have the ability to come here and 'transfer' for a limited amount
 *  of time, if they choose to quit their craft guild and rejoin Smiths.
 *
 * Palmer 2-Aug-2006
 *  Fixed so 'buy' doesn't work for non-Smiths, just people trying to join.
 *
 * Raymundo, 7/31/2020
 *  Fixed typo in the long description.
 *
 * Varian, 2/20/21
 * Put _bores_ back in the list of names so that necklace recovery
 * is able to function again.
 */

#pragma save_binary;

inherit "/lib/trade.c";
inherit "/sys/global/money";
inherit "/std/monster";
inherit "/std/act/chat";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "../smiths.h"
//#include <money.h>

#define WEP SMITHSDIR_OBJ+"bo_axe"
#define BO_NECKLACE SMITHSDIR_OBJ+"npc_neck"
#define NECKLACE SMITHSDIR+"necklace"

int give();
void wield_me();
void equipped();
void transfer_from_lay();
int do_buy(string str);
int do_pay(string str);
string del_white_space(string str);


object item, giver;
int    check_on=0;


string
del_white_space(string str) 
{
    string *words;

    if (sizeof(words = explode(str, " ")) > 1)
	str = implode(words, "_");
    return str;
}



/*
* Function name: log_guild
* Description  : This function logs some actions of members of the guild.
*                It uses a larger cycle than basically coded.
* Arguments    : string text - the message to log.
*/
nomask private void
log_guild(string text)
{
   setuid();
   seteuid(getuid());

   if (file_size(SMITH_MEMBERSHIP_LOG) > MAX_MEMBERSHIP_LOG_SIZE)
      {
      rename(SMITH_MEMBERSHIP_LOG, (SMITH_MEMBERSHIP_LOG + ".old"));
   }

   write_file(SMITH_MEMBERSHIP_LOG, text);
}


void
create_monster()
{
   if (!IS_CLONE)
      return;

   set_name( ({"bores"}) );
   add_name( ({"_bores_", "guild master"}) );
   set_living_name("bores");
   set_title("High Master of the Smiths Guild");
   set_race_name("human");
   set_adj("grey");
   set_adj("wizened");
   set_long("This human must be at least sixty years old, but he is still"+
      " powerfully built and you do not think you would risk attacking him"+
      ".\nHe is also wearing mithril necklace studded with gems"+
      " which indicates him as a High Master of the Smiths guild.\n");

             /* STR  DEX  CON INT WIS DIS */
   set_stats(({ 210, 210, 210, 90, 90, 100 }));

   set_default_answer(QCTNAME(TO)+" tells you: That is of no interest to the"+
      " smiths guild.\n");
   add_ask(({"smiths"}), QCTNAME(TO)+" tells you: This is the marvelous guild"+
      " of the smiths.\nIf you want to join then I suggest you read the large"+
      " leather book about our guild.\n");
   add_ask(({"join","membership"}), QCTNAME(TO)+" tells you: If you want to"+
      " join then you"+
      " must buy an iron bar from me <pay bores>, and forge a necklace from it. When you"+
      " have finished that, return here and give me the necklace. If you"+
      " have made a good job I might accept you into the guild.\n");
   add_ask(({"buy","iron bar","iron bars"}),QCTNAME(TO)+" tells you: Okay-"+
      " you can pay"+
      " me "+IRON_COST+" copper coins and I will give you the iron bar.\n");
   add_ask(({"necklace"}),QCTNAME(TO)+" tells you: To make a necklace you"+
      " will need an iron bar.\n");
   add_ask(({"items","forging items","making items"}),
      QCTNAME(TO)+" tells you: You can presently make swords, axes, maces,"+
      " knives, necklace, helmets and armours. Some weapons can be made"+
      " for both singlehanded and twohanded use.\n");
   add_ask(({"forging"}),
      QCTNAME(TO)+" tells you: In order to forge an item you need to both"+
      " prepare the item and start forging the object.\n");
   add_ask(({"forge room","forges"}),
      QCTNAME(TO)+" tells you: Besides forging you can melt items made"+
      " here and polish items in there.\n");
   add_ask(({"iron","steel","blue steel","high steel"}),
      QCTNAME(TO)+" tells you: That is a very useful metal for forging.\n");

   set_chat_time(30);
   add_chat("The Blacksmiths guild is very old and highly respected.");
   add_chat("No smith has yet bested the abilities of the dwarves of old"+
      " when it comes to making weapons.");

   set_alignment(100);
   set_skill(SS_WEP_AXE,100);
   set_skill(SS_DEFENCE,80);
   set_skill(SS_PARRY,80);
   add_prop(LIVE_I_ALWAYSKNOWN, 1);
   remove_prop(NPC_M_NO_ACCEPT_GIVE);

   set_alarm(1.0, 0.0, &wield_me());
}

void
init_living()
{
   add_action(do_pay, "pay");
   add_action("transfer_from_lay", "transfer");
   add_action(do_buy, "buy");
   ::init_living();
}

int
do_buy(string str)
{
    string item_name, coin_pay_text, coin_get_text;
    string *words, item_file;
    int    *money_arr, amount, price, i;
    object *order;
   
   if (!IS_MEMBER(TP))
   {
       TO->command("say You can <pay bores> if you'd like to try to join this guild.\n");
       return 1;
   }

    if (!CAN_SEE_IN_ROOM(TO))
    {
        notify_fail("I can't see!\n");
        return 1;
    }
    if (!CAN_SEE(TO, TP))
    {
        notify_fail("I can't see you!\n");
        return 1;
    }
    if (!strlen(str))
    {
        notify_fail("Buy what?\n");
        return 0;
    }

    str = lower_case(str);
    words = explode(str, " ");
    if (sizeof(words) > 1)
    {
        sscanf(words[0], "%d", amount);
        if (amount > 0)
            str = implode(words[1..sizeof(words)], " ");
        else
            amount = 1;
    }
    else
        amount = 1;

    item_name = del_white_space(str);

    if (item_name == "iron_bar" || item_name == "bar" || item_name == "iron_bars" || item_name == "bars")
    {
        item_file = SMITHSDIR_OBJ+ "ir_bar";
    }

    else
    {
        write("Buy what, an iron bar?\n");
        return 1;
    }
    price = IRON_COST * amount;

    if (!take_money(TP,IRON_COST * amount)) {
         TO->command("say You don't have enough"+
            " money to pay me. Come back when you have earned some more.");
            return 1;
    }

    //write("You pay Bores for " + amount + " "+str+".\n");
    if (amount == 1) {
        write("You pay Bores for one iron bar.\n");
        }
    else {
        write("You pay Bores for " + amount + " iron bars.\n");
        }

    order = allocate(amount);
    for (i = 0; i < amount; i++)
    {
        order[i] = clone_object(item_file);
        if (order[i]->move(TP)!=0) {
            TO->command("say It seems you cannot even carry the"+
               " bar. I will drop the bar on the floor for you.");
            order[i]->move(ENV(TP));
        }
    }

    return 1;   
}


void
transfer_from_lay() {
    object shadow, necklace;
    int guild_exp, result;
    string player_name;

    player_name = TP->query_name();
    guild_exp = SMITHS_TRANSFER_OBJ->query_player(player_name);
    if (SMITHS_TRANSFER_OBJ->query_player(player_name) == 0)
    {
        write("You can't transfer. You weren't in the Smith lay guild.\n");
        return;
    }

     shadow = clone_object(SMITHSDIR+"smiths_craft_shadow");

     if ((result = shadow->shadow_me(TP, "craft", GUILD_STYLE, GUILD_NAME)) != 1)
     {
            shadow->remove_shadow();
            write("There was an error, you are not able to transfer at this"+
               " time.\nPlease make a bug report, error: " + result +
               " on shadowing.\n");


        return;
     }

     /* new member of guild is accepted */
     TP->clear_guild_stat(SS_CRAFT);
     TP->add_cmdsoul("/d/Shire/guild/smiths/smiths_craft_soul");
     TP->update_hooks();
     TP->set_guild_stat(SS_CRAFT, guild_exp);

     // item->remove_object();

     seteuid(getuid(this_object()));

     necklace = clone_object(NECKLACE);
     necklace->add_adj("iron");
     necklace->set_short("iron necklace");
     if (necklace->move(TP)!=0) {
        TO->command("say It seems you cannot carry your necklace."+
           " I will keep it for you, just come back and <get"+
           " necklace> whenever you want to.");
     }

    // Remove from transfer list so they can't do it again.
    SMITHS_TRANSFER_OBJ->remove_player(player_name);
    write("Bores gives you your old necklace. Welcome back.\n");
    command("hmm");
    write("If the necklace looks a little dull, it should be back to normal next time you wake.\n");
    log_guild(extract(ctime(time()), 4, 15) + " " +extract(ctime(time()), 21, 4)+" " + WRITE_NAME(TP) + " transfered to the Craft Blacksmiths.\n");

}


void
enter_inv(object obj,object from) {
   ::enter_inv(obj,from);

   item=obj;
   giver=from;
   set_alarm(1.0, 0.0, give);
}

void
wield_me() {
   object wep,neck;

   seteuid(getuid(this_object()));

   wep = clone_object(WEP);
   wep->move(this_object());
   command("wield axe");
   neck = clone_object(BO_NECKLACE);
   neck->set_short("gem studded mithril necklace");
   neck->set_adj("mithril");
   neck->set_adj("gem studded");
   neck->move(this_object());
   command("wear necklace");

   set_alarm(3.0, 0.0, equipped);
}

void
equipped()
{
   check_on=1;
}

int
add_introduced(string name)
{
   set_alarm(1.0, 0.0, &command("introduce me to " + name));
   return 1;
}

int
do_pay(string str) {
   object ob;

   if (IS_MEMBER(TP))
   {
       TO->command("say You can <buy bar> or <buy NUMBER bars>.\n");
       return 1;
   }

   if ((str=="bores") || (str=="for iron bar")) 
   {

        if (TP->query_average_stat() < 55 && !IS_MEMBER(TP))
        {
            TO->command("say You are too inexperienced to join the Blacksmiths. " +
            "Come back when you have earned some more experience.");
            return 1;
        }

        if (!take_money(TP,IRON_COST)) {
         TO->command("say You don't have enough"+
            " money to pay me. Come back when you have earned some more.");
         return 1;
      }
      else {
         ob=clone_object(SMITHSDIR_OBJ+ "ir_bar");
         if (ob->move(TP)!=0) {
            TO->command("say Hmm.. It seems you cannot even carry the"+
               " bar; You'll need quite a bit of luck being as weak as"+
               " you are. I will drop the bar on the floor for you.");
            ob->move(ENV(TP));
         }

         TO->command("say Good luck with the forging!");
         TP->catch_msg("Bores hands you an iron bar.\n");
         TP->add_prop(LIVE_I_SMITH_ENTRANCE_QUEST, 1);
         return 1;
      }
   }
}

int
give() {
   string name;
   object obj,shadow;
   int result;

   name=giver->query_The_name(TO);

/*   if ((item->short()=="iron necklace") || (!check_on)) {             */
/* ** emergency fix until I can make something a little more elegant ** */

   if ((item->short()=="unworn iron necklace") || (!check_on)) {

      if (check_on)
      {
         TO->command("say Ahh - you have made a necklace I see.");
         if (item->query_forger() != giver->query_name()) {
            TO->command("say This necklace wasn't made by you, "+
               name+".");
            TO->command("give iron necklace to "+giver->query_real_name());
            return 1;
         }

             /* check new member */
         if ((giver->query_guild_name_craft()==GUILD_NAME)
            || (giver->query_guild_name_lay()==GUILD_NAME)) {
            command("say But you are already a member of the Smiths Guild!");
            return 1;
         }

         if (giver->query_guild_name_craft()) {
            command("say But you are already a member of a craftsman guild!");
            return 1;
         }

         shadow = clone_object(SMITHSDIR+"smiths_craft_shadow");

         if ((result = shadow->shadow_me(TP, "craft",
            GUILD_STYLE, GUILD_NAME)) != 1)
         {
				shadow->remove_shadow();
				write("There was an error, you are not able to join at this"+
				   " time.\nPlease make a bug report, error: " + result +
				   " on shadowing.\n");


            return 1;
         }

             /* new member of guild is accepted */
         giver->clear_guild_stat(SS_CRAFT);
         giver->add_cmdsoul("/d/Shire/guild/smiths/smiths_craft_soul");
         giver->update_hooks();

         item->remove_object();

         command("say This is a nice piece of work. Welcome to the guild.");
         command("bow "+giver->query_name());
         command("smile");

         seteuid(getuid(this_object()));

         obj = clone_object(NECKLACE);
         obj->add_adj("iron");
         obj->set_short("iron necklace");
         if (obj->move(giver)!=0) {
            TO->command("say It seems you cannot carry your necklace."+
               " I will keep it for you, just come back and <get"+
               " necklace> whenever you want to.");
         }

         write("Bores gives you the necklace again. This item is now the"+
            " token of your membership of the guild.\n");
         if (TP->query_prop(LIVE_I_SMITH_ENTRANCE_QUEST))
            TP->remove_prop(LIVE_I_SMITH_ENTRANCE_QUEST);
    // logs the join
    log_guild(extract(ctime(time()), 4, 15) + " " +extract(ctime(time()), 21, 4)+" " + WRITE_NAME(TP) + " joined the " +
        "Blacksmiths.\n");


      }
   }
   else {
      TO->command("say I don't really see what I should do with this, "+
         name+".");
      TO->command("give "+item->query_name()+" to "+
         giver->query_real_name());
   }
   return 1;
}
