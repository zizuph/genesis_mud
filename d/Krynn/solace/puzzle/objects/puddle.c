/* A puddle of water. ~solace/puzzle/objects/puddle */

inherit "/std/object";

#include "../defs.h"
#include "/sys/stdproperties.h"

int amount;

void create_object()
{
    set_name("puddle");
    add_name("water");
    set_short("@@short_desc");
    set_long("A puddle of water on the floor. It won't be long until it "+
        "has completely seeped through the floor.\n");

    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 1000);

    add_prop(OBJ_M_NO_GET, "You can't pick up a puddle of water!\n");

    set_alarm(1.0, 1.0, "seep_away");
}

string short_desc()
{
    switch(amount)
    {
        case 0..333:
            return("small puddle of water on the floor");

        case 334..666:
            return("medium-sized puddle of water on the floor");

        default:
            return("large puddle of water on the floor");
    }
}

void add_water(int i)
{
    if(amount + i <= 0)
        amount = 0;
    else if (amount + i >= 1000)
        amount = 1000;
    else
        amount += i;
}

int query_filled()
{
    return amount;
}

void seep_away()
{
    add_water(-10);

    if(file_name(E(TO)) == (LOCATIONS + "chemosh"))
    {
        tell_room(E(TO), "The water seeps through the fine-meshed grate on "+
            "the floor. You hear a hissing sound and the light flickers for "+
            "a second.\n");

        set_alarm(0.5, 0.0, "remove_object");
    }
    else if(amount <= 0)
    {
        tell_room(E(TO), "The puddle of water seeps through the floor and "+
            "disappears.\n");

        set_alarm(0.5, 0.0, "remove_object");
    }
}
