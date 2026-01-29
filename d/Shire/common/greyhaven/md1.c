inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include "defs.h"
#include "/sys/macros.h"

void add_stuff();

create_room() 
{
    set_short("The Great Eastroad");
/*    set_long("@@long_desc"); */
    set_long("You are standing outside an inn in the village Michel Delving. "+
	     "Northeast seems to lead to the fields surrounding the village, "+
	     "and south leads back towards the Eastroad.\n");
    add_item(({ "track", "tracks" }), "The tracks are mostly made by wagons "
	     + "and mules. There are also a few that indicate horses.\n");

    add_item(({ "door", "doors" }), "There is nothing unusual abou these "
	     + "wodden doors except for their round shape.\n");

    add_exit(MICH_DIR + "field","northeast",0,1);
    add_exit(GHAVEN_DIR + "gh1", "south", 0,1);
    add_exit(GHAVEN_DIR + "inn", "enter", "@@size");
    
    add_stuff();
}

void
add_stuff()
{
    object wife;

    if(!present("_amanda_"))
    {
	wife = clone_object(MICH_DIR + "npc/wife");
	wife->move(TO);
    }
}
