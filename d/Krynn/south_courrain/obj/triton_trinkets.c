/* 
 * Trinkets worn by the tritons in the Courrain Ocean.
 *
 * Based on burial ornament for the skeletons underneath 
 * the Tower of Arms in Palanthas.
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

void
create_armour()
{
}

void
set_armour_data(string data)
{
    seteuid(getuid());

    string* txt = explode(data,"&&");
    adj1 = txt[0];
    name1 = txt[1];

    set_ac(1);
    my_at();
    set_at(at);
    
	add_prop(OBJ_I_VOLUME, 50 + random(100));
	add_prop(OBJ_I_WEIGHT, 200 + random(150));
	add_prop(OBJ_I_VALUE, 140 + random(120));

    set_name(name1);
    add_pname("trinket");
    add_adj(adj1);

    set_keep(0);
    set_af(TO);

    set_short(my_short);
    set_long("This " + name1 + " is a trinket commonly worn by " +
        "the aquatic humanoids known as tritons.\n");

    recover_string = data;
}

void
make_the_trinket()
{
    adj1 = one_of_list(({"netted", "intricate", "beautiful", "coral", 
        "whalebone", "ornate", "pearl-studded" }));

    name1 = one_of_list(({"talisman", "charm", "amulet", "pendant",
        "ornament", "arm band", "armlet", "necklace", "earring"}));

    set_armour_data(adj1 + "&&" + name1);

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
            at = A_WRISTS;
            break;
        case "arm band":
        case "armlet":
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
    return ::query_recover() + "$$" + recover_string;
}

void
init_recover(string arg)
{
    string arm_recover, item_stuff;

    /* If this is an old recovery without the ::query_recover() 
     * stuff, just set item_stuff to arg */
    if (sscanf(arg, "%s$$%s", arm_recover, item_stuff) == 0)
        item_stuff = arg;

    ::init_recover(arg);
    set_armour_data(item_stuff);
}
