/* 
 * Stun Object
 * Goldberry, February 2002
 */


inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>

#include "/d/Terel/include/Terel.h";


public void   set_duration(int t);
public void   set_from(string str);

string from_ob = "attack";

public void
create_object()
{
    set_name("stun_ob");
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    set_no_show();
}


public void
self_destruction()
{
    tell_room(ETO, "The stunning effect of the "+ from_ob + " seems to "+
     "have worn off.\n");
    ETO->remove_stun();
    remove_object();
}

public void
set_duration(int t)
{
    ETO->add_stun();
    tell_room(ETO, "You are stunned!\n");
    set_alarm(itof(t), -1.0, self_destruction);
}

public void
set_from(string str)
{
    from_ob = str;
}
