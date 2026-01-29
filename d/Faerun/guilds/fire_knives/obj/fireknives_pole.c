#include "/d/Faerun/defs.h"
#include "../guild.h"
#include <ss_types.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <macros.h>
inherit "/std/object";


string from_type;
string corpse_short;
string r_name;
string c_race;

int alrm;

void
set_race_name(string s)
{
    c_race = s;
}


string
query_race_name()
{
    return c_race;
}


void
set_real_name(string s)
{
    r_name = s;
}


string
query_real_name()
{
    return r_name;
}


void
set_corpse_short(string s)
{
    corpse_short = s;
}


string
query_corpse_short()
{
    if(TP->query_met(r_name) && !query_prop(LIVE_I_NEVERKNOWN))
        return r_name;
    
    return corpse_short;
}


string
query_nonmet_name()
{
    return corpse_short;
}


void
remove_pole()
{
    tell_room(environment(this_object()),"Some dark-clad men arrives "
    +"and removes the "+short()+" before leaving again.\n");
            
    remove_object();
    
    return;
}


void
create_object()
{
    set_name("pole");
    
    set_short("large wooden pole with a dangling dead "
	+"@@query_corpse_short@@ "+
    "attached to it");
    
    set_long("You gaze upon a dreadful sight. A large, three "
    +"meter reinforced wooden pole "+
    "has been erected here, upon which is attached a dangling dead "
	+"@@query_corpse_short@@.\n");
    
    // 5 days
    set_alarm(432000.0, 0.0, &remove_pole());

    add_prop(OBJ_M_NO_GET,1);
}


void
start_emotes()
{
    int dice = random(3);
    
    switch(dice)
    {
        case 0:
        tell_room(environment(this_object()),"Flies surround "+
            "the "+short()+".\n");
        break;
        
        case 1:
        tell_room(environment(this_object()),"The dead "+corpse_short
		+" dangles in the wind.\n");
        break;
        
        case 2:
        tell_room(environment(this_object()),"The dead "+corpse_short
		+" is surrounded by flies and crawling maggots.\n");
        break;
    }
    
    if( sizeof(FILTER_PLAYERS(all_inventory( environment(this_object()) ) )))
        alrm = set_alarm(120.0,0.0,&start_emotes());
}


void
init()
{
    ::init();
    if(interactive(this_player()) && !get_alarm(alrm))
        alrm = set_alarm(60.0,0.0,&start_emotes());
}


