/*
 * /d/Gondor/Lorien/std/dimrill_base_room.c
 * Base room for the road to Lorien
 *
 * Mona 2020 
 *
 * Thanks: Varian for sharing his Anorian base.c code
 *
 */


#include "../lorien_defs.h"

inherit LORIEN_DIR_STD + "lorien_room";
inherit "/d/Gondor/common/lib/herbsearch";
inherit "/d/Gondor/common/lib/room_tell";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <macros.h>
#include "/d/Gondor/lorien/std/descriptors.c"
void 
create_dimrill_room() 
{
}

nomask void 
create_lorien_room() 
{

    create_dimrill_room();

} 


    add_item("dell"), 
        "The dell plunges down from the road on either side.  The sides " +
        "of the dell are steep and slope downwards towards a flat level " +
        "space at the bottom. Short bent fir trees grow amongst the green " +
        "plants and bushes that clothe the slopes.\n");
    add_item( ({"plants", "green plants", "plant", "green plant"}),
        "The majority of the green plants are a mixture of some odd looking " +
        "ferns, and some berry bushes.\n");
    add_item( ({"bushes", "berry bushes"}),
        "The berry bushes are pretty similar in appearance, but with " +
        "different colours of berries.  XXX\n");
    add_item( ({"colors", "colours", "color", "colour"}),
        "There are blue, deep blue, and red berry bushesn.\n");
    add_item( ({"fern", "ferns", "harts tongue", "harts-tongue", 
        "odd looking ferns", "odd ferns"}),
        "The leaves of this plant grow out from a center point looking " +
        "like a group of long shiny green tongues.  The ferns are unique " +
        "in appearance because the fronds lack the tooth-like divisions " +
        "most ferns are known for, and because they are slick and shiny." +
        "It is for their shape, like the long tongue of a deer, that " +
        "this foliage get's its name.  Harts-tongue.\n"); 
    add_item( ({"fronds", "frond", "tongues", "tongue", "leaves", "leaf"}),
        "The front of the fronds are a contiguous shiny green like long " +
        "thin tongues. On the back of the fronds one can see the " +
        "indications of the fern-like divisions, in the form of little " +
        "brown cigar-shaped clumps of spores.\n"); 
    add_item( ({"cigars", "cigar", "spore", "spores", "clumps of spores",
        "divisions", "division", "ladders", "ladder"}),
        "The spores cling to the back of the leaves like little ladders " +
        "made of tiny cigars.\n");
    add_item( ({"slope", "slopes"}),
        "The slope of the dell is about 45 degrees.  It is quite a steep " +
        "climb in or out of the dell.\n");
    add_item( ({"trees", "fir trees", "bent trees", "short trees", 
        "short bent trees", "short bent tree", "fir tree"}),
        "The fir trees that grow along the dell are short and bent, due to " +
        "the incline, having first grown outward from the soil and then " +
        "bent upwards towards the sun.  The trees are XXX\n");
    add_item( ({"bottom", "grassy space", "space"}),
        "The bottom of the dell is flat and grassy.  It looks like a nice " +
        "place to stop and rest or have a picnic.\n");
    add_item( ("grass"),
        "The grass is lush and green, and looks to be an inviting place " +
        "to relax.\n");

//stone or rock for firepit
Vaccinium myrtillus, bilberry, or blue whortleberry
Vaccinium vitis-idaea, lingonberry or red whortleberry
Vaccinium uliginosum, bog whortleberry/bilberry