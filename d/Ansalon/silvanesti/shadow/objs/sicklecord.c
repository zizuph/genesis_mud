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


/*
 * Function name: reset_weapon
 * Description:   Reset the weapon
 * Arguments:     arg: The reset argument.
 */
nomask
create_weapon()
{
          set_name("sicklecord");
          set_short("hooked sicklecord");
          set_long("The handle of this weapon has a sharp hooked blade "+
              "on one end and a four foot length of silk rope with a heavy "+
              "iron ring attatched on the other end.  One hand wield the "+
              "blade to cut, while the other swings the rope in an attempt "+
              "to hit with the ring.\n");
          set_default_weapon(31, 31, W_CLUB, W_SLASH | W_BLUDGEON, W_BOTH);
          set_pshort("hooked sicklecords");
          set_pname("sicklecords");
          add_name("cord");
          add_pname("cords");
          set_adj("hooked");
}

/*
 * Function name:
 * Description:
 * Arguments:
 * Returns:
 */

int twirl(string str)
{
  if (str == "cord" || str == "sicklecord" || str == "hooked sicklecord")
  {
    write("You swing the hooked sicklecord around menacingly above your head.\n");
    say(QCTNAME(TP) + " swings the hooked sicklecord around menacingly.\n");
  }
  else
    write("Twirl what?\n");

  return 1;
}
