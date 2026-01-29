/*
 * rotten_meat.c
 *
 * A disgusting lump of rotten meat, that cannot be picked up.
 *
 * Copyright (C): Kellon, oktober 2012
 *                Poul Erik Jensen
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

// I N H E R I T E D   F I L E S
inherit "/std/object";

// D E F I N I T I O N S

// G L O B A L   V A R S
int gAlarmID, gSink = 0;
string gMeatAdj = one_of_list(({ "blackened", "brownish",
    "greenish" }));

// P R O T O T Y P E S
public void sink_lump();

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : create_object
 *  Arguments: none
 *  Returns  : void
 * 
 *  Creates the object and sets up descriptions.
 *
 */
public void create_object()
{
    set_name("meat");
    add_name("lump");
    set_adj(gMeatAdj);
    add_adj("rotten");

    set_short("rotten " + gMeatAdj + " lump of meat");
    set_pshort("rotten " + gMeatAdj + " lumps of meat");

    set_long("Rotten and quite smelly, this lump of meat has " +
        "decayed too much and it is quite impossible to recognize " +
        "what kind of animal part it might have come from. Apart " +
        "from being dead, you quickly notice that it is very " +
        "alive with small white maggots.\n");

    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 2);

    add_prop(OBJ_M_NO_GET, "As you attempt to pick up the lump of " +
        "rotten meat, it falls apart and you have to let go. As " +
        "it drops down into the mud again, you notice several " +
        "maggots crawling out of the lump where it broke apart.\n");

    gAlarmID = set_alarm(1.0, 30.0, &sink_lump());
}


/*
 *  FUNCTION : sink_lump
 *  Arguments: None
 *  Returns  : None
 * 
 *  The lump of meat sinks slowly into the mud.
 *
 */
public void
sink_lump()
{
    object room = environment(TO);

    if (!gSink)
    {
        tell_room(room, "As the rotten " + gMeatAdj + " lump of " +
            "meat lands in the thick mud, it starts sinking " +
            "slowly.\n", 0, TO);

        gSink++;
        return;
    }

    switch (gSink)
    {
        case 1..3:
            tell_room(room, "With a strange bubbling sound, the " +
                "rotten " + gMeatAdj + " lump of meat sinks a " +
                "little deeper into the mud.\n", 0, TO);

            gSink++;
            return;

        case 4:
            tell_room(room, "With a final sucking noice, the " +
                "rotten " + gMeatAdj + " lump of meat disappears " +
                "down into the mud and vanishes from view.\n", 0,
                TO);

            remove_alarm(gAlarmID);
            TO->remove_object();
    }
}
