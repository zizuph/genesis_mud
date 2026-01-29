#pragma save_binary

inherit "/std/weapon";
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/shadow/local.h"
#include <ss_types.h>
#include <macros.h>
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

void
init()
{
    ::init();
    ADA("twirl");
}

nomask
create_weapon()
{
          set_name("spikecord");
          set_short("two-pronged spikecord");
          set_long("The handle of this weapon has a sharp pointed blade "+
              "on one end and a four foot length of silk rope with a "+
              "two-pronged hook attatched on the other end.  The hook looks "+
              "like it can aid a bit in climbing.  One hand wields the "+
              "blade to stab, while the other swings the rope in an attempt "+
              "to slash with the hook.\n");
          set_default_weapon(33, 33, W_CLUB, W_IMPALE | W_SLASH, W_BOTH);
          set_pshort("two-pronged spikecords");
          set_pname("spikecords");
          add_name("cord");
          add_pname("cords");
          set_adj("pronged");
          add_adj("two-pronged");
}

int twirl(string str)
{
  if (str == "cord" || str == "spikecord" || str == "two-pronged spikecord")
  {
    write("You twirl the hooked end of spikecord menacingly above your head.\n");
    say(QCTNAME(TP) + " twirls the hooked end of the spikecord menacingly.\n");
  }
  else
    write("Twirl what?\n");

  return 1;
}
