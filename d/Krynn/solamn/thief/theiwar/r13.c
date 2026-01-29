/* created by Aridor 05/19/94 */

#include "../local.h"

inherit LIGHTDARKROOM;

#include RND_MEET
#include <macros.h>
#include <ss_types.h>
#define  SAVE_FILE   GUARDROOM
#define  DID_MOVE             64  /* moved the gate */

static object guard1, guard2, guard3;
static object *warning = ({ });
int lev_state = 1; /* 1 = up, 0 = down */

void
switch_gate_state()
{
    if (DOORROOM->query_gate_state())
      {
	  DOORROOM->open_the_gate();
	  lev_state = 0;
      }
    else
      {
	  DOORROOM->close_the_gate();
	  lev_state = 1;
      }
    save_object(SAVE_FILE);
}


void
reset_room()
{
    int i = 0;
    if (!guard1)
      {
	  guard1 = RANDOM_MEET(THEIWARTABLE);
	  guard1->move_living("xxx",TO);
	  DOORROOM->add_inhabitant(guard1);
	  i++;
      }
    if (!guard2)
      {
	  guard2 = RANDOM_MEET(THEIWARTABLE);
	  guard2->move_living("xxx",TO);
	  DOORROOM->add_inhabitant(guard2);
	  i++;
      }
    if (!guard3)
      {
	  guard3 = RANDOM_MEET(THEIWARTABLE);
	  guard3->move_living("xxx",TO);
	  DOORROOM->add_inhabitant(guard3);
	  i++;
      }
    if (i >= 2)
      warning = ({ });
    if (random(6))
      return;
    /*switch_gate_state();*/
}


void
create_ld_room()
{
    set_short("In a small room");
    set_long("@@my_long");
    
    add_exit(THEIWAR + "r14", "west");
    
    add_prop(OBJ_S_WIZINFO, "To toggle the state of the great dwarfgate " +
	     "by hand, you can 'Call here switch_gate_state'.\n");
    
    add_item(({"lever","opening"}),
	     "@@lever_state");
    add_cmd_item(({"lever up","lever upwards","lever upward"}),
		 ({"push","pull","move"}),
		 "@@push_lever_up");
    add_cmd_item(({"lever"}),
		 ({"push","pull","move"}),
		 "@@push_lever");
    add_cmd_item(({"lever down","lever downwards","lever downward"}),
		 ({"push","pull","move"}),
		 "@@push_lever_down");
    seteuid(getuid(TO));

    restore_object(SAVE_FILE);
    reset_room();
}


string
my_long()
{
    return ("A small room which serves as the guardroom. " +
	    ((guard1 && E(guard1) == TO) || 
	     (guard2 && E(guard2) == TO) ||
	     (guard3 && E(guard3) == TO) ? "The room is currently " +
	     "occupied, even though you are not exactly sure what " +
	     "it is that these guards are guarding. " : "There " +
	     "is currently no one present here, and you can't help " +
	     "thinking there probably isn't anything worth guarding " +
	     "around anyway. ") + "From the south wall, a huge lever " +
	    "protrudes from a narrow opening.\n");
}


string
lever_state()
{
    if (lev_state)
      return "The lever is pointing upwards to the ceiling of the room.\n";
    else
      return "The lever is currently pointing downwards to the floor.\n";
}

int 
check_dwarf()
{
    object the_guard;
    if (guard1 && E(guard1) == TO)
      the_guard = guard1;
    else if (guard2 && E(guard2) == TO)
      the_guard = guard2;
    else if (guard3 && E(guard3) == TO)
      the_guard = guard3;
    if (the_guard && CAN_SEE(the_guard,TP))
      {
	  if (member_array(TP,warning) != -1)
	    {
		the_guard->command("say Now I've had it, you just stepped " +
				   "over the line.");
		if (guard1 && E(guard1) == TO)
		  guard1->attack_object(TP);
		if (guard2 && E(guard2) == TO)
		  guard2->attack_object(TP);
		if (guard3 && E(guard3) == TO)
		  guard3->attack_object(TP);
		return 1;
	    }
	  the_guard->command("say Leave that alone! I warn you!");
	  warning += ({ TP });
	  return 1;
      }
    return 0;
}

int
push_lever_down()
{
    NF("It is too dark to see.\n");
    if (!CAN_SEE_IN_ROOM(TP))
      return 0;
    if (check_dwarf())
      return 1;
    if (lev_state == 0)
      {
	  write("The lever is already pointing down.\n");
	  return 1;
      }
    if ((MECHANISM)->gate_can_be_moved(TP))
      {
	  (DOORROOM)->open_the_gate();
	  lev_state = 0;
	  save_object(SAVE_FILE);
	  if (TP->query_alignment() >= -300)
	    (MECHANISM)->fix_prop(TP, DID_MOVE);
	  write("You push the lever downwards.\n");
	  SAYBB(" pushes the lever downwards.\n");
	  if (TP->query_stat(SS_INT) > 40)
	    set_alarm(200.0,0.0,"realize",TP,"\n\n\n" +
		      "Hmm, you have the feeling something is still missing " +
		      "at the great Dwarfgate, but you just can't figure out " +
		      "what it could be.\n\n");
	  else if (TP->query_stat(SS_INT) > 50)
	    set_alarm(200.0,0.0,"realize",TP,"\n\n\n" +
		      "Suddenly you realize that anyone can just come by and " +
		      "close the great Dwarfgate again.\n\n");
      }
    else
      {
	  write("You try to push the lever downwards, but it seems " +
		"stuck and can't be moved!\n");
	  SAYBB(" tries in vain to push the lever down.\n");
      }
    return 1;
}

void
realize(object who, string str)
{
  if (!who->test_bit("Krynn",2,12))
    who->catch_msg(str);
}

int
push_lever_up()
{
    NF("It is too dark to see.\n");
    if (!CAN_SEE_IN_ROOM(TP))
      return 0;
    if (check_dwarf())
      return 1;
    if (lev_state == 1)
      {
	  write("The lever is already pointing up.\n");
	  return 1;
      }
    if ((MECHANISM)->gate_can_be_moved(TP))
      {
	  (DOORROOM)->close_the_gate();
	  lev_state = 1;
	  save_object(SAVE_FILE);
	  if (TP->query_alignment() <= 300)
	    (MECHANISM)->fix_prop(TP, DID_MOVE);
	  write("You push the lever upwards.\n");
	  SAYBB(" pushes the lever upwards.\n");
	  if (TP->query_stat(SS_INT) > 40)
	    set_alarm(200.0,0.0,"realize",TP,
		      "Hmm, you have the feeling something is still missing " +
		      "at the great gate, but you just can't figure out " +
		      "what it could be.\n");
	  else if (TP->query_stat(SS_INT) > 50)
	    set_alarm(200.0,0.0,"realize",TP,
		      "Suddenly you realize that anyone can just come by and " +
		      "raise the great gate again.\n");
      }
    else
      {
	  write("You try to push the lever upwards, but it seems " +
		"stuck and can't be moved!\n");
	  SAYBB(" tries in vain to push the lever up.\n");
      }
    return 1;
}

int
push_lever()
{
    if (lev_state == 0)
      return push_lever_up();
    else
      return push_lever_down();
}
