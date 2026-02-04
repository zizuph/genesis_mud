//-*-C++-*-
// file name:      
// creator(s):     Lilith June 2008
// last update:    Petros April 2009
// note: 
// bug(s):
// to-do:
// Modification Log:
//   - Added a common exit for reading the common board, April 2009
//   - Added a Vampire bulletin board

#include "../guild.h";

inherit ROOM_DIR+"vamp_room";

#include <ss_types.h>
#include <stdproperties.h>

// Global Variables
object desk, drawer;

// Prototypes
public void     load_board();

void
clone_desk()
{
    desk=clone_object(OBJ_DIR +"desk");
    desk->move(TO, 1);
    drawer=clone_object(OBJ_DIR +"drawer");
    drawer->move(TO, 1);


}

public string
desk_inv(void)
{
    if (!desk || ENV(desk)!=TO)
	return "";

    return desk->external_within();
}

public void 
create_vamp_room()
{

    set_short("Small study");
    set_long("This tiny study is hardly larger than a closet. It strongly "+
        "resembles the tapestry you passed in order to get here. On the "+
        "south side of the room, a board has been placed upon the wall. "+
        "There is a desk with a central drawer, a chair, and a painting "+
        "of a landscape. @@desk_inv@@\n");

    add_item(({"chair"}), 
        "It appears to be sturdy for all that it is as ancient as the desk "+
        "before it.\n");
    add_cmd_item(({ "chair", "ancient chair" }), 
        ({ "sit", "sit on"}), "You rest for a moment on the chair.\n");
    add_item(({"painting", "landscape", "painting of a landscape"}), 
        "It is amateurish and without any integral value. It looks "+
        "like a daytime view of the area surrounding the mansion, "+
        "probably painted from memory.\n");

    add_exit("uppertomb", "north");
//    add_exit("common_room", "common");
    
//  add_prop(VAMP_CAN_START_HERE,1);
       
    clone_desk();
//  load_board();
}

public void
load_board()
{
    object bb;
    setuid();
    seteuid(getuid());

    bb = clone_object(OBJ_DIR + "vampire_board");
    bb->move(this_object());
}

