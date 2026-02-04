
#include "/d/Terel/guilds/vamp/guild.h";
inherit "/d/Terel/guilds/vamp/room/vamp_room";
#include <stdproperties.h>

#define PATH "/d/Terel/dark/"

void
create_room()
{
   object door;
   set_short("inside the lair");
   set_long("The bowels of the earth rumble and groan, seeming to "+
       "echo and sigh great rushes of air. There is a very strong "+
       "stench here, the stench of hobgoblins.\n");
   add_exit(PATH + "hob/guard_room", "south", 0);
   add_exit(PATH + "hob/n2", "north", 0);
   reset_room();
}
