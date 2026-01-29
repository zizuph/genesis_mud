#pragma save_binary

inherit "/std/poison_effect";
#include <poison_types.h>

create_poison_effect()
{
  ::create_poison_effect();
  set_interval(10);
  set_time(strength*50);
}
