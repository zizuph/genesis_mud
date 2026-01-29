#pragma save_binary

inherit "/std/receptacle";
#include <stdproperties.h>



void
create_receptacle()
{

     set_short("tall clothes stand");
     set_name("stand");
     add_adj(({"tall","clothes"}));
     set_long("This tall clothes stand is made of iron painted in "+
     "a heavy-duty black lacquer.  It is strong and heavy, and you "+
     "can put your clothes here to keep them dry while you bathe.\n");

     add_prop(CONT_I_WEIGHT, 10000); /* Not too heavy to carry */
     add_prop(CONT_I_MAX_WEIGHT, 100000); /* Let us put things in it */
     add_prop(CONT_I_VOLUME, 100000000); /* Pretty darn big */
     add_prop(CONT_I_MAX_VOLUME, 10000000000); /* Put things in it */
     add_prop(CONT_I_RIGID, 1); /* Stands are rigid */
     add_prop(CONT_I_CLOSED, 0); /* Start with it opened */



}
