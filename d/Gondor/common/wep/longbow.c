#include <stdproperties.h>

inherit "/std/bow";

public void
create_bow()
{
    set_adj("blackened");
    add_name("longbow");
    set_short("blackened longbow");
    set_long("This longbow is of a very simple design, yet you suspect the " +
	     "bow would be capable of delivering a decent punch. The " +
	     "only elaborate thing about this bow is that the maker has " +
	     "taken time to dye the wood a dark grey colour. Whether that " +
	     "has been done for camoflauge or to make the bow look more " +
	     "fearsome remains unclear.\n");
    add_prop(OBJ_I_WEIGHT, 1400);
    add_prop(OBJ_I_VOLUME, 4250);
    set_hit(41);
    set_pen(49);
}
