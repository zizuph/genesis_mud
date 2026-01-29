inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    set_name("gem");
    set_adj("small");
    set_short("Milan's gem");
    set_long("This gem is very small, but probably still worth " +
        "something.\n");
    add_prop(OBJ_I_VALUE, 123);
    add_prop(OBJ_I_LIGHT, 123);
    add_prop(LIVE_I_IS, 1);
}

string
query_recover()
{
    return MASTER;
}

void
enter_env(object dest, object old)
{
  object milan;

  milan = find_player("milan");
  if(milan)
    this_object()->add_prop(TEMP_DRAGGED_ENEMIES, milan);

  ::enter_env(dest, old);
}
