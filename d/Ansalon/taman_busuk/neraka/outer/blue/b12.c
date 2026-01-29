/* Ashar, 7 May 97 */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit OUTER_OUT;

void
create_neraka_room()
{
	set_short("market square in Blue Quarter");
    set_extra_long("You are in the middle of the market square. The square " +
        "continues west and south of here. Shops line the square, and other " +
        "merchants wander around, hawking their wares. A small alley darts " +
        "away to the northwest between two ramshackle buildings. A sign " +
        "hangs above a building to the northeast, from which you hear " +
        "the clinking of cups and the noise of drunken conversation.");
    set_quarter(BLUE);

    add_item_sidewalks();
    add_item_buildings();
    add_item_market("square");
    add_item(({"alley","small alley"}),"The alley leads northwest.\n");
    add_item("sign","The sign consists of a crudely drawn picture of " +
        "a man in Solamnian armour hanging upside down from a rope " +
        "tied to his feet. Below the picture are the words: 'The " +
        "Hanged Knight'.\n");

    add_exit(NOUTER+"blue/b9","northwest","@@alleymsg");
    //add_exit(NOUTER+"blue/xxx","north");
    add_exit(NOUTER+"blue/pub1","northeast");
    add_exit(NOUTER+"blue/b14","east");
    add_exit(NOUTER+"blue/bank","southeast","@@bankmsg");
    add_exit(NOUTER+"blue/b13","south");
    add_exit(NOUTER+"blue/b8","west");
}

int
alleymsg()
{
	write("You head down the alley and emerge onto a dirt road.\n");
    return 0;
}

int
bankmsg()
{
	write("You step into a small, dark building.\n");
    return 0;
}

