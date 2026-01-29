/*
** A bowl for olive oil
**
** This bowl is found on the desk of the Triterian commander in
** argos/nwterr/rooms/camptent.c  It is part of the Olive Oil Healing
** potion newbie quest/tour.  With olives picked from the grove,
** the player may "press olives" in argos/swterr/rooms/ogroved.c,
** then get the oil blessed by a priest who is wandering in the dark
** woods. The blessed oil is then taken to the quest master for reward.
**/
 
inherit "std/object";
#include <stdproperties.h>
 
void
create_object()
{
    set_name(({"_argos_oliveoil_bowl","bowl"}));
    set_adj("ceramic");
    set_short("ceramic bowl");
    add_prop("_argos_oliveoil_bowl_full",0);     /* empty */
    add_prop("_argos_oliveoil_bowl_blessed",0);  /* not blessed */
     set_long("@@exa_bowl");
 
    add_prop(OBJ_I_WEIGHT, 150);
    add_prop(OBJ_I_VOLUME, 200);
}
 
string
exa_bowl() {
   string desc="It is a simple ceramic bowl of no special design. ";
 
   if (this_object()->query_prop("_argos_oliveoil_bowl_full")) {
      if (this_object()->query_prop("_argos_oliveoil_bowl_blessed"))
         return break_string(desc+
                "It is filled with a sweet smelling oil.\n",70);
      else return break_string(desc+
                "It is filled with olive oil.\n",70);
   }
   else
      return break_string(desc+"It is empty, but has a thin coat of " +
                               "olive oil inside.\n",70);
}
