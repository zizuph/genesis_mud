inherit "/std/drink";
#include <stdproperties.h>
#include <macros.h>

#define TP this_player()
#define ENV environment

object poison;

create_drink(){


set_name("brandy");
add_adj(({"goblet of", "apricot"}));
set_long("A silver goblet of apricot brandy.\n");
add_name("mystic_drink");

set_soft_amount(20);
set_alco_amount(20);

}

consume_text(){

tell_room(ENV(TP), TP->query_name() + " drinks a goblet of brandy.\n", TP);
TP->catch_msg("It is glorious and warms you up! The goblet fades away " +
  "as you consume the brandy.\n");
return 1;
}

