inherit "/d/Emerald/std/room";

void
create_outpost_room()
{
    set_short("Outpost Room");
    set_long("A room in the outpost.\n");
}

nomask void
create_emerald_room()
{
    create_outpost_room();
}


/* 
 * Function name:        add_lakeview
 * Description  :        items appropriate from outside the fort itself
 *                       or from towers
 */
public void
add_lakeview()
{
    try_item( ({ "dock", "pier", "docks" }),
        "A dock is visible in the distance to the west at the end"
      + " of a path which runs along the lakeshore.\n");
    try_item( ({ "path", "trail" }),
        "A path runs along the lakeshore, connecting the outpost"
      + " with a dock which is visible in the distance to the west.\n");
    try_item( ({ "mountain", "mountains", "peak", "peaks",
                 "blackwall mountains" }),
        "To the north, the shapes of the Blackwall Mountains loom"
      + " above the horizon, towering over the trees of the forest"
      + " which separate these shores from their jagged slopes.\n");
    try_item( ({ "forest", "tree", "trees", "woods",
                 "trees of the forest" }),
        "A great forest runs down from the feet of the Blackwall"
      + " Mountains to crowd up against the shores of the lake."
      + " The trees near to the outpost have been cleared away and"
      + " used as timber in the construction of this fortress.\n");
    try_item( ({ "lake", "lake telberin", "telberin lake",
                 "water", "waters of the lake", "waters" }),
        "The waters of Lake Telberin spread out before the fortress,"
      + " travelling to the edge of sight as one gazes southward.\n");
} /* add_lakeview */


/*
 * Function name:        add_outpost_items
 * Description  :        items appropriate for the outside rooms
 *                       whether within our outside of the fort
 */
public void
add_outpost_items()
{
    try_item( ({ "outpost", "large outpost", "fortress", "building",
                 "fort", "structure", "large structure" }),
        "Looking over the outpost, you get the feeling that much"
      + " hardship has been dealt to those who have sought to defend"
      + " it. Large sections of the thick logs which comprise the"
      + " forty foot walls have been badly burned. Of the four guard"
      + " towers which rise from each corner of the fortress, one has"
      + " been almost completely gutted by fire, now standing as little"
      + " more than a blackened shell. The gates of the outpost have"
      + " been smashed and hang uncertainly on their holdings.\n");
    try_item( ({ "log", "logs", "wood", "thick logs", "timbers",
                 "timber", "wall", "walls", "walls of the outpost",
                 "wall of the outpost", "outpost wall", "outpost walls",
                 "wall of the fortress", "walls of the fotress",
                 "fortress wall", "fortress walls" }),
        "The logs which form the nearly forty foot walls of this outpost are mighty"
      + " timbers indeed. The bark of the trees still clings to"
      + " the surface of many of the logs, though much has been"
      + " peeled away by the fires which have done so much damage"
      + " to this fort.\n");
    try_item( ({ "bark" }),
        "The bark is thick in places, though parts of the logs"
      + " have been stripped either by dragging or in the process"
      + " of shearing away the many limbs of the tree.\n");
    try_item( ({ "damage", "destruction", "burns", "charring",
                 "burned areas", "burned logs", "damaged areas",
                 "damaged area" }),
        "Heavy damage has been inflicted upon this outpost. Signs"
      + " of fire are present in numerous places along the walls,"
      + " and one of the guard towers is almost entirely destroyed.\n");
    try_item( ({ "tower", "towers", "watchtower", "watch tower",
                 "guard tower", "guard towers", "watch towers",
                 "watchtowers", "four guard towers" }),
        "Guard towers rise from each of the four corners of the"
      + " fortress. They are enclosed structures with small windows"
      + " which look down from the battlements, presumably to"
      + " allow archers a clear shot upon any would-be invading"
      + " force. The northeastern tower looks to have been almost"
      + " entirely destroyed.\n");
    try_item( ({ "northeast tower", "northeastern tower", "shell",
                 "blackened shell", "destroyed tower", "ruined tower" }),
        "The northeastern tower has nearly been burned down. Its"
      + " charred remains still rise above the walls of the"
      + " fortress, but offer no protection whatsoever to any"
      + " archer that would care to man that position.\n");
    try_item( ({ "ground", "down", "floor", "shore", "lakeshore",
                 "shore of the lake", "lake shore", "shores of the lake",
                 "north shore", "northern shore", "northern shores",
                 "north shores", "northern shores of the lake",
                 "northern shore of the lake", "north shore of the lake",
                 "north shores of the lake" }),
        "The ground here is filled with debris and charred remains"
      + " from the raids that have taken place on this outpost.\n");
    try_item( ({ "debris", "remains", "charred remains" }),
        "Debris are littered along the walls of the outpost,"
      + " particularly in places where fire has caused great"
      + " damage to the logs which form the walls of the structure.\n");
    try_item( ({ "sky", "up" }),
        "The sky is clear and windy along the lakeshore.\n");
    try_item( ({ "band", "bands", "iron bands", "holdings" }),
        "Iron bands are clasped to the logs which comprise the"
      + " ruined gates of this outpost. Many of them have been ripped"
      + " from the logs they are meant to support.\n");
    try_item( ({ "hinge", "hinges" }),
        "The hinges of the gates have been badly bent away from the"
      + " logs they are meant to hold secure.\n");
    try_item( ({ "gate", "gates", "ruined gate", "ruined gates",
                 "open gate", "open gates", "broken gate",
                 "broken gates", "open and broken gate",
                 "open and broken gates", "south gate", "south gates",
                 "southern gates", "southern gates of the outpost",
                 "north gate", "northern gate", "north gates",
                 "northern gates", "northern gates of the outpost" }),
        "The gates are about eight feet tall and made of thick wooden logs"
      + " that are held together with iron bands. A great deal of damage"
      + " has been recently dealt to these gates. Large sections of"
      + " the bands holding the hinges in place have been ripped from"
      + " their wooden holdings and much of the wood is scorched"
      + " and charred.\n");
    try_item( ({ "window", "windows", "small window", "small windows" }),
        "Small windows look out from the guard towers, presumably"
      + " offering an excellent mark on any enemy below.\n");
} /* add_outpost_items */


/*
 * Function name:        add_courtyard_view
 * Description  :        add items appropriate to rooms inside the
 *                       courtyard
 */
public void
add_courtyard_view()
{
    try_item( ({ "yard", "grounds", "courtyard" }),
        "This courtyard within the outpost appears lie upon"
      + " a section of the forest which has been clear-cut and then"
      + " leveled for the building of this structure. It spreads"
      + " out in a square area which contains a central building"
      + " which rises two stories above the ground. The walls of"
      + " the outpost frame the courtyard north, south, east, and"
      + " west, with a guard tower crowning each of the corners.\n");
    try_item( ({ "ladder", "ladders" }),
        "Beneath each guard tower, a ladder has been placed to serve"
      + " as access to the area above.\n");
    try_item( ({ "central building", "central complex", "complex",
                 "central complex of the outpost", "tall building",
                 "two-storied building",
                 "tall two-storied building" }),
        "The central complex of the outpost is a tall, two-storied"
      + " building which fills most of the courtyard. It has"
      + " entrances on its northern and southern sides. Like the"
      + " rest of the outpost, there are many signs of damage to"
      + " the exterior. However, the doors upon the entrances"
      + " look to have withstood the assaults, indicating that"
      + " perhaps the raiders succeeded in breaching no more"
      + " than the main walls of the fort.\n");
    try_item( ({ "entrance", "entrances" }),
        "The entrances to the central complex are fortified with"
      + " great steel doors which currently stand open.\n");
    try_item( ({ "door", "doors", "steel door", "steel doors",
                 "great steel door", "great steel doors" }),
        "Great steel doors stand open on the northern and southern"
      + " entrances to the central complex. It appears as if"
      + " these doors have held fast in the recent calamities"
      + " which have all but ruined this once formidable"
      + " outpost. Perhaps the inside of the complex remains"
      + " unspoiled.\n");
} /* add_courtyard_view */


/* 
 * Function name:        add_cant_see_items
 * Description  :        provide reasons for not being able
 *                       to see certain things
 */
public void
add_cant_see_items()
{
    try_item( ({ "mountain", "mountains", "blackwall mountains" }),
        "The Blackwall Mountains are not visible within the"
      + " courtyard due to the wall which forms its northern"
      + " border.\n");
    try_item( ({ "lake", "water", "waters", "water of the lake",
                 "waters of the lake", "lake telberin",
                 "telberin lake", "shore", "lakeshore",
                 "shores", "lakeshores" }),
        "Lake Telberin is not readily seen from within the"
      + " courtyard, though its scent is still fresh in your"
      + " nostrils.\n");
    try_item( ({ "forest", "woods", "trees", "tree" }),
        "The forest which surrounds this outpost to the north"
      + " is not visible over the walls.\n");
} /* add_cant_see_items */



/*
 * Function name:        climb_up_ladder
 * Description  :        allow players to climb the ladder
 *                       without the directional command
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
climb_up_ladder(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[up] [the] [narrow] 'ladder'"))
    {
        return 0; /* can't parse player syntax */
    }

    if (this_player()->query_wiz_level())
    {
        write("Normally we would move the player 'up' here using"
          + " command(). Since you are a wizard, that won't work."
          + " Simply type 'up' yourself.\n");
        return 1;
    }

    this_player()->command("up");
    return 1;
} /* climb_up_ladder */


/*
 * Function name:        climb_down_ladder
 * Description  :        allow players to climb the ladder
 *                       without the directional command
 * Arguments    :        string arg - what the player typed
 * Returns      :        1 - success, 0 - failure
 */
public int
climb_down_ladder(string arg)
{
    if (!strlen(arg))
    {
        notify_fail("Climb what?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[down] [the] [narrow] 'ladder'"))
    {
        return 0; /* can't parse player syntax */
    }

    if (this_player()->query_wiz_level())
    {
        write("Normally we would move the player 'down' here using"
          + " command(). Since you are a wizard, that won't work."
          + " Simply type 'down' yourself.\n");
        return 1;
    }

    this_player()->command("down");
    return 1;
} /* climb_down_ladder */


/*
 * Function name:        add_indoor_items
 * Description  :        add_items for the inside of the
 *                       complex
 */
public void
add_indoor_items()
{
    try_item( ({ "wall", "walls", "log", "logs", "timber", "timbers",
                 "walls of the complex", "walls of the building", "wood"}),
        "Logs have been fastened together to form the walls of this"
      + " complex, which is no less sturdy than the walls which"
      + " surround the outpost.\n");
    try_item( ({ "ground", "floor", "stone", "stones", "down" }),
        "The floor of this complex is comprised of stones which have"
      + " been set in place to form a sturdy foundation.\n");
    try_item( ({ "complex", "building", "central complex",
                 "area" }),
        "This central complex within the outpost is a large building"
      + " formed of the same logs which were used to build the outer"
      + " wall of the fortress. It is a large building, with many"
      + " rooms which are meant to house the troops who have sought"
      + " to hold the outpost against invaders to secure a foothold"
      + " on the north shore. Remarkably, the interior of this building"
      + " looks untouched by the sort of damage which has been visible"
      + " everywhere within the courtyard.\n");
    try_item( ({ "hall", "halls", "passage", "passages",
                 "corridor", "corridors" }),
        "The corridors within this building are narrow, and yet"
      + " not dark. There is an illumination which fills this"
      + " building, dispersing shadows.\n");
    try_item( ({ "illumination", "light" }),
        "There is a great deal of light within this building,"
      + " though you see no obvious source of the illumination.\n");
    try_item( ({ "ceiling", "roof", "up", "boards", "board" }),
        "Boards have been set across the top of the passages and"
      + " rooms of this building to form the ceiling.\n");
    try_item( ({ "here", "room" }), long);
    try_item( ({ "lake", "lakeshore", "lake telberin", "water",
                 "waters", "waters of the lake", "forest",
                 "woods", "trees", "tree", "mountains", 
                 "mountain", "peaks", "blackwall mountains",
                 "sky" }),
        "Such things are not visible from within the complex.\n");
    try_item( ({ "outpost", "fortress", "tower", "towers",
                 "guard tower", "guard towers", "courtyard",
                 "yard", "outpost walls", "walls of the outpost",
                 "gate", "gates" }),
        "The outer portions of the outpost are not visible here"
      + " within the central complex.\n");
} /* add_indoor_items */
