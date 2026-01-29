/* 
 * Room in the Aghar Mines in Krynn Newbie Zone
 * a3.c
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
    set_short("Games Room");
    set_long("This room is used by the Aghar to entertain "
    +"themselves. In certain areas of the room there are small piles "
	+"of refuse. There are small tables in this room which seem to be "
	+"used as play areas. Small dead lizard puppets, bits of string and "
    +"pieces of trash are strewn about.\n");
        
    add_item(({"desk", "desks", "tables", "table"}), "Fashioned out of "
    +"bits of garbage, these desks are poorly made and barely holding "
    +"together. Set upon the garbage tables are bits of string, pieces "
    +"of paper, and other bits of garbage that appear to be used "
    +"for fun and games.\n");
	add_item(({"puppet", "dead-lizard", "dead lizards", "dead-lizards", 
	"dead lizard", "dead lizard puppets","puppets"}), "Puppets made from petrified "
	+"and dead lizards and bits of coloured string. It seems as though "
	+"they may have been participating in a wedding.\n");
	add_item(({"string", "bits of string", "strings", "bit of string",
	"pattern", "colourful pattern"}),
	"Small pieces of coloured string are tied into knots and strewn about "
	+"in a colourful pattern.\n");
	add_item(({"trash", "bits of trash", "pieces of trash","pieces of paper",
	"paper", "balls","ball"}), "Small pieces and bits of trash crumpled "
	+"into balls are placed on the table.\n");
    
    add_exit(RDIR + "a4","southwest",0);
    add_exit(RDIR + "a2","east",0);
    reset_pal_gully_room();
    
}