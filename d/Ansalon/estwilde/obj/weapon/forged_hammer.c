inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

string material = "bugged";

string
query_recover()
{
    return 0;
}

void
set_material(string str)
{
    if(str == material)
      return;
    remove_adj(material);
    material = str;
}

string
query_material()
{
    return material;
}

create_weapon()
{
    set_name("warhammer");
    set_short("@@short_desc");
    set_long("@@long_desc");
    set_default_weapon(25,34,W_CLUB,W_BLUDGEON,W_ANYH);
    add_prop(OBJ_I_VOLUME, 6000);
    add_prop(OBJ_I_WEIGHT, 8000);
}

string
short_desc()
{
    return material + " warhammer";
}

string
long_desc()
{
    return "Crafted by dwarven hands, this warhammer " +
      "with a broad head of " +material+ " looks like " +
      "it could do some damage.\n";
}
