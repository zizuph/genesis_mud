/*
 *  /d/Gondor/clubs/nisse/obj/cram.c
 *
 *  Cram. The dwarven waybread.
 *
 *  Deagol, March 2003
 */

inherit "/std/food";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_food()
{
    ::create_food();
    
    set_name("cram");
    add_name(({"waybread", "bread", "cake"}));
    set_pname("crams");
    set_short("cake of cram");
    set_pshort("cakes of cram");
    set_long("This way bread which is believed to have dwarven origins " +
        "is hard and tasteless but very filling. The cram is made from " +
        "bits of smoked meats, cereal grains and lard. It tastes as bad " +
        "as you might think.\n");

    set_amount(250);

    add_prop(OBJ_I_VALUE, 1200);
    add_prop(OBJ_I_WEIGHT, 300);
    add_prop(OBJ_I_VOLUME, 300);
}

/*
 *  Function name: special_effect
 *  Description  : This routine is called when a player eats the cram.
 *  Arguments    : int amnt - amount of food
 */
public void
special_effect(int amnt)
{
    object	player = TP;
    int		max_fatigue;
    int		fatigue;
    int		stomach_size;
    int		stomach_free;
    int		amount;
    
    max_fatigue = player->query_max_fatigue();
    fatigue = max_fatigue / 2 + random (40);
    stomach_size = player->eat_max();
    stomach_free = player->query_stuffed();
    amount = stomach_size - stomach_free;
    amount /= 5;
    player->add_fatigue(fatigue);
    while(player->eat_food(amount, 0));

    write("You shudder. You cannot remember the last time that you ate " +
        "anything quite so tasteless. But the cram fills your stomach " +
        "pretty well and makes you feel better.\n");
}
