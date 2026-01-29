/*
 * Vase for Avenir houses.
 *
 * Lilith, Feb 2022
 */
#pragma strict_types
#include "../defs.h"

inherit "/std/container";

#include <macros.h>
#include <composite.h>
#include <stdproperties.h>

string type = one_of_list(({ "vase", "bowl", "urn" }));
string what = one_of_list(({ "glass", "clay", "onyx", "soapstone", "wood" }));
string madj = one_of_list(({ "large", "beautiful", "distinctive"}));

void reset_container();

public void
create_container()
{

    set_name(type);
	set_adj(what);
	add_adj(madj);
    set_short("@@empty_str@@"+ madj +" "+ what +" "+ type +"@@full_str@@");
    set_long("It is a "+ madj +" "+ type +" made of "+ what +".\n");

    add_prop(OBJ_I_VOLUME, 260);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VALUE, 26);

    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_MAX_VOLUME, 600);
    add_prop(CONT_I_MAX_WEIGHT, 200);
	add_prop(OBJ_M_NO_GET, "You'd probably tip the table over. Better not.\n");
	
	seteuid(getuid());
	reset_container();
}

public string
empty_str(void)
{
    if (!sizeof(all_inventory()))
	return "empty ";
    else
	return "";
}

public string
full_str(void)
{
    object *flowers = filter(all_inventory(), &->id("bouquet"));

    if (!sizeof(flowers))
	return "";

    if (sizeof(flowers) > 2)
	return " overflowing with bouquets of flowers";

    return " containing " + COMPOSITE_DEAD(flowers);
}

public void
reset_container(void)
{
    int size;
    object obj;


	size = 3;
	while(size--)
	{
	    if (!catch(obj = clone_object(BAZAAR + "Obj/flower/bouquet")))
	    {
		obj->set_colour(
		  one_of_list(({"white", "yellow", "pink", "orange" })));
		obj->set_type(one_of_list(
		    ({"aster", "dragonflower", "freesia", "iris", "orchid", "rose",
           "daisy", "carnation", "iris", "peony", "lily" })));
		obj->create_flower();
		obj->move(this_object(), 1);
	    }
	}
}
