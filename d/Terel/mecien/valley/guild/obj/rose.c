inherit "/std/herb";
#include <herb.h>
#include <macros.h>
#include <stdproperties.h>

create_herb(){



  set_name("rose");
  set_herb_name("melyas");
add_name("mystic_rose");
  set_short("@@my_short");

set_id_long(
"This is a rare variety of rose, called Melyas. It is said that it grows " +
"only in places where the earth has been consecrated, such as temple grounds.. " +
"Its powers and properties have never really been discovered.\n");

set_unid_long("It is a beautiful rose, it has a very beautiful and mysterious smell.\n");
set_herb_value(50);
set_decay_time(5000);
set_find_diff(2);
set_id_diff(50);
set_effect(HERB_HEALING, "mana", 10);
add_prop(OBJ_I_VALUE, query_herb_value());

   colour();

}

colour(){
  string *color;
   color = ({ "red", "pink", "black", "purple", "white", "yellow", "orange" });

   add_adj(color[random(sizeof(color))]);
}

my_short(){
  return query_adj() + " rose";
}
