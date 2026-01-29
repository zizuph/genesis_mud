// white clothes for the snob_elf in tomato-drop quest.
// made by Kazz, March 1995

inherit "/std/armour";

#include <wa_types.h>

create_armour()
{
  set_name("hat");
  set_short ("white, showy hat");
  add_adj(({"white", "showy"}));
  set_long ("White, showy hat worn to impress others.\n");
  set_ac (3);
  set_at (A_HEAD);
}
