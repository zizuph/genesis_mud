inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{
    set_name("_knight_cloak");
    add_name(({ "robe", "cloak" }));
    set_adj("white");
    set_short("white cloak with a platinum crest");
    set_pshort("white cloaks with platinum crests");
    set_long("This white cloak is made of the finest wool. It pins" +
      " at the neck with a crest finely worked in platinum.\n");
    add_item("crest", "It is the figure of a Kingfisher in flight," +
      " bearing a sword in one claw and a rose in the other.\n");
    set_ac(10);
    set_at(A_ROBE);
}      
