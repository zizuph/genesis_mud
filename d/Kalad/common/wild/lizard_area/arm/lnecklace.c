/*
 * /d/Kalad/common/wild/lizard_area/arm/lnecklace
 *
 * Necklace for Lizard People
 * Coded by Mirandus 02/22
 */
#pragma strict_types
inherit "/std/armour.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>


void
create_armour()
{
      
   set_name("necklace");
   set_adj("jagged");
   add_adj("tooth");
   set_short("jagged tooth necklace");
    set_long("This is a " + query_short() + " made from teeth of fallen " +
        "Saurians. It represents your bond with the Saurians and your " +
        "recognition of the ancestry that came before you. These teeth " +
        "represent those of your line who have passed. One day your tooth " +
        "shall be added to the string and it will be passed down. Type " +
        "<help saurian> to learn more about the guild.\n");
    set_wf(this_object());
    set_slots(A_NECK);
   set_at(A_NECK);
   set_ac(1);
   add_prop(OBJ_I_VALUE,1500);
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,100);
}


