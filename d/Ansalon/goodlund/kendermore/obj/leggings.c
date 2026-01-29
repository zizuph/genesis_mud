/* Kender leggings by Gwyneth, 05/17/99 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

#define adjecs query_adjs()

string *adjs=({"blue", "red", "green", "yellow", "orange", "purple"});
string *type=({"sparkly", "tight", "flashy", "bright"});
string ctype = "bright";
string cadj = "blue";

void
create_armour()
{
    ctype = type[random(4)];
    cadj = adjs[random(6)];
    set_name(({"leggings","_clothes_"}));
    add_name("clothes");
    set_short(ctype + " " + cadj + " pair of leggings");
    set_pshort(ctype + " " + cadj + " pairs of leggings");
    set_adj(({ ctype, cadj }));
    set_long("It's a " + adjecs[0] + " and comfortable pair of leggings, " + 
        "commonly worn by kender. The cloth " + 
        "is a beautiful " + adjecs[1] + " colour. It looks perfect for " + 
        "travel or show!\n"); 
    set_ac(7);
    set_at(A_LEGS);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 300);
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "&&" + ctype + "&&" +
        cadj;
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    set_adj(({a[1], a[2]}));
    init_arm_recover(a[0]);
}


