inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>

#define RECOVER_MARKER "#ARMOURER VARS#"

#define ARMOUR_ARR_PNAME       0
#define ARMOUR_ARR_SHORT       1
#define ARMOUR_ARR_PSHORT      2
#define ARMOUR_ARR_AT          3
#define ARMOUR_ARR_VOLUME      4
#define ARMOUR_ARR_COST        5
#define ARMOUR_ARR_AC_FACTOR   6
#define ARMOUR_ARR_COST_FACTOR 7

#define MATERIAL_ARR_WEIGHT 0
#define MATERIAL_ARR_COST   1
#define MATERIAL_ARR_AC     2

static string recover_string = "";

void
config_me(string type, string material)
{
    mapping armour_map = ([
        "helmet"      : ({ "helmets",
                           "%s helmet",
                           "%s helmets",
                           A_HEAD,
                           1800,
                           400,
                           9,
                           3 }),
        "greaves"     : ({ "greaves",
                           "pair of %s greaves",
                           "pairs of %s greaves", 
                           A_LEGS,
                           1000,
                           400,
                           9,
                           2 }),
        "bracers"     : ({ "bracers",
                           "pair of %s bracers",
                           "pairs of %s bracers", 
                           A_ARMS,
                           800,
                           400,
                           9,
                           2, }),
        "body-armour" : ({ "body-armours",
                           "%s body-armour",
                           "%s body-armours",
                           A_TORSO,
                           7200,
                           600,
                           10,
                           5 }),
        "shield"      : ({ "shields",
                           "%s shield",
                           "%s shields",
                           A_SHIELD,
                           2500,
                           400,
                           10,
                           4 }),
    ]);

    mapping material_map = ([ 
        "copper"  : ({ 1350, 200, 15, }),
        "bronze"  : ({ 1400, 300, 20, }),
        "iron"    : ({ 1600, 400, 25, }),
        "steel"   : ({ 1600, 550, 30, }),
        "mithril" : ({ 1350, 850, 35, }),
    ]);
 
    mixed *material_data = material_map[material];
    mixed *armour_data   = armour_map[type];

    string arm_pname  = armour_data[ARMOUR_ARR_PNAME];
    string arm_short  = sprintf(armour_data[ARMOUR_ARR_SHORT], material);
    string arm_pshort = sprintf(armour_data[ARMOUR_ARR_PSHORT], material);

    recover_string = type + ";" + material;

    set_at(armour_data[ARMOUR_ARR_AT]);
    set_adj(material);
    set_name(type);

    if (strlen(arm_pname))
    {
        set_pname(arm_pname);
    }

    if (strlen(arm_short))
    {
       set_short(arm_short);
    }

    if (strlen(arm_pshort))
    {
        set_pshort(arm_pshort);
    }

    set_ac(material_data[MATERIAL_ARR_AC] * 
        armour_data[ARMOUR_ARR_AC_FACTOR] / 10);

    add_prop(OBJ_I_VALUE, material_data[MATERIAL_ARR_COST] * 
        armour_data[ARMOUR_ARR_COST_FACTOR] / 2);
    add_prop(OBJ_I_WEIGHT, material_data[MATERIAL_ARR_WEIGHT] * 
        armour_data[ARMOUR_ARR_VOLUME] / 1200);
    add_prop(OBJ_I_VOLUME, armour_data[ARMOUR_ARR_VOLUME]);

    set_long("A finely made " + short() + ".  You notice a small " +
        "inscription on it, \"Crafted by Eril of Telberin\".\n");

    update_prop_settings();
}

void
init_arm_recover(string str)
{ 
    string junk, type, material;

    ::init_arm_recover(str);

    if (sscanf(str, "%s" + RECOVER_MARKER + "%s", junk, recover_string) != 2)
    {
        return;
    }

    sscanf(recover_string, "%s;%s", type, material);

    config_me(type, material);
}
    
string
query_recover()
{
    return ::query_recover() + RECOVER_MARKER + recover_string;
}
