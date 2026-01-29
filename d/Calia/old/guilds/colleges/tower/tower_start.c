/* A room on the second floor of the Tower of Elemental Magic 
   Created 16.1.2000, Bishop
*/

inherit "/d/Calia/guilds/colleges/tower/tower_base.c";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h";


create_room()
{
    set_short("Tower Starting Chamber");

    set_long("You stand in a room where students of the elements" +
        " who are done with sleep, study and meditation gather to" + 
        " venture out into the world. It is possible to <start" +
        " here>. " + basic_desc + " Through an archway to the south"+
        " you see a small room that is used for storage, and to" +
        " your east a corridor stretches.\n");
        
    add_item("archway", "It's an open archway, with no closing mechanism.\n");

    add_exit(TOWER + "tower_corr_2_5.c", "east", 0, 1);
    add_exit(TOWER + "tower_equipment.c", "south", 0, 1);

    make_college_room();
}