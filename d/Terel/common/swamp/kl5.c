inherit "/d/Terel/common/swamp/kl";

#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>

#define PATH "/d/Terel/common/swamp/"

#define TP   this_player()
#define TO   this_object()
#define ETP  environment(TP)

int aid;

/*
 * Function name: query_moving_object_list
 * Description:   return list of moving objects to clone at each reset.
 */
public string*
query_moving_object_list()
{
    return ({PATH + "kg", PATH + "kobold",
             PATH + "kobold"});
}

public void
create_room()
{
    ::create_room();
    
    set_short("Lair tunnel");
    set_long("A dank and dismal tunnel, crudely formed. The walls " +
             "are more mud than stone. A small stream of water " +
             "fills the floor.\n");

    add_item(({"water", "stream"}),
             "A small stream of filthy water that runs through the cave.\n");
    add_item("walls", "Crudely carved from mud and stone.\n");
    add_item("mud", "Much of the tunnel is packed mud.\n");

    add_exit(PATH + "kl3", "south", 0);
    add_exit(PATH + "kl7", "northeast", &CheckExit("northeast"));
    add_exit(PATH + "kl9", "northwest", &CheckExit("northwest"));
    
    reset_room();
}
