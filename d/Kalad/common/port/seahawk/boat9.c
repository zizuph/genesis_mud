#include "../default.h"
inherit PORT_ROOM;

void
create_port_room()
{
    set_short("The Stern of the Seahawk");
    set_long("You find yourself at the ship's stern, the rear section "+
      "of the vessel. It seems to be a gathering place for the lack-luster "+
      "sailors that are supposed to keep the Seahawk in tiptop shape. A "+
      "dart board has been drawn on the side of the railing in the west. "+
      "Overhead are the billowing white sails of the ship. The cry of "+
      "seagulls fills the air.\n");
    add_item(({"dart board","board"}),"It has been crudely sketched onto "+
      "the ship's side by some white chalk. A few marking on the side "+
      "seem to indicate how many times a particular person won.\n");
    add_item(({"markings","marking"}),"Unfortunately, a recent rainshower "+
      "has caused parts of the chalk writing to run and fade, making it "+
      "completely unreadable.\n");
    add_item(({"railing"}),"A small, five foot high barrier that prevents "+
      "the foolish and unwary from falling off the ship and possible "+
      "drowning.\n");
    add_item(({"billowing white sails","billowing sails","white sails","sails","sail"}),
      "Great canvases of cloth that were once used to power the Seahawk "+
      "on its many journeys. However, now that she is permanently docked "+
      "at the pier, they only serve as a reminder of those old glory days.\n");
    add_item(({"seagulls","seagull"}),"The noisy sea birds are flying "+
      "directly overhead, giving you cause for fear of being hit by an "+
      "unwanted bird dropping.\n");

    add_prop(ROOM_NO_TIME_DESC,1);

    add_exit(PORT + "seahawk/boat8", "north");
    add_exit(PORT + "seahawk/boat3", "east");
    add_exit(PORT + "seahawk/boat10", "south");
}

