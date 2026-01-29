
/* File name :  board_tent.c
 *
 * Inside the board tent. There is a table where the archers may leave 
 * notes for other guildmembers.
 *
 * Blizzard, 05.11.2003
 */
 
#include "/d/Krynn/common/defs.h"
#include "../guild.h"

inherit R_FILE


public void
create_krynn_room()
{
    set_short("inside a small tent");
    set_long("You are standing inside an almost empty tent. Except the " +
        "small table staning in the middle of the room, there is not " +
        "much here. On the table you notice a pile of papers, an ink and " +
        "and a quill.\n");
    
    add_item(({ "paper", "papers", "notes", "pile", "pile of papers" }),
        "There is a pile of papers on the table. Maybe you should take " +
        "a closer look at it.\n");
    add_item( "ink",
        "An almost full bottle of ink, standing on the table.\n");
    add_item( "quill", 
        "A simple long quill is lying next to the bottle of ink. You could " +
        "use it for writing a note.\n");
    
    INSIDE;
    NO_TIME;
    
 /* Clone the guild board */
    room_add_object(GUILD_OBJ + "archer_board", 1, 0);
    
    add_exit(GUILD_ROOM + "archer_camp7.c", "out", 0, 1);
    
}
