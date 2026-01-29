/* The ring worn by the skeleton. by Teth Jan 18, 1997 */

inherit "/std/armour";
#include "/d/Krynn/common/defs.h"
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>

public void
create_armour()
{
    set_name("ring");
    add_adj( ({ "bejewelled", "ancient" }) );
    set_ac(1);
    set_at(A_ANY_FINGER);
    set_short("bejewelled ancient ring");
    set_pshort("bejewelled ancient rings");
    set_long("This ring is ancient, perhaps the family ring of some "+
            "nobleperson. It is covered with jewels that glitter in "+
            "the light, each flashing red or green. The band of the ring "+
            "is made of silver, but is tarnished now.\n");
    add_item(({"jewels","red jewels","green jewels"}),"These jewels are "+
            "beautiful, worth a small fortune. Unfortunately, some of "+
            "them are now chipped or abraded, reducing their value. They " +
            "appear to be rubies and emeralds.\n");
    add_item(({"band","silver band"}),"The silver band of the ring is " +
            "tarnished due to the nonexistent care it has received. This " +
            "looks irreversible.\n");
    add_prop(OBJ_I_VOLUME, 15);
    add_prop(OBJ_I_WEIGHT, 55);
    add_prop(OBJ_I_VALUE, 100 + random(200));
}

