#include "/d/Terel/guilds/vamp/guild.h";
inherit "/d/Terel/guilds/vamp/room/vamp_room";
#include <stdproperties.h>

#define PATH "/d/Terel/dark/"

void
create_room()
{
    set_short("dark stairwell");
    set_long("These stairs seem to wind endlessly in both "+
        "directions. There is a strong smell here, strong "+
        "enough to make your eyes water.\n");
    add_exit(PATH + "hob/n4", "down", 0);
    add_exit(PATH + "hob/n6", "up", 0);
    reset_room();
}
