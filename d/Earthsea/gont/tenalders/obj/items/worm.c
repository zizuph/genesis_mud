/*
 * The scarecrow's head
 * coded by Amelia   5/24/97
*/

#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>

public void
create_food()
{
    set_name("_green_worm_");
    add_name("worm");
    set_adj(({"fat", "green", "juicy"}));
    set_short("fat green worm");
    set_long("A big fat green juicy-looking worm. " +
        "It is the kind of worm that lives in apples.\n");
    set_amount(30);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 0);
}

public void
special_effect(int num)
{
    if(num > 1)
    {
        write("The worms wiggle as they goes down.\n");
    } else {
        write("The worm wiggles as it goes down.\n");
    }
}

public int
query_the_worm()
{
    return 1;
}
