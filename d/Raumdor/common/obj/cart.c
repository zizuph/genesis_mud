/* This is exprimental. If used elsewhere, it should be made into a library.
 */

#include "defs.h"
inherit STD_DIR + "breakable_container";

object pulled_by, *guards = ({});

void
create_container()
{
    ::create_container();
    set_name("cart");
    add_adj("wooden");
    set_short("wooden cart");
    set_long(
      "It is a wooden cart with two shafts one side, made to be drawn by a " +
      "beast of burden. Its two wheels are large with thick spokes, a design " +
      "for heavy loads.\n");
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_RIGID, 1);
    // add_prop(CONT_I_HEIGHT, ...);
    add_prop(CONT_I_MAX_VOLUME, 960000); // 960 liters
    add_prop(CONT_I_MAX_WEIGHT, 540000); // 540kg
    add_prop(CONT_I_VOLUME, 32000);      // 320 liters
    add_prop(CONT_I_WEIGHT, 160000);     // 500 kg/m^3 (spruce) = volume * 5
    add_prop(OBJ_I_CAN_BE_PULLED, 1);
}

public mixed
set_pulled_by(object ob)
{
    if (pulled_by)
        return "The " + QSHORT(TO) + " is already being pulled by the " +
               QSHORT(pulled_by) + ".\n";
    pulled_by = ob;
    set_no_show_composite(1);
    add_prop(OBJ_M_NO_GET,
      "You can't do that while it's being pulled by the " +
        QSHORT(pulled_by) + ".\n");
    return 1;
}

public void
clear_pulled_by(object ob)
{
    if (pulled_by == ob)
    {
        pulled_by = 0;
        set_no_show_composite(0);
        remove_prop(OBJ_M_NO_GET);
    }
}

public mixed
query_can_pull(object ob)
{
    // Roll 3kg for ever 1 STR
    if (ob->query_stat(SS_STR) < (query_prop(OBJ_I_WEIGHT) / 3000))
        return "The " + QSHORT(TO) + " is too heavy for the " +
            QSHORT(ob) + ".\n";
    if (query_prop(OBJ_I_BROKEN))
        return "The " + QSHORT(TO) + " needs to be detached first.\n";
    return 1;
}

int
do_pull(string str)
{
    if (PARSE_COMMAND_ONE(str, 0, "%i") != TO)
    {
        notify_fail(CAP(query_verb()) + " what?\n");
        return 0;
    }

    write("It is designed to be pulled one side, not pushed.\n");
    return 1;
}

int
do_push(string str)
{
    if (PARSE_COMMAND_ONE(str, 0, "%i") != TO)
    {
        DEFAULT_NOTIFY;
        return 0;
    }

    write(
      "It would be too unwieldy to pull yourself, even if you were strong " +
      "enough.\n");
    return 1;
}

public void
add_guard(object ob)
{
    if (member_array(ob, guards) < 0)
        guards += ({ob});
}

public object *
query_guards()
{
    return guards;
}

public mixed
query_prop(string prop)
{
    object *guardsHere;

    if (prop == CONT_M_NO_REM || prop == CONT_M_NO_INS)
    {
        guards -= ({0});
        if (sizeof(guards) && member_array(TP, guards) < 0)
        {
            guardsHere = FILTER_PRESENT(guards);
            if (sizeof(guardsHere))
                return "The " + short() + " is being guarded by " +
                  COMPOSITE_LIVE(guardsHere) + ".\n";
        }
    }
    return ::query_prop(prop);
}

void
check_break()
{
    try_break_container(3);
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    set_alarm(0.0, 0.0, &check_break());
}

void
enter_inv(object ob, object old)
{
    ::enter_inv(ob, old);
    set_alarm(0.0, 0.0, &check_break());
}

void
init()
{
    add_action(do_pull, "pull");
    add_action(do_push, "push");
}
