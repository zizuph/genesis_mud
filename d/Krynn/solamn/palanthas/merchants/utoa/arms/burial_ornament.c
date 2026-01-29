/* 
 * Mortis 10.2006
 *
 * Burial ornament for the skeletons underneath the Tower of Arms
 * in Palanthas.
 *
 * Arman 06.2016 
 * Reduced value by a factor of x10. 
 *
 * Cotillion, 2016-07-05 
 * - Fixed syntax error
 */

#pragma strict_types

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../../../local.h"

inherit "/d/Krynn/solamn/palanthas/obj/crafted_armour";

int at;
string adj1, adj2, name1;

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
    adj2 = txt[1];
    name1 = txt[2];

    set_ac(1);
    my_at();
    set_at(at);
    
	add_prop(OBJ_I_VOLUME, 100 + random(100));
	add_prop(OBJ_I_WEIGHT, 200 + random(150));
	add_prop(OBJ_I_VALUE, 30 + random(120));

    set_name(name1);
    add_pname("jewelry");
    add_adj(adj1);
    add_adj(adj2);

    set_keep(0);
    set_af(TO);

    set_short(my_short);
    set_long("Finished with loving detail and precision, this "
            + name1 + " is " + adj1 + " and " + adj2 + 
            " was no doubt once very expensive.\n");

    recover_string = data;
}

void
make_the_jewel()
{
    adj1 = one_of_list(({"gold", "platinum", "ruby-encrusted",
        "emerald-encrusted", "diamond-studded", "ornate", "simple",
        "noble", "brilliant", "lustrous", "luxurious"}));

    adj2 = one_of_list(({"gold", "platinum", "ruby-encrusted",
        "emerald-encrusted", "diamond-studded", "ornate", "linked",
        "chain"}));

    name1 = one_of_list(({"bracelet", "wristlet", "necklace", "pendant",
        "belt", "girdle"}));

    set_armour_data(adj1 + "&&" + adj2 + "&&" + name1);

}

string
my_short()
{
    if (adj1 == adj2)
    {
        return adj1 + " " + name1;
    }

    return adj1 + " " + adj2 + " " + name1;
}

void
my_at()
{
    switch(name1)
    {
        case "bracelet":
        case "wristlet":
            at = A_WRISTS;
            break;
        case "necklace":
        case "pendant":
            at = A_NECK;
            break;
        default:
            at = A_WAIST;
    }
}

