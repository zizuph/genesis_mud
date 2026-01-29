#pragma strict_types
#include "/d/Avenir/common/common.h"
#include "./defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <terrain.h>

inherit "/std/room";


void
create_room()
{
    set_short("A small bedroom");
    set_long("This is a small bedroom in the dilapidated old manor. "+
        "Actually it is oddly small for no obvious reason at all. " +
        "Dust swirls underfoot and the air has a faint musty smell. "+
        "The walls are of indeterminate colour after so many years "+
        "neglect, and the once-white ceiling is cracked in a few "+
        "places. The room is bare of any items that might give you "+
        "some hints as to the personality of those who once occupied "+
        "it. All that remains is a bed, a chest of drawers with a mirror "+
        "and a small carpet on the floor.\n");
    add_item(({"bed", "mattress"}),
        "You take a step forward and sit down on the " +
        "small bed. Its relatively hard and you couldn't bounce on it " +
        "even if you wanted to.\n");
    add_item(({"chest","chest of drawers","drawers"}),"You " +
        "touch the chest of drawers with your hands. This chest " +
        "is very well made and has a very solid look.\n");
    add_cmd_item(({"chest","chest of drawers","drawers"}), "open",
        "The empty drawers open and close smoothly.\n");
    add_item("mirror","You take a quick look in the mirror " +
        "and see the usual sight of yourself.\n");
    add_item("carpet","You kneel down and examine the carpet " +
        "carefully. It is a small rug and you roll it to the side " +
        "to see if anything is hidden under it. Nothing can " +
        "be found though, so you return it to its former place.\n");
    add_item(({"wall","walls"}),"You take a glance at the walls and " +
        "see a small painting on the left wall.\n");
    add_item(({"painting"}),
        "You take a closer look at this small painting. " +
        "It is amazingly detailed and you realise this is a nice piece of " +
        "art that was probably very appreciated by the owner. You can " +
        "clearly make out a lake with a small boat on it. The boat is " +
        "illuminated by a shaft of light and far away above the treetops " +
        "you can see the tower of the house.\n");
    add_item(({"ceiling", "crack", "cracks"}), 
        "You stand on the lumpy mattress to get a better look at the "+
        "ceiling.\nUpon closer inspection, you realize that your effort "+
        "was in vain. The cracks in the ceiling are not the least bit "+
        "interesting.\n");
    add_item("left wall", "On the left wall is hanging a small " +
        "painting.\n");
    add_item("right wall", "There is something slightly odd with " +
        "the right wall. The colour is perhaps a tad different " +
        "but it also doesnt look as robust like the rest of the building.\n");
    set_terrain(TERRAIN_RESIDENCE);
    add_exit("platform","south");
    add_prop(OBJ_S_SEARCH_FUN, "search_right_wall");

    IN_IN;
    reset_room();
}

void
reset_room()
{

}

void
init()
{
    ::init();
    add_action("do_knock", "knock");
    add_action("open_drawer", "open");
    add_action("measure_bedroom","measure");
    add_action("break_wall","break");
    add_action("break_wall","tear");
}

int
do_knock(string str)
{
  if (strlen(str) && (str == "on wall" || str == "on walls" || str == "on left wall"))
  {
      write("You walk up to the left wall and place your ear close. " +
          "Nothing unusual can be heard from the wall.\n");
          return 1;
  }
  if (strlen(str) && (str == "on right wall" || str == "on the right wall"))
  {
      write("You walk up to the right wall and place your ear close. " +
          "When you gently tap on the wall you can hear a hollow sound.\n");
          return 1;
  }
  else
      if (strlen(str))
      {
          write("You make a move to knock on something, but decide its " +
              "unnecessary.\n");
              return 1;
      }
      return 0;
}

int
open_drawer(string str)
{
    if (strlen(str) && (str == "drawer" || str == "drawers" || str == "chest"))
    {
    write("You pull out one of the drawers. Its empty. " +
        "The hollow sound from the wooden chest tells you " +
        "that nothing is stored in either of the drawers.\n");
        return 1;
    }
}

string
search_right_wall(object player, string str)
{
    object ob;

    switch (str)
    {
        case ("right wall"):
            say(({METNAME + " steps up to the right wall and starts to search " +
                "it closely.\n",
            TART_NONMETNAME + " steps up to the right wall and starts to search " +
                "it closely.\n",
                "You hear something from the right wall.\n"}), TP);
            return "You search all over the right wall but " +
                "all you find out is that the wall appears to be " +
                "of another material than other walls. When you " +
               "push the wall it bulges slightly from the preasure.\n";
        default:
            return "";
    }
}
 

int
measure_bedroom(string str)
{
 
    if ((str) && (str == "bedroom"))
    {
        write("Its approximately 6 feet wide.\n");
        return 1;
    }
    return 0;
 
}
 
int
break_wall(string str)
{
    if ((str) && ((str == "wall") || (str == "right wall")))
    {
        write("You press your shoulder to the wall and try to break it " +
            "down. The wall bulges a little, but nothing else. It " +
            "is impossible to tear it down.\n");
 
        say(({METNAME + " tries to break down the right wall.\n",
            TART_NONMETNAME + " tries to break down the right wall.\n",
            "You hear a loud thud from the right wall.\n"}), TP);
        return 1;
 
    }
    return 0;
}
