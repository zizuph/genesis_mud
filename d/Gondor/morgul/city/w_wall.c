#pragma strict_types

inherit "/d/Gondor/common/lib/area_room";
inherit "/d/Gondor/morgul/feeling.c";

#include <macros.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"

#define  OTHER_SIDE    (MORGUL_DIR + "city/sec_entr")

/*
 *  Global Variables
 */
int     opening;
string  passage_text = " A dark passageway has opened in the dark"
                     + " stone surface of the wall here, surrounded"
                     + " by the thick clinging shadows.";

#include "/d/Gondor/morgul/city/entr_funs.h"  // its ugly, so sue me...

public string
short_desc()
{
    return "along the perimiter walls of Minas Morgul, just"
      + " west of the City Gate";
}

public string
long_desc()
{
    return "Along the perimeter walls of Minas Morgul, just"
      + " west of the City Gate. A barely noticable path has crept"
      + " away from the main road to the east following the line of"
      + " the heavy city walls. Shadows have fallen over everything"
      + " in this place, focusing a great darkness especially over"
      + " the outward wall of the city, which frowns down on the path"
      + " from the immediate south.\n";
}

void
create_area_room()
{
    set_areatype(AREATYPE_NONE);
    set_areadesc("concealed path");
    set_area("outer walls");
    set_areaname("Minas Morgul");
    set_land("Gondor");

    add_item(({"wall","walls","perimeter wall","perimeter walls"}),
        "@@exa_wall");
    add_item(({"rune","runes","inscription","inscriptions","letter",
               "letters"}), "@@exa_runes");
    add_item(({"gate","city gate","great city gate"}),
        "The gate is a ways off to the east following the wall"
      + " of the city. It is not directly visible from here.\n");
    add_item(({"morgul","minas morgul","city"}),
        "The city of Dark Sorcery looms to the south, closing"
      + " off vision of all but its cruel and darkly lit walls. From"
      + " within, a presence of power and terror can be felt.\n");
    add_item(({"sky","moon","sun","stars","clouds","cloud","star"}),
        "The shadows cast from the great walls of the city seem"
      + " to encase that which is above as well as below in their"
      + " deep shroud. Neither sun, nor moon, nor light of star is"
      + " to be seen.\n");
    add_item(({"ground","path","paths"}),
        "The path is barely visible, being little more than a"
      + " slightly worn stretch of the otherwise barren ground. It"
      + " seems to disappear into the darkness along the wall.\n");
    add_item(({"darkness","gloom","shadow","shadows"}), "@@exa_shadows");
    add_item(({"opening","openings","passageway","passageways",
               "dark opening","dark passageway"}),
        "@@exa_opening");

    add_cmd_item(({"rune","runes","inscription","wall"}), "read",
                 exa_runes());

    add_exit(MORGUL_DIR + "city/w_wall1","east");
    
    set_up_herbs( ({ HERB_DIR + "morgurth", HERB_DIR + "angurth" }), 
                 ({"bank", "flat", "ground", "meadow"}), 3);
    enable_reset(200);
}

void
open_wall()
{
    OTHER_SIDE->open_wall();
}

void 
setup_passageway_exit() 
{
    add_exit(OTHER_SIDE, "south", block_passageway);
}

void
remove_passageway_exit()
{
    remove_exit("south");
}

void
init()
{
    ::init();

    add_action(rasp_password, "rasp");
}
