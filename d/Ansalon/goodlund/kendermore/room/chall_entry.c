/* Entry way to city hall (City Hall not open), Gwyneth, June 1999 */

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit KENDERMORE_IN;
inherit STREET_DESC;

void
reset_kendermore_room()
{
    return;
}

void
create_kendermore_room()
{
    set_short("The entry way of city hall");
    set_long("This is the entry way of City Hall. Some chairs line the " + 
        "wall for those who need to wait for an audience with the mayor " + 
        "or other official. A cork board has been nailed to the wall " + 
        "where citizens and visitors alike can post messages. The mayor " + 
        "won't tolerate foul language and abuse, so think before you post. " + 
        "Two kender guards stand by the door that leads further into the " + 
        "building, and a small common room lies to the north.\n");
    add_item(({"hall", "city hall", "entryway"}), "You stand in the " + 
        "entryway of city hall. This is where the officials of Kendermore " + 
        "meet and discuss matters, at least when they can be found. The " + 
        "mayor also holds an audience on the second floor at times.\n");
    add_item("door", "It leads to the east, further into the building.\n");
    add_item("street", "@@street_descr@@\n");
    add_item(({"chair", "chairs"}), "They look rather comfortable, and " + 
        "bolted down to the floor. That must explain why they are still " + 
        "here.\n");
    add_item("walls", "They are made of unadorned wood.\n");
 
    add_exit(KROOM + "street34", "west", 0);
    add_exit(KROOM + "null", "east", "@@block_message");
    add_invis_exit("/d/Genesis/room/common", "north", 0);

    clone_object(KOBJ + "normal_board")->move(TO);    

    reset_kendermore_room();
}

int
block_message()
{
    write("The two kender guards block your way, since you don't belong " + 
        "in that part of the building.\n");
    return 1;
}

