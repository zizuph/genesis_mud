   /* Bores Smithman - High Master Smith */

/*
 *
 * Had to hack the file for Mercade's "unworn" implementation
 *  - will be back to fix properly - Jaypeg May 00
 * Added age check to buy iron bars. player must be wanderer to join.
 * Really small players cause errors when forging necklace.
 * -- Finwe, July 2004
 */

#pragma save_binary;

inherit "/sys/global/money";
inherit "/std/monster";
inherit "/std/act/chat";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "../smiths.h"

#define WEP      SMITHSDIR_OBJ+"bo_axe"
#define BO_NECKLACE SMITHSDIR_OBJ+"npc_neck"
#define NECKLACE SMITHSDIR+"necklace"

int give();
void wield_me();
void equipped();
int pay(string str);

object item, giver;
int    check_on=0;

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

   set_name(({"bores","guild master"}));
   add_name("bores");
   set_title("High Master of the Smiths Guild");
   set_race_name("human");
   set_adj("grey");
   set_adj("wizened");
   set_long("This human must be at least sixty years old, but he is still"+
      " powerfully build and you do not think you would risk attacking him"+
      " .\nHe is also wearing mithril necklace studded with gems"+
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
      " must buy an iron bar from me, and forge a necklace from it. When you"+
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

   remove_prop(NPC_M_NO_ACCEPT_GIVE);

   set_alarm(1.0, 0.0, &wield_me());
}

void
init_living()
{
   ::init_living();
   add_action("pay", "pay");
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

/* bores is paid in order to get an iron bar
*/

int
pay(string str) {
   object ob;

   if ((str=="bores") || (str=="for iron bar")) 
   {
//        if(IS_MEMBER(TP))
//            return 1;

        if (TP->query_average_stat() < 55 && !IS_MEMBER(TP))
        {
            TO->command("say You are too young to join the Blacksmiths. " +
            "Come back when you are older.");
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

         TO->command("say It is a pleasure dealing with you.\nGood luck"+
            " with the forging.");
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
         if ((giver->query_guild_name_lay()==GUILD_NAME)
            || (giver->query_guild_name_occ()==GUILD_NAME)) {
            command("say But you are already a member of the Smiths Guild!");
            return 1;
         }

         if (giver->query_guild_name_lay()) {
            command("say But you are already a member of a layman guild!");
            return 1;
         }

         if (giver->query_race_name()=="goblin") {
            command("say I do not want to see your race in the smiths guild.");
            return 1;
         }

         shadow = clone_object(SMITHSDIR+"smiths_lay_shadow");

         if ((result = shadow->shadow_me(TP, "layman",
            GUILD_STYLE, GUILD_NAME)) != 1)
         {
				shadow->remove_shadow();
				write("There was an error, you are not able to join at this"+
				   " time.\nPlease make a bug report, error: " + result +
				   " on shadowing.\n");


            return 1;
         }

             /* new member of guild is accepted */
         giver->clear_guild_stat(SS_LAYMAN);
         giver->add_cmdsoul("/d/Shire/smiths/smiths_lay_soul");
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
