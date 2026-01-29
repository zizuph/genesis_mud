#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("Small back room in the ship");
    set_long("You've entered a small room that contains a wooden desk "+
      "that is layered with a variety of maps. The hardwood walls are bare "+
      "save for the southern wall, which contains a rough sketch of an "+
      "island. A thick layer of dust blankets everything.\n");
    add_item(({"wooden desk","desk"}),"A rickety oak desk that looks "+
      "as if a colony of termites attacked it, leaving it in a horrible "+
      "state. Lying on its top are several maps.\n");
    add_item(({"maps","map"}),"Due to extreme age and an overly moist "+
      "environment, the writing and markings on the maps have deteriorated "+
      "so far that nothing can be made of them.\n");
    add_item(({"hardwood walls","walls"}),"Which wall? The southern one?\n");
    add_item(({"hardwood wall","wall","southern wall"}),"The southern "+
      "side of the room has a roughly sketched map on it.\n");
    add_item(({"sketch","roughly sketched map"}),"A rough map of a "+
      "single island has been drawn. Judging from the directions aside the "+
      "sketch, you believe it lies somewhere southwest of the city of "+
      "Kabal. Beside the sketch of the island is one word, written "+
      "in bright red: Death.\n");
    add_item(({"thick layer of dust","thick layer","layer","dust"}),
      "The dust of years of disuse covers everything, making you choke "+
      "whenever you handle anything within the room.\n");

    add_prop(ROOM_I_INSIDE,1);

    add_exit(PORT + "seahawk/fl2", "north");
}

