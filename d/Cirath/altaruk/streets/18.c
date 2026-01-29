#include "../defs.h"

inherit ALT_STD + "room.c";

void
create_street()
{

    short_name("a busy street in Altaruk.");
    street_name("Merchant");
    extra_line("Most of the east side of the street is warehouses.");
    last_line("Someone has painted something on the west wall.");
    
    add_item(({"warehouses", "warehouse"}), "The buildings on the" +
        " east side of the street are warehouses. they appear" +
        " securely locked.\n");
    
    add_item("wall", "What wall?\n");
    add_item("west wall", "The wall has a crude painting of a red" +
        " sun with a hand covering the lower parts of it. Beneath" +
        " someone has written.\n" +
        " DEATH TO ALL DEFILERS! DEATH TO THE DRAGON KINGS!\n");

    add_exit("17.c", "north", 0,1,0);
    add_exit("20.c", "south", 0,1,0);
}
