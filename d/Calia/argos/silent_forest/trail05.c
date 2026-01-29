/*
 *   trail05.c
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
      "making it a hard journey. The trail continues south "+
      "further into the wilderness and to the north it narrows "+
      "into an even smaller walkpath.\n");
    
    add_item("trail", "The trail continues south, "+
      "and north it narrows into an even smaller walkpath.\n");
    add_item(({"trees","tree","pine trees"}),"The dense "+
      "pine trees growing here makes it hard traveling. "+
      "Makes you wonder what brought you here in the first place.\n"); 

    set_tell_time(250);
    add_tell("A small animal scurries quickly from "+
          "one bush to another.\n");
    add_tell("You hear a loud, shrieking sound coming "+
          "from one of the trees.\n");
    add_tell("One of the old trees goes 'Creak, creeek' "+
          "as the wind forces it to sway slowly.\n");
    add_tell("Suddenly everything is very quiet.\n");
     
    add_exit(SFDIR + "forest03x06.c","north", 0, 0,
        EXITNOTOBVIOUS);
    add_exit(SFDIR + "forest04x06.c","northeast", 0, 0,
        EXITNOTOBVIOUS);
    add_exit(SFDIR + "trail04","south");
    
}