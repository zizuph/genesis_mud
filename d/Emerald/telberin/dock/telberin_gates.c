/*
 *  /d/Emerald/telberin/dock/telberin_gates.c
 *
 *  This is the Main Gate of Telberin, which takes players into the
 *  city.
 *
 *  Copyright (c) August 2003, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/std/room";

#include <stdproperties.h>


/*
 * Function name:        create_emerald_room
 * Description  :        set up the room
 */
public void
create_emerald_room()
{
    set_short("before the gates of Telberin");
    set_em_long("You stand on a tall hillside before the vast gates"
      + " of the city of Telberin. A road runs up the hillside from"
      + " the south, where below in the distance the docks of"
      + " Telberin protrude from the shores of the Island into"
      + " the lake. The road takes a turn here, passing tall"
      + " grasses along its southern border before heading east"
      + " into the city through the vast archway of the main"
      + " gate.\n");

    add_item( ({ "portcullis" }),
        "A portcullis has been raised above the arch to allow"
      + " passage into the city.\n");
    add_item( ({ "arch", "vast arch", "archway", "great arch" }),
        "A great arch forms the gate of Telberin. A portcullis has"
       + " been lifted above it.\n");
    add_item( ({ "hill", "tall hill", "hillside", "tall hillside",
                 "hilltop", "western edge of the island" }),
        "The hill upon which you stand rises perhaps fifty feet"
      + " above the level of the lake which fills the view to"
      + " the west of the city. A road makes its way down to"
      + " the docks at the foot of the hill to the north. To"
      + " the south, tall grasses border its edge.\n");
    add_item( ({ "lake", "lake telberin", "telberin lake",
                 "water", "waters", "waters of the lake",
                 "clear water", "clear waters",
                 "waters of lake telberin",
                 "clear waters of lake telberin", "west" }),
        "The clear waters of Lake Telberin lie below this"
      + " hilltop, surrounding the island in all directions."
      + " A bridge spans the relatively short distance between"
      + " the shores of this island and the mainland which is"
      + " well within view to the west.\n");
    add_item( ({ "road", "street" }),
        "The road comes up the hill from the north, where far"
      + " below in that direction it meets the docks which"
      + " serve as transport to and from the Island. Tall grasses"
      + " run along the edge of the road directly to the south,"
      + " where the edge of the hilltop curves around to meet"
      + " the main gate of Telberin through which the road passes"
      + " as it turns to the east here.\n");
    add_item( ({ "grass", "grasses", "tall grass", "tall grasses",
                 "south", "edge of the road" }),
        "Grass has grown to the edge of the road south of"
      + " here where its significant height has obscured everything"
      + " below the hill in that direction.\n");
    add_item( ({ "dock", "docks", "dock of telberin", "telberin dock",
                 "docks of telberin", "telberin docks",
                 "main dock", "main docks", "base",
                 "base of the hill", "north", "foot of the hill" }),
        "The docks which have served Telberin for years lie at the"
      + " base of the hill to the north. Every so often, large ships"
      + " moore along its stretch where there is constant activity."
      + " A small pier runs north from the main dock.\n");
    add_item( ({ "pier", "small pier", "ferry" }),
        "The pier north of the main dock does not seem to be the"
      + " destination of any major traffic. Occasionally, a ferry"
      + " lands there before making its way north along the"
      + " lake.\n");
    add_item( ({ "ship", "ships", "large ship", "large ships" }),
        "A few large ships are moored along the dock below this"
      + " hill to the north. Occasionally, a ferry bound from Ceral"
      + " Isle makes its way into view from the south, pausing"
      + " at the dock to drop off and pick up passengers.\n");
    add_item( ({ "ceral isle" }),
        "Ceral Isle is not in view here. It is known to lie"
      + " at the far southern end of the lake. From there, it"
      + " is said that many ships run up and down the Telberin River"
      + " from the sea, bound for distant lands.\n");
    add_item( ({ "city", "telberin", "city of telberin",
                 "telberin city" }),
        "The city of Telberin covers nearly the entire island east"
      + " of here. Though you are aware of its great expanse, your"
      + " view of the city here is limited to the outside portions"
      + " of its western wall and the great main gate through which"
      + " the road runs directly to the east.\n");
    add_item( ({ "wall", "walls", "walls of the city", "city wall",
                 "city walls", "wall of the city", "wall of telberin",
                 "walls of telberin", "telberin wall", "telberin walls",
                 "great wall", "great walls", "massive wall",
                 "massive walls", "telberin" }),
        "The massive walls which border the city run along this"
      + " western edge of the island before curving gradually out"
      + " of view to the north and south. It is clear that a breach"
      + " of the Telberin defences would need to begin by tackling"
      + " this formidable obstacle. It runs forty feet from its"
      + " base to battlements which extend along its top. Guards"
      + " patrol constantly along its heights, especially here where"
      + " the main gate allows entry into Telberin.\n");
    add_item( ({ "guard", "guards" }),
        "Many guards watch this road from the heights of the wall"
      + " as well as the gate itself.\n");
    add_item( ({ "gate", "main gate", "gates", "main gates",
                 "gate of the city", "gates of the city",
                 "city gate", "city gates", "western gate",
                 "western gates", "gates of telberin", 
                 "gate of telberin", "telberin gate", "telberin gates",
                 "great gate", "great gates", "huge gate",
                 "huge gates" }),
        "The main gate which provides entry into Telberin looms over"
      + " the hilltop to the east, where the road passes through"
      + " into the city. A vast arch opens in the city wall, where"
      + " a portcullis is raised to allow passage. Guards stand in"
      + " rows beside the gates, checking the various wagons and"
      + " carts which roll constantly in and out of the city.\n");
    add_item( ({ "wagon", "wagons", "cart", "carts",
                 "wagons and carts" }),
        "The traffic is fairly regular along this road. Wagons"
      + " are loaded at the docks to the south, and make their way"
      + " up the hill to the gates of the city.\n");
    add_item( ({ "mainland", "mainland of emerald", "emerald" }),
        "The mainland of Emerald is not far from this island, and"
      + " connects via a large bridge which spans the waters.\n");
    add_item( ({ "bridge", "large bridge", "telberin bridge",
                 "burned bridge" }),
        "A large bridge connects this island to the mainland at"
      + " the base of this hill to the south. It looks as if the"
      + " bridge has been burned recently. A large section in the"
      + " middle has been utterly destroyed, and it is abandoned.\n");
    add_item( ({ "island" }),
        "The island upon which Telberin has been built is almost"
      + " completely filled by the breadth of the city itself.\n");
    add_item( ({ "sky", "up", "cloud", "clouds", "billowing cloud",
                 "billowing clouds" }),
        "Billowing clouds break up the stunning blue sky that shines"
      + " down over the island.\n");
    add_item( ({ "down", "ground", "floor" }),
        "The road at your feet is dusty and hard.\n");
    add_item( ({ "trail", "dusty trail", "dusty foot-trail",
                 "foot-trail" }),
        "Poking your head through the grasses, you spy a foot-trail"
      + " leading down to a secluded beach below this hilltop to"
      + " the south.\n");
    add_item( ({ "secluded beach" }),
        "Poking your head through the grasses, you peer upon a"
      + " secluded beach which lies below this hilltop to the south."
      + " It spreads out at the foot of the city walls, whose base"
      + " forms a barrier along the beach's northeastern border."
      + " The beach is not visible from the road unless one passes"
      + " these grasses which obscure it from view, and it looks"
      + " utterly secluded. Were it not for the foot-path which"
      + " leads up the hillside to the road, it would be easy to"
      + " think that the beach was never visited.\n");
    add_item( ({ "shore", "shores", "shores of the lake",
                 "beach", "beaches", "lakeshore",
                 "shore of the lake" }),
        "The lakeshore is not evenly visible here. To the north,"
      + " the shores are dominated by the docks which have been built"
      + " upon them. West of here, they arc around the hilltop until"
      + " they are lost from view to the south, where tall grasses"
      + " obscure visibility.\n");

    add_cmd_item( ({ "grass", "grasses", "tall grass",
                      "tall grasses" }),
                  ({ "search", "enter", "move" }),
        "You peer between the tall grasses to the south and discover"
      + " a foot-path leading down to a secluded beach which is"
      + " otherwise not visible from the road.\n");

    add_prop(ROOM_I_LIGHT, 9);


    add_exit("telberin_dock", "north");
    add_exit("hidden_beach", "south", 0, 1, 1);
    add_exit("/d/Emerald/telberin/west_gate", "east");
} /* create_emerald_room */
