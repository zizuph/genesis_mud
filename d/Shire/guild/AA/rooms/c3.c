#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include "../guild.h"

inherit SHIRE_ROOM;

void
create_room()
{
    set_short("Corridor");
    set_long("You stand in a corridor in the quarters of the Army of " +
        "Angmar. It continues north further into the guard quarters, " +
        "while the great fortress gates lie to the south. " +
        "A new archway leads off to the east while a wide opening " +
        "into a spacious hall is visible to the west.\n");
   
    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */

    add_item(({"gates","gate"}), "These massive wooden gates are opened "+
        "almost all the time. Probably because no one dares attack " +
        "this place.\n");
  
    add_item(({"east wall", "eastern wall", "arch", "archway"}),
        "A new archway has been set into it!\n" +
        "There is a large sign above it.\n");
    add_item(({ "west wall", "western wall", "opening", "chapel", "hall" }), 
        "This spacious hall appears rather welcoming, it might be a " +
        "good place to visit if you plan on joining the army.\n");
    add_item(({ "large sign", "sign" }), "The sign reads:\n\n" +
	      "Soldiers' mess hall.\n");

    add_exit(AA_DIR+"rooms/c2", "north", "@@my_guild_member@@");
    add_exit(AA_DIR+"rooms/gates", "south");
    add_exit(AA_DIR+"rooms/chapel", "west");
    add_exit(AA_DIR+"rooms/mess_hall", "east", "@@my_guild_member@@");
}

public int
my_guild_member()
{
/* allow wizards and AA to enter, but block everyone else. Finwe November 2017
if (!TP->query_guild_member(GUILD_NAME))
    {
	      write("You are not allowed in. You are not a soldier of the " +
	          "Army!\n");
	  return 1;
    }
*/

    if (this_player()->query_wiz_level())
    {
        return 0;
    }
    else if(TP->query_guild_member(GUILD_NAME)) 
    {
        write("A soldier of the Army snaps to attention as you pass by.\n");
        return 0;
    }
    else
    {
        write("Large orcs step out of the shadows and block you from going there.\n");
	    return 1;
    }
}
