#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
#include "/d/Gondor/defs.h"

public void
create_morgul_room()
{
    set_extraline("This is a dark and narrow street somewhere close " +
    "to the Great Tower. To the west you can see a run-down shop, to " +
    "the east there seems to be a sleazy dive. The street continues " +
    "south to the city wall, while to the north it runs into the " +
    "Morgul Road.");
    set_road(3);
    set_side("south");

    add_tower();
  add_item(({"wall","city wall"}), BSN(
    "All you can see from here is that some way to the south this " +
    "street seems to end at the foot of the southern city wall. "));
  add_item(({"morgul road"}), BSN(
    "To the north, you can see the broad Morgul Road running from " +
    "the Great Tower eastward to the Mordor Gate. "));
  add_item(({"shop"}), BSN(
    "The shop west of the street clearly has seen better days. " +
    "The building is half in ruins, only the ground floor is still " +
    "standing and has been roofed over using wooden planks. " +
    "Two windows and a door lead out in the street from the " +
    "building. Close to the door, someone has written " +
    "'Bolzog Shoppe' with red paint onto the wall. "));
  add_item(({"window","windows"}), BSN(
    "Do you mean the shop windows or the pub windows? "));
  add_item(({"shop window","shop windows"}), BSN(
    "Of the two windows going out on the street, one has been " +
    "walled up, the other has been secured with an iron grating. "));
  add_item(({"door","doors"}), BSN(
    "Which door do you mean, the shop door or the pub door?"));
  add_item(({"shop door"}), BSN(
    "The door is just a dark opening leading into the shop. " +
    "Close to it, someone has written 'Bolzog Shoppe' in red paint " +
    "on to the wall. "));
  add_item(({"dive","pub","sleazy dive"}), BSN(
    "Above the entrance into the sleazy dive west of the door, " +
    "you can read 'Dead Tark Pub' written with large crude letters " +
    "in black paint. The entrance leads down into the basement of the " +
    "building, and the smell of cheap booze and vomit comes out of it. "));
  add_item(({"pub windows","pub window"}), BSN(
    "There are no windows overlooking this street in the pub. " +
    "If there once were some, they must have been walled up long ago, " +
    "and the new masonry has been overpainted so you cannot see where the windows might have been. "));
  add_item(({"pub door","dive door","entrance","pub entrance","steps"}), BSN(
    "The entrance into the building east of the street leads a few steps " +
    "down into the basement of that building. Over the entrance, you " +
    "can read 'Dead Tark Pub' written in large crude letters. The smell of cheap booze " +
    "and vomit comes out of the entrance. "));
  add_item(({"letters"}), BSN(
    "Which letters? The red letters next to the shop door or the black letters over " +
    "the entrance into the pub?"));
  add_item(({"red letters"}), "You read: \n\n Bolzog Shoppe \n\n");
  add_item(({"black letters","crude letters","large letters"}), 
    "You read: \n\n Dead Tark Pub \n Ahyando, proprietor \n\n");
  add_exit(MORGUL_DIR + "city/mmr4","north","@@check_exit",1);
  add_exit(MORGUL_DIR + "city/rooms/new_pub","east","@@check_exit",1);
  add_exit(MORGUL_DIR + "city/darkstr1","south","@@check_exit",1);
  add_exit(MORGUL_DIR + "city/rooms/shop","west","@@block_npc@@",1);
}
