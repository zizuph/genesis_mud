/*
 * inkpot for Bilbo Quest
 * Finwe, 2/99
 */

inherit "/std/object";
#include <stdproperties.h>      /* Properties */

create_object()
{
    set_name(({"inkpot", "ink", "ink pot"}));
    add_name("_imladris_ink_");

    set_short("black inkpot");
    add_adj("black");

    set_long("This pot is small and squat. The top flares " +
		"out slightly and is covered with ink drippings. The pot " +
		"is made of potter and nearly full of black ink.\n");
    add_item(({"ink", "black ink"}),
        "The ink is black and slightly runny. It is used to pen " +
        "messages and correspondence by the elves. The ink " +
        "appears to be high quality as there are no noticable " +
        "lumps or impurities floating in it.\n");

    add_prop(OBJ_I_WEIGHT, 14);
    add_prop(OBJ_I_VALUE,  34);
    add_prop(OBJ_I_VOLUME, 20);

}

