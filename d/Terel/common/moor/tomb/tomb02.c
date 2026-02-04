// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc
/* from the imagination of Lord Sorgum ;)  */

#include "/d/Terel/include/Terel.h"
inherit MOOR_DIR +"tomb/tomb_base";
#include "../local.h"

#define COFFIN (TOMBDIR + "coffin")

void
create_room()
{
		::create_room();
		
    set_short("Large burial chamber");
    set_long("You have entered the main burial chamber of the tomb. "+ 
	    "It is a deep, oblong space with a barrel vault ceiling. "+
		"There are many marble byres bearing "+
        "coffins or the remains of coffins. The air is dank and "+ 
        "oppressively thick. There is an archway "+
		"above the exit to the south.\n");

    add_item(({"ceiling", "domed ceiling", "vault", "vaulted ceiling" }), 
       "The ceiling arches "+
        "above into a barrel vault, but any details are impossible to make "+
        "out due to the intense darkness shrouding this place.\n");
		
    add_item(({"byre", "byres", "marble byres"}),
        "Solid blocks of marble were hewn into byres for coffins "+
        "to rest upon.\n");

    add_item(({"dust", "white dust"}), 
        "The white dust is the decayed remains of bones and sinews.\n");

    add_item(({"arch", "archway", "carvings", "funereal carvings"}), 
	    "The arch is covered with grand funereal carvings.\n");

  
    add_prop(ROOM_I_LIGHT, -1);
	
    add_exit("tomb01", "south", 0);
	
	add_object(OBJDIR +"coffins", (4 + random(4)));
    add_object(OBJDIR +"coffin_new", 1);	
}


int 
enter_coffin(string str)
{
    if (!strlen(str) || !parse_command(str, ({ }),
        " [the] / [my] / [newer] / [new] / [open] 'coffin'", str))
    {
        notify_fail("Enter what? Enter the new coffin perhaps?\n");
        return 0;
    }

    if (COFFIN->is_occupied()) 
	{
        write("Someone is already in there. You can't enter it now.\n");
	    say(QCTNAME(TP) + "tries to enter the new coffin but can't.\n");
        return 1;
    }
    else 
    {	 
        TP->move_living("X", TOMBDIR + "coffin");
	    tell_room(QCTNAME(TP) + " enters the new wood coffin.\n");
		return 1;
    }
    write ("You can't seem to do that right now...\n");
    return 1;
}


void
init()
{
     ::init();
     add_action("enter_coffin", "enter");
}
