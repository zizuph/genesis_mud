/* Ashlar, 3 Aug 97 */

inherit "/std/armour";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>

#define ONE_OF(x)   ((x)[random(sizeof(x))])

string *a1 = ({ "soiled", "dirty", "tattered", "long",
    "grimy" });
string *a2 = ({ "white", "brown", "black", "yellowed",
    "leather", "cloth" });

string gAdj1, gAdj2;

void
set_desc(string adj1, string adj2)
{
    if (stringp(gAdj1))
        remove_adj(gAdj1);
    if (stringp(gAdj2))
        remove_adj(gAdj2);
    set_adj(gAdj1 = adj1);
    add_adj(gAdj2 = adj2);
    set_short(adj1 + " " + adj2 + " apron");
}

void
create_armour()
{
    set_name("apron");
    set_desc(ONE_OF(a1),ONE_OF(a2));
    set_long("This apron is rather dirty, and is covered with spots " +
        "in different colours. A strap goes around the neck, and " +
        "it is tied behind the back.\n");
   set_ac(2);
   set_at(A_ROBE);
   add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(2)+random(20));
   add_prop(OBJ_I_VOLUME, 800);
   add_prop(OBJ_I_WEIGHT, 1000);
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "&&" + gAdj1 + "&&" + gAdj2;
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    set_desc(a[1],a[2]);
    init_arm_recover(a[0]);
}


