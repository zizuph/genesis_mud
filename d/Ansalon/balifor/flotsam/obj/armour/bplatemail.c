inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include "/d/Ansalon/balifor/flotsam/local.h"

#define ARMOUR_CLASS 39

string color = "blue";

string
my_long()
{
    return "This is a shiny suit of "+color+" platemail, "+
	"emblazoned on the front with the image " +
	"of a fierce dragons head.\n";
}

void
create_armour()
{
    set_name("armour");
    add_name("platemail");

    add_adj(({color, "steel"}));

    set_short("blue steel platemail");
    set_long("@@my_long");
    set_ac(ARMOUR_CLASS);
    set_at(A_BODY);

    add_prop(OBJ_I_WEIGHT, 20000);
    add_prop(OBJ_I_VOLUME, 8000);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(ARMOUR_CLASS));
}

void
set_color(string str)
{
    remove_adj(color);
    color = str;
    add_adj(color);
    set_short(color+" steel platemail");
}

void
set_colour(string str)
{
    set_color(str);
}