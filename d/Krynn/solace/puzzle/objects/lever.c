/* A wooden lever. ~solace/puzzle/objects/lever */

inherit "/std/object";

#include "../defs.h"
#include "/sys/language.h"
#include "/sys/stdproperties.h"

int lever_number;

void create_object()
{
    set_name("lever");
    set_adj("wooden");
    set_long("@@long_description");

    add_prop(CONT_I_WEIGHT, 250);
    add_prop(CONT_I_VOLUME, 450);
}

int query_lever_number()
{
    return lever_number;
}

void set_lever_number(int i)
{
    lever_number = i;
}

string long_description()
{
    string str = "A pole of light supple wood with a circular section. It "+
        "is threaded at one end, as if to provide some way of screwing it "+
        "into something.";

    if(lever_number)
        str += " It has the number "+LANG_WNUM(lever_number)+" carved into "+
            "the other end.";

    return str + "\n";
}
