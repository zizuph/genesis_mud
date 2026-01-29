/*
 *    info.c  
 *
 * In this room players can find information about
 * the guild.
 *
 * Baldacin@Genesis, Dec 2003   
 *
 */

inherit "/std/room.c";
#include "../defs.h"
#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
    set_short("A small semicircular platform");
    set_long("On a small semicircular platform. The room is completely "+
      "bare, only a wooden pedestal with a book resting upon it. "+
      "The walls have been constructed from both branches and short "+
      "woody stumps and planks. South will take you back to the large "+
      "platform.\n");
    
    if (!present("amazon_race_info_book", TO))
    {
    	setuid();
        seteuid(getuid());
        clone_object(OBJ+"book")->move(TO, 1);
    }
    
    add_item(({"pedestal","wooden pedestal"}), "It is a sturdy wooden "+
      "pedestal with a book resting upon it.\n");
    add_item(({"wall","walls","branches","woody stumps","planks"}), "The semi"+
      "circular wall has been built from branches and some planks to "+
      "make it firm and sturdy.\n");
    add_item(({"platform","large platform"}), "Going south will take "+
      "you to the larger platform, connecting the other parts of the "+
      "tree.\n");
    
    add_exit(ROOMS + "platform","south");
}
