inherit "/std/drink";
#include <stdproperties.h>
#include <macros.h>

#define TP this_player()
#define ENV environment

object poison;

create_drink(){


set_name("wine");
add_adj(({"carafe of", "red"}));
set_long("A beautiful crystal carafe filled with red wine.\n");
add_name("mystic_drink");

set_soft_amount(20);
set_alco_amount(10);

}

consume_text(){

tell_room(ENV(TP), TP->query_name() + " drinks a carafe of red wine.\n", TP);
TP->catch_msg("You drink the fine red wine and feel happy. The carafe fades " 
  + "away as you finish it.\n");
return 1;
}

