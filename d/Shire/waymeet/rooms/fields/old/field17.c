/*
    /d/Shire/waymeet/rooms/fields/field17.c

    Field in the farm north of Waymeet
    Perrigrine, February 2019
*/

#pragma save_binary
#pragma strict_types

#include "defs.h"
#include "/d/Shire/eastroad/western/local.h"

inherit EAST_ROAD;

static object wolf;
void reset_shire_room();

void create_er_room()
{

    area = "near"; /* Distance from areaname */
    areaname = "Waymeet";
    land = "the Shire";
    areatype = 4;
    areadesc = "vegetable field";

    extraline = "These large vegetable fields provide produce for the village " +
        "of Waymeet. You see cabbages, beets, carrots, and other essentials " +
        "spread around in careful rows. Amongst the rows you notice rather large " +
        "pawprints.";

    add_item(({"surroundings","expanse","plain","shire"}),
      "The Shire is an expanse of plains, with the occasional village "
      +"or cultivated field, where the hobbits till the rich soil of the "
      +"Shire.\n");
    add_item(({"tracks","track","animal tracks", "prints", "pawprints", "paw prints"}),
      "You see quite a few tracks across the fields here. " +
      "They're from something fairly big like a dog or a wolf.\n");
    add_item(({"field", "fields"}),
        "These fields provide food for the village of Waymeet.\n");
    add_item(({"vegetables", "cabbage", "cabbages", "carrots", "beets", "food"}),
        "Many large and healthy vegetables fill these rows. They all look " +
        "like they are nearly ripe.\n");
    add_item(({"village", "Waymeet", "waymeet"}),
        "To the south you can see the small village of Waymeet.\n");
    add_item(({"farm", "house", "farmhouse", "farm house", "barn"}),
        "You can see the main farm buildings not farm from here.\n");

    reset_shire_room();

    add_exit(WAYM_FIELD_DIR + "field18","east");
    add_exit(WAYM_FIELD_DIR + "field09","north");
}

void reset_shire_room()
{
    setuid();
    seteuid(getuid());
    if(!objectp(wolf))
    {
        wolf = clone_object("/d/Gondor/common/npc/wolf");
        wolf->set_restrain_path("/d/Shire/waymeet/rooms/fields");
        wolf->set_random_move(2);
        wolf->move(TO);
    }

}
