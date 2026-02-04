inherit "/std/room";
     
#include <stdproperties.h>
#include <macros.h>

#include "/d/Terel/common/terel_defs.h"
#include "tomb.h"


reset_room()
{
     object benton;
     if(present("Benton"))return;
     benton=clone_object(TOMBDIR + "ccorpse");
     benton->move(this_object());
}

void
create_room()
{
    set_short("Gore chamber");
    set_long(
        "You feel as if you have stepped into Hell.  The room is filled " +
	"with grotesque, crippled, carved up carcasses.  " +
	 "Bloody torsos are " +
	"suspended from hooks in the ceiling by their own intestines. " +
	"The floor is littered with an upheaval of human entrails. " +
	"Chewed limbs dripping with pus and wretched chunks of bleeding " +
        "flesh are scattered everywhere.\n"
    );

    add_item(({"headstone", "slate headstone"}), 
        "The slate headstone has crumbled so much that you can only make " +
	"out the last three letters of the name, which are NIR.\n"
    );

    add_item(({"carcasses", "torsos"}), 
	"Decayed and shredded, the most disturbing thing about them is " +
	"teeth marks and nibbled look about them.\n"
    );

    add_item(({"entrails", "pus", "chunks"}), 
	"Don't look too closely, or you might toss your cookies.\n"
    );
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 0);
    
    add_exit(TOMBDIR + "grime_river", "grime", 0);
    reset_room();

}
