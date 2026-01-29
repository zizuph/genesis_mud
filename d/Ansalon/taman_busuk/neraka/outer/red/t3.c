#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

/* Carridin */

inherit OUTER_IN;
inherit RANTEAM;

void
create_neraka_room()
{
    set_short("Inside a canvas tent");
    set_long("You have entered a large tent made of black canvas. The " +
        "canvas withstands the harsh weather of the winter in the " +
        "mountains. In the middle of the tent is a fire pit, and a " +
        "few bedrolls and chests are placed around the tent.\n");
    set_quarter(RED);
    add_item_tent();
    set_team_size(2);
    set_random_table(NT_OUTERMASTER, 1);

    add_exit(NOUTER+"red/r30","out","@@msg@@",0,0);
    reset_room();
}

int
msg()
{
    write("You pull aside the flap, and exit the tent.\n");
    return 0;
}
