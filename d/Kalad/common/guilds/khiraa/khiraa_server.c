/*
    khiraa_server.c

    Guild member server for the Khiraa guild

    Fysix@Genesis, Feb 1998
 */

#pragma strict_types
#pragma save_binary

#include <files.h>
#include "default.h"

// Globals
mapping Lich_names,         // Lich names
        Circle_members,     // names of the circle
        Guild_orders;       // Which guild order is the mortal in?

// --- Friends & Seekers -----------------------------------------


  // Add a new seeker, this will give the council a list of people
  // who are applying to the guild. It gives the date/time, name and who
  // added them to the log. This way it is easier to keep track of applicants
  // to the guild. the log is SEEKER_LOG.
int
add_seeker(string name, string extra, string master_name)
{
    int i;
    string *names,s1,s2;
    mapping temp;
    object ob;

    temp = restore_map(SEEKER_LOG);

    if(!m_sizeof(temp))
        temp = ([]);

    // If member already listed there, cancel
    if(member_array(name,m_indexes(temp)) != -1)
        return 0;

    temp += ([name:capitalize(master_name)+" added on "+ctime(time())+
    ", seeking the "+extra]);

    // Inform the player of the good news! (if they are on)
    ob = find_player(name);
    if(objectp(ob))
        tell_object(ob,"You have been declared a seeker of the "+extra+" of "+
        "the Khiraa by "+master_name+".\n");

    // Save changes
    save_map(temp,SEEKER_LOG);
    return 1;
}


 // List the seekers of the guild
string
list_seekers()
{
    int i;
    string the_list;
    mapping temp;
    temp  = restore_map(SEEKER_LOG);
    the_list = "";
    if(!m_sizeof(temp))
        return "There are no seekers listed.\n";

    for(i=0; i < sizeof(m_indexes(temp));i++)
        the_list += C((m_indexes(temp))[i])+" - "+temp[(m_indexes(temp))[i]]+"\n";

    return the_list;
}

  // Remove the seeker from the list
int
remove_seeker(string name, string master_name)
{
    int i;
    string *names,s1,s2;
    mapping temp;
    object ob;

    temp = restore_map(SEEKER_LOG);

    if(!m_sizeof(temp))
        return 0;

    // If member not listed there, cancel
    if(member_array(name,m_indexes(temp)) == -1)
        return 0;

    temp = m_delete(temp,name);

    // Inform the player of the bad news! (if they are on)
    ob = find_player(name);
    if(objectp(ob))
        tell_object(ob,"You have been removed as a seeker of the Khiraa "+
        "by "+master_name+".\n");

    // Save changes
    save_map(temp,SEEKER_LOG);
    return 1;
}

 // This will add a new 'friend' of the Khiraa to the list. Council can
   // access this list, and it will show who added the person and what
   // time. Friends of the Khiraa have access to inside of the guild.
int
add_friend(string name, string master_name)
{
    string *names;
    mapping temp;
    object ob;

    temp = restore_map(FRIENDS_LOG);

    if(!m_sizeof(temp))
        temp = ([]);

    // If member already listed there, cancel
    if(member_array(name,m_indexes(temp)) != -1)
        return 0;

    temp += ([name:"Added by "+master_name+" on "+ctime(time())]);

    // Inform the player of the good news! (if they are on)
    ob = find_player(name);

    if(objectp(ob))
        tell_object(ob,"You have been declared a friend of the Khiraa "+
        "by "+master_name+".\n");
    // Save changes

    save_map(temp,FRIENDS_LOG);
    return 1;
}

string
list_friends()
{
    int i;
    string the_list;
    mapping temp;
    temp  = restore_map(FRIENDS_LOG);
    the_list = "";
    if(!m_sizeof(temp))
        return "There are no friends of the Khiraa listed.\n";

    for(i=0; i < sizeof(m_indexes(temp));i++)
        the_list += C((m_indexes(temp))[i])+" - "+temp[(m_indexes(temp))[i]]+"\n";

    return the_list;
}

int
remove_friend(string name, string master_name)
{
    int i;
    string *names,s1,s2;
    mapping temp;
    object ob;

    temp = restore_map(FRIENDS_LOG);

    if(!m_sizeof(temp))
        return 0;

    // If member not listed there, cancel
    if(member_array(name,m_indexes(temp)) == -1)
        return 0;

    temp = m_delete(temp,name);

    // Inform the player of the bad news! (if they are on)
    ob = find_player(name);
    if(objectp(ob))
        tell_object(ob,"You have been removed as a friend of the Khiraa "+
        "by "+master_name+".\n");

    // Save changes
    save_map(temp,FRIENDS_LOG);
    return 1;
}

// --- Lich names ------------------------------------------------

public mapping
query_lich_names()
{
    return Lich_names + ([ ]);
}

// Set the Lich name of a member
// Returns 0 if player was not a member

public int
set_lich_name(string real_name, string lich_name)
{
    real_name = lower_case(real_name);
    if (!Guild_orders[real_name])
        return 0;

    Lich_names[real_name] = lich_name;
    save_map(Lich_names, LICH_NAMES_FILE);
    return 1;
}

// What's the Lich name of a member
public string
query_lich_name(string real_name)
{
    if(Lich_names[lower_case(real_name)])
        return Lich_names[lower_case(real_name)];
    return "Newborn"; // Default Lich name
}

// --- Circle members --------------------------------------------


// Add a circle member,
// x = 0 : normal member, 1 : circle master, 2   
// Returns 0 if player was not a member

public int
add_circle_member(string real_name, int x)
{
    real_name = lower_case(real_name);
    if (!Guild_orders[real_name])
        return 0;

    if(x == 0 && Circle_members[real_name] )
        Circle_members = m_delete(Circle_members,real_name);
    else
        Circle_members[real_name] = x;
    save_map(Circle_members, CIRCLE_MEMBERS_FILE);
    return 1;
}

// Is the player a circle member?
// Returns: 0 : no circle member, 1 : member, 2 : master
public int
query_circle_member(string real_name)
{
    return Circle_members[lower_case(real_name)];
}

public string
query_circle_members()
{
    int i;
    string list;
    string *names = m_indexes(Circle_members);
    list = "";
    names = sort_array(names);
    for(i = 0; i <sizeof(names); i++)
    {
        if(Circle_members[names[i]] == 1)
        {
            list += "Circle Member of the Khiraa      - ";
        }
        else
            list += "Circle Master of the Khiraa      - ";
        list += C(names[i])+"\n";
    }
    return list;
}

// --- Guild orders ---------------------------------------------

public mapping
query_guild_orders()
{
    return Guild_orders + ([ ]);
}

// Set the guild order of a member
// order: integer between 1 and 25. Different for Lichs and DKs
// This holds the list of all the members and what their current
// level is. They are promoted by council to higher orders as
// they do good things for the guild, or tasks set forth by high
// levels. The higher the order, the more spells they get.

public void
set_guild_order(string real_name, int order)
{
    Guild_orders[lower_case(real_name)] = order;
    save_map(Guild_orders, GUILD_ORDERS_FILE);
}

// see if a member exists already
public int
member_exists(string real_name)
{
    real_name = lower_case(real_name);
    if(member_array(real_name,m_indexes(Guild_orders)) != -1)
        return 1;
    return 0;
}

// Return the guild order of a member
public int
query_guild_order(string real_name)
{
    return Guild_orders[lower_case(real_name)];
}

// Add a new guild member
public void
add_member(string real_name)
{
    real_name = lower_case(real_name);
    Circle_members[real_name] = 1; // Start at level 1    
}

// remove a guild member
public void
remove_member(string real_name)
{
    real_name = lower_case(real_name);

    if(Lich_names[real_name])
    {
        Lich_names = m_delete(Lich_names, real_name);
        save_map(Lich_names, LICH_NAMES_FILE);
    }
    if(Circle_members[real_name])
    {
        Circle_members = m_delete(Circle_members, real_name);
        save_map(Circle_members, CIRCLE_MEMBERS_FILE);
    }
    if(Guild_orders[real_name])
    {
        Guild_orders = m_delete(Guild_orders, real_name);
        save_map(Guild_orders, GUILD_ORDERS_FILE);
    }
}

/* Function    : member_purge
 * Description : check members if they still exist in this mud, otherwise
 *               kick them out. 20% random for each purge, since not all
 *               members need to be checked each time since it's quite time
 *               consuming
 */
void
member_purge()
{
    int    i, n;
    string *name = m_indices(Guild_orders);

    n = sizeof(name);
    for (i = 0; i < n; i++)
        if (random(100) < 20 && !SECURITY->exist_player(name[i]))
            remove_member(name[i]);
}

// Initialize
void
create()
{
    setuid();
    seteuid(getuid());

    Lich_names = restore_map(LICH_NAMES_FILE);
    Circle_members = restore_map(CIRCLE_MEMBERS_FILE);
    Guild_orders = restore_map(GUILD_ORDERS_FILE);
    
    // Purge members after a random amount of time
    set_alarm(1000.0 + itof(random(1000)), 0.0, member_purge);
}
