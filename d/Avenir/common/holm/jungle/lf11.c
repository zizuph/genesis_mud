// file name:        /d/Avenir/common/holm/jungle/lf11.c
// creator(s):       Lilith, Nov 96
// revisions:
// purpose:
// note:
// bug(s):
// to-do:           

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/jungle/jungle_base";

/* Include the local area defines, etc */
#include "/d/Avenir/common/holm/holm.h"

/*
 * Function name: reset_domain_room
 * Description:   This function should be used for for reseting herbs
 */
void reset_domain_room()
{
    set_searched(0);
    ::reset_domain_room();
}

/* Now create the room.  */
void
create_jungle_room()
{
    set_short("Base of an avalanche");
    set_long("You stand at the base of an avalanche. Loose stones "+
        "have formed a wart-like bulge at the forest's edge. "+
        "South, a crest of dark stone overhangs a ridge of rock "+
        "pillars like a giant wave waiting with endless patience "+
        "for the opportunity to break itself upon the greenery "+
        "below. Behind you, the forest seems to breathe, "+
        "exhaling a thick mist that settles around your ankles.\n");

    add_exit("lf8", "north", 0);

    add_cliff();
    add_moss();
    add_atrack();
    add_item(({"bulge", "wart-like bulge", "stones"}), 
        "Loose stones have fallen down the cliffside, and formed a "+
        "bulge at the base.\n");
    add_item("pillars", "The pillars are simply eroded stone which "+
        "stand upright in defiance of gravity.\n");
    add_item(({"ridge", "crest", "dark stone"}), "Above the pillars "+ 
        "is a ridge that is overhung by a dark spire fringed with "+
        "green.\n");
   reset_domain_room(); 
}
