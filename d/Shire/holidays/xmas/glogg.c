/*
 * Holiday food from Bree
 * Finwe, December 2002
 */

#include "/d/Shire/sys/defs.h"

inherit "/std/drink";

void
create_drink()
{
    set_name("glogg");
    add_name("mug of hearty glogg");
    add_name("mug of glogg");
    set_pname("gloggs");
    add_pname("mugs of hearty glogg");
    add_pname("mugs of glogg");
    set_adj("hearty");
    set_short("mug of hearty glogg");
    set_pshort("mugs of hearty glogg");
    set_long("This is a mug of hearty glogg. It is made from " +
        "red wine, sweetened with honey and enhanced with " +
        "cinnamon, cloves, orange peel, and raisins. " +
        "Slivered almonds have been added and the holiday " +
        "drink heated until it is very hot.\n");
    set_soft_amount(80);
    set_alco_amount(40);
}
