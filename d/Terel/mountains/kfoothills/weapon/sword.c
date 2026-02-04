#include "/d/Terel/include/Terel.h"
#include <wa_types.h>

inherit STDWEAPON;

create_weapon()
{
    ::create_weapon();
    set_name("shortsword");
    add_name("sword");
    set_pname("shortswords");
    add_pname("swords");
    set_adj("small");
    set_short(short_desc());
    set_long("This sword has been dented and chipped in many places " +
        "while still remaining functional, you doubt that it will " +
        "hold up under the stress of heated battle.\n");

    set_hit(10 + random(5));
    set_pen(7 + random(5));
    set_wt(W_SWORD);
    set_dt(W_SLASH|W_IMPALE);
    set_hands(W_ANYH);

    set_dull(1);
    set_likely_dull(15);
    set_corroded(1);
    set_likely_corr(15);
    set_likely_break(15);
    
    add_prop(OBJ_I_WEIGHT, 3000);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_VALUE, 75);

}

mixed
short_desc()
{
    switch(random(5))
    {
        case 0:
            set_pshort("chipped shortswords");
            add_adj("chipped");
            return "chipped shortsword";

        case 1:
            set_pshort("flimsy shortswords");
            add_adj("flimsy");
            return "flimsy shortsword";

        case 2:
            set_pshort("thin shortswords");
            add_adj("thin");
            return "thin shortsword";

        case 3:
            set_pshort("dented shortswords");
            add_adj("dented");
            return "dented shortsword";

        case 4:
            set_pshort("worn shortswords");
            add_adj("worn");
            return "worn shortsword";

        default:
            set_pshort("small shortswords");
            return "small shortsword";

    }
}

