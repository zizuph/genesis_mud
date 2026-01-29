/* Ashlar, 24 May 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit OUTER_IN;
inherit RANTEAM;

void
create_neraka_room()
{
    set_short("Inside a black canvas tent");
    set_long("You have entered a large tent made of black canvas. The " +
        "canvas withstands the harsh weather of the winter in the " +
        "mountains. In the middle of the tent is a fire pit, and a " +
        "few bedrolls and chests are placed around the tent.\n");
    set_quarter(BLACK);
   
    add_item_tent();

    add_exit(NOUTER+"black/b21","out","@@msg@@");

    set_random_table(NT_OUTERMASTER, 1);
    set_team_size(3);
    
    reset_room();
}

int
msg()
{
	write("You pull aside the flap, and exit the tent.\n");
    return 0;
}

