/* 
 *
 *   Varian - October 5, 2015
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/d/Gondor/common/lib/drink_water.c";
inherit "/d/Shire/lib/herbsearch";
inherit "/d/Gondor/common/lib/room_tell";

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>

public void drink_message(string from);

void
create_room()
{
    set_short("River path");
    set_long("You are walking along a small dirt path, which winds its way " +
        "along the rushing waters of the Diamond River. Green fields of tall " +
        "grass, sprinkled liberally with a rainbow of colourful " +
        "wildflowers, cover the gently rolling hills which rise around you. " +
        "The river flows down from the jagged heights of the Grey Mountains " +
        "which march up to the sky across the western horizon. Flowing past " +
        "you here, it continues south where it gurgles under an old bridge, " +
        "humpbacked and made of stone, before trailing away towards the " +
        "sparkling blue of the Pen Sea which spreads across the eastern " +
        "horizon. Off somewhere to the southeast, is the famous town " +
        "of Sparkle, the legendary port which connects to even the most " +
        "remote corners of the world.\n");

    add_exit(THIS_DIR + "ban1","south");
    add_exit(THIS_DIR + "riv2","north");


    add_item(({"bridge", "humbacked bridge", "old bridge", "stone bridge"}),
             "There is a stone bridge, humpbacked and rather old, spanning " +
             "the river just to the south. The path you are walking on " +
             "seems to lead there.\n");
    add_item(({"horizon", "horizons"}),
             "Jagged and snow-capped, the massive peaks of the Grey " +
             "Mountains dominate the western horizon, while to the east, " +
             "the sparkling blue waters of the Pen Sea seem to float " +
             "endlessly. In between, gentle hills of green grass roll " +
             "along the Diamond River, providing an escort on its journey to " +
             "the sea.\n");
    add_item(({"stone", "stones"}),
             "The entire bridge is made of stone, but you cannot see any " +
             "further details from here.\n");
    add_item(({"river", "stream", "diamond river"}),
             "The rushing waters of the Diamond River rush down from the " +
             "mountains which cover the horizon to the northwest, running " +
             "south past you here, before turning east " +
             "and emptying out into the blue waters of the Pen Sea which " +
             "spreads out to the east. The water itself looks cool and " +
             "fresh, a quick drink would probably taste great right now!\n");
    add_item(({"water", "waters"}),
             "You can the waters of the Diamond River as they rush along " +
             "beneath the old stone bridge as well as the shining blue water " +
             "of the Pen Sea as it sparkles in the distance across the " +
             "eastern horizon.\n");
    add_item(({"field", "fields", "hill", "hills"}),
             "Wild fields of tall green grass roll over gentle hills all " +
             "around you. Speckled with hundreds of wildflowers, the fields " +
             "have been splashed with a bright myriad of colours in every " +
             "direction. Endless insects buzz and drone around you, " +
             "flying in every direction.\n");
    add_item(({"bank", "banks", "west bank", "riverbank","riverbanks",
                "western bank"}),
             "You are on the western bank of the Diamond River, just " +
             "outside of the city of Sparkle. A small path trails away " +
             "along the river, winding through lush green fields.\n");
    add_item(({"east bank", "eastern bank"}),
             "You look across the Diamond River to see that the fields " +
             "look just as green and grassy as the west side.\n");
    add_item(({"grass", "green grass", "tall grass"}),
             "The grass is tall and green, growing abundantly enough to " +
             "cover the fields all around you with brilliant splashes of " +
             "colour from hundreds of wildflowers are sprinkled all around.\n");
    add_item(({"rushes", "lilies", "lily", "bullrushes", "rush", "bullrush"}),
             "A collection of bullrushes and lilies line the bank of the " +
             "river, hiding a collection of rocks and leaves.\n");
    add_item(({"leaves", "old leaves", "leaf", "old leaf", "cluster",
                "clusters"}),
             "As often happens, the river has deposited numerous clusters " +
             "of leaves along the bank. For the most part, the leaves have " +
             "found themselves caught up in the collection of bullrushes " +
             "and lilies that grow here.\n");
    add_item(({"pebble", "pebbles", "rock", "rocks"}),
             "There are dozens of smooth rocks and pebbles washed up along " +
             "the riverbank. For the most part, they seem to be hiding " +
             "in and amongst clusters of old leaves and the tall bullrushes " +
             "and lilies which grow here.\n");
    add_item(({"path", "dirt path", "small path", "winding path",
                "hidden path"}),
             "There is a small winding path here, following the western " +
             "bank of the river to both the north and the south. Despite " +
             "being well hidden, it appears to have seen some recent use.\n");
    add_item(({"mountain", "mountains"}),
             "Stretching across the western horizon you can see an endless " +
             "line of jagged, snow-capped mountain peaks as they pierce the " +
             "sky. These are the Grey Mountains, a legendary fixture in the " +
             "countryside surrounding Sparkle. It is said that the " +
             "traditional homeland of the dwarves, Dwarfheim is hidden " +
             "somewhere to the north, while somewhere in the south, goblins " +
             "have tunneled deep into the heart of the mountains, " +
             "establishing a realm of their own.\n");
    add_item(({"sea", "pen sea"}),
             "Spreading out to the east, farther than the eye can see, is " +
             "the Pen Sea. Nearby, to the east, you can see the famous " +
             "port of Sparkle, a major hub of activity with a constant " +
             "stream of ships arriving and departing from even the most " +
             "remote corners of the world.\n");
    add_item(({"sparkle", "town", "city", "village", "port"}),
             "Somewhere to the east, not too far away, is the legendary " +
             "port of Sparkle. It is said that from the docks in Sparkle, " +
             "you can find a ship to any land, no matter how far or remote.\n");
    add_item(({"flower", "wildflower", "flowers", "wildflowers"}),
             "Out in the distance, hidden in the tall, green grass, " +
             "wildflowers of every colour are sprinkled across the " +
             "hills and fields.\n");
    add_item(({"insect", "insects", "flies", "fly", "cricket", "crickets", 
                "grasshopper", "grasshoppers"}),
             "Hordes of buzzing flies, chirping crickets and jumping " +
             "grasshoppers fill the fields around you, making it clear " +
             "that you have left the city behind.\n");
    add_item(({"breeze", "wind", "cool breeze"}),
             "You cannot see the breeze of course, but you notice as the " +
             "rushes and grasses bend and sway in its passage.\n");
    add_item(({"up", "sky", "above"}),
             "Several white fluffy clouds lazily drift across the sky, " +
             "occasionally covering the bright rays of the sun.\n");
    add_item(({"cloud", "clouds", "sun"}),
             "There are many large clouds floating across the sky, often " +
             "obscuring the warmth of the bright yellow sun.\n");
    add_item(({"ground", "down"}),
             "Looking down, you can see the small dirt path that hugs " +
             "the riverbank.\n");


    set_drink_from(({"stream", "river", "diamond river"}));

    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_std_herbs("river", 6);
    add_tell("A warm breeze drifts past you, bringing the fresh smell " +
        "of grass and wildflowers.\n");
    add_tell("A bright orange butterfly flutters past you.\n");
    add_tell("The droning buzz of insects echoes around you.\n");
    add_tell("You hear the repetitive sound of crickets chirping in the " +
        "fields around you.\n");
    add_tell("A large silver fish jumps in the river with a loud splash.\n");
    add_tell("You are suddenly bombarded by a cloud of black flies buzzing " +
        "around your head.\n");
    add_tell("Two swallows chase each other across the fields, swooping " +
        "and diving.\n");
    add_tell("The long grass sways and bends in the warm breeze that " +
        "drifts past.\n");
    add_tell("The loud croaking of frogs echoes from the riverbank.\n");
    add_tell("A small yellow snake slithers across the path towards " +
        "the river.\n");
    add_tell("A majestic hawk floats in the air high above, drifting " +
        "around in a lazy circle before diving down into the fields.\n");
    add_tell("A brown grasshopper flies in front of you, jumping across " +
        "the path.\n");
    add_tell("A small white cloud casts a shadow as it drifts in front " +
        "of the sun.\n");
    add_tell("A brown rabbit hops through the grassy fields.\n");
    add_tell("You notice a small green frog jumping into the rushes.\n");
    add_tell("A blue dragonfly zips past, chasing down some insects in " +
        "search of a meal.\n");
    add_tell("A gentle gurgle comes from the rushing waters of the " +
        "Diamond River as it tumbles past.\n");
    add_tell("A tiny brown mouse scurries past, quickly hidden by the " +
        "tall grass.\n");

    set_tell_time(random(220) + 70);
    reset_room();
}

void
enter_inv(object ob, object from)
{
    start_room_tells();
    ::enter_inv(ob, from);
}

void

init()
{
    ::init();
    init_drink();
}

public void
drink_message(string from)
{
    write("You bend down, cup your hands and drink a mouthful of water from " +
        "the river. It feels cool and refreshing going down your throat.\n");
    say(QCTNAME(TP) + " bends down to drink some water from the river.\n");
}
