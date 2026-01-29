/*
*    Key for broken elven tower cabinet
*/
inherit "/std/key";

#include <stdproperties.h>

void
create_key() 
{
    ::create_key();
    set_name("key");
    add_name("_kurinost_elven_cabinet_key");
    set_short("delicate crystal key");
    set_adj("delicate");
    add_adj("crystal");
    set_long("This a delicate key that looks like a sliver of glass, " +
        "yet it has been ingenuously carved out of crystal.\n");

    add_prop(MAGIC_AM_MAGIC,({50,"enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This delicate key has been enchanted " +
        "with a simple spell causing it to return to a specific " +
        "location after it is used.\n", 1}));

    set_key(1241241);
    add_prop("_key_i_no_keyring",1); 

}
