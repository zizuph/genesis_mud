 /*
   Wayreth.

   whitestudy.c
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
#include "/d/Krynn/common/clock/clock.h"

inherit "/lib/commands";
inherit TOWERROOM;

#include "/d/Genesis/specials/debugger/debugger_tell.h"
#include "council_scroll_msg.h"

#define WHITE_ENTER "_i_may_enter_white"
#define RED_ENTER   "_i_may_enter_red"
#define BLACK_ENTER "_i_may_enter_black"
#define LEADER_LOG ("/d/Krynn/guilds/wohs/logs/wohs_conclave")

string
white_head_desc()
{
  if(!WOHS_MANAGER->query_is_council_white())
    return "the study of the Master of the White Robed Mages.";
  else if(QUERY_WHITE_COUNCIL(TP))
    return "your personal study as Master of the Order of the White Robed " +
      "Wizards.";
  else
    return "the study of " +capitalize(WOHS_MANAGER->query_is_council_white())+ ", " +
      "the current Master of the Order of the White Robed Mages.";
}

string time_desc()
{
	switch(GET_TIMEOFDAY)	
	{
		case TOD_DAWN:
		return "The rising sun sheds"; break;
		case TOD_DAY:
		return "The sun is high in the sky, shedding"; break;
		case TOD_TWILIGHT:
		return "The setting sun gives way to the moons of the night, shedding"; break;
		case TOD_NIGHT:
		return "The two visible moons shed"; break;
	}

        return "This doesn't WORK";
}

void
create_tower_room()
{
    set_short("This is the study of the Master of the White Robes");

    set_long("You have entered @@white_head_desc@@ A magnificent " +
        "multifaceted crystalline window on " +
	"the far wall spills a dazzling display of colored light "+
	"across the furnishings of this room. An intricately carved "+
	"citruswood desk dominates the opposite end of the room, and "+
	"behind it sits a simple leather armchair. What at first glance "+
	"appeared to be a pair of graceful rowan trees turns out to be a "+
	"cunningly designed book cabinet, around which there is an almost "+
	"indistinct field of shimmering energy. A plush leather couch for "+
	"visitors sits across from the desk, along with an extremely "+
	"comfortable footrest.\n");

    add_item(({"walls", "wall"}), "The walls are made of the same " +
             "black rune covered rock as the rest of the tower. " +
             "Some tapestries adorn the walls.\n");

    add_item("ceiling", "The ceiling is made of the same black " +
             "rune covered stone as the rest of the tower.\n");

    add_item("floor", "The floor is wooden and creaks slightly " +
             "as you walk across it.\n");

    add_item("window", "As you gaze out the window, you see an "+
	"incredible view of the surrounding forests, the Kharolis "+
	"mountains, and - off in the distance - the glint of light "+
	"that is the town of Haven. "+"@@time_desc@@"+" a gentle light over "+
	"the landscape.\n");   

    add_item(({"case","bookcase","cabinet"}), "Designed to appear as a pair of rowan "+
	"trees, this contraption is instead a bookcase, undoubtedly of gnomish "+
	"origin. The knobs of the cabinet are disguised as two protruding " +
	"bumps in the trunks of the trees, and it would seem that the case "+
	"could be opened by swinging the doors in opposite directions."+
	"It is, unfortunately, securely locked, both physically and magically.\n");

    add_item(({"desk", "citruswood desk", "carved desk"}), "You have never seen "+
	"such an amazing clutter of worthless papers, useless knicknacks, and "+
	"scribbled notes.  It's amazing that the desk doesn't topple over "+
	"from the sheer weight of all the paper. None of it looks terribly "+
	"important, however, and even if it was, you doubt you could find "+
	"anything useful in the vast pile. An ancient " +
        "scroll sits on the desk, outlining the commands of the Master of the " +
        "Order. The carvings along the front and sides "+
	"catch your eye.\n");

    add_item(({"ancient scroll","scroll"}),"An ancient scroll sits on the desk, " +
        "outlining the commands of the Master of the Order. You could " +
        "read it.\n");

    add_item("carvings", "Each panel of the desk seems to represent the history of one " +
	"of the major elven tribes, the Drow, the Eldar, and the Krynnish elves. The "+
	"carvings are done in fantastic detail, to the point that the figures almost "+
	"seem alive. Some sort of magic is undoubtedly at work.\n");

    add_item(({"couch","footrest"}),"This couch and footrest ensemble seems designed to "+
	"put the visitor to the office at complete ease. Indeed, they look so "+
	"comfortable, you wonder how anyone ever has the willpower to stand up.\n");
    
    add_item(({"chair","armchair"}),"The luxurious armchair is made of " +
             "dark brown leather and looks very comfortable.\n");

    // add_cmd_item(({"mastery of the white order","mastery of the order",
    //      "mastery"}),"claim","@@claim_council_position");

    add_cmd_item(({"ancient scroll","scroll"}),"read","@@read_council_scroll");

    add_exit(WTOWER + "conclave", "south", "@@leave_study");
} 

public mixed
prevent_teleport()
{
    if(!this_player())
	return 0;

    if(WOHS_MANAGER->query_renegade_wohs(TP))
        return "Something prevents you from teleporting there.";

    if(!QUERY_WHITE_COUNCIL(TP))
	return "Only the Head of the Order can teleport to this " +
            "location of the Tower of High Sorcery.";

    if(this_player()->query_guild_name_occ() == "Wizards of High Sorcery")
	return 0;

    return "Something prevents you from teleporting there.";
}

int
leave_study()
{
    if(TP->query_prop(WHITE_ENTER))
      TP->remove_prop(WHITE_ENTER);

    return 0;
}

static int
query_prevent_snoop() { return 1; }

// Vote now starts automatically, this function not required.

string
claim_council_position()
{
    if(WOHS_MANAGER->query_is_council_white())
      return "There is currently a Master of the White Order.\n";

    if(WOHS_MANAGER->query_wohs_order_colour(TP) != "white") 
      return "Only White Robe members can claim the position of " +
       "Head of the White Order.\n";

    WOHS_MANAGER->add_council_white(TP);
    WOHS_MANAGER->add_council_last_login("white");

    say(QCTNAME(TP) + " claims the leadership of the Order of the " +
       "White Robes!\n");
    return "You claim the leadership of the Order of the White " +
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

    if(!str || str != "as head of the order of the white robes")
    {
       notify_fail("Resign what? As Head of the Order of the White Robes?\n");
       return 0;
    }

    if(!QUERY_WHITE_COUNCIL(TP))
    {
       write("You are not Head of the Order of the White Robes. You can't " +
             "resign that position!\n");
       return 1;
    }

    write("You resign as Head of the Order of the White Robes.\n");
    say(QCTNAME(TP)+ " resigns as Head of the Order of the White Robes.\n");
    WOHS_MANAGER->remove_council_white();

    return 1;

}

int
endorse_order_change(string str)
{
    str = lower_case(str);

    if(!str)
    {
       notify_fail("Endorse whom to change to the Order of the White Robes?\n");
       return 0;
    }

    if(!QUERY_WHITE_COUNCIL(TP))
    {
       write("You are not Head of the Order of the White Robes. You cannot " +
             "endorse anyone to change to the Order of the White Robes!\n");
       return 1;
    }

    string player;

    if(parse_command(str, environment(TP), "%w [to] 'change' 'to' [the] 'order' 'of' 'the' 'white' 'robes'", player))
    {
       if(!WOHS_MANAGER->query_passed_wohs_test(player))
       {
          write("That individual is not a Wizard of High Sorcery!\n");
          return 1;
       }

       if(WOHS_MANAGER->query_renegade_wohs(player))
       {
          write("That individual is a Renegade, and exiled from the Tower!\n");
          return 1;
       }

       if(WOHS_MANAGER->query_wohs_order_colour(player) == "white")
       {
          write("That individual is already of the Order of the White Robes!\n");
          return 1;
       } 

       if(WOHS_MANAGER->query_endorse_order_change(player, "white"))
       {
          write("That individual is already endorsed to join the Order of the White Robes!\n");
          return 1;
       } 

       WOHS_MANAGER->endorse_order_change(player, "white");
       write("You provide your endorsement for " +capitalize(player)+ " to change to " +
             "the Order of the White Robes.\n");
       return 1; 

    }
    write("Endorse <whom> to change to the Order of the White Robes?\n");
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

    if(!QUERY_WHITE_COUNCIL(TP))
    {
       write("You are not Head of the Order of the White Robes. You cannot " +
             "unendorse anyone!\n");
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

       if(!WOHS_MANAGER->query_endorse_order_change(player, "white"))
       {
          write("That individual isn't endorsed to join the Order of the White Robes!\n");
          return 1;
       } 

       WOHS_MANAGER->unendorse_order_change(player, "white");
       send_debug_message("wohs", capitalize(player)+ " has been unendorsed " +
           "to change to the Order of the White Robes.", LEADER_LOG);
       write("You unendorse " +capitalize(player)+ ".\n");
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

    if(!QUERY_WHITE_COUNCIL(TP))
    {
       write("You are not Head of the Order of the White Robes. You cannot " +
             "exile anyone!\n");
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
          write("That individual is already a Renegade, and exiled from the Tower!\n");
          return 1;
       }

       if(WOHS_MANAGER->query_wohs_order_colour(player) != "white")
       {
          write("That individual is not of the Order of the White Robes. You have no " +
             "authority to exile a member of another Order!\n");
          return 1;
       } 

       if(WOHS_MANAGER->query_council_voting_open("white"))
       {
          write("While there is a current ballot for the next Head of the Order of " +
              "the White Robes, you cannot declare anyone as renegade.\n");
          return 1;
       } 

       WOHS_MANAGER->set_renegade_wohs(player);
       write("You declare " +capitalize(player)+ " a Renegade of the Orders, and " +
             "banish them from the Tower of Wayreth!\n");
       find_player(player)->catch_msg("\nYou have been declared a Renegade of the " +
             "Orders and banished from the Tower of Wayreth!\n\nBe warned! If you are "+
             "slain while exiled you will be expelled from the Wizards of High " +
             "Sorcery!\n\n");

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

    if(!QUERY_WHITE_COUNCIL(TP))
    {
       write("You are not Head of the Order of the White Robes. You cannot " +
             "forgive anyone!\n");
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
          write("That individual is not a Renegade, so has nothing to be forgiven for?\n");
          return 1;
       }

       if(WOHS_MANAGER->query_wohs_order_colour(player) != "white")
       {
          write("That individual is not of the Order of the White Robes. You have no " +
             "authority to forgive a member of another Order!\n");
          return 1;
       } 

       if(WOHS_MANAGER->query_council_voting_open("white"))
       {
          write("While there is a current ballot for the next Head of the Order of " +
              "the White Robes, you cannot forgive renegades.\n");
          return 1;
       }

       WOHS_MANAGER->remove_renegade_wohs(player);
       send_debug_message("wohs", capitalize(player)
           + " has been forgiven and is no longer exiled from the Tower.", LEADER_LOG);
       write("You forgive " +capitalize(player)+ " and allow them to return to " +
             "the Tower of Wayreth!\n");
       find_player(player)->catch_msg("\nYou have been forgiven by the Conclave of High Sorcery " +
             "and may return to the Tower of Wayreth!\n\n");

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
       !QUERY_BLACK_COUNCIL(TP) && !TP->query_wiz_level())
    {
       write("You are not Head of an Order of High Sorcery. You do not have the " +
             "authority to invite an aspirant to take the Test!\n");
       return 1;
    }

    string player, sponsor;

    if(parse_command(str, environment(TP), "%w 'to' 'take' 'the' 'test' [of] [high] [sorcery]", player))
    {
       if(!WOHS_MANAGER->query_is_member(player))
       {
          write("That individual is not an Aspirant of High Sorcery!\n");
          return 1;
       }

       if(WOHS_MANAGER->query_aspirant_title(player))
       {
          write("That individual is not an Aspirant of High Sorcery. While a practicing magician, " +
            "they need to publicly display themselves as Aspirants before they can " +
            "be invited to sit the Test.\n");
          return 1;
       }

       if(WOHS_MANAGER->query_passed_wohs_test(player))
       {
          write("That individual has already passed the Test of High Sorcery!\n");
          return 1;
       }

       if(WOHS_MANAGER->query_invited_wohs_test(player))
       {
          write("That individual has already been invited to take the Test of High Sorcery!\n");
          return 1;
       }

       sponsor = TP->query_real_name();

       WOHS_MANAGER->set_invited_wohs_test(player);
       WOHS_MANAGER->add_invited_wohs_test_list(player, sponsor);
       write("You permit " +capitalize(player)+ " to take the Test of High Sorcery, and " +
             "invite them to enter the Hall of Mages at the Tower of Wayreth!\n");
       find_player(player)->catch_msg("\nYou have been permitted to take the Test of " +
             "High Sorcery, and have been invited to enter the Hall of Mages at the " +
             "Tower of Wayreth!\n\n");

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

    if(!QUERY_RED_COUNCIL(TP) && !QUERY_WHITE_COUNCIL(TP) && !QUERY_BLACK_COUNCIL(TP))
    {
       write("You are not Head of an Order of High Sorcery. You do not have the " +
             "authority to withdraw an invitation from an aspirant to take the Test!\n");
       return 1;
    }

    string player;

    if(parse_command(str, environment(TP), "'invitation' 'to' 'take' 'the' 'test' [of] [high] [sorcery] 'from' %w", player))
    {
       if(!WOHS_MANAGER->query_is_member(player))
       {
          write("That individual is not an Aspirant of High Sorcery!\n");
          return 1;
       }

       if(WOHS_MANAGER->query_passed_wohs_test(player))
       {
          write("That individual has already passed the Test of High Sorcery! Too late to withdraw " +
             "their invitation!\n");
          return 1;
       }

       if(WOHS_MANAGER->query_player_started_wohs_test(player))
       {
          write("That individual has started the Test of High Sorcery! Too late to withdraw " +
             "their invitation!\n");
          return 1;
       }

       if(!WOHS_MANAGER->query_invited_wohs_test(player))
       {
          write("That individual hasn't been invited to take the Test of High Sorcery.\n");
          return 1;
       }

       WOHS_MANAGER->remove_invited_wohs_test(player);
       WOHS_MANAGER->remove_invited_wohs_test_list(player);
       write("You withdraw the invitation for " +capitalize(player)+ " to take the Test of High Sorcery!\n");
       find_player(player)->catch_msg("\nYour invitation to take the Test of " +
             "High Sorcery has been withdrawn by " +QTNAME(TP)+ "!\n\n");

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
       write("You are not Head of an Order of High Sorcery. You do not have the " +
             "authority to review the list the members of High Sorcery!\n");
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
       write("Bizarrely it seems there are no Wizards of High Sorcery. I think you " +
             "need to take a lie down, or report this to a higher authority.\n");
       return 1;
    }

    foreach(string name, string order: list)
    {
        size++;
        loc += capitalize(name) + " of the Order of the " +capitalize(order)+ " Robes";
        if (m_sizeof(list) - size == 1)
            loc += ", and\n  ";
        else if (m_sizeof(list) - size > 1)
               loc += ",\n  ";
     }

     write("You read the list of the current Wizards of High Sorcery, noting " +
           "there are currently " +LANG_NUM2WORD(white_members)+
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
        write("There are no Wizards declared Renegade of the Orders at present.\n\n");
     }
     else
     {
        write("The following Wizards have been declared Renegade of the Orders and " +
              "have been banished from the Tower of Wayreth:\n  "+ ren + ".\n\n\n");
     }

    foreach(string name, string sponsor: aspirants)
    {
        size2++;
        asp += capitalize(name) + " has been invited by " +capitalize(sponsor)+ " to take the Test";
        if (m_sizeof(aspirants) - size2 == 1)
            asp += ", and\n  ";
        else if (m_sizeof(aspirants) - size2 > 1)
               asp += ",\n  ";
     }

     if(asp == "")
     {
        write("There are currently no Aspirants that have been invited to take the Test.\n\n");
     }
     else
     {
        write("Aspirants that have been invited to take the test:\n" +"  "+ asp + ".\n\n\n");
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
 
    if(!QUERY_WHITE_COUNCIL(TP))
    {
       write("You are not Head of the Order of the White Robes. You cannot " +
             "ban anyone!\n");
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
          write("That individual is already banned from training and the Tower storage!\n");
          return 1;
       }

/*
       if(WOHS_MANAGER->query_wohs_order_colour(player) != "white")
       {
          write("That individual is not of the Order of the White Robes. You have no " +
             "authority to ban a member of another Order!\n");
          return 1;
       } 
*/

       WOHS_MANAGER->set_wohs_train_rack_ban(player);
       write("You ban " +capitalize(player)+ " from accessing the training and " +
             "equipment rooms of the Tower.\n");
       find_player(player)->catch_msg("\nYou have been banned from accessing the " +
             "training and equipment rooms of the Tower!\n\n");
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
 
    if(!QUERY_WHITE_COUNCIL(TP))
    {
       write("You are not Head of the Order of the White Robes. You cannot " +
             "forgive anyone!\n");
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
       if(WOHS_MANAGER->query_wohs_order_colour(player) != "white")
       {
          write("That individual is not of the Order of the White Robes. You have no " +
             "authority to unban a member of another Order!\n");
          return 1;
       } 
*/

       WOHS_MANAGER->remove_wohs_train_rack_ban(player);
       send_debug_message("wohs", capitalize(player)
           + " has been unbanned from training and storage rooms of the Tower.", LEADER_LOG);
       write("You unban " +capitalize(player)+ " and allow them to access the training " +
             "and equipment rooms of the Tower of Wayreth!\n");
       find_player(player)->catch_msg("\nYou have been unbanned by the Conclave of High Sorcery " +
             "and may access the equipment and training rooms of the Tower of Wayreth!\n\n");

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
 
    if(!QUERY_WHITE_COUNCIL(TP) && !TP->query_wiz_level())
    {
       write("You are not Head of the Order of the White Robes. You do not have " +
             "access to those missives and logs!\n");
       return 1;
    }

    write("You thoroughly review the recent events to happen within the Orders of " +
             "High Sorcery...\n\n");
    TP->more(read_file(LEADER_LOG,1));

    return 1;
} 