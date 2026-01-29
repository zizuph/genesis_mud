#pragma strict_types
inherit "/d/Gondor/common/lib/area_room";

#include "/d/Gondor/defs.h"


public string
short_desc()
{
    return "on a concealed path before the outer walls of Minas"
       + " Morgul";
}

public string
long_desc()
{
    return "A deeply shadowed pathway runs along the outer wall"
      + " of Minas Morgul here, heading away from the main gate of"
      + " the city which lies to the east. Darkness has fallen over"
      + " this area like a shroud, becoming denser as the path winds"
      + " to the west.\n";
}

void
create_area_room()
{
    set_areatype(AREATYPE_NONE);
    set_areadesc("concealed path");
    set_area("outer walls");
    set_areaname("Minas Morgul");
    set_land("Gondor");

    add_item(({"ground","path","shadowed path"}),
        "The path which runs along the ground here does not seem"
      + " to be used much by feet which leave any prints. It runs"
      + " east and west along the wall.\n");
    add_item(({"wall","outer wall","city wall"}),
        "The wall of the city frowns down over this path casting"
      + " deep shadows all about. The heavy masonry of the Kings of"
      + " old Gondor is evident in this work, though it has since been"
      + " defiled and put to evil purpose. It is not unlikely that"
      + " some Dark Sorcery is at work in its frame.\n");
    add_item(({"gate","main gate","city gate","great gate"}),
        "To the east the path runs toward the main gate of the"
      + " city, which is watched by many unseen eyes. The shadows"
      + " seem to lift slightly in that direction.\n");
    add_item(({"darkness","shadows","shadow"}),
        "The shadows which cover this path and the area do not"
      + " seem to have been cast entirely by the looming city wall"
      + " which rises directly to the south. Many of these shadows"
      + " linger and wait, heedless of light or movement.\n");
    add_item(({"sky","sun","moon","stars"}),
        "The shadows cast on this area seem to have dimmed even"
      + " the sky above, for no light comes to this place from sun,"
      + " moon, or stars.\n");

    add_exit(MORGUL_DIR + "city/w_wall","west");
    add_exit(MORGUL_DIR + "city/o_ngate","east");
    
    set_up_herbs( ({ HERB_DIR + "morgurth", HERB_DIR + "angurth" }), 
                 ({"bank", "flat", "ground", "meadow"}), 3);
    enable_reset(200);
}
