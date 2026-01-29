/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/nw_shore1.c
 *
 *  The shore of the lake runs diagonally northwest-southeast
 *  here as Del Rimmon draws away from its central western
 *  edge heading north.
 *
 *  Copyright (c) September 1997 by Cooper Sherry (Gorboth)
 *
 *  Emerald Conversion: November 2000
 *  Added fishing     : August 2021 (Gorboth)
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/lakeshore.c";

#include <stdproperties.h>;
#include "/d/Emerald/blackwall/delrimmon/defs.h"

/* prototypes */
void           create_lakeshore();
public void    reset_room();

/*
 * Function name: create_lakeshore
 * Description  : allows us to create the room with area presets
 */
void
create_lakeshore()
{
    set_loc(1);
    set_side("northwest");
    set_show_area_desc();

    set_extraline("The shore runs along the lake of Del Rimmon"
      + " curving to the east as one travels north. To the south,"
      + " a small stream is visible trailing out of the trees"
      + " of the hillsides.");

    add_item( ({"stream", "streams"}), BSN(
        "The stream is quite some ways to the south from here."
      + " All that is evident is that it runs from the woods"
      + " to meet with the waters of the lake."));
    add_cmd_item( ({"stream", "streams"}), 
        ({"drink", "search"}), BSN(
        "The stream is quite a ways off to the south, and quite"
      + " unaccessable from here."));


    add_exit(DELRIMMON_DIR + "lakeside/nw_wood2","north",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood2b","northwest",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/nw_wood1","west",0,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/w_shore5","southwest");
    add_exit(DELRIMMON_DIR + "lakeside/nw_shore2","northeast");

    add_prop("_live_i_can_fish", "alpine lake");

    set_no_exit_msg( ({ "east", "southeast", "south" }),
        "The waters of Del Rimmon spread out before you in that"
      + " direction.\n");

    FIX_EUID

    reset_room();
} /* create_lakeshore */

/*
 * Function name: reset_room
 * Description  : add a spear to the room at resets and set properties
 *                so that the spear looks the way we wish
 */
public void
reset_room()
{
    object  spear;

    if (!present("spear", TO) )
    {
        spear = clone_object(DELRIMMON_DIR + "obj/wep/spear");
        spear->add_prop(OBJ_I_BROKEN, 1);
        spear->add_prop_obj_i_broken();

        spear->set_long(BSN(
            "This spear is long and deadly looking. Tightly woven"
          + " black cords have been wound around the midsection of"
          + " the lengthy shaft to support a solid grip. The blade"
          + " of the spear seems to be made of iron which has been"
          + " blackened by some foul process. Stains of some sort"
          + " cover the blade."));
        spear->add_item( ({"blade", "blades"}), BSN(
            "The blade of this spear has been wrought of iron, and"
          + " then blackened by some foul process. Stains cover its"
          + " surface."));
        spear->add_item( ({"stain", "stains"}), BSN(
            "A closer look at the stains reveals fish scales, and"
          + " tiny entrails."));
        spear->add_item( ({"fish scales", "scales"}), BSN(
            "The stains upon the blade of this weapon are coated with"
          + " many fish scales. Having had time to dry in the sun,"
          + " they look rather dull and faded."));
        spear->add_item( ({"entrails", "tiny entrails"}), BSN(
            "Whether this weapon was used to merely catch fish, or"
          + " to gut them as well is not clear. Regardless, the"
          + " entrails dried upon the blade do not look pleasant."));

        spear->move(TO);
    }
} /* reset_room */
