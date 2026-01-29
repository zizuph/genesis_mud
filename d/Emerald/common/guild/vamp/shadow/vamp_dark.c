#include "/d/Emerald/sys/domain.h"
#include "../voptions.h"
#include "../guild.h"
 
#include <stdproperties.h>
 
public void check_vamp_dark();
 
int em_dark_lvl = 0;
int em_dark_on = 0;
 
public void
add_free_dvis(object env)
{
    if (em_dark_lvl && !query_vamp_option(VOPT_SUPPRESS_DARK))
    {
        env->add_prop(ROOM_I_FREE_VAMP_DVIS, env->query_prop(ROOM_I_FREE_VAMP_DVIS) + em_dark_lvl);
    }
}
 
public void
vamp_dark_enter_env(object env, object from)
{
    check_vamp_dark();
    add_free_dvis(env);
}
 
public void
remove_free_dvis(object env)
{
    if (em_dark_lvl && !query_vamp_option(VOPT_SUPPRESS_DARK))
    {
        env->add_prop(ROOM_I_FREE_VAMP_DVIS, env->query_prop(ROOM_I_FREE_VAMP_DVIS) - em_dark_lvl);
    }
}
 
public void
vamp_dark_leave_env(object from, object to)
{
    remove_free_dvis(from);
}
 
public void
apply_em_dark(int dark)
{
    if (dark < 0)
    {
        SW->catch_tell("");
    }

    SW->add_prop(CONT_I_LIGHT, SW->query_prop(CONT_I_LIGHT) + dark);
}

public void
check_vamp_dark()
{
    string domain;
 
    object env = environment(SW);
 
    if (this_player()->query_wiz_level())
    {
        return;
    }

    domain = env->query_domain();
 
    if (domain == DOMAIN_NAME)
    {
        if (query_vamp_option(VOPT_SUPPRESS_DARK))
        {
            if (em_dark_on)
            {
                if (em_dark_lvl)
                {
                    SW->add_prop(CONT_I_LIGHT, SW->query_prop(CONT_I_LIGHT) + em_dark_lvl);
 
                    modify_thirst_rate(-50);
                    em_dark_lvl = 0;
                 }
            }
            else
            {
                modify_thirst_rate(-50);
                em_dark_lvl = 0;
            }
        }
        else
        {
            if (em_dark_on)
            {
                if (!em_dark_lvl)
                {
                    modify_thirst_rate(50);
                    em_dark_lvl = 1 + query_vamp_stat() / 60;
                    SW->add_prop(CONT_I_LIGHT, SW->query_prop(CONT_I_LIGHT) - em_dark_lvl);
                }
            }
            else
            {
                em_dark_lvl = 1 + query_vamp_stat() / 60;
                set_alarm(0.0, 0.0, &apply_em_dark(-em_dark_lvl));
            }
        }

        SW->add_subloc(EM_DARKNESS_SUBLOC, this_object());
 
        em_dark_on = 1;
    }
    else
    {
        if (query_vamp_option(VOPT_SUPPRESS_DARK))
        {
            if (em_dark_on)
            {
                if (!em_dark_lvl)
                {
                    modify_thirst_rate(50);
                }
            }
        }
        else
        {
            if (em_dark_on)
            {
                if (em_dark_lvl)
                {
                    set_alarm(0.0, 0.0, &apply_em_dark(em_dark_lvl));
                    em_dark_lvl = 0;
                }
            }
        }
 
        SW->remove_subloc(EM_DARKNESS_SUBLOC);

        em_dark_on = 0;
    }
}
 
public void
vamp_suppress_dark(int on)
{
    if (!on && em_dark_lvl)
    {
        remove_free_dvis(environment(shadow_who));
    }
    else if (on && em_dark_lvl)
    {
        add_free_dvis(environment(shadow_who));
    }
 
    check_vamp_dark();
}

public string
show_darkness_subloc(object carrier, object for_whom)
{
    if (carrier != for_whom)
    {
        return "";
    }

    if (em_dark_on && em_dark_lvl && carrier->query_prop(CONT_I_LIGHT) < 0)
    {
        return "An aureole of darkness emanates from you.\n";
    }
}
