/*
 * File:    hall_upper_north
 * Creator: Cirion, 1998.06.14
 * Purpose: Room in the monk's guild hall
 */
#pragma strict_types
#include "defs.h"

inherit ROOMBASE;

void
create_room ()
{
    set_short("northern end of the upper hall");
    set_long("The floor of the northern end of this hall "
        + "is made from an iron grille, through which "
        + "the lower great hall can be seen. Sunlight "
        + "floods through the leaded-glass doors that lead "
        + "out to the northern balcony. To the east is a "
        + "dark stone stairwell, and to the west is "
        + "a small room with a desk. The high, domed "
        + "ceiling, which continues to the south, is "
        + "ringed with a narrow stone ledge, atop which "
        + "stand many small statues.\n");
    add_item(({"grille","iron","floor","ground"}),
        "The floor is made from thick iron grille-work, "
        + "allowing a view to the lower great hall below. "
        + "The grille seems very old, but sturdy."
        + living_view("hall_lower_north", " Through the "
        + "grille, you can see ", " down below.", " The great "
        + "hall below is quiet and empty.")
        + "\n");
    add_item(({"east","stair","stairwell"}),
        "The eastern doorway opens into a dark stairwell "
        + "which rises both above and below.\n");
    add_item(({"west","post office"}),
        "The room to the west has a feeling of silence "
        + "eminating from it.\n");
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
    add_item(({"desk","table"}),
        "The desk in the room to the west is small and made "
        + "from pine. Inset into its back are many small "
        + "cubbyholes.\n");
    add_item(({"balcony","north"}),
        "The balcony through the leaded glass doors to the "
        + "north looks over the front entrance to the "
        + "monastery.\n");
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

    // where, command
    add_exit("balcony_north", "north");
    add_exit("hall_upper_south", "south");
    add_exit("post", "west");
    add_exit("stair_upper", "east");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("east", "You walk out of the dark landing "
        + "into the sun filled north end of a large "
        + "hallway.\n");
}

string
statue_description()
{
    return "You peer up and see statues of old monks as well "
        + "as current ones: " + describe_statues(1) + ".\n";

}

