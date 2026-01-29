// -*-C++-*-
// file name: ~Avenir/common/dark/l4/cr.c
// creator(s):  Boriska Nov 9 1995
// last update: Jan 27 1995
// purpose:     Area handler, creates spreadsheet like area
//              Overloads communication and emotes in the area,
//              Creates echo effect.
//              Adds some features common for all rooms in the area,
//              required by the magic square quest.
// note:
// bug(s):
// to-do:     

inherit "/std/room";

#include "/d/Avenir/common/dark/dark.h"
#include "/d/Avenir/include/magic_square.h"

// Every open space has its bounds.
#define X_MAX 4
#define Y_MAX 4

static mixed *exits = ({
  ({"northwest", "north", "northeast"}),
  ({"west", "nowhere", "east"}),
  ({"southwest", "south", "southeast"})
});

static mapping vowels = ([ "a" : 1, "e" : 1, "i" : 1, "o" : 1, "u" : 1 ]);
		   
void
create_room()
{

  string *path;
  string room, base;
  int x,y,i,j;
 
  set_short("vast undeground cavern");
   
  set_long("This is a vast underground cavern. Your steps are echoing " +
	   "from the walls, floor and high ceiling which you cannot see in pitch " +
	   "darkness.\n");
  
  base = file_name(this_object());

  path = explode (base, "/");

  // room file name, without trailing ".c"
  room = path [sizeof(path)-1];

  // sanity check
  if (strlen(room) < 2)
    return;
  
  // extract x and y values, convert them to int.
  x = room[strlen(room)-2] - '0';
  y = room[strlen(room)-1] - '0';

  // full path to room w/o x and y
  base = base[0..strlen(base)-3];

  for (i = MAX(0,x-1); i <= MIN(x+1, X_MAX); i++)
    for (j = MAX(0,y-1); j <= MIN(y+1, Y_MAX); j++)
      add_exit (base + i + j, exits[i-x+1][j-y+1]);
	
  // remove_exit ("nowhere");
  // Ogre lives nowhere could be fun..

  // Hardcoding the square of size 3 in the center of 5x5 area here.
  // It does not appear to me that the size is going to be changed...
  if ( ABS(x - 2) <= 1 && ABS(y - 2) <= 1)
    add_item (({"floor","blood", "mark", "marks"}),
	      "There are blood marks on the floor!\n");
  else
    add_item ("floor", "The floor under your feet is a clean bed rock.\n");
  add_item("ceiling", "You cannot see much about it in the dark.\n");
  add_item(({"walls", "wall"}),
	   "The walls are clean bed rock.\n");
  add_prop(ROOM_I_LIGHT,0);
  IN;
  set_noshow_obvious(1);
}

void
init()
{
  ::init();
  // overload communications
  add_action ("do_echo", "say");
  add_action ("do_echo", "'", 1);
  add_action ("do_echo", "shout");
  add_action ("do_echo", "ponder");
  add_action ("do_echo", "think");
  add_action ("do_echo", "rsay");
}

int
do_echo (string str)
{
  string verb = query_verb();
  
  if (verb == "ponder")
    {
      write ("You ponder your life and feel relaxed.\n");
      return 1;
    }
  if (verb == "think")
    {
      write ("It is really hard to think about anything in this place.\n");
      return 1;
    }
  if (verb == "rsay")
    {
      write
     ("This insane place made you forget the last bits of your mother tongue.\n");
      return 1;
    }
  if (!str || strlen(str) < 2 )
    return 0;
  set_alarm ( 2.0, 0.0, "echo", str);
  return 0;
}


private void
echo (string str)
{
  int i, len = strlen(str);

  
  for ( i=len-2; i >=0; i--)
    // find consonant/vowel pair closest to the end of string
    if ( vowels [str[i+1..i+1]] && !vowels[str[i..i]])
      {
       tell_room (this_object(),
		  str[i..len-1] + "..." + str[i+1..len-1] + "\n");
	break;
      }
  return;
}
