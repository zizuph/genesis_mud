/*
 * A chest for the disks of mishakal.
 */

inherit "/std/container";
#include "/d/Krynn/xak/xlocal.h"
#include <macros.h>
#include <filter_funs.h>
#include <money.h>


int lock;
object bottle;

void
create_container()
{
    set_name("chest");
    set_adj("large");
    set_long("A large ironbound chest with a very solid rusty looking lock.\n");
    
    add_prop(CONT_I_WEIGHT, 2500000); 	
    add_prop(CONT_I_MAX_WEIGHT, 22500); 	
    add_prop(CONT_I_VOLUME, 3000); 	
    add_prop(CONT_I_MAX_VOLUME, 20300);
    add_prop(CONT_I_CLOSED, 1); 
    add_item("lock", "@@lock");	
    
    add_prop(OBJ_I_VALUE, 400); 		
}

string
lock()
{
    if (lock)
      {
	  write("The lock is in a bad shape, it looks like it has been melted.\n");
	  return "";
      }
    write("The lock looks very sturdy and also quite rusty.\n");
    return "";
}

void
init()
{
    ::init();
    ADA("open");
    ADA("unlock");
    ADA("pour");
    ADA("pick");
}

int
pick(string str)
{
    NF("Pick what?\n");
    if (str != "lock" && str != "rusty lock")
      return 0;
    if (lock)
      return 0;
    write("The lock is just too rusty to be picked.\n");
    return 1;
}

int
open(string str)
{
    object *ob;
    int i;
    notify_fail("Open what?\n");
    if ((str == "chest") || (str == "large chest"))
      {
	  if (lock == 0)
	    {
		write(BS("You cannot open the chest, it is firmly locked.", 70));
		return 1;
	    }
	  ob = FILTER_LIVE(all_inventory(environment(this_object())));
	  for (i = 0; i < sizeof(ob); i++)
	    {
		if (ob[i]->query_name() == "Khisanth")
		  {
		      write(BS("The dragon places a claw on top of the chest and grins"
			       + " evilly at you.", 70));
		      return 1;
		  }
	    }
	  
	  add_prop(CONT_I_CLOSED, 0);
	  write(BS("You open the lid of the chest.", 70));
	  SAY(" opens the chest.");
	  return 1;
      }
    return 0;
}

int
unlock(string str)
{
    notify_fail("Unlock what?\n");
    if ((str == "chest") || (str == "large chest"))
      {
	  if (lock == 1)
	    {
		write(BS("The chest is already unlocked!", 70));
		return 1;
	    }
	  write(BS("You have no key to open this lock, in fact you doubt if"
		   + " such a key even exists!! Yet there must be some way to"
		   + " get rid of the lock..", 70));
	  return 1;
      }
    return 0;
}

int
pour(string str)
{
    int prp;
    NF("Pour what on what?\n");
    if ((str == "acid on lock") || (str == "acid from bottle on lock"))
      {
	  if (lock == 1)
	    {
		write(BS("What lock!", 70));
		return 1;
	    }
	  if (bottle = present("xaka_bottle", TP))
	    {
		bottle->remove_object();
		clone_object(OBJ + "bottle.c")->move(TP);
		write(BS("You pour the acid from the bottle onto the lock. You see the acid"
			 + " eat through the rusted lock with ease and after a few seconds"
			 + " the lock is dissolved.", 70));
		prp = TP->query_prop("_player_i_black_dragon_quest");
		prp |= 8;
		TP->add_prop("_player_i_black_dragon_quest",prp);
		MONEY_MAKE_SC(prp * 10 - 100 + random(30))->move(TO,1);
		MONEY_MAKE_GC(prp - 20 + random(5))->move(TO,1);
		say(QCTNAME(TP) + " pours acid on the chest lock.\n");
		set_long(BS("A large ironbound chest.", 70));
		lock = 1;
		return 1;
	    }
	  return 0;
      }
    return 0;
}


