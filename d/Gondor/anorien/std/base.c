/*
 * Base room for Anorien
 *
 * Varian - 2016
 *
 * Added some Angurth herbs into the fields as changes to the
 * magic system mean that the mages need more of this herb
 * available. - Varian - Oct 2020
 *
 */

#include "../defs.h"

inherit ANORIEN_STD_DIR + "room";
inherit "/d/Gondor/common/lib/herbsearch";
inherit "/d/Gondor/common/lib/room_tell";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <macros.h>
#include "/d/Gondor/anorien/std/descriptors.c"

void set_items_plains();
void set_items_cairandros();
void set_items_anduin();
void set_items_entwash();
void set_items_road();
void set_items_stream();
void set_items_city();
void set_herbs_1();
void set_herbs_2();
void set_herbs_3();
void set_herbs_4();
void set_herbs_5();
void set_herbs_6();
void set_herbs_7();
void set_herbs_8();
void set_herbs_9();

int do_pick(string str);
int flowers_left = 10;
int trees;

/*
 * Function name:        create_plains_room
 * Description  :        Use create_plains_room() to make wild rooms that use
 *                       information from this file
 */
void create_plains_room() 
{
}

nomask void create_anorien_room() 
{

    create_plains_room();
/*
 * Function name:        add_tell - used when inheriting 
 *                       "/d/Gondor/common/lib/room_tell";
 * Description  :        Gives some atmosphere by providing some 'sounds'
 *                       in the room in a similar manner to echo
 */        
        add_tell("Several clouds pass in front of the " + 
            VBFC("sun_moon") + ", temporarily blocking out the " +
            VBFC("light_type") + " that shines down upon these fields.\n");
        add_tell("The " + VBFC("daylight_desc") + " sparkles down upon the " +
            "river in the distance, dancing across the surface.\n");
        add_tell("As some clouds part in the sky, bright " + VBFC("light_type") 
            + " from the " + VBFC("day_desc") + " " + VBFC("sun_moon") + 
            " spreads out across the grassy fields.\n");
        add_tell("A gentle breeze ripples through the tall grasses, " +
            "causing them to bend and sway with each gust of wind.\n");
        add_tell("Far off to the south, you see an eagle soaring in the " + 
            VBFC("daylight_desc") + " around jagged peaks of the White " +
            "Mountains in the distance.\n");
        add_tell("A small flock of birds chase each other, swooping and " +
            "diving all across the grassy fields.\n");
        add_tell("A gentle breeze ripples through the tall grasses, " +
            "causing them to bend and sway with each gust.\n");
        add_tell("Far to the southwest, you see an eagle soaring in the " + 
            VBFC("daylight_desc") + " around jagged peaks of the White " +
            "Mountains in the distance.\n");
        add_tell("A large flock of birds chase each other, swooping and " +
            "diving all across the fields.\n");
        add_tell("A gentle breeze ripples through the tall grasses, " +
            "causing them to bend and sway with each gust.\n");
        add_tell("Off in the distance, you see what appears to be a " +
            "bear wandering across the fields.\n");
        add_tell("A horde of tiny flies start buzzing around your face, " +
            "biting at your bare flesh.\n");
        add_tell("A horde of tiny flies start buzzing around your face, " +
            "biting at your bare flesh.\n");
        add_tell("A horde of tiny flies start buzzing around your face, " +
            "biting at your bare flesh.\n");
        add_tell("A brightly coloured dragonfly zips past, chasing down " +
            "some of the insects for a quick meal.\n");
        add_tell("A brightly coloured dragonfly zips past, chasing down " +
            "some of the insects for a quick meal.\n");
        add_tell("A yellow snake swiftly slithers past, quickly becoming " +
            "lost in the tall grasses.\n");
        add_tell("A green snake swiftly slithers past, quickly becoming " +
            "lost in the tall grasses.\n");
        add_tell("A flight of swallows dance in the air before taking " +
            "shelter in a nearby grove of fir trees.\n");
        add_tell("A small flight of swallows dance in the air before taking " +
            "shelter in a nearby grove of elm trees.\n");
        add_tell("A small flight of swallows dance in the air before taking " +
            "shelter in a nearby grove of oak trees.\n");
        add_tell("Dozens of tiny butterflies flutter across " +
            "the grassy fields in a parade of bright colours.\n");
        add_tell("A handful of tiny butterflies flutter across " +
            "the grassy fields in a parade of bright colours.\n");
        add_tell("A couple of tiny butterflies flutter across " +
            "the grassy fields in a parade of bright colours.\n");
        add_tell("A large deer, grazing in the fields looks up at you and " +
            "bounds away into a grove of oak trees.\n");
        add_tell("A young buck, grazing in the fields looks up at you and " +
            "bounds away into a grove of elm trees.\n");
        add_tell("The droning chirp of crickets echoes across the fields.\n");
/*
 * Function name:        set_tell_time
 * Description  :        Provides time increments between tells
 */
        set_tell_time(random(400) + 70);
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
 * Function name:        set_items_plains
 * Description  :        Items added to plains rooms when you include the line
 *                       set_items_plains(); 
 *                       Use for all plains rooms in Anorien
 */
void
set_items_plains()
{
    add_item(({"rivers"}),
        "There are two rivers nearby, the Entwash which slowly seeps " +
        "across the northern border of Anorien, and the Anduin which " +
        "cuts across the land just east of here.\n");
    add_item(({"river", "anduin", "bank", "banks", "waters", "great river"}),
        "Nearby, the grey waters of the mighty Anduin river rush past " +
        "as it carves a path through Anorien, running southwards through " +
        "the land of Gondor towards the sea.\n");
    add_item(({"grasses", "grass", "ground", "field", "fields", "green grass"}),
        "The ground here is full of a tall, green grass which bends gently " +
        "in the wind, swaying back and forth. Stretching off into the " +
        "distance, the fields are filled with endless insects which buzz " +
        "around everywhere, often around the large clusters of wildflowers " +
        "which hide in the grass.\n");
    add_item(({"flower", "flowers", "wildflower", "wildflowers"}),
        "Scattered across the fields, brilliant hues of red, purple, blue " +
        "and orange are visible where clusters of wildflowers are nestled " +
        "in the tall green grass.\n");
    add_item(({"insect", "insects"}),
        "The wide grassy fields are filled with the endless, buzzing drone " +
        "of insects. Most of the insects seem to be of the biting kind, " +
        "although you do see a number of bees hovering around the " +
        "wildflowers. Despite everything you do to shoo them away, it " +
        "does feel like there is an endless cloud of bitemes hovering " +
        "around your head.\n");
    add_item(({"biteme","bitemes", "fly", "flies"}),
        "These annoying little insects seem to be overjoyed that you, their " +
        "most recent meal, have arrived. No matter how much you swat at " +
        "them, there are still dozens more hovering around your head and " +
        "biting at your skin.\n");
    add_item(({"eagle","eagles"}),
        "Far off to the west, against the backdrop of Ered Nimrais, the " +
        "White Mountains, you occassionally see an eagle circling high in " +
        "the air.\n");
    add_item(({"swallow","swallows"}),
        "Every once in a while, you can see a small group of swallows " +
        "dipping and diving across the waters of the great river.\n");
    add_item(({"bird","birds"}),
        "This land is full of life, including hundreds of birds which " +
        "keep the air alive with song, and fly from one grove of trees " +
        "to another in small flocks.\n");
    add_item(({"dragonfly","dragonflies"}),
        "Dozens of dragonflies are zipping about, chasing down their " +
        "meals of the small, bothersome insects that constantly seem " +
        "to be in your face.\n");
    add_item(({"crickets","cricket", "grasshopper", "grasshoppers"}),
        "The constant chipring of crickets and grasshoppers drones in " +
        "your ears as you pass through these fields. You occasionally " +
        "spot some as they jump and fly around in the grass.\n");
    add_item(({"butterfly","butterflies"}),
        "Fluttering through the air, pushed along by the gentle breezes, " +
        "hundreds of butterflies drift across the fields in a dazzling " +
        "display of colours on parade.\n");
    add_item(({"gondor", "ithilien"}),
        "The river Anduin flows south from here, cutting through Ithilien " +
        "and the land of Gondor before it empties out into the sea.\n");
    add_item(({"fir", "fir trees", "evergreens", "firs"}),
        "Scattered around the land, several groups of fir trees have " +
        "sprouted up into small groves. Stretching tall up into the open " +
        "air, these evergreens could provide some shade and shelter from " +
        "the elements.\n");
    add_item(({"tree","trees"}),
        "Dozens of wide groves of trees are scattered around the fields " +
        "here, enriching the land with their lush green growth.\n");
    add_item(({"oak", "oaks"}),
        "Reaching high into the sky, you can see the tops of some mighty " +
        "oak trees at the heart of every grove nearby.\n");
    add_item(({"elm", "elms"}),
        "Tall and slender, dozens of elm trees cast their shade across " +
        "the fields of Anorien in small groves.\n");
    add_item(({"fir", "firs"}),
        "These evergreens cluster together in small groves that dot the " +
        "surrounding fields.\n");
    add_item(({"grove","groves"}),
        "There are dozens of groves of trees scattered around Anorien. " +
        "Tall elms, wide firs and even mighty oaks gather in small " +
        "clusters, providing some shelter and shade in these fields.\n");
    add_item(({"fish","silver fish", "brown fish"}),
        "You cannot see any fish right at this moment, but occasionally " +
        "you will see one jumping in the Anduin river.\n");
    add_item(({"snake","snakes", "yellow snake", "green snake"}),
        "Every now and then, you will spot a small grass snake as it " +
        "slithers across the fields in search of a meal.\n");
    add_item(({"bear","bears"}),
        "You cannot see a bear right at this moment, but you suspect that " +
        "they often prowl near the Anduin, living amongst the dozens of " +
        "groves of trees to be found nearby.\n");
    add_item(({"deer","stag", "stags"}),
        "Ocassionaly you will see some deer grazing in the fields, yet any " +
        "time they feel you get too close, they jump up and dash away " +
        "into a grove of trees.\n");
    add_item(({"mountains", "white mountains", "ered nimrais"}),
        "Off in the distance to the south and west, the rugged peaks " +
        "of the White Mountains claw at the empty sky above.\n");
    add_item(({"rohan", "horse lords"}),
        "Rohan, the land of the horse lords, lays far off in the distance " +
        "to the west across the Mering Stream where the Eastfold begins.\n");
    add_item(({"west", "western horizon"}),
        "The fields of Anorien stretch far to the west, until they meet " +
        "the Eastfold at the Mering Stream and enter the lands of Rohan.\n");
    add_item(({"southwest", "southwestern horizon"}),
        "The fields of Anorien stretch far to the southwest, rolling over " +
        "hills all the way up to the snow-capped peaks of the White " +
        "Mountains.\n");
    add_item(({"northwest", "northwestern horizon"}),
        "The grey waters of the Entwash flow sluggishly through the marshy " +
        "lands which dominate the northwestern horizon.\n");
    add_item(({"north", "northern horizon"}),
        "The grey waters of the Entwash flow sluggishly through the marshy " +
        "lands which dominate the northwestern horizon.\n");
    add_item(({"east", "eastern horizon"}),
        "The fields of Anorien stretch far to the east, until they meet " +
        "the wide rushing waters of the mighty Anduin River.\n");
    add_item(({"southeast", "southeastern horizon"}),
        "The fields of Anorien stretch far to the southeast, rolling over " +
        "hills until they reach the Anduin River and the contested lands " +
        "of Ithilien.\n");
    add_item(({"northeast", "northeastern horizon"}),
        "The grey waters of the Entwash flow sluggishly through the marshy " +
        "lands which dominate the northeastern horizon before they empty " +
        "out into the rushing waters of the Anduin.\n");
    add_item(({"south", "southern horizon"}),
        "The tall jagged peaks of the White Mountains dominate the " +
        "southern horizon, running from west to east, before ending at " +
        "the Tower of Guard, Minas Tirith.\n");
    add_item(({"horizon", "horizons"}),
        "There is a lot of land around you out here, which horizon did " +
        "you want to examine?\n");
    add_item(({"minas tirith", "tower", "tower of guard","citadel"}),
        "The mighty fortress of Minas Tirith stands tall at the eastern " +
        "edge of the White Mountains.\n");
    add_item(({"stream", "mering stream"}),
        "The Mering Stream stands as the western border of Gondor, as " +
        "the Eastfold and the rest of Rohan stands on the other side.\n");
    add_item(({"mouth","mouths","entwash","mouths of the entwash"}),
        "The sluggish waters of the Entwash crawl along the northern " +
        "edge of these plains before emptying out into the Anduin.\n");
    add_item(({"up", "sky", "sun", "moon", "stars"}),
        "Looking up, you can see the " + VBFC("day_desc") + " " + 
        VBFC("sun_moon") + " high in the sky above you.\n");
    add_item(({"down", "ground"}),
        "The ground beneath your feet is covered with a blanket of tall " +
        "green grass.\n");
    add_item(({"anorien"}),
        "You are in the lands of Anorien, in the nation of Gondor.\n");
    add_item(({"snow", "snow-capped peaks", "peaks", "peak"}),
        "The only snow you can see is on the highest peaks of the White " +
        "Mountains that run across the southern horizon.\n");
}
/*
 * Function name:        set_items_cairandros
 * Description  :        Items added to plains rooms when you include the line
 *                       set_items_cairandros(); 
 *                       Use for all rooms on the island of Cair Andros
 */
void
set_items_cairandros()
{
    add_item(({"island", "cair andros"}),
        "You are on the island of Cair Andros which stands in the middle " +
        "of the rushing waters of the Anduin River. You can see tall stone " +
        "fortifications, guarding the ford, peeking out from behind the " +
        "trees.\n");
    add_item(({"fort","fortress","fortifications","stone fort","stone",
            "stone fortress","stone fortifications","tall fortifications",
            "tall stone fort","tall stone fortifications","tall fort",
            "tall fortress","tall stone fortress"}),
        "Peeking out from amongst the green trees, the grey stone of " +
        "a tall fort appears to be guarding the ford across the rushing " +
        "waters of the mighty Anduin river.\n");
    add_item(({"ford", "river", "anduin", "bank", "banks", "waters",
            "great river", "water"}),
        "A shallow ford connects the banks of the Anduin with the island " +
        "of Cair Andros nearby, providing access to the far side of the " +
        "river.\n");
}
/*
 * Function name:        set_items_ford
 * Description  :        Items added to plains rooms when you include the line
 *                       set_items_ford(); 
 *                       Use for all plains rooms in Anorien near the ford
 *                       to Cair Andros
 */
void
set_items_ford()
{
    add_item(({"island", "cair andros"}),
        "The long forested island of Cair Andros stands in the middle " +
        "Anduin river here. Clearly guarding the ford are tall " +
        "fortifications of grey stone.\n");
    add_item(({"fort","fortress","fortifications","stone fort","stone",
            "stone fortress","stone fortifications","tall fortifications",
            "tall stone fort","tall stone fortifications","tall fort",
            "tall fortress","tall stone fortress"}),
        "Peeking out from amongst the green trees, the grey stone of " +
        "a tall fort appears to be guarding the ford across the rushing " +
        "waters of the mighty Anduin river.\n");
        add_item(({"ford", "river", "anduin", "bank", "banks", "waters",
            "great river", "water"}),
        "A shallow ford connects the banks of the Anduin with the island " +
        "of Cair Andros here, providing access to the far side of the " +
        "river.\n");
}
/*
 * Function name:        set_items_anduin
 * Description  :        Items added to plains rooms when you include the line
 *                       set_items_anduin(); 
 *                       Use for all plains rooms in Anorien near the Anduin
 */
void
set_items_anduin()
{
    add_item(({"river", "anduin", "bank", "banks", "waters", "great river", 
            "water"}),
        "The rushing waters of the mighty Anduin flow nearby, " +
        "cutting through the land on its journey south towards the sea. " +
        "If you were thirsty, you could bend down near the banks and " +
        "drink the fresh water of the great river.\n");
    add_item(({"grasses", "grass", "reed", "reeds"}),
        "In addition to the tall grasses which line the fields here, you " +
        "notice several shoots of tall, green reeds growing along the " +
        "side of the river. The reeds seem to collect in large bunches " +
        "where the ground turns into marsh.\n");
    add_item(({"marsh", "marshland"}),
        "In several places along the banks of the river, the water runs " +
        "shallow and slow enough to have made the ground more of a marsh " +
        "than anything else. Very often, this marshland is characterized " +
        "by collections of tall reeds growing in large clusters.\n");
    add_item(({"fish","silver fish", "brown fish"}),
        "You cannot see any fish right at this moment, but occasionally " +
        "you will see one jumping in the river nearby.\n");
}
/*
 * Function name:        set_items_entwash
 * Description  :        Items added to plains rooms when you include the line
 *                       set_items_entwash(); 
 *                       Use for all plains rooms in Anorien beside the Entwash
 */
void
set_items_entwash()
{
    add_item(({"river", "entwash", "bank", "banks", "waters", "mouth",
            "water", "mouths", "mouths of the entwash"}),
        "The swirling grey waters of the river cut through the " +
        "marshlands, emptying out to the east at the mouths of the " +
        "Entwash.\n");
    add_item(({"marsh", "marshland", "fen", "fens", "swamp", "swamps",
            "wetlands","wetland"}),
        "This marshland spreads out across the northern horizon, bordering " +
        "the sluggish grey waters of the Entwash. The fens are green and " +
        "full of life, but so treacherous as to make any travel to the " +
        "north impossible from here.\n");
    add_item(({"anduin", "great river"}),
        "Away on the eastern horizon, the wide rushing waters of the " +
        "Anduin River cut through the lands of Gondor as it makes a path " +
        "south into the sea.\n");
    add_item(({"fish","silver fish", "brown fish"}),
        "You cannot see any fish right at this moment, but occasionally " +
        "you will see one jumping in the river nearby.\n");
}
/*
 * Function name:        set_items_road
 * Description  :        Items added to plains rooms when you include the line
 *                       set_items_road(); 
 *                       Use for all plains rooms in Anorien beside the road
 */
void
set_items_road()
{
    add_item(({"road", "stone road", "dusty road", "highway"}),
        "This dusty stone road is barely visible in the distance as it " +
        "stretches across the northern length of Gondor running from " +
        "east to west.\n");
}
/*
 * Function name:        set_items_stream
 * Description  :        Items added to plains rooms when you include the line
 *                       set_items_stream(); 
 *                       Use for the rooms beside the Mering Stream
 */
void
set_items_stream()
{
    add_item(({"stream", "water", "waters", "mering stream"}),
        "Just west of you flows the Mering Stream, marking the western " +
        "edge of Gondor. The Eastfold and the lands of Rohan can be " +
        "seen on the far bank of the stream.\n");
    add_item(({"far bank", "west bank", "western bank", "eastfold",
            "rohan"}),
        "This is eastern edge of the Eastfold, ending here " +
        "at the Mering Stream which marks the boundary between " +
        "Gondor and Rohan.\n");
    add_item(({"firien", "firien wood", "wood", "forest", "tree",
            "trees", "oak", "oak tree", "oak trees"}),
        "Springing up immediately to the south, ancient oak trees form " +
        "the Firien Wood, a forest on the western edge of Gondor. It is " +
        "rumoured that not a single tree has been felled here since the " +
        "days of Isildur.\n");
}
/*
 * Function name:        set_items_city
 * Description  :        Items added to plains rooms when you include the line
 *                       set_items_city(); 
 *                       Use for all plains rooms in Anorien beside Osgiliath
 */
void
set_items_city()
{
    add_item(({"city", "ruins", "osgiliath"}),
        "You can see the sprawling ruins of Osgiliath stretched out " +
        "just south of you here. You can barely make out what appears " +
        "to be a bridge crossing the Anduin in the middle of the city.\n");
    add_item(({"wall", "rammas", "rammas echor"}),
        "Rising up to the south is Rammas Echor, the mighty wall that " +
        "stretches for leagues around Minas Tirith, encircling the " +
        "Pelennor Fields.\n");
    add_item(({"minas tirith", "citadel", "tower","tower of guard"}),
        "Perched on the eastern edge of the White Mountains, the " +
        "citadel known as Minas Tirith, the Tower of Guard, stands " +
        "tall as the heart of Gondor.\n");
    add_item(({"pelennor", "pelennor fields"}),
        "Hidden behind Rammas Echor are the Pelennor Fields, their " +
        "fertile lands sloping down in terraces eastward towards the " +
        "Anduin.\n");
    add_item(({"forest", "forests", "ithilien"}),
        "Countless trees rise up on the far bank of the Anduin, the " +
        "fabled forests of Ithilien.\n");
    add_item(({"terrace", "terraces"}),
        "You cannot see any terraces here! However, you suspect that " +
        "there might be some on the other side of Rammas Echor.\n");
    add_item(({"bridge", "stone bridge"}),
        "You can barely make out what appears to be a massive stone " +
        "bridge that spans across the entire width of the mighty " +
        "Anduin river. You are not close enough to see any details " +
        "however, as the bridge is in the middle of Osgiliath.\n");
    add_item(({"snow", "snow-capped peaks", "peaks", "peak"}),
        "The only snow you can see is on the highest peaks of the White " +
        "Mountains that rise up to the west.\n");
    add_item(({"mountains", "white mountains", "ered nimrais"}),
        "Rising up before you to the west, the rugged peaks " +
        "of the White Mountains claw at the empty sky above.\n");
    add_item(({"west", "western horizon"}),
        "The fields of Anorien stretch far to the west, until they meet " +
        "the Eastfold at the Mering Stream and enter the lands of Rohan.\n");
    add_item(({"southwest", "southwestern horizon"}),
        "A tall citadel is visible to the southwest, having been built " +
        "on the eastern edge of the White Mountains. This is Minas Tirith, " +
        "the heart of Gondor.\n");
    add_item(({"northwest", "northwestern horizon"}),
        "Far away in the distance to the northwest, the plains of Anorien " +
        "become marshy as the sluggish waters of the Entwash flood the " +
        "land.\n");
    add_item(({"north", "northern horizon"}),
        "Far to the north, the rolling fields of Anorien eventually dip " +
        "down to meet the banks of the Anduin.\n");
    add_item(({"east", "eastern horizon"}),
        "The fields of Anorien stretch out to the east, until they meet " +
        "the wide rushing waters of the mighty Anduin River.\n");
    add_item(({"southeast", "southeastern horizon"}),
        "The ruined city of Osgiliath lays before you in this direction, " +
        "a broken casualty of war.\n");
    add_item(({"northeast", "northeastern horizon"}),
        "The grey waters of the Entwash flow sluggishly through the marshy " +
        "lands which dominate the northeastern horizon before they empty " +
        "out into the rushing waters of the Anduin.\n");
    add_item(({"south", "southern horizon"}),
        "To the south, Rammas Echor rises up in defense of Minas Tirith.\n");
}
/*
 * Function name:        do_relax
 * Description  :        Provides an emote to relax in the grass nearby
 * Returns      :        int 0 - Prompt for proper syntax
 *                       int 1 - Returns the emote
 */
int
do_relax(string str)
{
    if(!str)
    {
        notify_fail("Relax where? In the grass perhaps?\n");
        return 0;
    }
    if((str != "grass")  && (str != "grasses") && (str != "field")
        && (str != "in the grass") && (str != "in the grasses")
        && (str != "in the field"))
    { 
        ("Relax where? In the grass perhaps?\n");
        return 1;
    }
    write("You search around briefly to find a comfortable spot where you " +
        "can lie down in the grass and enjoy a peaceful, relaxing moment.\n\n" +
        "You feel yourself enter an almost meditative state as you lie down, " +
        "listening to the playful splash of the Anduin river as it rushes " +
        "nearby in compliment to the gentle whisper of the wind as a breeze " +
        "drifts through the grass surrounding you. The pure, clean air " +
        "invigorates your soul, granting you a refreshed sense of purpose " +
        "in life.\n");
    SAYBB(" lies down in the grass and takes a quiet break from the world.\n");
    return 1;
}
/* do_relax */

/*
 * Function name:        do_smell
 * Description  :        Provides an emote to smell the air around you
 * Returns      :        int 0 - Prompt for proper syntax
 *                       int 1 - Returns the emote
 */
int
do_smell(string str)
{
    if(!str)
    {
        notify_fail("What are you trying to smell? The air?\n");
        return 0;
    }
    if((str != "air")  && (str != "wind") && (str != "the air")
        && (str != "the air around you") && (str != "the wind")
        && (str != "the breeze") && (str != "breeze"))
    { 
        ("What are you trying to smell? The air?\n");
        return 1;
    }
    write("You close your eyes and take a deep breath, smelling the " +
        "air around you.\n\nA deep meditative trace washes over you, " +
        "and you can feel the dance of the breeze as it playfully " +
        "skips across the gentle hills of Anorien. The fragrance of " +
        "a thousand wilflowers infuse your soul while the scent of " +
        "the tall green grass envelops you, relaxing your mind, " +
        "leaving you feeling completely refreshed and invigorated.\n");
    SAYBB(" closes their eyes and takes a deep breath, almost as if they " +
        "are inhaling the very essence of the land.\n");
    return 1;
}
/* do_smell */

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
    set_up_herbs(({ HERB_DIR + "lothore", HERB_DIR + "redweed", 
                    HERB_DIR + "tuo", HERB_DIR + "alfirin",
                    HERB_DIR + "attanar", HERB_DIR + "basil",
                    HERB_DIR + "blackberry", HERB_DIR + "blueberry",
                    HERB_DIR + "mint", HERB_DIR + "lissuin",
                    HERB_DIR + "tyelka", HERB_DIR + "ungolestel",
                     }),
                ({"ground","field"}), 5);
}
set_herbs_2()
{
    set_up_herbs(({ HERB_DIR + "athelas", HERB_DIR + "holly",
                    HERB_DIR + "foxglove", RHOVANION_DIR + "herbs/anna.c",
                    RHOVANION_DIR + "herbs/yave.c", HERB_DIR + "astaldo",
                    HERB_DIR + "blung", HERB_DIR + "braspberry",
                    HERB_DIR + "caraway", HERB_DIR + "carrot",
                    HERB_DIR + "garlic", HERB_DIR + "gonion",
                    HERB_DIR + "ginger", HERB_DIR + "handasse",
                    HERB_DIR + "myrtle", HERB_DIR + "seregon",
                    HERB_DIR + "suranie", HERB_DIR + "tuo",
                     }),
                ({"ground","field"}), 5);
}
set_herbs_3()
{
    set_up_herbs(({ HERB_DIR + "lothore", HERB_DIR + "redweed", 
                    HERB_DIR + "athelas", HERB_DIR + "holly",
                     }),
                ({"ground","field"}), 5);
}
set_herbs_4()
{
    set_up_herbs(({ HERB_DIR + "lothore", HERB_DIR + "redweed", 
                    HERB_DIR + "tuo", HERB_DIR + "alfirin",
                    HERB_DIR + "foxglove", HERB_DIR + "astaldo",
                    HERB_DIR + "blung", HERB_DIR + "braspberry",
                    HERB_DIR + "caraway", HERB_DIR + "carrot",
                     }),
                ({"ground","field"}), 5);
}
set_herbs_5()
{
    set_up_herbs(({ HERB_DIR + "tuo", HERB_DIR + "alfirin",
                    HERB_DIR + "foxglove", HERB_DIR + "astaldo",
                    HERB_DIR + "attanar", HERB_DIR + "basil",
                    HERB_DIR + "blackberry", HERB_DIR + "blueberry",
                    HERB_DIR + "blung", HERB_DIR + "braspberry",

                     }),
                ({"ground","field"}), 5);
}
set_herbs_6()
{
    set_up_herbs(({ HERB_DIR + "lothore", HERB_DIR + "redweed", 
                    HERB_DIR + "athelas", HERB_DIR + "holly",
                    HERB_DIR + "garlic", HERB_DIR + "gonion",
                    HERB_DIR + "ginger", HERB_DIR + "handasse",
                    HERB_DIR + "tyelka", HERB_DIR + "ungolestel",
                     }),
                ({"ground","field"}), 5);
}
set_herbs_7()
{
    set_up_herbs(({ HERB_DIR + "foxglove", HERB_DIR + "astaldo",
                    HERB_DIR + "attanar", HERB_DIR + "basil",
                    HERB_DIR + "blackberry", HERB_DIR + "blueberry",
                    HERB_DIR + "blung", HERB_DIR + "braspberry",
                    HERB_DIR + "ginger", HERB_DIR + "handasse",
                    HERB_DIR + "myrtle", HERB_DIR + "seregon",
                    HERB_DIR + "tyelka", HERB_DIR + "ungolestel",
                     }),
                ({"ground","field"}), 5);
}
set_herbs_8()
{
    set_up_herbs(({ HERB_DIR + "athelas", HERB_DIR + "holly",
                    HERB_DIR + "suranie", HERB_DIR + "tuo",
                    HERB_DIR + "tyelka", HERB_DIR + "ungolestel",
                    HERB_DIR + "angurth", HERB_DIR + "red_pepper",
                     }),
                ({"ground","field"}), 5);
}
set_herbs_9()
{
    set_up_herbs(({ HERB_DIR + "lothore", HERB_DIR + "redweed", 
                    HERB_DIR + "athelas", HERB_DIR + "holly",
                    HERB_DIR + "tuo", HERB_DIR + "alfirin",
                    HERB_DIR + "foxglove", HERB_DIR + "astaldo",
                    HERB_DIR + "caraway", HERB_DIR + "carrot",
                    HERB_DIR + "garlic", HERB_DIR + "gonion",
                    HERB_DIR + "mint", HERB_DIR + "lissuin",
                    HERB_DIR + "myrtle", HERB_DIR + "seregon",
                     }),
                ({"ground","field"}), 5);
}
/*
 * Function name:        add_trees
 * Description  :        Allows for climbable trees to be added in a plains room
 */
public void
add_trees(int value)
{
    trees = value;
}
/* add_trees */
/*
 * Function name:        plains_climb_tree
 * Description  :        This code lets people hide in trees by adding a tree
 *                       shadow.
 * Thanks:               This code was created by Carnak
 */
public int
plains_climb_tree(string str)
{
    object shadow;
    
    if(!strlen(str))
    {
        notify_fail("What did you want to climb? A tree?\n");
        return 0;
    }
    if (!parse_command(str, ({}), " [up] [on] [the] [in] [a] 'tree' / 'trees'")
&&
        !this_player()->query_tree_shadow())
    {
        notify_fail("Are you trying to climb up a tree?\n");
        return 0;
    }
    
    if (this_player()->query_tree_shadow())
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
    seteuid(getuid());
    
    if (!(shadow = clone_object(AN_OBJ_DIR + "tree_shadow.c")))
    {
        notify_fail("You were unable to climb the tree.\n");
        return 0;
    }
    
    write("You manage to find a nearby tree to climb and scramble up into " +
          "the branches.\n");
    SAYBB(" climbs up a nearby tree.\n");
    
    shadow->shadow_me(this_player());
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
        if (plains_climb_tree(str))
            return 1;

    notify_fail("You do not seem to be able to climb that here.\n");

    return climb_function(str);
}
/* do_climb */

/*
 * Function name:        do_pick
 * Description  :        Provides a chance for a mortal to pick a flower or
 *                       two from the ground. The flower picked has no resale
 *                       value. /d/Gondor/anorien/cairandros/obj/wildflower.c
 * Returns      :        int 0 - Prompt for proper syntax
 *                       int 1 - Returns the emote
 * Thanks       :        Mercade via Mirandus
 */
public int
do_pick(string str)
{
    object flower;
    notify_fail("Pick what? Flowers?\n");
    
    if((str != "flower" && str != "flowers" && str != "wildflower" &&
        str != "wildflowers"))
        return 0;
        
    if (flowers_left < 1)
        {
            write("It seems like too many flowers have been picked! The " +
                "only remaining wildflowers around here have some angry " +
                "looking bees that won't let you pick them!\n");
            return 1;
        }
            
            setuid();
            seteuid(getuid());
            flower = clone_object(AN_OBJ_DIR + "wildflower");
            flower->move(this_player(), 1);
            write("You reach down to pick a colourful wildflower out of " +
                "the ground.\n");
            say(QCTNAME(TP) + " picks a colourful wildflower.\n");
            flowers_left = flowers_left -1;

        return 1;
}
/* do_pick */
public void
init()
{
    ::init();
    add_action("do_relax","relax");
    add_action("do_relax","rest");
    add_action("do_smell","smell");
    add_action("do_smell","sniff");
    add_action("do_pick","pick");
    add_action("do_climb","climb");
}