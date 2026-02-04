inherit "/std/drink";
#include <stdproperties.h>
#include <macros.h>

#define TP this_player()
#define ENV environment

object poison;

create_drink(){


set_name("milk");
add_adj(({"jug of", "fresh"}));
  set_long("An old stone jug filled with fresh cold milk.\n");
add_name("mystic_drink");

set_soft_amount(20);

}

consume_text(){

tell_room(ENV(TP), TP->query_name() + " drinks a jug of milk.\n", TP);
TP->catch_msg("You feel very healthy drinking the fresh milk!\n");
TP->heal_hp(10);
TP->add_tmp_stat(2, 12, 300);
return 1;
}

