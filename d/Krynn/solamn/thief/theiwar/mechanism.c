/* created by Aridor, 04/23/94 */

#include "../local.h"

inherit ROOM_BASE

#include <cmdparse.h>
#include <ss_types.h>
#include <macros.h>
#include <formulas.h>
#define  STR(who)              (who)->query_base_stat(SS_STR)
#define  FIXED                 31
                        /*used in prop to see if player did all by himself
                          bits: 1: oil chains
			        2: oil cogwheels
				4: sharpen pin
				8: untangle chains
			       16: replace broken cogwheel
			       */
#define  UNFIXED               128 /* entangle everything */
#define  DID_MOVE              64  /* closed/opened the gate */
#define  SOLVED_THE_QUEST      (FIXED | UNFIXED | DID_MOVE)
#define  QUEST_GROUP           2
#define  QUEST_BIT             12
#define  QUEST_EXP             40000
                         /* there are no real hints of its existence */
#define  EXTRA_EXP1            3000 /* visited the library */
#define  EXTRA_EXP2            7000 /* read the runes himself */
#define  GATE_IS_CLOSED        (DOORROOM->query_gate_state())
#define  QUEST_LOG             "/d/Krynn/common/log/quests/dwarfgate"
#define  PLAYER_I_READ_RUNES   "_player_i_read_runes"
#define  PLAYER_I_VISITED_LIBRARY "_player_i_visited_library"

/*prototype*/
void shut_door_again();

static int cog_broken = 1;  /*0 whole;     1 broken */
static int cog = 0;         /*0 unoiled;   1 oiled; 2 done oiling */
static int chain = 0;       /*0 messed up; 1 fixed; 2 oiled; 3 both*/
static int pins = 0;        /*0 not sharp; 1 sharp */
int how_many = 0;

void
reset_room()
{
    if (sizeof(all_inventory(TO)))
      return;
    if (DOORROOM->query_door_state() == 5)
      shut_door_again();
    if (!cog_broken || cog || chain || pins)
      {
	  if (random(8))
	    return;
	  cog_broken = 1; /* broken */
	  cog = 0;        /* unoiled */
	  chain = 0;      /* messed up */
	  pins = 0;       /* not sharp */
      }
}


void
create_room()
{
    set_short("The mechanism room.\nThere is one obvious exit: out");
    set_long("You are in a tiny narrow room with a lot of pins, cogwheels " +
	     "and chains all around you. There is an opening to the south, " +
	     "it is currently open.\nThere is one obvious exit: out.\n");
    DARK;
    INSIDE;

    add_exit(DOORROOM,"out","@@close_exit_after");
    add_exit(DOORROOM,"south","@@close_exit_after");
    set_noshow_obvious(1);

    add_item(({"pin","cogwheel","chain"}),"There are lots of them!\n");
    add_item(({"pins"}),"@@pin_state");
    add_item(({"cogwheels"}),"@@cogwheel_state");
    add_item(({"broken cogwheel"}),"@@broken_cogwheel_state");
    add_item(({"chains"}),"@@chain_state");
    add_item(({"holes","hole"}),
	     "There are several holes in the walls, through each of the " +
	     "holes, a chain disappears into the rock.\n");

    add_prop(ROOM_I_NO_EXTRA_DESC,1);
    add_prop(ROOM_I_NO_EXTRA_EXIT,1);

    add_cmd_item(({"pins","pin"}),({"sharpen"}),"@@sharpen_pin");
    add_cmd_item(({"chains","chain"}),
		 ({"untangle","disentangle","extricate","order","sort"}),
		 "@@untangle_chain");
    add_cmd_parse("[the] 'chain' / 'chains' [on] [over] [cogwheels] [cogwheel]",
		  ({"place","put","hang"}),"@@untangle_chain");
    add_cmd_item(({"pins","pin","chains","chain","cogwheel","cogwheels"}),
		 ({"entangle","mess","intricate","screw","hack","cut","jam",
		     "break"}), "@@mess_it_all_up@@");
    add_cmd_item(({"broken cogwheel","cogwheel"}),({"fix","replace"}),
		 "@@replace_cogwheel");
    add_cmd_item(({"cogwheels","cogwheel"}),({"oil"}),
		 "@@oil_cogwheels");
    add_cmd_item(({"oil on cogwheels","oil on cogwheel"}),({"pour"}),
		 "@@oil_cogwheels");
    add_cmd_item(({"chains","chain"}),({"oil"}),
		 "@@oil_chain");
    add_cmd_item(({"oil on chains","oil on chain"}),({"pour"}),
		 "@@oil_chain");
    seteuid(getuid(TO));
    restore_object(NUMBER_SOLVED);
}

void
fix_prop(object who, int what)
{
    int prp = who->query_prop(PLAYER_I_DWARFGATE);
    who->add_prop(PLAYER_I_DWARFGATE, prp | what);
}


void
shut_door_again()
{
    (DOORROOM)->shut_door_again();
}

int
close_exit_after()
{
    set_alarm(3.0,0.0,"shut_door_again");
    return 0;
}


string
pin_state()
{
    string str = "The pins are there to hold the chains in place. For each " +
      "of the three chains, there is a pin locked into the chain securing " +
      "it. ";
    if (pins == 0) /* not sharp */
      return str + "They still look like they cannot function though. One " +
	"of the pins is not sharp enough to hook the chain in place.\n";
    return str + "The pins look perfect, and every one is able to hold " +
      "its chain in place.\n";
}


string
cogwheel_state()
{
    string str = "The chains run around three cogwheels. These cogwheels " +
      "fill most of the room. The cogwheels are connected with each other " +
      "by a bunch of smaller cogwheels. ";
    if (cog_broken)
      str += "One of the smaller cogwheels is broken. ";
    if (cog == 0) /* unoiled */
      return str + "The cogwheels are all rusty and almost immovable.\n";
    if (cog == 1) /* oiled, but not finished */
      return str + "The cogwheels are oiled, but it will take a while " +
	"before the oil has losened the rust.\n";
    return str + "The cogwheels are oiled, and look almost as good as new.\n";
}

string
broken_cogwheel_state()
{
    if (cog_broken) /* broken */
      return "The broken cogwheel is about a foot in diameter and you " +
	"notice that apart from the crack through the middle of it, some " +
	"teeth are missing also.\n";
    return "You find no broken cogwheel.\n";
}

string
chain_state()
{
    string str = ("There are three big and heavy chains in this small room. " +
		  "Two of the chains disappear into holes in the southeastern " +
		  "wall, whereas the third chain leads to the northwest, also " +
		  "into small holes in the wall. ");

    if (chain == 0) /* messed up */
      return (str + "The chains are all rusty" +
	      (pins == 0 /* not sharp */ ? ". The pins fixing the chains, " +
	       "as well as the chains themselves, " : " and ") +
	      "are out of place and hanging loose. The chains tangle beside the " +
	      "cogwheels, instead of lying neatly over them.\n");
    if (chain == 1) /* fixed, not oiled */
      return str + "The chains are all rusty. At least they are in place.\n";
    if (chain == 2) /* oiled, not fixed  */
      return str + "The chains are freshly oiled but still out of place and " +
	"hanging loose, beside the cogwheels instead of lying neatly over them.\n";
    return str + "The chains are freshly oiled and back in place where they " +
      "should be.\n";
}

int
oil_chain()
{
    mixed *oil = FIND_STR_IN_OBJECT("oil",TP);
    object the_oil;
    NF("It is too dark to see.\n");
    if (!CAN_SEE_IN_ROOM(TP))
      return 0;
    if (oil && sizeof(oil))
      {
	  the_oil = oil[0];
	  if (function_exists("remove_oil",the_oil))
	    {
		if (the_oil->query_amount() >= 500)
		  the_oil->remove_oil(500);
		else
		  {
		      write("You don't have enough oil.\n");
		      return 1;
		  }
	    }
	  else
	    the_oil->remove_object();

	  write("You pour the oil on the chains.\n");
	  fix_prop(TP,1);
	  if (chain == 0 || chain == 2)
	    chain = 2; /* oiled */
	  else
	    chain = 3; /* oiled & fixed */
      }
    else
      write("You don't have any oil.\n");

    return 1;
}

void
fully_oiled()
{
    tell_room(TO,"A drop of oil drops onto the floor.\n");
    cog = 2; /* done oiling */
}

int
oil_cogwheels()
{
    mixed *oil = FIND_STR_IN_OBJECT("oil",TP);
    object the_oil;
    NF("It is too dark to see.\n");
    if (!CAN_SEE_IN_ROOM(TP))
      return 0;
    if (oil && sizeof(oil))
      {
	  the_oil = oil[0];
	  if (function_exists("remove_oil",the_oil))
	    {
		if (the_oil->query_amount() >= 300)
		  the_oil->remove_oil(300);
		else
		  {
		      write("You don't have enough oil.\n");
		      return 1;
		  }
	    }
	  else
	    the_oil->remove_object();

	  write("You pour the oil on the cogwheels.\n");
	  cog = 1; /* oiled */
	  fix_prop(TP,2);
	  set_alarm(28.0,0.0,"fully_oiled");
      }
    else
      write("You don't have any oil.\n");

    return 1;
}

int
replace_cogwheel()
{
    mixed *cogs = FIND_STR_IN_OBJECT("_cogwheel_",TP);
    object the_cog;
    NF("It is too dark to see.\n");
    if (!CAN_SEE_IN_ROOM(TP))
      return 0;
    if (cogs && sizeof(cogs))
      {
	  NF("You find no broken cogwheel.\n");
	  if (cog_broken == 0)
	    return 0;
	  if (TP->test_bit("Krynn",2,18))/* solved the furnace quest!*/
	    {
		the_cog = cogs[0];
		the_cog->remove_object();
		write("You replace the broken cogwheel with the new one.\n");
		cog_broken = 0; /* whole */
		fix_prop(TP,16);
	    }
	  else
	    {
		the_cog = cogs[0];
		the_cog->remove_object();
		write("You try to replace the broken cogwheel with the new " +
		      "one, but you must have done something wrong. The new " +
		      "cogwheel simply crumbles in your hands!\n");
	    }
      }
    else
      write("You don't have another cogwheel to replace the broken one.\n");

    return 1;
}

int
sharpen_pin()
{
    mixed *stone = FIND_STR_IN_OBJECT("sharpening stone",TP);
    if (!stone || stone == ({}))
      stone = FIND_STR_IN_OBJECT("whetstone",TP);
    NF("It is too dark to see.\n");
    if (!CAN_SEE_IN_ROOM(TP))
      return 0;
    if (stone && sizeof(stone))
      {
	  if (pins == 0) /* not sharp */
	    {
		write("You set to work, and sharpen the tip of the pin.\n");
		pins = 1; /* sharp */
		fix_prop(TP,4);
	    }
	  else
	    write("You try to sharpen the tip of the pin, but you find it " +
		  "sharpened already.\n");
      }
    else
      write("You don't have a sharpening stone.\n");
    return 1;
}

int
untangle_chain()
{
    NF("It is too dark to see.\n");
    if (!CAN_SEE_IN_ROOM(TP))
      return 0;
    if (chain & 1) /* fixed */
      write("The chains are all perfectly in place already.\n");
    else if (STR(TP) < 40)
      write("You disentangle the chains and try to heave them up onto the " +
	    "cogwheels, but you find they are just too heavy for you.\n");
    else
      {
	  write("You disentangle the chains and try to heave them up onto " +
		"the cogwheels. It is hard work, since the chains are quite " +
		"heavy, but finally you have it all done.\n");
	  chain |= 1;
	  fix_prop(TP,8);
      }
    return 1;
}

int
mess_it_all_up(string what)
{
    int extra = 0, al_change = 0, align;
    string str2, str = "";
    NF("It is too dark to see.\n");
    if (!CAN_SEE_IN_ROOM(TP))
      return 0;
    if (STR(TP) <= random(10) + 40)
      {
	  write("You try your best, but the chains are secured into place.\n");
	  return 1;
      }
    if (what == "chains")
      write("You pull hard on the chains and manage to get them all " +
	    "entangled. While you mess around, the pins and cogwheels " +
	    "securing the chains break and get all out of place, too.\n");
    else if (what == "pins")
      write("You pull hard on the pins and manage to break them. While you " +
	    "mess around, the chains fall off the cogwheels and a cogwheel " +
	    "breaks and get all out of place, too.\n");
    else if (what == "cogwheels")
      write("You pull hard on the cogwheels and manage to break one. While " +
	    "you mess around, the chains and pins securing the chains " +
	    "break and get all out of place, too.\n");
    else
      write("You pull hard and the room collapses.\n");
    pins = 0;
    cog_broken = 1;
    chain = 0;
    cog = 0;
    fix_prop(TP, UNFIXED);
    if (TP->query_prop(PLAYER_I_DWARFGATE) == SOLVED_THE_QUEST)
      {
	  al_change = ((GATE_IS_CLOSED) ? -1200 : 1200);
	  align = TP->query_alignment();
	  if ((TP->query_alignment() > 300 && GATE_IS_CLOSED) ||
	      (TP->query_alignment() < -300 && !GATE_IS_CLOSED))
	    {
		write("Your doing does not match your spirit! " +
		      "You don't feel more experienced.\n");
		write_file(QUEST_LOG,extract(ctime(time()), 4, 15)
			   + " " + TP->query_name() + " fail\n");
	    }
	  else
	    {
		if (TP->query_prop(PLAYER_I_VISITED_LIBRARY) & 1)
		  extra += EXTRA_EXP1;
		if (TP->query_prop(PLAYER_I_READ_RUNES))
		  extra += EXTRA_EXP2;
		if (extra)
		  str = "much ";
		write("You have fulfilled your deed!\n");
		if (align * al_change > 0)
		  str2 = "done the correct";
		else
		  str2 = "not done the wrong";
		if (GATE_IS_CLOSED)
		  write("You have once again brought eternal darkness upon " +
			"the dwarves. Your spirit of mind claims you have " +
			str2 + " thing.\n");
		else
		  write("You have once again brought the wonders of light " +
			"to the dwarves. Your spirit of mind claims you " +
			"have " + str2 + " thing.\n");
		TP->remove_prop(PLAYER_I_DWARFGATE);
		if (TP->test_bit("Krynn", QUEST_GROUP, QUEST_BIT))
		  {
		      write("You have already done this quest!\n");
		      return 1;
		  }
		write("You feel " + str + "more experienced!\n");
		TP->set_bit(QUEST_GROUP, QUEST_BIT);
		extra += QUEST_EXP;

		if (TP->query_exp() < extra)
		    extra = TP->query_exp();

		TP->add_exp(extra, 0);

		K_QUEST_LOG("quest", "Dwarf gate quest (" +
			    (GATE_IS_CLOSED?"Evil/Closed":"Good/Opened") +
			    ")", TP, extra);
		
		TP->adjust_alignment(al_change);

		how_many++;
		save_object(NUMBER_SOLVED);
	    }
      }
    else
      write("You haven't done all of the quest by yourself! No reward for " + 
	    "you yet.\n");
    return 1;
}

int
break_pin(string str)
{
    return mess_it_all_up("pin");
}

int
break_chain(string str)
{
    return mess_it_all_up("chain");
}

int
break_cogwheel(string str)
{
      return mess_it_all_up("cogwheel");
}

int
gate_can_be_moved(object who)
{
    int i = who->query_prop(PLAYER_I_DWARFGATE);
    if (i != FIXED)
      return 0;
    if (STR(who) < 33)
      return 0;
    return (chain == 3 && cog == 2 && pins == 1 && cog_broken == 0);
}

void
shortcut()
{
    if (TP->query_name() != "Aridor")
      return;
    chain = 3;
    cog = 2;
    pins = 1;
    cog_broken = 0;
}




