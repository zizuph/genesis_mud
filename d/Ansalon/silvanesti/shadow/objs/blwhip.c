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
          set_name("whip");
          set_short("braided leather whip");
          set_long("This flail is a wooden handle attatched to an iron "+
              "rod by a chain link.  The handle's length is about three "+
              "feet long, the rod is one foot long.\n");
          set_default_weapon(25, 25, W_CLUB, W_BLUDGEON, W_ANYH);
          set_pshort("braided leather whips");
          set_pname("whips");
          set_adj("braided");
          set_adj("leather");
}

/*
 * Function name:
 * Description:
 * Arguments:
 * Returns:
 */
