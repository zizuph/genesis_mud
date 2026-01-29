/*
 * Basket for use in tending the garden
 *
 * These baskets are necessary to tend the gardens in the Elementalist
 * temple. They can be obtained from the shed in the Diabrecho room.
 *
 * Created by Petros, May 2011
 */
#pragma strict_types

#include <stdproperties.h> 

inherit "/std/receptacle";

/*
 * Function:    create_receptacle
 * Description: The default constructor for the receptacle object
 */
public void
create_receptacle()
{
   set_name("basket");
   add_name("_elementalist_garden_basket");
   add_adj( ({ "hand-woven", "walnut" }) );

   set_short("hand-woven walnut basket");
   set_long("The " + short() + " has been crafted with intricately "
      + "woven strips of wood from a walnut tree. The workmanship of "
      + "the individual weaves is astounding.\n");    
   
   add_prop(CONT_I_WEIGHT, 250);  /* It weights 250 grams */
   add_prop(CONT_I_MAX_WEIGHT, 2250);     /* It can hold 2000 grams*/
   add_prop(CONT_I_VOLUME, 30);   /* Only 30 ml volume (very small) */
   add_prop(CONT_I_MAX_VOLUME, 2030);     /* 2 litres of volume */    
}
