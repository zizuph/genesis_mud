inherit "/std/receptacle";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <poison_types.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

int trap = 1;
object poison;

void
create_container()
{
    set_name("chest");
    set_adj("large");
    add_adj("wooden");
    set_short("@@short_descr");
    set_pshort("large wooden chests");
    set_long("@@long_descr");
    set_key(CHEST_KEY);
    set_pick(40);
    add_prop(OBJ_I_VALUE,120);
    add_prop(CONT_I_IN,1);
    add_prop(CONT_I_RIGID,0);
    add_prop(CONT_I_TRANSP,0);
    add_prop(CONT_I_WEIGHT, 2500000);
    add_prop(CONT_I_VOLUME,7500);
    add_prop(CONT_I_MAX_WEIGHT, 22500);
    add_prop(CONT_I_MAX_VOLUME,20300);
    add_prop(CONT_I_CLOSED, 1);
    add_prop(CONT_I_LOCK, 1);

    add_cmd_item(({"trap","poison needle"}),
      ({"remove","disarm"}),"@@remove_trap");
    add_item("lock","Ah hah! The lock has been trapped! " +
      "Probably to discourage thieves from picking it.\n");
    add_item(({"needle","poison needle","trap"}),
      "A poison needle trap. Those tampering with the lock " +
      "would likely get stung by it, unless they manage to have " +
      "the key or are skilled enough to disarm it.\n");

    seteuid(getuid());
}

int
remove_trap()
{
    object enemy = TP;
    if(trap == 0)
    {
	write("The trap is already disarmed.\n");
	return 1;
    }
    if(TP->query_skill(SS_FR_TRAP) < (random(50) + 21))
    {
	if(TP->query_skill(SS_FR_TRAP) < (random(60) + 1))
	{
	    write("Ack! You fumbled with the trap, setting it off!\n" +
	      "A poisoned needle pokes you in the finger!\n");
	    say(QCTNAME(TP) + " snarls in dismay as he " +
	      "accidently sets off the poison needle trap he " +
	      "was trying to remove.\n");

	    poison = clone_object("/std/poison_effect");
	    if(poison)
	    {
		poison->move(enemy);
		poison->set_time(2400);
		poison->set_interval(10);
		poison->set_strength(20);
		poison->set_damage(({POISON_FATIGUE, 175, 
		    POISON_HP, 15}));
		poison->start_poison();
	    }

	    trap = 0;
	    return 1;
	}
	write("You fail to remove the trap.\n");
	return 1;
    }
    write("You skillfully disarm the poison needle " +
      "trap guarding this chest.\n");
    say("With a smug grin, " +QTNAME(TP)+ " skillfully " +
      "disarms the trap guarding the chest.\n");
    trap = 0;
    return 1;
}

public int
do_default_pick(string str)
{
    object enemy = TP;

    if(!str || str != "lock on chest")
    {
	notify_fail("Pick what? The lock on chest?\n");
	return 0;
    }
    if(trap == 1)
    {
	write("You carelessly forgot to look for traps!\n" +
	  "You have just set off " +
	  "a poison needle into your finger!\n");

	poison = clone_object("/std/poison_effect");
	if(poison)
	{
	    poison->move(enemy);
	    poison->set_time(2400);
	    poison->set_interval(10);
	    poison->set_strength(20);
	    poison->set_damage(({POISON_FATIGUE, 175, 
		POISON_HP, 15}));
	    poison->start_poison();
	}

	trap = 0;
	return 1;
    }
    ::do_default_pick(str);
    return 1;
}

void
enter_inv(object obj, object from)
{
    if (living(obj))
    {
	write("You cannot put that into the chest.\n");
	return;
    }
    ::enter_inv(obj,from);
}


void
leave_inv(object obj, object to)
{
    ::leave_inv(obj,to);
}


string
short_descr()
{
    return "large wooden chest";
}

string
lock_descr()
{
    if(!trap)
	return "";

    if(TP->query_skill(SS_AWARENESS) > 70 ||
      TP->query_race_name() == "dwarf")
	return "You notice something unusual about the " +
	"lock on the chest, a poison needle trap craftily " +
	"hidden within the scroll work.";
    if(TP->query_skill(SS_AWARENESS) > 45)
	return "You can't pick what it is, but there " +
	"is something unusual about the lock on this " +
	"chest.";
    return "";
}

string
long_descr()
{
    return "This a long chest crafted from a very dark " +
    "wood by skilled hands. It looks rather old, as there " +
    "are faint marks of weathering on it. " +lock_descr() +
    "\n";
}
