/* Ashlar, 3 Aug 97 */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

string gAdj;

void
set_desc(string a)
{
    if (stringp(gAdj))
        remove_adj(gAdj);

    add_adj(gAdj = a);
    set_short("ragged " + a + " clothing");
}

void
create_armour()
{
   set_name("clothing");
   set_adj("ragged");
   set_desc(({"white","brown","grey","soiled"})[random(4)]);
   set_long("This ragged clothing is dirty and very worn.\n");
   set_ac(3);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(3)-random(10));
   add_prop(OBJ_I_VOLUME, 400);
   add_prop(OBJ_I_WEIGHT, 600);
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "&&" + gAdj;
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    set_desc(a[1]);
    init_arm_recover(a[0]);
}
