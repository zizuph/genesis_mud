/*  diploma.c */
/*  janus 920831 */

#include "/d/Terel/include/Terel.h"

inherit  STDOBJECT;
#include <stdproperties.h>
#include "/d/Terel/common/terel_std_rec.h"

object owner;

public void
create_object()
{
    set_name("diploma");
    set_short("diploma");
    set_adj("gardeners");
    set_long("This is a fancy gardeners diploma. It states that you are " +
        "a certified gardener. As a certified gardener you are charged to " +
		"take part in keeping the Enchanted Garden beautiful.\n");
    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,1);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_NO_GET, 0);
    add_prop(OBJ_I_NO_GIVE, 1);
}

public void
destruct_me(object to, object from)
{
    object room;
    object *enviros = all_environment(TO);
    int print_msg;
    if (living(ENV(TO)) && ENV(TO) != owner)
    {
        ENV(TO)->catch_vbfc("The " + short() + " was awarded to " +
            owner->query_name() + ", not to you.\nA strong gust of wind " +
            "blows the " + short() + " out of your hands, beyond " +
            "your reach, and out of sight.\n");
        remove_object();
        return;
    }
    foreach (object enviro : enviros)
    {
        if(enviro == owner) return;
    }
    foreach (object enviro : enviros)
    {
        foreach (object obj : all_inventory(enviro))
        {
            if (living(obj))
            {
                room = enviro;
                print_msg = 1;
                break;
            }
        }
        if (print_msg) break;
    }
    if (print_msg)
    {
        if (room == to)
        {
            tell_room(room, "The " + short() +
                " blows away with the wind.\n");
        }
        else
        {
            tell_room(room, "You hear a muffled pop from inside the " +
                ENV(TO)->query_name() + " and a thin line of smoke trails " +
                "out of it.\n");
        }
    }
    remove_object();
    return;
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    if (!owner) owner = to;
    TO->set_long("This is a fancy gardeners diploma, issued personally to " +
        owner->query_name() + ". It reads:\n" + break_string("You are " +
        "a certified gardener. As a certified gardener you are charged to " +
		"take part in maintaining the beauty of the Enchanted Garden.",
        60, 5) + "\n");
    if (to != owner) set_alarm(0.5, 0.0, &destruct_me(to, from));
}


