
/* Entrance to the museum. Cirion 042296 */
// Lilith Oct 2021: changed museum exit dir to be to ne

inherit "/std/room";
#include "/d/Avenir/common/common.h"

void create_room()
{
    set_short("Northeast to Museum and Kestares Tribunal");
    set_long("The path ends abruptly in the east, blocked by a high "+
        "mud-brick wall. A stone path climbs northeast here, toward "+
		"extensive grounds and a massive edifice of white marble with "+
		"pillars rising up on either side of "+
        "the archway leading within. The gravel walk gives way to a "+
        "cobbled path which flows south between the back of buildings "+
		"and the mud-brick wall. "+
        "The sudden formality here is a curious change from the funct"+
        "ional nature of the bazaar in the west.\n");
    AI(({"pillar","pillars"}),
        "They are huge, made from white polished granite.\n");
    AI(({"building","edifice","house","museum"}),
        "It is a massive building, pristine and white.\n");
    AI(({"path", "stone path", "northeast path", "slabs"  }),
        "It looks like it is made of irregular slabs of "+
        "stones such as jasper and carnelian. It curves away "+
        "to the northeast.\n");
    AI(({"cobbled path", "cobbles", "cobblestones", "cobblestone"}), 
	    "The cobbles of the path are simple gray stones.\n");
    AI(({"walk", "gravel", "gravel walk" }), 
        "It leads west toward the center of the bazaar.\n");
    AI(({"wall", "mud-brick wall" }),
        "It is a mud-brick wall, very high, and so smooth as to be "+
        "fairly impossible to climb.\n");
    AI(({"buildings", "back of buildings", "bazaar buildings"}),
        "These are the back sides of the bazaar buildings.\n");

    AE(BAZAAR+"extr/str15", "west");
    AE(BAZAAR+"extr/str25", "south");
    AE(BAZAAR+"museum/gallery1", "northeast");
}
