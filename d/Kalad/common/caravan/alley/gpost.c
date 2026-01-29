#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_hear_bell(1);

    set_short("Inside the guard post");
    set_long("This is the small and relatively cramped room where the "+
      "guards usually stay. Windows on each of the four walls of this small "+
      "structure give you an almost unrestricted field of view. A table, some chairs "+
      "and a cabinet lie about the room.\n");

    add_item(({ "windows", "window" }), "Each of the windows is grimy, but is "+
      "still clean enough for you to see everything in the clearing in "+
      "front of the storage sheds.\n");

    add_item(({ "clearing" }), "Its what lies just outside of this guard post.\n");

    add_item(({ "storage sheds", "storage shed", "sheds", "shed" }), "The rows "+
      "of storage units where cargo for the Trading Company is placed.\n");

    add_item(({ "walls", "wall" }), "They are built out of pine wood.\n");

    add_item(({ "table" }), "A small round table built out of varnished "+
      "pine wood.\n");

    add_item(({ "chairs", "chair" }), "More like stools, they don't look "+
      "at all comfortable, leading you to believe that the guards stand "+
      "more often then sit.\n");

    add_item(({ "cabinet" }), "A large wooden cabinet, where the day to day "+
      "documents involved in storing goods in the sheds is kept.\n");

    add_exit(CVAN + "alley/yard1", "out");
}
