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
    return ({PATH + "kobold", PATH + "kobold2", PATH + "kg", 
             PATH + "kobold", PATH + "kobold", PATH + "kobold"});
}

public void
create_room()
{
   ::create_room();
   
   set_short("Lair");
   set_long("This bleak and sunken cavern is filled with moss and " +
            "many kinds of rotting plants. The walls are slick " +
            "with slime and mold. The cavern is rudely carved, " +
            "even unstable. Small niches in the walls look like " +
            "shelves.\n");
   
   add_item(({"niches", "shelves", "nests", "beds"}),
            "They are tiny alcove like niches and hold a mess of " +
            "dried plants, seemingly to serve as nests.\n");
   add_item("slime",
            "It hangs from the walls, colorless, but not odorless!\n");
   add_item("mold", "Foul crops of filthy mold.\n");
   add_item("water", "It is stagnant and coats the floor.\n");
   add_item("plants", "Rotted and putrid.\n");
   
   add_exit(PATH + "kl1", "up", 0);
   add_exit(PATH + "kl3", "north", &CheckExit("north"));
   add_exit(PATH + "kl4", "east", &CheckExit("east"));
   
   reset_room();
}
