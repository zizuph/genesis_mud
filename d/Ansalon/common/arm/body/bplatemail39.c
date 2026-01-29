inherit "/std/armour";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

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
    add_name("platemail");
    add_adj(({color, "steel"}));
    set_short("blue steel platemail");
    set_long("@@my_long");
    set_ac(39);
    set_at(A_BODY);
    add_prop(OBJ_I_VOLUME, 8000);
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

string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "&&" + color;
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    set_color(a[1]);
    init_arm_recover(a[0]);
}
