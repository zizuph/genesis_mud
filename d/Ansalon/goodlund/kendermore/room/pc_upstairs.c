#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <macros.h>

inherit KENDERMORE_IN;
inherit STREET_DESC;

object sbottle;

void
reset_kendermore_room()
{
    if (!sbottle)
    {
        sbottle = clone_object(KOBJ + "sbottle");
        sbottle->move(TO);
    }
}

void
create_kendermore_room()
{
    set_short("A comfortable bedroom");
    set_long("This looks like the living quarters of the person who " +
        "works in the office downstairs. It is lightly decorated with " + 
        "a bed, a dresser and an end table. A heavy rug has been placed " + 
        "on the floor near the bed. The room is lit by a small window " + 
        "during the day, and a greasy lantern at night. A set of stairs " + 
        "lead back down to the office.\n");
    add_item(({"wall", "floor", "ceiling"}), "It is made of wood.\n");
    add_item("walls", "They are made of unadorned wood.\n");
    add_item("lantern", "Someone must refill it regularly, since it's " + 
        "still burning.\n");
    add_item("bed", "It looks very comfortable.\n");
    add_item("dresser", "It is a beautiful piece of wooden furniture.\n");
    add_item(({"table", "end table"}), "There is nothing on it.\n");
    add_item(({"rug", "heavy rug"}), "It is very soft and colourful.\n");
    add_item("window", "You can see the streets of Kendermore from here.\n");
    add_item(({"streets", "street"}), "@@street_descr@@\n");
    add_item("stairs", "They look creaky, but safe.\n");
 
    add_exit(KROOM + "pc_boffice", "down", "@@down_message");

    reset_kendermore_room();
    return;
}

int
down_message()
{
    write("You head down the stairs with a loud CREEEEAAAAKKKK.\n");
    return 0;
}
