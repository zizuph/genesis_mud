/* Ashlar */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <language.h>

inherit OUTER_IN;
inherit RANTEAM;

void
create_neraka_room()
{
    set_short("inside a canvas tent");
    set_long("You have entered a large tent made of black canvas. The " +
        "canvas withstands the harsh weather of the winter in the " +
        "mountains. In the middle of the tent is a fire pit, and a " +
        "few bedrolls and chests are placed around the tent.\n");
    set_quarter(BLUE);
    add_item_tent();

    add_exit(NOUTER+"blue/b17","out","@@msg@@");

    set_random_table(NT_OUTERMASTER, 1);
    set_team_size(2+random(2));
    
    reset_room();
}

int
msg()
{
	write("You pull aside the flap, and exit the tent.\n");
    return 0;
}

mixed
neraka_dragon_enter(object dragon, object from)
{
    tell_room(TO,
        "The tent is ripped to shreds as " + LANG_ADDART(dragon->short()) +
        " claws its way in.\n");
    set_short("inside a ripped canvas tent");
    set_long("You are standing inside the ripped shreds of a black " +
        "canvas tent, which desolately hang from half-broken tent poles. " +
        "In the center of the ruined tent is a fire pit, and a few " +
        "bedrolls and chests are scattered in the area.\n");
    return 0;
}
