/* Kender hat by Gwyneth, 05/17/99 */

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>

#define adjecs query_adjs()

string *adjs=({"blue", "red", "green", "yellow", "orange", "purple"});
string *type=({"feathered", "sparkly", "leather", "bright"});

void
create_armour()
{
    string first_adj = type[random(4)], sec_adj = adjs[random(6)];
    set_name(({"hat","_clothes_"}));
    add_name("clothes");
    set_adj(first_adj);
    set_short(first_adj + " " + sec_adj + " hat");
    set_pshort(first_adj + " " + sec_adj + " hats");
    set_pname("hats");
    add_adj(sec_adj);
    set_long("This " + adjecs[0] + " hat is a type often seen around " +
        "Kendermore. The material is a beautiful " + adjecs[1] + " colour. " +
        "There is a small hole in the back for a topknot.\n"); 
    set_ac(10);
    set_at(A_HEAD);
    add_prop(OBJ_I_VALUE, 120);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_WEIGHT, 300);
}

