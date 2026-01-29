 /*
   Wayreth.

   blackstudy.c
   ------------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : March 2017
   By ...........: Arman

 */

#pragma strict_types
#pragma no_clone

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/guilds/wohs/defs.h"
#include "/d/Krynn/common/defs.h"

inherit "/lib/commands";
inherit TOWERROOM;

#include "/d/Genesis/specials/debugger/debugger_tell.h"
#include "council_scroll_msg.h"

#define WHITE_ENTER "_i_may_enter_white"
#define RED_ENTER   "_i_may_enter_red"
#define BLACK_ENTER "_i_may_enter_black"
#define LEADER_LOG ("/d/Krynn/guilds/wohs/logs/wohs_conclave")

string
black_head_desc()
{
  if(!WOHS_MANAGER->query_is_council_black())
    return "the study of the Master of the Order of the Black Robed " +
        "Wizards.";
  else if(QUERY_BLACK_COUNCIL(TP))
    return "your personal study as Master of the Order of the Black " +
        "Robed Wizards.";
  else
    return "the study of " +capitalize(WOHS_MANAGER->query_is_council_black())+ 
        ", the current Master of the Order of the Black Robed Wizards.";
}

void
create_tower_room()
{
   set_short("The Study of the Head of the Order of the Black Robes");
    set_long("You are standing in @@black_head_desc@@ "+
      "The room is clustered with all sorts of things. You see jars, " +
      "crates, boxes, tins, and scrolls all over the place. " +
      "Books lie piled on top of each other in stacks " +
      "and in the middle of this whole jumble is a large " +
      "oak desk with a highbacked chair facing towards you. " +
      "You are also able to detect a few shelves along the west " +
      "wall and from the ceiling hang four different sized " +
      "cages. The room is very chilly.\n");
   
   add_item(({"study", "room"}), "It is hard to get an idea of the " +
      "exact size of this room due to all the things taking " +
      "space. Only a few feet of open space is to be found on " +
      "the floor giving access to various parts of the room.\n");
   add_item("jars", "There are jars of all sorts of sizes and shapes. " +
      "Round ones and square ones, big ones and small ones, " +
      "blue ones and red ones, low ones and tall ones.\n");
   add_item("round jars", "In these jars are several different sorts " +
      "of insects. Among others you see cockroaches, grasshoppers, " +
      "beetles and small spiders crawling around.\n");
   add_item("corner", "In the far off corner you see a few paintings" +
      "leaning against the wall.\n");
   add_item("square jars", "These clear glass jars contain sparkling" +
      "powders of various colours.\n");
   add_item("big jars", "The big jars are made of terracotta and you " +
      "are unable to see what is inside of them. They are sealed " +
      "and there is no way you could open them without it" + 
      "showing.\n");
   add_item("small jars", "Many of the small jars are empty but in a " +
      "few of them you find rosepetals, sand, some sticky stuff " +
      "and a black thick liquid.\n");
   add_item("blue jars", "All the blue jars have little lables on them " +
      "and they are tightly sealed.\n");
   add_item("red jars", "These jars are all empty.\n");
   add_item("low jars", "Small pieces of bark lie in these jars. You " +
      "recognise birch and pine bark.\n");
   add_item("tall jars", "Long sticks of some yellowish colour stand " +
      "in these jars. They all seem the same and all jars are " +
      "full except one.\n");
   add_item(({"things", "jumble"}), "There are so many things lying " +
      "around in this study that it is hard to know where to " +
      "start looking if one was searching for something.\n");
   add_item("crates", "Several crates stand in the room. No one seems " +
            "to have had the time to unpack them, for you " +
      "notice a thick layer of dust on several of them.\n");
   add_item("boxes", "There are some small wooden boxes here and " +
      "there in the room and you notice that a couple of them " +
      "have small holes in them. As you go closer to examine " +
      "one of them you see a long claw sticking out of one of " +
      "the holes. You decide it best not to open the boxes.\n");
   add_item("tins", "These metal tins contain small seeds of " +
      "various sorts.\n");
   add_item("scrolls", "Some lie piled on the shelves and several " +
      "more lie scattered around the desk.\n");
   add_item(({"stacks", "books"}), "Old tomes bound in leather lie in " +
      "stacks all over the room. Some have titles in languages " +
      "you have never seen before and some have strange symbols " +
      "written with peculiar ink.\n");
   add_item(({"desk", "oak desk"}), "This large oak desk is littered " +
      "with scrolls and papers. An ancient scroll sits on the desk, " +
        "outlining the commands of the Master of the Order.\n");
   add_item(({"ancient scroll","scroll"}),"An ancient scroll sits on the " +
       "desk, outlining the commands of the Master of the Order. You " +
       "could read it.\n");
   add_item("cages", "They are all made of sturdy metal wires.\n");
   add_item("first cage", "In this large cage you see a large coal-" +
      "black bird. Its beady eyes follow your movements with a " +
      "scrutinizing gaze.\n");
   add_item("second cage", "This small cage is filled with wood-wool. " +
      "You notice some furry little animal move about inside the " +
      "wool.\n");
   add_item("bird", "His coal-black feathers gleam as he slowly turns " +
      "his head towards you.\n");
   add_item("third cage", "This cage is empty.\n");
   add_item("fourth cage", "You see that this cage has been reinforced " +
      "with extra wire mesh. A rank odour emanates from the cage " +
      "and you understand why it is hanging so high up.\n"); 
   add_item("ceiling","The ceiling is made of stone and in each corner " +
      "hangs a sphere of dim glass radiating a soft light. There " +
      "are also four cages hanging at the back of the room.\n");
   add_item(({"wall", "walls"}), "The walls are made of stone.\n");
   add_item("paintings", "There are three paintings leaning against " +
      "the wall. You notice that they are all painted by Udhucair, " +
      "the famous Abanasinian artist.\n");
   add_item("first painting", "It depicts a beautiful stone mansion " +
      "with a garden at the side. Some mountains can be seen in the " +
      "background and threatening storm clouds are gathering in the " +
      "horizon.\n");
   add_item("second painting", "This picture is a portrait of a lady " +
      "dressed in a deep blue, almost black, velvet riding habit. Her " +
      "hair is dark brown and tied back with a black velvet ribbon. " +
      "Her features are delicate and her dark brown eyes are heavily " +
      "accentuated by her pale skin. At her side sits a majestic grey " +
      "wolfhound.\n");
   add_item("third painting", "This large portrait shows a knight in " +
      "full armour. His decorated breastplate showing it to be a " +
      "Solaminan armour of a Knight of the Crown. His face is very " +
      "weathered, his hair black, and his flat grey eyes seem to " +
      "follow you wherever you are in the room. At his feet lies a " +
      "heavy warhammer, gleaming with a dark glow and behind him in " +
      "shadows a pair of gleaming eyes can be seen.\n");
   add_item(({"shelves", "bookshelves"}), "Rows upon rows of leather " +
      "bound books line the shelves.\n");
   add_item(({"leather books", "tomes", "old books"}), "As you start " +
      "to look at the books you notice that there is a very thick " +
      "layer of dust upon them all. You decide it best not to stir " +
      "the dust for fear of sneezing and disturbing someone.\n");

    // add_cmd_item(({"mastery of the black order","mastery of the order",
    //      "mastery"}),"claim","@@claim_council_position");

    add_cmd_item(({"ancient scroll","scroll"}),"read",
        "@@read_council_scroll");

    add_exit(WTOWER + "conclave","north","@@leave_study");
}

public mixed
prevent_teleport()
{
    if(!this_player())
	return 0;

    if(WOHS_MANAGER->query_renegade_wohs(TP))
        return "Something prevents you from teleporting there.";

    if(!QUERY_BLACK_COUNCIL(TP))
	return "Only the Head of the Order can teleport to this " +
            "location of the Tower of High Sorcery.";

    if(this_player()->query_guild_name_occ() == "Wizards of High Sorcery")
	return 0;

    return "Something prevents you from teleporting there.";
}

int
leave_study()
{
    if(TP->query_prop(BLACK_ENTER))
      TP->remove_prop(BLACK_ENTER);

    return 0;
}

static int
query_prevent_snoop() { return 1; }

string
claim_council_position()
{
    if(WOHS_MANAGER->query_is_council_black())
      return "There is currently a Master of the Black Order.\n";

    if(WOHS_MANAGER->query_wohs_order_colour(TP) != "black") 
      return "Only Black Robe members can claim the position of " +
       "Head of the Black Order.\n";

    WOHS_MANAGER->add_council_black(TP);
    WOHS_MANAGER->add_council_last_login("black");

    say(QCTNAME(TP) + " claims the leadership of the Order of the " +
       "Black Robes!\n");
    return "You claim the leadership of the Order of the Black " +
       "Robes!\n";
}

void
init()
{
    ADD("grant_person", "grant");
    ADD("remit_person", "revoke");
    ADD("resign_conclave", "resign");
    ADD("endorse_order_change", "endorse");
    ADD("unendorse_order_change", "unendorse");
    ADD("exile_member", "exile");
    ADD("forgive_member", "forgive");
    ADD("ban_member", "ban");
    ADD("unban_member", "unban");
    ADD("invite_sohm_test", "permit");
    ADD("uninvite_sohm_test", "withdraw");
    ADD("list_wohs_members","list");
    ADD("peruse_events", "peruse");
    ::init();
}

/* A function that allows conclave members to allow others into their
 * offices
 */

int
grant_person(string str)
{
    object target;
    str = lower_case(str);

    NF("Wizards should add the prop if they deem it necessary.\n");
    if (TP->query_wiz_level())
        return 0;

    NF("What?\n");
    if (!QUERY_WHITE_COUNCIL(TP) &&
        !QUERY_RED_COUNCIL(TP) &&
        !QUERY_BLACK_COUNCIL(TP))
        return 0;	

    NF("Grant whom permission to enter your office?\n");
    if (!str)
        return 0;

    NF(C(str)+ " is not a Wizard of High Sorcery. They won't be " +
        "able to enter the Tower, let alone your office!\n");
    if(!WOHS_MANAGER->query_passed_wohs_test(str))
        return 0;

    NF("You can't find that Wizard in the realms at the moment.\n");
    if (!find_player(str))
        return 0;

    target = find_player(str);

    NF("You have already granted "+target->query_name()+" permission " +
       "to enter your office.\n");
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
      "to enter "+HIS(TP)+" office on the eighth floor of the Tower of " +
      "High Sorcery in Wayreth.\n");
    return 1;
}

int remit_person(string str)
{
    object target;
    str = lower_case(str);

    NF("Wizards should remove the prop if they deem it necessary.\n");
    if (TP->query_wiz_level())
        return 0;

    NF("What?\n");
    if (!QUERY_WHITE_COUNCIL(TP) &&
        !QUERY_RED_COUNCIL(TP) &&
        !QUERY_BLACK_COUNCIL(TP))
        return 0;	

    NF("Revoke whom permission to enter your office?\n");
    if (!str)
        return 0;

    if (!find_player(str))
        return 0;

    target = find_player(str);

    NF("That person does not currently have permission to enter " +
       "your office.\n");
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
    target->catch_msg(TP->query_The_name(target)+" removes permission " +
      "for you to enter "+HIS(TP)+" office in the Tower of High Sorcery.\n");
    return 1;
}

// Conclave commands

int
resign_conclave(string str)
{
    str = lower_case(str);

    if(!str || str != "as head of the order of the black robes")
    {
       notify_fail("Resign what? As Head of the Order of the Black " +
           "Robes?\n");
       return 0;
    }

    if(!QUERY_BLACK_COUNCIL(TP))
    {
       write("You are not Head of the Order of the Black Robes. You " +
           "can't resign that position!\n");
       return 1;
    }

    write("You resign as Head of the Order of the Black Robes.\n");
    say(QCTNAME(TP)+ " resigns as Head of the Order of the Black Robes.\n");
    WOHS_MANAGER->remove_council_black();

    return 1;
}

int
endorse_order_change(string str)
{
    str = lower_case(str);

    if(!str)
    {
       notify_fail("Endorse whom to change to the Order of the Black " +
           "Robes?\n");
       return 0;
    }

    if(!QUERY_BLACK_COUNCIL(TP))
    {
       write("You are not Head of the Order of the Black Robes. You " +
           "cannot endorse anyone to change to the Order of the Black " +
           "Robes!\n");
       return 1;
    }

    string player;

    if(parse_command(str, 
        environment(TP), "%w [to] 'change' 'to' [the] 'order' 'of' 'the' 'black' 'robes'", 
        player))
    {
       if(!WOHS_MANAGER->query_passed_wohs_test(player))
       {
          write("That individual is not a Wizard of High Sorcery!\n");
          return 1;
       }

       if(WOHS_MANAGER->query_renegade_wohs(player))
       {
          write("That individual is a Renegade, and exiled from the " +
              "Tower!\n");
          return 1;
       }

       if(WOHS_MANAGER->query_wohs_order_colour(player) == "black")
       {
          write("That individual is already of the Order of the Black " +
              "Robes!\n");
          return 1;
       } 

       if(WOHS_MANAGER->query_endorse_order_change(player, "black"))
       {
          write("That individual is already endorsed to join the Order " +
              "of the Black Robes!\n");
          return 1;
       } 

       WOHS_MANAGER->endorse_order_change(player, "black");
       write("You provide your endorsement for " +capitalize(player)+ 
           " to change to the Order of the Black Robes.\n");
       return 1; 

    }
    write("Endorse <whom> to change to the Order of the Black Robes?\n");
    return 1;
}

int
unendorse_order_change(string str)
{
    str = lower_case(str);

    if(!str)
    {
       notify_fail("Unendorse whom?\n");
       return 0;
    }

    if(!QUERY_BLACK_COUNCIL(TP))
    {
       write("You are not Head of the Order of the Black Robes. You " +
           "cannot unendorse anyone!\n");
       return 1;
    }

    string player;

    if(parse_command(str, environment(TP), "%w", player))
    {
       if(!WOHS_MANAGER->query_passed_wohs_test(player))
       {
          write("That individual is not a Wizard of High Sorcery!\n");
          return 1;
       }

       if(!WOHS_MANAGER->query_endorse_order_change(player, "black"))
       {
          write("That individual isn't endorsed to join the Order of " +
              "the Black Robes!\n");
          return 1;
       } 

       WOHS_MANAGER->unendorse_order_change(player, "black");
       write("You unendorse " +capitalize(player)+ ".\n");
       send_debug_message("wohs", capitalize(player)+ " has been " +
           "unendorsed to change to the Order of the Black Robes.", 
           LEADER_LOG);
       return 1; 

    }
    write("Unendorse <whom>?\n");
    return 1;
}
  
int
exile_member(string str)
{
    str = lower_case(str);

    if(!str)
    {
       notify_fail("Exile whom?\n");
       return 0;
    }

    if(!QUERY_BLACK_COUNCIL(TP))
    {
       write("You are not Head of the Order of the Black Robes. You " +
           "cannot exile anyone!\n");
       return 1;
    }

    string player;

    if(parse_command(str, environment(TP), "%w", player))
    {
       if(!WOHS_MANAGER->query_passed_wohs_test(player))
       {
          write("That individual is not a Wizard of High Sorcery!\n");
          return 1;
       }

       if(WOHS_MANAGER->query_renegade_wohs(player))
       {
          write("That individual is already a Renegade, and exiled from " +
              "the Tower!\n");
          return 1;
       }

       if(WOHS_MANAGER->query_wohs_order_colour(player) != "black")
       {
          write("That individual is not of the Order of the Black Robes. " +
              "You have no authority to exile a member of another Order!\n");
          return 1;
       } 

       if(WOHS_MANAGER->query_council_voting_open("black"))
       {
          write("While there is a current ballot for the next Head of " +
              "the Order of the Black Robes, you cannot declare anyone " +
              "as renegade.\n");
          return 1;
       } 

       WOHS_MANAGER->set_renegade_wohs(player);
       write("You declare " +capitalize(player)+ " a Renegade of the " +
           "Orders, and banish them from the Tower of Wayreth!\n");
       find_player(player)->catch_msg("\nYou have been declared a " +
           "Renegade of the Orders and banished from the Tower of " +
           "Wayreth!\n\nBe warned! If you are slain while exiled you " +
           "will be expelled from the Wizards of High Sorcery!\n\n");

       return 1;
    }

    write("Exile <whom>?\n");
    return 1;
}

int
forgive_member(string str)
{
    str = lower_case(str);

    if(!str)
    {
       notify_fail("Forgive whom?\n");
       return 0;
    }

    if(!QUERY_BLACK_COUNCIL(TP))
    {
       write("You are not Head of the Order of the Black Robes. You " +
           "cannot forgive anyone!\n");
       return 1;
    }

    string player;

    if(parse_command(str, environment(TP), "%w", player))
    {
       if(!WOHS_MANAGER->query_passed_wohs_test(player))
       {
          write("That individual is not a Wizard of High Sorcery!\n");
          return 1;
       }

       if(!WOHS_MANAGER->query_renegade_wohs(player))
       {
          write("That individual is not a Renegade, so has nothing to " +
              "be forgiven for?\n");
          return 1;
       }

       if(WOHS_MANAGER->query_wohs_order_colour(player) != "black")
       {
          write("That individual is not of the Order of the Black " +
              "Robes. You have no authority to forgive a member of " +
              "another Order!\n");
          return 1;
       } 

       if(WOHS_MANAGER->query_council_voting_open("black"))
       {
          write("While there is a current ballot for the next Head of " +
              "the Order of the Black Robes, you cannot forgive " +
              "renegades.\n");
          return 1;
       }

       WOHS_MANAGER->remove_renegade_wohs(player);
       send_debug_message("wohs", capitalize(player)
           + " has been forgiven and is no longer exiled from the Tower.", 
           LEADER_LOG);
       write("You forgive " +capitalize(player)+ " and allow them to " +
           "return to the Tower of Wayreth!\n");
       find_player(player)->catch_msg("\nYou have been forgiven by the " +
           "Conclave of High Sorcery and may return to the the Tower " +
           "of Wayreth!\n\n");

       return 1;
    }

    write("Forgive <whom>?\n");
    return 1;
}

int
invite_sohm_test(string str)
{
    str = lower_case(str);

    if(!str)
    {
       notify_fail("Permit whom to take the Test of High Sorcery?\n");
       return 0;
    }

    if(!QUERY_RED_COUNCIL(TP) && !QUERY_WHITE_COUNCIL(TP) && 
       !QUERY_BLACK_COUNCIL(TP))
    {
       write("You are not Head of an Order of High Sorcery. You do not " +
           "have the authority to invite an aspirant to take the Test!\n");
       return 1;
    }

    string player, sponsor;

    if(parse_command(str, 
        environment(TP), "%w 'to' 'take' 'the' 'test' [of] [high] [sorcery]", 
        player))
    {
       if(!WOHS_MANAGER->query_is_member(player))
       {
          write("That individual is not an Aspirant of High Sorcery!\n");
          return 1;
       }

       if(WOHS_MANAGER->query_aspirant_title(player))
       {
          write("That individual is not an Aspirant of High Sorcery. " +
              "While a practicing magician, they need to publicly " +
              "display themselves as Aspirants before they can " +
              "be invited to sit the Test.\n");
          return 1;
       }

       if(WOHS_MANAGER->query_passed_wohs_test(player))
       {
          write("That individual has already passed the Test of High " +
              "Sorcery!\n");
          return 1;
       }

       if(WOHS_MANAGER->query_invited_wohs_test(player))
       {
          write("That individual has already been invited to take the " +
              "Test of High Sorcery!\n");
          return 1;
       }

       sponsor = TP->query_real_name();

       WOHS_MANAGER->set_invited_wohs_test(player);
       WOHS_MANAGER->add_invited_wohs_test_list(player, sponsor);
       write("You permit " +capitalize(player)+ " to take the Test of " +
           "High Sorcery, and invite them to enter the Hall of Mages at " +
           "the Tower of Wayreth!\n");
       find_player(player)->catch_msg("\nYou have been permitted to " +
           "take the Test of High Sorcery, and have been invited to " +
           "enter the Hall of Mages at the Tower of Wayreth!\n\n");

       return 1;
    }

    write("Permit <whom> to take the Test?\n");
    return 1;
}

int
uninvite_sohm_test(string str)
{
    str = lower_case(str);

    if(!str)
    {
       notify_fail("withdraw invitation to take the Test from whom?\n");
       return 0;
    }

    if(!QUERY_RED_COUNCIL(TP) && !QUERY_WHITE_COUNCIL(TP) && 
       !QUERY_BLACK_COUNCIL(TP))
    {
       write("You are not Head of an Order of High Sorcery. You do not " +
           "have the authority to withdraw an invitation from an " +
           "aspirant to take the Test!\n");
       return 1;
    }

    string player;

    if(parse_command(str, 
        environment(TP), "'invitation' 'to' 'take' 'the' 'test' [of] [high] [sorcery] 'from' %w", 
        player))
    {
       if(!WOHS_MANAGER->query_is_member(player))
       {
          write("That individual is not an Aspirant of High Sorcery!\n");
          return 1;
       }

       if(WOHS_MANAGER->query_passed_wohs_test(player))
       {
          write("That individual has already passed the Test of High " +
              "Sorcery! Too late to withdraw their invitation!\n");
          return 1;
       }

       if(WOHS_MANAGER->query_player_started_wohs_test(player))
       {
          write("That individual has started the Test of High Sorcery! " +
              "Too late to withdraw their invitation!\n");
          return 1;
       }

       if(!WOHS_MANAGER->query_invited_wohs_test(player))
       {
          write("That individual hasn't been invited to take the Test " +
              "of High Sorcery.\n");
          return 1;
       }

       WOHS_MANAGER->remove_invited_wohs_test(player);
       WOHS_MANAGER->remove_invited_wohs_test_list(player);
       write("You withdraw the invitation for " +capitalize(player)+ 
           " to take the Test of High Sorcery!\n");
       find_player(player)->catch_msg("\nYour invitation to take the " +
           "Test of High Sorcery has been withdrawn by " +QTNAME(TP)+ 
           "!\n\n");

       return 1;
    }

    write("Withdraw invitation to take the Test from <whom>?\n");
    return 1;
}

int
list_wohs_members(string str)
{    
    if(!str || str != "members")
    {
       notify_fail("List what? Members?\n");
       return 0;
    }

    if(!QUERY_RED_COUNCIL(TP) && !QUERY_WHITE_COUNCIL(TP) && 
       !QUERY_BLACK_COUNCIL(TP) && !TP->query_wiz_level())
    {
       write("You are not Head of an Order of High Sorcery. You do not " +
           "have the authority to review the list the members of High " +
           "Sorcery!\n");
       return 1;
    }

    mapping list = WOHS_MANAGER->query_wohs_members_list();
    mapping aspirants = WOHS_MANAGER->query_invited_wohs_test_list();
    string  loc = "";
    string  ren = "";
    string  asp = "";
    int     size = 0;
    int     size2 = 0;
    int     white_members = WOHS_MANAGER->count_wohs_order_members("white");
    int     red_members = WOHS_MANAGER->count_wohs_order_members("red");
    int     black_members = WOHS_MANAGER->count_wohs_order_members("black");

    if(!m_sizeof(list))
    {
       write("Bizarrely it seems there are no Wizards of High Sorcery. " +
           "I think you need to take a lie down, or report this to a " +
           "higher authority.\n");
       return 1;
    }

    foreach(string name, string order: list)
    {
        size++;
        loc += capitalize(name) + " of the Order of the " +
            capitalize(order)+ " Robes";
        if (m_sizeof(list) - size == 1)
            loc += ", and\n  ";
        else if (m_sizeof(list) - size > 1)
               loc += ",\n  ";
     }

     write("You read the list of the current Wizards of High Sorcery, " +
         "noting there are currently " +LANG_NUM2WORD(white_members)+
         " of the White Robed Order, " +LANG_NUM2WORD(red_members)+ 
         " of the Red Robed Order, and " +LANG_NUM2WORD(black_members)+
         " of the Black Robed Order:\n\n" +"  "+ loc + ".\n\n\n");

    foreach(string name, string order: list)
    {
        size++;
        if(WOHS_MANAGER->query_renegade_wohs(name))
            ren += capitalize(name);
        if (m_sizeof(list) - size == 1)
            ren += ", and ";
        else if (m_sizeof(list) - size > 1)
            ren += ", ";
     }

     if(ren == "")
     {
        write("There are no Wizards declared Renegade of the Orders at " +
            "present.\n\n");
     }
     else
     {
        write("The following Wizards have been declared Renegade of the " +
            "Orders and have been banished from the Tower of " +
            "Wayreth:\n  "+ ren + ".\n\n\n");
     }

    foreach(string name, string sponsor: aspirants)
    {
        size2++;
        asp += capitalize(name) + " has been invited by " +
            capitalize(sponsor)+ " to take the Test";
        if (m_sizeof(aspirants) - size2 == 1)
            asp += ", and\n  ";
        else if (m_sizeof(aspirants) - size2 > 1)
               asp += ",\n  ";
     }

     if(asp == "")
     {
        write("There are currently no Aspirants that have been invited " +
            "to take the Test.\n\n");
     }
     else
     {
        write("Aspirants that have been invited to take the test:\n" +"  "+
            asp + ".\n\n\n");
     }

    return 1;

}

int
ban_member(string str)
{
    str = lower_case(str);

    if(!str)
    {
       notify_fail("Ban whom?\n");
       return 0;
    }
 
    if(!QUERY_BLACK_COUNCIL(TP))
    {
       write("You are not Head of the Order of the Black Robes. You " +
           "cannot ban anyone!\n");
       return 1;
    }
 
    string player;

    if(parse_command(str, environment(TP), "%w", player))
    {
       if(!WOHS_MANAGER->query_passed_wohs_test(player))
       {
          write("That individual is not a Wizard of High Sorcery!\n");
          return 1;
       }

       if(WOHS_MANAGER->query_wohs_train_rack_ban(player))
       {
          write("That individual is already banned from training and " +
              "the Tower storage!\n");
          return 1;
       }

/*
       if(WOHS_MANAGER->query_wohs_order_colour(player) != "black")
       {
          write("That individual is not of the Order of the Black Robes. " +
              "You have no authority to ban a member of another Order!\n");
          return 1;
       } 
*/

       WOHS_MANAGER->set_wohs_train_rack_ban(player);
       write("You ban " +capitalize(player)+ " from accessing the " +
           "training and equipment rooms of the Tower.\n");
       find_player(player)->catch_msg("\nYou have been banned from " +
           "accessing the training and equipment rooms of the Tower!\n\n");
       return 1;
    }

    write("Ban <whom>?\n");
    return 1;
}

int
unban_member(string str)
{
    str = lower_case(str);

    if(!str)
    {
       notify_fail("Unban whom?\n");
       return 0;
    }
 
    if(!QUERY_BLACK_COUNCIL(TP))
    {
       write("You are not Head of the Order of the Black Robes. You " +
           "cannot forgive anyone!\n");
       return 1;
    }
 
    string player;

    if(parse_command(str, environment(TP), "%w", player))
    {
       if(!WOHS_MANAGER->query_passed_wohs_test(player))
       {
          write("That individual is not a Wizard of High Sorcery!\n");
          return 1;
       }

       if(!WOHS_MANAGER->query_wohs_train_rack_ban(player))
       {
          write("That individual has not been banned?\n");
          return 1;
       }
/*
       if(WOHS_MANAGER->query_wohs_order_colour(player) != "black")
       {
          write("That individual is not of the Order of the Black Robes. " +
              "You have no authority to unban a member of another Order!\n");
          return 1;
       } 
*/

       WOHS_MANAGER->remove_wohs_train_rack_ban(player);
       send_debug_message("wohs", capitalize(player)
           + " has been unbanned from training and storage rooms of the "
           + "Tower.", LEADER_LOG);
       write("You unban " +capitalize(player)+ " and allow them to access "
           + "the training and equipment rooms of the Tower of Wayreth!\n");
       find_player(player)->catch_msg("\nYou have been unbanned by the " +
           "Conclave of High Sorcery and may access the equipment and " +
           "training rooms of the Tower of Wayreth!\n\n");

       return 1;
    }

    write("Unban <whom>?\n");
    return 1;
}  

int
peruse_events(string str)
{
    str = lower_case(str);

    if(!str || str != "events")
    {
       notify_fail("Peruse what? Events?\n");
       return 0;
    }
 
    if(!QUERY_BLACK_COUNCIL(TP))
    {
       write("You are not Head of the Order of the Black Robes. You do " +
           "not have access to those missives and logs!\n");
       return 1;
    }

    write("You thoroughly review the recent events to happen within " +
        "the Orders of High Sorcery...\n\n");
    TP->more(read_file(LEADER_LOG,1));

    return 1;
}   