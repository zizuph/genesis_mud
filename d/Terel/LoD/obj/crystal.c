/*
 * crystal.c
 *
 */
#include "/d/Terel/include/Terel.h"
inherit STDOBJECT;

#include <ss_types.h>

#include "/d/Terel/LoD/dungeon/quest.h"

int lit = 0;

public void
reset_object()
{
    if (lit) {
        change_prop(OBJ_I_LIGHT, 0);
        ETO->update_light(1);
        lit = 0;
    }
}

public void
create_object()
{
    set_name("crystal");
    add_name("block");
    set_adj(({"large"}));
    
    set_long("It is the largest single-crystal you ever have seen. " +
             "It has no flaws and looks very clear, still, you cannot " +
             "see through it.\n");
    
    add_prop(OBJ_I_WEIGHT, 150000);
    add_prop(OBJ_I_VOLUME, 53000);
    add_prop(OBJ_I_VALUE, 10000);
    add_prop(OBJ_I_LIGHT, 0);
    add_prop(OBJ_M_NO_GET, "It's too heavy.\n");
    add_prop(OBJ_M_NO_GIVE, "It's too heavy.\n");
}

public int
do_enter(string str)
{
    if (!str || !id(str))
        return 0;
    
    if (!TP->query_prop(DQ_DUBBING) || !lit)
        return 0;

    if (!CAN_SEE_IN_ROOM(TP) || !CAN_SEE(TP, TO) || !lit)
        return 0;
        
    write("You merge with the " + short() + "!\n");
    say(QCTNAME(TP) + " disappears into the " + short() + "!\n");
    TP->move_living("M", LOD_DIR + "dungeon/cryst1");
}

public int
do_touch(string str)
{
    if (!str || !id(str))
        return 0;
        
    notify_fail("Touch what?\n");
    if (!CAN_SEE_IN_ROOM(TP) || !CAN_SEE(TP, TO))
        return 0;
        
    write("You touch the " + short() + ".\n");
    say(QCTNAME(TP) + " touches the " + short() + ".\n");
        
    if (!lit) {
        change_prop(OBJ_I_LIGHT, 1);
        ETO->update_light(1);
        tell_room(ETO, "The " + short() + " becomes brighter.\n");
        lit = 1;
    }
    
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_enter, "enter");
    add_action(do_touch, "touch");
}
