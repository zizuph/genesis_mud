#pragma strict_types
#include "/d/Avenir/common/common.h"
#include "../defs.h"
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <macros.h>
#include <tasks.h>
#include <terrain.h>

inherit "/std/object";
int kill_id = 0;
float time_to_die;
int time_init, is_dead = 0;

void execute_maggot();

void
create_object()
{

    set_short("small struggling maggot");
    set_long("This is a small struggling maggot, perfect " +
        "to bait a fishing hook with.\n");
    add_name("maggot");
    add_name("_maggot");
    add_adj(({"small","struggling"}));
    add_prop(OBJ_I_VOLUME, 50);
    add_prop(OBJ_I_WEIGHT, 10);    // Maggot weights 10g
    setuid();
    seteuid(getuid());
}

void
kill_maggot()
{

    time_init = time();
    time_to_die = ((rnd() * 420.0) + 5.0);
    if ((TO->query_kill_id()) == 0)
    {
        kill_id = set_alarm(time_to_die, 0.0, &execute_maggot());
    }
}

int
query_kill_id()
{
    return kill_id;
}

void
reset_kill_id()
{
    kill_id = 0;
    time_to_die = 0.0;
    time_init = 0;
}

void
remove_kill()
{
    if (query_kill_id())
    {
        remove_alarm(query_kill_id());
        reset_kill_id();
    }
}

void
execute_maggot()
{
    set_short("dead maggot");
    set_long("This is a dead maggot, no longer perfect " +
        "to bait a fishing hook with. A good can would " +
        "perhaps have kept it alive had you put it " +
        "in there.\n");
    remove_adj(({"small","struggling"}));
    add_adj("dead");
    is_dead = 1;
    if (!(random(3)))
        (ENV(TO))->catch_msg("You feel a sense of loss as if something " +
            "just died.\n");
    reset_kill_id();
}

int
query_time_to_die()
{
    if (time_to_die)
        return ((ftoi(time_to_die) + time_init) - time());
    else
    return 0;
}

int
query_dead()
{
    return is_dead;
}
