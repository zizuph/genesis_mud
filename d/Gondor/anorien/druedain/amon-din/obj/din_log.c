inherit "/std/object";

#include "/d/Gondor/defs.h"

void
create_object()
{
    set_name("amon_din_log");
    add_name(({"log"}));
    add_adj(({"ash-grey"}));
    set_short("ash-grey log");
    set_long(BSN("This is extremely dry and brittle, having taken on"
      + " a strangely pale, ash-grey colour. It is almost as if"
      + " something has sapped it of its natural essence."));
}

void
init()
{
    ::init();
    add_action("light_log", "light");
}

int
light_log(string str)
{
    if (!strlen(str))
    {
        NFN("Light what?");
        return 0;
    }

    if (str != "log" || str != "ash-grey log")
    {
        NFN("What do you want to light?");
        return 0;
    }

    write(BSN("The log has been sapped of its burning potential and"
      + " cannot be lit."));
    return 1;
}
