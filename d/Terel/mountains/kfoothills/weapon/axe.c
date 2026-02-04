#include "/d/Terel/include/Terel.h"
#include <wa_types.h>

inherit STDWEAPON;

create_weapon()
{
    ::create_weapon();
    set_name("axe");
    add_name("hatchet");
    set_pname("hatchets");
    add_pname("axes");
    set_adj("stone");
    set_short(short_desc());
    set_long("A chunk of hard rock about the size of a fist has been " +
        "ground flat on one side creating a chipped but effective edge " +
        "used for chopping. A small shaft of wood has been fastened on " +
        "with some crude leather strappings. \n");

    set_hit(10 + random(5));
    set_pen(10 + random(5));
    set_wt(W_AXE);
    set_hands(W_ANYH);
    set_dt(W_SLASH|W_BLUDGEON);
    set_dull(1);
    set_likely_corr(0);
    set_likely_break(15);
    set_likely_dull(30);
    
    add_prop(OBJ_I_WEIGHT, 3500);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 100);

}

mixed
short_desc()
{
    switch(random(5))
    {
        case 0:
            set_pshort("chipped stone hatchets");
            add_adj("chipped");
            return "chipped stone hatchet";

        case 1:
            set_pshort("dull stone hatchets");
            add_adj("dull");
            return "dull stone hatchet";

        case 2:
            set_pshort("small stone hatchets");
            add_adj("small");
            return "small stone hatchet";

        case 3:
            set_pshort("worn stone hatchets");
            add_adj("worn");
            return "worn stone hatchet";

        case 4:
            set_pshort("crude stone hatchets");
            add_adj("crude");
            return "crude stone hatchet";

        default:
            set_pshort("stone hatchets");
            return "stone hatchet";
    }
}
