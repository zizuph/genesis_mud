#pragma save_binary

inherit "/std/weapon";

#include "/sys/wa_types.h"
#include "/sys/formulas.h"


/*
 * Function name: reset_weapon
 * Description:   Reset the weapon
 * Arguments:     arg: The reset argument.
 */
nomask
create_weapon()
{
          set_name("flail");
          set_short("short iron flail");
          set_long("This flail is a wooden handle attatched to an iron "+
              "rod by a chain link.  The handle's length is about three "+
              "feet long, the rod is one foot long.\n");
          set_default_weapon(27, 27, W_CLUB, W_BLUDGEON, W_ANYH);
          set_pshort("short iron flails");
          set_pname("flails");
          set_adj("iron");
          set_adj("short");
}

/*
 * Function name:
 * Description:
 * Arguments:
 * Returns:
 */
