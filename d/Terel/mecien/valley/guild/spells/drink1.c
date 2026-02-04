inherit "/std/drink";
#include <stdproperties.h>
#include <macros.h>

#define TP this_player()
#define ENV environment

create_drink(){


set_name("nectar");
set_adj("cordial of");
set_long("A beautiful silver cordial filled with a sweet fruit nectar.\n");
add_name("mystic_drink");

set_soft_amount(10);

}

consume_text(){

tell_room(ENV(TP), TP->query_name() + " drinks a cordial of nectar.\n", TP);
TP->catch_msg("The nectar is sweet and refreshing. As you finish the last drops, "
+ "the silver cordial fades away.\n");
TP->add_fatigue(50);
return 1;
}

