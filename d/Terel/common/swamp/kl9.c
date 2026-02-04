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
    return ({PATH + "kobold2", PATH + "kobold2", 
             PATH + "kobold2", PATH + "kobold2"});
}

public void
create_room()
{
   ::create_room();
   
   set_short("Lair tunnel");
   set_long("This long tunnel is filled with a stream of filthy " +
            "water, in which are layers of red algae. A rank smell " +
            "emanates from the entire tunnel.\n");

   add_item("slime",
            "It hangs from the walls, colorless, but not odorless!\n");
   add_item("mold",  "Foul crops of filthy mold.\n");
   add_item("water", "It is stagnant and coats the floor.\n");
   add_item("plants", "Rotted and putrid.\n");
   
   add_exit(PATH + "kl5", "southeast", 0);
   
   reset_room();
}
