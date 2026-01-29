/* Armour coded by Arren, November 93 */

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("chain-mail");
    add_name(({ "mail", "chainmail", "chain mail" }));
    set_pname("chain-mails");
    add_pname("mails");
    add_pname("chainmails");
    set_adj("red");
    add_adj(({ "orc", "dirty", "grey" }));
    set_short("dirty grey chain-mail");
    set_long(BSN(
    "An orc-made chainmail good enough to have been made by a skilled "+
    "human. It was once painted red but the paint has mostly worn off. "+
    "Now it is dirty grey from neglect."));

    set_default_armour(25, A_BODY, ({ -2, 3, -1 }), 0);

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(25, A_BODY));
    add_prop(OBJ_I_VOLUME, 3600);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(25)+random(200)-100);
}
