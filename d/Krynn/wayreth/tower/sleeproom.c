/*
   Wayreth. Sleeping Quarters

   sleeproom.c
   -----------

   Coded ........: February 1997
   By ...........: Kentari

   Latest update : October 2016
   By........... : Arman

*/

#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/guilds/wohs/defs.h"

inherit TOWERROOM;

#include "/d/Genesis/specials/debugger/debugger_tell.h"

int white_countdown;

// Set to 1 if you want to turn off the automated Conclave voting system
#define VOTING_DISABLED  0

#define VOTE_LOG (WOHS_LOGS + "wohs_vote_outcome")

public void
create_tower_room()
{
   set_short("Sleeping quarters");
   set_long("Being so secluded, this room works quite well as the " + 
	"sleeping quarters for Wayreth Tower. In the " +
	"middle of the room large red, black and white curtains " +
	"separates the chamber for the wizards of the three Orders. Silence is the " +
	"understood policy to be in effect here, and any loud noises " +
	"or chatter would seem out of place. Wizards of High Sorcery may choose to " +
        "<start here> when entering the realms.\n");
	
   AI(({"curtains","large curtains","middle","red black and white curtains"}),
	"Curtains patterned with the three colors of the magic orders " +
	"separate the chamber for the privacy and respect of " +
	"the mages staying in Wayreth Tower.\n");

   add_exit(WTOWER + "meditation", "south", 0);
   add_prop(OBJ_I_LIGHT, 2);

   add_cmd_item("here", "start", "@@do_start");
}

int
do_start()
{
   if(this_player()->query_guild_name_occ() != WOHS_GUILD_NAME) 
   {
      notify_fail("Only Wizards of High Sorcery may stay in the Tower " +
          "of Wayreth!\n");
      return 0;
   }
   TP->set_default_start_location(WOHS_STARTROOM);
   write("You have decided to stay in the Tower of Wayreth, and will " +
       "start here when you enter the realms.\n");
   return 1;
}

//Election functions for WoHS

int
filter_wohs(object ob)
{
    if (ob->query_guild_name_occ() == WOHS_GUILD_NAME)
        return 1;
    
    return 0;
}

void
log_vote_outcome(string order)
{
   string outcome = "\nOutcome of the vote for the Head of the Order " +
       "of the " +C(order)+ " robes is as follows:\n\nNominations came " +
       "from "; 

   mapping nominees = WOHS_MANAGER->query_council_nomination_list(order);
   mapping voters = WOHS_MANAGER->query_has_voted(order);
   mapping final_votes = WOHS_MANAGER->query_council_vote_list(order);
   int     size = 0;

   foreach(string name, string order: nominees)
   {
        size++;
        outcome += capitalize(name) + " (lvl " +nominees[name]+ ")";
        if (m_sizeof(nominees) - size == 1)
            outcome += ", and ";
        else if (m_sizeof(nominees) - size > 1)
            outcome += ", ";
    }

    outcome += ".\nThe following members voted: ";

    size = 0;
    foreach(string name, string order: voters)
    {
        size++;
        outcome += capitalize(name);
        if (m_sizeof(voters) - size == 1)
            outcome += ", and ";
        else if (m_sizeof(voters) - size > 1)
            outcome += ", ";
    }

    outcome += ".\n\nThe voting outcome was as follows:\n";

    size = 0;
    foreach(string name, string order: final_votes)
    {
        size++;
        outcome += capitalize(name) + " tallied " +final_votes[name]+ 
            " vote(s)";

        if (m_sizeof(final_votes) - size == 1)
            outcome += ", and\n";
        else if (m_sizeof(final_votes) - size > 1)
            outcome += ",\n";
     }

     outcome += ".\n\n";

    send_debug_message("wohs", outcome, VOTE_LOG);
}

// Functions for the Order of the White Robes

void
start_white_election()
{
   DEBUG("White council election started.");

   // 86400 is one day, 864000 is 10 days
   int duration = time() + 864000;

   // int duration = time() + 60;

   filter(users(), filter_wohs)->catch_tell("\nA gust of wind whispers " +
       "past you, followed by a message: The Order of the White Robes " +
       "has commenced an election for the next Head of the Order to " +
       "represent them on the Conclave of Wizards.\n\n");

   WOHS_MANAGER->set_council_voting_open("white", duration);

}

public void
complete_white_election()
{
   // Check winner of election
   mapping results = WOHS_MANAGER->query_council_vote_list("white");
   string winner;
   int size, votes, highest_vote = 0;

   // If no-one has voted, we restart the process
   if(!m_sizeof(results))
   {
       DEBUG("Restarted white election due to no voters.");
       WOHS_MANAGER->clear_council_nomination_list("white");
       filter(users(), filter_wohs)->catch_tell("\nA gust of wind " +
           "whispers past you, followed by a message: Due to a lack of " +
           "votes, the election for Head of the Order of the White " +
           "Robes has been restarted.\n\n");
       start_white_election();
       return;
    }

   foreach(string nominee: m_indexes(results))
   {
      size++;
      votes = results[nominee];

      if(WOHS_MANAGER->query_wohs_order_colour(nominee) != "white")
      {
         DEBUG(nominee + " no longer white robe, vote set to zero.\n");
         votes = 0;
      }

      if(votes > highest_vote)
      {
         winner = nominee;
         highest_vote = votes;
         DEBUG("Highest vote changed to " +nominee+ ".");
      }
    }

   // check for a draw
   foreach(string nominee: m_indexes(results))
   {
      size++;
      votes = results[nominee];

      if(votes == highest_vote)
      {
         if(winner != nominee)
         {
            DEBUG("We have a draw.");
            mapping tiebreaker = WOHS_MANAGER->query_council_nomination_list("white");
            DEBUG("Winner level: " + tiebreaker[winner]+ 
                ", Nominee level: " +tiebreaker[nominee]);
            // highest ranking of those tied wins
            if(tiebreaker[winner] < tiebreaker[nominee])
            {
               winner = nominee;
               DEBUG("Winner switched to nominee");
            }
         }
      }
    }

   // Reset previous head of the white council
   WOHS_MANAGER->remove_council_white();
   DEBUG("White council reset.");

   // Set new head of order.
   if(winner)
   {
      WOHS_MANAGER->add_council_white(winner);
      DEBUG("New white head is "+winner+ ".");
      find_player(winner)->catch_msg("\nYou have been voted by your " +
          "peers to be the next Master of the Order of the White " +
          "Robes!\n\n");

      filter(users(), filter_wohs)->catch_tell("\nA gust of wind " +
          "whispers past you, followed by a message: The Order of the " +
          "White Robes has voted " +C(winner)+ " to be the next Head " +
          "of the Order to represent them on the Conclave of Wizards.\n\n");
    }

   // Log the vote
   log_vote_outcome("white");

   // Reset annual election timer
   WOHS_MANAGER->reset_annual_council_vote("white");

   // Reset new idle councillor indictment timer
   WOHS_MANAGER->add_council_last_login("white");

   // Close council voting
   WOHS_MANAGER->set_council_voting_open("white", 0);

   // Clear nomination list
   WOHS_MANAGER->clear_council_nomination_list("white");

   // Reset votes and voter list
   WOHS_MANAGER->clear_council_vote_list("white");
   WOHS_MANAGER->clear_has_voted("white");


}

public void
check_white_wohs_council()
{

   if(VOTING_DISABLED)
    return;

   // No members of the Order so no vote
   if(WOHS_MANAGER->count_wohs_order_members("white") == 0)
   {
       DEBUG("No white members, no election.");
       return;
    }

   // Check if White council position is empty and voting hasn't already started.
   if(!WOHS_MANAGER->query_is_council_white() &&
      !WOHS_MANAGER->query_council_voting_open("white"))
   {
       DEBUG("White council empty.");
       start_white_election();
       return;
    }

    // check if it is time for an annual election and a vote hasn't started
    if((time() > WOHS_MANAGER->query_next_annual_council_vote("white")) &&
      !WOHS_MANAGER->query_council_voting_open("white"))
    {
       DEBUG("Annual white election started.");
       start_white_election();
       return;
    }

    // Check if white vote currently open
    if(WOHS_MANAGER->query_council_voting_open("white"))
    {
       int vote_time = WOHS_MANAGER->query_council_voting_open("white");
       DEBUG("Time: " +time()+ ", Vote time: " +vote_time+ ".");

       if(time() > WOHS_MANAGER->query_council_voting_open("white"))
       {
          DEBUG("White council vote timer finished.");
          complete_white_election();
          return;
       }
    }

    return;
}

// Functions for the Order of the Red Robes

void
start_red_election()
{
   DEBUG("Red council election started.");

   // 86400 is one day, 864000 is 10 days
   int duration = time() + 864000;

   // int duration = time() + 60;

   filter(users(), filter_wohs)->catch_tell("\nA gust of wind whispers " +
       "past you, followed by a message: The Order of the Red Robes " +
       "has commenced an election for the next Head of the Order to " +
       "represent them on the Conclave of Wizards.\n\n");

   WOHS_MANAGER->set_council_voting_open("red", duration);

}

public void
complete_red_election()
{
   // Check winner of election
   mapping results = WOHS_MANAGER->query_council_vote_list("red");
   string winner;
   int size, votes, highest_vote = 0;

   // If no-one has voted, we restart the process
   if(!m_sizeof(results))
   {
       DEBUG("Restarted red election due to no voters.");
       WOHS_MANAGER->clear_council_nomination_list("red");
       filter(users(), filter_wohs)->catch_tell("\nA gust of wind " +
           "whispers past you, followed by a message: Due to a lack of " +
           "votes, the election for Head of the Order of the Red Robes " +
           "has been restarted.\n\n");
       start_red_election();
       return;
    }

   foreach(string nominee: m_indexes(results))
   {
      size++;
      votes = results[nominee];

      if(WOHS_MANAGER->query_wohs_order_colour(nominee) != "red")
      {
         DEBUG(nominee + " no longer red robe, vote set to zero.\n");
         votes = 0;
      }

      if(votes > highest_vote)
      {
         winner = nominee;
         highest_vote = votes;
         DEBUG("Highest vote changed to " +nominee+ ".");
      }
    }

   // check for a draw
   foreach(string nominee: m_indexes(results))
   {
      size++;
      votes = results[nominee];

      if(votes == highest_vote)
      {
         if(winner != nominee)
         {
            DEBUG("We have a draw.");
            mapping tiebreaker = WOHS_MANAGER->query_council_nomination_list("red");
            DEBUG("Winner level: " + tiebreaker[winner]+ 
                ", Nominee level: " +tiebreaker[nominee]);
            // highest ranking of those tied wins
            if(tiebreaker[winner] < tiebreaker[nominee])
            {
               winner = nominee;
               DEBUG("Winner switched to nominee");
            }
         }
      }
    }

   // Reset previous head of the red council
   WOHS_MANAGER->remove_council_red();
   DEBUG("Red council reset.");

   // Set new head of order.
   if(winner)
   {
      WOHS_MANAGER->add_council_red(winner);
      DEBUG("New red head is "+winner+ ".");
      find_player(winner)->catch_msg("\nYou have been voted by your " +
          "peers to be the next Master of the Order of the Red Robes!\n\n");

      filter(users(), filter_wohs)->catch_tell("\nA gust of wind " +
          "whispers past you, followed by a message: The Order of the " +
          "Red Robes has voted " +C(winner)+ " to be the next Head of " +
          "the Order to represent them on the Conclave of Wizards.\n\n");
   }

   // Log the vote
   log_vote_outcome("red");

   // Reset annual election timer
   WOHS_MANAGER->reset_annual_council_vote("red");

   // Reset new idle councillor indictment timer
   WOHS_MANAGER->add_council_last_login("red");

   // Close council voting
   WOHS_MANAGER->set_council_voting_open("red", 0);

   // Clear nomination list
   WOHS_MANAGER->clear_council_nomination_list("red");

   // Reset votes and voter list
   WOHS_MANAGER->clear_council_vote_list("red");
   WOHS_MANAGER->clear_has_voted("red");

}

public void
check_red_wohs_council()
{

   if(VOTING_DISABLED)
    return;

   // No members of the Order so no vote
   if(WOHS_MANAGER->count_wohs_order_members("red") == 0)
   {
       DEBUG("No red members, no election.");
       return;
    }

   // Check if Red council position is empty and voting hasn't already started.
   if(!WOHS_MANAGER->query_is_council_red() &&
      !WOHS_MANAGER->query_council_voting_open("red"))
   {
       DEBUG("Red council empty.");
       start_red_election();
       return;
    }

    // check if it is time for an annual election and a vote hasn't started
    if((time() > WOHS_MANAGER->query_next_annual_council_vote("red")) &&
      !WOHS_MANAGER->query_council_voting_open("red"))
    {
       DEBUG("Annual red election started.");
       start_red_election();
       return;
    }

    // Check if red vote currently open
    if(WOHS_MANAGER->query_council_voting_open("red"))
    {
       int vote_time = WOHS_MANAGER->query_council_voting_open("red");
       DEBUG("Time: " +time()+ ", Vote time: " +vote_time+ ".");

       if(time() > WOHS_MANAGER->query_council_voting_open("red"))
       {
          DEBUG("Red council vote timer finished.");
          complete_red_election();
          return;
       }
    }

    return;
}

// Functions for the Order of the Black Robes

void
start_black_election()
{
   DEBUG("Black council election started.");

   // 86400 is one day, 864000 is 10 days
   int duration = time() + 864000;

   // int duration = time() + 60;

   filter(users(), filter_wohs)->catch_tell("\nA gust of wind whispers " +
       "past you, followed by a message: The Order of the Black Robes " +
       "has commenced an election for the next Head of the Order to " +
       "represent them on the Conclave of Wizards.\n\n");

   WOHS_MANAGER->set_council_voting_open("black", duration);

}

public void
complete_black_election()
{
   // Check winner of election
   mapping results = WOHS_MANAGER->query_council_vote_list("black");
   string winner;
   int size, votes, highest_vote = 0;

   // If no-one has voted, we restart the process
   if(!m_sizeof(results))
   {
       DEBUG("Restarted black election due to no voters.");
       WOHS_MANAGER->clear_council_nomination_list("black");
       filter(users(), filter_wohs)->catch_tell("\nA gust of wind " +
           "whispers past you, followed by a message: Due to a lack of " +
           "votes, the election for Head of the Order of the Black Robes " +
           "has been restarted.\n\n");
       start_black_election();
       return;
    }

   foreach(string nominee: m_indexes(results))
   {
      size++;
      votes = results[nominee];

      if(WOHS_MANAGER->query_wohs_order_colour(nominee) != "black")
      {
         DEBUG(nominee + " no longer black robe, vote set to zero.\n");
         votes = 0;
      }

      if(votes > highest_vote)
      {
         winner = nominee;
         highest_vote = votes;
         DEBUG("Highest vote changed to " +nominee+ ".");
      }
    }

   // check for a draw
   foreach(string nominee: m_indexes(results))
   {
      size++;
      votes = results[nominee];

      if(votes == highest_vote)
      {
         if(winner != nominee)
         {
            DEBUG("We have a draw.");
            mapping tiebreaker = WOHS_MANAGER->query_council_nomination_list("black");
            DEBUG("Winner level: " + tiebreaker[winner]+ 
                ", Nominee level: " +tiebreaker[nominee]);
            // highest ranking of those tied wins
            if(tiebreaker[winner] < tiebreaker[nominee])
            {
               winner = nominee;
               DEBUG("Winner switched to nominee");
            }
         }
      }
    }

   // Reset previous head of the black council
   WOHS_MANAGER->remove_council_black();
   DEBUG("Black council reset.");

   // Set new head of order.
   if(winner)
   {
      WOHS_MANAGER->add_council_black(winner);
      DEBUG("New black head is "+winner+ ".");
      find_player(winner)->catch_msg("\nYou have been voted by your " +
          "peers to be the next Master of the Order of the Black " +
          "Robes!\n\n");

      filter(users(), filter_wohs)->catch_tell("\nA gust of wind " +
          "whispers past you, followed by a message: The Order of the " +
          "Black Robes has voted " +C(winner)+ " to be the next Head " +
          "of the Order to represent them on the Conclave of Wizards.\n\n");
   }

   // Log the vote
   log_vote_outcome("black");

   // Reset annual election timer
   WOHS_MANAGER->reset_annual_council_vote("black");

   // Reset new idle councillor indictment timer
   WOHS_MANAGER->add_council_last_login("black");

   // Close council voting
   WOHS_MANAGER->set_council_voting_open("black", 0);

   // Clear nomination list
   WOHS_MANAGER->clear_council_nomination_list("black");

   // Reset votes and voter list
   WOHS_MANAGER->clear_council_vote_list("black");
   WOHS_MANAGER->clear_has_voted("black");

}

public void
check_black_wohs_council()
{

   if(VOTING_DISABLED)
    return;

   // No members of the Order so no vote
   if(WOHS_MANAGER->count_wohs_order_members("black") == 0)
   {
       DEBUG("No black members, no election.");
       return;
    }

   // Check if black council position is empty and voting hasn't already started.
   if(!WOHS_MANAGER->query_is_council_black() &&
      !WOHS_MANAGER->query_council_voting_open("black"))
   {
       DEBUG("black council empty.");
       start_black_election();
       return;
    }

    // check if it is time for an annual election and a vote hasn't started
    if((time() > WOHS_MANAGER->query_next_annual_council_vote("black")) &&
      !WOHS_MANAGER->query_council_voting_open("black"))
    {
       DEBUG("Annual black election started.");
       start_black_election();
       return;
    }

    // Check if black vote currently open
    if(WOHS_MANAGER->query_council_voting_open("black"))
    {
       int vote_time = WOHS_MANAGER->query_council_voting_open("black");
       DEBUG("Time: " +time()+ ", Vote time: " +vote_time+ ".");

       if(time() > WOHS_MANAGER->query_council_voting_open("black"))
       {
          DEBUG("black council vote timer finished.");
          complete_black_election();
          return;
       }
    }

    return;
}  

public void
check_all_wohs_council_votes()
{
     check_white_wohs_council();
     check_red_wohs_council();
     check_black_wohs_council();
}

/*
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 *                We need to add the drown object to livings who enter.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 */
public void
enter_inv(object ob, object from)
{
     ::enter_inv(ob, from);

     check_all_wohs_council_votes();
}

