#include "/d/Terel/guilds/vamp/guild.h";
inherit "/d/Terel/guilds/vamp/room/vamp_room";
#include <stdproperties.h>

#define PATH "/d/Terel/dark/"

void
create_room()
{
   set_short("the base of a dark stairwell");
   set_long("Darkness and stench. Stench and darkness. Stairs "+
       "winding upward through the dark bowls of the earth.\n");
   add_exit(PATH + "hob/n1", "south", 0);
   add_exit(PATH + "hob/n3", "up", 0);
   reset_room();
}
