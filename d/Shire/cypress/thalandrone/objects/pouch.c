/*
 * A common money pouch
 * -- Finwe, May 2001
 */

#pragma save_binary

inherit "std/container";

#include "/d/Shire/cypress/sys/defs.h"
#include <macros.h>
#include <money.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>

inherit "/lib/keep";

create_container()
{
    set_name("pouch");
    set_short("moldy leather pouch");
    set_adj("leather");
    set_long("This is a moldy leather pouch used for keeping " +
        "money. It looks like it has been buried for quite " +
        "sometime as there are holes in the once fine leather.\n");
    add_prop(CONT_I_WEIGHT,100); /* weight 100 g */
    add_prop(CONT_I_MAX_WEIGHT,1100); /* can hold 1 kg */
    add_prop(CONT_I_VOLUME,100); /* it's volume is 0.1 l */
    add_prop(CONT_I_MAX_VOLUME,1100); /* holds 1 litre */
    add_prop(OBJ_I_VALUE,40);
    
    set_keep(1); /*pouch keepable */

    MONEY_MAKE_SC(random(20))->move(this_object(), 1);
  	MONEY_MAKE_CC(random(15))->move(this_object(), 1);
   	MONEY_MAKE_GC(random(3))->move(this_object(), 1);

}
