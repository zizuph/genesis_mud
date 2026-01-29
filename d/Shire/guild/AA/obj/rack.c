inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <filter_funs.h>

int Allow_misc=0;
int Allow_armour=0;
int Allow_weapon=0;
int Allow_glowing=0;
int Allow_nonglowing=0;




/*
 * Function name: prevent_enter
 * Description:   limited items allowed
 */
public int
prevent_enter(object ob)
{
    if (!Allow_glowing && (ob->check_recoverable() ||
        strlen(ob->query_auto_load())))
    {
        return 5;
    }

    if (!Allow_nonglowing && !ob->check_recoverable() &&
        !strlen(ob->query_auto_load()))
    {
        return 5;
    }
    
    if (!Allow_armour && ob->check_armour())
    {
        return 5;
    }

    if (!Allow_weapon && ob->check_weapon())
    {
        return 5;
    }

    if (!Allow_misc && !ob->check_weapon() && !ob->check_armour())
    {
        return 5;
    }
    
    return 0;
}        
  
public void set_allow_weapon(int i)
{
    Allow_weapon=i;
}

public void set_allow_armour(int i)
{
    Allow_armour=i;
}

public void set_allow_misc(int i)
{
    Allow_misc=i;
}

public void set_allow_glowing(int i)
{
    Allow_glowing=i;
}

public void set_allow_nonglowing(int i)
{
    Allow_nonglowing=i;
}


nomask void
create_container()
{
    if(!IS_CLONE)
        return;

    add_prop(OBJ_M_NO_GET, "You are unable to take that.\n");

    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    add_prop(CONT_I_MAX_WEIGHT,99999999);
    add_prop(CONT_I_MAX_VOLUME,99999999);

    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_ATTACH, 1);
    add_prop(CONT_I_RIGID,  1);

    //set_no_show_composite(1);

}

