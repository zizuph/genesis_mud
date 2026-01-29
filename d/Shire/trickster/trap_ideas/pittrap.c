/*
* /d/Shire/trickster/obj/pittrap.c
* By Dunstable, Oct 15, 1995
*
* Some additions and changes made by
* Igneous Sept, 1996
*/

#pragma save_binary

inherit "/std/object";
#include "/d/Shire/trickster/trickster.h"
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#define SHORT "Deep in a hole"
#define LONG "This hole is deeper than you thought coming down it,"+\
"and climbing out again is sure to be tiring work.\n"
#define HOLE "hole","You are deep down in a hole.\n"
#define TRAP_LAST_ROOM "trap_last_room"

/* Prototype */
int fall_in(object player);

/* Global Vars */
int not_ready = 1;
int trapqual = 50;
int trapsize = 50;
// Initialize the above vars to something
object traproom;
string trapsetter;

// Trapsize is set by the player making the trap,
// the larger the trap, the more likely one is to fall into it
// Trapqual is determined by the player's set traps and
// some other things, it determines how hard the trap is
// to see.
// Trapsetter = who set the trap
// Traproom = a flag to make sure we only clone one trap room for this trap


void
set_trapqual(int qual)
{
    trapqual = qual;
    return;
}

void
set_trapsize(int size)
{
    trapsize = size;
    return;
}

void
set_trapsetter(string who)
{
    trapsetter = who;
    return;
}

object
get_trap_room()
{
    FIXEUID
    //  chaged from /std/room because it had no domain link.
    traproom = clone_object("/d/Shire/trickster/obj/pit_room");
    traproom->set_short(SHORT);
    traproom->set_long(LONG);
    traproom->add_item(HOLE);
    return traproom;
}

void
create_object()
{
    set_name("trap");
    add_name("trickster_pit_trap");
    add_name(({"pit","leaves","tarpaulin"}));
    set_long("@@my_long");
    set_short("@@my_short");

    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_VOLUME);
    add_prop(OBJ_M_NO_GET,"You can't pick up the trap!\n");
}

string
my_long()
{
    int level;
    level = TP->query_skill(SS_FR_TRAP) + trapsize; 

    switch(level)
    {
    case 0..25:
	return "You find no trap.\n";
	break;
    case 26..60:
	return "Some leaves are gathered in a pile here.\n";
	break;
    case 61..90:
	return "This appears to be a pit type trap!\n";
	break;
    case 91..150:
	return "This is a pit type trap, which can be disabled.\n";
	break;
    default:
	return "";
	break;
    }

}

string
my_short()
{
    int level;
    level = TP->query_skill(SS_FR_TRAP) + trapsize;

    switch(level)
    {
    case 0..25:
	return "";
	break;
    case 26..60:
	return "pile of leaves";
	break;
    case 61..90:
	return "pile of leaves covering a tarpaulin";
	break;
    case 91..150:
	return "pile of leaves over a tarpaulin, covering a trap";
	break;
    default:
	return "";
	break;
    }
}

void
init()
{
    object tp;
    tp = this_player();

    ::init();
    add_action("do_disarm","disarm");
    add_action("do_disarm","disable");
    add_action("do_disarm","reveal");
    //   Quick flag so when it's created people don't fall in.
    if (not_ready)
    {
	not_ready = 0;
	return;
    }
    set_alarm(0.5,0.0,&fall_in(tp));

}

int
do_disarm(string str)
{
    int success;
    object dis_trap;

    if(!str)
    {
	write(capitalize(query_verb())+ " what?\n");
	return 1;
    }

    if((str != "trap") && (str != "pit") && (str != "pit trap"))
    {
	write(capitalize(query_verb())+ " what?\n");
	return 1;
    }

    if (TP->query_mana() < 20)
    {
	notify_fail("You are to mentally exhausted to disarm the "+str+"!\n");
	return 0;
    }
    //   Players lose mana for trying this.
    TP->add_mana(-10);

    if (TP->resolve_task(trapqual, ({SS_FR_TRAP,TS_DEX})) > 0)

      {
	  write("You successfully disarmed the pit trap.\n");
	  say(QCTNAME(TP) + " successfully disables a pit trap here.\n");
	  FIXEUID
	  dis_trap = clone_object(DIS_PIT_TRAP);
	  if (traproom)
	  {
	      dis_trap->set_trapped_room(traproom);
	  }
	  dis_trap->move(environment(TO));
	  TO->remove_object();
	  return 1;
      }

      write("You try to disable the trap, but you just don't think you managed it.\n");
      return 1;
  }



    int
    fall_in(object player)
    {
	int success;
	object getoutofjail;

	if(player->query_real_name() == trapsetter)
	{
	    player->catch_msg("You avoid your own trap and grin mischeviously, "+
	      "thinking of all the mischief it will cause.\n");
	    return 1;
	}

	success = player->resolve_task(trapqual, ({SS_AWARENESS, SS_FR_TRAP}));



	if(success >= trapqual + trapsize)
	{
	    player->catch_msg("You notice that the earth is a bit unsteady under "+
	      "your feet.\nYour keen sense notes that there is a trap here!\n");
	    return 1;
	}

	if(player->query_prop("_i_just_got_trapped"))
	{
	    player->catch_msg("You note the location of the trap here and fail to "+
	      "fall into it again.\n");
	    return 1;
	}

	FIXEUID /* Added by Elwing */
	getoutofjail = clone_object(PASS_OB);
	getoutofjail->move(player);
	player->catch_msg("You stumble and fall suddenly into a deep hole.\n");
	player->add_prop(TRAP_LAST_ROOM,environment(TO));
	if(traproom)
	{
	    player->add_prop(TRAP_LAST_ROOM,environment(TO));
	    player->move_living("M",traproom,1,0);
	    tell_room(environment(TO),QCTNAME(player)+ " disappears suddenly "+
	      "with a short yell.\n");

	    return 1;
	}
	player->move_living("M",get_trap_room(),1,0);
	tell_room(environment(TO),QCTNAME(player)+ " disappears suddenly "+
	  "with a short yell.\n");

	return 1;
    }
