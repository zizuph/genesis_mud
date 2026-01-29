/*
 *      /d/Gondor/arnor/fornost/fornost.c
 *
 *      Master room for Fornost.
 *
 *      Copyright (c) 1997 by Christian Markus
 *
 *      Description originally written by Arren.
 *      Transferred into this file and recoded by 
 *      Olorin, February 1997. 
 */
#pragma strict_types

inherit "/d/Gondor/arnor/arnor_room.c";

#include "/d/Gondor/defs.h"

static string
set_arnor_long()
{
    return BSN(query_arnor_time());
}

public void
create_fornost()
{
}

public void
create_arnor()
{
    create_fornost();

    set_long(set_arnor_long);
}

static void
add_buildings(string extra = "")
{
    string  desc = "All the buildings are in ruins, the " +
        "only difference is the degree of disintegration.";

    if (strlen(extra))
        desc += " " + extra;

    add_item("buildings", BSN(desc));
}

static void
add_bushes(string extra = "")
{
    string  desc = "The bushes are green and full of life.";

    if (strlen(extra))
    {
        desc += " " + extra;
        desc = BS(desc);
    }

    add_item("bushes", desc + "\n");
}

static void
add_columns(string extra = "")
{
    string  desc = "They must have been tall.";

    if (strlen(extra))
    {
        desc += " " + extra;
        desc = BS(desc);
    }

    add_item("columns", desc + "\n");
}

static void
add_cracks(string extra = "")
{
    string  desc = 
        "In the cracks grow some some persistent grass.";

    if (strlen(extra))
    {
        desc += " " + extra;
        desc = BS(desc);
    }

    add_item(({ "cracks", "cracked stones" }), desc + "\n");
}

static void
add_entrance(string extra = "")
{
    string  desc = "It was made to fit the size of humans.";

    if (strlen(extra))
    {
        desc += " " + extra;
        desc = BS(desc);
    }

    add_item("entrance", desc + "\n");
}

static void
add_foundation(string extra = "")
{
    string  desc =
        "The walls of the tower must have been thick, but now all that "+
        "remains is a small mound.";

    if (strlen(extra))
        desc += " " + extra;

    add_item(({ "foundation", "tower" }), BSN(desc));
}

static void
add_grass(string extra = "")
{
    string  desc = "The grass is long and yellow-green.";

    if (strlen(extra))
    {
        desc += " " + extra;
        desc = BS(desc);
    }

    add_item("grass", desc + "\n");
}

static void
add_ground(string extra = "")
{
    string  desc = "The ground is covered by rubble.";

    if (strlen(extra))
    {
        desc += " " + extra;
        desc = BS(desc);
    }

    add_item("ground", desc + "\n");
}

static void
add_hills(string extra = "")
{
    string  desc =
        "The North Downs form a line of hills running from the southwest "+
        "to the northeast.";

    if (strlen(extra))
        desc += " " + extra;

    add_item(({ "hill", "hills", "north downs", "downs"}), BSN(desc));
}

static void
add_ivy(string extra = "")
{
    string  desc = 
       "It has shining dark green leaves. It grows densely.";

    if (strlen(extra))
    {
        desc += " " + extra;
        desc = BS(desc);
    }

    add_item( ({ "ivy", }), desc + "\n");
}

static void
add_mound(string extra = "")
{
    string  desc = 
        "Crumbled heaps of rubble is all that remains of the buildings.";

    if (strlen(extra))
    {
        desc += " " + extra;
        desc = BS(desc);
    }

    add_item( ({ "mound", "heap" }), desc + "\n");
}

static void
add_outer_wall(string extra = "")
{
    string  desc = 
        "The height of the wall varies. At some points it's mostly "+
        "intact, at others it's almost completely tumbled down.";

    if (strlen(extra))
        desc += " " + extra;

    add_item( ({ "outer wall", "wall" }), BSN(desc));
}

static void
add_roof(string extra = "")
{
    string  desc = 
        "The open sky is now the roof.";

    if (strlen(extra))
    {
        desc += " " + extra;
        desc = BS(desc);
    }

    add_item( ({ "roof", }), desc + "\n");
}

static void
add_rubble(string extra = "")
{
    string  desc = 
        "Waste fragments of stone covering the ground.";

    if (strlen(extra))
    {
        desc += " " + extra;
        desc = BS(desc);
    }

    add_item( ({ "rubble", "fragments" }), desc + "\n");
}

static void
add_ruins(string extra = "")
{
    string  desc = 
        "This was once a fortress city. Now there is only the memory "+
        "of its former greatness. As you look around you can only see "+
        "tumbled and ruined buildings everywhere, overgrown by grass. "+
        "But there is sense of peace. Even though the fortress itself "+
        "was broken, its spirit was not.";

    if (strlen(extra))
        desc += " " + extra;

    add_item( ({ "ruins", "ruin", "fortress" }), BSN(desc));
}

static void
add_stones(string extra = "")
{
    string  desc = 
        "The stones are hard, yet in the end they did not prevail "+
        "against the final attack.";
    
    if (strlen(extra))
        desc += " " + extra;

    add_item( ({ "stones", "stone" }), BSN(desc));
}

static void
add_street(string extra = "")
{
    string  desc =
        "Once it must have been straight and broad, but now the street "+
        "is overgrown by grass and bushes. The street is filled with "+
        "rubble, making it somewhat hard to discern.";

    if (strlen(extra))
        desc += " " + extra;

    add_item("street", BSN(desc));
}

static void
add_tower_wall(string extra = "")
{
    string  desc = 
        "Even though the lower parts of the tower still stand, they "+
        "show signs of being battered. Here and there you can see "+ 
        "cracked stones.";

    if (strlen(extra))
        desc += " " + extra;
    add_item(({ "tower wall", "wall", "tower" }), BSN(desc));
}

static void
add_walls(string extra = "")
{
    string  desc = "Nothing much is left of the walls.";

    if (strlen(extra))
    {
        desc += " " + extra;
        desc = BS(desc);
    }

    add_item( ({ "wall", "walls", }), desc + "\n");
}
