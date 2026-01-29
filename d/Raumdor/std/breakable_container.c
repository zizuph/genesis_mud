#include "defs.h"
inherit "/std/container";

varargs public string
query_the_name(object pobj)
{
    string result = ::vbfc_short(pobj);
    if (result == "something")
        return "something";
    return "the " + result;
}

varargs public string
query_The_name(object pobj)
{
    return capitalize(query_the_name(pobj));
}


public void
break_container()
{
    object dest, tell, exclude,
            e = E(TO),
            *inv = AINV(TO);
    string items = COMPOSITE_DEAD(inv),
           beginning = QCTNAME(TO),
           end = " breaks",
           unseen = "You hear a clamour, like something breaking apart";

    if (sizeof(inv))
        end += ", spilling " + QCOMPDEAD;
    // Someone is carrying it
    if (living(e))
    {
        dest = E(e);
        beginning += " carried by " + QTNAME(e);
        tell = dest;
        exclude = e;
        e->catch_msg(QCTNAME(TO) + end + "!\n");
    }
    // It's on the floor
    else if (e->query_prop(ROOM_I_IS))
    {
        dest = e;
        tell = dest;
    }
    // It's in an object. We assume that object is in a room.
    else
    {
        tell = E(e);
        if (e->query_prop(CONT_I_ATTACH))
        {
            dest = E(e);
            beginning += " on the " + QSHORT(e);
        }
        else
        {
            dest = e;
            if (e->query_prop(CONT_I_TRANSP))
            {
                beginning += " in the " + QSHORT(e);
                end += " inside";
            }
            else
            {
                beginning = "You hear the sound of something break inside " +
                            "the " + QSHORT(e);
                end = "";
            }
        }
    }
    if (tell == dest)
    {
        int type = dest->query_prop(ROOM_I_TYPE);
        if (type == ROOM_IN_WATER)
        {
            if (sizeof(inv))
            {
                end += " and making a splash";
                unseen += ", and then a splash";
            }
        }
        else if (type == ROOM_UNDER_WATER)
            unseen = "";
        else
        {
            if (sizeof(inv))
                end += " all over";
        }
    }

    TELL_CAN_SEE_OTHER(tell, beginning + end + "!\n", exclude);
    if (strlen(unseen))
        TELL_CANNOT_SEE_OTHER(tell, unseen + "!\n", exclude);
    set_short("broken " + short());
    add_prop(OBJ_I_BROKEN, 1);
    add_prop(CONT_M_NO_INS, "It's broken.\n");
    foreach (object obj: inv)
        obj->move(dest);
}


public int
result_break_container(int strength)
{
    // The higher the strength, the more full it has to be to break
    // e.g. strength = 10 means it risks breaking beginning at 90%
    // strength = 2 means it risks breaking at 50%
    if (random(query_prop(CONT_I_MAX_VOLUME) / strength) > volume_left() ||
      random(query_prop(CONT_I_MAX_WEIGHT) / strength) > query_prop(CONT_I_MAX_WEIGHT) - query_prop(OBJ_I_WEIGHT))
        return 1;
    return 0;
}

public int
try_break_container(int strength)
{
    if (!result_break_container(strength))
        return 0;
    break_container();
    return 1;
}

