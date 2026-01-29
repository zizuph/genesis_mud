/* Modified from std_knife in ~/common/wep/knife */
/* Large knife wielded by big kender in Kendermore */
/* Gwyneth, June 1999 */

#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Ansalon/common/defs.h"

inherit "/std/weapon";
string *knifelooks=({"silvery","sleek","leaf-shaped","sharp"});
string *knifetype=({"dagger","knife"});
string type = "knife";
string looks = "silvery";
int attack = 0;

create_weapon()
{
    type = knifetype[random(2)];
    looks = knifelooks[random(4)];
    set_name(({type,"_knife_"}));
    set_adj(({"large", looks}));
    set_long("It's a "+short()+". It looks like a decent enough weapon.\n");
    set_default_weapon(18, 18, W_KNIFE, W_SLASH, W_ANYH);
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 1000);
}

string
query_recover()
{
    return MASTER + ":" + query_wep_recover() + "&&" + type + "&&" +
        looks; 
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    set_name(a[1]);
    set_adj(({"large", a[2]}));
    init_wep_recover(a[0]);
}
