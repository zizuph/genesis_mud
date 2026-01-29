/*
 * The code for this shield was borrowed from
 * /d/Krynn/solamn/vin/armour/s_shield.c
 *
 *  Arman 11/5/99
 */
inherit "/std/armour";
#include <wa_types.h>
#include <formulas.h>
#include "/d/Ansalon/common/defs.h"

string material = "bugged";
string strap = "Arman's scalp";

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

set_strap(string str)
{
    if(str == strap)
      return;
    strap = str;
}

public void
create_armour()
{
    set_name("shield");
    set_adj("dwarven");
    set_ac(30);
    set_at(A_SHIELD);
    set_am( ({0,0,0}) );
    set_short("@@short_desc");
    set_long("@@long_desc");
    set_af(TO);

    add_prop(OBJ_I_VOLUME, 4600);
    add_prop(OBJ_I_WEIGHT, 8000);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(36) + (random(200)));
}

string
short_desc()
{
    return material + " dwarven shield";
}

string
long_desc()
{
    return "This is a large shield crafted from " +
      material+ " with an arm strap made from " +strap+
      ", styled to suit someone the " +
      "size of a dwarf. A design of two twin peaks has been " +
      "skillfully engraved in the middle of the shield, the " +
      "symbol of Iron Delving.\n";
}

mixed
wear(object what)
{
    if (TP->query_race() != "dwarf")
    {
        TP->catch_msg("This was crafted to be worn by a dwarf. " +
          "You can't seem to get it to fit on your arm properly.\n");
        return 1;
    }
    return 0;
}

public int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY, A_LEGS }) );
}
