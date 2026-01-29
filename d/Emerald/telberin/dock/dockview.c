/*
 *  /d/Emerald/telberin/dock/dockview.c
 *
 *  This module adds some good descriptions for the docks.
 *
 *  Created August 2007 by Cooper Sherry (Gorboth)
 */

/*
 * Function name:        add_dock_stuff
 * Description  :        To conserve filespace, we'll make this function
 *                       available so other rooms can use it too.
 */
public void
add_dock_stuff()
{
    this_object()->try_item( ({ "cargo", "barrel", "barrels", "crate", "crates",
                 "crates and barrels", "barrels and crates" }),
        "Barrels and crates make their way off the ships onto the"
      + " docks where they sit in rows waiting to be loaded and"
      + " taken into the city.\n");
    this_object()->try_item( ({ "dock", "docks", "dock of telberin",
                 "docks of telberin", "telberin dock", "telberin docks",
                 "main dock", "main docks" }),
        "These docks look well constructed, and stand tall above the"
      + " waters of the lake. A number of ships are moored along"
      + " the length of the dock, where occasionally elves move to"
      + " and fro loading or unloading cargo. Where the docks"
      + " meet the mainland, a road runs south up a hill. North of"
      + " the main dock, a pier runs out into the waters of the"
      + " lake.\n");
    this_object()->try_item( ({ "shore", "shores", "lakeshore", "shores of the lake",
                 "shore of the lake" }),
        "The shores of the lake travel around the island south and"
      + " east of here until they are lost from view due to the"
      + " contour of their path.\n");
    this_object()->try_item( ({ "island" }),
        "The island which extends in all directions to the south,"
      + " though very large, is covered almost completely by the"
      + " city of Telberin, whose walls wrap around the rocky"
      + " surfaces.\n");
    this_object()->try_item( ({ "ship", "ships" }),
        "A few ship are moored along the dock. Some are clearly"
      + " cargo ships, while others have, perhaps, a more military"
      + " purpose.\n");
    this_object()->try_item( ({ "road", "hill", "hillside", "slope", "south" }),
        "South of here, a road travels up the slope of a hill"
      + " toward the main gates of Telberin which lie at its"
      + " top.\n");
    this_object()->try_item( ({ "gate", "gates", "main gate", "main gates",
                 "main gates of telberin", "gates of telberin",
                 "main gate of telberin", "gate of telberin" }),
        "The gates of Telberin are visible in the distance at"
      + " the top of a hill. From here, you can not make out"
      + " much detail.\n");
    this_object()->try_item( ({ "telberin", "city", "city of telberin",
                 "telberin city" }),
        "Telberin, fairest jewel of all Emerald, rises majestically"
      + " from the shores of the lake, crowning the rocky slopes of"
      + " the island with its pearlescent towers and spires. Despite"
      + " the damage that certain portions of the city seem to have"
      + " sustained, there is no mistake - this is a major capitol"
      + " of great influence and wealth.\n");
    this_object()->try_item( ({ "tower", "towers", "spire", "spires",
                 "pearlescent tower", "pearlescent towers",
                 "pearlescent towers and spires" }),
        "The city is a wonder to behold. The eye is drawn up along"
      + " the length of miracle pillars and spires which seem to"
      + " reach impossibly into the sky.\n");
    this_object()->try_item( ({ "damage", "broken towers", "broken tower",
                 "burned building", "burned buildings" }),
        "Telberin seems to have suffered some form of calamity"
      + " recently. Large sections of the city are filled with"
      + " burned buildings and broken towers, almost as if a"
      + " terrible fire, or successful raid had occurred.\n");
    this_object()->try_item( ({ "pier", "small pier", "north" }),
        "A small pier runs off from the main dock into the lake"
      + " to the north.\n");
    this_object()->try_item( ({ "lake", "lake telberin", "telberin lake",
                 "water", "waters", "waters of the lake" }),
        "Lake Telberin surrounds this island in all directions,"
      + " its crystal form dazzlingly beautiful in the bright"
      + " light. A bridge spans the waters to the west, travelling"
      + " over the lake to the mainland.\n");
    this_object()->try_item( ({ "mainland", "mainland of Emerald" }),
        "The mainland of Emerald is not too far to the west, over"
      + " the narrow body of the lake which runs between it and"
      + " this island.\n");
    this_object()->try_item( ({ "bridge", "large bridge", "burned bridge" }),
        "A bridge connects this island to the mainland to the"
      + " west, crossing over the waters of the lake. It appears"
      + " to have been burned and partially destroyed. Its entire"
      + " middle section is missing, and it is completely"
      + " abandoned.\n");
    this_object()->try_item( ({ "sky", "up", "cloud", "clouds",
                 "billowing cloud", "billowing clouds" }),
        "The sky above is filled with billowing clouds which"
      + " slowly drift over the city.\n");
    this_object()->try_item( ({ "down", "ground", "floor" }),
        "The dock is firmly grounded beneath your feet.\n");
} /* add_dock_stuff */