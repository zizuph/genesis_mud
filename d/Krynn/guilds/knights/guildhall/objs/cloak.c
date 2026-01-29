inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("cloak");
    add_name("robe");
    set_adj("white");
    set_short("white cloak with a platinum crest");
    set_long("This white cloak is made of finest wool. It pins at " +
             "the neck with a crest finely worked in platinum.\n");
    add_item("crest", "It is the figure of a Kingfisher in flight, "+
             "bearing a sword in one claw and a rose in the other.\n");
    set_ac(10);
    set_at(A_ROBE);
}      
