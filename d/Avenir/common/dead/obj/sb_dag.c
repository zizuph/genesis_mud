// Dagger for the banshee of the masrhes
//    -I.

inherit "/std/weapon";
#include "/d/Avenir/common/common.h"

create_weapon()
{

    set_name("dagger");
    add_name(({"knife","dagger"}));
    set_pname(({"daggers","knives"}));
    set_adj(({"silverblue","silver","blue","steel"}));
    set_short("silverblue dagger");
    set_long("This is a long straight dagger, tapering off to a "
        +"razor sharp tip. The blade is made of an alloy of "
        +"silver and some unidentifiable blue metal. The haft seems "
        +"to be made mostly of oak, rising to a thin steel handguard "
        +"in the middle.\n");

    set_hit(20);
    set_pen(20);   // as good as a non-magical knife is allowed to be
    set_wt(W_KNIFE);

    set_dt(W_IMPALE);
    set_hands(W_RIGHT);

   add_prop(OBJ_I_VALUE, 1183);
   add_prop(OBJ_I_WEIGHT, 800);
   add_prop(OBJ_I_VOLUME, 1000);

}

