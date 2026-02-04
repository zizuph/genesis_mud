/*
 *  Dragon Claw Pub, Kitchen
 *  Coded by Shinto 110798
 *
 */

#include "/d/Terel/include/Terel.h"

inherit STDROOM;


int drink();

/*
 * Function name: query_object_list
 * Description:   return list of object to clone at each reset.
 */
public string*
query_object_list()
{
    return ({CALATHIN_DIR +"npc/std_citizen"});
}

/*
 * Function name: create_room
 * Description:   Default constructor
 */
public void
create_room()
{
    ::create_room();
    set_short("Kitchen of the Dragon Claw Pub");
    set_long("You are now in the Dragon Claw Pub. Shelves line the "+
        "west and east walls. On the north wall is a fireplace for "+
        "cooking. The south wall has some shelves and a well against "+
        "it. The only way out of the kitchen is through the door on the "+
        "east wall.\n");

    add_item(({"wall","walls"}), "The walls are made of stone "+
             "to keep out the harsh wind and snow.\n");
    add_item(({"shelf", "shelves"}),
             "The shelves contain all kinds of ingredients for food, as "+
             "well as plates, glasses, and utensils.\n");
    add_item("fireplace", "The fire place is built into the stone wall, "+
              "it's used to cook the meals provided here at the pub.\n");
    add_item("well","A stone well that provides water for the patrons "+
              "to drink, also used for cooking and cleaning.\n");
    add_cmd_item(({"well","water"}), ({"drink"}), "@@drink");
    INSIDE;
    add_exit(CALATHIN_DIR +"pubs/drag_pub", "east",0);

    reset_room ();

}

int
drink()
{
    if (TP->drink_soft(TP->drink_max() / 16,0))
    {
        say(QCTNAME(TP) + " drinks some water from the well.\n");
        write("You drink some ice cold water and feel very refreshed.\n");
         return 1;
    }
    write("Hmm, you are not thirsty at all at the moment.\n");
    return 1;

}
