#include "/d/Terel/guilds/vamp/guild.h";
inherit "/d/Terel/guilds/vamp/room/vamp_room";
#include <stdproperties.h>

#define PATH "/d/Terel/dark/"

void
create_room()
{
   set_short("dark stairwell");
   set_long("A set of stairs seeming to wind into eternity, "+
       "up and down. There is a stench in the air, faint, "+
       "but discernable.\n");
   add_exit(PATH + "hob/n5", "down", 0);
   add_exit(PATH + "hob/n7", "up", 0);
   reset_room();
}
