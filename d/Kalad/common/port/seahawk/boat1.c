#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
     /*always do this*/
    set_short("The front entrance of the Seahawk");
    set_long("This is the front entrance of the Seahawk, the first ship "+
      "of Kabal. By its appearance this ship seems to have been here for "+
      "quite some time. Muted noise sounds from somewhere below you. The "+
      "wooden deck here is marred by scratches that look like they were "+
      "the result of numerous battles.\n");
    add_item(({"wooden deck","deck"}),"The aging wooden planks of the "+
      "ships top deck still look capable of holding a great deal of weight.\n");
    add_item(({"aging wooden planks","aging planks","wooden planks","planks","plank"}),
      "Long wooden boards that serves as the Seahawk's upper deck.\n");
    add_item(({"scratches","scratch"}),"The scars on the deck look "+
      "consistent with damage taken from cannon fire and burning pitch.\n");

    add_prop(ROOM_NO_TIME_DESC,1);

    add_exit(PORT + "seahawk/boat8", "west");
    add_exit(PORT + "s74", "north");
    add_exit(PORT + "seahawk/boat2", "east");
    add_exit(PORT + "seahawk/boat3", "south");
}

