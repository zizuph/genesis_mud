inherit "/std/object";
#include <stdproperties.h>
#include "defs.h"

string colour;

string query_colour() { return colour; }

void set_colour(string new_colour)
{
    remove_adj(colour);
    colour = new_colour;
    set_adj(colour);
}

string short() { return colour + " rod"; }

string long() { return "This is a thin " + colour + " rod.\n"; }

string query_adj() { return colour; }

void create_object()
{
    set_name("rod");
    colour = "black";
    set_adj(colour);
    add_prop(OBJ_I_CHANGEABLE_COLOUR, 1);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 100);
}
