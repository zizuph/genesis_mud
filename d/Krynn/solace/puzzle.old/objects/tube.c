/* Tube into which water must be poured. ~solace/puzzle/objects/tube */

inherit "/std/container";

#include "../defs.h"
#include "/sys/language.h"
#include "/sys/stdproperties.h"

#define LEVEL_DESC ({ "near the bottom",                           \
                      "a quarter of the way from the bottom",      \
                      "halfway up",                                \
                      "three-quarters of the way from the bottom", \
                      "near the top",                              \
                      "at the top"                                 })

int water_level;

int query_filled()
{
    return water_level;
}

void fill_me(int amount)
{
    if(amount <= 0)
        return;

    if(water_level + amount <= 3000)
        water_level += amount;
    else
        water_level = 3000;
}

void add_object_to_me()
{
    remove_prop(CONT_M_NO_INS);

    seteuid(getuid(TO));
    clone_object(OBJECTS + "pouch")->move(TO);

    add_prop(CONT_M_NO_INS, "You can't quite get it into the tube.\n");
}

void create_container()
{
    set_name("tube");
    set_adj("tall");
    add_adj("clear");
    set_long("This is a clear glass tube, open at the top and fixed to the "+
        "ground at the bottom. It is very tall but is thinner than your arm. "+
        "@@present_pouch_and_how_full@@It seems to be made, not from glass, "+
        "but from a strange enchanted material that does not break.\n");

    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_HIDDEN, 1);

    add_prop(CONT_I_VOLUME,     0);
    add_prop(CONT_I_WEIGHT,     0);
    add_prop(CONT_I_MAX_VOLUME, 10000);
    add_prop(CONT_I_MAX_WEIGHT, 10000);

    add_prop(CONT_I_NO_REM, "@@can_get_object@@");

    add_prop(OBJ_M_NO_GET, "It is fixed to the ground: You cannot take it.\n");

    add_object_to_me();
}

int can_get_object()
{
    if(water_level == 3000)
        return 0;
    else
        return 1;
}

string present_pouch_and_how_full()
{
    object *cont = I(TO);

    if(sizeof(cont))
    {
        if(!water_level)
            return "Inside, you can see "+LANG_ADDART(cont[0]->short())+" "+
                "lying on the bottom. ";
        else
            return "Inside, you can see "+LANG_ADDART(cont[0]->short())+" "+
                "floating in water "+LEVEL_DESC[water_level / 600]+". ";
    }
    else
    {
        if(!water_level)
            return "";
        else
            return "Inside, you can see that water has been poured in, "+
                "right up to the top. ";
    }
}
