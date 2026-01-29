/* 
 *
 *  Under the humpbacked bridge,  Varian - October 5, 2015
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/std/room";
inherit "/d/Gondor/common/lib/drink_water.c";
inherit "/d/Gondor/common/lib/room_tell";

#include "wild.h"
#include <stdproperties.h>
#include <macros.h>
#include <state_desc.h>

public void drink_message(string from);
int do_pull(string str);
int do_climb(string str);

void
create_room()
{
    set_short("Under the bridge");
    set_long("You are standing on the western bank of the Diamond River, " +
        "beneath an old stone bridge which arches overhead. Scattered " +
        "pebbles and rocks hide amongst a collection of rushes, lilies and " +
        "old leaves, lining the riverbank. A small dirt path, almost hidden, " +
        "runs north and south along the river before winding out into the " +
        "green, grassy fields which lay beyond. A cool breeze seems to drift " +
        "along the river, brushing past you and bringing the fresh aroma " +
        "of wildflowers. The buzzing, clicking and chirping of the insects " +
        "from the fields seems to fill your ears. Meanwhile, up above, you " +
        "can hear travellers crossing the bridge which hides them from view, " +
        "moving along the road to or from the town of Sparkle.\n");

    add_exit(THIS_DIR + "riv1","north");
    add_exit(THIS_DIR + "driv1", "south");


    add_item(({"bridge", "humbacked bridge", "old bridge", "stone bridge"}),
             "This wide, stone bridge appears to be fairly old, yet is " +
             "still in good repair. It arches high above your head here " +
             "as it jumps across the rushing waters of the Diamond River. " +
             "The bridge primarily appears to be constructed from large " +
             "fieldstones set into mortar.\n");
    add_item(({"stone", "stones", "fieldstone", "fieldstones"}),
             "There are dozens of fieldstones set into the side of the " +
             "bridge, all packed tightly together and set in a dark grey " +
             "mortar. Most of the stones are small, but some are almost " +
             "as large as you!\n");
    add_item(({"river", "stream", "diamond river", "water", "waters"}),
             "The rushing waters of the Diamond River rush down from the " +
             "mountains which cover the horizon to the northwest, cross " +
             "under the bridge here running south, before turning east " +
             "and emptying out into the blue waters of the Pen Sea which " +
             "spreads out somewhere to the east. The water itself looks cool " +
             "and fresh, it would be a simple matter to bend down and take " +
             "a drink of water from the river.\n");
    add_item(({"bank", "banks", "west bank", "riverbank","riverbanks",
                "western bank"}),
             "You are on the western bank of the Diamond River, just " +
             "outside of the city of Sparkle. A small path trails away " +
             "along the river, winding through lush green fields.\n");
    add_item(({"east bank", "eastern bank"}),
             "You look across the Diamond River to see that the fields " +
             "look just as green and grassy as the west side.\n");
    add_item(({"field", "fields", "hill", "hills"}),
             "Wild fields of tall green grass roll over gentle hills all " +
             "around you. The fields are unbroken save for the Diamond " +
             "River and the dusty road which crosses it here above " +
             "you, at the bridge.\n");
    add_item(({"grass", "green grass", "tall grass"}),
             "The grass is tall and green, growing abundantly enough to " +
             "cover the fields all around you, all the way down to the " +
             "riverbank.\n");
    add_item(({"road", "dusty road", "dust"}),
             "You cannot see the road from here, but it passes along the " +
             "bridge above your head.\n");
    add_item(({"small stone", "small stones", "smaller stones",
                "smaller stone", "small fieldstone", "smaller fieldstone", 
                "small fieldstones", "smaller fieldstones"}),
             "Some of these fieldstones are larger, and some are smaller, " +
             "yet all of them appear to be well set into the bridge. Even " +
             "reaching out in an attempt to wiggle the smallest of stones " +
             "proves that the bridge is extremely solid.\n");
    add_item(({"mortar", "cement"}),
             "The grey mortar which cements the stones of the bridge into " +
             "place appears to be in very good repair, especially for a " +
             "bridge this old! It is obvious that someone has taken " +
             "especially good care of it.\n");
    add_item(({"mountain", "mountains"}),
             "Stretching across the western horizon there is an endless " +
             "line of jagged, snow-capped mountain peaks as they pierce the " +
             "sky. These are the Grey Mountains, a legendary fixture in the " +
             "countryside surrounding Sparkle. It is said that the " +
             "traditional homeland of the dwarves, Dwarfheim is hidden " +
             "somewhere to the north, while somewhere in the south, goblins " +
             "have tunneled deep into the heart of the mountains, " +
             "establishing a realm of their own.\n");
    add_item(({"sea", "pen sea"}),
             "If you were not down beside the river, you would be able to " +
             "see the endless stretch of the Pen Sea covering the entire " +
             "eastern horizon.\n");
    add_item(({"large stone", "large stones", "larger stones",
                "larger stone", "large fieldstone", "larger fieldstone", 
                "large fieldstones", "larger fieldstones"}),
             "Some of these fieldstones are huge, even to the point where " +
             "they are almost as big as you! In fact, one large brown " +
             "fieldstone almost looks like it could be a door.\n");
    add_item(({"sparkle", "town", "city", "village", "port"}),
             "Somewhere to the east, not too far away, is the legendary " +
             "port of Sparkle. It is said that from the docks in Sparkle, " +
             "you can find a ship to any land, no matter how far or remote.\n");
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
    add_item(({"path", "dirt path", "small path", "winding path"}),
             "There is a small winding path here, following the western " +
             "bank of the river to both the north and the south. Despite " +
             "being well hidden, it appears to have seen some recent use.\n");
    add_item(({"people", "traveller", "travellers"}),
             "You cannot see them, but you hear the passage of the " +
             "occasional traveller as they pass along the bridge overhead.\n");
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
    add_item(({"brown stone", "brown fieldstone"}),
             "This brown fieldstone is huge, and placed right in the " +
             "middle of the bridge. It is so tall and wide that it almost " +
             "looks like a door.\n");
    add_item(({"door", "stone door"}),
             "Well, this is not really a door. It is just a very large " +
             "fieldstone that has been set into the bridge.\n");
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
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

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
        "Diamond river as it tumbles past.\n");
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
    add_action("do_pull","pull");
    add_action("do_climb","climb");
}

public void
drink_message(string from)
{
    write("You bend down and cup your hands to drink a mouthful of water from " 
        + "the river. It feels cool and refreshing going down your throat.\n");
    say(QCTNAME(TP) + " bends down to drink some water from the river.\n");
}


int
do_pull(string str)
{
if(!str)
    {
        write("Pull what?\n");
        return 1;
    }

    if((str != "large stone") && 
        (str != "larger stone") && (str != "larger fieldstone") 
        && (str != "large fieldstone") && (str != "brown fieldstone")
        && (str != "brown stone"))
    { 
        write("Pull what?\n");
        return 1;
    }
    write("You pull hard on the edge of the large, brown fieldstone and open " +
        "a hidden door! You quickly slip inside. If you needed to go back to the " +
        "river, you should be able to go 'out'.\n");
    SAYBB(" has apparently gone somewhere, but you did you not see where.");
    TP->move_living("M",THIS_DIR + "ban2",1,0);
    SAYBB(" slips inside from the hidden door.");
    return 1;
}

public int
do_climb(string str)
{
    if(!strlen(str))
    {
        notify_fail("Climb where?\n");
        return 0;
    }

    if (!parse_command(str, ({}),
        " [up] [above] [over] [the] [humpbacked]"
      + " [hump-backed] [[north] [northern] [on] [top]"
      + " [hump] [backed] [back] [humpback] [hump-back]"
      + " [stone] 'bridge' / 'rail'") &&
        str != "up")
    {
        notify_fail("Where do you wish to climb?\n");
        return 0;
    }

    write("You climb up back to the top of the bridge.\n");
    SAYBB(" climbs over the side of the bridge");
    TP->move_living("M",WILD_DIR + "hump",1,0);
    SAYBB(" arrives climbing up over the northern rail of the bridge.");
    return 1;
} /* do_climb */

public string
do_search(object pl, string arg)
{
    if (member_array(arg,
        ({ "large stone", 
           "larger stone", 
           "large fieldstone", 
           "larger fieldstone", 
           "brown stone", 
           "brown fieldstone", 
           "large stones", 
           "larger stones", 
           "large fieldstones", 
           "larger fieldstones",}) ) == -1)
    {
        return "Your search reveals nothing special.\n";
    }

    return "To your surprise, This brown fieldstone might actually be " +
        "a door! You think you could probably pull it open.\n";

}

