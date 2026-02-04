#include "/d/Terel/include/Terel.h"
inherit "/d/Terel/std/messenger";

#define MESG_WALKER 1
#define MESG_FLIER  2

void
create_messenger()
{
    set_gender(MALE);
    set_race_name("albatross");
    set_adj("small");
    set_long("An small albatross, ready to serve you. He will "
            +"help you <send> a message or <resend> a previous "
            +"attempt. You may also <send reply> if you have "
            +"received a message.\n");

    add_prop(OBJ_I_WEIGHT,  300);
    add_prop(CONT_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME,  200);
    add_prop(CONT_I_VOLUME, 150);
    add_prop(OBJ_I_VALUE,   388);

    set_messenger_type(MESG_FLIER);
    set_send_uses(9);
}
