/* An armour should always begin with these statements: */
#include "/d/Terel/include/Terel.h"
inherit STDARMOUR;

#include "/sys/wa_types.h"  /* wa_types.h contains some definitions we want */

void
create_terel_armour()
{
    /* Set the name, short description and long description */
    set_name("jacket");
    set_short("leather jacket"); 
    set_long("A waxed and metal reinforced leather jacket.\n");

    set_adj(({"leather","waxed","leather"}));

    /* Now we want to set the armour class, and perhas a modifier to it */
    set_ac(8);
    /*        impale, slash, bludgeon */
    set_am(({  0,     1,     -1 }));

    /* We also need to set what type of armour this is */
    set_at(A_TORSO); /* It protects the head */
}

