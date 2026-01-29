inherit "/std/object";

#include "/d/Kalad/defs.h"

#define KALAD_GLOWSHROON    "_kalad_glowshroon"

nomask 
void create_object()
{
    set_name("glowob");
    add_prop(OBJ_I_VOLUME,0);
    add_prop(OBJ_I_WEIGHT,0);
    add_prop(OBJ_M_NO_DROP,1);
    add_prop(OBJ_M_NO_GIVE,1);
    add_prop(OBJ_M_NO_SELL,1);
    add_prop(OBJ_I_INVIS,1);
    set_no_show();
}

void 
enter_env(object to, object from)
{
    ::enter_env(to,from);

    if(living(to)) 
    {
        to->add_subloc(KALAD_GLOWSHROON,TO);
        to->add_prop(CONT_I_LIGHT,to->query_prop(CONT_I_LIGHT) + 1);
    }
}

void 
leave_env(object from, object to)
{
    ::leave_env(from, to);
    if(living(from))
    {
        from->add_prop(CONT_I_LIGHT,from->query_prop(CONT_I_LIGHT) - 1);
        from->remove_subloc(KALAD_GLOWSHROON);
    }
}

string
show_subloc(string subloc, object on, object for_ob)
{
    if(on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";
    if(subloc != KALAD_GLOWSHROON)
        return "";

    if(on == for_ob)
        return "Your skin is glowing with a bright white light!\n";
    return C(HIS(on))+" skin is glowing with a bright white light!\n";
}

void
set_remove_time(int i)
{
    set_alarm(itof(i),0.0,"remove_object");
}

void
remove_object()
{
    tell_object(E(TO),"Your skin stops glowing.\n");
    tell_room(E(E(TO)),QCTNAME(E(TO))+"'s skin stops glowing.\n",E(TO));
    ::remove_object();
}

