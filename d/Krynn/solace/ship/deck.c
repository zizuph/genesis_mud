inherit "/d/Krynn/std/deck";
#include "local.h"

object boat_loc;
string boat_loc_str;

void
create_deck()
{
    set_short("On the Solace-Newports rowboat");
    set_long(BS("This is a small rowboat, made of resined " +
        "planks. It is used by a Solace villager to provide " +
        "the service of rowing people to and from Newports." +
        " The boat is small and comfortable, but smells of fish.", 70));
    add_cmd_item("fish","smell","Yes, you can smell the oily fish " +
        "scent.\n");
    add_item(({"small rowboat","rowboat"}),"This rowboat is " +
        "simple in design. Resined planks form the frame of " +
        "the boat, and they are obviously of a buoyant wood. " +
        "Oars are present near the middle of the boat.\n");
    add_item(({"planks","resined planks"}),"The planks are made " +
        "of a soft wood, probably Crystalmir pine.\n");
    add_item(({"wood","buoyant wood","soft wood"}),"Closer " +
        "inspection definitely reveals that they are made of pine.\n");
    add_item("oars","The oars are long and slender, yet strong. " +
        "They look well-used.\n");
    add_cmd_item("oars","get","The oars are attached to the frame " +
        "of the boat through metal brackets, making them impossible " +
        "to take.\n");

    set_deck_sound("@@sounds");
}

sounds()
{
    if (random(2))
    return "The rowboat rocks slightly, as the balance is upset.\n";
    return "The human glides the boat effortlessly through a " +
        "narrow passage.\n";
}

public int
query_no_time() { return 1; }

/*
void
set_boat_loc(object bl)
{
     if (objectp(bl) && bl->query_prop(ROOM_I_IS)) {
         boat_loc = bl;
         boat_loc_str = file_name(bl);
     } 
}

object
query_boat_loc()
{
    return boat_loc; 
}
*/

/* Needed for the map to know we are in a boat in a room somewhere else */

object
query_room_env()
{
      return environment(query_ship());
//    return boat_loc;
}
