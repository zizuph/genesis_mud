/*
 * dtower2.c
 *
 *
 * Copyright (C): Kellon, august 2012
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include "/d/Krynn/common/defs.h"
#include <money.h>
#include "local.h"

inherit CAMPBASE;
inherit "/lib/unique";

// G L O B A L   V A R S

// P R O T O T Y P E S
public int descend_tower();

object dragon, cabinet, scroll, chest, sc, gc, quiver, arrows, arrows2,
    sword;

#define DEFAULT_SWORD "/d/Krynn/qualinesti/wep/elongsword"
#define DEFAULT_BOW "/d/Krynn/qualinesti/wep/elven_bow"

public void
reset_kurinost_room()
{

    if(!objectp(cabinet))
    {
        cabinet = clone_object(RSOBJS + "cabinet");
        cabinet->move(TO, 1);
    }

    if(!objectp(chest))
    {
        chest = clone_object(RSOBJS + "dragon_chest");
        chest->move(TO, 1);
    }

    if (!present(scroll, cabinet))
    {
        scroll = clone_object("/d/Krynn/common/scrolls/storm_fury_scroll");
        scroll->move(cabinet, 1);
        cabinet->add_prop(CONT_I_CLOSED, 1);
        cabinet->add_prop(CONT_I_LOCK, 1);
    }

    if (!present(sc, chest))
    {
        sc = MONEY_MAKE_SC(random(200) + 60);
        sc->move(chest, 1);
        chest->add_prop(CONT_I_CLOSED, 1);
        chest->add_prop(CONT_I_LOCK, 1);
    }

    if (!present(gc, chest))
    {
        gc = MONEY_MAKE_GC(random(50) + 26);
        gc->move(chest, 1);
        chest->add_prop(CONT_I_CLOSED, 1);
        chest->add_prop(CONT_I_LOCK, 1);
    }

    if (!present(quiver, chest))
    {
        quiver = clone_object("/d/Krynn/qualinesti/obj/quiver");
        quiver->move(chest, 1);
        arrows = clone_object(RSWEAPON + "runed_arrow");
        arrows2 = clone_object(RSWEAPON + "runed_arrow");
        arrows->move(quiver, 1);
        arrows2->move(quiver, 1);
        chest->add_prop(CONT_I_CLOSED, 1);
        chest->add_prop(CONT_I_LOCK, 1);
    }

    if (!present(sword, chest))
    {
        sword = clone_unique(RSWEAPON + "mantooth", 10, DEFAULT_SWORD, 40);
        sword->move(chest, 1);
        chest->add_prop(CONT_I_CLOSED, 1);
        chest->add_prop(CONT_I_LOCK, 1);
    }

    if(!objectp(dragon))
    {
        dragon = clone_object(RSLIVING + "green_dragon");
        dragon->sit_down();
        dragon->move(TO, 1);
    }

    if(objectp(dragon) && (!dragon->query_attack()))
        dragon->sit_down();
}

public int
query_dragon_present()
{
    if(!objectp(dragon))
        return 0;
    else 
        return 1;
}

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : create_kurinost_room
 *  Arguments: None
 *  Returns  : Void
 * 
 *  create_room function that sets up descriptions and exits.
 *
 */
public void
create_kurinost_room()
{
    set_short("upper floor of a broken elven tower");
    set_long("You stand at the upper floor of a broken elven tower. Its " +
        "roof and northern walls have collapsed, exposing you to the " +
        "elements and allowing the " +show_tower_light()+ " to cast " +
        "jagged shadows across the large yet barren platform. On the far " +
        "side of the platform stands a crystal cabinet of elven make and " +
        "a large wooden chest.\n");         

    add_item(({"upper floor", "floor", "platform", "tower", 
        "broken elven tower", "elven tower", "barren platform" }),
        "The upper floor of the broken tower is one large open " +
        "platform, stripped bare of most furnishings. The elven tilework " +
        "on the floor is heavily scarred with giant claw marks.\n");

    add_item(({"roof", "northern walls", "northern wall", "north wall",
        "opening", "gaping opening" }),
        "The roof and northern walls of the tower have collapsed, leaving " +
        "the platform here open to the elements. From the opening " +
        show_tower_light()+ " illuminates the " +
        "platform you stand on, casting jagged shadows around you.\n");

    add_item(({"jagged shadows", "shadows", "shadow", "light" }),
        "Shadows are cast by " +show_tower_light()+ " streaming through " +
        "the gaping opening in the northern wall, like columns of jagged " +
        "darkness across the floor.\n");

    add_item(({"elven tilework","tiles","tilework","claw marks","marks"}),
        "Claw marks from a great beast have scarred the elven tilework " +
        "here.\n");

    add_exit(RSROOMS + "dtower1", "down", descend_tower, 3);

    KURINOSTMAP;
    reset_room();
}


public int
descend_tower()
{
    write("You make your way down the dark staircase to the ground " +
        "floor of the broken tower.\n");
    return 0;
}

