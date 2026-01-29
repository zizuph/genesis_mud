
/* File name :  start_tent.c
 *
 * Elven Archers' starting place.
 *
 * Blizzard, 05.11.2003
 */
 
#include "/d/Krynn/common/defs.h"
#include "../guild.h"

inherit R_FILE


public void
create_krynn_room()
{
    set_short("inside the large dark-green tent");
    set_long("You are standing inside a large dark-green tent. It was made " +
        "with great precision, which is typical for elven work. The " +
        "canvas looks a bit the worse for wear here and there but still " +
        "it offers good protection against rain and a night chill. " +
        "There are many furs and elven blankets lying on the floor, " +
        "as well as the dried leaves that regularly drift in here with " +
        "the wind.\n");
    
    add_item(({ "leaves", "dried leaves", "leaf" }),
        "There are several small piles of dried leaves that have drifted " +
        "here with the wind.\n");
    add_item(({"blanket", "blankets", "elven blanket", "elven blankets"}),
        "They are really warm and soft in touch. You probably could " +
        "use them when you decide to go sleep.\n");
    add_item(({ "fur", "warm furs", "warm fur", "furs", "soft furs" }),
        "There are several warm and soft animal furs lying on the floor.\n");
    
    INSIDE;
    NO_TIME;
    
    add_exit(GUILD_ROOM + "archer_camp5.c", "out", 0, 1);
    
}
