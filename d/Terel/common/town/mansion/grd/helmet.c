/* An armour should always begin with these statements: */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;

#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */

void
create_terel_armour()
{
    /* Set the name, short description and long description */
    set_name("helmet");
    set_short("medium sized helmet"); /* Observe, not 'a small helmet' */
    set_long("It's small but would probably protect you a little.\n");

    /* Now, a player can refere to this armour as 'armour' and 'helmet'. To
     * distinguish it from other helmets, we want the player to be able to 
     * use 'small helmet' as an id too.
     */
    set_adj("small");

    /* Now we want to set the armour class, and perhas a modifier to it */
    set_ac(6);
    /*        impale, slash, bludgeon */
    set_am(({-1,0,1}));

    /* We also need to set what type of armour this is */
    set_at(A_HEAD); /* It protects the head */
}

