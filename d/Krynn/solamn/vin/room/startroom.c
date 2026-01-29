
/* New Vingaard Keep startroom */
/* Morrigan and Teth Jan 97 */

#include "../knight/guild.h"
#include <ss_types.h>
#include <files.h>
#include <macros.h>

inherit IN_BASE;

object statue;

void
reset_vin_room()
{
}

void
create_vin_room()
{
    set_short("Upper Level of the Keep");
    set_long("This is the central room of the upper level of Vingaard " +
        "Keep. A silver sign is posted near the middle of the room. " +
        "A stairway lead upwards and downwards, while halls veer off to the " +
        "west, north, east and south. A statue sits in one corner. A lamp " +
        "hangs from the ceiling, in another corner.\n");
    AI(({"sign","silver sign"}),"The sign is silver, crafted by an expert.\n");
    ACI(({"sign","silver sign"}),"read","The sign reads:\n    Knights of " +
        "Solamnia and Squires may <start here>.\n\n");
    AI("stairway","The stairway spirals up to a small room, and down " +
        "to the Great Hall of Vingaard Keep.\n");
    AI("halls","The halls lead to areas of import to a Knight of Solamnia.\n");
    AI("east hall","The east hall seems to end quickly.\n");
    AI("south hall","The south hall leads to a balcony.\n");
    AI("west hall","The west hall leads to the chapel.\n");
    AI("north hall","The north hall enters another open area.\n");
    AI("lamp","The lamp lights the room with a soft glow.\n");
    ACI("lamp",({"get","reach"}),"The lamp is out of your reach.\n");
    AI("ceiling","The ceiling is made of typical stone.\n");
    AI("floor","The floor has many scuff marks from the boots of Knights.\n");
    AI("stone","It is hard and volcanic.\n");
    AI(({"walls","wall"}),"The walls are made of the typical stone found " +
        "throughout Vingaard Keep.\n");
    AI("hall","Which one?\n");


    add_prop(ROOM_I_LIGHT,2);
    ACI("here", "start", "@@do_start");

    AE(VROOM + "west_hallway", "west", 0);
    AE(VROOM + "north_hallway", "north", 0);
    AE(VROOM + "east_hallway", "east", 0);
    AE(VROOM + "south_hallway", "south", 0);
    AE(VROOM + "common", "up", 0);
    AE(VROOM + "great_hall", "down", 0);

    statue = clone_object(VOBJ + "vinas_statue.c");
    statue->move(TO);

    reset_vin_room();
}

int
do_start()
{
    NF("Start where?\n");
    if (!MEMBER(TP))
        return 0;
    TP->set_default_start_location(START_ROOM);
    write("You will now always start here in Vingaard Keep.\n");
    return 1;
}
