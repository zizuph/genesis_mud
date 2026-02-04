
#include "/d/Terel/guilds/vamp/guild.h";
inherit "/d/Terel/guilds/vamp/room/vamp_room";
#include <stdproperties.h>

#define PATH "/d/Terel/dark/"

void
create_room()
{
   set_short("dark stairwell");
   set_long("An eye-watering stench weighs heavily on the "+
       "air here.  Stairs seem to spiral up and down into "+
       "infinity.\n");
   add_exit(PATH + "hob/n2", "down", 0);
   add_exit(PATH + "hob/n4", "up", 0);
   reset_room();
}
