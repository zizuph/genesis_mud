/*
 *  /d/Gondor/minas/houses/hallows1.c
 *
 *  The Rath Dinen, Before the Tombs.
 *
 *  Alto, 18 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/std/room.c";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/std/tell.c"


#define INNER_MINAS "/d/Gondor/minas"


public void
create_gondor()
{
    set_short("On the Rath Dinen, before the Tombs");
    set_long("The blinding fog suddenly vanishes and you find yourself "
        + "standing on a wide paved avenue. Here the Rath Dinen is true "
        + "to its name, the Silent Street, where there are no sounds "
        + "save your own breathing. Looming before you to the north is "
        + "the House of Stewards. To the south is the House of Kings.\n");

    add_exit(INNER_MINAS + "/houses/stewards1", "north", 0, 0);
    add_exit(INNER_MINAS + "/houses/kings1", "south", 0, 0);
    add_exit(INNER_MINAS + "/dinen/dinen23", "west", 0, 0);

    add_item(({"fog", "blinding fog"}), "To the west, where the "
        + "Rath Dinen narrows into a path, a thick fog can be seen "
        + "gathering.\n");
    add_item(({"path"}), "On the west end of the street, the Rath "
        + "Dinen narrows to a small path covered in white gravel.\n");
    add_item(({"gravel", "pebbles"}), "The western path is covered "
        + "by small white pebbles that look to have come from the Sea.\n");
    add_item(({"street", "rath dinen", "avenue"}), "Here the Rath Dinen is wide "
        + "and paved with large square flagstones. It comes to an end "
        + "against the precipice of Mount Mindolluin, where the Houses "
        + "of Kings and Stewards stand.\n");
    add_item(({"precipice", "mountain", "mount mindolluin"}), "A large "
        + "knee of the mountain has cut off the eastern end of the "
        + "valley. The mountain thus dominates the eastern, northern "
        + "and western sky.\n");
    add_item(({"sky", "horizon", "lightning"}), "Mount Mindolluin walls "
        + "the eastern horizon, "
        + "wraps around to the north and rises out of sight to the west. "
        + "Lightning flickers now and then, but you can hear no thunder.\n");
    add_item(({"flagstones"}), "Heavy white flagstones pave the Rath "
        + "Dinen here. They appear to be made of the same stone from which "
        + "the two Tombs are constructed.\n");
    add_item(({"building", "buildings"}), "Which one? There are two "
        + "of them: the House of Kings and the House of Stewards.\n");
    add_item(({"houses", "tombs"}), "The House of Kings stands to the "
        + "south. The House of Stewards stands in the north like a "
        + "mirror image. Neither house looks like a place to tread lightly.\n");
    add_item(({"house of kings"}), "A massive flight of stone stairs "
        + "leads to the great tomb of the Kings of Gondor. Many giant "
        + "columns line the front of the building, and images of men "
        + "long dead can be seen among the empty halls beneath its "
        + "pale dome. Although none but the dead sleep here, a feeling "
        + "of danger emanates from the Tomb.\n");
    add_item(({"house of stewards"}), "A massive flight of stone stairs "
        + "leads to the resting place of the Stewards of Gondor. Many "
        + "giant columns line the front of the building, and images of "
        + "men long dead can be seen among the empty halls beneath its "
        + "pale dome. Although only Stewards long dead rest within, a "
        + "feeling of danger emanates from the Tomb.\n");
    add_item(({"flight", "stairs"}), "There must be one hundred large "
        + "rectangular stairs leading down from each Tomb. The thought "
        + "of climbing them sends shivers down your spine.\n");
    add_item(({"columns", "images"}), "Fifty huge columns stand before "
        + "each Tomb. Among them are the carven images of men long dead. " 
        + "From here you cannot make out any details.\n");
    add_item(({"hall", "halls"}), "From here only the entrance halls "
        + "of each Tomb are visible.\n");
    add_item(({"dome", "domes"}), "Atop each Tomb rises a towering white "
        + "dome. Flags hang from poles mounted at the apex of each.\n");
    add_item(({"flags"}), "A flag bearing a silver tree with seven silver "
        + "stars on a sable field hangs from the dome on the House of "
        + "Kings. A plain white flag is mounted above the House of "
        + "Stewards.\n");
    add_item(({"stone", "native stone", "blocks"}), "Tough stone quarried from "
        + "the foothills of Mount Mindolluin. You wonder how the huge "
        + "blocks could have possibly been transported to this place.\n");



    reset_room();

}   

