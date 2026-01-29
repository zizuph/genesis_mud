/*
 * hall2.c
 * 
 * Skippern 20(c)02
 *
 * The living room.
 */
#include "../../defs.h"
inherit DOL_STD + "inside";

#include <macros.h>
#include <stdproperties.h>

/* Prototypes */

/* Code */
void
create_inside()
{
    set_short("a living room");

	set_long("You find yourself in a large hall, a doorway to the southwest " +
		"leads to a hall, a dozen high and narrow windows lines the room " +
		"allowing a loucious amount of light to enter during the day, and a " +
		"large gold and cristal lamp dominates the center of the room. On " +
		"the far wall a fireplace is situated with a large ornamented " +
		"mantlepiece. Cream coloured silk curtains drapes the sides of the tall " +
		"windows. Each side of the door, a tall column shaped as a greeting " +
		"king stands.\n");
	
	add_item("doorway", "A doorway leads southwest into the hall. Each side of the " +
		"door, a tall column shaped as a greeting king stands. The doorway itself " +
		"is large enough for a troll to pass, or three knights abreast.\n");
	add_item( ({ "window", "windows", "narrow window", "narrow windows" }), 
		"Along each side of the room, a dozen narrow windows are located. The clear " +
		"glass in the windows allows for a loucious amount of light to enter during " +
		"the day, without admitting too much of the activities inside for any spectators " +
		"on the outside. Each side of the window are edged with elegant cream coloured " +
		"silk curtains, framing the windows perfectly.\n");
	add_item( ({ "curtain", "curtains", "silk curtain", "silk curtains", "cream curtain",
		"cream curtains", "cream coloured curtain", "cream coloured curtains",
		"cream coloured silk curtains", "cream coloured silk curtain" }),
		"Framing the narrow windows are a pair of cream coloured silk curtains. They hang " +
		"in perfect folds from the tall ceiling above the windows, and with a few elegant " +
		"ropes are tied to the sides in order not to cover the windows. It looks like a " +
		"simple task to untie these ropes and cover up the windows, but the servants " +
		"probably wouldn't allow you to do such a trifle job.\n");
	add_item( ({ "lamp", "gold lamp", "cristal lamp", "gold and cristal lamp" }),
		"From the ceiling high above you see a gold and cristal lamp, with probably a " +
		"hundred small oil burners. It looks like the lamp is attached to some sort of " +
		"whiching system, allowing the servants to lower it to the floor in order to " +
		"light it, or to refill it with oil. The lamp gives of a soft glow illuminating " +
		"the entire room.\n");

    add_exit(DOL_HILLS + "j-11/hall1", "southwest", 0, 1);
}
