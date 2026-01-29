/* chapel/obj/bowl.c is cloned by chapel/rectory.v */
inherit "/std/object";
 
#include <stdproperties.h>
#include <macros.h>
#include "../chapel.h"
#include <composite.h>
 
/* Prototypes */
int throw(string arg);
 
void
create_object()
{
   set_name("bowl");
   add_name("wedding_bowl");
   add_adj("rice");
   set_long("This is a small crystal bowl filled with rice to throw at "+
      "the married couple when the wedding is over.\n");
 
   add_prop(OBJ_I_WEIGHT, 300);
   add_prop(OBJ_I_VOLUME, 450);
}
 
void
init()
{
   ::init();
   add_action(throw, "throw");
}
 
int
couple(object ob)
{
   if (ob->query_prop(JUST_MARRIED))
      return 1;
   return 0;
}
 
int
throw(string arg)
{
   object *arr;
   int i;
 
   notify_fail("Throw what?\n");
   if (arg != "rice")
      return 0;
   arr = filter(all_inventory(environment(this_player())), couple);
   notify_fail("But the couple isn't here!\n");
   if (sizeof(arr) < 1)
      return 0;
   write("You shower " + COMPOSITE_LIVE(arr) + " with rice.\n");
   say(QCTNAME(this_player()) + " showers " + COMPOSITE_LIVE(arr) +
      " with rice.\n", arr + ({ this_player() }));
   for (i=0;i++;i<sizeof(arr)) {
      arr[i]->catch_msg(QCTNAME(TP) + " showers you with rice.\n");
    }
   return 1;
}
