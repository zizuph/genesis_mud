inherit "std/object";

#include <macros.h>
#include "/d/Gondor/defs.h"

void
create_object()
{
    set_name("branch");
    add_adj(({"long","willow","slender"}));
    set_short("slender willow branch");
    set_long(BSN("This branch seems to have been broken from a willow"
      + " and it looks like this may be a good tool to swat at bugs"
      + " with."));
}

int
do_swat(string str)
{
    object  obj;
    string  det = "the ";

    if (!strlen(str))
    {
        NFN("Swat what?");
        return 0;
    }

    if (!(parse_command(str, ENV(TP), "[at] %o", obj)))
    {
        NFN("That doesn't seem to be here to swat!");
        return 0;
    }

    if (living(obj))
    {
        if (!obj->id("mosquito"))
        {
            write(BSN("Come now, lets save it for the mosquitos!"));
            return 1;
        }
    }

    write(BSN("You swat wildly at the "+obj->query_short()+" with your"
      + " long willow branch."));
    tell_room(environment(TP), QCTNAME(TP)+" swats wildly at the "
      + obj->query_short()+" with a long willow branch.\n", TP);

    if (obj->id("mosquito"))
    {
        switch(random(3))
        {
            case 0:
            case 1:
                write("Ack! You missed him!\n");
                break;
            case 2:
                write("Got him!\n");
                obj->calculate_hp();
                obj->set_hp(0);
                obj->do_die(TP);
                break;
        }
        return 1;
    }
    return 1;
}


void
init()
{
    ::init();
    add_action(do_swat, "swat");
}
