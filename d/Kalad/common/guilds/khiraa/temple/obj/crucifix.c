#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#include <filter_funs.h>
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
create_object()
{
    set_name("crucifix");
    set_short("large wooden crucifix with a burning @@query_corpse_short@@ "+
    "nailed to it");
    set_pshort("large wooden crucifixes with burning @@query_corpse_short@@ "+
    "nailed to them");

    set_long("You gaze upon a horrible sight. A large, wooden crucifix "+
    "has been erected here, upon which is nailed a @@query_corpse_short@@ "+
    "that is consumed by plume of multi-colored fire, screaming "+
    "with terrible agony. You might be able to put it to 'rest'.\n");

    add_prop(OBJ_M_NO_GET,1);
}

void
start_screams()
{
    if(random(2))
    {
        if(random(2))
            tell_room(E(TO),"The "+corpse_short+" screams with agony!\n");
        else
            tell_room(E(TO),"The sickly smell of burnt flesh wafts off "+
            "the "+short()+".\n");
    }
    else
    {
        tell_room(E(TO),"The "+corpse_short+" burns and sizzles gruesomly.\n");
    }
    
    if( sizeof(FILTER_PLAYERS(all_inventory( E(TO) ) )))
        alrm = set_alarm(60.0,0.0,&start_screams());
}

void
init()
{
    ::init();
    if(interactive(TP) && !get_alarm(alrm))
        alrm = set_alarm(60.0,0.0,&start_screams());
    AA(do_cut,rest);
}

int
do_cut(string str)
{
    object corpse;
    seteuid(getuid());
    NF("Rest what? The corpse?\n");
    if(str != "corpse")
        return 0;
    NF("You are not a cleric.\n");
    if(TP->query_guild_style_occ() != "cleric" &&
       TP->query_guild_style_lay() != "cleric" &&
        TP->query_knight_level() == 3) // Let KoS sword rest them
        return 0;
    NF("You are not holy enough.\n");
    if(TP->query_alignment() < 1000)
        return 0;

    if(TP->query_knight_level())
    {
        write("You call upon Paladine to dispell this horrible sight, "+
        "and lay to rest the corpse of this poor soul.\n");
        say(QCTNAME(TP)+" calls upon Paladine to dispell this horrible, "+
        "sight, and with a wave of "+HIS(TP)+" hand, it is gone.\n");
    }
    else
    {
    write("You dispell the horrible sight with a wave of your hand.\n");
    say(QCTNAME(TP)+" dispells the "+short()+" with a wave of "+HIS(TP)+
    " hand.\n");
    }
    remove_object();
    return 1;
}

