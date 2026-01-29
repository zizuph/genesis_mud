/* goblin caves */

#include "../local.h"

inherit SHIRE_ROOM;

int brooch_in_room=1;

void
prepare_brooch()
{
    brooch_in_room=1;
}

void
create_shire_room()
{
    object door;

    seteuid(getuid());

    add_prop(ROOM_I_LIGHT, 0);
    add_prop(ROOM_I_INSIDE, 1);

    set_short("cell in prison");
    set_long("You are in the cell in goblin prison. it is dark with wet "+
      "walls and it stinks. Not a nice place to stay.\n");
    add_item(({"wall","walls"}),BS("The walls are natural rock except the "+
	"northern wall that was build from big blocks of rock. Now "+
	"one block is removed from wall revealing a hole. The block "+
	"itself is lying under the hole.\n"));
    add_item("blocks",BS("Big blocks of dark cold rock. Walls are usually "+
	"made from such blocks.\n"));
    add_item("block",BS("Big block of dark cold rock. Walls are usually "+
	"made from such blocks. This one was obviously in the wall "+
	"before someone make a hole there.\n"));
    add_item("hole",BS("Someone removed block from wall making a hole. "+
	"You may be able to squeeze through it.\n"));

    door = clone_object(MISTY_OBJ_DIR + "grating_1_d");
    door->move(this_object());
    door->set_key("gcave_cell_no_1"); /* Tells the door which key fits. */
}

init()
{
    ::init();
    add_action("move_something", "move");
    add_action("enter_hole", "enter");
}

int move_something(string arg)
{
    seteuid(getuid());

    NF("Move what?\n");
    if(arg != "block") return 0;
    if(brooch_in_room)
    {
	brooch_in_room = 0;
	clone_object(MISTY_OBJ_DIR+"brooch")->move(TO);
	TP->catch_msg("You summon all your strength and move block of rock "+
	  "little to the side. You reveal small brooch that was "+
	  "under the block.\n");
	say(QCTNAME(TP)+" moves block of rock little to the side revealing "+
	  "small brooch that was under the block.\n");
	return 1;
    }
    TP->catch_msg("You summon all your strength and move block of the rock "+
      "little to the side.\n");
    say(QCTNAME(TP)+" moves block of the rock little to the side.\n");
    return 1;
} 

int enter_hole(string arg){
    NF("Enter what?\n");
    if(arg != "hole") return 0;
    TP->catch_msg("You squeeze your body through the hole...\n");
    say(QCTNAME(TP)+" leaves through hole in wall.\n");
    tell_room(CAVE_DIR+"d6",QCTNAME(TP)+" enters room trough "+
      "hole in wall.\n");
    TP->move_living("M",CAVE_DIR+"d6");
    return 1;
}
