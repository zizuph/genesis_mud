/* 
 * Room in the Aghar Mines in Krynn Newbie Zone
 * a15.c
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
    set_short("Meeting Hall");
    set_long("This is a large open chamber, much like the "
    +"mess halls. Here there are small little garbage desks set up "
    +"for the Aghar to stand behind when the feel like talking. "
    +"There is a bigger garbage desk at the front of the room. "
    +"This room seems as though it has rarely been used and is "
    +"actually quite a bit cleaner than the rest of the mine. "
    +"There are small plots of dirt that appear to have been turned "
    +"over with little scratchings above them in the wall.\n");
    
    add_item(({"plots", "dirt", "overturned dirt", "graves"}), "These "
    +"appear to be small graves. Above are scratchings of what might "
    +"be considered names. Apparently this room is used to bury the "
    +"Aghar who have been slain by the bloodthirsty Dewar in this "
    +"dispute over the mine.\n");
    add_item(({"scratchings", "names", "markings"}), "The markings are "
    +"illegible. It is impossible to see what they say.\n");
    add_item(({"seats", "rows", "seat", "row"}), "Small seats made entirely "
	+"from garbage have been setup here for Aghar to sit on if they wish.\n");
	add_item(({"small desk", "small desks", "small garbage desk", 
	"small garbage desks","desks"}), "Small desks made from garbage for Aghar "
	+"dwarves who wish to speak about a matter of importance.\n");
	add_item(({"big desk", "big desks", "big garbage desk", 
	"big garbage desks", "bigger garbage desk", "bigger garbage desk"}),
	"A bigger desk at which the Highbulp of the Aghar Dwaves will sit when "
	+"a meeting is in session.\n");
	
    
    add_exit(RDIR + "a14","west",0);
    add_exit(RDIR + "a16","southeast",0);
    reset_pal_gully_room();
    
}