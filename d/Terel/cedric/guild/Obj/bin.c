#pragma save_binary

inherit "/std/container";
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include "/d/Terel/cedric/guild/guild_defs.h"
#include "/d/Terel/common/terel_std_rec.h"

/*
 * A labeled bin to hold weapons at the check-in of the Minstrels Guild.
 * Functions: set_label(string name), query_label(), query_capital_label()
 * Cedric 1/93
 */
 
string label_name;

void
create_container()
{
    set_name("bin");
    set_short("bin labeled '@@query_capital_label@@'");
    set_long(BS("This bin, clearly labeled '@@query_capital_label@@' "
    + "across the front, is made of tough hardwood, marred and scratched "
    + "by countless blades, points, and edges.\n"));
    add_prop(CONT_I_MAX_VOLUME, 500000);
    add_prop(CONT_I_MAX_WEIGHT, 500000);
    add_prop(CONT_I_RIGID, 1);
}

void
set_label(string name)
{
    label_name = name;
}

string
query_label()
{
    return label_name;
}

string
query_capital_label()
{
    return capitalize(label_name);
}