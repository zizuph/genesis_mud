inherit "/std/object";

#include "../ctower.h"
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>

static string pyr_color;
static string transform_file;

void create_object()
{
  set_name(({ "globe", "ctower_globe" }));
  set_adj("crystal");
  set_long("A black, opaque sphere, floating in mid-air.\n");
  remove_prop(OBJ_I_WEIGHT);
  remove_prop(OBJ_I_VOLUME);
  remove_prop(OBJ_I_VALUE);
  add_prop(OBJ_M_NO_GET, "The globe won't move.\n");
}

void set_transform(string file)
{
  transform_file = file;
}

void set_color(string color)
{
  pyr_color = color;
}

void transform_globe()
{
  object pyr;

  setuid();
  seteuid(getuid());

  if (pyr = clone_object(CTOWER_OBJ + "pyramid"))
  {
    tell_room(environment(), 
        "The globe falls to the ground and begins to change its shape.\n" +
        "The globe's featureless curves sharpen into hard angles " +
        "and flatten into the faces of a crystal pyramid.\n");
    pyr->set_color(pyr_color);
    pyr->move(environment(), 1);
    remove_object();
  }
}

int is_wand(object ob)
{
  return (ob && ob->id("phase_quest_wand"));
}

int feel(string str)
{
  object ob;

  if (!parse_command(str, ({ this_object() }), "[the] %o", ob))
  {
    return 0;
  }

  write("The surface of the globe is extremely cold and totally " +
      "smooth--completely featureless.  You feel a slight pull " +
      "on your hand, as if the globe were drawing it in.\n");
  return 1;
}
   
void touch_it(object ob)
{
  if (!is_wand(ob))
  {
    if (ob->query_prop(OBJ_M_NO_DROP))
    {
      write("You feel the globe try to absorb the " + ob->short() +
          ", but something prevents it from doing so.\n");
      return;
    }

    tell_room(environment(), "The " + ob->short() + 
        " is absorbed into the crystal globe!\n");
    ob->remove_object();
    return;
  }

  transform_globe();  
}

int touch(string str)
{
  string globe, wand;
  object globe_ob, pyr;
  mixed *oblist;

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
    write("You " + query_verb() + " the globe.\nIts surface is " +
        "extremely cold.  You feel a slight pull on your hand, as " +
        "if the globe were trying to pull you into it.\n");
    return 1;
  }

  notify_fail("Touch the globe with what?\n");
  if (!parse_command(wand, deep_inventory(this_player()), 
      "[the] %i", oblist) || !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
  {
    return 0;
  }

  for_each(oblist, touch_it);
  return 1;
}

void throw_it(object ob)
{
  if (!is_wand(ob))
  {
    tell_room(environment(), "The " + ob->short() + 
        " is absorbed into the globe!\n");
    ob->remove_object();
    return;
  }

  ob->move(environment(), 1);
  transform_globe();
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
