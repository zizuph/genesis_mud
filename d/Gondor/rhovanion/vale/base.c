#include "../defs.h"

inherit RHOVANION_STD_DIR + "room";
inherit "/d/Gondor/common/lib/herbsearch";
inherit RHOVANION_DIR + "mirkwood/std/warning";
inherit "/d/Gondor/common/lib/room_tell";

#include <macros.h>

void set_items_vale();
void set_items_east();
void set_items_west();
void set_items_mirk();
void set_items_mist();
void set_items_river();
void set_items_oldroad();
void set_items_gate();
void set_items_ford();
void set_items_carrock();
void set_herbs_1();
void set_herbs_2();
void set_herbs_3();
void set_herbs_4();
void set_herbs_5();
void set_herbs_6();
void set_herbs_7();
void set_herbs_8();
void set_herbs_9();


void create_vale_room() 
{
}

nomask void create_rhovanion_room() 
{

    create_vale_room();


        add_tell("A gentle breeze ripples through the tall grasses, " +
            "causing them to bend and sway with each gust of wind.\n");
        add_tell("Far to the west, you see an eagle soaring around the " +
            "jagged peaks of the Misty Mountains.\n");
        add_tell("A swirling wind follows the Anduin river south through " +
            "the valley, causing the tall grasses to bend and sway.\n");
        add_tell("The dull roar of the Anduin echoes through the valley " +
            "as the rushing waters tumble past on their way south.\n");
        add_tell("A small flock of birds chase each other, swooping and " +
            "diving all across the vale.\n");
        add_tell("A gentle breeze ripples through the tall grasses, " +
            "causing them to bend and sway with each gust.\n");
        add_tell("Far to the west, you see an eagle soaring around the " +
            "jagged peaks of the Misty Mountains.\n");
        add_tell("A swirling wind follows the Anduin river south through " +
            "the valley, causing the tall grasses to bend and sway.\n");
        add_tell("The dull roar of the Anduin echoes through the valley " +
            "as the rushing waters tumble past on their way south.\n");
        add_tell("A large flock of birds chase each other, swooping and " +
            "diving all across the vale.\n");
        add_tell("A gentle breeze ripples through the tall grasses, " +
            "causing them to bend and sway with each gust.\n");
        add_tell("Far to the west, you see an eagle soaring around the " +
            "jagged peaks of the Misty Mountains.\n");
        add_tell("A swirling wind follows the Anduin river south through " +
            "the valley, causing the tall grasses to bend and sway.\n");
        add_tell("The dull roar of the Anduin echoes through the valley " +
            "as the rushing waters tumble past on their way south.\n");
        add_tell("A flock of birds chase each other, swooping and " +
            "diving all across the vale.\n");
        add_tell("Off in the distance, you see what appears to be a " +
            "bear wandering into Mirkwood forest.\n");
        add_tell("A small group of honeybees buzz around, landing on the " +
            "brightly coloured wildflowers.\n");
        add_tell("A handful of honeybees buzz around, landing on the " +
            "brightly coloured wildflowers.\n");
        add_tell("A small honeybee flies around your head, inspecting " +
            "you before settling on a blue wildflower.\n");
        add_tell("A little honeybee flies around your head, inspecting " +
            "you before settling on a yellow wildflower.\n");
        add_tell("A tiny honeybee flies around your head, inspecting " +
            "you before settling on a red wildflower.\n");
        add_tell("A large, silver fish jumps high out of the waters of " +
            "the Anduin, landing again with a loud splash.\n");
        add_tell("A large, brown fish jumps high out of the waters of " +
            "the Anduin, landing again with a loud splash.\n");
        add_tell("A small, silver fish jumps high out of the waters of " +
            "the Anduin, landing again with a loud splash.\n");
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
            "shelter in a nearby grove of fir trees.\n");
        add_tell("Dozens of tiny butterflies flutter across " +
            "the grassy fields in a parade of bright colours.\n");
        add_tell("A handful of tiny butterflies flutter across " +
            "the grassy fields in a parade of bright colours.\n");
        add_tell("A couple of tiny butterflies flutter across " +
            "the grassy fields in a parade of bright colours.\n");
        add_tell("A large deer, grazing in the fields looks up at you and " +
            "bounds away into Mirkwood forest.\n");
        add_tell("A young buck, grazing in the fields looks up at you and " +
            "bounds away into Mirkwood forest.\n");
        add_tell("The droning chirp of crickets echoes across the vale.\n");
        add_tell("The droning chirp of crickets echoes across the vale.\n");
        add_tell("The droning chirp of crickets echoes across the vale.\n");
        add_tell("The droning chirp of crickets echoes across the vale.\n");

        set_tell_time(random(220) + 70);
}

void
enter_inv(object ob, object from)
{
    start_room_tells();
    ::enter_inv(ob, from);
}

void
set_items_vale()
{
    add_item(({"river", "anduin", "bank", "banks", "waters", "great river"}),
        "You can see the rushing, grey waters of the mighty Anduin river " +
        "as it carves a path through the land, running southwards towards " +
        "the land of Gondor.\n");
    add_item(({"grasses", "grass", "ground", "field", "fields", "green grass",
            "yellowish grass", "yellow grass", "yellow-green grass"}),
        "The ground here is full of a tall, yellow-green grass which seems " +
        "to sway in the wind with every breeze which passes you by. The " +
        "fields seem to be filled with endless insects which buzz " +
        "around everywhere, often around the large clusters of wildflowers " +
        "which hide in the grass.\n");
    add_item(({"flower", "flowers", "wildflower", "wildflowers"}),
        "Scattered across the valley, brilliant hues of red, purple, blue " +
        "and orange are visible where clusters of wildflowers are nestled " +
        "in the tall grass.\n");
    add_item(({"insect", "insects"}),
        "The fields of the vale are filled with the endless, buzzing drone " +
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
        "Far off to the west, against the backdrop of the Misty Mountains, " +
        "you occassionally see an eagle circling high in the air.\n");
    add_item(({"swallow","swallows"}),
        "Every once in a while, you can see a small group of swallows " +
        "dipping and diving across the valley.\n");
    add_item(({"bird","birds"}),
        "This valley is full of life, including hundreds of birds which " +
        "keep the air alive with song, and fly from one grove of trees " +
        "to another in small flocks.\n");
    add_item(({"dragonfly","dragonflies"}),
        "There are many dragonflies zipping about, chasing down their " +
        "meals of the small, bothersome insects that constantly seem " +
        "to be in your face.\n");
    add_item(({"crickets","cricket", "grasshopper", "grasshoppers"}),
        "The constant chipring of crickets and grasshoppers drones in " +
        "your ears as you pass through these fields. You occasionally " +
        "spot some as they jump and fly around in the grass.\n");
    add_item(({"butterfly","butterflies"}),
        "Fluttering through the air, pushed along by the gentle breezes, " +
        "hundreds of butterflies drift across the valley in a dazzling " +
        "display of colours on parade.\n");
    add_item(({"bee", "bees", "honeybee", "honeybees"}),
        "Buzzing all around the vale are dozens of honeybees which drift " +
        "from one flower to the next, obviously collecting pollen.\n");
    add_item(({"valley", "vale", "vale of the anduin"}),
        "This valley cuts down deep into the earth, settling only as it " +
        "reaches the banks of the great river below. You spot the " +
        "occasional rocky outcropping, but each side of the valley " +
        "appears to be mostly covered with tall, yellow grass with " +
        "scattered groves of trees tossed about.\n");
    add_item(({"gondor", "south", "sea"}),
        "The river Anduin flows south from here, cutting through the " +
        "land before it eventually reaches the forests of Ithilien, in " +
        "the land of Gondor, and then continues on south where it " +
        "empties itself into the sea. \n");
    add_item(({"fir", "fir trees", "evergreens", "firs"}),
        "Scattered around the valley, several groups of fir trees have " +
        "sprouted up into small groves. Stretching tall up into the open " +
        "air, these evergreens could provide some shade and shelter from " +
        "the elements.\n");
    add_item(({"tree","trees"}),
        "You can see several small groves of trees scattered around " +
        "the valley, while to the east, the tall black oaks of Mirkwood " +
        "loom up in ominous silence.\n");
    add_item(({"oak", "oaks"}),
        "Small groves of oak trees are scattered across the vale, while " +
        "endless black oak trees fill the legendary Mirkwood forest.\n");
    add_item(({"elm", "elms"}),
        "Tall and slender, dozens of elm trees cast their shade across " +
        "the valley in small groves.\n");
    add_item(({"grove","groves"}),
        "There are dozens of groves of trees scattered around the valley. " +
        "Tall elms, wide firs and even mighty oaks gather in small " +
        "clusters, providing some shelter and shade in the vale.\n");
    add_item(({"outcropping", "rocks", "rocky outcropping"}),
        "Scattered across the valley are many rocky outcroppings, " +
        "which upon closer inspection actually appear to be massive " +
        "boulders, jagged and broken, strewn about in a random manner.\n");
    add_item(({"boulder", "broken boulders", "broken boulder", "boulders"}),
        "Dozens of massive boulders, jagged and broken, lay scattered " +
        "around the Vale of the Anduin, as if carelessly discarded by " +
        "some littering giant.\n");
    add_item(({"fish","silver fish", "brown fish"}),
        "You cannot see any fish right at this moment, but occasionally " +
        "you will see one jumping in the Anduin river.\n");
    add_item(({"snake","snakes", "yellow snake", "green snake"}),
        "Every now and then, you will spot a small grass snake as it " +
        "slithers across the fields in search of a meal.\n");
    add_item(({"bear","bears"}),
        "You cannot see a bear right at this moment, but being so close " +
        "to Mirkwood forest, you would not be entirely surprised to see " +
        "one from time to time.\n");
    add_item(({"deer","stag", "stags"}),
        "Ocassionaly you will see some deer grazing in the fields, yet any " +
        "time they feel you get too close, they jump up and dash far away.\n");
}
void
set_items_east()
{
    add_item(({"hills", "foothills", "rocks", "outcropping", "stone", "hill",
            "foothill", "stones", "rock"}),
        "Scattered around the valley, you spot the occasional stone " +
        "outcropping, especially across the river on the western bank " +
        "where rocky foothills begin their long march up towards the " +
        "snow-capped peaks of the Misty Mountains.\n");
    add_item(({"mountains", "misty mountains"}),
        "On the far side of the Anduin river, standing tall, barren " +
        "and grey, the Misty Mountains reach up towards the sky " +
        "far above, leaving you to feel small and insignificant down here " +
        "below. The peaks are all snow-capped, and often half-concealed " +
        "by the misty clouds which give the mountains their name.\n");
    add_item(({"cloud", "clouds", "mist", "peaks", "peak"}),
        "Swirling clouds of mist nestle around the peaks of the great " +
        "mountains which stand tall on the west side of the valley.\n");
    add_item(({"black oaks", "black oak", "forest", "mirkwood"}),
        "Close, perhaps too close for comfort, an endless mass of " +
        "tall, black trees jut forcefully up out of the ground to mark " +
        "the border of the legendary Mirkwood forest.\n");
}
void
set_items_west()
{
    add_item(({"hills", "foothills", "rocks", "outcropping", "stone", "hill",
            "foothill", "stones", "rock"}),
        "Scattered around the valley, you spot the occasional stone " +
        "outcropping, especially on this side of the Anduin river, " +
        "where the rocky foothills begin their long march up towards the " +
        "snow-capped peaks of the Misty Mountains.\n");
    add_item(({"mountains", "misty mountains"}),
        "Immediately before you, standing tall, barren and grey, the Misty " +
        "Mountains reach up towards the sky " +
        "far above, leaving you to feel small and insignificant down here " +
        "below. The peaks are all snow-capped, and often half-concealed " +
        "by the misty clouds which give the mountains their name.\n");
    add_item(({"cloud", "clouds", "mist", "peaks", "peak"}),
        "Swirling clouds of mist nestle around the peaks of the great " +
        "mountains which stand tall above you.\n");
    add_item(({"oaks", "oak", "forest", "mirkwood"}),
        "On the far side of the Anduin river, countless tall black " +
        "oak trees rise above the horizon in an endless mass, forming " +
        "the infamous Mirkwood forest.\n");
}
void
set_items_river()
{
    add_item(({"river", "anduin", "bank", "banks"}),
        "You are standing near the banks of the Anduin river, where the blue " +
        "water lazily drifts by in a slow, winding manner as it wanders " +
        "south towards the lands of Gondor.\n");
    add_item(({"grasses", "grass", "reed", "reeds"}),
        "In addition to the tall grasses which line the fields here, you " +
        "notice several shoots of tall, green reeds growing along the " +
        "side of the river. The reeds seem to collect in large bunches " +
        "where the ground turns into marsh.\n");
    add_item(({"marsh", "marshland"}),
        "In several places along the banks of the river, the water runs " +
        "shallow and slow enough to have made the ground more of a marsh " +
        "than anything else. Very often, this marshland is characterized " +
        "by collections of tall \n");
}
void
set_items_mist()
{
    add_item(({"mountains", "misty mountains"}),
        "You are standing at the very feet of the massive Misty Mountains. " +
        "From your vantage point here, you cannot even see their peaks, " +
        "as they appear immersed into the cloudy mist which crowns their " +
        "peaks. Unless you decide to take a strong interest in mountain " +
        "climbing, you will not be able to pass farther west here, you " +
        "would have to seek a pass through the mountains instead.\n");
}
void
set_items_mirk()
{
    add_item(({"oaks", "oak", "forest", "mirkwood"}),
        "A tall line of black trees seems to jump up out of the ground " +
        "immediately east of here, casting dark and gloomy shadows out " +
        "towards the valley as they lurk menacingly, warning stray " +
        "travellers to stay away. Long twisted branches, each covered " +
        "by hundreds of dark green leaves, seem to watch the vale of " +
        "the Anduin carefully, waiting for an unwary traveller to " +
        "trespass beneath their boughs.\n");
    add_item(({"shadow", "shadows"}),
        "Mirkwood forest, which looms menacingly to the east, appears " +
        "to be full of dark, ominous shadows. The shadows stretch out " +
        "in their inky blackness, grasping like claws that only shrink " +
        "away from the light of the sun.\n");
    add_item(({"branch", "branches", "bough", "boughs"}),
        "Gnarled and twisted, the black branches of these mighty oaks " +
        "appear to reach out in a grotesque manner, as if searching " +
        "for some unsuspecting prey to gather in a deadly and fatal " +
        "embrace.\n");
    add_item(({"leaf", "leaves", "green leaf", "green leaves"}),
        "Thousands of dark, green oak leaves cover the branches of the " +
        "trees which mark the border of Mirkwood forest. Somewhat " +
        "surprisingly, few of them have fallen to the ground, as most " +
        "of the leaves still cling tightly to the black branches, allowing " +
        "small pockets of shadow and gloom to peek out from behind their " +
        "shelter.\n");
}
void
set_items_oldroad()
{
    add_item(({"road", "old road"}),
        "You can make out an old road cutting through the grasses of the " +
        "vale just south of you. The road seems to stretch from a pass " +
        "in the mountains to the west, across a wide ford across the " +
        "Anduin river, and then continuing east right into the dark " +
        "gloom of Mirkwood forest.\n");
    add_item(({"ford", "ford"}),
        "You can see a wide ford running across the rippling shallows of the " +
        "wild waters of the great Anduin river. The ford is clearly marked " +
        "by an old road which winds away from the crossing, climbing the " +
        "rugged hills which cover both sides of the valley.\n");
    add_item(({"pass", "mountain pass"}),
        "The old road seems to wind out of an opening in the rocky crags " +
        "of the fabled Misty Mountains. The opening appears to be a " +
        "mountain pass which could provide passage to the " +
        "west for an experienced traveller.\n");
}
void
set_items_gate()
{
    add_item(({"two trees", "oak trees", "trees", "gate", "forest gate"}),
        "While the dark forest of Mirkwood looms before you, two particular " +
        "trees stand out before you. Covered in lichen and twisting ivy, " +
        "these two trees lean towards each other high above your head, " +
        "forming a great arch that hovers over the elf path. This is the " +
        "forest gate, an entrance into the infamous Mirkwood forest.\n");
    add_item(({"ivy", "vine", "vines", "bark", "lichen"}),
        "Dozens of strangling vines of ivy in addition to large " +
        "patches of lichen, cover the bark of the " +
        "great oak trees which form the forest gate.\n");
    add_item(({"elf path", "path"}),
        "A narrow path is visible on the ground here, leading beneath an " +
        "arch of two ancient oak trees, it leads into the murky depths " +
        "of Mirkwood forest.\n");
}
void
set_items_ford()
{
    add_item(({"ford", "old ford", "crossing"}),
        "The Anduin river seems to spread out wide near you here, " +
        "allowing a ford to cross the shallows. On either side of the " +
        "ford, an old road wanders up the side of the vale, trailing " +
        "off towards Mirkwood to the east and the Misty Mountains to " +
        "the west.\n");
}
void
set_items_carrock()
{
    add_item(({"rock", "carrock", "eyot", "island"}),
        "In the middle of the Anduin stands an eyot composed of a massive " +
        "rock which thrusts proudly up into the air. The rushing waters " +
        "are cloven in two as they tumble past the island, revealing " +
        "only a series of flat stones which rise just above the surface " +
        "of the river between the rock and the eastern shore.\n");
    add_item(({"stones", "flat stones", "path", "stone path"}),
        "These black stones are rather flat, and rise up just about the " +
        "surface of the water. There seems to be a line of them, winding " +
        "a path from the eastern bank of the river to the deep " +
        "shadows cast along the side of the massive rock which juts up " +
        "out of the Anduin.\n");
    add_item(({"shadow", "shadows", "cave"}),
        "It looks like these shadows delve straight into the rock, almost " +
        "like a cave tunneling inside.\n");
}

void
init()
{
::init();
add_action("do_relax","relax");
}
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







