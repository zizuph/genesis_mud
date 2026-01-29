/* Balcony of the New Vingaard, by Morrigan Dec 96 */

#include "../local.h"

inherit BATTLEMENT;

object herb_rack;

string
batt_desc()
{
    return "This is a balcony overlooking all of Vingaard Keep. " +
           "You are on a raised platform. A railing encircles the platform, " +
           "as a measure to protect people from falling off. Stairs " +
           "are carved down and north, leading back to the hallway. ";
}

public void
create_battlement()
{
    set_short("Platform above Vingaard Keep");
    AI("balcony","The balcony rises above the level of the main guild hall " +
        "of Vingaard Keep, reaching the height of the battlements.\n");
    AI(({"raised platform","platform"}),"This platform is flat, and " +
        "juts out above Vingaard Keep. The area of the platform is quite " +
        "large, as if something huge could occasionally be found here.\n");
    AI("railing","Made of iron, the metal railing encircles the platform, " +
        "preventing people from accidentally slipping or falling off the " +
        "platform.\n");
    ACI(({"platform","raised platform","balcony"}),"jump","The railing gets " +
        "in your way.\n");
    AI("stairs","The stairs lead through thick curtains into a " +
        "hallway further inside Vingaard Keep.\n");
    AI(({"curtains","thick curtains"}),"They are made of a thick " +
        "red fabric.\n");

    AE(VROOM + "south_hallway", "north", "@@go_north", 0);
}

int
go_north()
{
    write("You pass through the thick red curtains into the hallway.\n");
    return 0;
}

void
reset_vin_room()
{
    if (!herb_rack)
    {
        herb_rack = clone_object(VOBJ + "herb_rack");
        herb_rack->move(TO);
    }

}