/*
   quest_map.c
   -----------

   Coded ........: 95/05/03
   By ...........: Jeremiah

   Latest update : 95/05/30
   By ...........: Jeremiah

   This is the map used in solving the Pax Tharkas prisoner quest.
   The gully_ghost has it, and will give it to the player who 
   brings him the evidence he needs, the diary_page.

*/

inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"


void
create_object()
{
   set_name(({"map", "_quest_map_"}));
   set_short("small map");
   set_long("This is a small map of the area around Pax Tharkas. " +
            "It shows most of the area south of, and a little " +
            "of the area north of, Pax Tharkas. Across the map " +
            "is written Kal-Thax. It shows many paths and trails " +
            "in the southern areas. It is probably very useful " +
            "for someone who needs to find his way in that area.\n");

   add_adj("old");
   
   add_prop(OBJ_I_VALUE,5);
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,75);
}
