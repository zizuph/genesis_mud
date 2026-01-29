#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <stdproperties.h>

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("Between tall wooden buildings");
    set_long("The narrow street, more resembling an"+
        " alley, leads between two-story wooden buildings"+
        " built closely together to give room for as"+
        " many as possible. This is probably living quarters"+
        " for fishermen and harbour workers, making up the"+
        " lower class of the population of Gont Port. The"+
        " walls of the houses lean in over the street,"+
        " casting dark shadows over it. To the southwest"+
        " the living quarters change to warehouses, and"+
        " you can spot the grey water of the harbour"+
        " beyond while to the east the narrow street"+
        " continues further inside the city. Just to the north"+
        " is a small dark sinister stone building with bars on"+
        " the windows.\n");
    add_item("walls","The walls of the houses are built"+
        " of wooden boards, and lean in a dangerous angle"+
        " out over the narrow street you are standing on.\n");
    add_item("city","You are in the busy city of Gont"+
        " Port, renowned all over the Archipelago for the"+
        " good trading opportunities and the perfectly"+
        " protected natural harbour.\n");
    add_item(({"street","alley"}),"The narrow street"+
        " is almost just another alley leading between the"+
        " tall two-story wooden buildings. The walls"+
        " of the houses lean in over your head, casting dark"+
        " shadows over the dirty street.\n");
    add_item((({"building", "small building", "dark building",
        "sinister building", "small dark sinister building",
        "north building"})),
        "The building to the north looks like it might be a "+
        "jailhouse.\n");
    add_item(({"houses","buildings"}),
        "On both sides of the street"+
        " are two-story wooden buildings packed closely"+
        " together to give room for as many as possible."+
        " These houses are probably living quarters for"+
        " fishermen and harbour workers.\n");
    add_item("water","Through the alley to the southwest"+
        " you can spot the grey water of the harbour.\n");
    add_item("warehouses","To the southwest the living"+
        " quarters change to warehouses as you get closer"+
        " to the harbour.\n");
    add_exit("city_road21", "southwest");
    add_exit("city_road27", "east");
    add_exit("../jailhouse", "north");
}
