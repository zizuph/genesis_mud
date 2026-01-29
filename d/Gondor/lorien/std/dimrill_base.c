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

// void set_items_all();
// void set_items_dimrill();
void set_items_all_dimrill();
void set_items_near_dimrill();  //dimrill desc close enough to see falls
void set_items_far_dimrill();  //dimrill desc from further away
void set_items_mirrormere();
void set_items_mereafar();
void set_items_sunnymere();
void set_items_shadymere();
void set_items_fauna_1();
void set_items_silverlode();
void set_tells_dimrill();   //for dimrill road .gorse scent
void set_tells_mirromere();
void set_herbs_shadymere();
void set_herbs_sunnymere();
void set_items_golden_haze();
// void set_herbs_dimrill();
// void set_herbs_silverlode();
// along the river perhaps a stumble in puddle risk
// void set_herbs_w_road();
// void set_herbs_little_falls();
// void set_herbs_road_forest();
// void set_herbs_forest();
// must add heather and whinto all
int 
do_harvest(string str);
int bark_left = 4;
int trees;

/*
 * Function name:        create_dimrill_room
 * Description  :        Use create_dimrill_room() to make rooms that 
 *                       use information from this file
 */
void 
create_dimrill_room() 
{
}

nomask void 
create_lorien_room() 
{

    create_dimrill_room();

} 

/*
 * Function name:        set_tells_dimrill 
 * Description:          uses add_tell to set dimrill road room tells
 */
void 
set_tells_dimrill()
{ 
/* Function name:      add_tell - used when inheriting 
 *                       "/d/Gondor/common/lib/room_tell";
 * Description  :        Gives some atmosphere by providing some 'sounds'
 *                       in the room in a similar manner to echo
 */   
        //add_item(southern mountains)   
        add_tell("The wildlife noises suddenly go silent.\n");
        add_tell("A dusty, dry wind blows past, leaving you gritty.\n");
        add_tell("The harsh caw of a saturnine crow breaks the silence.\n");
        add_tell("A few small birds fly up as if startled, then eveything " +
            "goes unnaturally silent.\n");
        //add actual birds later
        add_tell("In the distance you can faintly hear the guttural sounds " +
            "of arguing orcs approaching.\n");
        add_tell("A distant thumping march of orcs gradually grows closer.\n");
        add_tell("Some clouds pass in front of the " + VBFC("sun_moon") + 
            ", darkening the " + VBFC("daylight_desc") + ".\n");
        add_tell("Some clouds part in the " + VBFC("daylight_desc") +
            " sky, and a stark " + VBFC("sun_moon") + " peers down " +
            "inauspiciously from above.\n");
        add_tell("A drying breeze blows through, rustling the nearby " +
            "foliage.\n");
        add_tell("Far off in the distance, an eagle soars in the " +
            VBFC("daylight_desc") + " towards the southern mountains.\n");
        add_tell("A hollow sounding wind whistles through the glade.\n");
        add_tell("A dry breeze blows and you catch a faint wiff of " +
        "coconut.\n\tStrange.");
        add_tell("You catch a faint scent of sweet coconut on the breeze.\n");
        add_tell("You catch a faint wiff of coconut on the breeze, " +
        "intermingled with the stench of orc.\n");

/*
 * Function name:        set_tell_time
 * Description  :        Provides time increments between tells
 */
        set_tell_time(random(200) + 70);
}

/*
 * Function name:        set_tells_mirrormere()
 * Description:          uses add_tell to set tells for mirrormere sward
 */
void 
set_tells_mirromere()
{ 
/* Function name:      add_tell - used when inheriting 
 *                       "/d/Gondor/common/lib/room_tell";
 * Description  :        Gives some atmosphere by providing some 'sounds'
 *                       in the room in a similar manner to echo
 */   
        //add_item(southern mountains)   
        add_tell("The wildlife noises suddenly go silent.\n");
        add_tell("A wind blows past, bringing a gust of humid air " +
            "in from over the mere.\n");
        add_tell("The harsh caw of a saturnine crow breaks the silence.\n");
        add_tell("A few small birds fly up as if startled, then eveything " +
            "goes unnaturally silent.\n");
        //add actual birds later
        add_tell("A bird hops along in the grass, looking for worms.\n");
        add_tell("Crickets chirp in the nearby grass.\n");
        add_tell("The chirping crickets all fall silent at once.\n");
        add_tell("In the distance you can faintly hear the guttural sounds " +
            "of arguing orcs passing on the roads.\n");
        add_tell("A distant thumping march of orcs gradually grows closer.\n");
        add_tell("Some clouds pass in front of the " + VBFC("sun_moon") + 
            ", darkening the " + VBFC("daylight_desc") + ".\n");
        add_tell("Some clouds part in the " + VBFC("daylight_desc") +
            " sky, and a stark " + VBFC("sun_moon") + " peers down " +
            "inauspiciously from above.\n");
        add_tell("A cool breeze of fresh air blows through, rustling the " +
            "nearby foliage.\n");
        add_tell("Far off in the distance, an eagle soars in the " +
            VBFC("daylight_desc") + " towards the southern mountains.\n");
        add_tell("The " +VBFC("daylight_desc") + " bounces off the " +
            "surface of the mere.\n");


/*
 * Function name:        set_tell_time
 * Description  :        Provides time increments between tells
 */
        set_tell_time(random(200) + 70);
}

/*
 * Function name:        set_tells_silverlode_road
 * Description:          uses add_tell to set dimrill rooms along Silverlode
 */
void 
set_tells_silverlode_road()
{ 
/* Function name:      add_tell - used when inheriting 
 *                       "/d/Gondor/common/lib/room_tell";
 * Description  :        Gives some atmosphere by providing some 'sounds'
 *                       in the room in a similar manner to echo
 */   
        //add_item(southern mountains)   
        add_tell("The wildlife noises suddenly go silent.\n");
        add_tell("A cool wind blows past, bringing a gust of chilly air " +
            "in from over the stream.\n");
        add_tell("The harsh caw of a saturnine crow breaks the silence.\n");
        add_tell("A few small birds fly up as if startled, then eveything " +
            "goes unnaturally silent.\n");
        //add actual birds later
        add_tell("The stream gurgles and crashes against some rocks.\n");
        add_tell("In the distance you can faintly hear the guttural sounds " +
            "of arguing orcs approaching.\n");
        add_tell("A distant thumping march of orcs gradually grows closer.\n");
        add_tell("Some clouds pass in front of the " + VBFC("sun_moon") + 
            ", darkening the " + VBFC("daylight_desc") + ".\n");
        add_tell("Some clouds part in the " + VBFC("daylight_desc") +
            " sky, and a stark " + VBFC("sun_moon") + " peers down " +
            "inauspiciously from above.\n");
        add_tell("A cool breeze of fresh air blows through, rustling the " +
            "nearby foliage.\n");
        add_tell("Far off in the distance, an eagle soars in the " +
            VBFC("daylight_desc") + " towards the southern mountains.\n");
        add_tell("The " +VBFC("daylight_desc") + " bounces off the " +
            "stream as it gurgles past.\n");
        add_tell("A cold-water fish make a splash in the stream.\n");
        add_tell("The water of the stream spashes against some rocks!\n");
        add_tell("The stream gurgles and crashes down the rocky channel.\n");
        add_tell("The water of the stream surging and foaming, turns " +
            "white over some rapids as it crashes down the channel.\n");
        add_tell("A hollow sounding wind whistles through the trees.\n");
        add_tell("There is a flicker of movement in the trees at the edge " +
        "of the stream.\n");
        add_tell("For a second something moves in the " + VBFC("light_type") + 
        ", casting the flicker of an elvish shadow under a tree alongside " +
        "the road.\n\t When you look again, there is nothing there.\n");

/*
 * Function name:        set_tell_time
 * Description  :        Provides time increments between tells
 */
        set_tell_time(random(150) + 70);
}

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

/*
 * Function name:        set_items_dimrilldale
 * Description  :        Items added to  rooms when you include the line
 *                       set_items_dimrilldale(); 
 *                       Use for close to Dimril Dale and Mirrormere at 
 *                       road9.c start to use 
 */
void
set_items_all_dimrill()
{
    add_item( ({"mountains", "mountain"}),
        "which mountains do you want to look at? The northern mountains?" +
        "Or the mountains to the south?\n");
    add_item( ({"northern mountains", "north mountains", 
        "mountains to the north"}), 
        "Three snow capped peaks of the great mountain range rise up " +
        "majestically to the north. It is a breathtaking view. Celebdil " +
        "looms to the northwest, while the northeast is dominated by " +
        "Fanuidhol, and the third peak, Caradhras rises up between and " +
        "behind the other two, forming an imposing guard at their backs.\n");
    add_item( ({"southern mountains", "south mountains",
        "mountains to the south", "misty mountains"}), 
        "To the south, the Misty Mountains recede as far as the eye " +
        "can see.\n");

    add_item( ({"east gate", "east gates", "great gate", "great gates",
            "great east gate", "great east gates", "gate", "gates", 
            "dimrill gate", "dimrill gates"}),
        "The Dimrill Gate, to Moria looms huge and foreboding in the " +
        "northwest. Once a grand and ostentatious display of the " +
        "craftsmanship and riches of the dwarves, the dark glistening " +
        "stone of this legendary city, is now equally foreboding as it " +
        "once was great. The shining stone gates have been torn asunder. " +
        "And the gaping black opening peers out, over Dimrill Dale and " +
        "Mirrormere, like a dark evil eye from the pass between Celebdil " +
        "and Caradhras. Its dark presence sends an uneasy feeling over " +
        "the valley.\n");
    add_item( ({"fanuidhol", "bundushathur", "cloudyhead"}),
        "It is a grand mountain whose snow-capped peak disappears into the " +
        "clouds.\n");
    add_item( ({"celebdil", "zirakzigil", "silvertine"}),
        "This is the southern and western most of the three mountains. It " +
        "is a little smaller than the other two, and it's peak rises up " +
        "like a silver spike into the sky.\n");
    add_item( ({"sky", "night sky", "midnight sky", "morning sky",
        "mid-day sky", "mid-morning sky", "afternoon sky", 
        "mid-afternoon sky"}), " " + VBFC("sky_desc") + " \n");
    add_item( ({"cloud", "clouds"}), "Which clouds are you trying to see? " + 
        "Clouds around the mountain peak? Or do you want to look for " +
        "clouds in the sky above?\n");
    //add_item( ({"
    // add clue in one of clouds to durins quest  
    add_item( ({"valley", "dale", "dimrill dale"}), 
        "The big open valley of Dimrill Dale sprawls down from the " +
        "mountains to the northwest.  Near their feet the valley narrows " +
        "to a high sided vale, wherein can be seen the gleam of a large " +
        "body of water.\n");
    add_item( ({"feet", "mountain feet", "foot", "mountain foot", 
            "feet of the mountain", "foot of the mountain",
            "feet of the mountains"}),
        "The feet of the mountains are shrouded in mist./n");
}

/*
 * Function name:        set_items_near_dimrill
 * Description  :        Items added to rooms when you include the line
 *                       set_items_near_dimrill(); 
 *                       Use for rooms where the Dimrill Stair falls can
 *                       be seen from close. DO NOT USE with:
 *                       set_items_far_dimrill
 */
void
set_items_near_dimrill()
{
    add_item( ({"caradhras", "azanulbizar", "redhorn", "barazinbar"}),
        "This immense mountain rises up, giving almost malevolent feeling " +
        "of domination, as it's hulking mass reaches up to a snow-capped " +
        "peak. The falls of Dimrill Stair, make their cascade down its " +
        "front.\n");
    add_item( ({"glen", "vale", "narrow valley", "dark vale", "steep valley"}),
        "The narrow shadow-filled valley runs up between the arms of " +
        "Celebdil and Fanuidhol, towards Caradhras. At the valley-head a " +
        "torrent of water flows down like white lace, over an endless " +
        "ladder of short falls. The falls throw up fine mist shrouding " +
        "the feet of the great mountains.\n");
    add_item( ({"falls", "waterfalls", "waterfall", "dimrill stair", 
            "dimrill stairs",}), 
        "The falls form a ladder rolling down the mountain with their lacey " +
        "foam. Along side the falls runs a path, stretching its way up the " +
        "side of Carahdras.\n");
    add_item( ({"path"}),
        "The path is a naturally occurring stone stair that follows the " +
        "tiered course of the falls. Once improved as a grand path, it is " +
        "now cracked and has fallen into disrepair.\n");
    add_item( ({"mist"}),
        "The mist rises up from the fine spray that becomes airborne, as " +
        "flowing water crashes against the rocks of the falls.\n");  
    add_item( ({"foam"}),
        "It is the typical white water that occurs as flowing water crashes " +
        "over the rocks that form the falls.\n");
    add_item( ({"stair", "stairs"}),
        "The stairs mimic the path of the water, cascading in strides, down " +
        "the mountain. Upon a closer look, it appears that the stairs were " +
        "once grand, the way broad and easy to travel. Now some are " +
        "cracked, possibly as if they had been intentionally damaged, and " +
        "large trees fallen trees and other obstacles block the path in " +
        "places.\n");
    add_item( ({"fallen trees", "trees"}),
        "The are huge long dead trees that have either fallen or been " +
        "placed, in the path along Dimrill Stair.\n");
    add_item( ({"obstacles"}),
        "The obstacles the are made up of fallen trees, boulders and the " +
        "like.\n");
    add_item( ({"boulders"}),
        "There are some on the path of Dimrill Stair in places, barring the " +
        "way.\n");
}

/*
 * Function name:        set_items_far_dimrill
 * Description  :        Items added to rooms when you include the line
 *                       set_items_far_dimrill(); 
 *                       Use for rooms where the Dimrill Dale can be seen
 *                       but is too far to make out details of the 
 *                       Dimrill Stair Falls. DO NOT USE with:
 *                       set_items_near_dimrill
 */
void
set_items_far_dimrill()
{
    add_item( ({"caradhras", "azanulbizar", "redhorn", "barazinbar"}),
        "This immense mountain rises up, giving almost malevolent feeling " +
        "of domination, as it's hulking mass reaches up to a snow-capped " +
        "peak.\n");
    add_item( ({"glen", "vale", "narrow valley", "steep valey"}),
        "In the distance, " +
        "the narrow shadow-filled valley runs up between the arms of " +
        "Celebdil and Fanuidhol, towards Caradhras. The feet of the great " +
        "mountains are shrouded in mist.\n");
    //add_item ( ({"dimrill dale"}), "xxx\n");
}

/*
 * Function name:        set_items_fauna_1
 * Description  :        Items added to rooms when you include the line
 *                       set_items_fauna_1(); 
 *                       This function is called by two functions below 
 *                       so please leave it above set_items_mereafar()
 *                       and don't include it if you include that.
 */void
set_items_fauna_1()
{
    add_item( ("heather"),
        "The heather lends a unique beauty to the countryside with its " +
        "pinks and purples that contrast with the bright yellow flowers of " +
        "the nearby gorse. Bits of green show from below the flowers.\n");
    add_item( ({"pinks", "purples", "green", "greens", "bits of green", 
        "bits", "pink", "purple"}),
        "You take a closer look at the heather. Long clusters of little " +
        "pink flowers, are set on purple stems, with closely set clusters " +
        "of little leaves that grow off the stems like light-green shoots.\n");   
    add_item( ({"flower", "flowers"}),
        "Which flowers do you want to look at? The pink heather flowers? " +
        "or the yellow gorse flowers?\n");
    add_item( ({"pink flowers", "pink flower", "heather flowers", 
        "heather flower"}),
        "The closed flowers of the heather are are conical, like a tight " +
        "bud. The ones that are open look like a bell made up of pretty " +
        "pink petals.\n"); 
    add_item( ({"stem" , "stems"}),
        "Which stems do you want to look at?  The heather stems? or " +
        "the gorse stems?\n");
    add_item( ({"heather stems", "heather stem", "stems of heather",
        "stems of the heather"}),
        "The stems are a deep purple and lend much color to the heather " +
        "bushes, especially as combined with the pink flowers growing on " +
        "top. Clusters of small green leaves growing out in shoots " +
        "underneath.\n");
    add_item( ({"leaves", "leaf"}),
        "Which leaves do you want to look at?  The heather leaves? or the " +
        "gorse leaves?\n");
    add_item( ({"heather leaves", "heather leaf"}),
        "The leaves of the heather are small and compacted closely " +
        "together in groups to form long sprigs that grow out from the " +
        "purple stems.\n");
    add_item( ({"bush", "bushes"}),
        "Which bushes do you want to look at? The Heather bushes? or the " +
        "whin?\n");
    add_item( ({"whin" , "whin bushes", "whin bush"}),
        "The whin are thorny bushes, mostly gorse.\n");  
    add_item( ({"gorse", "gorse bush", "gorse bushes"}),
        "The gorse shrubs are covered in an explosion of yellow flowers. " +
        "The foliage, if you can call it that, is more like creased spines " +
        "than regular leaves. The spines are about an inch long and jut " +
        "out threateningly all along the branching stems.\n");
    add_item( ({"yellow flowers", "yellow gorse flowers", "gorse flowers",
        "yellow flower", "yellow gorse flower", "gorse flower"}),
        "On closer look what seemed to be big bright yellow flowers are " +
        "actually clusters of many smaller flowers grouped together in " +
        "clumps all over the spiky bushes. The small flowers have five " +
        "bright petals and are similar in shape to pea flowers.\n"); 
    add_item( ({"spikes", "spike", "spine", "spines", "thorn", "thorns",
        "gorse leaves", "gorse leaf", "spine"}), 
        "It is hard to tell if these are leaves or thorns, because they " +
        "are so spiky. The bush appears to be an evergreen and the " +
        "spikes look dangerous.\n");
    add_item( ({"gorse stems", "whin stems", "branching stems", "woody stems",
        "gorse stem", "whin stem", "branching stem", "woody stem"}),
        "The gorse stems are woody and branching, like long arms loaded " +
        "with flowers and spikes, giving a wild untamed look to the " +
        "countryside.\n");
    add_item( ({"evergreen", "evergreens"}),
        "Much of what grows here is of the evergreen species: the heather " +
        "and gorse bushes, as well as many of the trees.\n");
//add_item clusters

    add_tell("You catch a faint wiff of coconut.\n");
/*
 * Function name:        set_tell_time
 * Description  :        Provides time increments between tells
 */
    set_tell_time(random(150) + 70);
}

/*
 * Function name:        set_items_mirrormere
 * Description  :        Items added to rooms when you include the line
 *                       set_items_mirrormere(); 
 *                       Use for rooms on the banks of Mirromere
 */
void
set_items_mirrormere()
{
    add_item( ({"mirrormere", "mere", "lake", "pond"}),
        "The shallow waters of the mere are as still and smooth as glass. " +
        "It is a magnificent sight. Unbroken by a single ripple the " +
        "water's surface is a perfect reflection of the the sky above. " +
        "A sward of green surrounds the pond, shelving down to the " +
        "unbroken surface. The mere is long and oval shaped, It runs, " +
        "like the head of a spear thrust through the northern glen, " +
        "falling deeper and deeper into shadow as it reaches toward " +
        "the back of the steep valley between Celebhil and Fanuidhol. " + 
        "The pond terminates in a point, at the foot of Carahdras.\n");
    add_item( ({"water", "waters", "surface", "reflection"}),
        "You look at the surface of the pond, and see the sky reflected " +
        "there. " + VBFC("mirror_desc") + "\n");
    add_item( ("road"), "On a grassy sward next to the mere. The road lies " +
        "to the south.\n");
//add sward
    add_item( ("sward"), "Oh rats, I havent added the sward desc yet.\n");
}

/*
 * Function name:        set_items_sunnymere
 * Description  :        Items added to rooms when you include the line
 *                       set_items_sunnymere(); 
 *                       Use for all southern rooms on the banks of  
 *                       Mirrormere
 */
void
set_items_sunnymere()
{
    // placeholder
}

/*
 * Function name:        set_items_shadymere
 * Description  :        Items added to rooms when you include the line
 *                       set_items_shadymere(); 
 *                       Use for all northern rooms on the banks of  
 *                       Mirrormere
 */
void
set_items_shadymere()
{
    // placeholder
}

/*
 * Function name:        set_items_mereafar
 * Description  :        Items added to rooms when you include the line
 *                       set_items_mereafar(); 
 *                       Use for road rooms where Mirrormere can be seen 
 *                       from afar.
 */
void
set_items_mereafar()
{
    set_items_fauna_1();
    add_item( ({"mirrormere", "mere", "lake", "body of water", "surface",
        "pond"}),
        "The mere is long and oval shaped, running like the head of a " +
        "spear, thrust through the narrow and deep northern glen. It runs " +
        "between Celebhil and Fanuidhol, terminating in a point, " +
        "at the foot of Carahdras.\n");
    add_item( ("road"), "The road winds its way thru the trees, among " +
        "clumps of heather and whin that grow here and there. To the north " +
        "there opens a dark vale, where lies a mere. To the northwest " +
        "lies a great mountain where in the distance the Great Gates of " +
        "Moria can be seen. To the east are low lands.\n");
    add_item( ({"low lands", "lands", "golden haze", "distant golden haze",
        "haze"}), "It is too far way to see much of what lies to the east " +
        "other than a distant golden haze.\n"); 
    // added here because we cant see to the east from within the steep valley
    //  Heather and whin are added to set_items_fauna_1() called above
}


/*
 * Function name:        set_items_silverlode
 * Description  :        Items added to rooms when you include the lines
 *                       set_items_silverlode(); 
 *                       Use for the rooms beside the river Silverlode
 */
void
set_items_silverlode()
{
    add_item( ({"river", "stream", "water", "waters", "silverlode", 
        "celebrant", "silverlode river", "celebrant river"}),
        "The river flows to  north of the road. Deep and quiet the water " +
        "moves quickly along. On the far bank of the stream the forest " +
        "continues on towards the northern mountains.\n");
    // add_item( ({"northern mountains"}), );  
    add_item( ({"far bank", "north bank", "northern bank"}),
        "This is the southern edge of the forest which spreads northwards " +
        "towards XXXX .\n");
    add_item( ({"bank", "banks", "riverbank"}), "Which bank do you want to " +
        "look at? The near bank, or the far bank?\n");  
    add_item( ({"near bank", "south bank", "southern bank"}), 
        "The riverbank is covered in grass, with the occasional boulder " +
        "here and there. It slopes downward towards the shore at the " +
        "water's edge.\n");
    add_item( ({"shore", "edge", "water's edge", "waters edge", 
        "water edge"}),
        "Really not much to see from this distance.\n");
    //climb bank
    //add boulder/s

}

/*
 * Function name:        set_items_golden_haze
 * Description  :        Items added to rooms when you include the lines
 *                       set_items_golden_haze(); 
 *                       Use for the rooms beside the river Silverlode
 *                       in which LL forest is distant
 */
void
set_items_golden_haze()
{
    add_item( ({"golden horizon", "horizon", "haze", "golden haze"}),
        "The river winds it's way off into the distance into the flat " +
        "lands there until it disappears into a golden haze of softness, " +
        "whose hues blend and shift from golden ground into the more " +
        "translucent hues of a distant sky lit with golden light.\n");
    add_item( ({"distant sky", "hues", "golden light", "light"}),
        " You can't make out more detail from here.\n");
    add_item( ({"flat lands", "lands"}), 
        "The flat lands disappear into golden haze.\n");
}

/*
 * Function name:        set_herbs
 * Description  :        Makes all herbs in this list available to be found
 *                       when searching for herbs.
 *                       Different numbers provide different lists
 *                       Must add set_herbs_areaname into rooms
 */
/* use set_herbs_sunnymere(); for the well lit areas of Mirrormere */
void
set_herbs_sunnymere()
{
    set_up_herbs( ({EARTHSEA_HERB_DIR + "clover3", 
                    EARTHSEA_HERB_DIR + "w_hallow",
                    EARTHSEA_HERB_DIR + "morel",
                    EARTHSEA_HERB_DIR + "blue_gentian",
                    EARTHSEA_HERB_DIR + "moly",
                    EARTHSEA_HERB_DIR + "morning_glory",
                    KRYNN_HERB_DIR + "asparagus",
                    KRYNN_HERB_DIR + "crocus",
                    KRYNN_HERB_DIR + "veronica",
                    SHIRE_HERB_DIR + "tansy",
                }),
                    //add blung to sides and lothore & pawnrose to DS

                     ({"ground", "field"}), 5);
}

/* Use set_herbs_shadymere(); for dark areas of Mirrormere */
void
set_herbs_shadymere() 
{
    set_up_herbs( ({ HERB_DIR + "curugwath",
                    AVENIR_HERB_DIR + "fordinfa",
                    AVENIR_HERB_DIR + "narcissus",
                    EARTHSEA_HERB_DIR + "clover3", 
                    EARTHSEA_HERB_DIR + "morning_glory",
                    KRYNN_HERB_DIR + "asparagus",
                    KRYNN_HERB_DIR + "brown_slime",
                    KRYNN_HERB_DIR + "skullcap",
                    SHIRE_HERB_DIR + "columbine",
                }),
                ({"ground", "field"}), 5);
}

void
set_herbs_shadymere2() 
{
    set_up_herbs( ({ HERB_DIR + "curugwath",
                    HERB_DIR + "blung",
                    AVENIR_HERB_DIR + "fordinfa",
                    AVENIR_HERB_DIR + "narcissus",
                    EARTHSEA_HERB_DIR + "clover3", 
                    EARTHSEA_HERB_DIR + "morning_glory",
                    KRYNN_HERB_DIR + "asparagus",
                    KRYNN_HERB_DIR + "brown_slime",
                    KRYNN_HERB_DIR + "skullcap",
                    SHIRE_HERB_DIR + "columbine",
                    
                }),
                ({"ground", "field"}), 5);
}                  

/*
 * Function name:        add_trees
 * Description  :        Allows for climbable trees to be added to a room
 */
public void
add_trees(int value)
{
    trees = value;
}
/* add_trees */

/*
 * Function name:       dimrill_climb_tree
 * Description  :        This code lets people hide in trees by adding a tree
 *                       shadow.
 * Thanks:               This code was created by Carnak
 */
public int
dimrill_climb_tree(string str)
{
    object shadow;
    
    if (!strlen(str) )
    {
        notify_fail("What did you want to climb? A tree?\n");
        return 0;
    }
    if (!parse_command(str, ({}), 
        " [up] [on] [the] [in] [a] 'tree' / 'trees'") &&
        !this_player()->query_tree_shadow() )
    {
        notify_fail("Are you trying to climb up a tree?\n");
        return 0;
    }
    
    if (this_player()->query_tree_shadow() )
    {
        if (str == "down")
        {
            this_player()->climb_down_tree();
            return 1;
        }
        
        notify_fail("You are already in the tree, perhaps you would " +
        "like to climb down?\n");
        return 0;
    }
    
    setuid();
    seteuid(getuid() );
// IMPORTANT  change below to add our own tree shadow   
    if ( !(shadow = clone_object(AN_OBJ_DIR + "tree_shadow.c") ) )
    {
        notify_fail("You were unable to climb the tree.\n");
        return 0;
    }
    
    write("You manage to find a nearby tree to climb and scramble up into " +
          "the branches.\n");
    SAYBB(" climbs up a nearby tree.\n");
    
    shadow->shadow_me(this_player() );
    shadow->add_present_objects();
    
    return 1;
}
/* wild_climb_tree */

/*
 * Function name:        climb_function
 * Description  :        Initiates the climbing options in rooms
 */
public int
climb_function(string str)
{
    return 0;
}
/* climb_function */

/*
 * Function name:        do_climb
 * Description  :        Allows the player to climb things
 * Returns      :        Climbable Trees if present in the room
 */
public int
do_climb(string str)
{
    if (trees)
        if (dimrill_climb_tree(str) )
            return 1;

    notify_fail("You do not seem to be able to climb that here.\n");

    return climb_function(str);
}
/* do_climb */

/*
 * Function name:        do_harvest
 * Description  :        Provides a chance for a mortal harvest bark from
 *                       birch trees. The bark has XXX protperties
 *                        /d/Gondor/lorien/obj/birchbark.c
 * Returns      :        int 0 - Prompt for proper syntax
 *                       int 1 - Returns the emote
 * Thanks       :        Varian via Mercade via Mirandus
 */
public int
do_harvest(string str)
{
    object bark;
    notify_fail("Harvest what? Bark from a Birch tree?\n");
    
    if ( (str != "bark" && str != "barks" && str != "birch" &&
        str != "tree") )
        return 0;
    
    if (bark_left < 1)
        {
            write("It seems like all the bark has been stripped! If " +
                "you tried to take anymore it would probably kill the " +
                "tree!!\n");
            // maybe later add here allowance to kill the tree               
            return 1;
        }
            
            setuid();
            seteuid(getuid() );
            bark = clone_object(LORIEN_DIR_OBJ + "birchbark");
            /* add birchbark.c-- undecided as to have this a quest item with 
             * only uses such as have it sewn into items or to add it as an 
             * herb but with those additional uses.
             */
            bark->move(this_player(), 1);
            write("You harvest some bark from the birch tree.\n");
            // fail for strip or pull bark-- also more than one tree from 
            // the x number tree

            say(QCTNAME(TP) + " strips some bark from a birch tree.\n");
            // which tree?
            bark_left = bark_left -1;

        return 1;
}
/* do_harvest */

public void
init()
{
    ::init();

    add_action("do_harvest", "harvest");
    add_action("do_harvest", "strip");
    add_action("do_harvest", "peel");
    add_action("do_climb", "climb");
}
