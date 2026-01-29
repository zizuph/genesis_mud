/*
* End of the path through the birch forest.
*
* Special commands allow you to enter the undergrowth
* to the east and north.
*
* Coded by Porta 971018.
*/

#pragma strict_types
#pragma no_clone

inherit "/std/room";
inherit "/d/Earthsea/herbs/specials/hs";

#include <stdproperties.h>
#include "/d/Earthsea/herbs/herb_sets/park_herbs.h"
#include <macros.h>

public void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "earthsea_map.txt");
    set_short("End of the gravel path");
    set_long("This is a quiet spot of the birch grove"+
        ", well-hidden deep inside the park."+
        " The gravel path becomes more and more narrow and"+
        " suddenly ends. Around you the tall stems of birch"+
        " trees rise high up toward the sky, and block"+
        " most of the sunlight from coming through. Thick"+
        " undergrowth prevents you from looking further"+
        " in among the trees, but you guess the tall city"+
        " wall has to be close to the west. The light is"+
        " dim here, and you hear birdsong from the crowns"+
        " of the trees.\n");
    add_item((({"trees", "birch trees", "trunks"})),
        "The grove of white birch trees is quite thick here, "+
        "blocking most of the sunlight from coming through.\n");
    add_item((({"path", "gravel path"})), "The gravel path "+
        "ends here in this more isolated area of the park.\n");
    add_item("grove","This is a dark part of the grove,"+
        " with the tall birches shadowing most of the light"+
        " of day. Thick vegetation grows between the stems,"+
        " preventing your view around.\n");
    add_item(({"undergrowth","vegetation"}),
        "New sprouts of birch grow thick"+
        " on all sides of the gravel path, but you think you"+
        " might be able to make your way through to the east"+
        " and north.\n");
    add_item("path","The gravel path suddenly ends here,"+
        " and the only way is back towards the south.\n");
    add_item("stems","Tall stems rise high up towards"+
        " the sky, with crowns entangled above your head"+
        " effectively blocking most of the sunlight.\n");
    add_item("crowns","Above your head the leafy branches"+
        " of the birch trees are entangled to an almost"+
        " compact roof.\n"); 
    set_up_herbs(select_herb_files(PARK_HERBS), PARK_LOCATIONS, 3);
    add_exit("park_4", "south");
    reset_room();
}

/* Function allowing players to enter vegetation or
undergrowth east and north, transporting them to the
corresponding room */
public int
enter_vegetation(string str)
{
    object to = this_object(), tp = this_player();
    string dir;

    if (!str)
        return notify_fail("Enter what?\n");

    if (str == "vegetation" || str == "undergrowth")
        return notify_fail("Enter what in which direction?\n");

    if (parse_command(str, to,
        "[the] 'vegetation' / 'undergrowth' [to] [the] %s", dir))
    {
        if(dir != "east" && dir != "north")
            return notify_fail("Enter the vegetation in which direction?\n");

        write("You make your way through the undergrowth.\n");
        say(QCTNAME(tp) + " makes " + tp->query_possessive() +
	    " way through the undergrowth to the " + dir + ".\n");
        tp->move_living("M", "/d/Earthsea/gont/gont_city/rooms/park_" +
            (dir == "north" ? "6" : "3"), 1);
        say(QCTNAME(tp) + " arrives through the forest.\n");

        return 1;
    }

    return notify_fail("Enter what?\n");
}

public int
make_way(string str)
{
    object to = this_object(), tp = this_player();
    string dir;

    if (!str)
        return notify_fail("Make what?\n");

    if (parse_command(str, to,
        "[way] [through] [the] 'vegetation' / 'undergrowth' [to] [the] %s", dir))
    {
        if (dir != "east" && dir != "north")
            return notify_fail("Make your way through the vegetation in which direction?\n");

        write("You make your way through the undergrowth.\n");
        say(QCTNAME(tp) + " makes " + tp->query_possessive() +
	    " way through the undergrowth to the " + dir + ".\n");
        tp->move_living("M", "/d/Earthsea/gont/gont_city/rooms/park_" +
            (dir == "north" ? "6" : "3"), 1);
        say(QCTNAME(tp) + " arrives through the forest.\n");

        return 1;
    }

    if (str[..2] == "way")
        return notify_fail("Make your way through what?\n");

    return notify_fail("Make what?\n");
}

public void
init()
{
    ::init();
    add_action(enter_vegetation, "enter");
    add_action(make_way, "make");
}
