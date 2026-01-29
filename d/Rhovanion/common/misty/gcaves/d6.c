/* goblin caves */

inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

#define CAVE_DIR MISTY_DIR + "gcaves/"

int hole_i_is = 0;
int block_i_is = 0;
int block_is_loose = 0;
int alarm, locked;
object door;

void
reset_room()
{
  object *arr, room, locker;
  int i;

  if(sizeof(FILTER_LIVE(all_inventory(TO))))
  {
    set_alarm(500.0, 0.0, "reset_room");
    return;
  }
  if((room = find_object(CAVE_DIR+"d4")) && 
     sizeof(FILTER_LIVE(all_inventory(room))))
  {
    set_alarm(200.0, 0.0, "reset_room");
    return;
  }
  if((room = find_object(CAVE_DIR+"d5")) && 
     sizeof(FILTER_LIVE(all_inventory(room))))
  {
    set_alarm(500.0, 0.0, "reset_room");
    return;
  }

  arr = all_inventory(TO);
  if(room) arr += all_inventory(room);
  arr -= ({ door });

  if(sizeof(arr))
    for(i=0; i<sizeof(arr); i++)
      arr[i]->move(CAVE_DIR+"d12");

  locker = clone_object(CAVE_DIR + "locker");
  locker->move(TO);
  locker->command("unlock grating with key");
  locker->command("open grating");
  locker->remove_object();
  locked = 0;

  hole_i_is = 0;
  block_i_is = 0;
  block_is_loose = 0;
  remove_item("hole");
  remove_item("block");
  (CAVE_DIR+"d5")->prepare_brooch();
}

int
clean_up()
{
  reset_room();
  return 0;
}

void
create_room()
{
  object key;

  seteuid(getuid());

  add_prop(ROOM_I_LIGHT, 0);
  add_prop(ROOM_I_INSIDE, 1);

    set_short("cell in prison");
    set_long("You are in the cell in goblin prison. It is dark with wet "+
             "walls and it stinks. Not a nice place to stay.\n");
    add_item(({"wall","south wall","east wall","west wall",
               "north wall","walls"}),
              "The walls are natural rock except the "+
              "northern and southern walls that were build from big blocks "+
              "of rock. "+"@@hole_desc");
    add_item("blocks","Big blocks of dark cold rock. Walls are usually "+
              "made from such blocks.\n");

    door = clone_object(CAVE_DIR + "grating_2_d");
    door->move(TO);
    door->set_key("gcave_cell_no_2"); /* Tells the door which key fits. */
}

string
hole_desc(){
  if(hole_i_is) return "One block is removed from southern wall "+
                       "making a hole.\n";
  return "\n";
}

string
block_desc(){
  if(block_i_is) return "When you knock on it, it sounds somehow "+
                        "different than the other blocks in the wall.\n";
  return "You find no block.\n";
}

init()
{
    ::init();
    add_action("enter_hole", "enter");
    add_action("knock_on", "knock");
    add_action("smash_block", "smash");
    add_action("push_block", "push");
    add_action("pull_block", "pull");
}

int knock_on(string arg){
  NF("Knock on what?\n");
  if(arg != "on blocks") return 0;
  if(block_i_is || hole_i_is)
  {
    TP->catch_msg("You start again systematically knock on the blocks...\n"+
            "All other blocks sound similarly.\n");
    say(QCTNAME(TP)+" starts again systematically knock on the blocks..\n"+
            "All other blocks soud similarly.\n");
    return 1;
  }
  block_i_is = 1;
  add_item("block","@@block_desc");
  TP->catch_msg("You start systematically knock on the blocks...\n"+
          "Oops!!! This block in south wall sounds somehow different!\n");
  say(QCTNAME(TP)+" starts systematically knock on the blocks..\n"+
          "Oops!!! That block in south wall sounds somehow different!\n");
  return 1;
}

int smash_block(string arg){
  NF("Smash what?\n");
  if((!block_i_is) || (arg != "block")) return 0;
  block_is_loose += 1;
  TP->catch_msg("You smash the block...   BANG!!!!\n");
  say(QCTNAME(TP)+" smashes the block...   BANG!!!!\n");
  return 1;
}

int push_block(string arg){
  NF("Push what?\n");
  if((!block_i_is) || (arg != "block")) return 0;
  if(block_is_loose < 11)
  {
    TP->catch_msg("You push block with all your strength but it "+
                  "doesn't move at all.\n");
    say(QCTNAME(TP)+" pushes block with all "+TP->query_possessive()+
            " strength but it doesn't move at all.\n");
    return 1;
  }
  TP->catch_msg("You push block with all your strength...\n"+
                "It moves slooooowly until it falls to the other side.\n");
  say(QCTNAME(TP)+" pushes block with all "+TP->query_possessive()+
            " strength...\n"+
            "It moves slooooowly until it falls to the other side.\n");
  block_i_is = 0;
  hole_i_is = 1;
  add_item("hole","@@hole_desc");
  remove_item("block");
  return 1;
}

int pull_block(string arg){
  NF("Pull what?\n");
  if((!block_i_is) || (arg != "block")) return 0;
  TP->catch_msg("You try to pull block but you can't get firm grip.\n");
  say(QCTNAME(TP)+" tries to pull block but "+TP->query_pronoun()+
            " can't get firm grip.\n");
  return 1;
}

int enter_hole(string arg){
  NF("Enter what?\n");
  if((!hole_i_is) || (arg != "hole")) return 0;
  TP->catch_msg("You squeeze your body through the hole...\n");
  say(QCTNAME(TP)+" leaves through hole in wall.\n");
  tell_room(CAVE_DIR+"d5",QCTNAME(TP)+" enters room trough "+
                                       "hole in wall.\n");
  TP->move_living("M",CAVE_DIR+"d5");
  return 1;
}

void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if(!locked && !alarm && living(ob))
  {
    alarm = 1;
    set_alarm(5.0, 0.0, "make_trap");
  }
}

void
make_trap()
{
  object ob;

  if((ob = find_object(CAVE_DIR+"d4")) && 
     sizeof(FILTER_LIVE(all_inventory(ob))))
  {
    set_alarm(5.0, 0.0, "make_trap");
    return;
  }
  if((!(ob = find_object(CAVE_DIR+"d5")) || 
     !sizeof(FILTER_LIVE(all_inventory(ob)))) &&
     !sizeof(FILTER_LIVE(all_inventory(TO))))
  {
    alarm = 0;
    return;
  }
  alarm = 0;
  locked = 1;
  ob = clone_object(CAVE_DIR + "locker");
  ob->move(CAVE_DIR+"d4");
  ob->command("close grating");
  ob->command("lock grating with key");
  tell_room(TO,"You hear laugh from above.\n");
  tell_room(TO,"A male goblin voice shouts: Now you will stay there forever!!!!!\n");
  ob->command("shout Now you will stay there forever!!!!!");
  ob->remove_object();
}
