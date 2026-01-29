
inherit "/std/food";
#include <stdproperties.h>

#define TP this_player()
create_food()
{
    set_name("bread");
    set_adj("mystic");
    set_long("A small mystical loaf of luminous bread.\n");
    set_amount(50); /* 50 grams of food. */
    add_prop(OBJ_I_WEIGHT, 300); 
    add_prop(OBJ_I_VOLUME, 100);
}

int eat_one_thing(object ob)
{
    set_alarm(1.0, -1.0, "nourish", TP);
    return ::eat_one_thing(ob);
    
}

void
nourish(object pl){


    pl->catch_msg("You feel a mystic power as the bread nourishes you.\n");
    pl->add_mana(15);
    pl->heal_hp(5);
}

    
