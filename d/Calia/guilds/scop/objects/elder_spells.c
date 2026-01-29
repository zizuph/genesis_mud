
/*
 * elder_spells.c
 *
 * The Elder Spells Spell Object for the Spirit Circle of Psuchae
 *
 * Copyright (C): Jaacar, August 1st, 2003
 *
 */

#pragma strict_types
#pragma save_binary

inherit "/std/object";
inherit "/d/Genesis/newmagic/spellcasting.c";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"
#include SPIRIT_HEADER
#include COUNCIL_HEADER

void
create_object()
{
    set_name("_spirit_elder_spells_");
    set_no_show();
    add_prop(OBJ_I_VALUE, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_WEIGHT, 1);

    add_prop(OBJ_M_NO_INS, 1);
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    
    seteuid(getuid());
}

varargs void
add_eighth_spells()
{
    mixed *eighth_spell_list = EIGHTH_LEVEL_SPELL_LIST;
    int i, size;
     
    size = sizeof(eighth_spell_list);

    for (i=0; i < size; i++)
    {
        add_spell(clone_object(SPIRIT_SPELLS + eighth_spell_list[i]));
    }
}

void
remove_eighth_spells()
{
    mixed *eighth_spell_list = EIGHTH_LEVEL_SPELL_LIST;
    int i, size;
     
    size = sizeof(eighth_spell_list);

    for (i=0; i < size; i++)
    {
    	remove_spell(eighth_spell_list[i]);
    }
}

public void
update_eighth_spells(int level)
{
    object ob = environment(TO);
    
    if (living(ob))
    {
    	remove_eighth_spells();
    	add_eighth_spells();
    }
}

int
str_compare(string a, string b)
{
    if (b > a)
        return 1;
    else if (b < a)
        return -1;
    else
        return 0;
} 

/*
 * Function name: list_spells
 * Description:   This function is called to list the spells from
 *                the player soul when the command "spells" is used.
 */
public void
list_spells()
{
    mapping spells;
    string *verbs;
    int i;
    object ob;

    spells = query_spell_map();

    verbs = m_indices(spells);

    if (!sizeof(verbs))
    {
        write("You have not divined for any elder gifts yet.\n");
        return;
    }

    /* sort the verbs */
    verbs = sort_array(verbs, "str_compare", TO);

    write("========================================\n"+
          "=   Elder Ranking Gifts of Psuchae:    =\n"+
          "========================================\n");

    i = sizeof(verbs);

    while(i--)
    {
    	int j;
    	string s, *desc;
    	
    	if (ob = get_spell_object(verbs[i]))
    	{
    	    desc = ({ ob->query_spell_desc() || "" });

            if (strlen(desc[0]) > 40)
                desc = explode(break_string(desc[0],40),"\n");

            s = sprintf("%-15s  %-20s\n",verbs[i], desc[0]);
            for (j=1; j<sizeof(desc); j++)
            {
                s += sprintf("%-15s  %-20s\n","", desc[j]);
            }
            write(s);
        }
    }
}

public void
remove_object()
{
    /* Remove any cloned instances of spells that are registered with this
     * spellcasting object so that they aren't sitting around just taking up
     * memory.  You can either call remove_object() in the spells yourself,
     * or use the utility function cleanup_spells() to do it.
     */
    cleanup_spells();
    ::remove_object();
}


void
enter_env(object env, object from)
{
    if (!(IS_MEMBER(env)))
        remove_object();
    
    ::enter_env(env, from);
    add_spell_object(env);
}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    remove_spell_object(env);
}


