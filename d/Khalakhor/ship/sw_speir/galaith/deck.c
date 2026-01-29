/**********************************************************************
 * - deck.c                                                         - *
 * - On deck of ship                                                - *
 * - Created by Damaris@Genesis 12/2000                             - *
 * - Undated by Damaris@Genesis 05/2005                             - *
 **********************************************************************/
#pragma save_binary
#pragma strict_types
 
inherit "/d/Genesis/ship/deck";
#include "local.h"
#include <stdproperties.h>
#include "/d/Khalakhor/sys/terrains.h"
 
public void create_deck()
{
    set_short("On the deck of the "+SHIP_NAME);
    set_long("This smooth impressive ship is named "+
      "the "+SHIP_NAME+". It has been constructed of sturdy wood "+
      "beams. It has an enormous central mast with massive sails, "+
      "which are all designed to weather storms and pull this vessel "+
      "through the waters quickly. Though not an enormous ship, it is "+
      "very impressive. The view from the deck is remarkable.\n");
 
    add_item(({"deck","area"}),"@@query_long");
    add_item(({"ship","vessel","small vessel",SHIP_NAME}),
      "This is the ship that transports passengers and cargo "+
      "between the village of SaMorgan and Galaith Isle in the "+
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
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_SHIPDECK); 
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(GALAITH + "cabin", "cabin", 0);

    set_deck_sound("@@sounds");
}
 
public string sounds()
{
   if(random(3))
     return "The ship glides smoothly through the cool waters.\n";
     return "The ship creaks slightly as it slices through a huge wave.\n";

}
