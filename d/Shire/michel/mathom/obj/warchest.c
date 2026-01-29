inherit "/std/receptacle";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>

void fill_chest();

void
create_receptacle()
{

     set_short("massive heavy warchest");
     set_name("warchest");
     add_name("chest");
     add_adj(({"massive","heavy","war"}));
     set_long("This old warchest is of very poor quality, though it is big.\n");
     add_prop(CONT_I_WEIGHT, 10000); /* Not too heavy to carry */
     add_prop(CONT_I_MAX_WEIGHT, 100000); /* Let us put things in it */
     add_prop(CONT_I_VOLUME, 100000000); /* Pretty darn big */
     add_prop(CONT_I_MAX_VOLUME, 10000000000); /* Put things in it */
     add_prop(CONT_I_RIGID, 1); /* Desks are rigid */
     add_prop(CONT_I_CLOSED, 1); /* Start with it closed */

    set_alarm(1.2,0.0,"fill_chest");

}

void
fill_chest()
{
   object knife, mathom1, mathom2, mathom3, armour, armour2, armour3;
   knife = clone_object(MICH_DIR + "wep/mace");
   knife->move(TO,1);

   mathom1 = clone_object(MICH_DIR + "mathom/obj/mathom");
   mathom1->move(TO,1);

   mathom2 = clone_object(MICH_DIR + "mathom/obj/mathom");
   mathom2->move(TO,1);

   mathom3 = clone_object(MICH_DIR + "mathom/obj/mathom");
   mathom3->move(TO,1);

   armour = clone_object(MICH_DIR + "arm/mhelmet");
   armour->move(TO,1);

   armour2 = clone_object(MICH_DIR + "arm/mmail");
   armour2->move(TO,1);

   armour3 = clone_object(MICH_DIR + "arm/mshield");
   armour3->move(TO,1);
}