inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void
create_weapon()
{
    set_short("pruning knife");
    add_adj(({"sharp", "pruning"}));
    set_name("knife");
    set_long("This knife is small yet very sharp. It appears "+
       "to have been used to cut roses and other beautiful "+
       "flowers. An unnatural yet beautiful sheen comes from "+
       "the blade.\n");
    set_hit(18);
    set_pen(13);
    set_wt(W_KNIFE);
    set_dt(W_SLASH|W_IMPALE);
    add_prop(MAGIC_AM_MAGIC, ({ 20, "enchanted"}));
}

string
query_recover()
{
    return MASTER;
}
