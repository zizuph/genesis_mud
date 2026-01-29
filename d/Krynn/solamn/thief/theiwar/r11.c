/* created by Aridor 04/21/94 */

#include "../local.h"

inherit ROOM_BASE

#include <macros.h>
#include <ss_types.h>
#define SAVE_FILE      DOORROOM
#define CAVERN_LIST    ({DOORROOM, GUARDROOM, \
			 THEIWAR + "r12", \
			 THEIWAR + "r14", \
			 THEIWAR + "r15", \
			 THEIWAR + "r16", \
			 THEIWAR + "r17", \
			 THEIWAR + "r18", \
			 THEIWAR + "r19", \
			 THEIWAR + "r20", \
			 THEIWAR + "r21", \
			 THEIWAR + "r22", \
			 THEIWAR + "r23" })
#define LOCK_STATE       6
#define MECHA_EMPTY      (!sizeof(MECHANISM->subinventory()))

/*prototypes*/
void close_the_gate();

/*state of the gate*/
int gate_is_closed = 1;
/*state of the mechanism*/
static int state = 0;

object *inhabitants = ({ });


void
create_thief_room()
{
    set_short("The Gate");
    set_long("You are standing at the great gate. The hall continues " +
	     "northwest while sloping upwards from here, leading further " +
	     "into the mountain. " +
	     "The walls have been carved in with ornaments and runes." +
	     "@@door_description@@\n" +
	     "@@gate_description@@\n");
    add_exit(THEIWAR + "r12","northwest");
    add_exit(THEIWAR + "outside", "southeast","@@gate_closed");

    DARK;

    add_item(({"gate","great gate"}),
	     "The entire southeastern wall makes up the great gate, " +
	     "which in former times was opened frequently to let " +
	     "people in and out. @@gate_description@@\n");
    add_item("carvings","You look carefully at the carvings and you can " +
	     "see some ornaments but you also detect old runes.\n");
    add_item(({"runes"}), "@@runes");
    add_item("ornaments","These ornaments frame the runes, and looking " +
	     "closer you can see symbolized weapons, axes and hammers, " +
	     "as well as other tools, and objects of daily life, but " +
	     "you can also recognize figures of different sizes and shapes.\n");
    add_item(({"figures","figure"}),
	     "You recognize all humanoid races of Krynn: Dwarves, Humans, " +
	     "Elves, Gnomes, Kender, even Ogres, Goblins and Minotaurs.\n");
    add_item(({"kender","goblins","minotaurs"}),
	     "They are typical representatives of their race and they have " +
	     "been carved with great detail, protruding from the wall.\n");
    add_item(({"elves","gnomes","dwarves","humans","ogres"}),
	     "They are typical representatives of their race and they have " +
	     "been carved with great detail, protruding from the wall. You notice " +
	     "however that these specific figures somehow look very polished.\n");
    add_item(({"wall","walls","floor","ceiling"}),
	     "Everything is rock around here, walls, floor, ceiling. You can see " +
	     "some carvings on the walls.\n");
    add_cmd_item(({"runes"}),({"read"}), "@@runes");
    add_cmd_item(({"figures","figure","on figure","on figures"}),({"press","push"}),
		 "@@press_figure");
    add_cmd_item(({"dwarf","dwarves","on dwarf","on dwarves"}),({"press","push"}),
		 "@@press_dwarf");
    add_cmd_item(({"elf","elves","on elf","on elves"}),({"press","push"}),
		 "@@press_elf");
    add_cmd_item(({"human","humans","on human","on humans"}),({"press","push"}),
		 "@@press_human");
    add_cmd_item(({"kender","on kender"}),({"press","push"}),
		 "@@press_kender");
    add_cmd_item(({"ogre","on ogre","ogres","on ogres"}),({"press","push"}),
		 "@@press_ogre");
    add_cmd_item(({"goblin","goblins","on goblin","on goblins"}),({"press","push"}),
		 "@@press_goblin");
    add_cmd_item(({"gnome","gnomes","on gnome","on gnomes"}),({"press","push"}),
		 "@@press_gnome");
    add_cmd_item(({"minotaur","minotaurs","on minotaur","on minotaurs"}),
		 ({"press","push"}), "@@press_minotaur");
    seteuid(getuid(TO));
    restore_object(SAVE_FILE);
    if (!gate_is_closed)
      LIGHT;
    /*set_alarm(2.0,0.0,"toggle_rooms");*/
}

void
init()
{
    ADA("open");
    ADA("close");
    ::init();
}

int
open(string str)
{
    NF("Open what?\n");
    if (str == "gate" || str == "great gate")
      {
	  if (!gate_is_closed)
	    write("The gate is already open!\n");
	  else
	    write("You cannot see any means to open the gate " +
		  "here. It must be remote controlled.\n");
	  return 1;
      }
    return 0;
}

int
close(string str)
{
    NF("Close what?\n");
    if (str == "gate" || str == "great gate")
      {
	  if (gate_is_closed)
	    write("The gate is already closed!\n");
	  else
	    write("You cannot see any means to close the gate " +
		  "here. It must be remote controlled.\n");
	  return 1;
      }
    return 0;
}

void
toggle_rooms()
{
    if (gate_is_closed)
      return;
    CAVERN_LIST->make_light();
    inhabitants->make_good();
}

string
door_description()
{
    if (state == LOCK_STATE)
      return " A piece of the wall looks like it has been turned inside out.";
    return "";
}

string
gate_description()
{
    if (gate_is_closed)
      return "The great gate is closed.";
    return "The great gate is open, allowing light to flood into the room.";
}


int
gate_closed()
{
    if (!gate_is_closed)
      {
	  write("You walk out the gate.\n");
	  return 0;
      }
    write("The great gate is closed!\n");
    return 1;
}

void
close_the_gate2()
{
    tell_room(TO,"With a deafening crunching, the great gate settles " +
	      "into place. The light that come in from the outside " +
	      "is suddendly blocked out, plunging the room into utter " +
	      "darkness.\n" +
	      "Just as sudden as everything began, silence decends back " +
	      "onto the room.\n");
    DARK;
    gate_is_closed = 1;
    seteuid(getuid(TO));
    save_object(SAVE_FILE);
    CAVERN_LIST->make_dark();
    inhabitants->make_evil();
}

void
close_the_gate()
{
    tell_room(TO,"A sudden, loud, grinding noise jerks you up. You notice " +
	      "the great gate is starting to swing downwards, sealing " +
	      "off the exit!\n\n");
    set_alarm(7.0,0.0,"close_the_gate2");
}

void
open_the_gate2()
{
    tell_room(TO,"With a dangerous crunch, the gate has fully opened now " +
	      "and settled itself into place. Outside you have a splendid " +
	      "outlook on the Plains of Solamnia.\n");
}

void
open_the_gate()
{
    tell_room(TO,"A sudden, loud, grinding noise jerks you up. You notice " +
	      "a stream of light coming into the room, where you now can " +
	      "see the great gate slowly starting to swing upwards, " +
	      "revealing an exit to fresh air and clear blue sky.\n");
    LIGHT;
    gate_is_closed = 0;
    seteuid(getuid(TO));
    save_object(SAVE_FILE);
    CAVERN_LIST->make_light();
    inhabitants->make_good();
    set_alarm(7.0,0.0,"open_the_gate2");
}

string
runes()
{
    int lan = TP->query_skill(SS_LANGUAGE);
    int aln = TP->query_alignment();
    string str;
    NF("It is too dark to see.\n");
    if (!CAN_SEE_IN_ROOM(TP))
      return 0;
    if (TP->query_race() == "dwarf")
      lan += 16;
    if (aln >= 180)
      str = "sad and uncomfortable ";
    else if (aln <= -180)
      str = "beloved ";
    else
      str = "";
    if (lan > 31)
      {
	  TP->add_prop("_player_i_read_runes",1);
	  return ("The runes describe life under the mountain, the coming " +
		  "and going of visitors through this great gate, of " +
		  "merchants and vendors, of the sunshine outside, the " +
		  str + "darkness inside, and of happy and cheerful times. " +
		  "You can also read about the Graystone of Gargath, which " +
		  "lead to the creation of the dwarven race, and there is a " +
		  "book mentioned of this in the Great Library of " +
		  "Palanthas.\n");
      }
    if (lan > 23)
      return ("The runes describe life under the mountain, the coming and " +
	      "going of visitors through this great gate, of merchants and " +
	      "vendors, of the sunshine outside, the " + str + "darkness " +
	      "inside, and of happy and cheerful times.\n");
    if (lan > 15)
      return ("You take a hard effort and manage to decipher some of the " +
	      "runes. You learn about the sunshine outside and the beloved " +
	      "darkness inside, and how happy and cheerful times were.\n");
    if (lan > 5)
	return ("These are strange looking runes that you can identify as " +
		"dwarven.\n");
    return "You can't make anything of these runes.\n";
}

void
open_hole(object who)
{
    state = LOCK_STATE;
    who->catch_msg("The wall right in front of your face starts to move! " +
		   "You are quite baffled and you are even more surprised " +
		   "as the floor you are standing on moves into the " +
		   "opening.\n");
    if ((who->query_prop(PLAYER_I_DWARFGATE) & 64) &&
	(!gate_is_closed && who->query_alignment() > 300))
      who->catch_msg("Suddenly you realize that anyone can just come by " +
		     "and close the great gate again, maybe you should " +
		     "do something to prevent that?\n");
    else if ((who->query_prop(PLAYER_I_DWARFGATE) & 64) &&
	     (gate_is_closed && who->query_alignment() < -300))
      who->catch_msg("Suddenly you realize that anyone can just come by " +
		     "and open the great gate again, maybe you should " +
		     "do something to prevent that?\n");
    else if ((!gate_is_closed && who->query_alignment() > 300) || 
	     (gate_is_closed && who->query_alignment() < -300))
      who->catch_msg("\n\n\nYou get the certain feeling that to change the " +
		     "current state of the area would not be a wise thing " +
		     "to do for you as it would not match your spirit of  " +
		     "mind. You should please try again later, when your " +
		     "action may be able to change the situation towards " +
		     "your preferences.\n\n\n");
    who->move_living("into the opening", THEIWAR + "mechanism",1,0);
}

void
pop_door_to_mechanism(object who)
{
    if (E(who) != TO)
      return;
    who->catch_msg("You hear the sounds of a mechanism behind the wall " +
		   "starting to work.\n");
    tell_room(TO,"Strange clogging noises can be heard from behind the " +
	      "walls.\n",who);
    set_alarm(3.0,0.0,"open_hole",who);
}

int
press_figure()
{
    NF("It is too dark to see.\n");
    if (!CAN_SEE_IN_ROOM(TP))
      return 0;
    write("Which figure do you want to press on?\n");
    return 1;
}

int
mechanism_is_not_ok()
{
    if (state != LOCK_STATE)
      return 0;
    if (MECHA_EMPTY)
      set_alarm(1.0,0.0,"shut_door_again");
    return 1;
}

int
press_human()
{
    NF("It is too dark to see.\n");
    if (!CAN_SEE_IN_ROOM(TP))
      return 0;
    write("You press on the human figure...\nNothing happens.\n");
    if (mechanism_is_not_ok())
      return 1;
    if (state == 2)
      state = 3;
    else
      state = 0;
    return 1;
}
int
press_ogre()
{
    NF("It is too dark to see.\n");
    if (!CAN_SEE_IN_ROOM(TP))
      return 0;
    write("You press on the ogre figure...\nNothing happens.\n");
    if (mechanism_is_not_ok())
      return 1;
    if (state == 1)
      state = 2;
    else
      state = 0;
    return 1;
}

int
press_elf()
{
    NF("It is too dark to see.\n");
    if (!CAN_SEE_IN_ROOM(TP))
      return 0;
    write("You press on the elf figure...\nNothing happens.\n");
    if (mechanism_is_not_ok())
      return 1;
    state = 1;
    return 1;
}

int
press_gnome()
{
    NF("It is too dark to see.\n");
    if (!CAN_SEE_IN_ROOM(TP))
      return 0;
    write("You press on the gnome figure...\nNothing happens.\n");
    if (mechanism_is_not_ok())
      return 1;
    if (state == 3)
      state = 4;
    else
      state = 0;
    return 1;
}

int
press_dwarf()
{
    NF("It is too dark to see.\n");
    if (!CAN_SEE_IN_ROOM(TP))
      return 0;
    write("You press on the dwarf figure...\n");
    if (state < 4)
      {
	  write("Nothing happens.\n");
	  state = 0;
	  return 1;
      }
    if (mechanism_is_not_ok())
      {
	  write("You hear a click and a rumble but nothing happens.\n" +
		"You feel someone is blocking the mechanism.\n");
	  return 1;
      }
    write("You can hear something going on...\n");
    set_alarm(5.0,0.0,"pop_door_to_mechanism",TP);
    return 1;
}

int
press_goblin()
{
    NF("It is too dark to see.\n");
    if (!CAN_SEE_IN_ROOM(TP))
      return 0;
    write("You press on the goblin figure...\nYou hear a couple of clicks, " +
	  "then everything is silent again.\nNothing happens.\n");
    if (mechanism_is_not_ok())
      return 1;
    state = 0;
    return 1;
}

int
press_kender()
{
    NF("It is too dark to see.\n");
    if (!CAN_SEE_IN_ROOM(TP))
      return 0;
    write("You press on the kender figure...\nNothing happens.\n");
    return 1;
}

int
press_minotaur()
{
    NF("It is too dark to see.\n");
    if (!CAN_SEE_IN_ROOM(TP))
      return 0;
    write("You press on the minotaur figure...\nYou are unsure, but you " +
	  "may have heard something.\nNothing happens.\n");
    return 1;
}

int
query_gate_state()
{
    return gate_is_closed;
}

void
shut_door_again()
{
    if (state == LOCK_STATE)
      {
	  state = 0;
	  tell_room(TO,"You hear sounds from a shifting motion. The wall " +
		    "slides back into place.\n");
      }
}

void
add_inhabitant(object who)
{
    inhabitants += ({ who });
    if (!gate_is_closed)
      who->make_good();
    inhabitants -= ({ 0 });
}

