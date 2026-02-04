#include "/d/Terel/include/Terel.h"
#include <wa_types.h>

inherit STDWEAPON;

create_weapon()
{
    ::create_weapon();
    set_name("knife");
    add_name("dagger");
    set_pname("daggers");
    add_pname("knives");
    set_adj("metal");
    set_short(short_desc());
    set_long("A crudely made dagger with a short thin blade. " +
        "Tattered leather straps have been wrapped around this " +
        "low-grade metal providing for an uncomfortable " +
        "but effective handle.\n");

    set_hit(7 + random(5));
    set_pen(10 + random(5));
    set_wt(W_KNIFE);
    set_dt(W_SLASH|W_IMPALE);
    set_hands(W_ANYH);

    set_dull(1);
    set_likely_dull(15);
    set_corroded(1);
    set_likely_corr(20);
    set_likely_break(15);
    
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 500);
    add_prop(OBJ_I_VALUE, 100);

}

mixed
short_desc()
{
    switch(random(5))
    {
        case 0:
            set_pshort("old daggers");
            add_adj("old");
            return "old dagger";

        case 1:
            set_pshort("crude daggers");
            add_adj("crude");
            return "crude dagger";

        case 2:
            set_pshort("flimsy daggers");
            add_adj("flimsy");
            return "flimsy dagger";

        case 3:
            set_pshort("thin daggers");
            add_adj("thin");
            return "thin dagger";

        case 4:
            set_pshort("short daggers");
            add_adj("short");
            return "short dagger";

        default:
            set_pshort("metal daggers");
            return "metal dagger";
    }
}
