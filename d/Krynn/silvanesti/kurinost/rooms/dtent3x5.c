/*
 * dtent3x5.c
 *
 * Inside a tent in the camp at Kurinost.
 *
 * Copyright (C): Kellon, oktober 2012
 *                Poul Erik Jensen
 *
 */
#pragma strict_types

// I N C L U D E D   F I L E S
#include <stdproperties.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "local.h"

// I N H E R I T E D   F I L E S
inherit INSIDEBASE;

// D E F I N I T I O N S

// G L O B A L   V A R S
object mob1, mob2, mob3, mob4, mob5;
object *gMlist = ({ mob1, mob2, mob3, mob4, mob5 });
int gMaxmobs = random(3) + 3;

// P R O T O T Y P E S
public void setup_tells();
public object choose_mob(status aurak_here = 0);

// P U B L I C   F U N C T I O N S
/*
 *  FUNCTION : reset_kurinost_room
 *  Arguments: none
 *  Returns  : void
 * 
 *  Reset the room.
 *
 */
public void
reset_kurinost_room()
{
    for (int ct = 0; ct < gMaxmobs; ct++)
    {
        if (!objectp(gMlist[ct]))
        {
            if (ct == 0)
            {
                gMlist[ct] = choose_mob(1);   // 1 if Aurak
            }
            else
            {
                gMlist[ct] = choose_mob();
            }
            
            gMlist[ct]->move(TO);

            switch (random(3))
            {
                case 0:
                    tell_room(TO, QTNAME(gMlist[ct]) + " arrives " +
                        "throwing the tentflap aside!\n", gMlist[ct],
                        gMlist[ct]);
                    break;

                case 1:
                    tell_room(TO, "Opening the flap of the tent, " +
                        QNAME(gMlist[ct]) + " arrives, preparing " +
                        "to go off duty.\n", gMlist[ct], gMlist[ct]);
                    break;

                case 2:
                default:
                    tell_room(TO, "Staring darkly at you, " +
                        QNAME(gMlist[ct]) + " arrives through " +
                        "the open flap.\n", gMlist[ct], gMlist[ct]);
                    break;
            }
        }
    }
}


/*
 *  FUNCTION : create_kurinost_room
 *  Arguments: none
 *  Returns  : void
 * 
 *  Create the room.
 *
 */
public void
create_kurinost_room()
{
    set_short("crude grey tent");
    set_long("Barely more than tattered cotton rags sewed together " +
        "from mismatched patches with crude stitches, this grey " +
        "tent is held upright by two crude and quite thick " +
        "wooden poles. What the tent seems to lack in quality it " +
        "certainly has in size, as it must to be about eight by four " +
        "meters of space inside, with bunk space for four to six " +
        "soldiers.\n");
    add_item(({ "crude tent", "grey tent", "crude grey tent",
        "tent" }), "Barely more than tattered cotton rags sewed " +
        "together from mismatched patches with crude stitches, " +
        "this grey tent appears rather simple. About eight by " +
        "four meters, the tent seems able to house quite a few " +
        "soldiers. Standing on bare ground, noone seems to have " +
        "prepared beds or set up any equipment in here yet. A wide " +
        "opening protected only by a flap of cloth is the only " +
        "entrance to the tent.\n");
    add_item(({ "patches", "mismatched patches" }), "Cotton rags " +
        "have been sewed together with crude stitches, making the " +
        "many greyish pathces that make up this tent.\n");
    add_item(({ "flap", "opening", "flap of cloth" }), "Attached " +
        "in one side and hanging loosely, the flap at the opening " +
        "barely protects the tent from the weather outside. It " +
        "seems to be made from a single large piece of greyish " +
        "cloth. You can exit the tent by leaving out through the " +
        "flap.\n");
    add_item(({ "pole", "wooden pole", "thick pole",
        "thick wooden pole" }), "Two thick wooden poles seems to " +
        "have been roughly cut and are now used to hold the tent " +
        "upright. Crude but seemingly effective enough.\n");

    add_exit(RSROOMS + "dcamp3x5", "out", 0, 3);

    setuid();
    seteuid(getuid());

    setup_tells();
    KURINOSTMAP;

    reset_room();
}


/*
 *  FUNCTION : setup_tells
 *  Arguments: none
 *  Returns  : void
 * 
 *  Sets the basic tells of the rocky shores of Silvanesti.
 *
 */
public void
setup_tells()
{
    set_tell_time(420);

    add_tell("Faint wailings of seagulls carry through the " +
        "entrance to the tent.\n");

    add_tell("A faint breeze enters the tent, carrying the smell " +
        "of decaying refuse and burning wood from the outside.\n");

    add_tell("Faint sounds of cracking firewoods carry through " +
        "the tent opening.\n");
}
