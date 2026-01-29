/*
 * /d/Rhovanion/anduin/andu_serv.c
 *
 */
inherit "/d/Rhovanion/lib/mapserver";

#include <ss_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Rhovanion/defs.h"

#define CLOCK "/d/Gondor/elessar/lib/clock"
#define TIME (string)CLOCK->query_time_of_day()

/*
 * Function name: query_file_with_map
 * Description:	  This function is necessary to redefine
 * Returns:	  Should return string or object that defines function
 *                string *map()  (actual map of the area)
 */
mixed
query_file_with_map()
{
    return "/d/Rhovanion/quetzl/andutesting/tmap";
}

int
this_is_room(string arg)
{
  if((arg == "r") || (arg == "R") || (arg == "M") || (arg == "K"))
      return 0;
  return ::this_is_room(arg);
}

int
query_map_fatigue(string here)
{
  if (here == "P") 
  return ::query_map_fatigue(here);
      return 5;
}

/*
 * Function name: query_paths
 * Returns:	  Should return array of letters representing paths on map
 */
string *
query_paths()
{
  return ({ "P" });
}

string
path_desc_start(string where)
{
  if(where == "P")
    return "The oldpath continues to the ";
  return ::path_desc_start(where);
}

string
path_desc_end(string where)
{
  if(where == "P")
    return " through Anduin";
  return ::path_desc_end(where);
}

string *query_show()
{
  return ({ "M","K","R","r","B","E" });
}

string
neighbour_desc_start(string from, string to)
{
  if(to == "M")
      return "The Misty Mountains loom over you to the ";
  if(to == "P")
      return "The Old Path is to the ";
  if(to == "R")
      return "The Anduin river flows past to the ";
  if(to == "r")
      return "A tributary of the Anduin flows quietly by to the ";
  if(to == "B")
      return "There is a large house to the ";
  if(to == "E")
      return "There is something that looks like a large nest to the ";
  if(to == "K")
      return "Mirkwood Forest lies dark and gloomy to the ";
  return ::neighbour_desc_start(from, to);
}

void
reset_map_room(string where)
{}

/*
 * Function name: set_up_room
 * Description:	  Called when room from map is created
 * Argument:	  where - letter from the map corresponding to this room
 * Usage:         Here you should set things like descriprions, items,
 *                properties etc for your room.
 */
void
set_up_room(string str)
{
  switch (str)
  {
    case "x":
    case "p":
    case "X":
    case "H":
    case "T":
	set_short("Plains of Anduin");
	set_long("@@my_long:"+file_name(TO)+"|"+str+"@@");
        add_exits();
	break;
    case "P":
	set_short("Oldpath");
	set_long("@@my_long:"+file_name(TO)+"|"+str+"@@");
        add_exits();
	break;
    case "E":
        set_short("Eagle's Eyrie");
        set_long("None of the Eagles seem to be home at the moment.\n");
        add_exits();
        break;
    case "B":
        set_short("Outside of Beorn's House");
        set_long("There is a large house here in the northeastern part of " +
            "the Vale of Anduin, the door stands open.\n");
        add_exits();
        break;
  }
  reset_room();
}

/*
 * Function name: player_is_lost
 * Description:	  Test if player lost directions
 * Argument:	  who - object living
 * Returns:	  1 if lost,  0 if knows directions
 */
int
player_is_lost(object who, string where)
{
    return 0;
}

string x_long()
{
    string text;

        switch(TIME)
        {
            case "early morning":
                switch(random(2))
                {
                case 0:
                    text =
                    "The sun is rising over the Vale of Anduin, filling the " +
                    "valley with the sounds of awakening animals and the " +
                    "quiet whisper of wind through the long brown grass.  " +
                    "Looking up you see the sun shining through the branches " +
                    "of a distant tree."; break;
                case 1:
                    text =
                    "Dawn has arrived in the Vale of Anduin.  The sun is " +
                    "ascending into the sky, chasing the shadows back before " +
                    "it.  The sunlight glistens off of the dew on the grass, " +
                    "and in the distance, you see fog rising off of the " +
                    "river."; break;
                 } break;
            case "morning": text =
                "It is morning in Anduin, and the sound of birds singing " +
                "fills the still air with music.  The sun is warm and " +
                "bright above you."; break;
            case "noon": text =
                "The sun is directly overhead, and shines down on the " +
                "whole valley.  In the distance you see a reflection off " +
                "of the mighty river."; break;
            case "afternoon": text =
                "The sun is beginning to drop down from the sky again, " +
                "and though it is not yet evening, you can feel the " +
                "night approaching."; break;
            case "evening": text =
                "Evening has come to the Vale of Anduin, and with it " +
                "comes the sound of distant owls hooting, and the faint " +
                "shining of stars in the dusky sky."; break;
            case "night": text =
                "Night has fallen.  The gelid moon hangs huge and white " +
                "in the sky.  Stars shine down in pinpoints of white fire, " +
                "reflecting off of the Anduin river-- making it a silver " +
                "ribbon of light in the darkness."; break; 
        }
    return text;
}

string
my_long(string arg)
{
    string text;

    switch(arg)
    {
        case "X":
        case "p":
        case "H":
        case "T":
        case "x": text = x_long(); break;   
        case "P": text = "This is the Oldpath which runs through Anduin.  " +
            "It is kept clear by the efforts of the woodsmen and the elves " +
            "who live in the area, otherwise the dark forces from Mirkwood " +
            "would have overrun it long ago."; break;
    }
    return text+"\n";
}

