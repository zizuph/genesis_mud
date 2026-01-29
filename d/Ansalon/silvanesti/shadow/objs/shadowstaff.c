#pragma save_binary

inherit "/std/weapon";
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/silvanesti/shadow/local.h"
#include <ss_types.h>
#include <macros.h>
#include "/sys/wa_types.h"
#include "/sys/formulas.h"

nomask
create_weapon()
{
          set_name("shadowstaff");
          set_short("shadowstaff");
          set_long("This four foot long wooden staff has an iron spear " +
              "blade on its end.  The blade has two nasty hooks coming " +
              "out of one side.  It looks like once this weapon enters " +
              "its target's body, it will be hard and painful to remove.\n");
          set_default_weapon(35, 35, W_POLEARM, W_IMPALE, W_BOTH);
          set_pshort("shadowstaves");
          set_pname("shadowstaves");
          add_name("staff");
          add_pname("staffs");
          add_pname("staves");
}
