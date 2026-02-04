#include "/d/Terel/guilds/vamp/guild.h";
inherit "/d/Terel/guilds/vamp/room/vamp_room";
#include <stdproperties.h>

#define PATH "/d/Terel/dark/"

void
create_room()
{
    set_short("dark stairwell");
    set_long("Stairs spiralling through darkness and stone. A stench "+
        "seems to waft upward on a current of warm air.\n");
    add_exit(PATH + "hob/n3", "down", 0);
    add_exit(PATH + "hob/n5", "up", 0);
    reset_room();
}
