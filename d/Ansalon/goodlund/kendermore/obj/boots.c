/* Kender boots by Gwyneth, 05/17/99 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

#define adjecs query_adjs()

string *adjs=({"blue", "red", "green", "yellow", "orange", "purple"});
string *type=({"fur-lined", "sparkly", "flashy", "bright"});
string boottype = "flashy";
string bootadj = "blue";

void
create_armour()
{
    boottype = type[random(4)];
    bootadj = adjs[random(6)];
    set_name(({"boots","_clothes_"}));
    set_short(boottype + " " + bootadj + " pair of boots");
    set_pshort(boottype + " " + bootadj + " pairs of boots");
    add_name("clothes");
    set_adj(({ boottype, bootadj }));
    set_long("It's a warm and comfortable pair of " + adjecs[0] + " boots " +
        "commonly worn by kender. The material is a " +
        "beautiful " + adjecs[1] + " colour. It looks perfect for travel or " +
        "show!\n"); 
    set_ac(4);
    set_at(A_FEET);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 300);
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "&&" + boottype + "&&" +
        bootadj;
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    set_adj(({a[1], a[2]}));
    init_arm_recover(a[0]);
}

