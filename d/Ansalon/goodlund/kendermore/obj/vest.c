/* Kender vest by Gwyneth, 05/17/99 */

#include "../local.h"
#include "/d/Ansalon/common/defs.h"
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

inherit "/std/object";
inherit "/lib/wearable_item";

#define adjecs query_adjs()

string *colour=({"blue", "red", "green", "yellow", "orange", "purple"});
string *type=({"flashy", "bright"});
string ctype = "bright";
string cadj = "green";

void
create_object()
{
    ctype = type[random(2)];
    cadj = colour[random(6)];
    set_name(({"vest","_clothes_"}));
    add_name("clothes");
    set_adj(({ ctype, cadj }));
    set_long("It's a " + adjecs[0] + " vest, commonly worn by kender. " + 
        "The cloth is a beautiful " + adjecs[1] + " colour. It looks " + 
        "perfect for travel or show!\n"); 
    set_slots(A_ROBE);
    add_prop(OBJ_I_VALUE, 90);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 300);
    
    set_layers(1);
    set_looseness(20);
}

void
leave_env(object from, object to)
{
        wearable_item_leave_env(from, to);
        ::leave_env(from, to);
}
/*
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
*/
