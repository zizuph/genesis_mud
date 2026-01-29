/* Kender cloak by Gwyneth, 05/17/99 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

#define adjecs query_adjs()

string *adjs=({"blue", "red", "green", "yellow", "orange", "purple"});
string *type=({"expensive", "sparkly", "flashy", "bright"});
string ctype = "flashy";
string cadj = "yellow";

void
create_armour()
{
    ctype = type[random(4)];
    cadj = adjs[random(6)];
    set_name("cloak");
    add_name(({"clothes","_clothes_"}));
    set_adj(({ ctype, cadj }));
    set_short(ctype + " " + cadj + " cloak");
    set_pshort(ctype + " " + cadj + " cloaks");
    set_pname("cloaks");
    set_long("It's a warm and " + adjecs[0] + " cloak, commonly worn by " + 
        "kender. The cloth is a beautiful " + adjecs[1] + " colour. It " + 
        "looks perfect for travel or show!\n"); 
    set_ac(5);
    set_at(A_ROBE);
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

