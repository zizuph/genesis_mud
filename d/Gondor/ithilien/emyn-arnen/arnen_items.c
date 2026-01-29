/*
 *      /d/Gondor/ithilien/emyn-arnen/arnen_items.c
 *
 *      Copyright (c) 1997 by Christian Markus
 *
 *      To replace arnen_defs.h.
 *
 *      Modification log:
 */
#pragma strict_types

#include "/d/Gondor/defs.h"

static void
add_hill(string extra = "")
{
    string  desc =
        "The green hills gently rising on all sides are the hills of Emyn " +
        "Arnen, the land in southern Ithilien that was the home of the House " +
        "of Hurin, the house of the Stewards of Gondor. It rises between the " +
        "road and the Anduin, and was said to be the most beautiful part of " +
        "Ithilien before it fell under the Shadow.";

    if (strlen(extra))
        desc += (" " + extra);

    TO->add_item( ({"hill", "hills", "emyn arnen"}), BSN(desc));
}

static void
add_palace_roof(string extra = "")
{
    string  desc =
        "The vaulted roof is resting on large stone pillars. "
        + "It was made from large grey stone blocks that form large "
        + "roman arches.";

    if (strlen(extra))
        desc += (" " + extra);

    TO->add_item(({"roof", "ceiling", }), BSN(desc));
}

static void
add_palace_walls(string extra = "")
{
    string  desc =
        "The walls are made of large grey stone blocks that were "
        + "expertly hewn, polished and fitted together without the "
        + "use of mortar.";

    if (strlen(extra))
        desc += (" " + extra);

    TO->add_item(({"wall", "walls", }), BSN(desc));
}

static void
add_pillar(string extra = "")
{
    string  desc =
        "The pillars are made of large round stone slabs that are "
        + "several feet high and piled on each other to the total "
        + "height of the hall which must be more than 6 yards.";

    if (strlen(extra))
        desc += (" " + extra);

    TO->add_item(({"pillar", "pillars", }), BSN(desc));
}

static void
add_palace_floor(string extra = "")
{
    string  desc =
        "The floor is made of large grey stone slabs which have seen "
      + "the passing of many years and many boots. They are cut from "
      + "the same rock as the walls and the roof.";

    if (strlen(extra))
        desc += (" " + extra);

    TO->add_item(({"floor", "ground", }), BSN(desc));
}

static void
add_palace_stones(string extra = "")
{
    string  desc =
        "The stone blocks that were used for the floor, the walls, "
      + "and the roof were all cut from the same rock of "
      + "light grey colour. Master masons have fitted them together "
      + "so expertly that nowhere the use of mortar was required.";

    if (strlen(extra))
        desc += (" " + extra);

    TO->add_item(({"stone", "stones", "rock", "slabs", "stone slabs",
        "stone blocks", "blocks", }), BSN(desc));
}

static void
add_cellar_walls(string extra = "")
{
    string  desc =
        "The walls are made from large uneven stone blocks.";

    if (strlen(extra))
        desc += (" " + extra);

    TO->add_item(({"wall", "walls", }), BSN(desc));
}

static void
add_cellar_roof(string extra = "")
{
    string  desc =
        "The roof is made from large uneven stone blocks that form "
        + "a high vault above your head.";

    if (strlen(extra))
        desc += (" " + extra);

    TO->add_item(({"roof", "ceiling", "vault", }), BSN(desc));
}

static void
add_cellar_stones(string extra = "")
{
    string  desc =
        "The stone blocks that were used for the walls and the ceiling "
      + "were probably hewn from the same rock that was used for the "
      + "halls of the ground floor, but the blocks down here were not "
      + "polished nor were they fitted together as expertly as above.";

    if (strlen(extra))
        desc += (" " + extra);

    TO->add_item(({"stone", "stones", "blocks", "stone blocks", }), 
        BSN(desc));
}

static void
add_cellar_floor(string extra = "")
{
    string  desc =
        "The ground is covered with black cobblestones, probably made "
      + "from granite.";

    if (strlen(extra))
        desc += (" " + extra);

    TO->add_item(({"floor", "ground", "cobblestones", }), BSN(desc));
}
