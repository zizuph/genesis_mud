/*
 * Path in Tom Bombadill's Clearing
 * By Finwe, December 2001
 */
 
#pragma strict_types

#include "/d/Shire/sys/defs.h" 
#include "../local.h"

inherit CLEAR_BASE;
 
void
create_path_room()
{
    set_areadesc("dark");
    set_area("path in");
    set_areaname("the Old Forest");
    set_land("Eriador");
    set_areatype(0);

    set_extraline("You stand on top of a small knoll. It is grass " +
        "covered with some short, yellow flowers growing on at the edges. " +
        "To the east is a clearing while to the west the forest " +
        "spreads out before you.");

// items not neaded as player isn't in clearing anymore/yet
    remove_item(({"downs", "barrow downs"}));
    remove_item(({"green hills", "hills"}));
    remove_item(({"fogs", "fog", "mists", "mist", "swirling fog", 
            "swirling fogs", "swirling mists", "swirling mist"}));

// modified from base file
    add_item(({"forest", "old forest"}),
        "The forest is dark and forboding. Tall trees block most " +
        "of the @@light_type@@ light, leaving an almost stifling " +
        "feeling. Some say the forest is haunted and that it " +
        "moves about on its own, though this is speculation and " +
        "no one knows for sure.\n");
    add_item(({"ground", "path", "trail"}),
        "The ground is unusually smooth and covered with short, " +
        "clipped grass, as if it was mowed.\n");
    add_item(({"trees", "tree"}),
        "The trees are tall and dark looking. Many are ancient " +
        "looking. Their tall branches shade reach to the sky, " +
        "blocking most of the @@light_type@@ light. The branches " +
        "move about, almost on their own.\n");

    add_item(({"yellow flowers", "small flowers", "small yellow flowers",
            "buttercups", "flowers"}),
        "The plants are and covered with tall stalks of small " +
        "yellow flowers. The flowers are the color of butter, and " +
        "are made up of five overlapping rounded petals. Each " +
        "flower stalk has between three to five flowers on it.\n");
    add_item("knoll",
        "The knoll is rounded and and coverd with a rich, green " +
        "grass. It is slightly higher than the clearing to the " +
        "northeast, almost as if it is an entrance to there. " +
        "Growing around the knoll are small, yellow flowers.\n");

    add_exit(ROOMS_DIR + "path15", "west");
    add_exit(ROOMS_DIR + "path06", "northeast");
}

