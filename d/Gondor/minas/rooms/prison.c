#pragma strict_types

inherit "/d/Gondor/std/room";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define SAVE_FILE	(MINAS_DIR + "rooms/prison")
#define DATA_REASON	0
#define DATA_DAYS	1
#define DATA_RACE	2
#define PRISON_CHAIN	(MINAS_DIR + "obj/prison_obj")
#define PRISON_CHAIN_ID	"Minas_Tirith_Prison_Chain"

void    check_chain(object prisoner, int time);

mapping	prisoners = ([]);

void
create_gondor() 
{
    set_short("in a dark, damp prison-cell somewhere in Minas Tirith");
    set_long(BSN("You are sitting in a dark and damp prison-cell, somewhere "
      + "in Minas Tirith. A solid iron door locked from the outside is "
      + "keeping you in between these old stone walls. You will probably "
      + "spend some time here, depending on how serious your crime was."));
    add_item(({"wall","walls","stone wall","stone walls"}), BSN(
        "The stone walls were built many centuries ago, but are still "
      + "solid as...stone."));
  add_item(({"door","iron door"}), BSN("The solid iron door is locked "
      + "from the outside, and there's no keyhole here."));
  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_M_NO_TELEPORT,"This is a prison, no escape possible.\n");
}

int
query_prison_day(string name)
{
    mixed  *data;

    FIX_EUID
    restore_object(SAVE_FILE);
    if (sizeof(data = prisoners[name]))
        return data[DATA_DAYS];
    return -1;
}

void
log_prisoner(string name, string reason, string race)
{
    FIX_EUID
    restore_object(SAVE_FILE);
    prisoners[name] = ({ reason, CLOCK->query_third_age_days(), race });
    save_object(SAVE_FILE);
}

varargs int
jail_time(object prisoner, int time, string reason = "unknown")
{
    if (!objectp(prisoner))
        return 0;
    if (!time)
        time = 300;
    if (!present(prisoner,TO))
    {
        prisoner->move_living("to prison", TO);
        prisoner->catch_msg("A cityguard takes hold of you, and throws you "
          + "into a prison.\n");
    }
    set_alarm(itof(time), 0.0, "release", prisoner);
    check_chain(prisoner, time);

    log_prisoner(prisoner->query_real_name(), reason, prisoner->query_race());
    return 1;
}

void
check_chain(object prisoner, int time)
{
    object  chain;

    if (present(PRISON_CHAIN_ID, prisoner))
        return;

    chain = clone_object(PRISON_CHAIN);
    chain->set_prisoner_name(prisoner->query_real_name());
    chain->set_prison_time(time);
    chain->move(prisoner, 1);
}

void
init() 
{
    ::init();
    add_action("blockact","quit");
    add_action("blockact","commune");
    add_action("try_open","open");

}

int
try_open(string str)
{
    if (!strlen(str) || str != "door")
        return 0;
    write("The door is locked from the outside.\n");
    return 1;
}

int
blockact() 
{
    write("You cannot do that while you are in prison!\n");
    return 1;
}

int
release(object prisoner)
{
    if (!objectp(prisoner) || !present(prisoner, TO))
        return 0;

    tell_room(TO,"A guard comes in and says: You are free to go, "+prisoner->query_name()+".\n");
    prisoner->move_living("to freedom", MINAS_DIR + "rooms/mtoffice");
    tell_object(prisoner,"The guard takes you out of the prison cell, and releases you.\n");
    tell_room(TO,"The guard takes "+QTNAME(prisoner)+" out of the prison.\n");
    return 1;
}

void
reset_rq_stage()
{
    prisoners = ([]);
    FIX_EUID
    save_object(SAVE_FILE);
}

void
remove_prisoner(string name)
{
    FIX_EUID
    restore_object(SAVE_FILE);
    m_delete(prisoners, name);
    save_object(SAVE_FILE);
}

