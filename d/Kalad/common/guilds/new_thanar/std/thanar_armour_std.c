/*  This modifies the standard armour code to allow for ac to be 
*   changed based on a calculation of a players physical stats when 
*   compared to their mental stats. 
*
 *  Coded by Mirandus
*/

inherit "/std/armour";
inherit "/lib/keep";
inherit "/d/Kalad/std/volume";

#include <wa_types.h>
#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>


public varargs string 
short(object for_obj)
{
    string res;

    if (!obj_short)
    {
    remove_adj("unworn");
    res = ::short(for_obj);
    add_adj("unwworn");
    return res;
    }
    else
    {
    return ::short(for_obj);
    }
}

void
create_armour()
{
    ::create_armour();
}

public void
enter_env(object dest, object from)
{
    int stat_percent, stat_phys_avg, stat_ment_avg, old_ac,
    new_ac, *phys_stats, *ment_stats;
    float stat_mod;
    
    object TO = this_object();
    
    ::enter_env(dest, from);
    
       
    old_ac = MASTER_OB(TO)->query_ac();
        
    
    if (!living(dest)) return;
    phys_stats = ({ SS_STR, SS_CON, SS_DEX }); 
    stat_phys_avg = reduce(&operator(+)(,), map(phys_stats, 
        dest->query_stat)) / sizeof(phys_stats);
    
    ment_stats = ({ SS_WIS, SS_INT, SS_DIS }); 
    stat_ment_avg = reduce(&operator(+)(,), map(ment_stats, 
        dest->query_stat)) / sizeof(ment_stats);
    
    stat_percent = min(110,(stat_ment_avg *100)/ stat_phys_avg);
    
    switch(stat_percent) 
    {
    case 110:  
        stat_mod = 1.7;
        break;
    
    case 107..109:
        stat_mod = 1.65;
        break;
        
    case 104..106:
        stat_mod = 1.6;
        break;
        
    case 101..103:
        stat_mod = 1.5;
        break;
    
    case 99..100:
        stat_mod = 1.45;
        break;

    case 97..98:
        stat_mod = 1.4;
        break;        

    case 95..96:
        stat_mod = 1.35;
        break;

    case 93..94:
        stat_mod = 1.3;
        break;
        
    case 91..92:
        stat_mod = 1.2;
        break;
    
    default:
        stat_mod = 1.0;
        break;
    }
    
    
    new_ac = min(60,(ftoi(itof(old_ac) * (stat_mod))));
            
    set_default_armour(new_ac, A_WAIST, 3, 0);
    
}

