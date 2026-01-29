/* This is experimental. If used, elsewhere it should be made into a library.
 */
#pragma strict_types
#include "defs.h"

#define M_IN "clops in"
#define M_OUT "clops away"
#include "/d/Genesis/steed/new/steed.h";
inherit "/d/Genesis/steed/new/steed";

object pulled_object;

void
create_steed()
{
    string adj = one_of_list(({"bay", "black", "buckskin", "chestnut",
      "cream", "dun", "gray", "roan", "sorrel"}));
    set_name("carthorse");
    add_adj(adj);
    set_short(adj + " carthorse");
    set_long("It is a tall horse with " + LANG_ADDART(adj) +
             " coat and muscular build, bred for pulling. It is equipped " +
             "with a harness.\n");
    add_item("harness",
      "The harness is strapped to the carthorse, allowing it to be fastened " +
      "and unfastened from a cart or plow.\n");
    set_stats(({200, 120, 160, 40, 60, 160}));
    set_m_in(M_IN);
    set_m_out(M_OUT);
    set_stuffed(query_prop(LIVE_I_MAX_EAT));
}

public varargs string short(object for_obj)
{
    if (pulled_object && for_obj && for_obj != TO)
        return ::short(for_obj) + " pulling " +
               LANG_ADDART(pulled_object->short());
    return ::short(for_obj);
}

public object
query_pulled_object()
{
    return pulled_object;
}

public mixed
set_pulled_object(object ob)
{
    if (pulled_object)
        return "The " + short() + " is already pulling the " +
               pulled_object->short() + ".\n";
    if (!present(ob, E(TO)))
        return "The " + ob->short() + " isn't close enough to the " +
               short() + ".\n";
    if (!ob->query_prop(OBJ_I_CAN_BE_PULLED))
        return "The " + short() + " isn't suited for pulling the " +
               ob->short() + ".\n";
    mixed result = ob->set_pulled_by(TO);
    if (result != 1)
        return result;

    pulled_object = ob;
    set_m_in(M_IN + ", pulling " + LANG_ADDART(ob->short()));
    set_m_out(M_OUT + ", pulling " + LANG_ADDART(ob->short()));
    return 1;
}

public varargs int
query_cannot_move_to(object living, mixed destination, string where_t)
{
    int result = ::query_cannot_move_to(living, destination, where_t);

    if (result)
        return result;

    result = pulled_object->query_can_pull(TO);

    if (result != 1)
    {
        living->catch_msg(result);
        return 7;
    }
    return 0;
}

public void
stop_pulling_object()
{
    pulled_object->clear_pulled_by(TO);
    pulled_object = 0;
    set_m_in(M_IN);
    set_m_out(M_OUT);
}

public void
enter_env(object dest, object old)
{
    if (pulled_object &&
        (!present(pulled_object, old) || pulled_object->move(dest)))
        stop_pulling_object();
    return ::enter_env(dest, old);
}

public int
do_fasten(string str)
{
    object ob, *obs1, *obs2;
    if (!parse_command(str, E(TP), "%i 'to' %i", obs1, obs2) ||
        sizeof(obs1) != 2 || sizeof(obs2) != 2 ||
        (obs1[1] != TO && obs2[1] != TO))
    {
        notify_fail(CAP(query_verb()) + " what to what?\n");
        return 0;
    }

    if (obs1[1] == TO)
        ob = obs2[1];
    else
        ob = obs1[1];

    string s      = short();
    mixed  result = set_pulled_object(ob);
    if (result == 1)
    {
        TP->catch_msg("You " + query_verb() + " the " + QSHORT(ob) +
                      " to the " + s + ".\n");
        TELL_CAN_SEE_OTHER(E(TO),
          QCTNAME(TP) + " fastens the " + QSHORT(ob) + " to the " + s + ".\n",
          TP);
    }
    else
        TP->catch_msg(result);
    return 1;
}

public int
do_unfasten(string str)
{
    object ob, *obs1, *obs2;
    if (!parse_command(str, E(TP), "%i 'from' %i", obs1, obs2) ||
        sizeof(obs1) != 2 || sizeof(obs2) != 2 ||
        (obs1[1] != TO && obs2[1] != TO))
    {
        notify_fail(CAP(query_verb()) + " what from what?\n");
        return 0;
    }

    if (obs1[1] == TO)
        ob = obs2[1];
    else
        ob = obs1[1];

    if (ob != pulled_object)
    {
        TP->catch_msg("The " + QSHORT(TO) + " is not fastened to the " +
                      QSHORT(ob) + ".\n");
        return 1;
    }
    stop_pulling_object();
    TP->catch_msg("You " + query_verb() + " the " + QSHORT(ob) +
                  " from the " + QSHORT(TO) + ".\n");
    TELL_CAN_SEE_OTHER(E(TO),
      QCTNAME(TP) + " unfastens the " + QSHORT(ob) + " from the " +
        QSHORT(TO) + ".\n",
      TP);
    return 1;
}

public void
add_fatigue(int f)
{
    if (pulled_object)
    {
        object ob = calling_object();
        if (ob->query_prop(ROOM_I_IS) || ob->is_rider_shadow())
            f *= pulled_object->query_prop(OBJ_I_WEIGHT) / 20000;
    }
    ::add_fatigue(f);
}

public void
fail_mount_hook(object who)
{
    if (who)
    {
        who->catch_msg("The " + QSHORT(TO) + " rears back, refusing.\n");
        TELL_CAN_SEE_OTHER(E(TO), "The " + QSHORT(TO) +
          " rears back, refusing to let " + QTNAME(who) + " mount " +
          HIM(TO) + ".\n", TP);
    }
}
public void
handle_lead_status(int sts, object living)
{
    if (sts == STEED_STS_CANNOT_BE_LEAD)
       living->catch_msg("The " + short() + " refuses to follow you.\n");
    else
        ::handle_mount_status(sts, living);
}

public int
can_lead(object living)
{
    if (MASTER_OB(living) == COMMON_NPC_DIR + "labourer")
        return STEED_STS_OK;
    return STEED_STS_CANNOT_BE_LEAD;
}

public int
can_mount(object o)
{
    if (o->query_skill(SS_ANI_HANDL) < 40)
        return STEED_STS_SKILL_TOO_LOW;
    return STEED_STS_OK;
}

public void
init_living()
{
    ::init_living();
    add_action(do_fasten, "fasten");
    add_action(do_unfasten, "unfasten");
}
