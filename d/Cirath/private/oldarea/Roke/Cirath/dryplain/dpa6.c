inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

object warrior1,warrior2,warrior3;

reset_room()
{
	if(!(warrior1||warrior2||warrior3)) /* Make sure all are dead before all are dead*/
	{
	warrior1 = clone_object(MONSTER+"warrior");
	warrior2 = clone_object(MONSTER+"warrior");
	warrior3 = clone_object(MONSTER+"warrior");
	warrior1->move(TO);
	warrior2->move(TO);
	warrior3->move(TO);
	}
}




void create_room()
{
	set_short("Dry plains");
	set_long(break_string("You are in the north end of the starnge path. Some tracks shows that"+
	"Dangerous things are happening here every now and then. The blood on the ground is still "+
	"fresh. There is a stone placed in the middle of this room, it almost looks like an altar. "+
	"There is much danger in the air. You shiver from the cold. \n",70));
	add_item((("stone")),"A huge stone with blood on \n");
	add_item((("altar")),"In the middle of the altar there is some button \n");
	add_exit(DRYPLAIN+"dpa5","south");
reset_room();
}
init()
{
    ::init();
    add_action("press","press");
}

int
press(string str)
{
    mixed words;

    if (!strlen(str)) return 0;
    if (str != "button")
	if (member_array("press",explode(str," ")) == -1)
	    return 0;
	else
	{
	    notify_fail("Press what?\n");
	    return 0;
	}
    write("You press the button with all your power.\n \n \n");
    TP->move_living("through a hole in the ground",DRYPLAIN+"dpa9",1);
    tell_room(QCTNAME(TP)+ " presses something and disappears.\n");
    return 1;
}