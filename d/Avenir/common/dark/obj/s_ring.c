// Stone ring, can be worn only by male chars. Cloned in l4/n28.
// Made by Boriska, Dec 1994

#include <stdproperties.h>
#include <wa_types.h>
#include <const.h>

inherit "/std/armour";

void
create_armour()
{
  set_name ("ring");
  set_short ("stone ring");
  add_adj ("stone");
  set_long (
   "Heavy ring made from dark stone. It was apparently made for a man's\n" +
   "hand to wear on.\n");

  set_at(A_ANY_FINGER);
  set_ac(5);
  
  add_prop (OBJ_I_WEIGHT, 20);
  add_prop (OBJ_I_VOLUME, 5);
  add_prop (OBJ_I_VALUE, 100);
}

mixed
wear_me()
{
  int gender = this_player()->query_gender();
  
  if (gender != G_MALE)
    return gender == G_FEMALE ?
      "The stone ring slips from your thin finger.\n" :
      "The stone ring does not suit you.\n";

  return ::wear_me();
}


