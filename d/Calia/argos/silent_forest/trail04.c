/*
 *   trail04.c
 *
 * Baldacin@Genesis, Nov 2003
 */
#include "ldefs.h"
inherit FORESTSTD;
inherit "/d/Calia/std/room_tell_room";

void
create_room()
{
    set_short("On a small over-grown trail");
    set_long("You are traveling along a small over-grown "+
      "trail where dense pine trees grows close together, "+
      "making it a hard journey. An old rickety hut is standing "+
      "next to the path here and the trail stretches "+
      "north further into the wilderness and east "+
      "towards a bridge crossing a small stream.\n");
    
    add_item(({"stream","freshwater stream"}), "A little "+
      "bit further downstream the freshwater stream takes "+
      "a sharp turn, changing its flow to the east.\n");
    add_item(({"bridge", "wooden bridge"}), "It seems to "+
      "be made of some kind of hardwood tree. Small, yet "+
      "strong and sturdy.\n");
    add_item("trail", "The trail continues in a north-"+
      "east direction.\n");
    add_item(({"trees","tree","pine trees"}),"The dense "+
      "pine trees growing here makes it hard traveling. "+
      "Makes you wonder what brought you here in the first place.\n"); 
    add_item(({"hut","old hut", "old rickety hut"}),"An old "+
      "rickety hut, it looks abandoned but perhaps you should "+
      "enter it and have a look.\n");

    set_tell_time(250);
    add_tell("A small animal scurries quickly from "+
          "one bush to another.\n");
    add_tell("You hear a loud, shrieking sound coming "+
          "from one of the trees.\n");
    add_tell("One of the old trees goes 'Creak, creeek' "+
          "as the wind forces it to sway slowly.\n");
    add_tell("Suddenly everything is very quiet.\n");
     
    add_cmd_item(({"hut","old hut", "old rickety hut"}),
        "enter","@@enter_hut");
        
    add_exit(SFDIR + "trail05","north");
    add_exit(SFDIR + "trail03","east");
    
}

int
enter_hut()
{     
    write("You enter the old rickety hut.\n");
    TP->move_living("entering the old rickety hut", SFDIR + "hut", 0, 0);
    return 1;
}