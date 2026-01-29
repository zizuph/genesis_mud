/* Marisol's Workroom. Upgrade by Marisol (07/10/1998)*/

#pragma save_binary

inherit "/std/room";
#include "/sys/macros.h";
#include "/d/Emerald/sys/macros.h"
#include "/sys/stdproperties.h"

void
create_room()
{
    set_short("Marisol's Workroom");
    set_long("This is the Fountain's Retreat, where Marisol "+
        "meditates about all her works. The sun shines through "+
        "the emerald leaves of oak and maple, and water leaps "+
        "and falls inside the singing fountain. There is a tree "+
        "near the fountain, a full-grown willow. It roots has slowly "+
        "cracked the marble tiles around the fountain. Moss have grown "+
        "inside the cracks, extending tendrils of green verdure "+
        "around the basin.\n");


    add_item("fountain",
        "The fountain is a marvelous sight, full of grace and light. "+
        "The white marble reflects the sunlight so that it "+
        "seems to glow with its own radiance.\n");


    add_item("basin",
        "A white porcelain basin. It is carved into the ground. "+
        "It is full of cool water that comes from another small "+
        "basin. It is spouting from a tower that collects the water "+
        "shooting out from the top of the fountain.\n");


add_prop(OBJ_I_CONTAIN_WATER,1);


    add_item(({"tree","willow","leaves","leaf"}),
        "The branches of the full-grown willow tower above the "+
        "fountain. A cool breeze freshens the air under the tree, "+
        "singing with the leaves. Sometimes a leaf falls into the "+
        "fountain and floats in the clear water.\n");


    add_exit("/d/Genesis/wiz/virtual","virtual","@@check_exit");

    

}
int

check_exit()
{
    if(TP->query_wiz_level())
        return 0;
    write("Only wizards can use this exit.\n");
    return 1;
}

int
drink_it(string str)
{
    if ((str == "water") || (str == "water from basin"))
    {

    if(!this_player()->drink_soft(500))
    {
        write("You are too full to drink any more water.\n");
        return 1;
    }

        write("You take a drink of the earthy-tasting water. "+
       "You feel refreshed.\n");

        say(QCTNAME(TP) + "drink some water from the basin.\n");
       return 1;
    }

        notify_fail("Drink what?\n");
        return 0;
}

void
init()
{

    ::init();
    add_action(drink_it, "drink");

}

