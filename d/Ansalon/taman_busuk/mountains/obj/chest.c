/* Navarre June 2006, added check so the chest is not accessible 
 * if the knight is still alive
 */

inherit "/std/receptacle";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"

object webnet;
object knight;

void
create_container()
{
    set_name("chest");
    set_adj("heavy");
    add_adj("wooden");
    set_short("@@short_descr");
    set_pshort("grand oak chests");
    set_long("@@long_descr");
    set_key(7111111);
    set_pick(60);

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
    return "heavy wooden chest";
}

string
long_descr()
{
    return "This crude chest made of heavy wood with a large iron lock.\n";
}


public int
do_default_open(string str)
{
    if(!strlen(str) || !parse_command(str, ({}), "[the] [heavy] [wooden] 'chest'"))
    {
      notify_fail("Open what?\n");
      return 0;
    }

    knight = present("garren", environment(this_object()));   
    if(knight && knight!=this_player())
    {
      this_player()->catch_tell("There is no way to get to the chest with the knight still here.\n");
      return 1;
    }
  return ::do_default_open(str);
}

public int
do_default_close(string str)
{
    if(!strlen(str) || !parse_command(str, ({}), "[the] [heavy] [wooden] 'chest'"))
    {
      notify_fail("Close what?\n");
      return 0;
    }
    knight = present("garren", environment(this_object()));

    if(knight && knight!=this_player())
    {
      this_player()->catch_tell("There is no way to get to the chest with the knight still here.\n");
      return 1;
    }
  return ::do_default_close(str);
}

public int
do_default_lock(string str)
{
    if(!strlen(str) || !parse_command(str, ({}), "[the] [heavy] [wooden] 'chest' [with] [key]"))
    {
      notify_fail("Lock what with what?\n");
      return 0;
    }
    knight = present("garren", environment(this_object()));
    if(knight && knight!=this_player())
    {
      this_player()->catch_tell("There is no way to get to the chest with the knight still here.\n");
      return 1;
    }

  return ::do_default_lock(str);
}

public int
do_default_unlock(string str)
{
    if(!strlen(str) || !parse_command(str, ({}), "[the] [heavy] [wooden] 'chest' [with] [key]"))
    {
      notify_fail("Unlock what with what?\n");
      return 0;
    }
    knight = present("garren", environment(this_object()));

    if(knight && knight!=this_player())
    {
      this_player()->catch_tell("There is no way to get to the chest with the knight still here.\n");
      return 1;
    }
    return ::do_default_unlock(str);
}

public int
do_default_pick(string str)
{
    if(!strlen(str) || !parse_command(str, ({}), "[the] [heavy] [wooden] 'chest'"))
    {
      notify_fail("Pick what?\n");
      return 0;
    }
    knight = present("garren", environment(this_object()));
    if(knight && knight!=this_player())
    {
      this_player()->catch_tell("There is no way to get to the chest with the knight still here.\n");
      return 1;
    }
  return ::do_default_pick(str);
}
