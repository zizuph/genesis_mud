inherit "/std/drink";
#include <stdproperties.h>
#include <macros.h>

#define TP this_player()
#define ENV environment

object poison;

create_drink(){


set_name("ale");
add_adj(({"mug of", "dark"}));
  set_long("A tall mug of dark and hearty ale.\n");
add_name("mystic_drink");

set_soft_amount(20);
set_alco_amount(10);

}

consume_text(){

tell_room(ENV(TP), TP->query_name() + " drinks a mug of ale.\n", TP);
TP->catch_msg("You feel delighted. The mug fades away as you finish the ale.\n");
TP->heal_hp(5);
return 1;
}

