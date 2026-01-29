/* 	this is a object of the volcano

	coder(s):	Deinonychus

	history:	DD.MM.YY	what done		who did
			01.04.93	created			Deinonychus

	purpose:	none

	quests:		none
	special:	none

	to do:		unlock, open
	bug:		none known
*/


inherit "/std/container";
#include "objects.h"
#include <stdproperties.h>
#include <macros.h>

/* prototypes */
string long();
int do_lock(string arg);
int do_unlock(string arg);
int do_close(string arg);
int do_open(string arg);
reset_container();
  
/*
 * Function name:	create_container
 * Description:		createor
 * Arguments:		none
 * Returns:		none
 */
create_container()
{
  /* descriptions */

  set_name("cupboard");
  set_short("armour cupboard");
  set_pshort("armour cupboards");
  set_long("@@long@@");
  set_adj(({"armour"}));

    /* properties */

  add_prop(OBJ_I_VALUE, 0);
  add_prop(CONT_I_WEIGHT, 20000);
  add_prop(CONT_I_MAX_WEIGHT, 50000);
  add_prop(CONT_I_VOLUME, 10000);
  add_prop(CONT_I_MAX_VOLUME, 100000);
  add_prop(CONT_I_RIGID, 1);
  add_prop(OBJ_I_NO_GET, 1);
  add_prop(CONT_I_LOCK, 0);
  add_prop(CONT_I_CLOSED, 0);
  add_prop(CONT_I_TRANSP, 1);
  enable_reset();
  reset_container();
} /* create_container*/


/*
 * Function name: long
 * Description:   returns long description depending if closed or not
 * Arguments:     none
 * Returns:       long description
 */
string
long()
{
  if(query_prop(CONT_I_CLOSED))
    return BS("This cupboard is made for holding weapons. It has a " +
      "glass-door so you can see what's in it.\n");
  else
    return BS("This cupboard is made for holding weapons. The door is " +
      "wide open.\n");
}

/*
 * Function name: init
 * Description:   add commands to the player
 * Arguments:     none
 * Returns:       none
 */
init()
{
  ::init();
  add_action("do_lock", "lock");
  add_action("do_unlock", "unlock");
  add_action("do_open", "open");
  add_action("do_close", "close");
}

/*
 * Function name: do_lock
 * Description:   let a player lock the cupboard
 * Arguments:     arguments given to the command
 * Returns:       0/1
 */
int
do_lock(string arg)
{
  object obj1, obj2;
 
  NF("Lock what?\n");
  
  if(!arg)
    return 0;
    
  NF("Lock what with what?\n");

  if(!parse_command(arg, all_inventory(environment()) + all_inventory(TP), "%o 'with' %o", obj1, obj2))
    return 0;

  if(obj1 != TO)
    return 0;

  if(query_prop(CONT_I_LOCK))
  {
    NF("The cupboard is already locked.\n");
    return 0;
  }

  if(MASTER_OB(obj2) != OBJECT("c-key"))
  {
    NF("I'm afraid this is not the right key.\n");
    return 0;
  }

  write("You lock the cupboard with the key.\n");
  say(QCTNAME(TP) + " locks the cupboard.\n");
  change_prop(CONT_I_LOCK, 1);
  return 1;
}
 
/*
 * Function name: do_unlock
 * Description:   let a player unlock the cupboard
 * Arguments:     arguments given to the command
 * Returns:       0/1
 */
int
do_unlock(string arg)
{
  object obj1, obj2;
 
  NF("Unlock what?\n");
  
  if(!arg)
    return 0;
    
  NF("Unlock what with what?\n");

  if(!parse_command(arg, all_inventory(environment()) + all_inventory(TP), "%o 'with' %o", obj1, obj2))
    return 0;

  if(obj1 != TO)
    return 0;

  if(!query_prop(CONT_I_LOCK))
  {
    NF("The cupboard is not locked.\n");
    return 0;
  }

  if(MASTER_OB(obj2) != OBJECT("c-key"))
  {
    NF("I'm afraid this is not the right key.\n");
    return 0;
  }

  write("You unlock the cupboard with the key.\n");
  say(QCTNAME(TP) + " unlocks the cupboard.\n");
  change_prop(CONT_I_LOCK, 0);
  return 1;
}
 
/*
 * Function name: do_open
 * Description:   let a player open the cupboard
 * Arguments:     arguments given to the command
 * Returns:       0/1
 */
int
do_open(string arg)
{
  object obj;
 
  NF("Open what?\n");
  
  if(!arg)
    return 0;
    
  if(!parse_command(arg, environment(), "%o", obj))
    return 0;

  if(obj != TO)
    return 0;

  if(query_prop(CONT_I_LOCK))
  {
    NF("The cupboard is locked. You can't open it without a key.\n");
    return 0;
  }
  
  if(!query_prop(CONT_I_CLOSED))
  {
    NF("The cupboard is already open.\n");
    return 0;
  }

  write("You open the cupboard.\n");
  say(QCTNAME(TP) + " opens the cupboard.\n");
  change_prop(CONT_I_CLOSED, 0);
  return 1;
}
 
/*
 * Function name: do_close
 * Description:   let a player close the cupboard
 * Arguments:     arguments given to the command
 * Returns:       0/1
 */
int
do_close(string arg)
{
  object obj;
 
  NF("Close what?\n");
  
  if(!arg)
    return 0;
    
  if(!parse_command(arg, environment(), "%o", obj))
    return 0;

  if(obj != TO)
    return 0;

  if(query_prop(CONT_I_CLOSED))
  {
    NF("The cupboard is already closed.\n");
    return 0;
  }

  write("You close the cupboard.\n");
  say(QCTNAME(TP) + " closes the cupboard.\n");
  change_prop(CONT_I_CLOSED, 1);
  return 1;
}
  

/*
 * Function name: reset_container()
 * Description:   Resets the room.
 * Arguments:     none
 * Returns:       nothing
 */

void
reset_container()
{
  TO->change_prop(CONT_I_LOCK, 0);
  TO->change_prop(CONT_I_CLOSED, 0);

  if(!present("knife", TO))
    clone_object(WEAPON("toothknife"))->move(TO);
  if(!present("sword", TO))
    clone_object(WEAPON("hornsword"))->move(TO);
  if(!present("club", TO))
    clone_object(WEAPON("club"))->move(TO);
  if(!present("axe", TO))
    clone_object(WEAPON("axe"))->move(TO);
  if(!present("war-hammer", TO))
    clone_object(WEAPON("war-hammer"))->move(TO);

  TO->change_prop(CONT_I_LOCK, 1);
  TO->change_prop(CONT_I_CLOSED, 1);
}

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
