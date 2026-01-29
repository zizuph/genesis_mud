/*
 * Cellar  of Tom Bombadil's house
 * Finwe, January 2002
 */

inherit "/d/Shire/room";

#include "/d/Shire/sys/defs.h"
#include "../local.h"
#include <stdproperties.h>

object door;

create_shire_room() 
{
    set_short("Cellar below the kitchen");
    set_long("This is the cellar below the fruit garden. It is very " +
        "large, dark, and dank without the usual musty smells " +
        "associated with such rooms. Here, foods and drinks are " +
        "stored through the seasons. A wooden staircase leads back " +
        "up to the kitchen.\n");
   
    add_item(({"pipes", "air vent", "vents"}), 
      "The pipes lead outside through the ceiling. They enable fresh " +
      "air to circulate in the root cellar and draw out moisture " +
      "and gasses, keeping the fruits and vegetables fresh.\n");
    add_item(({"walls", "wall"}),
        "The walls are dirt that has been hard packed, smoothed, and " +
        "cleaned. Lining all four walls are wooden shelves, full of " +
        "crates holding fruits and vegetables. Beneath the staircase " +
        "are small wine casks. On the east wall are two pipes " +
        "leading outside.\n");
    add_item(({"floor"}),
        "The floor is is dry and made of hard packed dirt. It is " +
        "smooth and very clean.\n");
    add_item(({"ceiling"}),
        "The ceiling is smooth except for two pipes that lead " +
        "outside. Hanging from the ceiling are dried herbs, flowers, " +
        "and braided stalks of garlic.\n");
    add_item(({"shelves"}),
        "The shelves are sturdy and made of wood. They are full of " +
        "large open crates and baskets used for storing fruits and " +
        "vegetables. The shelves line all four walls.\n");
    add_item(({"crates", "baskets", "large crates", "large baskets"}),
        "The large crates and baskets are made of wood. They are " +
        "full fruits and vegetables packed in sawdust. They sit " +
        "on the shelves that line the walls.\n");
    add_item(({"sawdust"}),
        "The sawdust is made of fine wood chips used for storing " +
        "food in the crates and barrels.\n");
    add_item(({"fruits", "vegetables"}),
        "You don't see any as it is all packed in the crates and " +
        "barrels and covered with sawdust. However, it can be " +
        "assumed there is quite a bit stored here as the shelves " +
        "are full.\n");
    add_item(({"garlic", "braided stalks of garlic"}),
        "They are large white bulbs with braided stalks that have " +
        "turned white.\n");
    add_item(({"dried herbs", "herbs"}),
        "The are bunches of herbs that have been picked and now " +
        "hang upside down from the ceiling. They fill the room " +
        "with a pungent aroma.\n");
    add_item(({"dried flowers"}),
        "The flowers are recently picked blooms that have been " +
        "tied together and hang upside down from the ceiling. They " +
        "fill the room with a sweet fragrance.\n");
    add_item(({"wine casks"}),
        "The wine casks are small and made from oak. They are " +
        "round and aged looking. Some of the casks have are plain " +
        "looking while others have marks identifying them from Bree, " +
        "and villages in the Shire.\n");
   
    door = clone_object(OBJ_DIR + "cellar_door");
    door -> move(this_object());
    add_prop(ROOM_I_NO_CLEANUP, 1); // We don't want this room to be unloaded

   
    add_prop(ROOM_I_LIGHT,1);
    add_prop(ROOM_I_INSIDE,1);
    reset_shire_room();
}

