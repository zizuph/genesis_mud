/* Flames that light a room */
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#define FLAME_DESC     \
   "All around, tiny flickering flames seem to illuminate the area.\n"

object    fire;

int check_light();

void create_object()
{
  set_name("flames");
  add_name("flame");
  add_name("elemental_flames");
  set_short("flames");
  set_long("Transparent, flickering flames that dance at the "
   + "edge of your perception.\n");

  remove_prop(OBJ_I_WEIGHT);
  remove_prop(OBJ_I_VOLUME);

  set_no_show_composite(1);

  add_prop(OBJ_M_NO_GET, "Your hand passes right throught the flames.\n");
  add_prop(OBJ_I_LIGHT, check_light);
}

void dormant()
{
  if(!objectp(fire))
  {
    remove_object();
    return;
  }

  fire->add_dormant_flame(this_object());
}

/*
 * We are only light if we are within one room of our
 * elemental master
 */
int check_light()
{
  object where = environment(this_object());
  string place;

  if(!objectp(fire) || !environment(fire))
  {
    set_alarm(0.0, 0.0, remove_object);
    return 0;
  }

  /* Without this, we get recursion errors */
  if(!where->query_prop(ROOM_I_IS))
    return 0;

  place = file_name(environment(fire));

  if(member_array(place, where->query_exit_rooms()) == -1)
  {
    dormant();
    return 0;
  }

  return 1;
}

void enter_env(object to, object from)
{
  ::enter_env(to, from);

  from->remove_my_desc(this_object());
  
  if(!to->query_prop(ROOM_I_IS))
    return;

  to->add_my_desc(FLAME_DESC, this_object());
}

varargs int moveto(object where, object caller)
{
  string place;

  if(present("elemental_flames", where))
  {
    dormant();
    return 0;
  }

  fire = caller;

  place = file_name(environment(fire));

  if(member_array(place, where->query_exit_rooms()) == -1)
  {
    dormant();
    return 0;
  }

  move(where, 1);
  tell_room(environment(this_object()), "Strange, transparent blue "
    + "flames start to flicker all around.\n");
  return 1;
}

void init()
{
  ::init();
  check_light();
}
  

void flicker()
{
  tell_room(environment(this_object()), "The tiny "
    +"flames flicked and dance, casting intricate shadows "
    +"all around.\n");
}

