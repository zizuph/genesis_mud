#pragma strict_types
#pragma no_inherit

inherit "/std/scroll";

#define SUBLOC "gardener_title_subloc"

#include "../defs.h"
#include <stdproperties.h>

public void
create_scroll()
{
   set_name("scroll");
   add_name(GARDENER_NOTEBOOK_ID);
   set_adj("annotation");
   set_short("annotation scroll");
   set_long("This is your annotation scroll, where you record " +
      "information about various herbs and components you encounter to " +
      "file in your journal later.\n");
   add_prop(OBJ_M_NO_DROP, 1);
   add_prop(OBJ_M_NO_STEAL, 1);
   add_prop(OBJ_M_NO_SELL, 1);
   add_prop(OBJ_M_NO_GIVE, 1);
}

/*
 * Function name: read_it
 * Description:   If player wanted to do anything to this book we end up here.
 * Arguments:     verb - The verb the player had used
 */
void
read_it(string verb)
{
    this_player()->gardener_read_notepad();
}

public void
enter_env(object tp, object from)
{
   ::enter_env(tp, from);

   if(!interactive(tp))
   {
      return;
   }

   tp->add_subloc(SUBLOC, this_object());
}

public void
leave_env(object tp, object to)
{
   ::leave_env(tp, to);

   if(!interactive(tp))
   {
      return;
   }

   tp->remove_subloc(SUBLOC, this_object());
}

public string
show_subloc(string subloc, object tp, object for_obj)
{
   int display = tp->query_gardener_display_title();

   if(display != GARDENER_TITLE_SUBLOC)
   {
      return 0;
   }

   string title = tp->query_gardener_title();
   string desc = (tp == for_obj
      ? "You are "
      : (capitalize(tp->query_pronoun()) + " is ")
   );

   desc += (title[0..0] == "A" ? "an " : "a ");
   desc += title;
   desc += ".\n";

   return desc;
}

public string
query_auto_load()
{
   return GARDENER_NOTEBOOK_OBJ;
}
