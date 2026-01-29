 // Driftwood  /d/Avenir/common/port/obj/uw_driftwood.c
 // Creator:   Glinda june-95
 // Purpose:   "noise" for the uw quest.

inherit "/std/object";

#include "/d/Avenir/common/common.h"

create_object()
{
   set_short("piece of driftwood");
   set_pshort("pieces of driftwood");
   set_name("driftwood");
   add_name("piece");
   set_long("This is a piece of driftwood. It seems to have been lying " +
            "in the sea for a long time, the water having smoothened its " +
            "edges, turning it into a familiar shape.\n");
   add_item(({"shape"}),"@@shape@@");

   add_prop(OBJ_I_WEIGHT, 1200);
   add_prop(OBJ_I_VOLUME, 1000); //when it dries up anyway
   add_prop(OBJ_I_VALUE,  2);    //everythings worth _something_
}

string
shape()
{
   switch(TP->query_skill(SS_AWARENESS))
   {
      case 0..30:
         return "It looks like...hmm...You have no idea really.\n";
         break;
      case 31..49:
         return "It looks somewhat like ... no that isnt it.\n";
         break;
      case 50..70:
         return "Could it be a fish of some kind?\n";
         break;
      default:
         return "It looks like a perfectly shaped salmon.\n";
   }
}
