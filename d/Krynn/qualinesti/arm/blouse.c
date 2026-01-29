
inherit "/std/armour";
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>

#define adjecs query_adjs()

string *adjs=({"blue", "red", "green", "yellow", "orange", "purple"});
string *type=({"comfortable", "bright"});
string blousetype = "bright";
string blouseadj = "yellow";

void
create_armour()
{
    blousetype = type[random(2)];
    blouseadj = adjs[random(6)];
    set_name(({"blouse","_clothes_"}));
    set_pname("blouses");
    set_short(blousetype + " " + blouseadj + " blouse");
    set_pshort(blousetype + " " + blouseadj + " blouses");
    add_name("clothes");
    set_adj(({ blousetype, blouseadj }));
    set_long("It's a beautiful " + adjecs[1] + " blouse, commonly worn by " + 
        "kender. It looks very " + adjecs[0] + ", and perfect for travel or " + 
        "show!\n"); 
    set_ac(39);
    set_at(A_CHEST);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_WEIGHT, 700);
}

string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + "&&" + blousetype + "&&" +
        blouseadj;
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");
    set_adj(({a[1], a[2]}));
    init_arm_recover(a[0]);
}

