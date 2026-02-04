/*
 * Modifications:  Lilith April 2009
 *   removed CON poison portion of sunlight penalty, left hp ding and msgs.
 */
#include "../defs.h";

#include <stdproperties.h>

static int Con_drained;

static int Last_notify;

static void undo_burn(int light)
{
    if (Last_notify>0 && Con_drained>light)
    {
        if (light>0)
        {
            QSW->catch_msg("You find the sun burning less than before.\n"); 
        }
        else
        {
            QSW->catch_msg("You find temporary refuge from the burning "+
               "sun.\n");
        }
    }
    Last_notify=0;
    if (Con_drained>light)
    {
    //    QSW->set_stat_extra(SS_CON,QSW->query_stat_extra(SS_CON)+1);
        Con_drained--;
    }
}

public int query_sunlight_level(object room)
{
    if (room->query_prop(ROOM_I_INSIDE))
    {
        return 0;
    }
    
    int sun=room->query_prop(ROOM_I_SUNLIGHT);
    if (!sun)
    {
        return 0;
    }

    int darkness=QSW->query_prop(OBJ_I_LIGHT);
    if (darkness<0)
    {
        darkness*=5;
    }
    else
        darkness=0;
    int light=min(
        room->query_prop(ROOM_I_LIGHT),
        room->query_prop(OBJ_I_LIGHT));
    
    if (light<=-darkness)
    {
        return 0;
    }
    
    sun+=sun*(darkness)/light;

    sun-=QSW->query_vamp_stat()/10;
    
    sun=max(0,sun);
   
    return sun;
            
}

public void check_sunlight()
{
    if (!QSW || !environment(QSW))
    {
        return;
    }    
    
    int sun=query_sunlight_level(environment(QSW));
            
    int new_penalty=2*sun*(QSW->query_stat(SS_CON)+Con_drained)/100;
            
    if (new_penalty<=Con_drained)
    {
        undo_burn(new_penalty);
        return;
    }
    
    if (Last_notify % 5 == 0 || !random(5))
    {
        QSW->catch_msg("Your skin burns under the heat of the sun.\n");
    }
    Last_notify++;
    
    if (Con_drained<new_penalty)
    {
        //QSW->set_stat_extra(SS_CON,QSW->query_stat_extra(SS_CON)-1);
        Con_drained++;
    }
    QSW->heal_hp(-sun/5);
    
    if (QSW->query_hp()<=0)
    {
        QSW->catch_msg("The intensity of the sun consumes your body.\n");
        QSW->do_die(environment(QSW));
    }
    
}

