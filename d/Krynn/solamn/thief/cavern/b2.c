/* created by Aridor 02/09/94 */

#include "../guild/guild.h"

inherit ROOM_BASE

#include <macros.h>

void
create_thief_room()
{
    set_short("In a cavern.\nThere is one obvious exit: south");
    set_long("This is a cavern. This cavern is completely void except for the " +
	     "door at the north wall.\nThere is a door leading north.\n" +
	     "There is one obvious exit: south.\n");
    
    set_noshow_obvious(1);
    add_exit(JOIN_ROOM,"north","@@only_with_quest");
    add_exit(TURNB,"south","@@if_open");
    
    DARK;
    
    add_item("door",
	     "It's an ordinary looking, very strong iron door. " +
	     "You think you can make out some old paint on the door. " +
	     "However, you cannot see a lock.\n");
    add_search("door",1,"You're not too sure, but it could just be the word " +
	       "'Treasury' that's been written on the door.\n");
    add_item(({"old paint","paint"}),
	     "You're not too sure, but it could just be the word 'Treasury' " +
	     "that's been written there.\n");
    add_cmd_item("door","open",VBFC_ME("open_door"));
}

string
open_door()
{
    if ((TP->query_prop(THIEF_I_CAN_ENTER) == 15 ||
	 MEMBER(TP)) /* && !BANISHED(TP) */ && !sizeof(TP->query_team_others()))
      return "You can just go north to open the door.\n";
    return "You try to open the door but it won't budge.\n";
}

int
only_with_quest()
{
    if ((TP->query_prop(THIEF_I_CAN_ENTER) == 15 ||
	 MEMBER(TP)) /* && !BANISHED(TP) */ && !sizeof(TP->query_team_others()))
      {
	  SAY(" opens the door.\n");
	  tell_room(JOIN_ROOM, "The door opens.\n");
	  set_alarm(1.0,0.0,"close_again");
	  write("You open the door, walk through, and close the door again.\n");
	  
	  /*reward exp if solved for the first time.*/
	  if (TP->query_prop(THIEF_I_CAN_ENTER) == 15 && !MEMBER(TP) &&
	      !TP->test_bit("Krynn",GUILD_GROUP, QUEST_BIT))
	    {
		seteuid(getuid(TO));
                K_QUEST_LOG("guild/thief/quest", "Entrance quest", TP,
			    QUEST_EXP);

		write("You feel more experienced!\n");
		TP->set_bit(GUILD_GROUP, QUEST_BIT);
		TP->add_exp(QUEST_EXP);
	    }
	  TP->remove_prop(THIEF_I_CAN_ENTER);
	  
	  return 0;
      }
    write("You try in vain, but the door won't budge.\n");
    TELL_ROOM(TO, TP, " rambles about at the door, but fails to accomplish " +
	      "anything.", TP);
    tell_room(JOIN_ROOM, "You can hear someone rambling on the door.\n");
    return 1;
}

void
close_again()
{
    tell_room(TO,"The door closes again.\n");
    TELL_ROOM(JOIN_ROOM, TP, " closes the door.\n", TP);
}


int
if_open()
{
    if ((TURNB)->query_exit_direction() == "north")
      return 0;
    write("You find that it is impossible to leave the room as the door " +
	  "ends in a brick wall!\nYou push again, and suddenly you fall " +
	  "through the wall into another room, the wall slamming back " +
	  "into place behind you.\n");
    return 0;
}

