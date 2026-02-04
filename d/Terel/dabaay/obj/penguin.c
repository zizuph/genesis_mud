#include "/d/Terel/include/Terel.h"
inherit "/d/Terel/std/messenger";

#define MESG_WALKER 1
#define MESG_FLIER  2

void
create_messenger()
{
    set_race_name("penguin");
    set_adj("small");
    set_long("A small penguin, ready to serve you. He will "
            +"help you <send> a message or <resend> a previous "
            +"attempt.\n");
    add_prop(OBJ_I_WEIGHT,  600);
    add_prop(CONT_I_WEIGHT, 350);
    add_prop(OBJ_I_VOLUME,  550);
    add_prop(CONT_I_VOLUME, 350);
    add_prop(OBJ_I_VALUE,    288);

    set_messenger_type(MESG_WALKER);
    set_send_uses(6);
}
