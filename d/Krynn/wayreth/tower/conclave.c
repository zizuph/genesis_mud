/*
   Wayreth.

   conclave.c
   ----------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : October 2016
   By ...........: Arman

*/

#include <macros.h>
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/guilds/wohs/defs.h"

inherit "/lib/commands";
inherit TOWERROOM;

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define WOFFICE  WTOWER + "whitestudy"
#define ROFFICE  WTOWER + "redstudy"
#define BOFFICE  WTOWER + "blackstudy"
#define WHITE_ENTER "_i_may_enter_white"
#define RED_ENTER   "_i_may_enter_red"
#define BLACK_ENTER "_i_may_enter_black"
#define LEADER_LOG ("/d/Krynn/guilds/wohs/logs/wohs_conclave")

int check_whitehead();
int check_redhead();
int check_blackhead();

object board;

string
white_head_desc()
{
  if(!WOHS_MANAGER->query_is_council_white())
    return "the Master of the White Robed Mages.";
  else
    return capitalize(WOHS_MANAGER->query_is_council_white())+ ", Head " +
      "of the Order of the White Robed Mages.";
}

string
red_head_desc()
{
  if(!WOHS_MANAGER->query_is_council_red())
    return "the Master of the Red Robed Mages.";
  else
    return capitalize(WOHS_MANAGER->query_is_council_red())+ ", Head " +
      "of the Order of the Red Robed Mages.";
}

string
black_head_desc()
{
  if(!WOHS_MANAGER->query_is_council_black())
    return "the Master of the Black Robed Mages.";
  else
    return capitalize(WOHS_MANAGER->query_is_council_black())+ ", Head " +
      "of the Order of the Black Robed Mages.";
}

void
create_tower_room()
{
    set_short("Conclave board room and lobby");
    set_long("This is the area of the conclave of the mages of Wayreth. " +
        "Here the masters of the three Orders of mages have " +
        "their private studies. White is to the north, Red is " +
        "to the west, and Black is to the south. A levitating tablet " +
        "spins lazily here in the middle of the room that you could " +
        "examine for more information. A coloured bell cord hangs in " +
        "front of each of the three offices of the Wayreth conclave and " +
        "an exit leads east to the stairwell.\n");

    AI(({"spectres","powerful spectres","spectre","guardian",
        "subtle spectres"}), "Though you can't see them, you have no " +
        "doubt that they'll make their presence known should you " +
        "attempt to enter an office unbidden.\n");

    AI(({"tablet","levitating tablet"}),
        "In the middle of the room floats a tablet, suspended in the " +
        "air through levitation magicks. The tablet explains a number " +
        "of the commands you can use in this room:\n" +
        "         <check> who the current Conclave are or check their " +
        "activity,\n         <wohscheck> an alternative to the check command," +
        "\n         <indict> inactive Conclave members of your " +
        "Order,\n         <petition> to change Orders.\n\n" +
        "When a vote is called for the next Head of your Order, you " +
        "may:\n         <nominate> yourself as a participant in the " +
        "ballot for the Head of the Order,\n         <retract> your " +
        "nomination from a vote,\n         <list> current nominations " +
        "for the Head of your Order,\n         <vote> for a nominated " +
        "participant to be the next Head of your Order.\n\n"); 

    AI(({"coloured cord","cord","cords","bell cord","bell cords",
        "coloured bell cords"}),
        "Which bell cord? The white, red, or black cord?\n");
    AI(({"white cord","white bell cord","silk"}),
        "Pull this cord, made of thick, pure white silk, to ring the " +
        "bell inside the office of @@white_head_desc@@\n");
    AI(({"red cord","red bell cord","satin"}),
        "Pull this cord, made of thick, vibrant crimson satin, to ring " +
        "the bell inside the office of @@red_head_desc@@\n");
    AI(({"black cord","black bell cord"}),
        "Pull this cord, made of thick, deep midnight velvet, to ring " +
        "the bell inside the office of @@black_head_desc@@\n");
    ACI(({"white","white cord","white bell cord"}),"pull", 
        "@@do_pullwhite");
    ACI(({"red","red cord","red bell cord"}),"pull", "@@do_pullred");
    ACI(({"black","black cord","black bell cord"}),"pull", 
        "@@do_pullblack");
    ACI(({"tablet","levitating tablet"}),"read",
        "In the middle of the room floats a tablet, suspended in the air " +
        "through levitation magicks. The tablet explains a number of the " +
        "commands you can use in this room:\n         <check> who the " +
        "current Conclave are or check their activity,\n" +
        "         <wohscheck> an alternative to the check command,\n" +
        "         <indict> inactive Conclave members of your Order,\n" +
        "         <petition> to change Orders.\n\n" +
        "When a vote is called for the next Head of your Order, you " +
        "may:\n         <nominate> yourself as a participant in the " +
        "ballot for the Head of the Order,\n         <retract> your " +
        "nomination from a vote,\n         <list> current nominations " +
        "for the Head of your Order,\n         <vote> for a nominated " +
        "participant to be the next Head of your Order.\n\n");

    add_exit(WTOWER + "stairwell08", "east", 0);
    add_exit(WTOWER + "whitestudy", "north", check_whitehead);
    add_exit(WTOWER + "blackstudy", "south", check_blackhead);
    add_exit(WTOWER + "redstudy", "west", check_redhead);

    board = clone_object(WOBJ + "conclave_board");
    board->move(this_object());
}

int
do_pullwhite()
{
    write("You pull the white bell cord and a faint ringing is " +
      "heard in the office to the north.\n");
    say( QCTNAME(TP)+" pulls the white bell cord and a " +
      "faint ringing is heard in the office to the north.\n");
    tell_room(WOFFICE,"A bell materializes above the door and " +
      "rings, signaling that someone is outside and wishing " +
      "for your attention.\n");
    return 1;
}

int
do_pullred()
{
    write("You pull the red bell cord and a faint ringing is " +
      "heard in the office to the west.\n");
    say( QCTNAME(TP)+" pulls the red bell cord and a " +
      "faint ringing is heard in the office to the west.\n");
    tell_room(ROFFICE,"A bell materializes above the door and " +
      "rings, signaling that someone is outside and wishing " +
      "for your attention.\n");
    return 1;
}

int
do_pullblack()
{
    write("You pull the black bell cord and a faint ringing is " +
      "heard in the office to the south.\n");
    say( QCTNAME(TP)+" pulls the black bell cord and a " +
      "faint ringing is heard in the office to the south.\n");
    tell_room(BOFFICE,"A bell materializes above the door and " +
      "rings, signaling that someone is outside and wishing " +
      "for your attention.\n");
    return 1;
}

int
check_whitehead()
{

    if(WOHS_MANAGER->query_is_council_white() == TP->query_real_name())
        return 0;
    if (TP->query_prop(WHITE_ENTER))
        return 0;
    if (TP->query_wiz_level())
        return 0;
    if (!TP->query_prop(WHITE_ENTER))
    {
        write("A powerful and ghastly spectral guardian appears before " +
          "you and with a single, freezing touch " +
          "halts all thoughts of entering the office of the Head " +
          "of the White Robed Wizards.\n");
        say("A powerful and ghastly spectral guardian appears before "+
          QTNAME(TP)+ " and with a touch halts all thoughts of " +
          "continuing north.\n");
        return 1;
    }
}

int
check_redhead()
{

    if(WOHS_MANAGER->query_is_council_red() == TP->query_real_name())
        return 0;
    if (TP->query_prop(RED_ENTER))
        return 0;
    if (TP->query_wiz_level())
        return 0;
    if (!TP->query_prop(RED_ENTER))
    {
        write("A powerful and ghastly spectral guardian appears before " +
          "you and with a single, freezing touch " +
          "halts all thoughts of entering the office of the Head " +
          "of the Red Robed Wizards.\n");
        say("A powerful and ghastly spectral guardian appears before "+
          QTNAME(TP)+ " and with a touch halts all thoughts of " +
          "continuing west.\n");
        return 1;
    }
}

int
check_blackhead()
{

    if(WOHS_MANAGER->query_is_council_black() == TP->query_real_name())
        return 0;
    if (TP->query_prop(BLACK_ENTER))
        return 0;
    if (TP->query_wiz_level())
        return 0;
    if (!TP->query_prop(BLACK_ENTER))
    {
        write("A powerful and ghastly spectral guardian appears before " +
          "you and with a single, freezing touch " +
          "halts all thoughts of entering the office of the Head " +
          "of the Black Robed Wizards.\n");
        say("A powerful and ghastly spectral guardian appears before "+
          QTNAME(TP)+ " and with a touch halts all thoughts of " +
          "continuing south.\n"); 
        return 1;
    }
}

void
init()
{
    ADD("grant_person", "permit");
    ADD("grant_person", "grant");
    ADD("remit_person", "remit");
    ADD("remit_person", "revoke");
    ADD("check_council", "check");
    ADD("check_council", "wohscheck");
    ADD("indict_council", "indict");
    ADD("change_order", "petition");
    ADD("nominate_for_council","nominate");
    ADD("unnominate_for_council","retract");
    ADD("list_nominations", "list");
    ADD("vote_for_council","vote");
    ::init();
}

string
time_message(int time)
{
   if(time < 1800)
     return "less than half an hour";
   else if(time < 3600)
     return "less than an hour";
   else if(time < 7200)
     return "approximately one hour";
   else if(time < 172800)
   {
     int hours = time / 3600;
     return "approximately " +hours+ " hours";
   }
   else
   {
     int days = time / 86400;
     return "approximately " +days+ " days";
   }
}


int
check_council(string str)
{
   str = lower_case(str);

   int last_login_white, last_login_red, last_login_black, white_time, 
       red_time, black_time;

   int annual_white = WOHS_MANAGER->query_next_annual_council_vote("white") 
       - time();
   int annual_red = WOHS_MANAGER->query_next_annual_council_vote("red") 
       - time();
   int annual_black = WOHS_MANAGER->query_next_annual_council_vote("black") 
       - time();

   string white_msg, red_msg, black_msg, white_name, red_name, black_name;

   if(!str || (str != "the activity of the conclave" && 
       str != "the current conclave" && str != "activity of the conclave" &&
       str != "current conclave"))
   {
      NF("Check what? The activity of the conclave? Or the current " +
        "conclave?\n");
      return 0;
    }

   if(str == "the current conclave" || str == "current conclave")
   {
      if(!WOHS_MANAGER->query_is_council_white())
      {
         white_name = "There is currently no Head of the Order of the " +
             "White Robes.\n";

         if(WOHS_MANAGER->count_wohs_order_members("white") == 0)
         {
           white_name += "There are no members of the Order of the White " +
               "Robes, so no elections are planned to be held.\n";
         }
         else if(WOHS_MANAGER->query_council_voting_open("white") > 0)
         {
           white_name += "A ballot for the election of the Head of the " +
               "Order of the White Robes is currently taking place, " +
               "closing in " +
               time_message(WOHS_MANAGER->query_council_voting_open("white") - time())+ 
               ".\n";
         }
      }
      else 
      {
         white_name = "The Head of the Order of the White Robes is " +
                      C(WOHS_MANAGER->query_is_council_white())+ ".\n";

         if(WOHS_MANAGER->query_council_voting_open("white") > 0)
         {
           white_name += "A ballot for the election of the Head of the " +
               "Order of the White Robes is currently taking place, " +
               "closing in " +
               time_message(WOHS_MANAGER->query_council_voting_open("white") - time())+ 
               ".\n";
         }
         else
         {
           white_name += "The next annual election for the Order of the " +
               "White Robes is due to commence in " +
               time_message(annual_white)+ ".\n";
           DEBUG("Annual white time: " +annual_white+ ".");
         }
      }

      if(!WOHS_MANAGER->query_is_council_red())
      {
         red_name = "There is currently no Head of the Order of the Red " +
             "Robes.\n";

         if(WOHS_MANAGER->count_wohs_order_members("red") == 0)
         {
           red_name += "There are no members of the Order of the Red " +
               "Robes, so no elections are planned to be held.\n";
         }
         else if(WOHS_MANAGER->query_council_voting_open("red") > 0)
         {
           red_name += "A ballot for the election of the Head of the " +
               "Order of the Red Robes is currently taking place, " +
               "closing in " +
               time_message(WOHS_MANAGER->query_council_voting_open("red") - time())+ 
               ".\n";
         }
      }
      else 
      {
         red_name = "The Head of the Order of the Red Robes is " +
                      C(WOHS_MANAGER->query_is_council_red())+ ".\n";

         if(WOHS_MANAGER->query_council_voting_open("red") > 0)
         {
           red_name += "A ballot for the election of the Head of the " +
               "Order of the Red Robes is currently taking place, " +
               "closing in " +
               time_message(WOHS_MANAGER->query_council_voting_open("red") - time())+ 
               ".\n";
         }
         else
           red_name += "The next annual election for the Order of the " +
               "Red Robes is due to commence in " +
               time_message(annual_red)+ ".\n";
      }

      if(!WOHS_MANAGER->query_is_council_black())
      {
         black_name = "There is currently no Head of the Order of the " +
             "Black Robes.\n";

         if(WOHS_MANAGER->count_wohs_order_members("black") == 0)
         {
           black_name += "There are no members of the Order of the Black " +
               "Robes, so no elections are planned to be held.\n";
         }
         else if(WOHS_MANAGER->query_council_voting_open("black") > 0)
         {
           black_name += "A ballot for the election of the Head of the " +
               "Order of the Black Robes is currently taking place, " +
               "closing in " +
               time_message(WOHS_MANAGER->query_council_voting_open("black") - time())+ 
               ".\n";
         }
      }
      else 
      {
         black_name = "The Head of the Order of the Black Robes is " +
                      C(WOHS_MANAGER->query_is_council_black())+ ".\n";

         if(WOHS_MANAGER->query_council_voting_open("black") > 0)
         {
           black_name += "A ballot for the election of the Head of the " +
               "Order of the Black Robes is currently taking place, " +
               "closing in " +
               time_message(WOHS_MANAGER->query_council_voting_open("black") - time())+ 
               ".\n";
         }
         else
           black_name += "The next annual election for the Order of the " +
               "Black Robes is due to commence in " +
               time_message(annual_black)+ ".\n";
      }

      write(white_name +"\n"+ red_name +"\n"+ black_name);
      say(QCTNAME(TP)+ " checks who the current Conclave of High " +
          "Sorcery are.\n"); 
      WOHS_STARTROOM->check_all_wohs_council_votes();
   
      return 1;
   }

   if(!WOHS_MANAGER->query_is_council_white())
      white_msg = "There is currently no Head of the Order of the White " +
          "Robes.\n";
   else
   {
      last_login_white = time() - 
          WOHS_MANAGER->query_council_last_login("white");
      white_msg = "The Head of the Order of the White Robes last " +
          "entered the realms " +time_message(last_login_white)+ " ago.\n";
   }
   if(!WOHS_MANAGER->query_is_council_red())
      red_msg = "There is currently no Head of the Order of the Red " +
          "Robes.\n";
   else
   {
      last_login_red = time() - 
          WOHS_MANAGER->query_council_last_login("red");
      red_msg = "The Head of the Order of the Red Robes last entered " +
          "the realms " +time_message(last_login_red)+ " ago.\n";
   }
   if(!WOHS_MANAGER->query_is_council_black())
      black_msg = "There is currently no Head of the Order of the Black " +
          "Robes.\n";
   else
   {
      last_login_black = time() - 
          WOHS_MANAGER->query_council_last_login("black");
      black_msg = "The Head of the Order of the Black Robes last entered " +
          "the realms " +time_message(last_login_black)+ " ago.\n";
   }

   write(white_msg + red_msg + black_msg);
   say(QCTNAME(TP)+ " checks the activity of the Conclave of High " +
       "Sorcery.\n"); 
   
   return 1;
}

int
indict_council(string str)
{
   str = lower_case(str);

   // 22 days a council member can be inactive before being able to be 
   // indicted... 86400 is one day, 1950080 is 22 days

   int indictment_time = 1950080;
   string order = QUERY_WOHS_ROBE(TP);

   if(!str || str != "member of the conclave")
   {
      NF("Indict member of the conclave?\n");
      return 0;
   }

   if(order == "white")
   {
      if(WOHS_MANAGER->query_council_property("council_white_last_login") > 
          indictment_time)
      {
         write("The Head of the Order of the White Robes has been " +
             "active within the last 22 days. You have no indictment " +
             "grounds until the 22 days inactivity has been exceeded.\n");
         return 1;
      }
      write("You indict " +capitalize(WOHS_MANAGER->query_is_council_white())+ 
          " for being inactive for over 22 days. The position of the " +
          "Head of the Order of the White Robes is now vacant.\n");
      say(QCTNAME(TP)+ " indicts " +
          capitalize(WOHS_MANAGER->query_is_council_white())+ 
          " for being inactive for over 22 days. The position of Head " +
          "of the Order of the White Robes is now vacant.\n");
      WOHS_MANAGER->remove_council_white();

      return 1;
   }

   if(order == "red")
   {
      if(WOHS_MANAGER->query_council_property("council_red_last_login") > 
          indictment_time)
      {
         write("The Head of the Order of the Red Robes has been active " +
             "within the last 22 days. You have no indictment grounds " +
             "until the 22 days inactivity has been exceeded.\n");
         return 1;
      }
      write("You indict " +capitalize(WOHS_MANAGER->query_is_council_red())+
          " for being inactive for over 22 days. The position of the " +
          "Head of the Order of the Red Robes is now vacant.\n");
      say(QCTNAME(TP)+ " indicts " +
          capitalize(WOHS_MANAGER->query_is_council_red())+ 
          " for being inactive for over 22 days. The position of Head " +
          "of the Order of the Red Robes is now vacant.\n");
      WOHS_MANAGER->remove_council_red();

      return 1;
   }

   if(order == "black")
   {
      if(WOHS_MANAGER->query_council_property("council_black_last_login") >
          indictment_time)
      {
         write("The Head of the Order of the Black Robes has been " +
             "active within the last 22 days. You have no indictment " +
             "grounds until the 22 days inactivity has been exceeded.\n");
         return 1;
      }
      write("You indict " +capitalize(WOHS_MANAGER->query_is_council_black())+ 
          " for being inactive for over 22 days. The position of the " +
          "Head of the Order of the Black Robes is now vacant.\n");
      say(QCTNAME(TP)+ " indicts " +
          capitalize(WOHS_MANAGER->query_is_council_black())+ 
          " for being inactive for over 22 days. The position of Head " +
          "of the Order of the Black Robes is now vacant.\n");
      WOHS_MANAGER->remove_council_black();

      return 1;
   }

    write("You are not aligned to an Order, so cannot indict any of " +
        "the current Conclave.\n");
    return 1;
}

/* A function that allows conclave members to allow others into their
 * offices
 */

int
grant_person(string str)
{
    object target;

    NF("Wizards should add the prop if they deem it necessary.\n");
    if (TP->query_wiz_level())
        return 0;

    NF("What ?\n");
    if (!QUERY_WHITE_COUNCIL(TP) &&
        !QUERY_RED_COUNCIL(TP) &&
        !QUERY_BLACK_COUNCIL(TP))
        return 0;	

    NF("Grant whom permission to enter your office?\n");
    if (!str)
        return 0;

    str = lower_case(str);

    if (!find_player(str) || !P(str, TO))
        return 0;

    target = P(str, TO);

    NF("You have already granted "+target->query_name()+".\n");
    if ((target->query_prop(WHITE_ENTER) &&
        QUERY_WHITE_COUNCIL(TP)) ||
        (target->query_prop(RED_ENTER) &&
        QUERY_RED_COUNCIL(TP)) ||
        (target->query_prop(BLACK_ENTER) &&
        QUERY_BLACK_COUNCIL(TP)))
        return 0;

    if (QUERY_WHITE_COUNCIL(TP))
        target->add_prop(WHITE_ENTER, 1);
    if (QUERY_RED_COUNCIL(TP))
        target->add_prop(RED_ENTER, 1);
    if (QUERY_BLACK_COUNCIL(TP))
        target->add_prop(BLACK_ENTER, 1);
    write("You permit "+target->query_the_name(TP)+" to " +
      "enter your office.\n");
    target->catch_msg(TP->query_The_name(target)+" permits you " +
      "to enter "+HIS(TP)+" office.\n");
    return 1;
}

int remit_person(string str)
{
    object target;

    NF("Wizards should remove the prop if they deem it necessary.\n");
    if (TP->query_wiz_level())
        return 0;

    NF("What ?\n");
    if (!QUERY_WHITE_COUNCIL(TP) &&
        !QUERY_RED_COUNCIL(TP) &&
        !QUERY_BLACK_COUNCIL(TP))
        return 0;	

    NF("Revoke whom permission to enter your office?\n");
    if (!str)
        return 0;

    str = lower_case(str);

    if (!find_player(str) || !P(str, TO))
        return 0;

    target = P(str, TO);

    NF("That person does not currently have permission.\n");
    if ((!target->query_prop(WHITE_ENTER) &&
        QUERY_WHITE_COUNCIL(TP)) ||
       (!target->query_prop(RED_ENTER) &&
        QUERY_RED_COUNCIL(TP)) ||
       (!target->query_prop(BLACK_ENTER) &&
        QUERY_BLACK_COUNCIL(TP)))
        return 0;

    if (QUERY_WHITE_COUNCIL(TP))
        target->remove_prop(WHITE_ENTER);
    if (QUERY_RED_COUNCIL(TP))
        target->remove_prop(RED_ENTER);
    if (QUERY_BLACK_COUNCIL(TP))
        target->remove_prop(BLACK_ENTER);
    write("You revoke permission for "+target->query_the_name(TP)+" to " +
      "enter your office.\n");
    target->catch_msg(TP->query_The_name(target)+" revokes permission " +
      "for you to enter "+HIS(TP)+" office.\n");
    return 1;
}

int
change_order(string str)
{
    if(!str)
    {
       notify_fail("Petition what? To change to another Order?\n");
       return 0;
    }

    string colour;
    string name = TP->query_real_name();
    int guild_stat = TP->query_skill(WOHS_GUILD_STAT);

    if(TP->query_guild_name_occ() != WOHS_GUILD_NAME)
    {
       notify_fail("Only those of an Order can petition to change!\n");
       return 0;
    }

    if(QUERY_WHITE_COUNCIL(TP) || QUERY_RED_COUNCIL(TP) || 
        QUERY_BLACK_COUNCIL(TP))
    {
       notify_fail("You will need to resign your position on the " +
          "Conclave before you can change Orders.\n");
       return 0;
    }

    if(parse_command(str, 
        environment(TP), "[to] 'change' 'to' [the] %w 'order'", colour))
    {
      if(colour == "white")
      {
         if(QUERY_WOHS_ROBE(TP) == "white")
         {
            write("You are already a member of the Order of the White " +
                "Robes!\n");
            return 1;
         }

         if(!WOHS_MANAGER->query_endorse_order_change(TP, "white"))
         {
            write("You will need to have the endorsement of the Head of " +
                "the Order of the White Robes first before you can " +
                "petition a change.\n");
            return 1;
         }

         if(TP->query_alignment() < 190)
         {
            write("Your alignment needs to be greater than trustworthy " +
                "before you will be considered for the Order of the " +
                "White Robes.\n");
            return 1;
          }

            write("You successfully petition the Conclave to change to " +
                "the Order of the White Robes!\n");
            say(QCTNAME(TP)+ " successfully petitions the Conclave to " +
                "change to the Order of the White Robes!\n"); 
            send_debug_message("wohs", capitalize(name) + " has changed " +
                "to the Order of the White Robes.", LEADER_LOG);

            WOHS_MANAGER->set_wohs_order_colour(TP, "white");
            WOHS_MANAGER->remove_wohs_members_list(name);
            WOHS_MANAGER->add_wohs_members_list(name, "white");
            WOHS_MANAGER->unendorse_order_change(TP, "white");
            TP->set_skill(WOHS_GUILD_STAT, guild_stat / 4);
            object guild_robe = present("wohs_robe_object", TP);
            if (objectp(guild_robe))
            {
                tell_object(TP,"Your robe begins to unravel and " +
                    "reform!\n");
                TP->command("$remove hood");
                guild_robe->set_robe_colour(WOHS_MANAGER->query_wohs_order_colour(TP));
            }
            return 1;
         }

      if(colour == "red")
      {
         if(QUERY_WOHS_ROBE(TP) == "red")
         {
            write("You are already a member of the Order of the Red " +
                "Robes!\n");
            return 1;
         }

         if(!WOHS_MANAGER->query_endorse_order_change(TP, "red"))
         {
            write("You will need to have the endorsement of the Head of " +
              "the Order of the Red Robes first before you can petition " +
              "a change.\n");
            return 1;
         }

         if((TP->query_alignment() < -929) || (TP->query_alignment() > 909))
         {
            write("Your alignment needs to be less than holy and " +
                "greater than damned before you will be considered for " +
                "the Order of the Red Robes.\n");
            return 1;
          }

            write("You successfully petition the Conclave to change to " +
                "the Order of the Red Robes!\n");
            say(QCTNAME(TP)+ " successfully petitions the Conclave to " +
                "change to the Order of the Red Robes!\n");
            send_debug_message("wohs", capitalize(name) + " has changed " +
                "to the Order of the Red Robes.", LEADER_LOG); 

            WOHS_MANAGER->set_wohs_order_colour(TP, "red");
            WOHS_MANAGER->remove_wohs_members_list(name);
            WOHS_MANAGER->add_wohs_members_list(name, "red");
            WOHS_MANAGER->unendorse_order_change(TP, "red");
            TP->set_skill(WOHS_GUILD_STAT, guild_stat / 4);
            object guild_robe = present("wohs_robe_object", TP);
            if (objectp(guild_robe))
            {
                tell_object(TP,"Your robe begins to unravel and reform!\n");
                TP->command("$remove hood");
                guild_robe->set_robe_colour(WOHS_MANAGER->query_wohs_order_colour(TP));
            }
            return 1;
         }

      if(colour == "black")
      {
         if(QUERY_WOHS_ROBE(TP) == "black")
         {
            write("You are already a member of the Order of the Black " +
                "Robes!\n");
            return 1;
         }

         if(!WOHS_MANAGER->query_endorse_order_change(TP, "black"))
         {
            write("You will need to have the endorsement of the Head of " +
              "the Order of the Black Robes first before you can " +
              "petition a change.\n");
            return 1;
         }

         if((TP->query_alignment() > -240))
         {
            write("Your alignment needs to be less than unsympathetic " +
               "before you will be considered for the Order of the " +
               "Black Robes.\n");
            return 1;
          }

            write("You successfully petition the Conclave to change to " +
               "the Order of the Black Robes!\n");
            say(QCTNAME(TP)+ " successfully petitions the Conclave to " +
               "change to the Order of the Black Robes!\n"); 
            send_debug_message("wohs", capitalize(name) + " has changed " +
               "to the Order of the Black Robes.", LEADER_LOG);

            WOHS_MANAGER->set_wohs_order_colour(TP, "black");
            WOHS_MANAGER->remove_wohs_members_list(name);
            WOHS_MANAGER->add_wohs_members_list(name, "black");
            WOHS_MANAGER->unendorse_order_change(TP, "black");
            TP->set_skill(WOHS_GUILD_STAT, guild_stat / 4);
            object guild_robe = present("wohs_robe_object", TP);
            if (objectp(guild_robe))
            {
                tell_object(TP,"Your robe begins to unravel and reform!\n");
                TP->command("$remove hood");
                guild_robe->set_robe_colour(WOHS_MANAGER->query_wohs_order_colour(TP));
            }
            return 1;
         }

      }

       write("Petition to change to the <what> order? White, red, or " +
           "black?\n");
       return 1;
}

int
nominate_for_council(string str)
{
    if(!str)
    {
       notify_fail("Nominate yourself for what? The Conclave?\n");
       return 0;
    }

    str = lower_case(str);

    if(str != "myself for the conclave")
    {
       notify_fail("Nominate yourself for what? The Conclave?\n");
       return 0;
    }

    string order = QUERY_WOHS_ROBE(TP);
    string name = TP->query_real_name();
    int level = TP->query_guild_level_occ();

    if(!WOHS_MANAGER->query_council_voting_open(order))
    {
       notify_fail("There is not currently a vote running for the Head " +
           "of the Order of the " +capitalize(order)+ " Robed Wizards " +
           "for you to nominate for.\n");
       return 0;
    }

    if(level < 3)
    {
       notify_fail("To nominate for the Head of the Order you must be " +
           "ranked at least a Wizard of the Seventh " +capitalize(order)+ 
           " Circle.\n");
       return 0;
    }

    write("You nominate yourself as a canditate for the Head of the " +
        "Order of the " +capitalize(order)+ " Robed Wizards!\n");
    WOHS_MANAGER->add_council_nomination_list(name, order, level);

    return 1;
} 

int
unnominate_for_council(string str)
{
    if(!str || str != "nomination")
    {
       notify_fail("Retract what? Nomination?\n");
       return 0;
    }

    string order = QUERY_WOHS_ROBE(TP);
    string name = TP->query_real_name();

    if(!WOHS_MANAGER->query_council_voting_open(order))
    {
       notify_fail("There is currently not a vote running for the Head " +
           "of the Order of the " +capitalize(order)+ " Robed Wizards " +
           "for you to retract a nomination.\n");
       return 0;
    }

    mapping list = WOHS_MANAGER->query_council_nomination_list(order);

    if(member_array(name, m_indexes(list)) == -1)
    {
       notify_fail("You haven't nominated for the Head of the Order.\n");
       return 0;
    }

    write("You retract your nomination as a canditate for the Head of " +
        "the Order of the " +capitalize(order)+ " Robed Wizards.\n");
    WOHS_MANAGER->remove_council_nomination_list(name, order);

    return 1;
} 

int
list_nominations(string str)
{
    if(!str || str != "nominations")
    {
       notify_fail("List what? Nominations?\n");
       return 0;
    }

    string order = QUERY_WOHS_ROBE(TP);
    string name = TP->query_real_name();

    if(!WOHS_MANAGER->query_council_voting_open(order))
    {
       notify_fail("There is currently not a vote running for the Head " +
           "of the Order of the " +capitalize(order)+ " Robed Wizards.\n");
       return 0;
    }

    mapping list = WOHS_MANAGER->query_council_nomination_list(order);
    string  ren = "";
    int     size = 0;

    if(!m_sizeof(list))
    {
       write("No one has yet nominated for the position of Head of the " +
           "Order of the " +capitalize(order)+ " Robed Wizards.\n");
       return 1;
    }

    foreach(string name, string order: list)
    {
        size++;
        ren += capitalize(name);
        if (m_sizeof(list) - size == 1)
            ren += ", and ";
        else if (m_sizeof(list) - size > 1)
            ren += ", ";
     }

     if(ren == "")
     {
        write("There are no Wizards who have nominated for the " +
            "position of Head of the Order of the " +capitalize(order)+ 
            " Robed Wizards.\n");
        return 1;
     }
     else
     {
        write("The following Wizards have nominated themselves for " +
            "the position of Head of the Order of the " +capitalize(order)+
            " Robed Wizards:\n  "+ ren + ".\n\n\n");
        return 1;
     }

    return 1;
}

int
vote_for_council(string str)
{
    if(!str)
    {
       notify_fail("Vote for whom?\n");
       return 0;
    }

    str = lower_case(str);

    string order = QUERY_WOHS_ROBE(TP);
    string name = TP->query_real_name();
    int level = TP->query_guild_level_occ();
    int votes = min(8, max(level -2));
    mapping list = WOHS_MANAGER->query_council_nomination_list(order);
    mapping voter_list = WOHS_MANAGER->query_has_voted(order);

    if(!WOHS_MANAGER->query_council_voting_open(order))
    {
       notify_fail("There is currently no vote running for the Head of " +
           "the Order of the " +capitalize(order)+ " Robed Wizards, so " +
           "there is no point in voting!\n");
       return 0;
    }

    if(level < 3)
    {
       notify_fail("To vote for the Head of the Order you must be " +
           "ranked at least a Wizard of the Seventh " +capitalize(order)+ 
           " Circle.\n");
       return 0;
    }

    if(m_sizeof(voter_list) && member_array(name, m_indexes(voter_list)) > -1)
    {
       notify_fail("You have already voted for the Head of the Order of " +
           "the " +capitalize(order)+ " Robed Wizards. You only get one " +
           "vote!\n");
       return 0;
    }

    string arg;

    if (parse_command(str, environment(TP), "[for] %s", arg))
    {
        if (!arg)
        {
            write("Who do you want to vote for?\n");
            return 1;          
        } 

        if(arg == "myself")
            arg = name;

        if (member_array(arg, m_indexes(list)) == -1)
        {
            write("That person hasn't nominated themselves for the Head " +
                "of the Order of the " +capitalize(order)+ 
                " Robed Wizards.\n");
            return 1;
        }

        write("You vote for " +capitalize(arg)+ " to be the next Head " +
            "of the Order of the " +capitalize(order)+ " Robed Wizards.\n");
        DEBUG("Votes generated in Conclave room: " +votes+ ".");
        WOHS_MANAGER->add_council_vote_list(arg, order, votes);
        WOHS_MANAGER->add_has_voted(name, order);
        return 1;
    }

    write("Urgh... function messed up.\n");
    return 1; 

}

