/* created by Aridor 02/09/94 */

#include "../local.h"

inherit ROOM_BASE

#define MY_EXITS        ({"2","4","7","5"})
#define EXIT_DIR        ({"north","west","south","east"})
#define COMPLE_EXIT_DIR ({"south","east","north","west"})
#define DEFAULT_DIR     3

int exit = DEFAULT_DIR;
int busy_turn = 0;

/*Prototype*/
void rumble_in_all_rooms();

void
create_thief_room()
{
  set_short("In a cavern");
  set_long("This is a cavern. There is a wooden spiral staircase in the " +
	   "middle of the room leading down and an exit leading " +
	   "@@query_exit_direction@@. Otherwise the room is bare.\n");
  
  add_exit(TURNB, "down");
  add_exit(CAVERN + "c" + MY_EXITS[exit], EXIT_DIR[exit]);

  DARK;

  add_item(({"stairs","staircase"}),
	   "These are simple wooden stairs circling down into darkness.\n");
}

void
quiet_in_all_rooms()
{
  int i;
  tell_room(TO, "The room has stopped moving and all is quiet again, maybe even too quiet?\n");
  tell_room(TURNB, "The rumbling ceases and everything is quiet again, maybe even too quiet?\n");
  for(i=0; i<sizeof(MY_EXITS); i++)
    tell_room(CAVERN + "c" + MY_EXITS[i], "The rumbling ceases and everything is quiet again, maybe even too quiet?\n");
  busy_turn = 0;
}


void
rumble_in_all_rooms()
{
  int i;
  tell_room(TO, "Grrrr!\nYou hear a strange rumbling noise all around you and " +
	    "suddenly the room starts to move!\n");
  tell_room(TURNB, "You hear the ceiling starting to rumble a little...\n");
  for(i=0; i<sizeof(MY_EXITS); i++)
    tell_room(CAVERN + "c" + MY_EXITS[i], "You hear the wall to your " + COMPLE_EXIT_DIR[i] + " starting to rumble.\n");

  set_alarm(5.0,0.0,"quiet_in_all_rooms");

}


void
turn_me_left(int silent)
{
  if (busy_turn)
    {
	if (!silent)
	  write("The wheel cannot be moved at the moment.\n");
	return;
    }
  if (!silent)
    write("You turn the wheel around to the left once.\n");
  busy_turn = 1;
  remove_exit(EXIT_DIR[exit]);
  exit -= 1;
  if (exit < 0)
    exit = 3;

  /*tell rumbling to all adjacent rooms */
  rumble_in_all_rooms();

  add_exit(CAVERN + "c" + MY_EXITS[exit], EXIT_DIR[exit]);
}


void
turn_me_right(int silent)
{
    if (busy_turn)
    {
	if (!silent)
	  write("The wheel cannot be moved at the moment.\n");
	return;
    }
    if (!silent)
      write("You turn the wheel around to the right once.\n");
    busy_turn = 1;
    remove_exit(EXIT_DIR[exit]);
    exit += 1;
    if (exit > 3)
      exit = 0;
    
    /*tell rumbling to all adjacent rooms */
    rumble_in_all_rooms();
    
    add_exit(CAVERN + "c" + MY_EXITS[exit], EXIT_DIR[exit]);
}


string
query_exit_direction()
{
  return EXIT_DIR[exit];
}
