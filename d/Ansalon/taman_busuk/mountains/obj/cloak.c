inherit "/std/armour";

#include <wa_types.h>

void
create_armour()
{

    add_name(({ "robe", "cloak" }));
    set_adj("greying");
    set_short("greying cloak with a platinum crest");
    set_pshort("greying cloaks with platinum crests");
    set_long("This was once a white cloak made of the finest wool, " +
      "however it has obviously not been cleaned in a long time and " +
      "is now is a dulling grey. It pins" +
      " at the neck with a crest finely worked in platinum.\n");
    add_item("crest", "It is the figure of a Kingfisher in flight," +
      " bearing a sword in one claw and a rose in the other.\n");
    set_ac(10);
    set_at(A_ROBE);
}      
