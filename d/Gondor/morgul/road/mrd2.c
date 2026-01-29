/*
 *	/d/Gondor/morgul/road/mrd2.c
 *
 *	Coded by Olorin.
 *
 *	Modification log:
 *	30-Jan-1997, Olorin:	Changed inheritance.
 */
#pragma strict_types

inherit "/d/Gondor/morgul/road/mroad.c";

#include "/d/Gondor/defs.h"

public void
create_area_room()
{
    set_areatype(8);
    set_areadesc("barren field");
    set_area("evil");
    set_areaname("Ithilien");
    set_land("Gondor");
    set_extraline("The road runs east from here, climbing steeply, while "+
    "it turns northwest rounding the great shoulder of rock here. "+
    "A long-tilted valley, a deep gulf of shadow, runs back far back into "+
    "the mountains. Upon the further side, some way within the "+
    "valley's arms, high on a rocky seat upon the black knees of the "+
    "Ephel Duath, stands the walls and tower of Minas Morgul. All is "+
    "dark about it, the earth and the clouded sky, but the city is lit "+
    "with a ghostly glow that illuminates nothing. Further east the road "+
    "reaches a bridge crossing the stream towards Minas Morgul.");
    add_item("bridge","The bridge is white, and permits the road to pass across\n"+
    "the foul-smelling stream. The faintly glowing road then goes on\n"+
    "towards the black gate of Minas Morgul.\n");
    add_item("road","The old road runs east towards a white bridge crossing the\n"+
    "Morgulduin, glowing faintly. In the other direction it turns northwest\n"+
    "rounding a great rocky shoulder of the mountain.\n");
    add_item(({"city","morgul","minas morgul"}),
    BS("The city of Minas Morgul lies on the far side of the stream. It "+
    "is lit with light, although not the enchanted moonlight of long ago, "+
    "but paler indeed than the moon, wavering and blowing like a noisome "+
    "exhalation of decay, a corpse-light, a light illuminating nothing. "+
    "In the walls and tower windows show, like countless black holes looking "+
    "inward into emptiness, but the topmost course of the tower revolved "+
    "slowly, first one way and then another, a huge ghostly head leering "+
    "into the west.\n"));
    add_item("stream","The foul smell from the Morgulduin makes you want to\n"+
    "stay as far away from it as possible.\n");

    add_exit(MORGUL_DIR +"road/mrd3", "east",      check_allow, 2);
    add_exit(MORGUL_DIR +"road/mrd1", "northwest", stop_escape, 2);

    set_up_herbs( ({ HERB_DIR + "morgurth", HERB_DIR + "angurth" }), 
        ({"bank", "flat", "ground", "meadow"}), 3);

    reset_room();
    enable_reset(200);

}
