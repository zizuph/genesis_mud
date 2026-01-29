/* 
 * Trinkets worn by the ogres of the Tharkadan mountains.
 *
 * Based on burial ornament for the skeletons underneath the Tower of Arms
 * in Palanthas.
 *
 */

#pragma strict_types

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

inherit "/std/armour";
inherit "/lib/keep";

int at;
string recover_string, adj1, name1;

/* Prototypes */
void my_at();
string my_short();
void set_armour_data(string data);

void
create_armour()
{
}

varargs void
set_trinket_adjective(string desc)
{
    if (!strlen(desc))
        desc = one_of_list(({"tribal", "simple", "runed", "crude", "bone",
        "ornate", "onyx-encrusted", "primitive", "dull", "copper-studded" }));
    
    adj1 = desc;
}

varargs void
set_trinket_name(string desc)
{
    if (!strlen(desc))
        desc = one_of_list(({"talisman", "charm", "amulet", "pendant",
        "ornament", "arm band", "armlet","earring"}));
    
    name1 = desc;
}

void
make_the_trinket()
{
    set_trinket_adjective();
    set_trinket_name();
    set_armour_data("&&" + adj1 + "&&" + name1 + "&&");
}

void
set_armour_data(string data)
{
    seteuid(getuid());
    
    string foo, bar;
    
    sscanf(data, "%s&&%s&&%s&&%s", foo, adj1, name1, bar);
    if (sizeof(explode(data, "&&")) < 3)
        sscanf(data, "%s&&%s", adj1, name1);
    
    if (intp(adj1) || adj1 == "0")
        set_trinket_adjective();
    
    if (intp(name1) || name1 == "0")
        set_trinket_name();
    
    set_ac(1);
    my_at();
    set_at(at);
    
	add_prop(OBJ_I_VOLUME, 50 + random(100));
	add_prop(OBJ_I_WEIGHT, 200 + random(150));
	add_prop(OBJ_I_VALUE, 30 + random(120));

    /* This armour is wearable by ogres. */
    add_prop(AOD_WEAR_PROP, 1);
    
    set_name(name1);
    add_pname("trinket");
    add_adj(adj1);

    set_keep(0);
    set_af(TO);

    set_short(my_short);
    set_long("This " + name1 + " is a trinket commonly worn by a tribe " +
        "of ogre barbarians lairing in the Tharkadan mountain range.\n");

    recover_string = "&&" + adj1 + "&&" + name1 + "&&";
}

string
my_short()
{

    return adj1 + " " + name1;
}

void
my_at()
{
    switch(name1)
    {
        case "talisman":
        case "charm":
        case "ornament":
        case "armlet":
            at = A_WRISTS;
            break;
        case "arm band":
            at = A_ARMS;
            break;
        case "earring":
            at = A_EARS;
            break;
        default:
            at = A_NECK;
    }
}

string
query_recover()
{
    return ::query_recover() + recover_string;
}

void
init_recover(string arg)
{
    ::init_recover(arg);
    ::init_keep_recover(arg);
    set_armour_data(arg);
}
