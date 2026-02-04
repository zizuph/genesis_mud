inherit "/std/drink";
#include <stdproperties.h>
#include <macros.h>

#define TP this_player()
#define ENV environment

object poison;

create_drink(){


set_name("water");
add_adj(({"flagon of", "spring"}));
set_long("A gold flagon filled with crystal clear spring water.\n");
add_name("mystic_drink");

set_soft_amount(50);

}

consume_text(){

tell_room(ENV(TP), TP->query_name() + " drinks a flagon of spring water.\n", TP);
TP->catch_msg("Pure and cold, the spring water cleanses you. The flagon " +
"fades away as you finish the water.\n");
  poison = present("poison", TP);
  if(poison){
   poison->remove_object();
  }
   TP->add_tmp_stat(1, 10, 100);
TP->add_fatigue(10);
return 1;
}

