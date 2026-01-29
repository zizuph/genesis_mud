#pragma strict_types

inherit "/std/object";

#include "zigg.h"
#include "flowers.h"

#include <macros.h>
#include <composite.h>
#include <stdproperties.h>


private static string type;


public void
remove_object(void)
{
    all_inventory(TO)->remove_object();
    ::remove_object();
}

private string
my_long(void)
{
    return "This is a mangled "+ type +" of flowers that used to be "+
	"made up of "+ COMPOSITE_DEAD(all_inventory(TO)) +".\n";
}

private void
dissolve(void)
{
    tell_room(ENV(TO),
	"The "+ short() +" dissolves away, leaving no traces behind.\n");

    remove_object();
}

public void
create_object(void)
{
    set_long(my_long);
    set_adj("mangled");
    set_name(({"zigg::mangle"}));

    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 50);

    if (IS_CLONE)
	set_alarm(60.0, 0.0, dissolve);
}

public void
set_mangled(string kind, string short, string pshort)
{
    set_name(type = kind);
    set_short("mangled "+ short);
    set_pshort("mangled "+ pshort);
}

public void
update_flowers(void)
{
    /* Prevent removal of inventory. */
    add_prop(CONT_I_CLOSED, 1);
}
