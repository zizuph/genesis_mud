/* The is a fake Grunts collar, for use on the nps in the guild.       */
/* Coded 19/12/95 by Tulix III.                                        */

inherit "/std/armour";

#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour()
{
    
    set_name("collar");
    set_adj("spiked");
    add_adj("leather");
    add_name("fake_grunts_collar");
    set_long("The collar is the symbol of the Grunts guild.\n"
         + "It is proudly worn by many tough goblins that you may meet.\n");
    set_short("spiked leather collar");
   
    set_ac(0);            /* Not much use as armour, to be honest */
    set_at(A_NECK);       /* This collar is worn around the neck  */
    
    add_prop(OBJ_I_WEIGHT, 100);  /* Weight 100g */
    add_prop(OBJ_I_VOLUME, 50);   /* Volume 50ml */
    add_prop(OBJ_I_VALUE, 0);     /* Genuinely priceless */
    add_prop(OBJ_S_WIZINFO, "This collar is a lousy fake!\n");
}
