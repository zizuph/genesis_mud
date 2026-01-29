inherit "/std/object";
#include "/d/Kalad/defs.h"

/* Sarr */

int gem;

void 
set_gem_here()
{
    gem = 1;
}

void
create_object()
{
    set_name("tree");
    set_adj("tall");
    add_adj("apple");
    set_short("tall apple tree");
    set_long("This is a very large apple tree. You see many little "+
    "red apples hanging from it, and the sweet smell of apples "+
    "fill the air.\n");
    add_prop(OBJ_M_NO_GET,"It is stuck quite deep in the ground.\n");
}

void
init()
{
    ::init();
    AA(do_pick,pick);
}

int
do_pick(string str)
{
    NF("Pick what?\n");
    if(str != "apple")
        return 0;
    if(gem == 1)
    {
        gem = 0;
        write("As you try and grab an apple, your hand brushes againts "+
        "a branch, and a sparkling blue gem falls out and hits you on "+
        "the head!\n");
        seteuid(getuid());
        clone_object(NOBLE(obj/blue_gem))->move(E(TP));
        return 1;
    }
    write("All of the good ones are too far up high and you can't reach.\n");
    return 1;
}

