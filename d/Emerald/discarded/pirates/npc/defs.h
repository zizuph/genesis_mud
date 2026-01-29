#include "/d/Emerald/defs.h"
#include "/d/Emerald/common/guild/pirates/pirates_defs.h"
#include "/d/Emerald/lib/prestige.h"

int introed;

void
react_intro()
{
   if(!introed)
      set_alarm(6.0,0.0,"intro",TO);
   introed = 1;
   return;
}

void
intro(object to)
{
   set_alarm(20.0,0.0,"reset_introed");
   to->command("introduce myself");
   return;
}

void
reset_introed()
{
   introed = 0;
   return;
}
