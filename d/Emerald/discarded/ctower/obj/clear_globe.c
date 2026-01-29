inherit "/std/container";

#include "../ctower.h"
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <composite.h>

#define WEIGHT_MIN 4500

static string pyr_color;
static string transform_file;

void create_container()
{
  object key;

  set_name(({ "globe", "ctower_globe" }));
  set_adj("crystal");
  set_adj("clear");
  set_short("crystal globe");
  set_long("A clear, crystal sphere, floating in mid-air.\n");
  remove_prop(OBJ_I_WEIGHT);
  remove_prop(OBJ_I_VOLUME);
  remove_prop(OBJ_I_VALUE);
  add_prop(CONT_I_CLOSED, 1);
  add_prop(CONT_I_TRANSP, 1);
  add_prop(OBJ_M_NO_GET, "The globe won't move.\n");

  setuid(); 
  seteuid(getuid());

  if (key = clone_object(CTOWER_OBJ + "key"))
  {
    key->move(this_object(), 1);
  }
}

int is_wand(object ob)
{
  return (ob && ob->id("phase_quest_wand"));
}

void destroy_globe()
{
  object *inv;

  tell_room(environment(), "The globe shatters!\n");

  if (sizeof(inv = all_inventory()))
  {
    tell_room(environment(), capitalize(COMPOSITE_DEAD(inv)) +
        " fall" + (sizeof(inv) == 1 ? "s" : "") + " to the floor.\n");

    inv->move(environment(), 1);
  }

  remove_object();
}

int feel(string str)
{
  object ob;

  if (!parse_command(str, ({ this_object() }), "[the] %o", ob))
  {
    return 0;
  }

  write("The surface of the globe if totally smooth--completely " +
      "featureless.\n");
  return 1;
}
   
void touch_it(int break_flag, object ob)
{
  if (!is_wand(ob))
  {
    if (!break_flag)
    {
      write("You touch the " + ob->short() + " to the globe.\n");
      return;
    }

    write("You hit the globe with the " + ob->short() + ".\n");
    if (ob->query_prop(OBJ_I_WEIGHT) > 4500)
    {
      destroy_globe();
    }
  }

  destroy_globe();
}

int touch(string str)
{
  string globe, wand;
  object globe_ob, pyr;
  mixed *oblist;
  int break_flag;

  if (!strlen(str))
  {
    return 0;
  }

  if (sscanf(str, "%s with %s", globe, wand) != 2)
  {
    globe = str;
  }

  if (!parse_command(globe, ({ this_object() }), "[the] %o", globe_ob))
  {
    notify_fail("Touch what?\n");
    return 0;
  }

  if (!strlen(wand))
  {
    write("You " + query_verb() + " the globe.\n");
    return 1;
  }

  notify_fail("Touch the globe with what?\n");
  if (!parse_command(wand, deep_inventory(this_player()), 
      "[the] %i", oblist) || !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
  {
    return 0;
  }

  break_flag = (query_verb() == "hit");
  for_each(oblist, &touch_it(break_flag));
  return 1;
}

void throw_it(object ob)
{
  write("You throw the " + ob->short() + " at the globe.\n");

  ob->move(environment(), 1);

  if (ob->query_prop(OBJ_I_WEIGHT) > WEIGHT_MIN || is_wand(ob))
  {
    destroy_globe();
  }
}

int throw(string str)
{
  string what, globe;
  object globe_ob;
  mixed *oblist;

  if (!strlen(str))
  {
    return 0;
  }

  if (sscanf(str, "%s at %s", what, globe) != 2) 
  {
    what = str;
  }

  notify_fail("Throw what?\n");
  if (!parse_command(what, deep_inventory(this_player()), "[the] %i",
       oblist) || !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
  {
    return 0;
  }

  if (!parse_command(globe, ({ this_object() }), "[the] %o", globe_ob))
  {
    notify_fail("Throw where?\n");
    return 0;
  }

  if (!sizeof(oblist = filter(oblist, &operator(==)(0) @
      &->query_prop(OBJ_M_NO_DROP))))
  {
    notify_fail("You can't throw that.\n");
    return 0;
  }

  for_each(oblist, throw_it);
  return 1;
}

int break_globe(string str)
{
  object ob;

  if (parse_command(str, ({ this_object() }), "%o", ob))
  {
    notify_fail("Break it how?\n");
  }
  
  return 0;
}

void init()
{
  ::init();
  
  add_action(touch, "touch");
  add_action(touch, "hit");
  add_action(throw, "throw");
  add_action(break_globe, "break");
  add_action(feel, "feel");
}  
