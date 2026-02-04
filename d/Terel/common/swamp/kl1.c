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
    return ({PATH + "kg", PATH + "kobold", PATH + "kobold",
             PATH + "kobold", PATH + "kobold", PATH + "kobold"});
}

public void
create_room()
{
   ::create_room();
   
   set_short("Sunken Cave");
   set_long("In the midst of the swamp and geysers is a sunken cave. " +
            "Its mouth opening from the jutting rocks. The cave is " +
            "dark and deep, it seems to be filled with water.\n");
   
   add_item("cave", "It is deep and dark, it looks to be a lair.\n");
   add_item("rocks", "These formations form the cave.\n");
   
   add_exit(PATH + "kl2", "down", &CheckExit("down"));
   add_exit(PATH + "g1",  "southwest", 0);
   add_exit(PATH + "sw5", "northeast", 0);
   
   reset_room();
}
