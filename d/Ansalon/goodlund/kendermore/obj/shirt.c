/* Kender shirt by Gwyneth, 05/17/99 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

#define adjecs query_adjs()

string *adjs=({"blue", "red", "green", "yellow", "orange", "purple"});
string *type=({"sparkly", "flashy", "bright"});
string ctype = "sparkly";
string cadj = "red";

void
create_armour()
{
    ctype = type[random(3)];
    cadj = adjs[random(6)];
    set_name(({"shirt","_clothes_"}));
    add_name("clothes");
    set_short(ctype + " " + cadj + " shirt");
    set_pshort(ctype + " " + cadj + " shirts");
set_pname("shirts");
    set_adj(({ ctype, cadj }));
    set_long("It's a " + adjecs[0] + " short-sleeved shirt, commonly worn " + 
        "by kender. The cloth is a beautiful " + adjecs[1] + " colour. " + 
        "It looks perfect for travel or show!\n"); 
    set_ac(12);
    set_at(A_BODY);
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


