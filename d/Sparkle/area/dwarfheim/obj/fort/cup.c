#pragma strict_types
#pragma save_binary

inherit "/std/container";

#include "defs.h"

#include <stdproperties.h>

void fill_me();

void
create_container()
{
    set_name("cup");
    add_name("real_coffee");
    set_short("cup of coffee");
    set_adj("coffee");
    set_long("This is a coffee cup, of the same kind that the dwarven king uses.\n");
    add_prop(CONT_I_WEIGHT,100); /* weight 100 g */
    add_prop(CONT_I_MAX_WEIGHT,350); /* can hold 350 g */
    add_prop(CONT_I_VOLUME,250); /* it's volume is 0.25 l */
    add_prop(CONT_I_MAX_VOLUME,800); /* holds 800 ml */
    add_prop(OBJ_I_VALUE,2);

    fill_me();
}

int
nodrink(string str)
{
    if (str != "cup" && str != "coffee" && str != "cup of coffee")
    {
        return 0;
    }

    write("You can't drink the coffee, it's too strong for you.\n");
    return 1;
}

void
init()
{
    ::init();

    add_action(nodrink,"drink");
}

void
fill_me()
{
    seteuid(getuid(TO));
    clone_object(S_LOCAL_OBJ_DIR + "coffee")->move(TO);
}

