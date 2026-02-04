/*
 * Changelog:
 *  November 2009 - Vamp blood should not ever be negative. (Petros)
 *
 */
                   
#include "../defs.h";

object Last_env;

public int query_base_vamp_stat();

public int query_max_blood()
{
    return 40+query_base_vamp_stat();
}

public int query_blood()
{
    // Blood can never be negative
    return max(0, QSW->query_skill(VAMP_BLOOD));
}

public int query_missing_blood()
{
    return query_max_blood()-query_blood();
}


public void add_blood(int blood)
{
    int current = query_blood();
    
    current += blood;
    
    // Ensure blood range of 0->query_max_blood()
    current = max(0, current);
    current = min(query_max_blood(), current);
    
    QSW->set_skill(VAMP_BLOOD, current);

}

public int query_blood_modifier()
{
    return query_missing_blood()/30;
}

public int thirst()
{
    return min(100,(query_missing_blood()*100/query_max_blood()));
}

/*
 * Function name: desc_vamp_thirst
 * Description:   Returns a string describing the vampire's
 *                thirst level.
 */
varargs public string
desc_vamp_thirst(object for_obj = QSW)
{
    string msg;

    int th=thirst();
    
    if (TO->query_bloodguard())
    {
        th/=2;
    }

    if (for_obj != QSW)
    {
        switch (max(0, th + 
                (random(2) ? random(10) : -random(10))))
        {
            case 0..10:
                msg = "'s skin is still warm with the glow " +
                    "of fresh blood.\n";
                break;
            case 11..30:
                msg = " appears to be well nourished.\n";
                break;
            case 31..60:
                msg = "'s lusterless eyes indicate " +
                    POSS(QSW) + " need to feed.\n";
                break;
            case 61..80:
                msg = "'s skin is dry and sallow.  " + 
                    capitalize(PRO(QSW)) + " is obviously in " +
                   "need of blood.\n";
                break;
            case 81..90:
                msg = " is obviously barely sustained.\n";
                break;
            default:
                msg = " is in torpor.\n";
            
                break;
        }
        
        return QSW->query_The_name(for_obj) + msg;
    }

    switch (th)
    {
        case  0.. 10:
            return "The thirst is sated.\n";
        case 11.. 30:
            return "The thirst is barely noticeable.\n";
        case 31.. 60:
            return "The thirst is becoming ever more noticeable.\n";
        case 61.. 80:
            return "The thirst compels you to seek out a victim.\n";
        case 81.. 90:
            return "The thirst torments you, driving you to seek fresh blood.\n";
        case 91..100:
            return "The thirst is nearly overwhelming, compelling you to "+
                "feed.\n";
        default:
            return "The thirst is overwhelming; you must feed immediately.\n";
    }
}


public void reduce_blood()
{
    set_alarm(itof(max(60,TO->query_vamp_stat())),0.0,reduce_blood);
    
    if (QSW && environment(QSW) && 
            environment(QSW)->query_prop(ROOM_I_NO_THIRST))
    {
        return;
    }

    if (!interactive(QSW))
    {
        return;
    }

    int reduction=0;
    
    if (environment(QSW)!=Last_env || !random(15))
    {
        reduction-=1;
    }
    
    if (TO->query_sunlight_modifier()>5)
    {
        reduction-=1;
    }
    
    if (TO->query_attack())
    {
        reduction-=1;
    }
    add_blood(reduction);
    
    if (!random(2) && reduction)
    {
        TO->reduce_blood_skills();
    }
    if (query_vamp_option(VOPT_NOTIFY_THIRST) && reduction)
    {
        QSW->catch_msg(desc_vamp_thirst());
    }
    
    Last_env=environment(QSW);
}
