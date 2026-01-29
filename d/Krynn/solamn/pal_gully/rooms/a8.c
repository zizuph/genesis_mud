/* 
 * Room in the Aghar Mines in Krynn Newbie Zone
 * a8.c
 */

#include <macros.h>
#include "../local.h"
#include CLOCKH

inherit PAL_GULLY_BASE;

object dwarf1;
object dwarf2;
object dwarf3;

/*
 * Function name: reset_pal_gully_room
 * Description  : Resets the room
 */
void
reset_pal_gully_room()
{
    if (!objectp(dwarf1))
    {
        dwarf1 = clone_object(LIV + "aghar");
        dwarf1->move(TO);
    }
    if (!objectp(dwarf2))
    {
        dwarf2 = clone_object(LIV + "aghar");
        dwarf2->move(TO);
    }
	if (!objectp(dwarf3))
    {
        dwarf3 = clone_object(LIV + "aghar");
        dwarf3->move(TO);
    }
}

/*
 * Function name: create_pal_gully_room()
 * Description  : Constructor for the room, modify this to change room.
 */
void 
create_pal_gully_room()
{
    set_short("Living Quarters");
    set_long("Small piles of refuse and softer bits of garbage have "
    +"been fashioned into beds for the Aghar. Little boxes made "
    +"from bits of scrap metal sit at the end of each bed to allow the "
    +"Aghar to keep items of importance to them. There are little "
    +"toys and other items set between the makeshift beds. The room is "
    +"lit with oil lanterns.\n");
    
    add_item(({"beds", "piles", "makeshift beds", "refuse"}),
	"Soft bits of garbage have been piled into makeshift beds that "
	+"are used by the Aghar Dwarves. Little tokens and other items "
	+"that they have collected rest between the beds.\n");
    add_item(({"tokens", "items", "toys", "knick knacks",
	"discarded wooden toys", "coloured string","string", "dolls",
	"small stuffed dolls", "stuffed dolls"}), "Bits of "
    +"coloured string, discarded wooden toys, small stuffed dolls "
    +"and other knick knacks are neatly placed between the beds. They "
    +"are well cared for and obviously treasured items of those "
    +"who sleep here.\n");
	add_item(({"boxes", "scrap boxes", "little boxes"}), "small boxes" 
	+"made from scrap metal and garbage. They are used to store items "
	+"that the Aghar dwarves find and wish to keep.\n");
    
    add_exit(RDIR + "a6","northeast",0);
    add_exit(RDIR + "a9","west",0);
    reset_pal_gully_room();
    
}