#include "/d/Terel/include/Terel.h"
inherit "/std/object";
#include "/d/Terel/guilds/white/lib/white.h"

string query_auto_load() { return MASTER + ":"; }
string query_recover() { return 0; }

public void
create_object()
{

    set_name("_white_brand_");
    set_no_show_composite(1);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_I_VOLUME, 0);
    add_item(({"seal","brand","palm","right palm"}), "Upon your right palm "+
            "is a brand of a twelve pointed star surrounded by a ring of blue fire. This "+
            "symbol marks your devotion to the Order of the White.\n");

}

string
show_subloc(string subloc, object on, object for_obj)
{

    if (subloc != WHITE_SUBLOC)
        return 0;

    if (for_obj == on)
        return "You bare a brand on your right palm.\n";

}

void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    dest->add_subloc(WHITE_SUBLOC, this_object());
    dest->add_prop(WHITE_SEAL, 1);

}
