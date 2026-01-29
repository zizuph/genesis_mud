inherit "/std/receptacle";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>

void fill_desk();

void
create_receptacle()
{

     set_short("old dented desk");
     set_name("desk");
     add_adj(({"old","dented"}));
     set_long("This old dented desk has seen many years, no doubt.\n");
     add_prop(CONT_I_WEIGHT, 10000); /* Not too heavy to carry */
     add_prop(CONT_I_MAX_WEIGHT, 100000); /* Let us put things in it */
     add_prop(CONT_I_VOLUME, 100000000); /* Pretty darn big */
     add_prop(CONT_I_MAX_VOLUME, 10000000000); /* Put things in it */
     add_prop(CONT_I_RIGID, 1); /* Desks are rigid */
     add_prop(CONT_I_CLOSED, 1); /* Start with it closed */

    set_alarm(1.2,0.0,"fill_desk");

}

void
fill_desk()
{
   object knife, mathom1, mathom2, mathom3;
   knife = clone_object(MICH_DIR + "wep/knife");
   knife->move(TO,1);

   mathom1 = clone_object(MICH_DIR + "mathom/obj/mathom");
   mathom1->move(TO,1);

   mathom2 = clone_object(MICH_DIR + "mathom/obj/mathom");
   mathom2->move(TO,1);

   mathom3 = clone_object(MICH_DIR + "mathom/obj/mathom");
   mathom3->move(TO,1);

}
