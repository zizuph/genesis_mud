/* Recoded by Teth for the new VK, Dec 6 1996 */
inherit "/std/drink";
#include "../../local.h"

public void
create_drink()
{
    set_soft_amount(185);
    set_alco_amount(21);
    set_name("wine");
    add_name("alcohol");
    set_adj(({"imported","Solanthian"}));
    add_adj("solanthian");
    set_pname("wines");
    add_pname("alcohols");
    set_short("imported Solanthian wine");
    set_pshort("imported Solanthian wines");
    set_long("This wine is imported from Solanthus, in southern " +
        "Solamnia. It is famous for its strong alcohol content, " +
        "due to the hybrid of grapes used.\n");
    set_drink_msg("The Solanthian alcohol leaves your mouth " +
        "with a bitter aftertaste.\n");
    add_prop(OBJ_I_WEIGHT, 185);
    add_prop(OBJ_I_VOLUME, 185);
}

