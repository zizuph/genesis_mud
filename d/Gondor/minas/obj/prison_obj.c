/*
 *	/d/Gondor/minas/obj/prison_obj.c
 *
 *	An invisible item that will put players back into
 *	prison if they escaped by linkdeath.
 *
 *	Olorin, June 1995
 */
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define PRISON		(MINAS_DIR + "rooms/prison")

int     prison_time = 300,
        alarm_id;
string  prisoner_name;

void
create_object()
{
    set_name("Minas_Tirith_Prison_Chain");
    add_name(({"chain", }));

    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_STEAL, 1);

    set_no_show();
}

void
set_prisoner_name(string name)
{
    prisoner_name = LOW(name);
}

void
set_prison_time(int time)
{
    prison_time = MAX(30, time);
}

string
query_auto_load()
{
    mixed  call;

    if (!alarm_id || !sizeof(call = get_alarm(alarm_id)))
        return 0;

    return MASTER + ":" + "#"
         + prisoner_name + "#"
         + ftoi(call[2]) + "#";
}

void
init()
{
    ::init();

    if ((TP != ENV(TO)) || (TP->query_real_name() != prisoner_name))
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    // make sure that the autoload string is updated
    TP->save_me(1);

    alarm_id = set_alarm(itof(prison_time - 10), 0.0, remove_object);
}

void
init_arg(string str)
{
    string  dummy;

    if (!strlen(str))
        return;

    sscanf(str, "%s#%s#%d#", dummy, prisoner_name, prison_time);

    if (ENV(TO)->query_real_name() != prisoner_name)
    {
        set_alarm(0.0, 0.0, remove_object);
        return;
    }

    ENV(TO)->move_living("into jail", PRISON);
    PRISON->jail_time(ENV(TO), prison_time, "returned from linkdeath");
}
    

