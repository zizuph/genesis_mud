/*
 *  /d/Emerald/blackwall/delrimmon/lakeside/sw_wood3b.c
 *
 *  This room along the southwestern slopes of the lake shore of
 *  Del Rimmon in the Blackwall Mountains holds a long forgotten monument
 *  which marks the burial ground of the Torque Wearers of old.
 *
 *  Copyright (c) March 1998, by Gorboth (Cooper Sherry)
 *
 *  Emerald Conversion: November 2000
 */
#pragma strict_types

inherit "/d/Emerald/blackwall/delrimmon/tree_room.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Emerald/blackwall/delrimmon/defs.h"

//  Global Variables
int     Show_Pillar;
object  Pillar;
object  Hole;

//  Prototypes
public string  bramble();
public string  bramble_fern();
public string  check_reveal();
public string  do_search(object tp, string arg);
public string  fern();
public string  mound();
public string  undergrowth();

public int  query_pillar() { return Show_Pillar; }

/*
 * Function name: create_tree_room
 * Description  : allows us to create the room with area presets
 */
void
create_tree_room()
{
    add_name( ({ "_special_digging_room" }) );
    set_loc(2);
    set_side("southwest");
    set_show_area_desc();

    set_extraline(check_reveal);

    add_item( ({"mound", "thick mound",
                "mound of vegetation",
                "thick mound of vegetation"}),
                 mound);
    add_item( ({"undergrowth", "ground", "vegetation"}), undergrowth);
    add_item( ({"brambles", "twisted brambles",}),
                 bramble);
    add_item( ({"shank", "shanks", "bramble shank", "bramble shanks"}),
    BSN("The shanks of the brambles are coiled and brown, winding"
      + " their thorny way throughout this area."));
    add_item( ({"fern", "ferns", "shaggy fern", "shaggy ferns"}), 
                 fern);
    add_item( ({"clump", "clumps", "patch", "patches",
                "clumps and patches",}), BSN(
        "The grouping of the ferns is random at best, dotting the"
      + " slope with the green and brown of many fronds."));
    add_item( ({"hump", "humps"}), BSN(
        "The vegetation drapes thickly over the hump of the mound."));
    add_item( ({"frond", "fronds",}), BSN(
        "The fronds of the many shaggy ferns in this area grow quite"
      + " thickly, creating the effect of a green carpet above the"
      + " mossy ground."));

    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    add_exit(DELRIMMON_DIR+"lakeside/w_wood1","north",check_sitting,1,1);
    add_exit(DELRIMMON_DIR+"lakeside/w_shore1","northeast",check_sitting,1,1);
    add_exit(DELRIMMON_DIR+"lakeside/sw_wood3","east",check_sitting,1,1);
    add_exit(DELRIMMON_DIR + "lakeside/sw_wood2b", "southeast",
             check_sitting,1,1);
    add_exit(DELRIMMON_DIR+"lakeside/sw_cliff4","south",check_sitting,1,1);
    add_exit(DELRIMMON_DIR+"lakeside/sw_cliff5","west",check_sitting,1,1);
    add_exit(DELRIMMON_DIR+"lakeside/w_wood1b","northwest",check_sitting,1,1);

    set_no_exit_msg( ({ "southwest" }),
        "Struggling with the underbrush, you discover that movement"
      + " in that direction will not be possible.\n");

    FIX_EUID

    Pillar = clone_object(DELRIMMON_DIR + "obj/pillar");
    Pillar->move(this_object());

    Hole = clone_object(DELRIMMON_DIR + "obj/hole")->move(this_object());


    enable_reset(200);  /* reset this room often to re-hide the pillar */
} /* create_tree_room */

/*
 * Function name: check_reveal
 * Description  : This will be the extraline for the long description
 *                of the room. It will vary depending on if the pillar
 *                has been revealed.
 * Returns      : string - the room description
 */
public string
check_reveal()
{
    string  room_txt;

    room_txt = "The undergrowth is thick here, choking the ground"
             + " with twisted brambles and shaggy ferns.";

    if (Show_Pillar)
    {
        room_txt +=" A large portion of the vegetation has been torn"
             + " back nearby.";
    }

    return room_txt;
} /* check_reveal */

/*
 * Function name: bramble
 * Description  : Gives us the description for the add_item for the
 *                brambles, varying based on the value of bramble_fern
 * Returns      : string - bramble description
 */
public string
bramble()
{
    string btxt = "The shanks of many brambles twist and wind through"
                + " this area, growing most heavily quite near to"
                + " here, where";

    return BSN(btxt + bramble_fern() );
} /* bramble */

/*
 * Function name: fern
 * Description  : Gives us the description for the add_item for the
 *                ferns, varying based on the value of bramble_fern
 * Returns      : string - fern description
 */
public string
fern()
{
    string ftxt = "Ferns of many sizes litter this area. They grow often"
                + " in clumps and patches, running especially thick quite"
                + " nearby, where";

    return BSN(ftxt + bramble_fern() );
} /* fern */

/*
 * Function name: bramble_fern
 * Description  : Called by fern() and bramble() to give a description
 *                of the vegetation based on whether or not the
 *                pillar has been revealed
 * Returns      : string - description of the vegetation
 */
public string
bramble_fern()
{
    string  veg_txt;

    if (Show_Pillar)
    {
        veg_txt = " much of the vegetation has been pulled back to reveal"
                + " a ragged stone pillar.";
    }

    else
    {
        veg_txt = " the vegetation seems to swell in a visible mound.";
    }

    return veg_txt;
} /* bramble_fern */

/*
 * Function name: mound
 * Description  : Gives us a description for the mound add_item, based
 *                on whether or not the pillar has been revealed
 * Returns      : string - description of the mound
 */
public string
mound()
{
    string  mtxt;

    if (Show_Pillar)
    {
        mtxt = "The many coiled ferns and brambles have been pulled"
             + " back here, revealing a ragged stone pillar.";
    }

    else
    {
        mtxt = "Brambles and other undergrowth in the area have"
             + " swollen to form a mound near to here. The leaves"
             + " of the many plants have formed a visible hump"
             + " which rises from the ground.";
    }

    return BSN(mtxt);
} /* mound */

/*
 * Function name: undergrowth
 * Description  : Gives us a description of the ground here, based on
 *                whether or not the pillar has been revealed
 * Returns      : string - description of the ground
 */
public string
undergrowth()
{
    string  groundtxt;

    groundtxt = "The ground here is covered with dense-growing ferns"
              + " and coiling bramble shanks. They grow particularly"
              + " thickly nearby, where";

    if (Show_Pillar)
    {
        groundtxt += " the vegetation has been pulled back to reveal"
                   + " a ragged stone pillar.";
    }

    else
    {
        groundtxt += " the vegetation swells over a mound of some sort.";
    }

    return BSN(groundtxt);
} /* undergrowth */

/*
 * Function name:       do_search
 * Description  :       handle searching the room & items
 * Arguments    :       object tp       this player
 *              :       string          whatever the player searched
 *
 */
public string
do_search(object tp, string arg)
{
    object pillar;

    if ( arg != "vegetation" && arg != "mound"
      && arg != "brambles" && arg != "ferns"
      && arg != "twisted brambles" && arg != "shaggy ferns"
      && arg != "thick vegetation" && arg != "hump"
      && arg != "ground" )
        /* a hint to give a target ... */
        return BSN("You poke around the area, but find "+
             "nothing interesting.");

    if ( !Show_Pillar &&
    TP->query_skill(SS_AWARENESS) >= (MIN_AWARE + random(RANDOM_AWARE)))
    {
        say(QCTNAME(TP) + " works to pull back the many layers of"
                 + " vegetation in the area, slowly revealing a"
                 + " ragged stone pillar which was entirely covered"
                 + " with brambles.\n");

        Show_Pillar = 1;

        return BSN("Pulling away the top layers of vegetation from the"
                 + " mound reveals a rough stony surface. As you remove"
                 + " more of the plants, the form of a ragged stone"
                 + " pillar is slowly exposed from its soggy confines.");
    }
    return BSN("You search the "+arg+
        ", but do not find anything of interest.");
} /* do_search */


/* 
 * Function name:        reset_room
 * Description  :        at resets, we re-hide the pillar
 *                       and make it mossy once again
 */
public void
reset_room()
{
    Show_Pillar = 0;
    Pillar->set_mossy(1);
    Hole->set_state(0);
} /* reset_room */
