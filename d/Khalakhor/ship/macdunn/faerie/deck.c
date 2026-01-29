/* File:          /d/Khalakhor/ship/macdunn/faerie/deck.c
 * Creator:       Teth
 * Date:          November 15, 1997
 * Modifications: 
 * Purpose:       The deck is a room on the Khalakhor to
 *                Faerie ship.
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/faerie/
 *                /d/Khalakhor/open/SHIPLINES
 *                /d/Khalakhor/ship/macdunn/faerie/crate.c
 *                /d/Khalakhor/ship/macdunn/faerie/apple.c
 *                /d/Khalakhor/ship/macdunn/faerie/box.c
 * Comments:
 *
 */

#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/deck";
#include "local.h"
#include <stdproperties.h>
#include "/d/Khalakhor/sys/terrains.h"

object box, crate;

public void
create_deck()
{
    set_short("on the deck of the Fiu Alladh");
    set_long("   This elegant ship is named the Fiu Alladh. " +
      "Handcrafted, it is the work of a master shipwright. " +
      "Silk sails adorn the mastpole, in the shape of swan " +
      "wings. The cabin of the ship is fitted into the frame, " +
      "integrating it in a unique style. The openness of the " +
      "deck allows a view of the surroundings from any " +
      "location.\n");
    add_item(({"deck","area"}),"@@query_long");
    add_item(({"ship","vessel","small vessel","Fiu Alladh",
        "fiu alladh"}),"This is the ship that ferries passengers " +
      "between the lands of Khalakhor and Faerie.\n");
    add_item("craftsmanship","The work of the shipwright is " +
      "indeed a marvel.\n");
    add_item(({"sail","silk sail"}),"No single sail stands out. " +
      "It is the assembly which is interesting.\n");
    add_item(({"sails","silk sails","assembly"}),"The sails " +
      "are woven of pure silk, a fabric which captures the wind " +
      "easily. The sails are in the shape of swan wings, either " +
      "by accident or design.\n");
    add_item(({"fabric","silk","pure silk"}),"A treasured " +
      "natural fabric, put to excellent use in this ship.\n");
    add_item(({"mastpole","pole","mast"}),"The cured oak mastpole " +
      "supports the silk sails used to propel the ship on windy " +
      "days.\n");
    add_cmd_item(({"mastpole","pole","mast","the mast","the pole",
        "the mastpole"}),"climb","You attempt to climb the " +
      "mastpole, but find that without handholds, you are " +
      "unable to achieve much height.\n");
    add_item(({"oak","cured oak"}),"This is a typical wood used to " +
      "build ships.\n"); 
    add_item(({"cabin","fitted cabin"}),"The cabin of the " +
      "ship is not a separate structure, but it is instead " +
      "integrated into the lines of the ship.\n");
    add_item(({"style","unique style"}),"This style seems " +
      "to accentuate natural lines and flow.\n");
    add_cmd_item(({"air","in the air"}),({"smell","breathe"}),
      "The air smells of sea salt.\n");
    add_item("sky","The sky above is partially cloudy.\n");

    add_exit(THIS_DIR + "cabin", "cabin", 0);

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_SHIPDECK); 

    set_deck_sound("@@sounds");

    box = clone_object(OBJ_DIR + "box");
    box->move(this_object(), 1);
    crate = clone_object(OBJ_DIR + "crate");
    crate->move(this_object(), 1);
}

public string
sounds()
{
    if(random(2))
        return "The ship skims through the water, " +
        "leaving only an odd ripple.\n";
    return "The ship effortlessly glides on the water.\n";
}
