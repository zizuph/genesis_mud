/*
 * BF Guild manager, mappings
 *
 */

#pragma save_binary
#pragma no_clone
#pragma no_shadow
#pragma no_inherit
#pragma strict_types

#include <files.h>
#include <composite.h>
#include <macros.h>
#include <std.h>
#include <stdproperties.h>
#include "../guild.h";

void create();

public static int alarm_id, cleanup_alarm, auto_intro;

mapping Bf_reputation;
mapping Bf_nodes;




private static mapping passer_by = ([]);

private void
perform_cleanup(void)
{
    /* Two weeks good? */
    int i, limit = 9999;
	
    string *people = m_indices(passer_by);

    cleanup_alarm = 0;

    if (!sizeof(people))
	return;

    for (i = 0; i < sizeof(people); i++)
    {
	    if (passer_by[people[i]][1] < limit)
	    m_delkey(passer_by, people[i]);
    }
}


/* 
 *  Make things happen when I meet the right people.
 */
public varargs void
register_living(object who, string direction, string node)
{
    /* Don't notice npcs */
    if (!query_interactive(who))
	return;

    // We dont register invisible creatures.
    if (who->query_prop(OBJ_I_INVIS))
    {
        return;
    }
    
    // We dont register otherplanar creatures
    if (who->query_ethereal() == 1)
    {
        return;
    }
    
    string name = who->query_real_name();

    passer_by[name] = ({ direction, time(), who->query_real_name(), node, name });

//    if (!cleanup_alarm && !random(3))
	//cleanup_alarm = set_alarm(itof(5), 0.0, perform_cleanup);
}


/*
 * Describe how long ago I met someone.
 */
public string
time_met_desc(int tm)
{
    int how_long_ago;

    /* How long ago I met the person, in minutes. */
    how_long_ago = (time() - tm) / 60;

    switch(how_long_ago)
    {
    case 0 .. 2:
	return "just now";
	break;
    case 3 .. 7:
	return "very recently";
	break;
    case 8 .. 20:
	return "fairly recently";
	break;
    case 21 .. 60:
	return "recently";
	break;
    case 61 .. 120:
	return "a little while ago";
	break;
    case 121 .. 250:
	return "a while ago";
	break;
    default:
	return "a long time ago";
	break;
    }

    // Sanity check
    return "sometime";
}


/*
 * Give a nice listing of those people who I have
 * encountered, based on whether I know them or not.
 *
 * E.g., "a long-armed elf, Cirion, and a sultry dark-skinned human"
 */
private string
list_met2(string whom)
{
    int i, s;
    mixed elem;
    string *indices, *descs = ({});
    
    string whoe, whoo;
    
    whoe = whom;

    indices = m_indices(passer_by);
    
    if (!sizeof(indices))
	return "That individual has not been detected yet.\n";

    s = sizeof(indices);
    i = -1;
	
    while(++i < s)
    {
		elem = passer_by[indices[i]];

        whoo = indices[i];
            
        if (whoe == whoo)
        {
			descs += ({capitalize(indices[i]) + elem[0] + time_met_desc(elem[1])+" ("+elem[3]+")\n"});
        }
        /*else
        {
            descs = ({"test" });
        } */    
    }
    
    /*if (whoe != whoo)
    {
		descs = ({"No information on that individual.\n"});
    }*/
        
	return COMPOSITE_WORDS_WITH(descs,"");
}


public string
ask_about_encountered(string str)
{
    write(list_met2(str));

    return "";
}


// for debugging...
public void
dump_met(void)
{
    dump_mapping(passer_by);
}











public int
query_bf_nodes(string real_name)
{
    return Bf_nodes[lower_case(real_name)];
}


public void
set_bf_nodes(string real_name, int bfnodes)
{
    Bf_nodes = restore_map(BF_NODES);
    Bf_nodes[lower_case(real_name)] = bfnodes;
    save_map(Bf_nodes, BF_NODES);
}


public void
clean_bf_nodes(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Bf_nodes[real_name])
    {
        Bf_nodes = m_delete(Bf_nodes, real_name);
        save_map(Bf_nodes, BF_NODES);
    }
}



















public int
query_bf_reputation(string real_name)
{
    return Bf_reputation[lower_case(real_name)];
}


public void
set_bf_reputation(string real_name, int bfrep_nr)
{
    Bf_reputation = restore_map(BF_REP);
    Bf_reputation[lower_case(real_name)] = bfrep_nr;
    save_map(Bf_reputation, BF_REP);
}


public void
clean_bf_reputation(string real_name)
{
    real_name = lower_case(real_name);
    
    if(Bf_reputation[real_name])
    {
        Bf_reputation = m_delete(Bf_reputation, real_name);
        save_map(Bf_reputation, BF_REP);
    }
}


void
create()
{
    int i;

    seteuid(getuid(this_object()));
    
    Bf_reputation = restore_map(BF_REP);
	Bf_nodes = restore_map(BF_NODES);
}
