/* An armchair. ~solace/puzzle/objects/armchair */

inherit "/std/object";

#include "../defs.h"
#include "/sys/macros.h"
#include "/sys/cmdparse.h"
#include "/sys/stdproperties.h"

object sitter;

void create_object()
{
    set_name("armchair");
    add_name("chair");
    set_adj("comfortable");
    add_adj("looking");
    set_long("@@my_long");

    add_prop(OBJ_I_WEIGHT, 20000);
    add_prop(OBJ_I_VOLUME, 10000);
    add_prop(OBJ_M_NO_GET, "The armchair is too heavy to lift.\n");
}

void init()
{
    ::init();

    add_action("sit_down", "sit");
    add_action("stand_up", "rise");
    add_action("stand_up", "stand");
}

int sit_down(string str)
{
    object *obj;

    if(!strlen(str))
    {
        notify_fail("Sit on what?\n");
        return 0;
    }

    if(objectp(sitter))
    {
        notify_fail("The chair is already occupied by "+
            sitter->query_the_name(TP)+".\n");
        return 0;
    }

    if(!parse_command(str, TP, "'on' / 'in' %s", str))
    {
        notify_fail("Sit how?\n");
        return 0;
    }

    obj = FIND_STR_IN_OBJECT(str, E(TP));

    if(!sizeof(obj) || obj[0] != TO)
    {
        notify_fail("Sit on what?\n");
        return 0;
    }

    if(TP->query_prop("_live_i_sit"))
    {
        write("You are already sitting down.\n");
        return 1;
    }

    sitter = TP;

    write("You sit down in the "+short()+".\n");
    say(QCTNAME(TP)+" sits on the "+short()+".\n");

    sitter->add_prop("_live_i_sit", TO);
    sitter->add_prop(LIVE_S_EXTRA_SHORT, " (sitting on an armchair)");
    return 1;
}

int stand_up(string str)
{
    if(sitter != TP)
    {
        notify_fail("But you are not sitting down!\n");
        return 0;
    }

    if(strlen(str) && (str != "from chair") && (str != "up"))
    {
        notify_fail("How did you want to stand?\n");
        return 0;
    }

    sitter = 0;

    write("You stand up from the chair.\n");
    say(QCTNAME(TP)+" rises from the "+short()+".\n");

    TP->remove_prop("_live_i_sit");
    TP->remove_prop(LIVE_S_EXTRA_SHORT);
    return 1;
}

string my_long()
{
    if(TP == sitter)
        return("This is the chair you are sitting in.\n");

    if(sitter)
        return("It looks comfortable, but "+sitter->query_the_name(TP)+" is "+
            "sitting on it.\n");
    else
        return("This chair looks comfortable, perhaps you could sit on it.\n");
}

object query_sitter()
{
    return sitter;
}
