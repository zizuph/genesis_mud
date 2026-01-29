/* This addition to /d/Krynn/std/room provides a means to simply
 * set a table name which contains npc/object pathnames.
 * See 'kman random_objects' for details on how the random
 * tables look. All random tables must be located in
 * /d/Krynn/common/rndtables/   !!!!
 *
 *
 * created by:
 * ~Aridor, 09/96
 *
 * updates:
 *
 */

#include "/d/Krynn/common/defs.h"
#include RND_MEET
#define TABLEPATH "/d/Krynn/common/rndtables/"

/* Variables */
static string auto_reset_table = 0;
/* the table with object pathnames */
static int    auto_reset_num = 0;
/* the number of objects to clone */
static int    auto_reset_slow_clone = 0;
/* clone slowly (alarm) instead of all at once. */
object        *auto_reset_objs = 0;
/* contains the list of objects that were cloned. */


/* Function name: auto_reset_move_hook
 * Arguments:     ob (the object that was cloned)
 * Description:   Called after the moving the object to the room.
 *                Redefine this function if you want something
 *                special to happen additionally
 *                (eg. display a message).
 */
public void
auto_reset_move_hook(object ob)
{
}

/* Function name: auto_reset_clone
 * Description:   Called for each object to clone.
 *                Actually clones the object.
 */
static void
auto_reset_clone()
{
  int res;
  object ob;

  ob = GET_RANDOM_OBJECT(auto_reset_table);
  auto_reset_objs += ({ ob });

  if (living(ob))
    res = ob->move_living("xx",TO);
  else
    res = ob->move(TO);
  if (res)
    ob->remove_object();
  auto_reset_move_hook(ob);
}

/* Function name: automatic_reset
 * Description:   Called by reset_room to start the random cloning.
 */
static void
automatic_reset()
{
  int i;

  if (!auto_reset_num || !auto_reset_table)
    return;

  if (!auto_reset_objs)
    auto_reset_objs = ({});
  for(i=sizeof(auto_reset_objs);i<auto_reset_num;i++)
  {
      if (i == sizeof(auto_reset_objs))
	auto_reset_clone();
      else
	set_alarm(itof(i*auto_reset_slow_clone),0.0,"auto_reset_clone");
  }
}

/* Function name: set_auto_reset
 * Arguments:     table: pathname of the random table (all tables must be in
 *                       /d/Krynn/common/rndtables/, so you can leave that out)
 *                num (default: 1): the number of objects to clone each reset.
 *                slowly (default: 0): clone slowly, ie. with an alarm.
 *                       0 means clone immediately, a higher number means more
 *                       delay.        
 * Description:   Set the pathname of the table and (optionally)
 *                the number of objects to clone and how quickly cloning should
 *                be done.
 */
public varargs void
set_auto_reset(string table, int num=1, int slowly=0)
{
    if (table && stringp(table))
      auto_reset_table = (table[0..0] == "/" ? table : TABLEPATH + table);
    else
      auto_reset_table = 0;
    auto_reset_num = num;
    auto_reset_slow_clone = slowly;
}

/* Function name: set_auto_reset_number
 * Arguments:     num
 * Description:   Set the number of objects to clone per reset
 */
public void
set_auto_reset_number(int num)
{
  auto_reset_num = num;
}

/* Function name: set_auto_reset_slow_clone
 * Arguments:     num
 * Description:   Set the clone delay (0: immediately)
 */
public void
set_auto_reset_slow_clone(int num)
{
  auto_reset_slow_clone = num;
}

/* Function name: query_auto_reset_table
 * Returns:       The table from which to clone the objects.
 */
public string
query_auto_reset_table()
{
  return auto_reset_table;
}

/* Function name: query_auto_reset_number
 * Returns:       The number of objects to clone per reset
 */
public int
query_auto_reset_number()
{
  return auto_reset_num;
}

/* Function name: query_auto_reset_objects
 * Returns:       The objects that have been cloned in the last resets
 */
public object*
query_auto_reset_objects()
{
  return auto_reset_objs;
}
