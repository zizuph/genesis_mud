/* Silver Spoon, by Teth, October 26, 1996 */

inherit "/std/object";
#include "/d/Krynn/common/defs.h"

create_object()
{
    set_name("spoon");
    add_name("metal");
    set_pname("spoons");
    add_pname("metals");
    set_short("silver spoon");
    set_pshort("silver spoons");
    set_adj("silver");
    set_long("This spoon is quite tarnished, but judging by the colour, "+
      "you gauge it to be a silver spoon! It is probably worth a "+
      "fair bit to a collector. Intricate designs are carved on "+
      "the handle.\n");
    add_item(({"designs","intricate designs","handle"}),"The handle has "+
      "a design of a rose embedded in swirls of shapes.\n");
    add_cmd_item(({"spoon","silver spoon"}),"polish","You have difficulty "+
      "polishing the spoon. The tarnish is too well set.\n");

    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_WEIGHT, 35);
    add_prop(OBJ_I_VALUE, 360);
}



