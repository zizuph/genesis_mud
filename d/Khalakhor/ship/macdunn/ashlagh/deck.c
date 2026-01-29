/* File:          /d/Khalakhor/ship/macdunn/ashlagh/deck.c
 * Creator:       Zima (copied from Teth)
 * Date:          June 17, 1998
 * Modifications:
 * Purpose:       The deck is a room on the Khalakhor to Baile Ashlagh ship
 * Related Files: /d/Khalakhor/ship/macdunn/
 *                /d/Khalakhor/ship/macdunn/ashlagh/
 *                /d/Khalakhor/open/SHIPLINES
 *                /d/Khalakhor/ship/macdunn/ashlagh/crate.c
 *                /d/Khalakhor/ship/macdunn/ashlagh/apple.c
 *                /d/Khalakhor/ship/macdunn/ashlagh/box.c
 * Comments:
 *
 */
#pragma save_binary
#pragma strict_types
 
inherit "/d/Genesis/ship/deck";
#include "local.h"
#include <stdproperties.h>
#include "/d/Khalakhor/sys/terrains.h"
 
public void create_deck()
{
    set_short("on the deck of the "+SHIP_NAME);
    set_long("   This elegant ship is named the "+SHIP_NAME+". "+
      "Constructed of heavy wood beams, it has a massive central "+
      "mast with voluminous sails, all designed to weather storms "+
      "and pull the heavy vessel through the waters quickly. "+
      "The cabin of the ship is situated to the aft, "+
      "its wood frame lined with shining brass. Though not an enourmous "+
      "ship, it is very impressive. The view from the deck is awe "+
      "inspiring.\n");
 
    add_item(({"deck","area"}),"@@query_long");
    add_item(({"ship","vessel","small vessel",SHIP_NAME, "aigne deas"}),
      "This is the ship that transports passengers and cargo "+
      "between the village of Baile Ashlagh and Port MacDunn in the "+
      "land of Khalakhor.\n");
    add_item("mast",
       "The central mast of the ship is, well, massive. You wonder how "+
       "the ship doesn't topple over from its weight. Obviously designed "+
       "to withstand powerful winds, it rises high above the deck "+
       "laden with large sails.\n");
    add_item("sails",
       "The large white sails hanging from the mast seem to be made of "+
       "wool and are very voluminous. You imagine a heavy wind in "+
       "those sails on that mast could carry the ship very quickly "+
       "and safely.\n");
    add_cmd_item(({"air","in the air"}),({"smell","breathe"}),
      "The air smells of sea salt.\n");
    add_item("sky","The sky above is partially cloudy.\n");
 
    add_exit(THIS_DIR + "cabin", "cabin", 0);
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_SHIPDECK);
    set_deck_sound("@@sounds");
}
 
public string sounds()
{
    if(random(3))
        return "The ship barrels through the cold waters at top speed.\n";
    return "The ship rises slightly as it slices through a huge wave.\n";
}
