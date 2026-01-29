/* SARR */
#define RAUMDOR_SCRIPTURE_WITNESSES "_raumdor_scripture_witnesses"
#include "defs.h"
inherit "/std/object";
inherit "/lib/holdable_item";
void
create_object()
{
    set_name(({"tome", "scripture"}));
    set_adj("ancient");
    set_long("The faded colors, aged clasps, and wrinkled leather binding "
        + "indicate that this tome is very old. It is completely covered "
        + "with intricately decorated with what appear to be holy symbols.\n");
    add_prop(OBJ_I_WEIGHT, 100);
    add_prop(OBJ_I_VOLUME, 80);
    add_prop(OBJ_M_NO_SELL,1);
}

void
leave_env(object from, object to)
{
    ::leave_env(from, to);
    holdable_item_leave_env(from, to);
}

void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_holdable_item();
}

void
enter_env(object to, object from)
{
    if (!query_prop(RAUMDOR_SCRIPTURE_WITNESSES))
    {
        if (from->id("_raumdor_scripture_chest"))
        {
            add_prop(RAUMDOR_SCRIPTURE_WITNESSES, filter(
                FILTER_CAN_SEE_IN_ROOM(FILTER_LIVE(AINV(E(from)))),
                from->check_seen)->query_real_name());
        }
    }
}

int
do_read(string str)
{
    object target;


    notify_fail("Read what?\n");
    if (!str)
        return 0;

    if (!TP->can_see_in_room())
    {
        notify_fail("It is too dark to read.\n");
        return 0;
    }

    if (parse_command(str, E(TP), "[the] %o", target) && target == TO)
    {
        write("You open the tome and try to read it, but it is " +
               "written in an old language that you do not understand.\n");
        return 1;
    } 

    return 0;
}

public void
init()
{
    ::init();
    add_action(do_read, "read");
}
