inherit "/d/Terel/common/swamp/kl";

#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/common/swamp/"

#define TP   this_player()
#define TO   this_object()
#define ETP  environment(TP)

/*
 * Function name: query_moving_object_list
 * Description:   return list of moving objects to clone at each reset.
 */
public string*
query_moving_object_list()
{
    return ({PATH + "kobold", PATH + "kg"});
}

public void
create_room()
{
   ::create_room();
   
    set_short("Lair tunnel");
    set_long("It's a tunnel with a small spring in the middle of " +
             "it. The walls are more of mud than the rest of " +
             "the cave.\n");

    add_item(({"water", "spring"}),
             "A small spring with very filthy water that runs southwest.\n");
    add_item("walls", "Crudely carved from mud and stone.\n");
    add_item("mud", "Much of the tunnel is packed mud.\n");
    
    add_exit(PATH + "kl5", "southwest", &CheckExit("southwest"));
    
    reset_room();
}
