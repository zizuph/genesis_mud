/* created by Aridor 02/09/94 */

#include "../local.h"

inherit ROOM_BASE

#define MY_EXITS        ({"2","4","7","5"})
#define EXIT_DIR        ({"north","west","south","east"})
#define COMPLE_EXIT_DIR ({"south","east","north","west"})
#define DEFAULT_DIR     2

int exit = DEFAULT_DIR;
int busy_turn = 0;

/*Prototype*/
void rumble_in_all_rooms();
varargs string turn_room_left(int silent = 0);
varargs string turn_room_right(int silent = 0);


void
reset_thief_room()
{
    string str;
    if (random(4))
      return;

    str = ("A small gnome arrives.\n" +
	   "The small gnome turns the wheel.\n");
    tell_room(TO,({ str, str, ""}));
    if (random(2))
      turn_room_left(1);
    else
      turn_room_right(1);
    str = ("The small gnome leaves.\n");
    tell_room(TO,({ str, str, ""}));
}

void
create_thief_room()
{
    set_short("In a cavern");
    set_long("This is a cavern. There is a glittering pole in the middle of the room, " +
	     "with a circular staircase winding itself upwards " +
	     "around it and disappears into darkness above. A strange wheel is " +
	     "fastened to the pole at about waist-height.\n");
    
    add_exit(TURNC, "up");
    add_exit(CAVERN + "b" + MY_EXITS[exit], EXIT_DIR[exit]);
    
    add_cmd_parse("[the] 'wheel' [to] [the] 'right'","turn",
		  "@@turn_room_right");
    add_cmd_parse("[the] 'wheel' [to] [the] 'left'","turn",
		  "@@turn_room_left");
    add_cmd_parse("[the] 'wheel'","turn",
		  "In which direction do you want to turn the wheel?\n");
    
    DARK;
    
    add_item(({"pole"}),
	     "The pole in the center of the room reaches from floor to " +
	     "ceiling and has a strange wheel fastened to it.\n");
    add_item(({"wheel"}),
	     "It is a round wheel made from iron with a diameter of about one foot. " +
	     "The wheel and the pole are actually just one piece.\n");
}


varargs string
turn_room_left(int silent = 0)
{
    (TURNC)->turn_me_left(silent);
    return "";
}

varargs string
turn_room_right(int silent = 0)
{
    (TURNC)->turn_me_right(silent);
    return "";
}

void
quiet_in_all_rooms()
{
    int i;
    tell_room(TO, "The room has stopped moving and all is quiet again, maybe even too quiet?\n");
    tell_room(TURNC, "The rumbling ceases and everything is quiet again, maybe even too quiet?\n");
    tell_room(TURNA, "The rumbling ceases and everything is quiet again, maybe even too quiet?\n");
    for(i=0; i<sizeof(MY_EXITS); i++)
      tell_room(CAVERN + "b" + MY_EXITS[i], "The rumbling ceases and everything is quiet again, maybe even too quiet?\n");
    busy_turn = 0;
    
}

void
rumble_in_all_rooms()
{
    int i;
    tell_room(TO, "Grrrr!\nYou hear a strange rumbling noise all around you and " +
	      "suddenly the room starts to move!\n");
    tell_room(TURNC, "You hear the floor starting to rumble a little...\n");
    tell_room(TURNA, "You hear the ceiling starting to rumble a little...\n");
    for(i=0; i<sizeof(MY_EXITS); i++)
      tell_room(CAVERN + "b" + MY_EXITS[i], "You hear the wall to your " + COMPLE_EXIT_DIR[i] + " starting to rumble.\n");
    
    set_alarm(7.0,0.0,"quiet_in_all_rooms");
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
    
    add_exit(CAVERN + "b" + MY_EXITS[exit], EXIT_DIR[exit]);
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
    
    add_exit(CAVERN + "b" + MY_EXITS[exit], EXIT_DIR[exit]);
}


string
query_exit_direction()
{
    return EXIT_DIR[exit];
}
