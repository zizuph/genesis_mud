
inherit "/std/object";
inherit "/lib/keep";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

#define QUERY_THIEF ob->query_guild_style_occ() == "thief" || ob->query_guild_style_lay() == "thief" || ob->query_race_name() == "kender"

object ob;


void
create_object()
{
    set_name("coin");
    set_adj("gold");
    set_long("@@long_desc");

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_VALUE, 30);
    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 144);
}

string
long_desc()
{
    ob = TP;

    if(QUERY_THIEF || TP->query_race() == "dwarf")
    {
    return "This is a gold coin, it looks like good " +
    "money... or does it? No! It is a craftily designed " +
    "dwarven trap! Best you leave it alone.\n";
    }

    return "This is a gold coin. It looks like good money.\n";

}