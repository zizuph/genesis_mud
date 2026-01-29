#pragma strict_types
#pragma no_clone

#include "../defs.h"

private string
describe_display(int display)
{
   if(display == GARDENER_TITLE_PRES || display == 0)
   {
      return "presentation";
   } else if(display == GARDENER_TITLE_SUBLOC) {
      return "description";
   } else if(display == GARDENER_TITLE_NOSHOW) {
      return "none";
   }

   return "error";
}

public int
_ldisplay(string str)
{
   object tp = this_player();
   int current_display = tp->query_gardener_display_title();
   int new_display = current_display;
   string current_desc = describe_display(current_display);

   if(!str || !strlen(str))
   {
      write("Your current Gardener title display setting is: " +
         current_desc + "\n");
      return 1;
   }

   if(str == "presentation")
   {
      new_display = GARDENER_TITLE_PRES;
   } else if(str == "description") {
      new_display = GARDENER_TITLE_SUBLOC;
   } else if(str == "none") {
      new_display = GARDENER_TITLE_NOSHOW;
   } else {
      return notify_fail("Available ldisplay options: description, presentation, none.\n");
   }

   if(current_display == new_display)
   {
      write("You leave your Gardener title display setting as it is.");
      return 1;
   }

   tp->set_gardener_display_title(new_display);

   write("You change your Gardener title display setting to: " +
      describe_display(new_display) + "\n");
   return 1;
}
