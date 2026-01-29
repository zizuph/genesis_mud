/* Created 29/9/98 by Bishop, of Calia. This is the "post office"
in the gnomish village of Rust.  */

#pragma save_binary

inherit "/std/room";

#include <defs.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#define PIGEON "/d/Genesis/obj/pigeon"

int
hire(string str)
{
    object pigeon;

    if (str != "pigeon")
    {
        notify_fail("Hire pigeon maybe?\n");
        return 0;
    }

    if (MONEY_ADD(TP, -20))
    {
        pigeon = clone_object(PIGEON);
        pigeon->move(TP);
        write("One of the gnomes sneaks up behind an unsuspecting" +
            " pigeon, and suddenly pounces it! After a brief" +
            " struggle, he manages to get the pigeon under" +
            " control, and gives it to you. You pay 20 coppers.\n");
    }

    else
    {
        write("You don't have enough money. Hiring a pigeon costs" +
            " 20 copper.\n");
    }

    return 1;
}

void
init()
{
    ::init();
    add_action(hire, "hire");
    add_action(hire, "buy");
}


create_room()
{
    set_short("Post office in gnome village");

    set_long("You have entered the post office of this small settlement." +
        " Pigeons are flying all over this hut, to the dismay of the gnomes" +
        " who work here. From time to time one of the gnomes manage to grab a" +
        " pigeon, attach a message to its leg, and throw it out of the" +
        " hole in the roof. You could probably hire a pigeon here.\n");

    add_item("pigeons","These birds, varying in colour from white to black," +
        " are used as maintain mail connection in these parts.\n");
    add_item("gnomes", "The gnomes who work here look stressed, and are" +
        " probably not used to handling pigeons.\n");
    add_item(({"hole","hole in the roof"}),"It's about three feet in" +
        " diameter. Looks like there is a board that one can move to cover" +
        " the hole on a rainy day.\n");
    add_item("board","You can only see the edge of it. Seems to be made out" +
        " of wooden planks, nailed together.\n");

    add_prop(ROOM_I_HIDE, 70);
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(VILLAGE+"village_path5","northwest",0,1);

}

