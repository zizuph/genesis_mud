/*inherit "/d/Gondor/common/room"; */
inherit "/std/room";     
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

object shade1,shade2;

create_room()
{
  set_short("A dimly lit room");
  set_long(BSN("This seems to be the main hall of the Shades quarters. "+
  "A few tables and chairs are placed on the floor, and oil-lamps suspended"+
    "from the ceiling only dimly lights the room. A dark passageway "+
    "leads out east, and a set of curtains hangs on the south wall, "+
    "only partly covering another doorway. North is another small hall."));
  add_item("oil-lamps","A couple of oil-lamps are burning quietly in a " +
"corner.\n");
  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_LIGHT,1);
  add_item(({"chairs","chair"}),BSN("Simple wooden chairs, nothing special at " +
    "all."));
  add_item(({"tables","table"}), BSN("Wooden tables with heavy amounts of nicks and " +
              "carvings from dagger points."));
  add_item("curtains", BSN("A set of dark black curtains drapped over the " +
           "south wall covers a arch to the southern quarters."));
  add_item("walls","The walls are made of grey-white stone.\n");
  add_item("ground", "The ground is dusty and made of a grey-white stone.\n");
  add_item("ceiling", "The ceiling is low and made of a grey-white stone.\n");
  add_item("rug", "An old tattered rug lies on the floor, dirty and trampled.\n");
  add_exit(SHADES_DIR + "hall2", "south", 0, 4);
  add_exit(SHADES_DIR+"corr1","east", 0, 4);
  add_exit(SHADES_DIR + "hall3", "north", 0, 4);
  add_stuff();
}
void init()
{
  ::init();
  add_action("move_rug","move");
}
int
move_rug(string str) {
  if(!str)
    return 0;

  if(str == "rug") {
    write("You move the rug and reveal a trap door leading down!\n");
    say(QCTNAME(TP) + "moves the rug and reveals a trap door!\n"); 
    add_exit(MINAS_DIR + "sewer/senter", "down", 0, 1);
    return 1;
    }
    NF("Move what?\n");
    return 0;
}
add_stuff()
{
  if (!shade1) 
    shade1 = clone_object(SHADES_DIR+"shade");
    shade1->move(this_object());
  if (!shade2) 
    shade2 = clone_object(SHADES_DIR+"shade2");
    shade2->move(this_object());
}

reset_room()
{
  add_stuff();
}

