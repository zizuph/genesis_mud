// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc
/* from the imagination of Lord Sorgum ;)  */

#include "/d/Terel/include/Terel.h"
#include "../local.h"
inherit MOOR_DIR +"tomb/tomb_base";


#include <ss_types.h>

void
create_room()
{
    object door;

	::create_room();
	
    set_short("Just inside tomb");
    set_long("You brave the shadows which seem to linger oddly " +
    "about the water-worn stones and make your way into the tomb. " +
    "You are immediately overcome by the sickening stench of decay. " +
	"The granite of the vault is dripping with slime mold. "+
    "Damp stone steps lead downward into darkness, while an archway "+
    "leads north into the main burial chamber.\n"
    );

    add_item(({"steps", "stone steps"}),
	"The damp stone steps are made of the same ancient granite as " +
    "the rest of the tomb.  The lead downwards into the black " +
    "recesses of the earth.\n"
    );
	
	add_item(({"archway", "doorway"}), "The doorway to the north is "+
    "an arch. The stone of the archway drips with mold and dampness "+
    "that obscures any details.\n");
	
	add_item(({"stones", "stone"}), "The stones have been eroded by "+
    "water over many, many years.\n");
	
    door = clone_object(TOMBDIR + "tomb_door2");
    door->move(TO);
    door->set_key(TOMB_DOOR_KEY);
	
    add_exit("under_tomb01", "down", "@@go_down", 0);
	add_exit("tomb02", "north", 0);
}

int
go_down()
{
    int tp_dis;

    tp_dis = (TP->query_stat(SS_DIS));

    if (tp_dis < 50) 
	{
        write("You are too afraid to descend the steps.  Perhaps you "+
          "should return here when you are more disciplined.\n");
        say(QCTNAME(TP)+" seems unable to continue any further.\n");
        return 1;
    }
	
    write_file(TOMBLOG, TP->query_real_name() + " went down into " +
        "the tomb "+ ctime(time()) +"\n");
    return 0;
}

/* This should be handled by the door object

do_lock(string str)
{
     notify_fail("Lock what?\n");
     if ((str == "door") || (str == "padlock")) {
      write("You can't do that.  The lock is on the other side!\n");
      return 1;
     }
     return 0;
}

do_unlock(string str)
{
     notify_fail("Unock what?\n");
     if ((str == "door") || (str == "padlock")) {
      write("You can't do that.  The lock is on the other side!\n");
      return 1;
     }
     return 0;
}
*/