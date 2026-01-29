inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Calia/abbrev.h"
 
void create_room() {
    set_short("Zima's foyer");
    set_long(
      "You are standing in the foyer of Zima's chambers, a " +
      "triangular room pointing south, the walls and ceiling " +
      "fashioned of black marble.  " +
      "A mysterious letter, crafted of ivory, adorns the floor of " +
      "this room.  " +
      "There is a silver portal here, through which you can go to " +
      "several locations, while an arched doorway leads south through " +
      "the corner to the central chamber.\n");
   add_item("letter",
      "Detailed into the dark marble floor with white ivory, this " +
       "mysterious symbol is the greek letter Theta.\n");
   add_item("portal",
      "A lightly glowing arched portal on the north wall, you may go " +
      "to many places by choosing one of the exits.\n");
   add_cmd_item("portal","enter","@@msg");
   add_item("doorway",
      "It leads through the southern corner into the central chamber.\n");
 
 
    add_exit("/d/Calia/zima/workroom","south",0);
   add_exit("/d/Calia/zima/argos/dephtemp/rooms/foyer","deph",0);
    add_exit("/d/Calia/zima/argos/metro/rooms/boardrm","argosbd",0);
    add_exit("/d/Calia/zima/argos/nwterr/rooms/r1","argosrd",0);
    add_exit("/d/Calia/zima/mclub/rooms/start","shrine",0);
    add_exit("/d/Genesis/start/human/town/tower", "tower",0);
}
 
int msg() {
   write("To use the portal, select one of the exits!\n");
    return 1;
}
