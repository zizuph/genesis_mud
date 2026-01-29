/*
 * modified by: Lilith, 23 Oct 2008
 *   -- removed the attack_delay per AoB
 *
 * Removed alarm to start bleeding from bleeds 
 * and called it directedly.
 * -- Lilith,  March 2009
 *
 * Borrowed for Vampires of Faerun, 2021
 * Nerull
 *
 */
inherit "/std/shadow";

#include <tasks.h>     /* For difficulty and stat defines */
#include <ss_types.h>  /* For skill defines */
#include <stdproperties.h> /* For standard properties */
#include <macros.h> /* For macros */
#include <filter_funs.h> /* For easy filters */
#include <composite.h> /* Composie words */

#include "/std/combat/combat.h";

#include "../guild.h";

#define BLEEDING_START_TIME 2.5

#define BLEEDING_END_TIME 300.0

#define HEAL_WOUND_HP   200

#define VAMPIRE_BLEED "vampire_bleed"

private mapping Start_alarms=([ ]);
private mapping End_alarms=([ ]);
private object Target_killer=0;


public int query_bleeding()
{
    return 1;
}


public int query_active_bleeding()
{
    return m_sizeof(End_alarms);
}


public object set_killed_by_bleed(object killer)
{
    Target_killer=killer;
}


public int query_hitloc_bleeding(int hitloc_id)
{
    if (End_alarms[hitloc_id])
    {
        return 1;
    }
    
}


public string query_name_for_hitloc(int hitloc_id)
{
    object co=this_object()->query_combat_object();

    
    mixed hitloc=co->query_hitloc(hitloc_id);

    if (!pointerp(hitloc))
    {
        return 0;
    }
    
    string hdesc=hitloc[HIT_DESC];
    
    switch (hdesc)
    {
        case "head":
            hdesc="throat";
            break;
        case "left arm":
            hdesc="left wrist";
            break;
        case "right arm":
            hdesc="right wrist";
            break;
        case "legs":
            hdesc="thigh";
            break;
    }

    return hdesc;    
}


public int query_id_for_hitloc_name(string name)
{
    object co=this_object()->query_combat_object();

    
    foreach (int id : co->query_hitloc_id())
    {
        mixed hitloc=co->query_hitloc(id);

        if (!pointerp(hitloc))
        {
            return 0;
        }
    
        string hdesc=hitloc[HIT_DESC];
    
        if (hdesc==name)
        {
            return id;
        }
    }
    return -1;
}


public void check_remove()
{
    if (!m_sizeof(Start_alarms) && !m_sizeof(End_alarms))
    {
        QSW->remove_subloc(VAMPIRE_BLEED);
        remove_shadow();
    }
}


public void end_bleeding(int hitloc_id)
{
    m_delkey(End_alarms,hitloc_id);
    
    string hdesc=query_name_for_hitloc(hitloc_id);
    
    if (hdesc)
    {
        this_object()->catch_msg("The blood trickling down your "+
        hdesc+" dries up.\n");
    }
    
    check_remove();   
}


public void start_bleeding(int hitloc_id)
{
    m_delkey(Start_alarms,hitloc_id);
    
    string hdesc=query_name_for_hitloc(hitloc_id);
    
    if (hdesc)
    {
        this_object()->catch_msg("You feel a trickle of blood down your "+
        hdesc+".\n");
        
        this_object()->tell_watcher(QCTNAME(this_object()) + " is bleeding, soaking "
        +"the ground!\n");           
    }
    
    End_alarms[hitloc_id]=set_alarm(BLEEDING_END_TIME,0.0,
        &end_bleeding(hitloc_id));
}


public void bleed_location(int hitloc_id)
{
    if (!m_sizeof(Start_alarms) && !m_sizeof(End_alarms))
    {
        QSW->add_subloc(VAMPIRE_BLEED,this_object());
    }
    int i=End_alarms[hitloc_id];
    if (i)
    {
        remove_alarm(i);
        End_alarms[hitloc_id]=set_alarm(BLEEDING_END_TIME,0.0,
            &end_bleeding(hitloc_id));
        return;
    }
    if (Start_alarms[hitloc_id])
    {
        return;
    }
    start_bleeding(hitloc_id);
}


public string show_subloc(string subloc, object on, object for_obj)
{
    if (subloc!=VAMPIRE_BLEED)
    {
        return QSW->show_subloc(subloc,on,for_obj);
    }
    
    string subloc;
    
    if (QSW->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
        return "";
    }

    if (m_sizeof(End_alarms)==0)
    {
        return "";
    }
    
    string * names=map(m_indexes(End_alarms), query_name_for_hitloc);
    
    names = names - ({ });
    
    subloc=
       (on == for_obj ? "You have " : 
           capitalize(QSW->query_pronoun()) + " has " ) +
       "a trail of blood on " +
       (on == for_obj ? "your" : QSW->query_possessive()) +
       " " + COMPOSITE_WORDS(names) + ".\n";
    return subloc;
}


/*public object make_corpse()
{
    if (!Target_killer)
    {
        return QSW->make_corpse();
    }
    
    object corpse=QSW->make_corpse();
    
    if (!objectp(corpse))
    {
        corpse = clone_object("/std/corpse");
        corpse->set_name(this_object()->query_name());
        corpse->change_prop(CONT_I_WEIGHT, 
                this_object()->query_prop(CONT_I_WEIGHT));
        corpse->change_prop(CONT_I_VOLUME, 
                this_object()->query_prop(CONT_I_VOLUME));
        corpse->add_prop(CORPSE_S_RACE, this_object()->query_race_name());
        corpse->add_prop(CONT_I_TRANSP, 1);
        corpse->change_prop(CONT_I_MAX_WEIGHT,
                            this_object()->query_prop(CONT_I_MAX_WEIGHT));
        corpse->change_prop(CONT_I_MAX_VOLUME,
                            this_object()->query_prop(CONT_I_MAX_VOLUME));
        corpse->set_leftover_list(this_object()->query_leftover());
    
    }

    //This corpse is about to die, so we try to pick it up
    this_object()->remove_prop(OBJ_I_NO_GET);

    object shadow = clone_object(VAMPIRES_GUILD_DIR+"shadows/corpse_shadow");
    shadow->shadow_me(corpse);
    
    if (!this_object()->move(Target_killer))
    {
        shadow->set_killer(Target_killer);
        shadow->initiate_drop_corpse();
    }
    return corpse;
}*/


public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    object env=environment(QSW);
    
    int result=QSW->move_living(how,to_dest,dont_follow,no_glance);
    
    if (!result && query_active_bleeding())
    {
        env->add_prop(ROOM_S_BLOOD_DIR,
            ({ how, QSW->query_race_name(), time() }) );
    }
    
    return result;
}


public void heal_wound(int hitloc_id)
{
    if (End_alarms[hitloc_id])
    {
        remove_alarm(End_alarms[hitloc_id]);
        end_bleeding(hitloc_id);
    }
    remove_alarm(Start_alarms[hitloc_id]);
    m_delkey(Start_alarms,hitloc_id);
    check_remove();   
}


public int heal_hp(int hp)
{
    QSW->heal_hp(hp);
    
    if (hp>HEAL_WOUND_HP && m_sizeof(End_alarms))
    {
        int hitloc=one_of_list(m_indexes(End_alarms));
        heal_wound(hitloc);
        return hp;
    }
    if (hp>HEAL_WOUND_HP && m_sizeof(Start_alarms))
    {
        int hitloc=one_of_list(m_indexes(Start_alarms));
        heal_wound(hitloc);
        return hp;
    }
}



