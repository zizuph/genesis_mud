/*
 * File:    hall_upper_south
 * Creator: Cirion, 1998.06.14
 * Purpose: Room in the monk's guild hall
 */
#pragma strict_types
#include "defs.h"

inherit ROOMBASE;

void
create_room ()
{
    set_short("southern end of the upper hall");
    set_long("High above is the domed stone ceiling that makes "
        + "the roof of the monastery. Near the top of the "
        + "dome is a narrow stone ledge, on which stand "
        + "many small statues of past monks, evenly spaced "
        + "out between each other. Large iron lamps hanging "
        + "from iron brackets in the wall provide light for "
        + "this part of the hall. Opening onto a small balcony "
        + "to the south is a wooden lattice door.\n");
    add_item(({"lamp","lamps","iron lamps","wrought iron lamps"}),
        "These lamps are made of wrought iron. They resemble "
        + "fiery orbs clasped in a dragon's claw.\n");
    add_item(({"light","sunlight"}),
        "The sunlight is warm, it seems to cling to the "
        + "walls with a tenacious hold.\n");
    add_item(({"ceiling","roof"}),
        "The ceiling here is the northern half of a great, "
        + "shallow dome that extends to the southern end of "
        + "the hall. The dome is smooth, made from some "
        + "white stone, and unadorned. It is beautiful in "
        + "its simplicity.\n"
        + VBFC_SAY("stares up at the dome above.\n"));
    add_item(({"shelf","ledge"}),
        "Ringing the base of the dome high above, and "
        + "continuing to the south, is a very thin ledge of "
        + "stone, supported by short, thick beams of wood "
        + "that angle out from the walls. Sitting atop the "
        + "ledge are many small wooden statues.\n"
        + VBFC_SAY("looks up at the ledge ringing the dome.\n"));
    add_cmd_item(({"down","floor",""}), ({"kneel"}),
        "You kneel down on the uncomfortable grille.\n");
    add_cmd_item(({"silence","to silence"}), ({"hear","listen"}),
        "Silence makes no noise.\n"
        + VBFC_SAY("tries futily to hear something.\n"));
    add_cmd_item(({"wall","dome","ledge","up"}), ({"climb","scale"}),
        "There is no way you could climb the wall, making "
        + "you wonder how they got the statues to the ledge "
        + "in the first place.\n"
        + VBFC_SAY("scratches and scrambles against the wall in a vain "
        + "attempt to climb up.\n"));

    add_item(({"statue","statues"}), VBFC_ME("statue_description"));

    WIZINFO("This is the south end of the upper hall in the "
        + "monks guild hall.\n");

    // where, command
    add_exit("balcony_south", "south");
    add_exit("hall_upper_north", "north");
    add_exit("meeting", "east");
    add_exit("temple_balcony", "west");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("south", "You walk back inside.\n");
}


string
statue_description()
{
    return "You peer up and see status of current and old "
        + "monks: " + describe_statues(0) + ".\n";

}


