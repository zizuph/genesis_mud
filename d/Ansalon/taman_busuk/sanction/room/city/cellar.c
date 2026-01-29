
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../../local.h"

inherit SANCTION_IN;

// Protypes
string open_trapdoor();
string unlock_trapdoor();
string lock_trapdoor();
string close_trapdoor();
int go_east();
void reset_sanction_room();

int trapdoor_locked = 1;
int trapdoor_open = 0;

object guard1;
object guard2;

void
create_sanction_room()
{
    set_short("An old cellar inside an old storage building");
    set_long("An old, dark, and long forgotten cellar inside a " +
             "storage building. It might have once been used for "+
             "storage but it has all been cleared out long ago.\n"+
             "In the middle of the roof is @@trapdoor@@ leading up.\n");

    add_item(({"building", "cellar"}), long());
    add_item(({"board", "floor"}), "The floor is made out of old wooden boards.\n");
    add_item("trapdoor", "There is a trapdoor leading up from the cellar into an old warehouse.\n");
    add_item("lock", "You notice a lock in the trapdoor.\n");
    add_cmd_item("trapdoor", "open", open_trapdoor);
    add_cmd_item("trapdoor", "unlock", unlock_trapdoor);
    add_cmd_item("trapdoor", "close", close_trapdoor);
    add_cmd_item("trapdoor", "lock", lock_trapdoor);
    add_exit(SCITY + "kalen_room", "east", go_east);
    reset_sanction_room();
}


void
reset_sanction_room()
{
    trapdoor_locked = 1;
    trapdoor_open = 0;
    remove_exit("up");

    if(!objectp(guard1))
    {
        guard1 = clone_object(SNPC+"kalen_guard1");
        guard1->move(TO, 1);
        guard1->arm_me();
    }
    if(!objectp(guard2))
    {
        guard2 = clone_object(SNPC+"kalen_guard2");
        guard2->move(TO, 1);
        guard2->arm_me();
    }
}

string open_trapdoor()
{
    if(trapdoor_locked)
    {
        return "You can't open it, it is locked.\n";
    }
    add_exit(SCITY + "warehouse03", "up");

    (SCITY+"warehouse03")->set_trapdoor_open_state(1);
    trapdoor_open = 1;
    return "You open the trapdoor.\n";
}

string unlock_trapdoor()
{
    if(trapdoor_locked == 0)
    {
        return "The trapdoor is already unlocked.\n";
    }
    trapdoor_locked = 0;
    (SCITY+"warehouse03")->set_trapdoor_locked_state(0);
    return "You unlock the trapdoor.\n";
}

string close_trapdoor()
{
    if(trapdoor_open)
    {
        trapdoor_open = 0;
        remove_exit("up");
        (SCITY+"warehouse03")->set_trapdoor_open_state(0);
        return "You close the trapdoor.\n";
    }
    return "The trapdoor is already closed.\n";
}

string lock_trapdoor()
{
    if(trapdoor_locked)
    {
        return "The trapdoor is already locked.\n";
    }
    (SCITY+"warehouse03")->set_trapdoor_locked_state(1);
    trapdoor_locked = 1;
    
    return "You lock the trapdoor.\n";

}

string trapdoor()
{
    if(trapdoor_open)
    {
        return "an open trapdoor";
    }
    else
    {
        return "a closed trapdoor";
    }
}

int go_east()
{
    object guard1 = present("_kalen_guard1");
    object guard2 = present("_kalen_guard2");

    int blocked_from_going_east = 0;
    
    if(guard1 && guard2)
    {
        TP->catch_msg(QCTNAME(guard1)+" and "+QTNAME(guard2)+" block your way to the east.\n");
        tell_room(TO, QCTNAME(guard1)+" and "+QTNAME(guard2)+" stop "+QTNAME(TP)+" from going east.\n", TP);
        blocked_from_going_east = 1;
    }
    else if(guard1)
    {
        TP->catch_msg(QCTNAME(guard1)+" blocks your way to the east.\n");
        tell_room(TO, QCTNAME(guard1)+" stops "+QTNAME(TP)+" from going east.\n", TP);
        blocked_from_going_east = 1;
    }
    else if(guard2)
    {
        TP->catch_msg(QCTNAME(guard1)+" blocks your way to the east.\n");
        tell_room(TO, QCTNAME(guard1)+" stops "+QTNAME(TP)+" from going east.\n", TP);
        blocked_from_going_east = 1;
    }
    return blocked_from_going_east;
}

void set_trapdoor_locked_state(int locked)
{
    trapdoor_locked = locked;
    tell_room(TO, "You hear a soft click.\n");
}

void set_trapdoor_open_state(int open)
{
    trapdoor_open = open;
    tell_room(TO, "Someone opens the trapdoor.\n");
}
