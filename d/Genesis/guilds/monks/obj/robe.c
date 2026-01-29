/*
 * File:     robe.c
 * Created:  Cirion
 * Purpose:  robe for the monks to wear
 * Modification Log:
 *
 */
#pragma strict_types

#include "../defs.h"
#include <math.h>
#include <wa_types.h>

inherit MONKLIB;
inherit "/std/armour";

string    robe_long (object for_obj);
string    robe_short (object for_obj);
varargs    void      randomize (object for_obj = 0);

string    colour = "grey";
string    colour_adjective = "light";
int       col_index;
int       adj_index;


// Colours shamelessly ripped off from Calia eye colors
// (/d/Calia/gelan/rooms/hairdresser) by Maniac
string   *colours = ({ "amber", "almond brown", "albino white", "amethyst",
    "amber brown", "aquamarine", "ashen", "black",
    "blue", "blood red", "brown", "bright blue",
    "bright green", "bright purple", "bright red", "bright yellow",
    "calico", "cerulean blue", "chestnut brown", "cinnamon",
    "cinder red", "coal black", "cloud grey", "crystal clear",
    "crimson red", "dark blue", "dark green", "dark",
    "dark brown", "dark grey", "dark yellow", "deep blue",
    "deep brown", "deep green", "deep purple", "ebony",
    "emerald green", "ember red", "forest green", "fiery red",
    "golden yellow", "green", "grey", "hazel green",
    "icy blue", "indigo", "ivory", "jet black",
    "light brown", "mahogany", "midnight black", "magenta",
    "ocean blue", "olive green", "pearly", "pink",
    "purple", "rainbow-hued", "red", "royal blue",
    "ruby red", "sapphire blue", "scarlet", "sienna",
    "silvery grey", "sky blue", "smoke grey", "snow white",
    "sorrel", "steel grey", "turquoise", "vermilion",
    "violet", "velvet black", "white", "walnut brown",
    "yellow", "light green" });

void
create_armour ()
{
    set_short(robe_short);
    set_long(robe_long);


    set_name("robe");
    set_pname("robes");

    // add the file name as a name for easy use with present()
    add_name(MASTER_OB(this_object()));

    set_ac(1);
    set_af(TO);
    set_at(A_ROBE);
    add_prop(OBJ_I_VALUE,   250);
    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VOLUME,  650);

    randomize ();
    set_may_not_recover ();
}

public int
set_colour (string str)
{
    if (member_array (str, colours) >= 0)
    {
        colour = str;
        return 1;
    }
    else
    {
        return 0;
    }
}

void
init_robe ()
{
    colour = colours [col_index];

    add_adj (explode (colour, " "));
}

varargs void
randomize (object for_obj = 0)
{
    if (objectp (for_obj))
    {
        col_index = NAME_TO_RANDOM (for_obj->query_name(), 341242, sizeof (colours));
    }
    else
    {
        col_index = random (sizeof (colours));
    }

    init_robe ();
}

string
robe_long (object for_obj)
{
    return "It is a soft robe made from some light fabric.\n";
}

string
robe_short (object for_obj)
{
    return colour + " robe";
}


