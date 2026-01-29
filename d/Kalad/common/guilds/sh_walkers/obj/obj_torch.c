/*
 * A torch for where ever.  It casts a light factor of 1.
 * This is not a torch for players, it is a non-gettable,
 * non-lightable, non-extinguishable torch to be loaded
 * into a room as an object.  The torch will also cause
 * players to see 'The torches cause eerie shadows to 
 * flicker along the wall.'
 *
 * I had the idea initially, but noticed that Stevenson 
 * already had one, so I borrowed his style for this one 
 * and added a few things in.
 *
 * /d/Kalad/common/guilds/sh_walkers/obj/torch_ob.c
 * Created By : Rico 7.01.97
 * First Modif: 
 */

#include "../defs.h"

inherit "/std/object.c";

void
create_object()
{
   set_short("cast iron torch");
   add_name("torch");
   add_adj(({ "cast", "iron", "cast iron" }));
   set_long("\nThe torch is mounted to the wall with a cast "+
      "iron bracket.  It causes eerie shadows to flicker "+
      "along the tunnel's surface.\n\n");
   
   add_item(({ "shadows", "eerie shadows", "flickering shadows" }),
      "\nThey make you uneasy as they dance along the surface of "+
      "the walls.  Every once in awhile you think you notice a "+
      "monster coming at you, but after calming down, you realize "+
      "that it was only the flickering shadows playing tricks on "+
      "your peripheral vision.\n\n");
   add_item(({ "bracket", "cast iron bracket" }), 
      "\nThis bracket keeps the torch mounted to the wall.  It's "+
      "so sturdy that you would be hard pressed to remove the "+
      "torch.\n\n");

   add_prop(OBJ_M_NO_GET, "\nYou grunt and groan and heave at it "+
      "with a mighty effort, but fail to even budge it!!\n\n" );
}

/*
 *  Function Name :  init
 *  Description   :  Call out for the shadow() function.
 */
void
init()
{
   ::init();
   
   if (random(20) > 10)
      set_alarm(1.0, 0.0, "shadows");
}

/*
 *  Function Name :  shadows
 *  Description   :  Tell the room a string every time a living
 *                   enters it.
 *  Returns       :  The string.
 */
void
shadows()
{
   /*  The color code in this bit doesn't work...  */
   tell_room(environment(this_object()),
      "The torch creates eerie, flickering shadows along the "+
      "tunnel's surface.\n");
}

