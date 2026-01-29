// file name:        /d/Kalad/common/wild/pass/drow/obj/backpack.c
// creator(s):       Nikklaus, Apr'97
// revision history: Lilith, Mar 99
// note:	Updated to use the 'new' wearable pack code.
// to-do:
// bug(s):

#pragma strict_types

inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

void
create_wearable_pack()
{
    set_name("backpack");
    add_name("pack");
    add_adj("soft");
    add_adj("leather");
    set_long("A simple yet rugged backpack made of purplish rothe-hide, "+
      "beaten soft and pliable. The sturdy pack looks like it could hold "+
      "quite a lot.  On the opening flap of the pack, the image of a tiny spider has "+
      "been scorched into the leather and dyed black, except for a red " +
      "hourglass on its back.\n");

    set_slots(A_BACK);
    set_looseness(15);
    set_layers(2);
    set_mass_storage(1); 
    set_cf(this_object());
    set_keep(1); 

    add_prop(OBJ_I_VALUE,  375);                           
    add_prop(CONT_I_WEIGHT, 5000);	  /* 5.0 kg */
    add_prop(CONT_I_VOLUME, 5000);         /* 5.0 L  */
    add_prop(CONT_I_MAX_WEIGHT, 125000);  /* 125.0 kg */
    add_prop(CONT_I_MAX_VOLUME, 125000);  /* 125.0 L  */
    add_prop(CONT_I_REDUCE_WEIGHT, 110); // reduces weight by 10%
}

string
query_recover()
{
     return MASTER + ":" + query_keep_recover() +
	 query_container_recover();
}

void
init_recover(string arg)
{
     init_keep_recover(arg);
     init_container_recover(arg);
}
