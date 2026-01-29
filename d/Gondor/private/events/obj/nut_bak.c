inherit "/std/food";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

public string *type = ({ "almond", "walnut", "hazelnut", "raisin", 
                         "slice", "apricot", "chip", "pecan", 
                         "seed", "peanut" });
/* Prototypes */
public void make_trailmix(string kind);

void
create_food()
{
    string kind = type[random(10)];

    set_name(({kind, "mix", "trailmix", "_gondor_trail_mix_"}));
    add_adj("gondorian");
    make_trailmix(kind);
    set_amount(10);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
}

public void
make_trailmix(string kind)
{
    string extra = kind;

    switch(kind)
    {
        case "almond":
            set_short("salted gondorian almond");
            set_pshort("salted almonds");
            set_adj("salted");
            add_name("nut");
            break;
        case "walnut":
            set_short("wrinkled gondorian walnut");
            set_pshort("wrinkled walnuts");
            set_adj("wrinkled");
            add_name("nut");
            break;
        case "hazelnut":
            set_short("brown gondorian hazelnut");
            set_pshort("brown hazelnuts");
            set_adj("brown");
            add_name("nut");
            break;
        case "raisin":
            set_short("sweet gondorian raisin");
            set_pshort("sweet raisins");
            set_adj("sweet");
            add_name("fruit");
            break;
        case "slice":
            set_short("dried gondorian coconut slice");
            set_pshort("dried coconut slices");
            set_adj("dried");
            add_adj("coconut");
            extra = "coconut slice";
            add_name("fruit");
            break;
        case "apricot":
            set_short("dried gondorian apricot");
            set_pshort("dried apricots");
            set_adj("dried");
            add_name("fruit");
            break;
        case "chip":
            set_short("dried gondorian banana chip");
            set_pshort("dried banana chips");
            set_adj("dried");
            add_adj("banana");
            extra = "banana chip";
            add_name("fruit");
            break;
        case "peanut":
            set_short("salted gondorian peanut");
            set_pshort("salted peanuts");
            set_adj("salted");
            add_name("nut");
            break;
        case "pecan":
            set_short("delicious gondorian pecan");
            set_pshort("delicious pecans");
            set_adj("delicious");
            add_name("nut");
            break;
        default:
            set_short("gondorian sunflower seed");
            set_pshort("sunflower seed");
            set_adj("sunflower");
            add_name("nut");
            extra = "sunflower seed";
            break;
    }

    set_long("This " + extra + " would fit in nicely in some " +
        "trailmix.\n");
}

