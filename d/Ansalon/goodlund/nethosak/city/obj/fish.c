inherit "/std/object";

#include "/sys/stdproperties.h"
#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include "/d/Krynn/common/defs.h"

string name();

void create_object()
{
    set_name(name()); 
    set_adj("young");
    set_long("This is a fish, perhaps from the Bloodsea area.\n");

    add_prop(OBJ_I_VOLUME, 600);
    add_prop(OBJ_I_WEIGHT, 600);
    add_prop(OBJ_I_VALUE, 0);
}

string
name()
{
    // Set name.
    string *names;
    names = ({"trout", "herring", "salmon"});
    return names[random(sizeof(names))];
}

