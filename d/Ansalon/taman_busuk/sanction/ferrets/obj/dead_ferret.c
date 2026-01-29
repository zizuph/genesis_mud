/*
 * dead_ferret.c
 * A fun little item. Pops out of coffin.c and can be used to "squeek"
 * 
 * Ares, July 2004
 *
 */


inherit "/std/object";

#include <stdproperties.h>

void
init()
{
    ::init();
    add_action("squeak","squeak");
    
}

void
create_object()
{
    set_name("ferret");
    add_name("dead_ferret");
    set_adj("dead");

    set_short("dead mummified ferret");
    set_pshort("mummified ferrets");
    set_long("This is the corpse of a long dead ferret. It was neatly wrapped "+
        "and care was taken to preserve the corpse itself. It is not edible. "+
        "There is a tag around it's neck that says 'IXI - SQUEAKERS' \n");

    add_prop(OBJ_I_WEIGHT,100);
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_VALUE, 0);

}

int
squeak(string str)
{

    write("You squeeze the mummified dead ferret and it makes a "+
        "loud squeaking sound! \n");
    say("The dead ferret squeaks at you! \n");

    reset_euid();
    
    return 1;
}