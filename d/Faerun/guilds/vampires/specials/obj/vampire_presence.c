#pragma strict_types

inherit "/std/creature.c";
inherit "/std/combat/unarmed.c";
inherit "/std/act/action.c";

#include "../../guild.h"
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>





#define TEMP_ROOM       (VAMPIRES_GUILD_DIR  +"rooms/temp_room")

#define HIS(x)          (x)->query_possessive()
#define HIM(x)          (x)->query_objective()
#define MAX_FAIL        12
#define ENV             environment
#define TO              this_object()
#define TP              this_player() 
#define CAP             capitalize   

#define ROOM_I_KEBAB "_i_ate_kebab"


       void    watch_target();
public void    remove_link();
public int     query_time_left();

static object  gVampire,
               gTarget,
               gParalyze;
               
static int     gDuration,
               gFail,
               gWatch,
               gExploded,
               gRemoved;


public void
create_creature()
{
    set_name(({"", }));
    set_pname(({"", }));
    set_race_name("");
    set_adj(({"", "", }));
    set_short("");
    set_pshort("");
    set_long("");
    set_alignment(0);

    set_stats(({ 10, 10, 10, 10, 10, 10 }));

    set_skill(SS_AWARENESS, 80);

    add_prop(CONT_I_WEIGHT, 1);
    add_prop(CONT_I_VOLUME, 1);
    add_prop(CONT_I_MAX_WEIGHT, 1);
    add_prop(CONT_I_MAX_VOLUME, 1);
    add_prop(OBJ_M_NO_ATTACK, "kill what?\n");    
    add_prop(LIVE_I_NO_ACCEPT_GIVE, 1);
    add_prop(LIVE_I_NO_GENDER_DESC, 1);
    add_prop(LIVE_I_NO_FOOTPRINTS,  1);
    add_prop(LIVE_I_NO_CORPSE,      1);
    add_prop(LIVE_I_NO_BODY,        1);
    add_prop(LIVE_I_NEVERKNOWN,     1);
    add_prop(LIVE_I_SEE_DARK, 100);    
    add_prop(OBJ_I_INVIS, 100);
     
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, "\n");
    add_prop(LIVE_I_NO_CORPSE,   1);


    set_no_show();
    set_no_show_composite(1);
}


public string
long_desc()
{
    object  tp = TP;
    string  msg = "\n";

      return msg;
    
}


public void
remove_object()
{
    if (!gRemoved)
    {
        remove_link();
        return;
    }

    ::remove_object();
}


public void
remove_link()
{
    string  vampire_msg = "";

    if (gRemoved++)
        return;

    
    if (previous_object() != gParalyze)
        gParalyze->stop_paralyze();
    
    gVampire->remove_stun();

    if (!gExploded)
    {
        gExploded = 1;
        
        if (!query_ghost())
        {
            
            vampire_msg = " and the link returns to the negative material plane whence "
              + "you summoned it";
        }
        
        if (objectp(gVampire))
        {
            gVampire->catch_msg("Your awareness enters your "
              + "body again"+vampire_msg+".\n");
            
              
            gVampire = 0;
        }
    }

    remove_object();
}


void
set_vampire(object ob)
{
    if (objectp(ob))
        gVampire = ob;
}


void
set_paralyze(object ob)
{
    if (objectp(ob))
        gParalyze = ob;
}


void
set_target(object ob)
{
    if (objectp(ob) && living(ob))
        gTarget = ob;
}


void
set_duration(int value)
{
    gDuration = set_alarm(itof(value), 0.0, remove_link);
}


void
start_watch()
{
    if (!objectp(gVampire) || !objectp(gTarget) ||
        !gDuration || !sizeof(get_alarm(gDuration)))
        remove_link();
        
    gVampire->catch_msg("You etablish a link to your child.\n");
    
    move_living("M", TEMP_ROOM, 0, 0);

    gWatch = set_alarm(0.5, 0.5, watch_target);
}


void
watch_target()
{
    object  target_env;
    string  txt;

    if (!objectp(gVampire))
    {
        set_alarm(0.0, 0.0, remove_link);
        return;
    }

    if (!objectp(gTarget) || !objectp(target_env = ENV(gTarget)))
    {
        gVampire->catch_msg("The link to your child fails for some unknown reason.\n");
          
        set_alarm(0.0, 0.0, remove_link);
        
        return;
    }

    if (MASTER_OB(ENV(TO)) == TEMP_ROOM)
    {
        txt = "You are trying to connect to your child ...\n";

        if (!target_env->query_prop(ROOM_I_KEBAB) && interactive(gTarget))
        {
            txt += "You feel the connection to your child is forming.\n";
              
            gVampire->catch_msg(txt, gVampire);
                
            move_living("M", target_env, 1, 0);           
        }
        else
            gVampire->catch_msg(txt, gVampire);
        return;
    }
    
    if (ENV(TO) != target_env)
    {
        if (!gFail)
            txt = "Your connection to your child is slightly unstable.\n";
        else
            txt = "";
        
        if (target_env->query_prop(ROOM_I_KEBAB) || !interactive(gTarget))
        {
            if (gFail++ > MAX_FAIL)
            {
                txt += "The link to your child fails for some unknown reason.\n";
                
                set_alarm(0.0, 0.0, remove_link);
            }
            else
            {
                txt += "The connection to your child is temporary lost, but "
                +"you focus on establishing it again ...\n";
            }
            gVampire->catch_msg(txt, gVampire);
        }
        else
        {
            gVampire->catch_msg(txt, gVampire);
            
            move_living("M", target_env, 1, 0);
           
            gFail = 0;
        }
        
        return;
    }
}


void
catch_msg(mixed str, object from_player)
{
    ::catch_msg(str, from_player);

    if ((from_player == TO) || !objectp(gVampire))
        return;
    
    gVampire->catch_msg("#link#: \n");
    gVampire->catch_msg(str, from_player);
}


void
enter_env(object to, object from)
{
    string  message = "";
    object *inv,
           *ld,
            tp;

    ::enter_env(to, from);

    if (!objectp(to) || !objectp(from))
        return;

    if (!objectp(gVampire))
    {
        remove_link();
        return;
    }

    if (present(gTarget, to))
    {
        message += "#link#: \n"
          + to->long();
          
        inv = FILTER_CAN_SEE(all_inventory(to), gVampire);
        
        inv -= ({ TO });
        
        tp = this_player();
        
        set_this_player(gVampire);
        
        if (sizeof(ld = FILTER_DEAD(inv)))
            message += CAP(COMPOSITE_DEAD(ld)) + ".\n";
        
        if (sizeof(ld = FILTER_LIVE(inv)))
            message += capitalize(COMPOSITE_LIVE(ld)) + ".\n";
        
        set_this_player(tp);
        
        gVampire->catch_msg(message, gVampire);
    }
}


public int
query_time_left()
{
    mixed   info;
    if (pointerp(info = get_alarm(gDuration)))
        return ftoi(info[2]);
    
    return -1;
}


public int
query_see_special_msg()
{
    return 1;
}