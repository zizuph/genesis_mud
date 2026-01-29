inherit "/std/weapon";
#include <wa_types.h>
#include <formulas.h>
#include "/d/Krynn/haven/local.h"

public void
create_weapon()
{
    set_name("warhammer");
    add_name(({"weapon","club", "hammer"}));
    set_pname("warhammers");
    add_pname(({"maces","weapons", "hammers"}));
    set_adj(({"glistening","two-handed","mithril"}));
    set_short("glistening two-handed warhammer");
    set_pshort("glistening two-handed warhammers");
    set_long("This is the magnificent hammer of Colin "+
      "Ironfist, as is plainly evident by the engraving along "+
      "the haft of this warhammer. The head of the hammer has "+
      "been sprinkled with mithril flecks, making the silvery "+
      "steel glisten with an almost magical looking glow. It is "+
      "remarkably light, and well balanced. A truly wonderful "+
      "weapon.\n");

    set_default_weapon(35, 35, W_CLUB, W_BLUDGEON, W_BOTH);

    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_WEIGHT, 4000);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(50,50));
}
