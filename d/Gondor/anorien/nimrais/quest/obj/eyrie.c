 
inherit "/std/container";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"

object solver;
 
create_container()
{
    set_name("eyrie");
    add_name("nest");
    set_adj("eagle's");
    set_short("eagle's eyrie");
    set_long("It's a big eyrie of an eagle. In it eggs would be well protected.\n");
/*  Commented this line out, Olorin
 * When you try to search an object which has set_no_show_composite(1)
 * set you get: You start to search something.
 * Since this led to several bug reports, I removed the line.
    set_no_show_composite(1);
*/
    add_prop(CONT_I_IN, 1);
    add_prop(CONT_I_RIGID, 1);
    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_WEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 2000);
    add_prop(CONT_I_MAX_WEIGHT, 4000);
    add_prop(CONT_I_MAX_VOLUME, 6000);
    add_prop(CONT_M_NO_REM, "@@check_remove");
    add_prop(OBJ_I_NO_GET, 1);
    FIX_EUID
    enable_reset();
}
 
void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);
    if (!obj->query_prop("_eagle_quest_egg"))
        return;
    solver = TP;
}
 
void
quest_check()
{
    int reward;
    object egg;
    if (!solver)
        return;
    if (!(egg = present("egg", TO)))
        return;
    if(!egg->query_prop("_eagle_quest_egg"))
        return;
 
    ENV(TO)->add_eagle();
    egg->remove_prop("_eagle_quest_egg");
    tell_room(ENV(TO), "The eagle sits onto the egg.\n");
    if (solver->test_bit("Gondor", GONDOR_GROUP, EAGLES_EGG_BIT))
        return;
    reward = solver->query_exp();
    if(reward > EAGLES_EGG_EXP)
        reward = EAGLES_EGG_EXP;
    solver->set_bit(GONDOR_GROUP, EAGLES_EGG_BIT);
    solver->adjust_alignment(300);
    solver->add_exp_quest(reward);
    tell_object(solver, BS("When the eagle returns to the eyrie and finds the " +
      "egg returned, he prays to Manwe Sulimo to reward you.\n"));
    tell_object(solver, "You feel much more experienced.\n");
    LOG_QUEST(solver, reward, "EAGLE'S EGG QUEST");
#if 0
    write_file(QUEST_LOG, "EAGLE'S EGG QUEST: Solved by "+solver->query_name()+" ("+
        solver->query_average_stat()+") on " + ctime(time()) + ", " + reward + " exp. \n");
#endif
    solver = 0;
}
 
mixed
check_remove()
{
    if (ENV(TO)->query_is_eagle())
        return "The eagle prevents you from getting anything from the eyrie.\n";
    return 0;
 
}
 
reset_container()
{
    object egg;
    ::reset_container();
    egg = present("egg", TO);
    if (egg) egg->remove_object(); /* We don't want dozens of eggs :) */
    if (ENV(TO)->query_is_eagle()) {
        tell_room(ENV(TO), "The eagle rises on its wings and flies away.\n");
        ENV(TO)->query_is_eagle()->remove_object();
        ENV(TO)->add_item(({"eagle"}),BSN(
          "High above the rock on which you are standing, " +
           "you can see an eagle circling the mountain. "));
    }
}
