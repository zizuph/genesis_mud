/* goblin caves */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define CAVE_DIR MISTY_DIR + "gcaves/"

int brooch_in_room=1;

void
prepare_brooch()
{
  brooch_in_room=1;
}

create_room()
{
  object door;

  seteuid(getuid());

  add_prop(ROOM_I_LIGHT, 0);
  add_prop(ROOM_I_INSIDE, 1);

    set_short("cell in prison");
    set_long("You are in a cell of the goblin prison. It is dark with wet "+
             "walls and it stinks. Not a nice place to stay.\n");
    add_item(({"wall","walls"}),BS("The walls are natural rock except the "+
              "northern wall that was built from big blocks of rock. Now "+
              "one block is removed from the wall revealing a hole. The block "+
              "itself is lying under the hole.\n"));
    add_item("blocks",BS("Big blocks of dark cold rock. The walls are usually "+
              "made from such blocks.\n"));
    add_item("block",BS("A big block of dark cold rock. The walls are usually "+
              "made from such blocks. This one was obviously in the wall "+
              "before someone removed it.\n"));
    add_item("hole",BS("Someone removed a block from the wall making a hole. "+
              "You may be able to squeeze through it.\n"));

    door = clone_object(CAVE_DIR + "grating_1_d");
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
    clone_object(OBJ_DIR+"brooch")->move(TO);
    TP->catch_msg("You summon all your strength and move the block of rock "+
                  "a little to the side. You reveal a small brooch that was "+
                  "hidden under the block.\n");
    say(QCTNAME(TP)+" moves the block of rock a little to the side revealing "+
              "a small brooch that was under it.\n");
    return 1;
  }
  TP->catch_msg("You summon all your strength and move the block of the rock "+
                "a little to the side.\n");
  say(QCTNAME(TP)+" moves the block of the rock a little to the side.\n");
  return 1;
} 

int enter_hole(string arg){
  NF("Enter what?\n");
  if(arg != "hole") return 0;
  TP->catch_msg("You squeeze your body through the hole...\n");
  say(QCTNAME(TP)+" leaves through the hole in wall.\n");
  tell_room(CAVE_DIR+"d6",QCTNAME(TP)+" enters the room through "+
                                       "the hole in wall.\n");
  TP->move_living("M",CAVE_DIR+"d6");
  return 1;
}
