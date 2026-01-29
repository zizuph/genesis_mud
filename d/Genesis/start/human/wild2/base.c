/*
 * /d/Genesis/start/human/wild2/base.c
 *
 * A base file to make the land around Sparkle more interesting.
 *
 * Varian - March, 2016
 *
 */

#pragma strict_types
#include "wild.h"

inherit "/std/room";
inherit "/d/Gondor/common/lib/herbsearch";
inherit "/d/Gondor/common/lib/room_tell";
inherit "/d/Gondor/common/lib/drink_water.c";

#include <macros.h>

void set_items_sparkle();
void set_items_orcvalley();
void set_items_darkroad();
void set_items_orcroad();
void set_items_field();
void set_items_mountain();
void set_items_brightroad();
void set_items_driver();
void set_items_forest();
void set_items_moor();
void set_herbs();

int do_relax(string str);
int do_pick(string str);
int flowers_left = 10;
int trees, mountain;

/*
 * Function name:        create_wild_room
 * Description  :        Use create_wild_room() to make wild rooms that use
 *                       information from this file
 */
void create_wild_room() 
{
}

nomask void create_room() 
{

    create_wild_room();
/*
 * Function name:        add_tell - used when inheriting 
 *                       "/d/Gondor/common/lib/room_tell";
 * Description  :        Gives some atmosphere by providing some 'sounds'
 *                       in the room in a similar manner to echo
 */

        add_tell("A gentle breeze ripples past you, flowing down from the " +
            "mountains and running out towards the sea.\n");
        add_tell("In the distance, you see an eagle slowly circling " +
            "in the air near a large mountain.\n");
        add_tell("A shadow momentarily falls across the land as a " +
            "cluster of clouds drift past the sun.\n");
        add_tell("You hear the shrill piercing cry of a hawk as its call " +
            "rings out across the wilderness.\n");
        add_tell("A small flock of birds dip and dive as they chase each " +
            "other nearby.\n");
        add_tell("A brief gust of wind pushes a blast of cool mountain air " +
            "past you, causing you to shiver slightly.\n");
        add_tell("A swirling wind blows past you on its way east.\n");
        add_tell("You see what appears to be a fox darting across the " +
            "fields in the distance.\n");
        add_tell("A bright orange butterfly flutters past you.\n");
        add_tell("The droning buzz of insects echoes around you.\n");
        add_tell("You hear the repetitive sound of crickets chirping in the " +
            "grass nearby.\n");
        add_tell("You are suddenly bombarded by a cloud of black flies " +
            "buzzing around your head.\n");
        add_tell("Two swallows chase each other across the fields, swooping " +
            "and diving.\n");
        add_tell("A handful of honeybees buzz around, landing on some " +
            "brightly coloured wildflowers.\n");
        add_tell("A small honeybee flies around your head, inspecting " +
            "you before settling on a blue wildflower.\n");
        add_tell("A little honeybee flies around your head, inspecting " +
            "you before settling on a yellow wildflower.\n");
        add_tell("A tiny honeybee flies around your head, inspecting " +
            "you before settling on a red wildflower.\n");
        add_tell("A horde of tiny flies start buzzing around your face, " +
            "biting at your bare flesh.\n");
        add_tell("A brightly coloured dragonfly zips past, chasing down " +
            "some insects for a quick meal.\n");
        add_tell("A yellow snake swiftly slithers past, quickly becoming " +
            "lost in the grass.\n");
        add_tell("A green snake swiftly slithers past, quickly becoming " +
            "lost in the grass.\n");
        add_tell("Dozens of tiny butterflies flutter across in front of you " +
            "in a parade of bright colours.\n");
        add_tell("A handful of tiny butterflies float on the breeze, " +
            "passing by in a parade of bright colours.\n");
        add_tell("A couple of tiny colourful butterflies dance above the " +
            "grass nearby.\n");
        add_tell("A large deer grazing in the fields looks up at you " +
            "before bounding away in the distance.\n");
        add_tell("A young buck is briefly visible in the distance before " +
            "he dashes away into a cluster of trees.\n");
        add_tell("You idly watch as some wispy white clouds float gently " +
            "across the sky.\n");
        add_tell("Some dark grey clouds hover over the mountains on the " +
            "western horizon, warning of rain.\n");
        add_tell("You quickly cover yourself as a short shower of cold " +
            "rain falls down before the sun peeks out and warms the air " +
            "again.\n");
        add_tell("Several grasshoppers cling to the weeds and grasses " +
            "nearby before jumping away.\n");
        add_tell("You hear the incessant buzzing of grasshoppers in the " +
            "grass nearby.\n");
        add_tell("You catch a brief glimpse of a furry brown field mouse " +
            "scurrying into the grass nearby.\n");
/*
 * Function name:        set_tell_time
 * Description  :        Provides time increments between tells
 */
        set_tell_time(random(550) + 100);
}

/*
 * Function name:        enter_inc
 * Description  :        Needed to start the room tells
 */
public void
enter_inv(object ob, object from)
{
    start_room_tells();
    ::enter_inv(ob, from);
}

/*
 * Function name:        set_items_sparkle
 * Description  :        Items added to wild rooms when you include the line
 *                       set_items_sparkle(); 
 *                       Use for rooms located within Sparkle valley
 */
public void
set_items_sparkle()
{
    add_item(({"river", "rivers"}),
        "There are two major rivers, the Diamond River and the Copper " +
        "river which run down from the Grey Mountains before they empty " +
        "out into the Pen Sea.\n");
    add_item(({"diamond river"}),
        "The Diamond River flows down from the north before it joins the " +
        "Copper River and turns east to empty out into the Pen Sea.\n");
    add_item(({"copper river"}),
        "The Copper River flows up from the south before it joins the " +
        "Diamond River and turns east to empty out into the Pen Sea.\n");
    add_item(({"grasses", "grass", "ground", "field", "fields", "green grass",
            "yellowish grass", "yellow grass", "yellow-green grass",
            "vegetation","meadow","meadows"}),
        "The fields and mountainsides all around the Sparkle valley are " +
        "covered with a carpet of green and yellow grass. The grass seems " +
        "to be home to a wide variety of animal life, including endless " +
        "hordes of annoying insects.\n");
    add_item(({"flower","flowers","wildflower","wildflowers"}),
        "Dotting the fields of grass with a colourful splash of whimsy, are " +
        "dozens of different wildflowers. Dozens of different varieties " +
        "in almost every colour attract a collection of bees and other " +
        "various insects.\n");
    add_item(({"blue flower","blue flowers","blue wildflower", 
            "blue wildflowers"}),
        "You can see several blue wildflowers growing in the yellow-green " +
        "grass nearby, most of them attracting the attention of various " +
        "insects.\n");
    add_item(({"red flower","red flowers","red wildflower", 
            "red wildflowers"}),
        "You can see handfuls of red wildflowers growing in the yellowish " +
        "grass nearby. Several honeybees seem to be jumping from one to " +
        "the next as they gather pollen.\n");
    add_item(({"yellow flower","yellow flowers","yellow wildflower", 
            "yellow wildflowers"}),
        "Several pockets of bright yellow wildflowers peek out of the green " +
        "grass which grows all around you.\n");
    add_item(({"weed","weeds","plants","coarse plants"}),
        "As one might expect, the fields here are filled with all sorts " +
        "of coarse plants scattered in amongst the flowers.\n");
    add_item(({"insect", "insects"}),
        "The fields and mountains of Sparkle valley are filled with the " +
        "buzzing drone of thousands of insects. From honeybees and " +
        "butterflies to black flies and bitemes, not to mention everything " +
        "else in between, they hover around the grassy fields and " +
        "wildflowers when they are not getting curious enough to inspect a " +
        "traveller such as yourself.\n");
    add_item(({"biteme","bitemes","fly","flies","black fly","black flies"}),
        "These annoying little insects seem to be overjoyed that you, their " +
        "most recent meal, have arrived. No matter how much you swat at " +
        "them, there are still dozens more hovering around your head and " +
        "biting at your skin.\n");
    add_item(({"eagle","eagles"}),
        "Occasionally, you can see the wide wings of an eagle, circling " +
        "in the sky near the mountains which dominate the western horizon.\n");
    add_item(({"swallow","swallows"}),
        "Every once in a while, you can see a small group of swallows " +
        "dipping and diving across the valley.\n");
    add_item(({"bird","birds"}),
        "This valley is full of life, including hundreds of birds which " +
        "keep the air alive with song, and fly from one grove of trees " +
        "to another in small flocks.\n");
    add_item(({"dragonfly","dragonflies"}),
        "In a valley so rich in life, and in particular small flying " +
        "insects, it is hardly surprising to see that so many dragonflies " +
        "are zipping around you as they catch their lunch.\n");
    add_item(({"crickets","cricket","grasshopper","grasshoppers"}),
        "The frequent buzz and chirp of grasshoppers and crickets fills " +
        "your ears as the insects jump around the grass nearby.\n");
    add_item(({"butterfly","butterflies","orange butterfly",
            "orange butterflies"}),
        "Dancing on the air above the grass nearby, there seem to be " +
        "hundreds of colourful butterflies fluttering around in a " +
        "parade of colour.\n");
    add_item(({"bee","bees","honeybee","honeybees"}),
        "You see plenty of honeybees with their fat yellow and black " +
        "striped bodies buzzing around, drifting from one flower to the " +
        "next as they collect pollen.\n");
    add_item(({"valley", "vale", "sparkle vale", "sparkle valley","land"}),
        "You are in Sparkle valley, where the Diamond and Copper Rivers " +
        "run down from the Grey Mountains and merge before they empty into " +
        "the Pen Sea. On the north side of the river mouth stands the " +
        "legendary port city of Sparkle. Three major roads branch out " +
        "from Sparkle: the Dark Road cutting through the mountains in the " +
        "north towards Dwarfheim and Larton, the Bright Road which dives " +
        "into the Jade forest in the south, and the Orc Road which climbs " +
        "over the high pass west into the traditional Orcish homeland.\n");
    add_item(({"sparkle","port","city","mouth","river mouth"}),
        "Sitting at the mouth of the rivers which run through the valley is " +
        "the legendary port of Sparkle. Sparkle is a great city, with tall " +
        "sailing ships which can take travellers to every part of the " +
        "donut. In this valley, it appears that all roads lead to Sparkle.\n");
    add_item(({"larton", "larstown"}),
        "You cannot see the city of Larton from here, but it is rumoured " +
        "to be the northern terminus of the Dark Road.\n");
    add_item(({"jade forest", "forest", "jade"}),
        "The Jade Forest grows at the southern end of the valley, crouching " +
        "along the edges of the Bright Road before it trails off into the " +
        "wilderness.\n");
    add_item(({"dwarfheim"}),
        "Dwarfheim is the traditional homeland of the Dwarven folk. It is " +
        "said that the heart of Dwarfheim is hidden in a cave behind a " +
        "waterfall, somewhere north of the Dark Road where the roads are " +
        "paved with gold.\n");
    add_item(({"tree","trees"}),
        "Dozens of small groves of trees are scattered across the fields, " +
        "hills and mountainsides. In the south end of the valley, the " +
        "groves become more frequent before they blossom into the dark " +
        "depths of the Jade Forest.\n");
    add_item(({"fir", "firs", "fir tree", "fir trees"}),
        "Dozens of these slender evergreens collect in small clusters here " +
        "and there across the Sparkle valley.\n");
    add_item(({"elm", "elms", "elm tree", "elm trees"}),
        "Tall and slender, dozens of elm trees cast their shade across " +
        "the valley in small groves.\n");
    add_item(({"grove","groves"}),
        "You can see several groves of trees, mostly elms and firs, which " +
        "gather on the grassy fields or huddle on the sloping hills of the " +
        "mountainsides.\n");
    add_item(({"hill", "hills", "hillside", "hillsides", "foothills",
            "foothill"}),
        "Countless hills rise and fall across the perimeter of the valley " +
        "as they march upwards to grow into the jagged heights of the " +
        "Grey Mountains.\n");
    add_item(({"boulder", "broken boulders", "broken boulder", "boulders"}),
        "You can see the occasional collection of rocky boulders which sit " +
        "alone in the grass.\n");
    add_item(({"fox","foxes","brown fox","brown foxes"}),
        "Every now and then, you catch sight of a brown fox as it runs " +
        "swiftly in the distance.\n");
    add_item(({"snake","snakes", "yellow snake", "green snake"}),
        "Every now and then, you will spot a small grass snake as it " +
        "slithers across the fields in search of a meal.\n");
    add_item(({"mouse","mice","brown mouse","brown mice"}),
        "There are probably dozens of mice hiding in the grasses nearby, " +
        "but you rarely catch a glimpse of the elusive creatures.\n");
    add_item(({"deer","stag","stags","buck","bucks"}),
        "Ocassionaly you will see some deer grazing in the fields, yet any " +
        "time they feel you get too close, they jump up and dash far away.\n");
    add_item(({"breeze","breezes","wind","gust"}),
        "You cannot see the wind of course, but occasional gusts and " +
        "breezes drift pass you as they tumble down from the mountains and " +
        "rush east to meet the sea.\n");
    add_item(({"mountain","mountains","grey mountains"}),
        "Stretching across the western horizon there is an endless " +
        "line of jagged, snow-capped mountain peaks as they pierce the " +
        "sky. These are the Grey Mountains, a legendary fixture in the " +
        "countryside surrounding Sparkle. It is said that the " +
        "traditional homeland of the dwarves, Dwarfheim is hidden " +
        "somewhere to the north, while somewhere in the south, goblins " +
        "have tunneled deep into the heart of the mountains, " +
        "establishing a realm of their own.\n");
    add_item(({"sea","pen sea","wave","waves","ocean"}),
        "Bordering the eastern edge of Sparkle valley is the Pen Sea, " +
        "where several tall sailing ships brave the crashing waves of the " +
        "ocean to carry goods and passengers all across the donut.\n");
    add_item(({"shadow","shadows","clouds","cloud","shade"}),
        "There are several clouds hanging in the sky, occasionally passing " +
        "in front of the sun casting down both shade and shadow.\n");
    add_item(({"ground","down"}),
        "Coarse grass of mixed patches of green and yellow stretches " +
        "across the ground all around you.\n");
    add_item(({"sky","up","sun"}),
        "High up in the sky, the bright yellow sun shines its light and " +
        "warmth across the valley floor.\n");
    add_item(({"hawk","hawks"}),
        "Every now and then, you can see the majestic forms of hawks as " +
        "they circle in the sky, looking for prey.\n");
    add_item(({"rain","raindrops"}),
        "It seems that this valley seems to spawn several sudden, if " +
        "short, showers of raindrops that water the land.\n");
    add_item(({"water","waters"}),
        "Sparkle valley is quite lush and fertile, with two strong " +
        "rivers rushing down from the mountains to empty into the sea " +
        "nearby.\n");
    add_item(({"ships","ship","sail","sails","sailing ships","sailing ship",
            "tall ship","tall ships","tall sailing ship",
            "tail sailing ships"}),
        "Many tall sailing ships are constantly arriving and departing " +
        "in the port of Sparkle, breaking across the mighty waves of " +
        "the Pen Sea.\n");
    add_item(({"green oaks", "faerie", "greenoaks"}),
        "The village of Green Oaks, in the land of Faerie, can be reached " +
        "by following the Orc Road as it cuts west through the Grey " +
        "Mountains and then turns to the south.\n");
    add_item(({"orc road"}),
        "The Orc Road travels west from Sparkle, through the taditional " +
        "orc hopelands and eventually to the village of Green Oaks " +
        "in the land of Faerie.\n");
    add_item(({"bright road"}),
        "The Bright Road travels south from Sparkle towards the wilderness " +
        "south of the Jade Forest.\n");
    add_item(({"dark road"}),
        "The Dark Road travels north from Sparkle, past the traditional " +
        "dwarven homeland of Dwarfheim, all the way to the city of " +
        "Larton.\n");
    add_item(({"pass","mountain pass","high pass"}),
        "The Orc Road cuts through the Grey Mountains to the west " +
        "through the high pass, leading towards the traditional orc " +
        "homelands and eventually Faerie.\n");
    add_item(({"horizon"}),
        "You quickly glance across the valley in all directions, but " +
        "you could probably focus on examining the northern, western, " +
        "southern or eastern horizon if you wanted.\n");
    add_item(({"north horizon","northern horizon","north"}),
        "Looking to the north, you can see the jagged peaks of the Grey " +
        "Mountains enclose the valley, separating it from distant " +
        "destinations such as Dwarfheim or the city of Larton.\n");
    add_item(({"west horizon","western horizon","west"}),
        "Looking to the west, the Grey Mountains are at their most " +
        "intimidating, blocking all passage save where the Orc Road " +
        "cuts through the high pass and into the orcish homelands " +
        "beyond.\n");
    add_item(({"east horizon","eastern horizon","east"}),
        "Looking to the east, you can see the bustling port city of " +
        "Sparkle, sitting gracefully on the coast of the Pen Sea.\n");
    add_item(({"south horizon","southern horizon","south"}),
        "Looking to the south, you see the slopes of the Grey Mountains " +
        "covered in the bundled masses of dark trees known as the Jade " +
        "Forest, which march down to huddle around the bright road.\n");
    add_item(({"northeast horizon","northeastern horizon","northeast"}),
        "Looking to the northeast, you can see the jagged peaks of the Grey " +
        "Mountains dwindle down as they approach the coast of the Pen Sea.\n");
    add_item(({"northwest horizon","northwestern horizon","northwest"}),
        "Looking to the northwest, you can see the jagged peaks of the Grey " +
        "Mountains enclose the valley, separating it from distant " +
        "destinations such as Dwarfheim or the city of Larton.\n");
    add_item(({"southeast horizon","southeastern horizon","southeast"}),
        "Looking to the southeast, you see the dark green trees of the " +
        "Jade Forest ending only when they reach the coast of the Pen " +
        "Sea.\n");
    add_item(({"southwest horizon","southwestern horizon","southwest"}),
        "Looking to the southwest, you see the slopes of the Grey Mountains " +
        "covered in bundled masses of dark trees known as the Jade " +
        "Forest, marching down to huddle around the bright road.\n");
    add_item(({"peak","peaks","mountain peak","mountain peaks","slope",
            "slopes","mountain slope","mountain slopes","jagged peak",
            "jagged peaks","snow","snow-capped peak","snow-capped peaks"}),
        "You can see rugged grey slopes of the Grey Mountains surrounding " +
        "most of this valley, their jagged, snow-capped peaks piercing the " +
        "clouds and clawing at the blue sky above.\n");
    add_item(({"snow","ice"}),
        "High above you in the distance, you can see snow and ice topping " +
        "the highest peaks of the Grey Mountains.\n");
}

/*
 * Function name:        set_items_orcvalley
 * Description  :        Items added to wild rooms when you include the line
 *                       set_items_orcvalley(); 
 *                       Use for rooms located in the orc valley
 */
public void
set_items_orcvalley()
{
    add_item(({"grasses", "grass", "ground", "field", "fields", "green grass",
            "yellowish grass", "yellow grass", "yellow-green grass",
            "vegetation"}),
        "The fields and mountainsides all around the orc valley are " +
        "covered with a carpet of green and yellow grass. The grass seems " +
        "to be home to a wide variety of animal life, including endless " +
        "hordes of annoying insects.\n");
    add_item(({"flower","flowers","wildflower","wildflowers"}),
        "Hiding in the tall grass with a colourful splash of whimsy, are " +
        "dozens of different wildflowers. Dozens of different varieties " +
        "in almost every colour attract a collection of bees and other " +
        "various insects.\n");
    add_item(({"blue flower","blue flowers","blue wildflower", 
            "blue wildflowers"}),
        "You can see several blue wildflowers growing in the yellow-green " +
        "grass nearby, most of them attracting the attention of various " +
        "insects.\n");
    add_item(({"red flower","red flowers","red wildflower", 
            "red wildflowers"}),
        "You can see handfuls of red wildflowers growing in the yellowish " +
        "grass nearby. Several honeybees seem to be jumping from one to " +
        "the next as they gather pollen.\n");
    add_item(({"yellow flower","yellow flowers","yellow wildflower", 
            "yellow wildflowers"}),
        "Several pockets of bright yellow wildflowers peek out of the green " +
        "grass which grows all around you.\n");
    add_item(({"weed","weeds","plants","coarse plants"}),
        "As one might expect, the fields here are filled with all sorts " +
        "of coarse plants scattered in amongst the flowers.\n");
    add_item(({"insect", "insects"}),
        "The fields and mountains of the orc valley are filled with the " +
        "buzzing drone of thousands of insects. From honeybees and " +
        "butterflies to black flies and bitemes, not to mention everything " +
        "else in between, they hover around the grassy fields and " +
        "wildflowers when they are not getting curious enough to inspect a " +
        "traveller such as yourself.\n");
    add_item(({"biteme","bitemes","fly","flies","black fly","black flies"}),
        "These annoying little insects seem to be overjoyed that you, their " +
        "most recent meal, have arrived. No matter how much you swat at " +
        "them, there are still dozens more hovering around your head and " +
        "biting at your skin.\n");
    add_item(({"eagle","eagles"}),
        "Occasionally, you can see the wide wings of an eagle, circling " +
        "in the sky near the mountains which dominate the eastern horizon.\n");
    add_item(({"swallow","swallows"}),
        "Every once in a while, you can see a small group of swallows " +
        "dipping and diving across the valley.\n");
    add_item(({"bird","birds"}),
        "This valley is full of life, including hundreds of birds which " +
        "keep the air alive with song, and fly from one grove of trees " +
        "to another in small flocks.\n");
    add_item(({"dragonfly","dragonflies"}),
        "In a valley so rich in life, and in particular small flying " +
        "insects, it is hardly surprising to see that so many dragonflies " +
        "are zipping around you as they catch their lunch.\n");
    add_item(({"crickets","cricket","grasshopper","grasshoppers"}),
        "The frequent buzz and chirp of grasshoppers and crickets fills " +
        "your ears as the insects jump around the grass nearby.\n");
    add_item(({"butterfly","butterflies","orange butterfly",
            "orange butterflies"}),
        "Dancing on the air above the grass nearby, there seem to be " +
        "hundreds of colourful butterflies fluttering around in a " +
        "parade of colour.\n");
    add_item(({"bee","bees","honeybee","honeybees"}),
        "You see plenty of honeybees with their fat yellow and black " +
        "striped bodies buzzing around, drifting from one flower to the " +
        "next as they collect pollen.\n");
    add_item(({"valley", "vale", "orc vale", "orc valley","land"}),
        "You are in the orc valley, west of the Grey Mountains near the " +
        "lands of Sparkle. The floor of the valley is blanketed with " +
        "the tall green trees of the Orc Forest, split open by the " +
        "highway known as the Orc Road which runs from the High Pass " +
        "in the east before turning towards Faerie in the south.\n");
    add_item(({"sparkle","city"}),
        "You cannot see the legendary city of Sparkle, as it rests " +
        "somewhere beyond the High Pass, east of the Grey Mountains.\n");
    add_item(({"orc forest", "forest", "woods"}),
        "Spread out like a blanket across the floor of the valley, " +
        "the Orc Forest is full of green, healthy trees. Upon further " +
        "reflection, it is probably full of healthy orcs too! You had " +
        "better be careful.\n");
    add_item(({"dwarfheim"}),
        "Dwarfheim is the traditional homeland of the Dwarven folk. It is " +
        "said that the heart of Dwarfheim is hidden in a cave behind a " +
        "waterfall, somewhere north of the Dark Road where the roads are " +
        "paved with gold.\n");
    add_item(({"tree","trees"}),
        "Dozens of small groves of trees are scattered across the fields, " +
        "hills and mountainsides. In the middle of the valley, the trees " +
        "collapse into the green mass known as the Orc Forest.\n");
    add_item(({"fir", "firs", "fir tree", "fir trees"}),
        "Dozens of these slender evergreens collect in small clusters here " +
        "and there across the orc valley.\n");
    add_item(({"elm", "elms", "elm tree", "elm trees"}),
        "Tall and slender, dozens of elm trees cast their shade across " +
        "the valley in small groves.\n");
    add_item(({"grove","groves"}),
        "You can see several groves of trees, mostly elms and firs, which " +
        "gather on the grassy fields or huddle on the sloping hills of the " +
        "mountainsides.\n");
    add_item(({"hill", "hills", "hillside", "hillsides", "foothills",
            "foothill"}),
        "Countless hills rise and fall across the perimeter of the valley " +
        "as they march upwards to grow into the jagged heights of the " +
        "Grey Mountains.\n");
    add_item(({"boulder", "broken boulders", "broken boulder", "boulders"}),
        "You can see the occasional collection of rocky boulders which sit " +
        "alone in the grass.\n");
    add_item(({"fox","foxes","brown fox","brown foxes"}),
        "Every now and then, you catch sight of a brown fox as it runs " +
        "swiftly in the distance.\n");
    add_item(({"snake","snakes", "yellow snake", "green snake"}),
        "Every now and then, you will spot a small grass snake as it " +
        "slithers across the fields in search of a meal.\n");
    add_item(({"mouse","mice","brown mouse","brown mice"}),
        "There are probably dozens of mice hiding in the grasses nearby, " +
        "but you rarely catch a glimpse of the elusive creatures.\n");
    add_item(({"deer","stag","stags","buck","bucks"}),
        "Ocassionaly you will see some deer grazing in the fields, yet any " +
        "time they feel you get too close, they jump up and dash far away.\n");
    add_item(({"breeze","breezes","wind","gust"}),
        "You cannot see the wind of course, but occasional gusts and " +
        "breezes drift pass you as they tumble down from the mountains and " +
        "rush east to meet the sea.\n");
    add_item(({"mountain","mountains","grey mountains"}),
        "Stretching across the northern and eastern horizons there is an " +
        "endless line of jagged, snow-capped mountain peaks that pierce the " +
        "sky. These are the Grey Mountains, passable only through the " +
        "High Pass to the east, which leads to the legendary city of " +
        "Sparkle.\n");
    add_item(({"shadow","shadows","clouds","cloud","shade"}),
        "There are several clouds hanging in the sky, occasionally passing " +
        "in front of the sun casting down both shade and shadow.\n");
    add_item(({"ground","down"}),
        "Coarse grass of mixed patches of green and yellow stretches " +
        "across the ground all around you.\n");
    add_item(({"sky","up","sun"}),
        "High up in the sky, the bright yellow sun shines its light and " +
        "warmth across the valley floor.\n");
    add_item(({"hawk","hawks"}),
        "Every now and then, you can see the majestic forms of hawks as " +
        "they circle in the sky, looking for prey.\n");
    add_item(({"rain","raindrops"}),
        "It seems that this valley seems to spawn several sudden, if " +
        "short, showers of raindrops that water the land.\n");
    add_item(({"green oaks", "faerie", "greenoaks"}),
        "The village of Green Oaks, in the land of Faerie, can be reached " +
        "by following the Orc Road as it heads south out of the valley.\n");
    add_item(({"orc road"}),
        "The Orc Road is a well-travelled highway that cuts through the " +
        "middle of this valley, connecting Sparkle with the elven lands " +
        "of Faerie.\n");
    add_item(({"pass","mountain pass","high pass"}),
        "The Orc Road cuts through the Grey Mountains to the east " +
        "through the high pass, leading towards the legendary city " +
        "of Sparkle.\n");
    add_item(({"horizon"}),
        "You quickly glance across the valley in all directions, but " +
        "you could probably focus on examining the northern, western, " +
        "southern or eastern horizon if you wanted.\n");
    add_item(({"north horizon","northern horizon","north"}),
        "Looking to the north, you can see the jagged peaks of the Grey " +
        "Mountains enclose the valley, preventing even the passage of " +
        "even the most experienced of exporers.\n");
    add_item(({"west horizon","western horizon","west"}),
        "The Grey Mountains slowly fade away into rugged hills that " +
        "cover the western horizon.\n");
    add_item(({"east horizon","eastern horizon","east"}),
        "Looking to the east, you see the mighty Grey Mountains as they " +
        "rise up high into the sky, broken only by the High Pass.\n");
    add_item(({"south horizon","southern horizon","south"}),
        "Looking to the south, you see the Grey Mountains cut across the " +
        "horizon, with only the Orc Road providing any hope of safe " +
        "passage.\n");
    add_item(({"northeast horizon","northeastern horizon","northeast"}),
        "Looking to the northeast, you can see the jagged peaks of the Grey " +
        "Mountains rise up tall and menacing.\n");
    add_item(({"northwest horizon","northwestern horizon","northwest"}),
        "Looking to the northwest, you can see the jagged peaks of the Grey " +
        "Mountains stretch off into the distance, spawning endless " +
        "ripples of rocky foothills.\n");
    add_item(({"southeast horizon","southeastern horizon","southeast"}),
        "Looking to the southeast, you see the Grey Mountains sweep down " +
        "towards the south to help surround the valley.\n");
    add_item(({"southwest horizon","southwestern horizon","southwest"}),
        "Looking to the southwest, you see the Grey Mountains cut across " +
        "the horizon, with only the Orc Road providing any hope of safe " +
        "passage.\n");
    add_item(({"peak","peaks","mountain peak","mountain peaks","slope",
            "slopes","mountain slope","mountain slopes","jagged peak",
            "jagged peaks","snow","snow-capped peak","snow-capped peaks"}),
        "You can see rugged grey slopes of the Grey Mountains surrounding " +
        "most of this valley, their jagged, snow-capped peaks piercing the " +
        "clouds and clawing at the blue sky above.\n");
}

/*
 * Function name:        set_items_darkroad
 * Description  :        Items added to wild rooms when you include the line
 *                       set_items_darkroad(); 
 *                       Use for rooms located on the Dark Road only
 */
public void
set_items_darkroad()
{
    add_item(({"road","path","dark road","highway","paving stone",
            "paving stones"}),
        "This is a raised highway running across the fields north of " +
        "Sparkle as it climbs up towards the treacherous pass through the " +
        "Grey Mountains known as the Renegade Cut. Few travellers seem " +
        "to follow this road these days, as the pass is now controlled " +
        "by bandits, but it is said that the northern terminus of the " +
        "road is the city of Larton.\n");
    add_item(({"pass","renegade cut","mountain pass","cut"}),
        "If you were to follow the this road far enough, you would come to " +
        "the mountain pass known as Renegade Cut. Travel through the cut is " +
        "now seen as nothing more than suicide as bandits now control the " +
        "mountain pass and this highway has since been given its " +
        "name of the Dark Road.\n");
}

/*
 * Function name:        set_items_orcroad
 * Description  :        Items added to wild rooms when you include the line
 *                       set_items_orcroad(); 
 *                       Use for rooms located on the Orc Road only
 */
public void
set_items_orcroad()
{
    add_item(({"road","path","orc road","highway","paving stone",
            "paving stones","flat stone","flat stones"}),
        "Thousands of flat stones have been cut and raised above the " +
        "land to build the Orc Road. The road leads directly west out of " +
        "Sparkle, climbing the high pass, before settling down into the " +
        "Orc Forest and eventually to the elven lands of Faerie.\n");
    add_item(({"pass","high pass","mountain pass"}),
        "High above you to the west, the Orc Road appears to cut " +
        "through the jagged peaks of the Grey Mountains using the " +
        "high pass before it enters orcish homelands.\n");
}

/*
 * Function name:        set_items_field
 * Description  :        Items added to wild rooms when you include the line
 *                       set_items_field(); 
 *                       Use for field rooms off of the roads
 */
public void
set_items_field()
{
    add_item(({"field","fields","meadow","meadows"}),
        "You are in the middle of wide fields of tall green and yellow " +
        "grass. Scattered all around you, several meadows are tucked in " +
        "beside the many small streams that feed into the Diamond River. \n");
    add_item(({"stream","streams"}),
        "You are in the middle of wide fields of tall green and yellow " +
        "grass. Scattered all around you, several meadows are tucked in " +
        "beside the many small streams that feed into the Diamond River. \n");
}

/*
 * Function name:        set_items_mountain
 * Description  :        Items added to wild rooms when you include the line
 *                       set_items_mountain(); 
 *                       Use for rooms located in the Grey Mountains
 */
public void
set_items_mountain()
{
    add_item(({"mountain","mountains","mountainside","mountainsides"}),
        "You are high up in the Grey Mountains, where the foothills fall " +
        "away before you and flatten out into Sparkle valley far below. " +
        "The mountain path you are on twists and turns across treacherous " +
        "footing, reminding you that a misstep could send you to your " +
        "death.\n");
    add_item(({"horizon","north horizon","northern horizon","north",
            "west horizon","western horizon","west","east horizon",
            "eastern horizon","east","south horizon","southern horizon",
            "south","northeast horizon","northeastern horizon","northeast",
            "northwest horizon","northwestern horizon","northwest",
            "southeast horizon","southeastern horizon","southeast",
            "southwest horizon","southwestern horizon","southwest"}),
        "You quickly glance all around, but deep in the mountains as " +
        "you are, you see nothing but more mountains in every direction!\n");
    add_item(({"peak","peaks","mountain peak","mountain peaks","slope",
            "slopes","mountain slope","mountain slopes","jagged peak",
            "jagged peaks","snow","snow-capped peak","snow-capped peaks"}),
        "You are deep in the rocky slopes of the Grey Mountains, surrounded " +
        "by the jagged snow-capped peaks that claw at the blue sky above. " +
        "The mountains themselves are covered in patches of tall grass " +
        "and beautiful wildflowers that collect in small fields, while " +
        "dozens of rocks and boulders of all sizes sit nestled on the " +
        "mountainside, accompanied by the occasional grove of trees.\n");
    add_item(({"trail","narrow trail","gravel trail","dirt trail","path",
            "narrow path","gravel path","dirt path","mountain path",
            "mountain trail"}),
        "This narrow trail winds through the steep slopes of the " +
        "mountains that surround you! It is quite obvious that the " +
        "only safe passage is to follow the path, lest you slip " +
        "and fall to your death!\n");
    add_item(({"ground","down"}),
        "Patches of coarse grass and wildflowers are mixed into the rocky " +
        "gravel that covers the steep mountainside around you.\n");
    add_item(({"gravel","stones","stone","pebble","pebbles","rock","rocks"}),
        "Thousands of loose stones and pebbles have created a rocky " +
        "gravel that covers the mountainside here. The only safe passage " +
        "seems to be available by following the trail.\n");
    add_item(({"boulder","boulders"}),
        "Several large boulders are resting on the grassy slopes of the " +
        "mountain nearby. Some of the boulders are very large indeed! " +
        "You had better hope that there are no landslides!\n");
    add_item(({"grasses", "grass", "ground", "field", "fields", "green grass",
            "yellowish grass", "yellow grass", "yellow-green grass",
            "vegetation","flower","wildflower","wildflowers","flowers"}),
        "Several patches of tall green grass filled with plenty of " +
        "beautiful wildflowers can be seen scattered all across the " +
        "mountainside.\n");
    add_item(({"field","fields","meadow","meadows"}),
        "The slopes of the mountains are broken by the occasional " +
        "small field or meadow, filled with green grass and colourful " +
        "wildflowers.\n");
    add_item(({"stream","streams"}),
        "You spot the occasional mountain stream in the distance, nestled " +
        "in amongst the grassy meadows. However, the trail does not " +
        "take you close enough to see them in greater detail.\n");
    add_item(({"tree","trees","grove","groves"}),
        "There are small clusters of trees growing all around you on " +
        "the rugged slopes of the mountains.\n");
}

/*
 * Function name:        set_items_brightroad
 * Description  :        Items added to wild rooms when you include the line
 *                       set_items_brightroad(); 
 *                       Use for rooms located on the Bright Road only
 */
public void
set_items_brightroad()
{
    add_item(({"road","path","bright road","highway","ground","down"}),
        "This road looks well maintained. The highway itself is made " +
        "of large white stones, split and cut into hexagonal shapes and " +
        "interlocked upon a raised surface. The paving stones are rounded, " +
        "sloping towards the white edgestones that frame the entire length " +
        "of the road. The entire Bright Road travels from Sparkle in the " +
        "north and through the Jade Forest before it reaches the wilderness " +
        "to the south.\n");
    add_item(({"stone","stones","paving stone","paving stones","white stone",
            "white stones"}),
        "These stones are hexagonal in shape and have been laid on a " +
        "raised surface which sits slightly above the grass on either " +
        "side of the road. The surface of the stones have been rounded so " +
        "that they slope away from the middle of the highway, down to " +
        "the white edgestones.\n");
    add_item(({"edgestone","edgestones","white edgestone","white edgestones"}),
        "The entire length of the Bright Road has rows of white stones " +
        "that mark the edge of the highway. The edgestones are also " +
        "carefully placed to help direct any runoff from the highway.\n");
    add_item(({"ditch","ditches","gutter","gutters"}),
        "There are occassional small ditches that act like gutters which " +
        "follow the Bright Road. It appears that they are simply here " +
        "to make the drainage more efficient.\n");
    add_item(({"shadow","shadows","dark shadow","dark shadows","dark"}),
        "The tall thick trees of the Jade Forest cast dark shadows " +
        "across the lands to the south, with only the straight white line " +
        "of the Bright Road dividing them.\n");
}

/*
 * Function name:        set_items_driver
 * Description  :        Items added to wild rooms when you include the line
 *                       set_items_driver(); 
 *                       Use for rooms located beside the Diamond River where
 *                       drinking is available
 */
public void
set_items_driver()
{
    add_item(({"river", "stream", "diamond river", "water", "waters"}),
        "The rushing waters of the Diamond River rush down from the " +
        "mountains which cover the horizon to the northwest, cross " +
        "under the bridge here running south, before turning east " +
        "and emptying out into the blue waters of the Pen Sea which " +
        "spreads out somewhere to the east. The water itself looks cool " +
        "and fresh, it would be a simple matter to bend down and take " +
        "a drink of water from the river.\n");
}

/*
 * Function name:        set_items_forest
 * Description  :        Items added to wild rooms when you include the line
 *                       set_items_forest(); 
 *                       Use for rooms located in the Jade Forest only
 */
public void
set_items_forest()
{
    add_item(({"forest","jade forest","trees","dark forest","jade",
            "wood","woods"}),
        "The dark shadows of the Jade forest huddle overhead as the " +
        "Bright Road attemps to cut through on its way south. The forest " +
        "has a bit of an unsavory reputation as tales of desperate bandits " +
        "ferocious ogres have always been linked there.\n");
    add_item(({"shadow","shadows","dark shadow","dark shadows","dark"}),
        "The dark shadows of the Jade Forest are oppressive and almost " +
        "overwhelming as they surround you here. You certainly get " +
        "the impression that it is much safer to stay on the white " +
        "stones of the highway that runs north and south through " +
        "the forest.\n");
}

/*
 * Function name:        set_items_moor
 * Description  :        Items added to wild rooms when you include the line
 *                       set_items_moor(); 
 *                       Use for rooms located on the moorlands
 */
public void
set_items_moor()
{
    add_item(({"moor","moors","moorland","fen","fens"}),
        "The gentle green foothills of the Grey Mountains turn into " +
        "soggy moorland as they flatten out to the east. There are " +
        "two bridges you can see that can take you across the river " +
        "to the heart of the moorlands.\n");
    add_item(({"mist","mists","fog","haze"}),
        "The land here is filled with fine mists that drift across the " +
        "moorlands, creating a fog that prevents you from seeing any " +
        "great distance\n");
    add_item(({"hill","hills"}),
        "Several low grassy hills ripple across the moors, causing " +
        "the stone path to weave its way east from the bridge.\n");
    add_item(({"tree","trees","grove","groves"}),
        "The land is mostly open, but on occasion, you can " +
        "see the occasional grove of trees growing here in the " +
        "moorlands, mostly wide limbed yews or bushy rowans with the " +
        "occasional shadow of a willow hiding in the mists.\n");
    add_item(({"path","stone path","small path","small stone path","trail"}),
        "This path has been made from hundreds of flat fieldstones which " +
        "have been laid atop the wet moorland.\n");
    add_item(({"willow","willows"}),
        "There are not too many trees growing on the moors, but you do " +
        "see the occasional willow growing nearby.\n");
    add_item(({"rowan","rowans"}),
        "Wide and bushy looking, you spot the occasional grove of " +
        "rowan trees growing on the low hills of the moor.\n");
    add_item(({"yew","yews"}),
        "With wide long limbs spread out as if to crawl across the moors, " +
        "you spot the occasional yew tree which grows here in the fens.\n");
    add_item(({"sparkle","town","city","village","port"}),
        "Somewhere over the moors, off to the south, lies Sparkle," +
        "the legendary port city which is the hub of the " +
        "Pen Sea. The town appears to be quite lively, as if it " +
        "never sleeps, a feeling which is only accented by the fact " +
        "that there appears to be an endless stream of ships which " +
        "are either arriving or departing from the great port.\n");
    add_item(({"mud","wetlands","ground","down"}),
        "The ground here is rather wet and muddy, save where you can " +
        "stand on the path of fieldstones.\n");
    add_item(({"horizon"}),
        "The fog is too heavy on the moors here to see very far in any " +
        "direction.\n");
    add_item(({"north horizon","northern horizon","north"}),
        "The fog is too heavy on the moors here to see very far in any " +
        "direction.\n");
    add_item(({"west horizon","western horizon","west"}),
        "The fog is too heavy on the moors here to see very far in any " +
        "direction.\n");
    add_item(({"east horizon","eastern horizon","east"}),
        "The fog is too heavy on the moors here to see very far in any " +
        "direction.\n");
    add_item(({"south horizon","southern horizon","south"}),
        "The fog is too heavy on the moors here to see very far in any " +
        "direction, however the town of Sparkle should be close by.\n");
    add_item(({"northeast horizon","northeastern horizon","northeast"}),
        "The fog is too heavy on the moors here to see very far in any " +
        "direction.\n");
    add_item(({"northwest horizon","northwestern horizon","northwest"}),
        "The fog is too heavy on the moors here to see very far in any " +
        "direction.\n");
    add_item(({"southeast horizon","southeastern horizon","southeast"}),
        "The fog is too heavy on the moors here to see very far in any " +
        "direction.\n");
    add_item(({"southwest horizon","southwestern horizon","southwest"}),
        "The fog is too heavy on the moors here to see very far in any " +
        "direction.\n");

}

/*
 * Function name:        do_relax
 * Description  :        Provides an emote to relax in the grass nearby
 * Returns      :        int 0 - Prompt for proper syntax
 *                       int 1 - Returns the emote
 */
public int
do_relax(string str)
{
    if(!strlen(str))
    {
        notify_fail("Relax where? In the grass perhaps?\n");
        return 0;
    }

    if (!parse_command(str, ({}),
        " [in] [on] [the] 'field' / 'grass'"))
    {
        notify_fail("Relax where? In the grass perhaps?\n");
        return 0;
    }
    write("You search around briefly to find a comfortable spot where you " +
        "can lie down in the grass and enjoy a peaceful, relaxing moment.\n");
    SAYBB(" lies down in the grass and takes a quiet break from the world.\n");
    return 1;
}
/* do_relax */

/*
 * Function name:        add_trees
 * Description  :        Allows for climbable trees to be added in a wild room
 */
public void
add_trees(int value)
{
    trees = value;
}
/* add_trees */

/*
 * Function name:        add_mountain
 * Description  :        Allows for a climbable mountain to be added 
 *                       into a wild room
 */
public void
add_mountain(int value)
{
    mountain = value;
}
/* add_mountain */

/*
 * Function name:        wild_climb_tree
 * Description  :        This code lets people hide in trees by adding a tree
 *                       shadow.
 * Thanks:               This code was created by Carnak
 */
public int
wild_climb_tree(string str)
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
    
    if (!(shadow = clone_object(OBJ_DIR + "tree_shadow.c")))
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
 * Returns      :        Climbable Trees or Mountains if present in the room
 */
public int
do_climb(string str)
{
    if (trees)
        if (wild_climb_tree(str))
            return 1;
    
    if (mountain)
        return 1;
    
    return climb_function(str);
}
/* do_climb */

/*
 * Function name:        do_pick
 * Description  :        Provides a chance for a mortal to pick a flower or
 *                       two from the ground. The flower picked has no resale
 *                       value. /d/Genesis/start/human/wild2/obj/wildflower.c
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
            flower = clone_object(WILD_DIR + "obj/wildflower");
            flower->move(this_player(), 1);
            write("You reach down to pick a colourful wildflower out of " +
                "the ground.\n");
            say(QCTNAME(TP) + " picks a colourful wildflower.\n");
            flowers_left = flowers_left -1;

        return 1;
}
/* do_pick */

/*
 * Function name:        set_herbs
 * Description  :        Makes all herbs in this list available to be found
 *                       when searching for herbs.
 *                       Must add set_herbs into wild rooms
 */
public void
set_herbs()
{
    set_up_herbs(({ "/d/Gondor/common/herbs/attanar",
                    "/d/Gondor/common/herbs/basil", 
                    "/d/Gondor/common/herbs/carrot", 
                    "/d/Gondor/common/herbs/chervil",
                    "/d/Gondor/common/herbs/garlic", 
                    "/d/Gondor/common/herbs/basil",
                    "/d/Gondor/common/herbs/blackberry", 
                    "/d/Gondor/common/herbs/blueberry",
                    "/d/Gondor/common/herbs/mint", 
                    "/d/Gondor/common/herbs/raspberry",
                    "/d/Gondor/common/herbs/oregano", 
                    "/d/Gondor/common/herbs/sage",
                    "/d/Gondor/common/herbs/savory", 
                    "/d/Gondor/common/herbs/thyme",
                    "/d/Gondor/common/herbs/marjoram", 
                    "/d/Gondor/common/herbs/marigold",
                     }),
                ({"ground","field"}), 5);
}

public void
init()
{
    ::init();
    add_action("do_relax","relax");
    add_action("do_relax","rest");
    add_action("do_pick","pick");
    add_action("do_climb","climb");
}





