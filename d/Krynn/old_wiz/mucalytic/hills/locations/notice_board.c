/* A notice-board in the hills. ~mucalytic/hills/locations/notice_board */

inherit "/std/room";

#include "../defs.h"
#include "/sys/stdproperties.h"

void reset_room()
{
    if(!present("notice_board"))
        room_add_object(OBJECTS + "notice_board");
}

void create_room()
{
    set_short("A path at the western edge of the foothills");
    set_long("The hills in this area seem to be diminishing in stature. "+
        "The terrain becomes less undulating and the path becomes more "+
        "distinct and less overgrown by weeds. You notice the smell of "+
        "salt in the air and guess that you are nearing the sea. The "+
        "path continues into the hills to the east and changes to solid "+
        "brick further westwards.\n");

    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_LIGHT, 50 + random(50));

    add_exit(LOCATIONS + "path24", "east", 0, 2);
//  add_exit(LOCATIONS + "sphere_of_light", "west", 0, 3);

    add_item("terrain", "The terrain here is quite grassy. To your east you "+
        "can see that it becomes more hilly.\n");

    add_item("path", "The path is made of a scattering of gravelly rock and "+
        "weeds. It runs quite straight in an east to west direction. Further "+
        "westwards, the road turns from gravel to brick.\n");

    add_item("hills", "The foot-hills here do not roll unremittantly and "+
        "ceaselessly as they do not far to your east, but seem to be no "+
        "more than soft undulations in the ground around you.\n");

    add_item("weeds", "The weeds are of many different colours and many "+
        "different shapes. Some are ugly and some have beautiful flowers, "+
        "but all of them grow in the most inconvenient places.\n");

    reset_room();
}
