/* Modified by Gwyneth from the std_knife in /d/Ansalon/common/wep/knife */
/* June 1999 */
/* Fixed problems with reffering to the weapon with proper name */
/* Torqual 11.01.2001 */

#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
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
    set_name("_knife_");
    add_name("knife");
    if( type == "dagger")
       add_name("dagger");
    set_short("medium " + looks + " " + type);
    set_pshort("medium " + looks + " " + type + "s");
    set_adj(({"medium", looks}));
    set_long("It's a "+short()+". It looks like a decent enough weapon.\n");
    set_default_weapon(15, 15, W_KNIFE, W_SLASH, W_ANYH);
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
    set_adj(({"medium", a[2]}));
    init_wep_recover(a[0]);
}

void
query_type()
{
    write("Type of weapon " + type + "\n");
}

void
set_type()
{
    type="dagger";
}
