/*
 * Pearl necklace for the elves
 * -- Finwe, February 2018
 */

#pragma save_binary

#include "/d/Shire/sys/defs.h"
#include <wa_types.h>

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/cmd/std/command_driver";

#define ITEM_NAME   "_random_pearl_strand_"
#define ADJ1        "simple"
#define ADJ2        "pearl"

void create_object()
{
    set_name("necklace");
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " necklace");

    set_long("This is a simple strand of pearls. They are irregularly " +
        "shaped and evenly spaced on a a silver chain. The pearls are " +
        "iridescent and look in good condition.\n");

    set_slots(A_NECK);
    set_layers(0);
    set_looseness(2);

    add_prop(OBJ_I_WEIGHT,  110);
    add_prop(OBJ_I_VOLUME,  100);
    add_prop(OBJ_I_VALUE,   100);

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

void
enter_env(object dest,object old)
{
    ::enter_env(dest,old);
    seteuid(getuid());

    remove_name(ITEM_NAME);
    add_name(ITEM_NAME);
    if(living(E(TO)))
        dest->add_subloc(ITEM_NAME, this_object());
}

public void
leave_env(object from, object to)
{
    this_player()->remove_subloc(ITEM_NAME);
}

