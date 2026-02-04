#include "/d/Terel/include/Terel.h"
#include "include/hills_defs.h"
inherit STDROOM;


public void
create_room()
{
    ::create_room();
    OUTSIDE;

    set_short("Windy foothills");
    set_long("The rolling foothills around you are devoid of " +
        "vegetation except for the occasional tuft of wild grasses " +
        "struggling to survive. A cold harsh wind blows down " +
        "from the mountains to your north. " +
        "The cold brisk air is filled with scents of salt and snow." +
        " Dark grey clouds filter any sunlight, casting a " +
        "shadowless twilight about you.\n");

    add_item(({"grass","wild grasses","foothills","vegetation"}),
        "A stubbly short-bladed grass clings to life, growing " +
        "here and there in small little clumps amoung the foothills.\n");

    add_item(("mountains"), "Standing tall in the north, " +
        "the massive Dragon Mountain peaks pierce the " +
        "dark, heavy clouds that have moved into this area.\n");

    add_item(({"peaks","mountain peaks"}), 
        "The mountain range to the north is comprised of " +
        "many tall snow-capped peaks.\n");

    add_item(({"sky","clouds"}), "Dark forboding clouds " +
        "hang low in the sky, gently churning but seemingly " +
        "unmoving.  The brisk air and laden clouds lead you to " +
        "believe that it may snow at anytime.\n");

}

