inherit "/d/Shire/khazad/moria_room_westcamp";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

/* Global Variables */

int wall_searched = 0;
int writing_read  = 0;
int runes_cleaned = 0;
int door_opened   = 0; 

void
create_moria_room()
{
  set_short("@@short_description@@");
  set_long("@@long_description@@");
 
  add_item(({ "wall", "walls" }),
     "They surround you on three sides, the highest one being the "+
     "north face of the depression.\n");
  add_item("face",
     "A flat high wall. Rather non-descript.\n");
  add_item(({ "writing", "runes" }), "@@runes");
/*
  add_item(({ "ceiling", "roof" }),
  add_item(({ "walls", "wall" }),
  add_item(({ "ground", "floor" }),
  add_item(({ "stalactite", "stalactites" }),
  add_item(({ "stalagmite", "stalagmites" }),
  add_item(({ "bat", "bats" }),
  add_item("cavern",
  add_item("insect", "insects", "beetles", "scorpions" }),
  add_item(({ "path", "paths" }),
  add_item(({ "pillar", "pillars" }),
  add_item("tower",

*/
  add_prop("_obj_s_search_fun","do_search");
 
  add_exit("/d/Shire/khazad/wcamp/westcamp5","south",0,1);
  add_exit("/d/Shire/khazad/wcamp/camp_tunnel1","north","@@check_door@@");
  set_noshow_obvious(1);
}

string
short_description()
{
  if (door_opened)
  {
    return "In a dim cavern.\n"+
           "There are two obvious exits: north, south";
  }
 
  else
  {
    return "In a dim cavern.\n"+
           "There is one obvious exit: south";
  }
}
 
string
long_description()
{
  if (door_opened)
  {
    return "You stand in a small depression. Stalagmites "+
           "practically block any further passage here. The path "+
           "seems to come to an end here. A tower rises above "+
           "the stalagmites off a ways to the southeast. A single "+
           "well worn path leads away from here to the south. In "+
           "the north face of the wall a stone door has been "+
           "opened.\n"+
           "There are two obvious exits: north, south.\n";
  }

  else
  {
    return "You stand in a small depression. Stalagmites "+
           "practically block any further passage here. The path "+
           "seems to come to an end here. A tower rises above "+
           "the stalagmites off a ways to the southeast. A single "+
           "well worn path leads away from here to the south.\n"+
           "There is one obvious exit: south.\n";
  }
}

string
runes()
{
  if (wall_searched)
  {
    writing_read = 1;;
    return "The writing appears to be ancient runes indecipherable "+
           "to you. You have a hard time making all of them out due "+
           "to the layers of dirt and grime that cover portions of it.\n";
  }

  else
    return "You find no writing.\n";
}

string
do_search(object searcher, string str)
{
  if (str != "wall")
    return 0;
  else
  {
    wall_searched = 1;
    return "You find faint traces of some writing on the nothern wall.\n";
  }
}

int
read_runes(string str)
{
  if (str != "runes")
  {
    notify_fail("Wipe what?\n");
    return 0;
  }

  if (writing_read)
  {
    write("You wipe the grime from the runes.\n");

/*    write("They read: "+
 *         "\n\n          Speak the name of the Deathless one to pass.\n\n");
 */
    runes_cleaned = 1;
    return 1;
  }
  
  else
  {
    notify_fail("You find no runes.\n");
    return 0;
  }
}

int
understand_runes(string str)
{
  int my_int = TP->query_stat(SS_INT);
  int my_skill = TP->query_skill(SS_LANGUAGE);

  if (!str)
    return 0;

  if (str != "runes")
  {
    notify_fail("Read what?\n");
    return 0;
  }

  else
  {
    if (!writing_read)
      return 0;

    if (!runes_cleaned)
      return 0;

    if ((my_int + my_skill) < 200)
    {
      write("You are certain these runes were made by dwarves but "+
            "you just can't seem to figure out what they mean.\n");
      return 1;
    }

    else
    {
      write("\n\n          Hail the Deathless One to pass.\n\n");
      return 1;
    }
  }
}

  int
open_door(string str)
{
  if (str != "durin")
    return 0;
   
  else
  {
    if (!writing_read)
      return 0;
  
    if (!runes_cleaned)
      return 0;
 
    else
    {
      write("You hail the ancient Lord of Khazad-dum.\n");
      say(QCTNAME(TP) + " hails an ancient name.\n");
      tell_room(TO, "The outline of a door glows faintly for a brief "+
            "second. Slowly a portion of the northern wall receedes "+
            "revealing a dark passage.\n");
      door_opened = 1;
      return 1;
    }
  }
}
 
void
init()
{
  ::init();
  add_action(read_runes,"dust");
  add_action(read_runes,"clean");
  add_action(read_runes,"wipe");
  add_action(understand_runes,"read");
  add_action(open_door,"hail");
}
 
int
check_door()
{
  if (!door_opened)
  {
    write("There is no obvious exit north.\n");
    return 1;
  }

  else
    return 0;
}
