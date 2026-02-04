/* An armour should always begin with these statements: */

inherit "/std/armour";
#include <stdproperties.h>
#include <macros.h>
#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */

void
create_armour()
{
    /* Set the name, short description and long description */
   set_name("skullcap");
   set_short("Lars' skullcap");
   set_long(break_string(
   "This is a skullcap, once worn by Lars.  It is thin and shiny, " +
   "and was not really intended as an armour, but as decoration.  " +
   "\n", 70));

    /* Now, a player can refere to this armour as 'armour' and 'helmet'. To
     * distinguish it from other helmets, we want the player to be able to 
     * use 'small helmet' as an id too.
     */

    /* Now we want to set the armour class, and perhas a modifier to it */
    set_ac(4);
    /*        impale, slash, bludgeon */
    set_am(({   -2,     1,      1 }));

    /* We also need to set what type of armour this is */
    set_at(A_HEAD); /* It protects the head */
}

