/* Testing random number generators. */
/* Gwyneth, June 1999 */

inherit "/std/object";
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

string *colour=({"red", "orange", "yellow", "green", "blue", "purple"});

int my_rand(int range);


void
create_object()
{
    set_name("bead");
    set_adj(colour[my_rand(6)]);
    add_adj("glass");
    set_long("It's a simple coloured glass bead.\n");
    add_prop(OBJ_I_VALUE, 20);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);
}

int
my_rand(int range)
{
    int t = time();
    t /= 2;
    t ^= random(255);
    t %= range;
    return(t);
}
