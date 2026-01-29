/* 
 * Room in the Aghar Mines in Krynn Newbie Zone
 * a13.c
 */

#include <macros.h>
#include "../local.h"
#include CLOCKH

inherit PAL_GULLY_BASE;

object dwarf1;
object dwarf2;
object dwarf3;
object dwarf4;
object dwarf5;

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
	if (!objectp(dwarf4))
    {
        dwarf4 = clone_object(LIV + "aghar");
        dwarf4->move(TO);
    }
	if (!objectp(dwarf5))
    {
        dwarf5 = clone_object(LIV + "aghar");
        dwarf5->move(TO);
    }
}

/*
 * Function name: create_pal_gully_room()
 * Description  : Constructor for the room, modify this to change room.
 */
void 
create_pal_gully_room()
{
    set_short("Mess Hall");
    set_long("A big open space has been made hear by "
    +"pushing all of the garbage back up against the walls. Along the "
    +"floor are set piles of what might be food. Scraps and "
    +"bits of half chewed food rest in the piles and appear "
    +"to be picked at from time time as some are smaller than "
    +"others. The entire room stinks to high heavens and "
    +"most of what is being eaten seems to be discarded "
    +"from somewhere else.\n");
    
    add_item(({"food", "scraps", "mouldy food", "half-chewed food",
	"half chewed food","pile", "piles"}), "Bits and pieces of "
    +"vegetables, fruit and bread lie on the ground in neat piles "
    +"placed there to be eaten whenever someone is hungry.\n");
    
    add_exit(RDIR + "a9","northwest",0);
    add_exit(RDIR + "a14","east",0);
    reset_pal_gully_room();
    
}