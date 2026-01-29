/* 	this is a object of the volcano

	coder(s):	Deinonychus

	history:	DD.MM.YY	what done		who did
			31.03.93	created			Deinonychus

	purpose:	A place where the players can put their shoes on

	quests:		none
	special:	none

	to do:		none
	bug:		none known
*/


inherit "/std/container";
#include "objects.h"
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <cmdparse.h>

#define MAX_ITEMS 10
#define GETERROR "Please use 'Get' to get something from shoe-stand.\n"
#define PUTERROR "Please use 'Put' to put something on shoe-stand.\n"
#define DEBUG

string *players;	/* holding the playernames of the stored object */
object *objects;	/* holding the stored object */
int free;		/* number of free slots */

create_container()
{
  /* descriptions */

  set_name("shoe-stand");
  set_short("shoe-stand");
  set_long(BS("This shoe-stand is in perfect condition.\n"));

  /* properties */

  add_prop(OBJ_I_VALUE, 0);
  add_prop(OBJ_I_NO_GET, 1);
  add_prop(CONT_I_WEIGHT, 300);
  add_prop(CONT_I_MAX_WEIGHT, 50300);
  add_prop(CONT_I_VOLUME, 400);
  add_prop(CONT_I_MAX_VOLUME, 50400);
  add_prop(CONT_I_RIGID, 1);
  add_prop(CONT_M_NO_INS, PUTERROR);
  add_prop(CONT_M_NO_REM, GETERROR);
  players = allocate(MAX_ITEMS);
  objects = allocate(MAX_ITEMS);
  free = MAX_ITEMS;
} /* create_container */

/*****************************************************************************/

/*
 * Function name: init
 * Description:   add some commands to the player
 * Arguments:     none
 * Returns:       nothing
 */

void
init()
{ 
  ::init();
  add_action("do_put", "Put");
  add_action("do_take", "Take");
  add_action("do_take", "Get");
}

/*****************************************************************************/

/*
 * Function name: put
 * Description:   put something on the wardrobe
 * Arguments:     command
 * Returns:       0/1
 */

int
do_put(string command)
{
  object *obj;

  NF("Put what on what?\n");

  obj = CMDPARSE_WITH_ITEM(command, "putprep", "putfun", "in_player", "in_env");
#ifdef DEBUG
  write(sizeof(obj));
#endif
  if(!sizeof(obj))
    return 0;
  else
    return 1;
}

/*****************************************************************************/

/*
 * Function name: do_take
 * Description:   check if the wanted object belongs to the player
 * Arguments:     command
 * Returns:       0/1
 */

int
do_take(string command)
{
  int index;
  object *obj;

  NF("Take what from what?\n");

  obj = CMDPARSE_WITH_ITEM(command, "takeprep", "takefun", "in_cont", "in_env");

#ifdef DEBUG
  write(sizeof(obj) + "\n");
#endif

  if(!sizeof(obj))
    return 0;
  else
    return 1;
    
}

/*****************************************************************************/

/*
 * Function name:	putprep
 * Description:		check if preposition for put is right
 * Arguments:		preposition
 * Returns:		0/1
 */
int putprep(string prep)
{
  if(prep == "on")
    return 1;
  else
    return 0;
}

/*****************************************************************************/

/*
 * Function name:	takeprep
 * Description:		check if preposition for take is right
 * Arguments:		preposition
 * Returns:		0/1
 */
int takeprep(string prep)
{
  if(prep == "from")
    return 1;
  else
    return 0;
}

/*****************************************************************************/

/*
 * Function name:	putfun
 * Description:		check if given object is something to wear on feet 
 * Arguments:		object
 * Returns:		0/1
 */
int putfun(object obj)
{
  if(obj->query_at() != A_FEET && obj->query_at() != A_R_FOOT &&
     obj->query_at() != A_L_FOOT )
  {
    write("I don't think " + LANG_THESHORT(TO) + " is the right place to " +
      "put " + LANG_THESHORT(obj) + ".\n");
    return 1;
  }

  if(!free)
  {
    write("There's no free place on " + LANG_THESHORT(TO) + ".\n");
    return 1;
  }

  write("You put " + LANG_ASHORT(obj) + " on " + LANG_THESHORT(TO) + ".\n");
  say(QCNAME(TP) + " puts " + LANG_ASHORT(obj) + " on " +
      LANG_THESHORT(TO) + ".\n");
  TO->change_prop(CONT_M_NO_INS, 0);
 
  obj->move(TO);
  TO->change_prop(CONT_M_NO_INS, PUTERROR);
  objects[MAX_ITEMS - free] = obj;
  players[MAX_ITEMS - free] = TP->query_name();
  free--;
  return 1;
}

/*****************************************************************************/

/*
 * Function name:	takefun
 * Description:		check if given object belong to the player 
 * Arguments:		object
 * Returns:		0/1
 */
int takefun(object obj)
{
  int index;

  index = member_array(obj, objects);

  if(players[index] != TP->query_name())
  {
    write("I don't think " + LANG_THESHORT(obj) + " belongs to you.\n");
    return 1;
  }
  
  write("You take " + LANG_ASHORT(obj) + " from " + LANG_THESHORT(TO) + ".\n");
  say(QCNAME(TP) + " takes " + LANG_ASHORT(obj) + " from " +
      LANG_THESHORT(TO) + ".\n");
  TO->change_prop(CONT_M_NO_REM, 0);
  obj->move(TP);
  TO->change_prop(CONT_M_NO_REM, GETERROR);
  free++;
  objects[index] = objects[MAX_ITEMS - free];
  players[index] = players[MAX_ITEMS - free];
  objects[MAX_ITEMS - free] = 0;
  players[MAX_ITEMS - free] = 0;
  return 1;
}

/*****************************************************************************/

/*
 * Function name:	in_player
 * Description:		used for CMDPARSE_WITH_ITEM
 			check if given object is in players inventory
 * Arguments:		none
 * Returns:		0/1
 */
int in_player(object obj)
{
  if(member_array(obj, all_inventory(TP)) >= 0)
    return 1;
  else
    return 0;
}

/*****************************************************************************/

/*
 * Function name:	in_env
 * Description:		used for CMDPARSE_WITH_ITEM
 			check if given objects is in environement of player
 * Arguments:		none
 * Returns:		0/1
 */
int in_env(object obj)
{
  if(member_array(obj, all_inventory(environment(TO))) >= 0)
    return 1;
  else
    return 0;
}

/*****************************************************************************/

/*
 * Function name:	in_cont
 * Description:		used for CMDPARSE_WITH_ITEM
 			check if given objects is in this container
 * Arguments:		none
 * Returns:		0/1
 */
int in_cont(object obj)
{
  if(member_array(obj, all_inventory(TO)) >= 0)
    return 1;
  else
    return 0;
}

/*****************************************************************************/

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */


mixed *test(string command)
{
  mixed *item1;
  mixed *item2;
  string prep;

  (parse_command(command, environment(TP), "%i %w %i", item1, prep, item2));
  return item1;
}
