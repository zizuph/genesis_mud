
/* 
   This is the spellcasting object for water spells of the 
   Elemental Worshippers guild. 

   Coded by Jaacar. 

   Modifications by Maniac 27/9/96
   Added Spell Ban - September 5th, 2003, Jaacar
*/ 

#pragma save_binary

#include "defs.h"

inherit "/std/object";
inherit "/d/Genesis/newmagic/spellcasting";

#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>
#include WORSHIP_HEADER
#include COUNCIL_HEADER


int count = 0;

int
is_worship(object living)
{
    return living->query_guild_name_lay() == GUILD_NAME;
}

string
query_auto_load()
{
    return MASTER + ":" + count;
}


int
dest_tool()
{
    object e;

    e = environment(this_object());

    if (interactive(e))
        e->catch_msg("The Water Chalice shatters into thousands of " +
                     "tiny pieces.\n");
    else
        tell_room(e, "The Water Chalice shatters into thousands of " +
                     "tiny pieces.\n");

    remove_object();
    return 1;
}


/* We don't let non-worshippers keep hold of these for long. */
void
init_arg(string arg)
{
    if (!is_worship(this_player()))
    {
        count = atoi(arg) + 1;
        if (count >= 50)
            set_alarm(5.0, 0.0, dest_tool);
    }
    if (TP->query_skill(SS_PUNISHMENT) == SPELL_BANNED)
        set_alarm(5.0, 0.0, dest_tool);
}


void
try_to_activate()
{
    if (is_worship(environment(TO)))
    {
        if (environment(TO)->query_skill(SS_CARVED) & WATER_FLAG)
        {
            remove_spell("/d/Calia/newworshippers/spells/t_kataraktas.c");
            add_spell("/d/Calia/newworshippers/spells/t_kataraktas.c");
            remove_spell("/d/Calia/newworshippers/spells/t_pagos.c");
            add_spell("/d/Calia/newworshippers/spells/t_pagos.c");            
            
            if (environment(TO)->query_skill(SS_PATRON_ELEMENTAL) & WATER_FLAG)
            {
                remove_spell("/d/Calia/newworshippers/spells/t_aleipso.c");
                add_spell("/d/Calia/newworshippers/spells/t_aleipso.c");
            }
        }
    }
}

void
create_object()
{
    set_name("chalice");
    add_name("worshipper_chalice");
    add_name(WORSHIPPER_OBJECT_ID);
    add_name(I_CAN_CAST);
    set_short("gold water chalice");
    set_long("This is a Water Chalice, shaped like a typical "+
        "wine glass and coated in gold.  Strange runes are "+
        "written vertically and evenly spaced around the outside "+
        "of the cup.  "+
        VBFC_ME("chal_long") + "\n");
    add_prop(OBJ_M_NO_INS, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_NO_GIVE, 1);
    add_prop(OBJ_I_NO_STEAL,1);
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    add_spell_object(env);
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    remove_spell_object(env);
}

string
chal_long()
{
    string long_desc;

    if(TP->query_skill(SS_CARVED) & WATER_FLAG)
        {
            long_desc = "The runes read: Diabrecho, "+
                capitalize(TP->query_real_name())+
                ", Meizon.  ";
        }
    else
        {
            long_desc = "The runes read: Diabrecho, "+
                capitalize(TP->query_real_name())+
                ".  ";
        }
    return long_desc;
}

void
init()
{
    ::init();
    
    try_to_activate();
}
