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
          set_name("chainblade");
          set_short("iron chainblade");
          set_long("This six and a half foot long length of chain has a curved, "+
              "blade attatched at the end.  Each link of the chain is also barbed "+
              "and could cause considerable lashing damage.  It is typically held "+
              "held by the hilt and used as a flail.\n");
          set_default_weapon(29, 29, W_CLUB, W_SLASH, W_ANYH);
          set_pshort("iron chainblades");
          set_pname("chainblades");
          add_name("blade");
          add_pname("blades");
          set_adj("iron");
}

/*
 * Function name:
 * Description:
 * Arguments:
 * Returns:
 */
