/*
 * master_key.c
 * The master key to open every lock on Genesis.
 * Written by Trenix@Genesis, 7-17-93
 *
 */

inherit "/std/key";

#include "/secure/std.h"
#include <stdproperties.h>

create_key()
{
    set_name( "key" );
    set_pname( "keys" );
    add_adj( "master" );
    set_long("This is the master key. It will open any and every lock.\n");
    set_key(0);
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_I_VALUE,0);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_M_NO_BUY,1);
    add_prop(OBJ_I_NO_STEAL,1);
    set_lock();
}

string query_auto_load()
{
    return explode(file_name(this_object()),"#")[0]+":";
}

mixed query_key()
{
    mixed *data, key;
    object obj, wizard;
    int fail;

    obj = previous_object();
    data = SECURITY->do_debug("get_variables",obj);
    key = 0;
    fail = 0;
    if ( data["key"] )
    {
        key = data["key"];
    }
    wizard = this_interactive();
    if ( !wizard )
    {
        fail = 1;
    }
    if ( !fail )
    {
        if ( !wizard->query_wiz_level() )
        {
            fail = 1;
        }
    }
    if ( fail )
    {
        if ( key != 0 )
        {
            key = 0;
        }
        else
        {
            key = 1;
        }
    }
    return key;
}

string stat_object()
{
    string str;

    str = ::stat_object();
    str += "\n";
    str += "Wizinfo: This is the master key for Genesis. It opens every lock in the game.\n"+
           "         It will fetch the variable expected by the door and return it\n"+
           "         properly only if the user of the object is a wizard, otherwise it\n"+
           "         returns the wrong value on purpose resulting in failure.\n"+
           "         The master key (tm) was written by Trenix@Genesis on July 17, 1993.\n";
    return str;
}
