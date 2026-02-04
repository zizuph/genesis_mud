/* A stone. Mortricia 921002.  */
inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

#define BSN(xx) break_string(xx+"\n", 70)
#define TP      this_player()
#define TO      this_object()

create_object()
{
    set_name("stone");
    set_adj("plain");
    set_short("@@my_short");
    set_pshort("@@my_pshort");
    set_long("@@my_long");
    add_prop(OBJ_I_VALUE, 90);
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 60);
}

string
my_short()
{
    return TO->query_adj()+" stone";
}

string
my_pshort()
{
    return TO->query_adj()+" stones";
}

string
my_long()
{
    return BSN("It is a "+TO->query_adj()+" stone.");
}
