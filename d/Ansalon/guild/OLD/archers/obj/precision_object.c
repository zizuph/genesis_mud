
/* This is the code for a precision object for the Elven Archers.
 *
 * 25.11.2003
 * Blizzard
 */
 
inherit "/std/object";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"
#include "../guild.h"

object                   archer;
static private int       gTohit_mod, gPenet_mod, gTime_mod, alarm_id;

public int
query_precision_tohit_mod()
{
    return gTohit_mod;
}

public int
query_precision_penet_mod()
{
    return gPenet_mod;
}

public int
query_precision_time_mod()
{
    return gTime_mod;
}

create_object()
{
    seteuid(getuid());
    
    set_name("_archer_precision_object_");
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_VALUE, 0);
                    
    set_no_show();                        
}

public void
remove_precision(object archer)
{
    if ( !archer->query_attack() )
        archer->catch_msg("You blink and relax, as your target is gone.\n");
    else
        archer->catch_msg("You blink and stop focusing on your target " +
            "so deeply.\n");
        
    remove_object();
}

public void
do_improve_aim(object archer)
{
    int   precision_skill;
    
    precision_skill = archer->query_skill(SS_IMPROVED_AIM);
    
    gTohit_mod      = 5 + (precision_skill / 10);  
    gPenet_mod      = precision_skill / 7;        /* Max 14% extra damage */
    gTime_mod       = MIN(gTohit_mod, 10);       
    
    archer->catch_msg("Your eyes narrow as you focus them on your target.\n");
    archer->add_mana(-25);
    alarm_id = set_alarm(25.0, 0.0, &remove_precision(archer));
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    
    if ( !objectp(to) )
    {
        remove_object();
        return;
    }
    
    if ( !living(to) )
    {
        remove_object();
        return;        
    }

    archer = to;
    do_improve_aim(archer);
}
 