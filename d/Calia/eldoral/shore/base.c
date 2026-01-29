#include "defs.h"

inherit "/std/room";
inherit HERBMASTER;

string main;

public int
woods_msg()
{
    write("You step off the shoreline and push your way through " +
        "the trees into the forest.\n");
    return 0;
}

public void
create_shore()
{
    if (!main)
        main = "";

    main += "You are standing on the rocky shoreline of Eldoral " +
        "Isle, a narrow strip of grey and broken stone that serves " +
        "to separate the thick, green forests of the island " +
        "and the misty waters of the lake. Across the " +
        "water, the mist shifts and swirls in strange, complex, " +
        "and random patterns, coaxed by a gentle breeze that crosses " +
        "the lake. The mist drifts back and forth much like the " +
        "gently rippling waves of the lake, dashing against the " +
        "green trees as the waves disperse against the pebbles " +
        "on the shore. The water itself is cold and calm and you have " +
        "no problems whatsoever seeing the bottom of the lake " +
        "near the shore; however it turns abruptly black not very " +
        "far from the shoreline, leading you to believe the lake " +
        "becomes very deep, very fast. ";

    add_item(({"mist", "fog"}),
        "Heavy and grey, a dark mist blankets the waters of the " +
        "lake, hiding everything beyond a short stone's throw " +
        "from your view.\n");
    add_item(({"water", "waters", "lake"}),
        "The water of the lake is cold and dark, but clear and " +
        "quite refreshing. The surface is also very calm, like " +
        "a mirror that goes on forever.\n");
    add_item(({"bottom", "lake bottom", "bottom of lake"}),
        "Near the shore you can see the pebbly bottom of the " +
        "lake beneath the cold waters, but it swiftly vanishes " +
        "to inky darkness a few paces from the water's edge.\n");
    add_item(({"shore", "shoreline"}),
        "The shore between the water and the impressive forest " +
        "on the island is comprised mainly of pebbles of various " +
        "sizes, bits of boulders that were crushed and worn down " +
        "smooth by the waters of the lake.\n");
    add_item(({"pebbles", "pebble"}),
        "The pebbles are quite common looking. Nothing more than " +
        "smooth, grey stones of various shapes and sizes.\n");
    add_item(({"forest", "tree", "trees"}),
        "On the inner side of the shore, a massive wall formed " +
        "by a dense forest of evergreen trees hides all that " +
        "might or might not lie beyond. The only way to find out " +
        "for sure, is to look beyond for yourself.\n");

    add_prop(ROOM_I_TYPE, ROOM_BEACH);

    setup_my_herbs();
    reset_room();
}

public void
create_direction(string where)
{
    set_short("on the " + where + " shore of Eldoral Isle");
    set_long(main + "\n\n");
}
