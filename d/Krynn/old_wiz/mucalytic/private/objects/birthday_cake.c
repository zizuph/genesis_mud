/* Vivien's Birthday cake. ~mucalytic/private/objects/birthday_cake */

inherit "/std/food";

#include "/sys/stdproperties.h"

void create_food()
{
    set_name("cake");
    set_adj("birthday");
    set_long("A very big birthday cake. Indeed it needs to be big because "+
        "it seems to have been made in layers. Some of these are chocolate "+
        "flavoured, others peach flavoured; all very tasty and all "+
        "sandwiched with cream, strawberries and raspberries. On top are "+
        "some eloquently written words saying: 'Happy Birthday Vivien!'.\n");

    set_amount(20 + random(20));

    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 125);
}
