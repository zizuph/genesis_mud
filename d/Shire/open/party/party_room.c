/*
* OG coding by Demonlord in 2.4.5
* Adaptions and enhancements by Tricky & Cheiron in 2.4.5
* Rewritten in 3.0 by Nosferatu
* Modernized by Tricky, Jan '94.
*/

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <std.h>
#include "party.h"
#include "/d/Shire/common/defs.h"

#define ROCKET 0 /* Some ID's */
#define CRACKER 1
#define CHAMPAGNE 2

#define ROCKET_MAX 10 /* Maximum to sell in a party */
#define CRACKER_MAX 6
#define CHAMPAGNE_MAX 40

#define CHAMPAGNEPRICE  15/* Prices */
#define ROCKETPRICE     100
#define CRACKERPRICE    200

#define SPEECH_DELAY 5.0     /* used as call-out timer for the 'speech' cmd */

#define MIN_LEVEL WIZ_NORMAL      /* minimum level to start a party */

/* Following defs are to make the code a bit more understandable */

#define UNCUT 0
#define CUT 1

#define NOONE 0
#define EVERYONE 1
#define WIZARDS 2
#define DOMAIN 4
#define MORTALS 8
#define ROOM 16
#define HATS 4
#define HIN 64
#define KNIGHT 128
#define RANGER 256


object  speaker, party_host;
int cake, speech_arr_size, party_invitees, *sold;
string  xtra_room_desc, xtra_cake_desc, *speech_arr, party_reason;
string  party_host_name;

/* Prototypes */
void pay_and_receive(int price, string filename, string name);
void do_speech_in_alarm(int arrnum);
void invite_to_party(object obj, string domain);

void
create_room()
{
   set_short("party room");
   set_long("@@room_desc");
   
   add_item("table", break_string("It is a round table with a huge cake in "
         + "the middle and plenty of chairs around.\n", 70));
   add_item("cake", "@@cake_desc");
   add_item(({"butler", "demon"}), break_string("A well dressed demon going "
         + "around serving the guests. You discover that the demon's tail is "
         + "in fact a corkscrew... The demon will help you with a speech if "
         + "you want it to.\n", 70));
   add_item(({"corkscrew", "tail"}),
      "The demon's tail looks really weird.\n");
   add_item(({"Genesis", "genesis"}),
      "You see the world of Genesis far below.\n");
   add_item("cloud", "Being in the seventh heaven sure seems nice.\n");
   
   add_exit("@@exit_partyroom", "out");
   
   add_prop(ROOM_I_INSIDE, 0);
   add_prop(ROOM_I_TYPE, ROOM_IN_AIR);
   add_prop(OBJ_S_WIZINFO, break_string("You can start a party by getting "
         + "the partytool (tm) from the partytool dispenser in "
         + "~Shire/common/guild/hguild2. All code related to partying, "
         + "parties or partytime should be in ~Shire/open/party/", 60));
   
   xtra_room_desc = "This room is supposed to be empty, since no party is "
   +"booked.";
   xtra_cake_desc = "Don't you dare touch it!";
   cake = UNCUT;
   party_invitees = NOONE;
}

string
room_desc()
{
   string str;
   
   str = "You are high above Genesis floating around among the clouds. "
   + "There is a huge table on one of the biggest clouds. You can also "
   + "see the big party cake set on the table. Next to the table you "
   + "can see a well dressed demon with a bottle of champagne. "
   + xtra_room_desc
   + " Type 'help party' for more info.\n";
   
   return break_string(str, 70);
}

string
cake_desc()
{
   string str;
   
   str = "This is the biggest cream cake you have ever laid your eyes on! "
   + xtra_cake_desc;
   
   return break_string(str + "\n", 70);
}

string
exit_partyroom(object obj)   /* argument given by do_end_party() */
{
   object tool;
   string room;
   
   if (!obj)
      obj = this_player();
   
   tool = present(PARTY_TOOL_ID, obj);
   if (tool)
      {
      room = tool->query_return_to_room();
      tool->remove_object();
   }
   else
      room = obj->query_default_start_location();
   
   return room;
}

void
enter_inv(object ob, object from)
{
   object tool;
   
   while (environment(from))
   from = environment(from); 
   
   if (from == this_object()) 
      return;
   
   tool = present(PARTY_TOOL_ID, ob);
   
   if (!tool)
      {
      tool = clone_object(PARTY_TOOL);
      tool->move(ob);
   }
   tool->set_return_to_room(file_name(from));
}

void
leave_inv(object ob, object to)
{
   object tool;
   
   if (to == this_object())
      return;
   
   if (tool = present(PARTY_TOOL_ID, ob))
      tool->remove_object();
}

void
init()
{
   ::init();
   add_action("do_catch_say", "say");
   add_action("do_catch_say", "rsay");
   add_action("do_catch_say", "converse");
   add_action("do_catch_say", "shout");
   add_action("do_catch_get", "get");
   add_action("do_catch_get", "take");
   add_action("do_emote", "emote");
   add_action("do_emote", ":");
   add_action("do_announce", "announce");
   add_action("do_announce", "speak");
   add_action("do_announce", "speech");
   add_action("do_cut", "cut");
   add_action("do_order", "order");
   add_action("do_order", "buy");
   add_action("do_invite", "invite");
   add_action("do_help", "help");
   add_action("do_end_party", "end");
   add_action("do_end_party", "stop");
   add_action("do_not_kill", "kill");
   add_action("do_back","back");
}

int
do_catch_say()
{
   if (!speaker)
      return 0;
   
   this_player()->catch_msg("Sssssshhhhh!\n" + QTNAME(speaker)
      + " is giving a speech.\n");
   return 1;
}

int
do_catch_get(string str)
{
   if (str != "cake" && str != "piece")
      return 0;
   
   if (present("cake", this_object()))
      return 0;
   
   if (present("piece", this_object()))
      return 0;
   
   if (present("_cake_", this_player()))
      {
      write("You already have some.\n");
      return 1;
   }
   
   if (cake == UNCUT)
      {
      write("The cake isn't cut yet.\n");
      return 1;
   }
   
   write("You quickly get yourself a piece of the giant cake.\n");
   clone_object(PARTY_CAKE)->move(this_player());
   xtra_cake_desc = "People have started eating it."; 
   return 1;
}

int
do_emote(string str)           /* copied from /cmd/wiz_cmd_apprentice.c */
{
   if (speaker)
      {
      this_player()->catch_msg("Don't do that, " + (QTNAME(speaker)
            +" is giving a speech.\n", 70));
      return 1;
   }
   
   if (!str)
      {
      notify_fail("Emote what?\n");
      return 0;
   }
   
   say(({METNAME + " " + str + "\n", TART_NONMETNAME + " " + str + "\n"}));
   write("Ok.\n");
   return 1;
}

int
do_announce(string str)
{
   string *tmparr, *newarr;
   int i;
   
   if (speaker)
      {
      this_player()->catch_msg("You can't do that, " + QCTNAME(speaker)
         +" is already giving a speech.\n");
      return 1;
   }
   if (!str)
      {
      notify_fail("What do you wish to announce?\n");
      return 0;
   }
   if (strlen(str) < 50)
      {
      notify_fail("Don't you think that's a bit thin for a speech?\n");
      return 0;
   }
   speech_arr = explode(str, " | ");
   
   if (sizeof(speech_arr) == 1)
      speech_arr = explode(str, "|");
   
   newarr = ({ });
   
   for (i = 0; i < sizeof(speech_arr); i++)
   {
      str = speech_arr[i];
      if (strlen(str) > 42) tmparr = explode(break_string(str, 30), "\n");
      else tmparr = ({ str });
      newarr += tmparr;
   }
   speech_arr = newarr;
   speech_arr_size = sizeof(speech_arr);
   speaker = this_player();
   do_speech_in_alarm(0);
   return 1;
}

void
do_speech_in_alarm(int arrnum)
{
   string strMET, strNONMET;
   
   if (!speaker)
      return;
   
   strMET = break_string(speaker->query_name() + " announces: "
      + speech_arr[arrnum] + "\n", 70);
   strNONMET = break_string("The " + speaker->query_nonmet_name()
      +" announces: " + speech_arr[arrnum] + "\n", 70);
   tell_room(this_object(), ({strMET, strNONMET}));
   
   if (arrnum == speech_arr_size-1)
      {
      speaker = 0;
      return;
   }
   set_alarm(SPEECH_DELAY, 0.0, &do_speech_in_alarm(arrnum + 1));
}

int
do_cut(string str)
{
   if (str != "cake")
      return 0;
   
   if (cake == CUT)
      {
      write("It is already cut.\n");
      return 1;
   }
   
   write("You cut up big slices of cake for everyone.\n");
   say(QCTNAME(this_player()) + " cuts up the gigantic cake so everyone can "
      + "get a piece.\n");
   cake = CUT;
   xtra_cake_desc = "It has been cut up by " + this_player()->query_name()
   + ".";
   return 1;
}

int
do_order(string str)
{
   object item;
   string qob, txt;
   int doe;
   
   if (!str)
      {
      notify_fail("Order what?\n");
      return 0;
   }
   
   qob = this_player()->query_objective();
   doe = MONEY_MERGE(MONEY_COINS(this_player()));
   
   switch (str)
   {
      case "bottle":
      case "champagne":
      case "bottle of champagne":
      if (doe < CHAMPAGNEPRICE)
         {
         write("You can't afford it.\n");
         return 1;
         }
      
      if (sold[CHAMPAGNE] < CHAMPAGNE_MAX)
         {
         sold[CHAMPAGNE]++;
         write(break_string("You order a bottle of champagne from the "
               + "demon. The demon runs quickly to you and gives you a "
               + "bottle of champagne which he opens with his "
               + "corkscrewtail.\n", 70));
         
         txt = " orders a bottle of champagne from the demon. The demon "
         + "runs quickly to " + qob + " and gives " + qob
         + " a bottle of champagne which the demon opens with his "
         + "corkscrewtail.";
         say(({break_string(METNAME + txt + "\n", 70), break_string(
                     TART_NONMETNAME + txt + "\n", 70)}));
         tell_room(this_object(), "POOOOP!\n");
         tell_room(this_object(), break_string("The demon asks "
               + (CHAMPAGNEPRICE-5) + " for the bottle and an extra 5 for "
               + "opening it.\n", 70));
         write("You pay the demon what you owe him.\n");
         say(QCTNAME(this_player()) + " gives the demon some money.\n");
         pay_and_receive(CHAMPAGNEPRICE, PARTY_CHAMPAGNE,
            "bottle of champagne");
           }
      else
         {
         write("The demon whispers to you: Sorry, I am out of "
            + "champagne!\n");
         say("The demon whispers something to " + QTNAME(this_player())
            + ".\n");
           }
      return 1;
      
      case "rocket":
      if (doe < ROCKETPRICE)
         {
         write("You can't afford it.\n");
         return 1;
          }
      
      if (sold[ROCKET] < ROCKET_MAX)
         {
         sold[ROCKET]++;
         write("You buy yourself a fine rocket from the butler.\n");
         say(QCTNAME(this_player()) + " buys some firework from the "
            + "butler.\n");
         pay_and_receive(ROCKETPRICE, PARTY_ROCKET, "rocket");
        }
      else
         {
         write("The demon whispers to you: Sorry, I am out of "
            + "rockets!\n");
         say("The demon whispers something to " + QTNAME(this_player())
            + ".\n");
           }
      return 1;
      
      case "firecracker":
      case "cracker":
      case "firecrackers":
      case "crackers":
      if (doe < CRACKERPRICE)
         {
         write("You can't afford it.\n");
         return 1;
         }
      
      if (sold[CRACKER] < CRACKER_MAX)
         {
         sold[CRACKER]++;
         write("You buy yourself some firework from the butler.\n");
         say(QCTNAME(this_player()) + " buys some firework from the "
            + "butler.\n");
         pay_and_receive(CRACKERPRICE, PARTY_CRACKER, "string of crackers");
           }
      else
         {
         write("The demon whispers to you: I'm out of those noisy "
            + "crackers, a good thing too!\n");
         say("The demon whispers something to " + QTNAME(this_player())
            + ".\n");
           }
      return 1;
      
      case "cake":
      case "piece of cake":
      write("The demon whispers to you: The cake is on " + party_host_name
         + ".\n");
      say("The demon whispers something to " + QTNAME(this_player())
         + ".\n");
      return 1;
      
      default:
      write("The demon-butler doesn't seem to be selling those.\n");
      return 1;
   }
}

/*
* Function name:   pay_and_receive
* Description:    Make the player pay for an item, and give the item back.
*    This function is called by do_order().
* Arguments:    price: The price to pay
*    filename: The filename of the item to clone
*    name: The name of the item.
*/ 
void
pay_and_receive(int price, string filename, string name)
{
   object obj;
   
   MONEY_ADD(this_player(), -price);
   obj = clone_object(filename);
   
   if (obj->move(this_player()))
      {
      write("You drop the " + name + ".\n");
      obj->move(environment(this_player()));
   }
}

int
do_invite(string str)
{
   object ob, tool;
   string whos;
   
   if (!str)
      {
      notify_fail("Invite who?\n");
      return 0;
   }
   
   ob = find_player(str);
   
   if (!ob)
      {
      notify_fail("No such player.\n");
      return 0;
   }
   
   write("You send " + ob->query_name() + " an invitation.\n");
   
   if (this_player() == party_host)
      whos = party_host->query_possessive();
   else
      whos = party_host_name + "'s";
   
   ob->catch_msg(break_string("You are personally invited by "
         + process_string(QNAME(this_player())) + " to join " + whos
         + " party. Type 'party' within " + DECISION_TIME + " minutes to "
         + "join it.\n", 70));
   
   tool = clone_object(PARTY_TOOL);
   tool->set_selfdestruct_timer(DECISION_TIME);
   tool->move(ob);
   return 1;
}

int
do_help(string str)
{
   if (str == "party")
      {
      write("Welcome to " + party_host_name + "'s party! Try these:\n"
         + "  emote <str>\n"
         + "  buy <champagne|rocket|firecracker>\n"
         + "  cut cake\n"
         + "  get <cake>\n"
         + "  invite <player>\n"
         + "  announce|speak|speech <str>\n"
         + "    you can force a newline with a '|'\n\n"
         + "Other nice commands:\n"
         + " If you have a champagne bottle: cheer <player|all>\n"
         + " If you have a cake: throw cake at <player>\n"
         + " If you don't want to catch a cake, you should try to duck.\n"
         + " The champagne and the cake can of course be consumed too.\n\n"
       + "In case of catastrophe, and the exit 'out' no longer \n"
       + "exists, the command 'back' will put you where you should \n"
       + "go.\n"
         + "Additional help can be obtained about these subjects:\n"
         + "  'demon' and 'announce'\n"
         + "Oh, " + party_host_name + " can also do 'end party' to end "
         + "this party.\n");
      return 1;
   }
   if (str == "demon" || str == "butler" || str == "speech" || str == "speak" ||
         str == "announce")
   {
      write("The demon whispers to you:\n"
         + " type 'speak line1 | line2 | ...'. The message will be divided up"
         + " into 3 parts. The line will be split at a '|' sign.\n"
         + "Example:\n"
         + "     announce Congratulations " + party_host_name
         + ". | Let's hope you'll be | a good wiz.\n"
         + "will be split up into:\n"
         + "     You announce: Congratulations " + party_host_name + ".\n"
         + "     You announce: Lets hope you'll be\n"
         + "     You announce: a great wiz.\n\n"
         + "The messages will be printed with some seconds interval, during\n"
         + "     which everyone else will be forced to be quiet.\n\n"
         + "Oh yes, here is the pricelist of the items you can buy:\n"
         + "  Champagne:    " + CHAMPAGNEPRICE + "\n"
         + "  Rocket:       " + ROCKETPRICE    + "\n"
         + "  Firecrackers: " + CRACKERPRICE   + "\n\n");
      say("The demon whispers something to " + QTNAME(this_player()) + ".\n");
      return 1;
   }
   return 0;
}

int
do_end_party(string str)
{
   object *obs, ob;
   string home;
   int i;
   
   if (str != "party")
      {
      notify_fail("Please give 'party' as argument to avoid any confusion.\n");
      return 0;
   }
   
   if (party_host && this_player() != party_host)
      {
      write("Only the creator of this party can end it.\n");
      return 1;
   }
   
   if (!party_host && WIZ_CHECK < MIN_LEVEL)
      {
      write("Sorry, but you have to be a wizard to end a party.\n");
      return 1;
   }
   
   tell_room(this_object(), "The party is over.\n");
   obs = deep_inventory(this_object());
   
   for (i = 0; i < sizeof(obs); i++)
   if (living(obs[i]) && (home = exit_partyroom(obs[i])))
      obs[i]->move_living("X", home);
   
   party_host = 0;
   obs = users();
   
   for (i = 0; i < sizeof(obs); i++)
   if (ob = present(PARTY_TOOL_ID, obs[i]))
      ob->remove_object();
   
   return 1;
}

/*
* This function is called externally   (by the PartyTool(tm))
*/

void
start_the_party()
{
   object *obs;
   int i;
   
   /* Test whether the party can be started */
   if (!(this_player()->query_wiz_level() ||
            (this_player()->test_bit("Shire", 0, 0) == 1 &&
            this_player()->query_base_stat(SS_LAYMAN) > 70)))
   {
      write("You have to be a high-level Hin Warrior or wizard to start a "
         + " party.\n");
      return;
   }
   
   if (party_host)
      {
      obs = deep_inventory(this_object());
      
      if (obs && sizeof(obs))
         {
         for (i = 0; i < sizeof(obs); i++)
         {
            if (interactive(obs[i]))
               {
               write("There is already a party going on, the partyroom "
                  + "is occupied.\n");
               return;
              }
          }
       }
   }
   
   /* Wizards can choose everything; Hins cannot. */
   if (this_player()->query_wiz_level())
      {
      write("For who do you wish to have the party? Choose one or more of:\n"
         + "   Everyone   - every player\n"
         + "   Wizards    - every wizard\n"
         + "   Domain     - the wizards in your domain\n"
         + "   Mortals    - every mortal\n"
         + "   Room       - all players in this room\n"
         + "   Hats       - all players carrying an object with id: party_hat\n"
         + "                don't forget to invite these, they're hilarious!\n"
         + "   Hin        - all members of the Hin Warrior guild\n"
         + "   Knight     - all members of the Solamnian Knight guild\n"
         + "   Ranger     - all members of the Gondorian Ranger guild\n\n"
         + "Separate choices with '&'.\n\n");
   }
   else
      {
      write("For who do you wish to have the party? Choose one or more of:\n"
         + "   Room       - all players in this room\n"
         + "   Hats       - all players carrying an object with id: party_hat\n"
         + "                don't forget to invite these, they're hilarious!\n"
         + "   Hin        - all members of the Hin Warrior guild\n"
         + "Separate choices with '&'.\n\n");
   }
   write("~q to abort> ");
   input_to("start_the_party2");
}

void
start_the_party2(string str)
{
   string *list;
   int i;
   
   if (str == "~q")
      {
      write("Aborting...\n");
      return;
   }
   
   if (str && str != "")
      {
      str = lower_case(str);
      list = explode(str, " & ");
      
      if (sizeof(list) == 1)
         list = explode(str, "&");
   }
   
   if (list && sizeof(list))
      {
      party_invitees = NOONE;
      
      for (i = 0; i < sizeof(list); i++)
      {
         switch (list[i])
         {
            case "everyone":
            if (this_player()->query_wiz_level())
               party_invitees |= EVERYONE;
            else
               {
               write("Invalid choice: '" + list[i] + "'.\n");
               write("Please choose again...\n");
               write("~q to abort> ");
               input_to("start_the_party2");
            }
            break;
            case "wizards":
            if (this_player()->query_wiz_level())
            party_invitees != WIZARDS;
            else
               {
               write("Invalid choice: '" + list[i] + "'.\n");
               write("Please choose again...\n");
               write("~q to abort> ");
               input_to("start_the_party2");
              }
            break;
            case "domain":
            if (this_player()->query_wiz_level())
            party_invitees != DOMAIN;
            else
               {
               write("Invalid choice: '" + list[i] + "'.\n");
               write("Please choose again...\n");
               write("~q to abort> ");
               input_to("start_the_party2");
                    }
            break;
            case "mortals":
            if (this_player()->query_wiz_level())
            party_invitees != MORTALS;
            else
               {
               write("Invalid choice: '" + list[i] + "'.\n");
               write("Please choose again...\n");
               write("~q to abort> ");
               input_to("start_the_party2");
                  }
            break;
            case "room":
                party_invitees != ROOM;
            break;
            case "hats":
            party_invitees != HATS;
            break;
            case "hin":
            party_invitees |= HIN;
            break;
            case "knight":
            if (this_player()->query_wiz_level())
               party_invitees |= KNIGHT;
            else
               {
               write("Invalid choice: '" + list[i] + "'.\n");
               write("Please choose again...\n");
               write("~q to abort> ");
               input_to("start_the_party2");
                }
            break;
            case "ranger":
            if (this_player()->query_wiz_level())
             party_invitees != RANGER;
            else
               {
               write("Invalid choice: '" + list[i] + "'.\n");
               write("Please choose again...\n");
               write("~q to abort> ");
               input_to("start_the_party2");
                }
            break;
            default:
            write("Invalid choice: '" + list[i] + "'.\n");
            write("Please choose again...\n");
            write("~q to abort> ");
            input_to("start_the_party2");
            return;
           }
       }
   }
   else
      {
      write("~q to abort> ");
      input_to("start_the_party2");
      return;
   }
   write("Please enter the reason for the party by continuing the following "
      +"sentence:\nThis party was created by " + this_player()->query_name()
      +" because...\n(don't forget punctuation...)\n");
   write("~q to abort> ");
   input_to("start_the_party3");
}

void
start_the_party3(string str)
{
   object *obs, tool;
   string sl, domain;
   int i;
   
   if (!str || str == "")
      {
      write("~q to abort> ");
      input_to("start_the_party3");
      return;
   }
   
   if (str == "~q")
      {
      write("Aborting...\n");
      return;
   }
   
   /*
   * Finally, we can start up the party.
   * First we invite everyone that has to be invited.
   */
   party_reason = str;
   
   if (tool = present(PARTY_TOOL_ID, this_player()))
      tool->remove_object();
   
   xtra_room_desc = "This party was created by "
   + this_player()->query_name() + " because " + party_reason;
   xtra_cake_desc = "Noone has touched it yet.";
   cake = UNCUT;
   sold = ({ 0, 0, 0 });
   speaker = 0;
   party_host = this_player();
   party_host_name = this_player()->query_name();
   obs = deep_inventory(this_object());
   log_file(PARTY_LOG, ctime(time()) + ", by " + party_host_name
      + "(" + party_host->query_wiz_level() +  ") for "
      + party_reason + ".\n");
   
   if (obs && sizeof(obs))
      {
      for (i = 0; i < sizeof(obs); i++)
      {
         sl = obs[i]->query_default_start_location();
         if (sl)
            {
            obs[i]->catch_msg("A party is starting right now: "
               + "moving you out.\n");
            if (!obs[i]->move(sl))
               obs[i]->remove_object();
           }
         else
            obs[i]->remove_object();
       }
   } 
   
   domain = SECURITY->query_wiz_dom(party_host->query_real_name());
   
   if (domain)
      {
      obs = filter(users(), "invited_filter", this_object(), domain);
      
      for (i = 0; i < sizeof(obs); i++)
      invite_to_party(obs[i], domain);
   }
}

/*
* The following functions are to determine if someone is a member of a
   * certain guild.
*/

int
is_HIN_member(object ob)
{
   return ob->test_bit("Shire", 0, 0);
}

int
is_KNIGHT_member(object ob)
{
   return ob->test_bit("Krynn", 1, 0);
}

int
is_RANGER_member(object ob)
{
   if (ob->query_guild_member("Gondorian Rangers Guild"))
      return 1;
   if (ob->query_wiz_level() < 1)
      return 0;
   if (present("ranger_ring", ob))
      return 1;
   return 0;
}

/*
* Function name:   invited_filter
* Description:    Check if someone is invited for a party.
   * Arguments:    obj: The player_object to check.
*    domain: The domain of the party_host.
* Returns:    1 if invited, 0 if not invited.
   */
int
invited_filter(object obj, string domain)
{
   if (obj == this_player())
      return 1;
   
   if (party_invitees & EVERYONE)
      return 1;
   
   if ((party_invitees & WIZARDS) &&
         SECURITY->query_wiz_rank() > WIZ_MORTAL)
   return 1;
   
   if ((party_invitees & DOMAIN) && (domain == 
            SECURITY->query_wiz_dom(obj->query_real_name())))
   return 1;
   
   if ((party_invitees & MORTALS) &&
         SECURITY->query_wiz_rank() == WIZ_MORTAL)
   return 1;
   
   if ((party_invitees & ROOM) &&
         (environment(obj) == environment(party_host)))
   return 1;
   
   if ((party_invitees & HATS) && present(PARTY_HAT_ID, obj))
      return 1;
   
   if ((party_invitees & HIN) && is_HIN_member(obj))
      return 1;
   
   if ((party_invitees & KNIGHT) && is_KNIGHT_member(obj))
      return 1;
   
   if ((party_invitees & RANGER) && is_RANGER_member(obj))
      return 1;
   
   return 0;
}

/*
* invite_to_party() is called by start_the_party3()
*/
void
invite_to_party(object obj, string domain)
{
   object tool;
   string *txt, msg;
   int i;
   
   msg = "";
   txt = ({ });
   
   if (party_invitees & EVERYONE)
      msg = "everyone in Genesis";
   else
      {
      if (party_invitees & WIZARDS)
         txt += ({ "all wizards", "all apprentices" });
      
      if (party_invitees & DOMAIN)
         {
         if (domain == SECURITY->query_wiz_dom(obj->query_real_name()))
            txt += ({ "all members of your domain" });
         else
            txt += ({ "all members of the domain " + domain });
      }
      
      if (party_invitees & MORTALS)
         txt += ({ "all mortals" });
      
      if (party_invitees & ROOM)
         {
         if (environment(party_host) == environment(obj))
            txt += ({ "everyone in this room" });
         else
            txt += ({ "everyone on the same room as " + party_host_name });
      }
      
      if (party_invitees & HATS)
         txt += ({ "all funny guys 'n gals" });
      
      if (party_invitees & HIN)
         txt += ({ "all members of the Hin Warrior guild" });
      
      if (party_invitees & KNIGHT)
         txt += ({ "all members of the Solamnian Knight guild" });
      
      if (party_invitees & RANGER)
         txt += ({ "all members of the Gondorian Ranger guild" });
      
      if (sizeof(txt) == 1)
         msg = txt[0];
      
      if (sizeof(txt) == 1)
         msg = txt[0];
      else
         msg = implode(txt[0..sizeof(txt)-2], ", ") + " and "
      + txt[sizeof(txt)-1];
   }
   obj->catch_msg(break_string("A party for " + msg
         + " has been created by " + party_host_name
         + " because " + party_reason + " Type 'party' within " + DECISION_TIME
         +" minutes to join it.\n", 70));
   tool = clone_object(PARTY_TOOL);
   tool->set_selfdestruct_timer(DECISION_TIME);
   tool->move(obj);
}

int
do_not_kill()
{
   
   int damage;
   if(!TP->query_prop("i_tried_to_kill_at_the_party"))
      {
      TP->catch_msg("The demon glares at you, noticing "+
         "telepathically what you are thinking of. You feel "+
         "quite certain that if you go through with an attack "+
         "you have no chance of surviving, for the demon will "+
         "undoubtedly hurl you from the cloud.\n");
      
      say(QCTNAME(TP)+ " looks quite malicious for a moment, "+
         "then calms down somewhat.\n");
      
      TP->add_prop("i_tried_to_kill_at_the_party",1);
      return 1;
   }
   
   if(TP->query_prop("i_tried_to_kill_at_the_party"))
      {
      
      damage = TP->query_max_hp();
      write("You were warned.\n");
      say("The demon growls at "+QCTNAME(TP)+ " and hurls "+
         HIM_HER(TP)+" from the cloud, providing a "+
         "certain death.\n");
      
      write("The demon picks you up, and with a gargantuan "+
         "growl hurls you from the cloud.\n");
      write("You tumble for what seems like forever, until "+
         "you make a sudden deceleration and your life "+
         "is plucked from your body by the insane force of gravity.\n");
      
      TP->move_living("M","/d/Shire/mountain/path/rock",0);
      TP->heal_hp(-damage);
      TP->do_die();
      return 1;
   }
}

int
do_back()
{
   object home;

   if(!TP->query_prop("_player_transed_from"))
     home = TP->query_prop(LIVE_O_LAST_ROOM);
   else home = TP->query_prop("_player_transed_from");

   TP->move_living("M",home,0);
   return 1;
}
