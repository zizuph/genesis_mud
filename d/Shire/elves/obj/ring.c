/*
 * Ring found on Elves
 * -- Finwe, February 2018
 */

#pragma save_binary

#include "/d/Shire/sys/defs.h"
#include <macros.h>

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/cmd/std/command_driver";

#define RING_NAME   "_random_ring_"
#define ADJ1        "elegant"
#define ADJ2        "polished"

void create_object()
{
    set_name("ring");
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " ring");

    set_long("This is a " + short() + ". It is made of Silver and fits on " +
        "any finger. A clear crystal, cut into the shape of a star, " +
        "sits on the face of the ring.\n");

    set_slots(A_ANY_FINGER);
    set_layers(0);
    set_looseness(2);

    add_prop(OBJ_I_WEIGHT,  20);
    add_prop(OBJ_I_VOLUME,  50);
    add_prop(OBJ_I_VALUE,  100);

}

public string
show_subloc(string subloc, object on, object for_obj)
{
  string data;

  if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
  {
    return "";
  }

  if (for_obj == on)
    data = "You are ";
  else
    data = capitalize(environment(this_object())->query_pronoun()) + " is ";

  data+="wearing a " + query_short() + ".\n";

  return data;
}

enter_env(object dest,object old)
{
    seteuid(getuid());

    remove_name(RING_NAME);
    add_name(RING_NAME);
    if(living(E(TO)))
        dest->add_subloc(RING_NAME, this_object());
}

public void
leave_env(object from, object to)
{
    this_player()->remove_subloc(RING_NAME);
}

