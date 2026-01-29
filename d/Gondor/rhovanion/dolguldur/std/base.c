/*
 * Base room for Dol Guldur
 *
 * Varian - November 2020
 */

#include "/d/Gondor/rhovanion/defs.h"

inherit RHOVANION_DIR + "dolguldur/std/room";
inherit "/d/Gondor/common/lib/herbsearch";
inherit "/d/Gondor/common/lib/room_tell";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <macros.h>
#include "/d/Gondor/rhovanion/dolguldur/std/descriptors.c"

void set_items_road();
void set_items_path();
void set_items_city();
void set_items_ruins();
void set_items_broken();
void set_herbs_1();
void set_herbs_2();

/*
 * Function name:        create_dg_room
 * Description  :        Use create_dg_room() to make rooms around Dol Guldur
 *                       which use information from this file
 */
void create_dg_room() 
{
}
/*create_dg_room*/

/*
 * Function name:        create_dolguldur_room
 * Description  :        Uses /d/Gondor/rhovanion/dolguldur/std/room.c to
 *                       create the local rooms
 */
nomask void create_dolguldur_room() 
{

    create_dg_room();

/* add_tell - used when inheriting /d/Gondor/common/lib/room_tell and all
 * VBFC items are found within /d/Gondor/rhovanion/dolguldur/std/descriptors.c
 * lines will be randomly chosen to provide "sounds" to the rooms */        
        add_tell("Dark, ominous clouds pass in front of the " + 
            VBFC("sun_moon") + ", hiding the " + VBFC("light_type") + 
            " from looking down upon Dol Guldur.\n");
        add_tell("The bright " + VBFC("daylight_desc") + " peeks out from " +
            "the dark clouds to glare down upon the ruins of Dol Guldur.\n");
        add_tell("As the dark clouds part in the sky, bright " + 
            VBFC("light_type") + " from the " + VBFC("day_desc") + 
            " " + VBFC("sun_moon") + " stretches out to cover " +
            "the land around you.\n");
        add_tell("You hear the echo of marching feet thumping " +
            "in the distance.\n");
        add_tell("The faint buzzing of insects echoes from the " +
            "nearby forest.\n");
        add_tell("As the dark clouds drift slowly across the sky, " +
            "the ruined towers of Dol Guldur stand out " +
            "like broken, jagged teeth in the shadows of the " +
            VBFC("day_desc") + " " + VBFC("light_type") + ".\n");
        add_tell("Two sparrows zip past you nearby, chasing " +
            "each other in the " + VBFC("light_type") + ".\n");
        add_tell("A cold wind whistles as it blows through " +
            "the trees and nearby ruins.\n");
        add_tell("A light breeze curls past you.\n");
        add_tell("You catch the scent of rotting garbage in the " +
            "air as a swift breeze swirls past you.\n");
        add_tell("A foul smell lingers in the air here.\n");
        add_tell("You hear a blood-curdling scream echo through " +
            "the ruins of Dol Guldur.\n");
        add_tell("You feel a set of eyes watching you from some nearby " +
            "shadows.\n");

    add_item( ({"cloud", "clouds", "dark cloud", "dark clouds"}),
        "Dark clouds hang overhead in a persistent, almost ominous " +
        "fashion.\n");
    add_item( ({"wildlife", "animals"}),
        "Various animals and birds seem to dart around the shadows " +
        "of the nearby\n");
    add_item( ({"sparrow", "sparrows"}),
        "You notice the occasional presence of some sparrows flitting " +
        "around from the nearby trees of Mirkwood forest.\n");
    add_item( ({"insect", "insects"}),
        "There is an endless droning buzz of insects surrounding you " +
        "here.\n");

/* set_tell_time  Provides time increments between tells */
        set_tell_time(random(500) + 70);

}
/*create_dolguldur_room*/

/*
 * Function name:        enter_inv
 * Description  :        Needed to start the room tells
 */
void
enter_inv(object ob, object from)
{
    start_room_tells();
    ::enter_inv(ob, from);
}
/*enter_inv*/

/*
 * Function name:        set_items_road
 * Description  :        Items added to road rooms when you include the line
 *                       set_items_road(); 
 *                       Use for all rooms on the road to Dol Guldur
 */
void
set_items_road()
{
    add_tell("You hear a faint rustle in some nearby bushes.\n");

    add_item( ({"road", "path", "trail"}),
        "Ancient stones peek through the ground along the ancient road you " +
        "are following. The ruins of Dol Guldur are nearby to the " +
        "northeast, and the trail here seems to wind away to the southwest " +
        "towards the Anduin river.\n");
    add_item( ({"stone", "stones", "paving stone", "paving stone",
            "ancient stone", "ancient stones", "ancient paving stone",
            "ancient paving stones"}),
        "Several paving stones, long ruined, peek through the ground here " +
        "in the middle of the road to Dol Guldur.\n");
    add_item( ({"city", "dol guldur", "ruins"}),
        "The ruins of Dol Guldur loom nearby, rising up against the " +
        "northeastern horizon. It has been rumoured that the ruins have " +
        "once again been inhabited.\n");
    add_item( ({"river", "anduin", "anduin river"}),
        "The Anduin river is not visible from here, being somewhere in the " +
        "distance to the southwest. An ancient road here seems to lead " +
        "towards it, away from the nearby ruins of Dol Guldur.\n");
    add_item( ({"ground", "down"}),
        "The ground here is mostly hard packed dirt along the ancient " +
        "road, while long grass and bushes grow along the edges as a " +
        "dark forest rises up along either side of the path.\n");
    add_item( ({"dirt", "hard dirt", "packed dirt"}),
        "The dirt here is packed hard, broken only by some ancient pacing " +
        "stones which follow the road to Dol Guldur.\n");
    add_item( ({"grass", "long grass", "brown grass", "long brown grass"}),
        "Tall strands of long, brown grass line the edge of the road " +
        "before melting away from the dark trees of Mirkwood forest. An " +
        "occasional breeze dances down the road, causing the grass to " +
        "wave back and forth in the wind.\n");
    add_item( ({"bushes", "bush", "shrub", "shrubs", "shrubbery"}),
        "Several bushes huddle up beneath the black trees of Mirkwood " +
        "forest, rustling in the wind, watching you in malicious silence " +
        "as you follow the road to Dol Guldur.\n");
    add_item( ({"tree", "black tree", "trees", "black trees", "dark tree",
            "dark trees", "tall tree", "tall trees"}),
        "Tall and black, the trees of Mirkwood forest loom over the " +
        "road to Dol Guldur, carefully monitoring your every move.\n");
    add_item( ({"forest", "mirkwood", "mirkwood forest"}),
        "The dark shadows of Mirkwood forest, born of the tall black " +
        "trees there, line both sides of the road to Dol Guldur.\n");
    add_item( ({"shadow", "shadows", "eyes", "unseen eyes"}),
        "Dark and oppressive, shadows linger at the edge of Mirkwood " +
        "forest where it meets the road here. The unescapable feeling " +
        "of being watched by unseen eyes never seems to leave you.\n");
    add_item( ({"up", "sky"}),
        "Dark clouds seem to eminate from the northeasten horizon above " +
        "the ruins, obscuring the " + VBFC("light_type") + " from the " +
        VBFC("day_time") + " " + VBFC("sun_moon") + ".\n");
    add_item( ({"garbage", "rotting garbage"}),
        "You cannot see any here, but the stench of rotting garbage " +
        "drifts towards you every time the wind blows out of the " +
        "northeast.\n");
}
/*set_items_road*/

/*
 * Function name:        set_items_path
 * Description  :        Items added to path rooms when you include the line
 *                       set_items_path(); 
 *                       Use for all rooms on the path around Dol Guldur
 */
void
set_items_path()
{
    add_tell("You hear a faint rustle in some nearby bushes.\n");
    add_tell("Black branches sway in the wind, bending over the path " +
        "as if reaching towards you.\n");

    add_item( ({"road", "path", "trail", "hidden road", "hidden path",
            "hidden train"}),
        "This hidden path runs through the forest, following just close " +
        "enough to the walls of Dol Guldur that glimpses of the wall can " +
        "be seen while remaining hidden from any watchers.\n");
    add_item( ({"dirt", "packed dirt", "hard dirt"}),
        "The dirt here is packed, as this was probably a game trail at one " +
        "time.\n");
    add_item( ({"city", "dol guldur", "ruins"}),
        "The ruins of Dol Guldur loom nearby, visible at times through the " +
        "black trees of Mirkwood. It has been rumoured that the ruins have " +
        "once again been inhabited.\n");
    add_item( ({"river", "anduin", "anduin river"}),
        "The Anduin river is not visible from here, being somewhere in the " +
        "distance to the southwest.\n");
    add_item( ({"ground", "down"}),
        "The ground here is mostly hard packed dirt along the hiden trail, " +
        "but everything off the trail is obscured by the thick brush which " +
        "huddles at the feet of Mirkwood's black trees.\n");
    add_item( ({"bushes", "bush", "shrub", "shrubs", "shrubbery"}),
        "Several bushes huddle up beneath the black trees of Mirkwood " +
        "forest, rustling in the wind, watching you in malicious silence.\n");
    add_item( ({"tree", "black tree", "trees", "black trees", "dark tree",
            "dark trees", "tall tree", "tall trees"}),
        "Tall and black, the trees of Mirkwood forest loom above you on " +
        "this hidden path, carefully monitoring your every move.\n");
    add_item( ({"forest", "mirkwood", "mirkwood forest"}),
        "The dark shadows of Mirkwood forest, born of the tall black " +
        "trees there, surround you in almost every direction.\n");
    add_item( ({"shadow", "shadows", "eyes", "unseen eyes"}),
        "Dark and oppressive, shadows linger inside Mirkwood forest, " +
        "falling over your every step in here. The unescapable feeling " +
        "of being watched by unseen eyes never seems to leave you.\n");
    add_item( ({"up", "sky"}),
        "Dark clouds seem to eminate from the easten horizon above " +
        "the ruins, obscuring the " + VBFC("light_type") + " from the " +
        VBFC("day_time") + " " + VBFC("sun_moon") + ".\n");
    add_item( ({"garbage", "rotting garbage"}),
        "You cannot see any here, but the stench of rotting garbage " +
        "drifts towards you every time the wind blows from the direction " +
        "of Dol Guldur.\n");
    add_item( ({"wall", "walls", "city wall", "city walls"}),
        "Barely visible through the trees, you can just make out the " +
        "rebuilt walls of Dol Guldur to the east.\n");
}
/*set_items_path*/

/*
 * Function name:        set_items_city
 * Description  :        Items added to rooms when you include the line
 *                       set_items_city; 
 *                       Use for all rooms inside of Dol Guldur
 */
void
set_items_city()
{
    add_tell("A small troop of orcs marches down the street.\n");
    add_tell("In the distance, you notice a group orc orcs sparring with " +
        "each other. Or are they killing each other? That last blow " +
        "looked fatal.\n");
    add_tell("A small orc runs past you on the street, ignoring you " +
        "completely.\n");

    add_item( ({"forest", "mirkwood", "mirkwood forest", "woods"}),
        "The tall black trees of Mirkwood forest are visible nearby, " +
        "their shadowy presence a constant feature in the background as " +
        "they tower above the city walls.\n");
    add_item( ({"wall", "city wall", "walls", "city walls"}),
        "The city walls of Dol Guldur have recently been restored, with " +
        "massive blocks of rough grey stone expertly cut and mortared " +
        "into place.\n");
    add_item( ({"ground", "down", "paving", "paving stones", "paved"}),
        "The city streets have been recently been paved with wide slabs " +
        "of flat stone.\n");
    add_item( ({"up", "sky"}),
        "Dark clouds drift up to cover the sky above you, obscuring the " 
        + VBFC("light_type") + " from the " + VBFC("day_time") + " " + 
        VBFC("sun_moon") + ".\n");
    add_item( ({"tree", "trees", "black tree", "black trees", "tall tree",
            "tall trees"}),
        "The tall black trees of Mirkwood are visible above the walls " +
        "of Dol Guldur.\n");
    add_item( ({"shadow", "shadows"}),
        "The city of Dol Guldur is seemingly covered in shadows, almost " +
        "as if they are bleeding in from the forest of Mirkwood which " +
        "surrounds the city walls.\n");
    add_item( ({"tower", "broken tower", "ruined tower"}),
        "Rising high above everything else, even the massive trees of " +
        "Mirkwood, is a broken tower of black stone that stands in the " +
        "middle of the city.\n");
    add_item( ({"garbage", "rotting garbage"}),
        "The city of Dol Guldur may have been recently restored, but " +
        "it is quickly becoming a mess. It appears that the inhabitants " +
        "have dropped garbage in almost every nook and corner, creating " +
        "a stench which is almost overpowering at times.\n");
    add_item( ({"stone", "stones"}),
        "Were you trying to look at the wall or the paving stones?\n");
    add_item( ({"ruin", "ruins", "rubble", "pile", "piles"}),
        "Although Dol Guldur has been largely restored in places, large " +
        "piles of rubble and ruins are still visible all around you.\n");
    add_item( ({"orc", "orcs", "soldier", "soldiers", "army"}),
        "This part of Dol Guldur appears to be heavily populated by " +
        "orcs, most of whom appear to be soldiers in a gathering army.\n");
    add_item( ({"building", "buildings", "ruined building",
            "ruined buildings"}),
        "The city of Dol Guldur is filled with ruined buildings, and " +
        "while much of the southwestern quarter has been restored, the " +
        "remnants of old buildings surround you.\n");
    add_item( ({"restored building", "restored buildings", "restored quarter",
            "southwest quarter", "southwestern quarter"}),
        "While much of the city is still in ruins, the southwestern " +
        "quarter of the city has been restored enough to house a " +
        "small army.\n");
}
/*set_items_city*/

/*
 * Function name:        set_items_ruins
 * Description  :        Items added to rooms with ruins when you include
 *                       the line set_items_ruins(); 
 *                       Use for all rooms with ruins
 */
void
set_items_ruins()
{
    add_tell("A small brown bird settles on a broken wooden beam for " +
        "a moment before flying away again.\n");

    add_item( ({"ruin", "ruins", "rubble", "pile", "piles", "debris"}),
        "There are massive piles of rubble in almost every direction you " +
        "look, the ruined remains of buildings of wood and stone which " +
        "have long since collapsed.\n");
    add_item( ({"wood", "beam", "beams", "wooden beams", "broken beam",
            "broken wood", "broken wooden beam", "broken beams",
            "broken wooden beams"}),
        "There are dozens of broken wooden beams poking out of the " +
        "rubble that surrounds you here.\n");
    add_item( ({"block", "stone block", "blocks", "stone blocks",
            "broken blocks", "broken block", "broken stone block",
            "broken stone blocks"}),
        "There are broken blocks of stone scattered all over the " +
        "gound here, where old buildings of Dol Guldur have yet to be " +
        "restored.\n");
    add_item( ({"stone", "stones"}),
        "Were you trying to look at the broken stone blocks, the city " +
        "wall or the paving stones?\n");
    add_item( ({"building", "buildings", "ruined building",
            "ruined buildings"}),
        "The city of Dol Guldur is filled with ruined buildings, and " +
        "while much of the southwestern quarter has been restored, the " +
        "remnants of old buildings surround you.\n");
    add_item( ({"restored building", "restored buildings", "restored quarter",
            "southwest quarter", "southwestern quarter"}),
        "While much of the city is still in ruins, the southwestern " +
        "quarter of the city has been restored enough to house a " +
        "small army.\n");
}
/*set_items_ruins*/

/*
 * Function name:        set_items_broken
 * Description  :        Items added to broken areas of Dol Guldur when you
 *                       include the line set_items_broken(); 
 *                       Use for all rooms in unrestored areas
 */
void
set_items_broken()
{
    add_item( ({"forest", "mirkwood", "mirkwood forest", "woods"}),
        "The tall black trees of Mirkwood forest are visible nearby, " +
        "their shadowy presence a constant feature in the background as " +
        "they tower above the city walls.\n");
    add_item( ({"wall", "city wall", "walls", "city walls"}),
        "The city walls of Dol Guldur have recently been restored, with " +
        "massive blocks of rough grey stone expertly cut and mortared " +
        "into place.\n");
    add_item( ({"paving", "paving stones", "paved"}),
        "There are no paving stones in the immediate area, at least, " +
        "if there are then they are so broken you cannot identify them.\n");
    add_item( ({"up", "sky"}),
        "Dark clouds drift up to cover the sky above you, obscuring the " 
        + VBFC("light_type") + " from the " + VBFC("day_time") + " " + 
        VBFC("sun_moon") + ".\n");
    add_item( ({"tree", "trees", "black tree", "black trees", "tall tree",
            "tall trees"}),
        "The tall black trees of Mirkwood are visible above the walls " +
        "of Dol Guldur.\n");
    add_item( ({"shadow", "shadows"}),
        "The city of Dol Guldur is seemingly covered in shadows, almost " +
        "as if they are bleeding in from the forest of Mirkwood which " +
        "surrounds the city walls.\n");
    add_item( ({"tower", "broken tower", "ruined tower"}),
        "Rising high above everything else, even the massive trees of " +
        "Mirkwood, is a broken tower of black stone that stands in the " +
        "middle of the city.\n");
    add_item( ({"garbage", "rotting garbage"}),
        "The city of Dol Guldur may have been recently restored, but " +
        "it is quickly becoming a mess. It appears that the inhabitants " +
        "have dropped garbage in almost every nook and corner, creating " +
        "a stench which is almost overpowering at times.\n");
    add_item( ({"ground", "down"}),
        "The ground here is covered in bits of broken stone blocks and " +
        "wooden beams.\n");
    add_item( ({"orc", "orcs", "soldier", "soldiers", "army"}),
        "Very few soldiers have wandered into the ruined parts of Dol " +
        "Guldur, although you have noticed the occasional orc clearing " +
        "away some of the debris.\n");
}
/*set_items_broken*/

/*
 * Function name:        set_herbs
 * Description  :        Makes all herbs in this list available to be found
 *                       when searching for herbs.
 *                       Different numbers provide different lists
 *                       Must add set_herbs_# into plains rooms
 */
void
set_herbs_1()
{
    set_up_herbs(({ HERB_DIR + "hemlock", HERB_DIR + "caraway", 
                    HERB_DIR + "fennel", HERB_DIR + "angurth",
                    HERB_DIR + "tyelka", HERB_DIR + "ungolestel",
                    HERB_DIR + "oregano", HERB_DIR + "athelas",
                     }),
                ({"ground", "field", "grass", "bushes"}), 5);
}
void
set_herbs_2()
{
    set_up_herbs(({ HERB_DIR + "savory", HERB_DIR + "thyme",
                    HERB_DIR + "sage", HERB_DIR + "saffron",
                    HERB_DIR + "tarragon", HERB_DIR + "rosemary",
                    HERB_DIR + "alfirin", HERB_DIR + "holly",
                     }),
                ({"ground", "field", "grass", "bushes"}), 5);
}