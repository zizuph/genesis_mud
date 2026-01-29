
/* This is the code for the fast draw object for the Elven Archers.
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

#define  DEBUG(x) (find_player("blizzard")->catch_msg("DEBUG: " + x + "\n"))

object                   archer;
static private int       gTohit_mod, gPenet_mod, gTime_mod, alarm_id,
                         gSpeed_Bonus, gCheck_id;

public int
query_fastdraw_tohit_mod()
{
    return gTohit_mod;
}

public int
query_fastdraw_speed_mod()
{
    return gSpeed_Bonus;
}

public int
query_fastdraw_penet_mod()
{
    return gPenet_mod;
}

public int
query_fastdraw_time_mod()
{
    return gTime_mod;
}

create_object()
{
    seteuid(getuid());
    
    set_name("_archer_fast_draw_object_");
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_VALUE, 0);
                    
    set_no_show();                        
}

public void
remove_fast_draw(object archer)
{
    archer->catch_msg("Your calm down and your moves return to normal.\n");

    archer->add_prop(LIVE_I_QUICKNESS, 
        archer->query_prop(LIVE_I_QUICKNESS) - gSpeed_Bonus);
    archer->query_combat_object()->cb_update_speed();

    DEBUG("My fatigue: " + archer->query_fatigue() );
    DEBUG("My speed: " + archer->query_prop(LIVE_I_QUICKNESS) );
    
    remove_alarm(gCheck_id);
    gCheck_id = 0;
        
    remove_object();
}

public void
update_archer_fatigue(object archer)
{
    if ( !gCheck_id )
    {
//        remove_alarm(gCheck_id);
        return;
    }
    
    if ( archer->query_fatigue() < 5 )
    {
        remove_fast_draw(archer);
        return;
    }
    
    DEBUG("Fatigue: " + archer->query_fatigue() );
            
    if ( archer->query_attack() )
    {
 /*
        if ( !random(4) )
            archer->catch_msg("You move on instinct...\n");
  */
        archer->add_fatigue(-4);
    }
 /*
    else if ( !random(4) )
        archer->catch_msg("Your moves slow down a bit...\n");
  */ 
}

public void
do_fast_draw(object archer)
{
    int   fast_draw_skill, ss_con;
    
    fast_draw_skill = archer->query_skill(SS_FAST_DRAW);
    ss_con          = archer->query_stat(SS_CON);
 
 /* These are negative bonuses */
    gTohit_mod      = 5 + (fast_draw_skill / 10);  
    gPenet_mod      = fast_draw_skill / 7;        /* Max 14% damage penalty */
    gTime_mod       = MIN(gTohit_mod, 10);   /* Offensive special will reset
                                              * by max 10 sec. faster. 
                                              */
    
    archer->catch_msg("Your take a deep breath and the world " +
        "seems to slow down as your moves speed up...\n");
    tell_room(E(archer), QCTNAME(archer) + "'s moves begin to blur before " +
        "your eyes...\n", archer);
    
    gSpeed_Bonus = 40 + (fast_draw_skill / 3);
    DEBUG("Speed Bonus: " + gSpeed_Bonus);
    
    archer->add_prop(LIVE_I_QUICKNESS, 
        archer->query_prop(LIVE_I_QUICKNESS) + gSpeed_Bonus);
    archer->query_combat_object()->cb_update_speed();
    DEBUG("My speed: " + archer->query_prop(LIVE_I_QUICKNESS) );    

    archer->add_fatigue(-(ss_con / 16));
    
    gCheck_id  = set_alarm(4.0, 4.0, &update_archer_fatigue(archer));
    
    alarm_id = set_alarm(25.0, 0.0, &remove_fast_draw(archer));

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
    do_fast_draw(archer);
}
 