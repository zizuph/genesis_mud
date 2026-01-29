/*
 * File:    hall_lower_south.c
 * Creator: Cirion, 1998.06.02
 * Purpose: South entrance hall to the monks guild
 */
#pragma strict_types

// since this is a guild room, save the binary of the file
// to facilitate quick loading after reboots
#pragma save_binary

#include "defs.h"

inherit ROOMBASE;

void
create_room ()
{
    set_short("great hall south");

    set_long("Grave and solemn, the south "
        + "end of this great hall lies in dusk and gloom. "
        + "The hall extends to the "
        + "north, where you can see sunlight "
        + "falling upon the floor through the metal "
        + "lattice ceiling. Within the east and west "
        + "walls are tall empty niches. Through the opening to the "
        + "west and framed by carved jade "
        + "pillars can be seen a massive, ornately "
        + "decorated temple. A stone archway "
        + "to the east leads into a large hall dominated "
        + "by a massive table, and a short passage to the "
        + "south leads out into a garden."
        + living_view("hall_lower_north", " Standing in the north "
        + "great hall, "
        + "you see ", ".", "")
        + "\n");

    add_item(({"floor","tile","tiles","ground","stone"}),"The "
        + "square tiles "
        + "that make up the floor are rough stone, "
        + "fitted together evently "
        + "and with great care. The stone, although "
        + "rough, is worn down "
        + "by the passage of many feet over the years.\n"
        + VBFC_SAY("stoops down to examine the stone tiles "
        + "that make up the floor.\n"));
    add_item(({"sun","sunlight"}),
        "The sunlight falling on the stones to the north "
        + "looks warm and inviting.\n");
    add_item(({"metal","lattice"}),
        "You can make out no details about the lattice "
        + "ceiling to the north.\n");
    add_item(({"ceiling","roof"}),
        "The ceiling high about is of dark stone blocks, "
        + "placed together to create a very shallow dome. "
        + "Painted on the ceiling is a vast mural of a "
        + "great, sinuous dragon.\n");
    add_item(({"dragon","mural","painting"}),
        "The dragon in the mural stares down at you with "
        + "indifferent eyes.\n");
    add_item("eyes",
        "The eyes of the dragon in the painting are "
        + "sparkling green.\n");
    add_item(({"temple","west"}),
        "You can make out few details of the dark temple to "
        + "the west.\n");
    add_item(({"pillar","pillars"}),
        "The pillars framing the entrance to the temple are "
        + "thin columns of jade, rising all the way to the "
        + "painted ceiling.\n");
    add_item("jade",
        "The jade of the pillars is smooth and lusterless.\n");
    add_item(({"passage","passageway","south"}),
        "A short passage runs into the southern wall, and "
        + "opens up into what looks like a large, sunlit "
        + "garden.\n");
    add_item(({"niche","niches","east niches","west niches"}),
        " These niches are decorative, being set into the "
        + "walls to accentuate the feelings of great speace "
        + "in this room.  The Niches are but a handsbreadth "
        + "deep and each has a unique and rather abstract "
        + "mosaic set into the mortar.\n");
    add_item(({"mortar","mosaic","mosaics"}),
        " The mosaics are abstract, formed of thousands of "
        + "tiny pieces of stone, bone, shell, and pottery "
        + "and tile shards pressed into mortar.\n");
    add_item(({"wall","walls","east wall","west wall","archway"}),
        "Made of pale gray stone that is simply dressed and "
        + "seamlessly fitted together.\n");

    add_cmd_item(({"stone","stones","tile","tiles","ground"}),
        ({"touch","feel"}),
        "The stones of the floor are smooth with the passage of many feet.\n"
        + VBFC_SAY("reaches down and touches the stone tiles.\n"));
    add_cmd_item(({"arch","archway"}), ({"touch","feel"}),
        "The marble of the eastern arch is smooth and cold.\n"
        + VBFC_SAY("touches the cold marble of the eastern arch.\n"));
    add_cmd_item(({"air","incense"}), ({"smell","sniff"}),
        "The air smells faintly of incense.\n"
        + VBFC_SAY("smells the air.\n"));

    add_prop(ROOM_I_INSIDE, 1);


    WIZINFO("This room is the south entrance hall to the monks guild.\n");

    // where, command
    add_exit("hall_lower_north", "north");
    add_exit("dining_hall", "east");
    add_exit("temple_e", "west");
    add_exit("garden", "south");

    // when we come from DIRECTION, we see MESSAGE
    ENTRANCE_MSG("north", "You pass along the great hall, "
        + "your footfalls making "
        + "no noise on the smooth stone underfoot.\n");
    ENTRANCE_MSG("east", "You walk through the doorway into the "
        + "great hall.\n");
    ENTRANCE_MSG("west", "You walk out of the temple into the "
        + "south great hall.\n");

}


