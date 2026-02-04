/* Coded by Novo May 2008
 *
 *  Mar 2009
 *  updated by Lilith to correct resistance check from air to illusion
 *  Apr 2009
 *  updated by Petros to do proper resistance checking, and fixed the
 *  validator. It wasn't working at all, causing it to always succeed.
 */

#include "../guild.h"
#include <tasks.h>
#include <ss_types.h>
#include <std.h>
#include <filter_funs.h>

#define HAIR_SUBLOC                     "hairstyle"
#define EYES_SUBLOC                     "eyes"
#define INCOGNITO_SUBLOC                "_incognito"
#define SKIN_SUBLOC                     "having_skincolour_subloc"
#define SPELL                           (CORELIB_DIR + "spell")

int Incognito=0;

int Mist=0;

int Revert_alarmid=0;

mapping Known_attributes=([ ]);

mapping Chosen_attributes=([ ]);

public string query_incog_attribute(string type);
public string valid_incog_override(string incog);
public void save_disguises();
public int query_vamp_stat();

int query_incognito()
{
    return Incognito;
}
    
int set_incognito(int val)
{
    Incognito=val;
}

public string return_colour_desc()
{
    string result=
        valid_incog_override(query_incog_attribute("skin_color"));
    if (result)
    {
        return result;
    }
    result=QSW->return_colour_desc();
    if (result)
    {
        return result;
    }
    object colorob=present("colourob",QSW);
    if (colorob)
    {
        return colorob->return_colour_desc();
    }
    return 0;
}

public string query_hair_length()
{
    string result=
        valid_incog_override(query_incog_attribute("hair_length"));
    if (result)
    {
        return result;
    }
    return QSW->query_hair_length();
}

public string query_hair_style()
{
    string result=
        valid_incog_override(query_incog_attribute("hair_style"));
    if (result)
    {
        return result;
    }
    return QSW->query_hair_style();
}

public string query_hair_colour()
{
    string result=
        valid_incog_override(query_incog_attribute("hair_color"));
    if (result)
    {
        return result;
    }
    return QSW->query_hair_colour();
}

public string query_hairstyle()
{
    return query_hair_length() + ", " + 
        query_hair_colour() + " and " + 
        query_hair_style(); 
}


public string query_eyes_colour()
{
    string result=
        valid_incog_override(query_incog_attribute("eyes_color"));
    if (result)
    {
        return result;
    }
    return QSW->query_eyes_colour();
}

public string query_eyes_type()
{
    string result=
        valid_incog_override(query_incog_attribute("eyes_type"));
    if (result)
    {
        return result;
    }
    return QSW->query_eyes_type();
}

public string query_eyes()
{
    if (!strlen(query_eyes_type()) || !strlen(query_eyes_colour()))
    {
        return 0;
    }
    return query_eyes_type() + " " + query_eyes_colour();
}

public int query_eyes_number()
{
    string result=
        valid_incog_override(query_incog_attribute("eyes_number"));
    if (result)
    {
        return (result=="one" ? 1 : 2);
    }
    return QSW->query_eyes_number();

}

public string query_race_name()
{
    string result=
        valid_incog_override(query_incog_attribute("race"));
    if (result)
    {
        return result;
    }
    if (query_vamp_option(VOPT_VAMPIRE_RACE))
    {
        return "vampyr";
    }
    return QSW->query_race_name();
}

public int set_incog_attribute(string type,string value)
{
    string * known = Known_attributes[type];
    
    if (!sizeof(known))
    {
        return 0;
    }
    if (member_array(value,known)<0 && strlen(value))
    {
        return 0;
    }
    if (strlen(value))
    {
        Chosen_attributes[type]=value;
        return 1;  
    }
    else
    {
        m_delkey(Chosen_attributes,type);
    }
    return 1;
}

public string * query_known_incog_attributes(string type)
{
    return Known_attributes[type];
}

public mapping query_all_known_incog_attributes()
{
    return secure_var(Known_attributes);
}


public string query_incog_attribute(string type)
{
    return Chosen_attributes[type];
}

public int add_known_incog_attribute(string type,string value)
{
    if (!sizeof(Known_attributes[type]))
    {
        Known_attributes[type] = ({ value });
        return 1;
    }
    if (member_array(value,Known_attributes[type])>=0)
    {
        return 0;
    }
    string * known=Known_attributes[type];
    
    known = known - ({ value, Chosen_attributes[type] });
    
    known = known[-9..] + ({ value });

    if (Chosen_attributes[type])
    {
        known+=({ Chosen_attributes[type] });
    }
    
    Known_attributes[type] = known;
    
    return 1;
}

public int
query_incognito_resistance(object player, object target)
{
    // Incognito Resistance is based on the Air element and Illusion
    setuid();
    seteuid(getuid());
    return SPELL->spell_resist_illusion(player, target, SS_ELEMENT_AIR, 
                                        TASK_FORMIDABLE);
}

public string valid_incog_override(string incog)
{
    if (!Incognito)
    {
        return 0;
    }
    if (QSW->query_attack())
    {
        return 0;
    }
    
    object prev = this_player();
    if (!living(prev))
    {
        // If for whatever reason, this_player() is not valid, we then
        // return 0
        return 0;
    }
    
    if (prev == QSW)
    {        
        return incog;
    }

    int prev_count = 0;
    string prev_func;
    while (prev_func = calling_function(prev_count))
    {
        if (prev_func == "print_who")
        {
            // When someone types who, we don't want it to
            // show the incognito, nor trigger the resistance
            // checks.
            return 0;
        }
        prev_count--;
    }
    
    if (query_incognito_resistance(shadow_who, prev) > random(100))
    {
        return 0;
    }

    int difficulty = TASK_EASY;

    if (!prev->query_humanoid())
    {
        difficulty = TASK_SIMPLE;
    }

    int new_result = 
        prev->resolve_task(difficulty,
                           ({ SS_AWARENESS, TS_INT, TS_WIS }),
                           QSW,
                           ({ SS_FORM_ILLUSION, TS_INT, TS_WIS }));
        
    if (new_result > TO->query_vamp_stat() / 2)
    {
        return 0;
    }

    return incog;
}

public string show_subloc(string subloc, object on, object for_obj)
{
    if (for_obj->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
        return QSW->show_subloc(subloc,on,for_obj);
    }
    
    if (subloc==EYES_SUBLOC && strlen(query_eyes()) && query_incognito())
    { 
        int num=TO->query_eyes_number();
        
        return 
            (for_obj == on ? "You have" : capitalize(PRO(on)) + " has")+
            (num == 1 ? " one " : " ") + query_eyes() + 
            (num == 1 ? " eye" : " eyes") + ".\n";
    }
    
    if (subloc==HAIR_SUBLOC && strlen(query_hair_length()) && 
        query_incognito() && strlen(query_hair_colour()) && 
        strlen(query_hair_style()))
    {
        return 
            (for_obj == on ? "Your" : capitalize(POSS(on))) +
            " hair is " + query_hairstyle() + ".\n";
    }
    if (subloc==INCOGNITO_SUBLOC && on==for_obj && query_incognito())
    {
        return "You have masked some of your features.\n";
    }
    if (subloc==SKIN_SUBLOC)
    {
        string color=return_colour_desc();
        if (!color || !strlen(color))
        {
            switch(query_vamp_stat())
            {
                case 0..50:
                    color="marble white";
                    break;
                case 51..100:
                    color="shimmering white";
                    break;
                case 101..150:
                    color="frost white";
                    break;
                default:
                    color="white";
                    break;
            }
        }
        if (!query_incognito())
        {
            switch (thirst())
            {
                case 0..15:
                    color+=" and flushed with blood";
                    break;
                case 16..30:
                    color+=" and rosy";
                    break;
                case 31..50:
                    break;
                case 51..75:
                    color+=" and blanched";
                    break;
                default:
                    color+=" and gaunt";
                    break;
            }
        }
        return 
            (for_obj == on ? "Your" : capitalize(POSS(on))) +
            " skin is " + color + ".\n";
    }
    return QSW->show_subloc(subloc,on,for_obj);

}

public mixed query_adj(int arg)
{
    if (!query_incognito())
    {
        return QSW->query_adj(arg);
    }
    string * adj=({ 
        valid_incog_override(query_incog_attribute("adj1")),
        valid_incog_override(query_incog_attribute("adj2")) })
        + QSW->query_adj(1);
   
    adj = adj - ({ 0 });
    if (arg)
    {
        return adj;
    }
    if (sizeof(adj))
    {
        return adj[0];
    }
    return 0;
}


/* 
 * PARSE_COMMAND
 *
 * These lfuns are called from within the efun parse_command() to get the
 * three different sets of ids. If no plural ids are returned then the
 * efun will try to make pluralforms from the singular ids.
 *
 * If no normal ids are returned then parse_command will never find the object.
 */
public string *
parse_command_id_list()         
{ 
    string * ids=QSW->parse_command_id_list();
    if (ids && sizeof(ids) && query_incognito() && 
        query_incog_attribute("race"))
    {
        ids+=({ query_incog_attribute("race") });
    }
    else
    if (ids && sizeof(ids) && query_vamp_option(VOPT_VAMPIRE_RACE))
    {
        ids+=({ "vampyr" });
    }
    
    return ids;
}

/*
 * Description: This function is used by the efun parse_command()
 */
public string *
parse_command_plural_id_list() 
{ 
    string * ids=QSW->parse_command_plural_id_list();
    if (ids && sizeof(ids) && query_vamp_option(VOPT_VAMPIRE_RACE))
    {
        ids+=({ "vampyr" });
    }
    return ids;
}

/*
 * Description: This function is used by the efun parse_command()
 */
public string *
parse_command_adjectiv_id_list() 
{
    string * ids=QSW->parse_command_adjectiv_id_list();
    if (ids && sizeof(ids) && query_incognito())
    {
        ids+=({ 
        valid_incog_override(query_incog_attribute("adj1")),
        valid_incog_override(query_incog_attribute("adj2")) });
        ids-=({ 0 });
    }
    return ids;
}


public mixed query_names()
{
    string * names=QSW->query_names();
    
    if (query_vamp_option(VOPT_VAMPIRE_RACE))
    {
        names+=({ "vampyr" });
    }
    if (query_incognito() && query_incog_attribute("race"))
    {
        names+=({ query_incog_attribute("race") });
    }
    return names;
}

public void load_disguises()
{
    Known_attributes=query_manager()->query_known_disguises(QSW);
    if (!Known_attributes)
    {
        Known_attributes=([ ]);
    }
    Chosen_attributes=query_manager()->query_chosen_disguise(QSW);
    if (!Chosen_attributes)
    {
        Chosen_attributes=([ ]);
    }
}

public void save_disguises()
{
    query_manager()->set_known_disguises(QSW,Known_attributes);
    query_manager()->set_chosen_disguise(QSW,Chosen_attributes);
}


public int query_mist()
{
    return Mist;
}

public void unset_mist()
{
    int i=Mist;
    mixed * watchers=(QSW && ENV(QSW) ? WATCHERS(QSW) : ({ }));

    QSW->remove_stun(); 
    QSW->remove_prop(LIVE_M_MOUTH_BLOCKED);
    QSW->remove_prop(LIVE_I_NEVERKNOWN);
    Mist=0;
    if (Revert_alarmid)
    {
        remove_alarm(Revert_alarmid);
    }
    Revert_alarmid=0;
    if (i)
    {
        
        QSW->catch_msg("You return once more to solid form.\n");
        watchers->catch_msg("The roiling mist quickly coalesces into the "+
        "shape of " + QNAME(QSW) + ".\n");
    }
}

public void set_mist()
{
    mixed * watchers=WATCHERS(QSW);

    if (!Mist)
    {
        QSW->catch_msg("You turn into a cloud of mist.\n");
        watchers->catch_msg("Darkness eminates from " + QTNAME(QSW) +
        "'s pores, enveloping " + OBJ(QSW) + " in a mist that rapidly "+
        "obscures " + OBJ(QSW) + " from sight.\n");
        QSW->add_stun(); 
        QSW->add_prop(LIVE_M_MOUTH_BLOCKED,"You are presently in mist "+
        "form, making noise impossible.\n");
        QSW->add_prop(LIVE_I_NEVERKNOWN,1);
        Mist=1;
        Revert_alarmid=set_alarm(10.0,0.0,unset_mist);
    }
}
    

public string short(object for_obj)
{
    if (Mist)
    {
        return "roiling mist of dark potentials";
    }
    return QSW->short();
}

public string query_nonmet_name()
{
    if (Mist)
    {
        return "roiling mist of dark potentials";
    }
    return QSW->query_nonmet_name();
}

public string long()
{
    if (Mist)
    {
        return "A dark and roiling mist ominous with potential, as if " +
        "it was alive.\n";
    }
    return QSW->long();
}

public string query_mm_out()
{
    if (!Mist)
    {
        set_mist();
        set_alarm(1.0,0.0,unset_mist);
    }
    return "dissipates quickly into nothing.";
}
    
public string query_mm_in()
{
    return "forms from nothingness.";
}


public string query_m_out()
{
    if (Mist)
    {
        return "drifts";
    }
    return QSW->query_m_out();
}
    
public string query_m_in()
{
    if (Mist)
    {
        return "drifts in";
    }
    return QSW->query_m_in();
}


