
inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

string material;

void
set_material(string str)
{
    if(str == material)
      return;
    remove_adj(material);
    material = str;
    add_adj(material);
}

void
create_object()
{
    set_name("ore");
    set_short("@@short_desc");
    set_long("@@long_desc");

    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_WEIGHT,8000);
    add_prop(OBJ_I_VOLUME,8000);

}

string
short_desc()
{
    return material + " ore";
}

string
long_desc()
{
    return "This is a large chunk of " +material+ " ore.\n";
}
