/* 
   This room is currently not accessible for players anymore. It used to
   be part of an ill-documented and illogical quest from the barbarian 
   chieftain in Que Shu, that has now been changed. The paper the chieftain 
   wants is now located on the Aurak leader in the Dragonarmy camp, which 
   makes a lot more sense
       
   Cherek, January 2016                              
*/


#include "../local.h"
inherit "/d/Krynn/std/outside_room";

int nest_searched = 0;

void
reset_krynn_room()
{
  nest_searched = 0;
}


void
create_krynn_room()
{
    set_short("Up in a tree");
    set_long("You are in the high branches of a tree. ");
    add_exit(TDIR+"rooms/plain-20-2-Z", "down", 0, 3, 1);
    add_cmd_item(({"tree","oak","oak tree","down"}),({"climb"}),"@@climb_down@@");

    add_item(({"branches"}),"The ones you stand on are easily able to hold " +
	     "you, but you dare not climb any higher.\n");
    add_item(({"nest","large nest"}),"The nest is empty.\n");
    add_search(({"nest","large nest"}), 8, PAPER, -1);
    add_search(({"large nest", "nest"}), 8, "search_nest", 1);
 
}

string
search_nest()
{
  string find_string = "";

  if(nest_searched)
  {
    find_string = "The nest is empty.\n";
  }
  else
  {
    find_string = "You find a piece of paper in the nest.\n";
    clone_object(TDIR+"obj/paper")->move(TP, 1);
    nest_searched = 1;
  }
  return find_string;
}


string
climb_down()
{
    this_player()->command("down");
    return "";
}
