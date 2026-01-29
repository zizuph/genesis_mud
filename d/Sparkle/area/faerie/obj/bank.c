/*
 * Bank object for the shop to separate trade settings
 */
inherit "/std/object";
inherit "/lib/bank";

#include "defs.h"
#include <stdproperties.h>

void
create_object() 
{
    set_name("_hidden_bank");
    add_prop(OBJ_I_NO_GET, 1);
    set_no_show();

    set_bank_fee(BANK_FEE + EXTRA_BANK_FEE);
    config_default_trade();
    config_trade_data();
}

void
init()
{
    ::init();
    bank_init();
}

