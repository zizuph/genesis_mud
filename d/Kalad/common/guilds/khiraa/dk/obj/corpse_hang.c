/* 
 * /d/Kalad/common/guilds/khiraa/dk/obj/corpse_hang.c
 * Purpose    : This is the corpse object that is used with the khiraa command 'hang'. You can hang a corpse up with a hook or rope, and it will turn into this corpse. It can be 'cut' down to turn it back into a normal corpse.
 * Located    : From the command 'hang'
 * Created By : Sarr 12.May.97
 * Modified By: 
 */ 

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
inherit "/std/object";


string from_type;
string corpse_short;
string r_name;
string c_race;

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
    return LANG_ADDART(corpse_short);
}

string
query_nonmet_name()
{
    return corpse_short;
}


void
set_from_type(string s)
{
    from_type = s;
}

string
query_from_type()
{
    return from_type;
}

void
create_object()
{
    set_name("corpse");
    set_short("corpse of @@query_corpse_short@@ hanging from "+ 
    "@@query_from_type@@");
    set_long("You stumble upon a grusome sight. A rotting corpse "+
    "of @@query_corpse_short@@ hangs upside down from "+
    "@@query_from_type@@, dripping blood in a small pool below "+
    "it. It's eyes are gouged out, and its mouth hangs open in a "+
    "ghastly silent scream. Upon its torso, a picture of a "+
    "grim looking skull has been painted.\n");
    add_prop(OBJ_M_NO_GET,1);
}

void
init()
{
    ::init();
    AA(do_cut,cut);
}

int
do_cut(string str)
{
    object corpse;
    seteuid(getuid());
    NF("Cut down what?\n");
    if(str != "down corpse")
        return 0;
    TP->catch_msg("You cut down the corpse from "+from_type+".\n");
    say(QCTNAME(TP)+" cuts down the corpse from "+from_type+".\n");

    corpse = clone_object("/std/corpse");            
    corpse->set_name(r_name);
    corpse->change_prop(CONT_I_WEIGHT,query_prop(OBJ_I_WEIGHT));
    corpse->change_prop(CONT_I_VOLUME,query_prop(OBJ_I_VOLUME));
    corpse->add_prop(CORPSE_S_RACE,query_race_name());
    corpse->add_prop(CONT_I_TRANSP, 1);
    corpse->change_prop(CONT_I_MAX_WEIGHT,
        corpse->query_prop(CONT_I_WEIGHT)*2);
    corpse->change_prop(CONT_I_MAX_VOLUME,
        corpse->query_prop(CONT_I_VOLUME)*2);
    corpse->move(E(TO));
    remove_object();
    return 1;
}

