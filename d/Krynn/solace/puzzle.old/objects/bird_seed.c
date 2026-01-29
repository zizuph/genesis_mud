/* Bird seed (for the cuckoo). ~puzzle/objects/bird_seed */

inherit "/std/food";

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

string where_am_i()
{
    if(LIVING(E(TO)))
        return "handful of";
    else
        return "measure of";
}

void create_food()
{
    set_name("bird-seed");
    add_name("bird seed");
    add_name("birdseed");
    add_name("seed");
    set_adj("@@where_am_i@@");
    set_long("Yellow bird-seed. It doesn't look very appetising, but "+
        "a bird would probably like it.\n");

    set_amount(25);

    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 60);
}

int eat_it(string str)
{
    write("You try to eat some bird-seed, but spit it out. It's disgusting!\n");
    say(QCTNAME(TP)+" tries to eat some bird-seed, but seems to dislike it.\n");
    return 1;
}
