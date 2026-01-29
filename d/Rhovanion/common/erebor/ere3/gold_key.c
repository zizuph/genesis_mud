inherit "/std/key";
#include "door.h"

create_key()
{
  set_adj("gold");
  set_adj("small");
  set_long("It's a small key, obviously it is made of gold. \n");
  set_key(GOLD);
}
