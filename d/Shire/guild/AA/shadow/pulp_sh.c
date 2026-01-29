/*
 * Revisions:
 * 	Lucius, Sept 2017: Changed add_leftover to the correct usage
 * 	                   of set_leftover_list.
 */
inherit "/std/shadow";

#include <stdproperties.h>
#include <language.h> /* Composite words */

public object make_corpse()
{
    object pulp=shadow_who->make_corpse();
    
    if (!objectp(pulp))
    {
        pulp = clone_object("/std/corpse");
        pulp->set_name(this_object()->query_name());
        pulp->change_prop(CONT_I_WEIGHT, 
                this_object()->query_prop(CONT_I_WEIGHT));
        pulp->change_prop(CONT_I_VOLUME, 
                this_object()->query_prop(CONT_I_VOLUME));
        pulp->add_prop(CORPSE_S_RACE, this_object()->query_race_name());
        pulp->add_prop(CONT_I_TRANSP, 1);
        pulp->change_prop(CONT_I_MAX_WEIGHT,
                            this_object()->query_prop(CONT_I_MAX_WEIGHT));
        pulp->change_prop(CONT_I_MAX_VOLUME,
                            this_object()->query_prop(CONT_I_MAX_VOLUME));
        pulp->set_leftover_list(this_object()->query_leftover());
    
    }
    
    string enemy_race=shadow_who->query_race_name();
    
    pulp->add_adj("bloody");
    pulp->add_name("pulp");
    pulp->set_short("bloody "+enemy_race+" pulp");
    pulp->set_pshort("bloody "+enemy_race+" pulps");
    pulp->set_long("This is the pulp that is left after you thoroughly "+
                "smash "+LANG_ADDART(enemy_race)+".\n");
    return pulp;
}
            
