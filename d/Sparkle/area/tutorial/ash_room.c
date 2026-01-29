/*
 *  /d/Sparkle/area/tutorial/ash_room.c
 *
 *  This is the master file for rooms in destroyed portions of the Tutorial
 *  after the player has made a choice to either aid or destroy Krolock.
 *
 *  Created April 2017, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "defs.h"

inherit SD_ROOM;

#include <stdproperties.h>

/* prototypes */
public void        create_ash_room();
nomask void        create_silverdell();
public void        add_outdoor_items();
public void        add_road_items();
public void        add_indoor_items();

/*
 * Function name:        create_ash_room
 * Description  :        a dummy function to be used by inheriting files
 */
public void
create_ash_room()
{
} /* create_ash_room */


/* 
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
nomask void
create_silverdell()
{
    create_ash_room();
} /* create_silverdell */


/*
 * Function name:        init_ash_room
 * Description  :        a setup function for the ash rooms
 * Arguments    :        string where - "indoor" for inside (default)
 *                                    - "outdoor" for outside
 *                       int corpses  - how many corpses to add (default = 0)
 */
public void
init_ash_room(string where = "indoor", int corpses = 0)
{
    string  ash_txt;
    int     n = random(3);
    object  corpse;

    if (where == "outdoor")
    {
        switch(n)
        {
            case 2:
                ash_txt = "Heaps of ash have covered most of the way here,"
                  + " as thick clouds of noxious black smoke are blown"
                  + " slowly past on a foul wind.";
                break;
            case 1:
                ash_txt = "Grey piles of ash and destruction lie in all"
                  + " directions here, silently smoking in the foul air.";
                break;
            default:
                ash_txt = "Burning waste lies all around, smouldering in"
                  + " the dense clouds of hot and filthy smoke.";
            break;
        }

        set_short("a path amid the ashes");
    }
    else if (where == "castle")
    {
        switch(n)
        {
            case 2:
                ash_txt = "Rubble from the destroyed castle walls lie in"
                  + " heaps all about you here.";
                break;
            case 1:
                ash_txt = "Charred stone and piles of rubble are all"
                  + " around you here.";
                break;
            default:
                ash_txt = "The castle lies in ruin all about you. The"
                  + " walls are charred and in many cases reduced to rubble.";
            break;
        }

        add_item( ({ "rubble", "wall", "walls", "heap", "heaps",
                     "heap of rubble", "heaps of rubble", "rubble heap",
                     "rubble heaps", "castle", "destroyed castle",
                     "building", "stone", "charred stone", "pile",
                     "piles", "pile of rubble", "piles of rubble",
                     "rubble pile", "rubble piles", "walls",
                     "castle wall", "castle walls", "ruin", "ruins" }),
            "The castle has been all but destroyed. Heaps of rubble are"
          + " now the norm, rather than castle walls.\n");

        set_short("amid the ruin of the destroyed castle");
    }
    else
    {
        switch(n)
        {
            case 2:
                ash_txt = "Just the shell of this building remains, charred"
                  + " and blackened by fire. It lies in ruin all about you.";
                break;
            case 1:
                ash_txt = "Collapsing timbers, smouldering and on the verge"
                  + " of ruin frame what is left of this building.";
                break;
            default:
                ash_txt = "Heaps of ash crowd this ruined building. The"
                  + " fires have gutted it, and it smokes in silent"
                  + " ruin all about you.";
            break;
        }

        add_item( ({ "building", "ruin", "timber", "timbers",
                     "collapsing timbers", "collapsing timber",
                     "frame", "burned building", "burned-out building",
                     "burned out building" }),
            "The fire has all but destroyed this place.\n");

        set_short("within a burned-out building");
    }

    set_long(ash_txt + "\n\n");

    while(corpses)
    {
        corpse = clone_object("/std/object");
        corpse->set_name("corpse");
        corpse->add_adj( ({ "charred", "humanoid" }) );
        corpse->set_short("charred corpse");
        corpse->set_long("A charred humanoid corpse lies amid the"
          + " ashes here. It would be impossible to recognize who it"
          + " once was.\n");
        corpse->add_prop(OBJ_M_NO_GET, "Leave the dead in peace.\n");
        corpse->add_prop(OBJ_I_WEIGHT, 50000);
        corpse->add_prop(OBJ_I_VOLUME, 100000);
        corpse->move(this_object());

        corpses--;
    }
 
    add_item( ({ "ash", "ashes", "pile", "piles", "pile of ash",
                 "piles of ash", "ash pile", "ash piles", "heap",
                 "heaps", "ash heap", "ash heaps", "heap of ash",
                 "heaps of ash", "waste", "burning waste" }),
        "All around are the remnants of a great fire.\n");
    add_item( ({ "fire", "great fire", "fires" }),
        "The fire has done its work and gone out.\n");
    add_item( ({ "smoke", "black smoke", "cloud", "cloud of smoke",
                 "clouds", "clouds of smoke", "smoke cloud", "smoke clouds" }),
        "Visibility is minimal amid the dark smoke that rises from the"
      + " piles of ash that lie everywhere here.\n");
    add_item( ({ "path" }),
        "One must thread a path through all these ashes.\n");
} /* init_ash_room */

        

/*
 * Function name:        ash_long
 * Description  :        Provide a long description for this room based
 *                       on whether it was outdoors or indoors. They will
 *                       all be primarily the same, with some built-in
 *                       randomness.


/*
 * Function name:        add_outdoor_items
 * Description  :        add_items that describe things present in
 *                       just about any outdoor room in Silverdell
 */
public void
add_outdoor_items()
{
    try_item( ({ "sky", "up", "blue sky" }), exa_sky);
    try_item( ({ "cloud", "clouds", "scattered clouds",
                 "puff", "puffs", "puffs of cloud", "filthy cloud",
                 "filthy clouds", "filthy black cloud", "black cloud",
                 "black clouds", "filthy black clouds",
                 "smoke", "dark smoke", "clouds of smoke",
                 "cloud of smoke", "smoke cloud", "dark cloud",
                 "dark clouds", "dark cloud of smoke",
                 "dark clouds of smoke", "twisting clouds",
                 "dark clouds", "twisting cloud", "twisting clouds",
                 "dark and twisting cloud", "dark and twisting clouds",
                 "white cloud", "white clouds" }),
        exa_cloud);
    try_item( ({ "sun", "sunlight", "rays", "rays of warmth",
                 "light", "illumination" }), exa_light);
    try_item( ({ "here", "area", "silverdell", "land", "lands",
                 "region", "domain" }), exa_silverdell);
    try_item( ({ "ground", "down", "floor", "pebble", "pebbles",
                 "dirt", "soil", "earth", "dust" }), one_of_list( ({
        "The ground here is solid beneath your feet.\n",
        "A few pebbles dot the ground, which is otherwise fairly"
      + " plain.\n",
        "You kick a bit at the dirt along the ground, testing the"
      + " earth with your foot.\n" }) ) );
    try_item( ({ "wind", "breeze", "smell", "stench" }), 
        "There is a bit of breeze here in the outdoors.\n");
} /* add_outdoor_items */


/*
 * Function name:        add_road_items
 * Description  :        add_items that describe the road
 */
public void
add_road_items()
{
} /* add_road_items */


/*
 * Function name:        add_town_items
 * Description  :        try_items for the town streets
 */
public void
add_town_items()
{
} /* add_town_items */


/*
 * Function name:        add_indoor_items
 * Description  :        generic items for indoor rooms
 */
public void
add_indoor_items()
{
} /* add_indoor_itmes */

