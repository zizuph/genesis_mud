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
    set_name("axe");
    add_name("battleaxe");
    set_short("@@short_desc");
    set_long("@@long_desc");
    set_hit(20);
    set_pen(27);
    set_wt(W_AXE);
    set_dt(W_SLASH);
    set_hands(W_ANYH);
    add_prop(OBJ_I_WEIGHT, 8000);
}

string
short_desc()
{
    return material + " battleaxe";
}

string
long_desc()
{
    return "This is a well crafted dwarven axe designed purely " +
      "for war. With two slashing heads of tempered and " +
      "sharpened " +material+ ", it looks like quite a " +
      "deadly weapon.\n";
}