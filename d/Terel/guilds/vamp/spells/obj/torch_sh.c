
#include "../../guild.h"

inherit "/std/shadow";

object Flicker_ob;


public void set_flicker_object(object obj)
{
    Flicker_ob=obj;
}

public object query_flicker_object()
{
    return Flicker_ob;
}



public string
query_light_fail()
{
    
    if (!Flicker_ob)
    {
        set_alarm(0.0,0.0,remove_shadow);
        return QSW->query_light_fail();
    }

    if (!ENV(Flicker_ob) || !ENV(ENV(Flicker_ob)))
    {
        set_alarm(0.0,0.0,remove_shadow);
        return QSW->query_light_fail();
    }

    object test_env=ENV(ENV(Flicker_ob));
    
    if (ENV(QSW)==test_env)
    {
        return "Strong winds keep the "+QSW->short()+" from being "+
        "relit.\n";
    }

    if (ENV(QSW) && ENV(ENV(QSW))==test_env)
    {
        return "Strong winds keep the "+QSW->short()+" from being "+
        "relit.\n";
    }

    set_alarm(0.0,0.0,remove_shadow);
    return QSW->query_light_fail();

}


public mixed
command_light()
{

    string result=query_light_fail();
    
    if (result && stringp(result))
    {
        return result;
    }
    return QSW->command_light();
}