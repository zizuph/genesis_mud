/*
 * This is the master for the Templars of Neraka.
 *
 * Louie 2004
 */

#include "../local.h"

inherit GUILD_IR;

#include <ss_types.h>

#define T_RANK      0 /* int: The guild rank */
#define T_NAME      1 /* string: The special title for this players */
#define T_DATA      2 /* mapping: Info about the character */
#define T_SIZE      3 /* The size of the mapping */

mapping members;

varargs int add_member(mixed who);
void save();

/** 
 * Create the room and restore props
 */
void
create_guild_room()
{
    setuid();
    seteuid(getuid());
    
    members = ([ ]);

    //restore_object(LOG + "admin");
    restore_object(SAVE_PATH + "admin");
    set_alarm(5.0, 1800.0, &save());
}

void
save()
{
    //save_object(LOG + "admin");
    save_object(SAVE_PATH + "admin");
}

void
remove_object()
{
    save();
}


varargs int
add_member(mixed who)
{
    string whoname;
    
    if (objectp(who))
        whoname = who->query_real_name();
    
    if (!who || members[whoname])
        return 0;
    
    members[whoname] = allocate(T_SIZE);
    members[whoname][T_NAME] = "";
    members[whoname][T_RANK] = 0;
    
    //who->clear_guild_stat(SS_LAYMAN);
    
    return 1;
}

public int
remove_member(mixed who)
{
     string whoname;
     if (objectp(who))
         whoname = who->query_real_name();
     
     if (!members[whoname])
         return 0;
     
     members = m_delete(members, whoname);
     
     who->clear_guild_stat(SS_LAYMAN);
     return 1;
}

public int
query_member(mixed who)
{
    if (objectp(who))
        who = who->query_real_name();
    
    return !!members[who];
}

/*

varargs string *
query_members_real_names(string color)
{
    
    return m_indexes(members);
}

*/

/*
varargs string *
query_members_guild_names(string color)
{
    // Have to figure this one out sometime 
    //return m_indexes(members);
}
*/

/*
* Adjust rank
* 0 = none (bugged)
* 1 = apprentice
* 2 = knight
* 3 = council
*/
int
adjust_templar_rank(mixed who, int ranks)
{
    int i;
    if (objectp(who)) {
        who = who->query_real_name();
    }
    
    if (!members[who]) {
        return 0;
    }
    
    i = members[who][T_RANK];
    
    i += ranks;
    
    if (i < 0) {
        i = 0;
    }
    
    if (i > 2) {
        i = 2;
    }
    
    members[who][T_RANK] = i;
    
    return 1;       
    
}

/*
* Set the rank
*/
int
set_templar_rank(mixed who, int rank)
{
    if (objectp(who)) {
        who = who->query_real_name();
    }
    
    if (!members[who]) {
        return 0;
    }
    
    if (rank < 0)
    {
        rank = 0;
    }
    
    if (rank > 2)
    {
        rank = 2;
    }
    
    members[who][T_RANK] = rank;
    
    return 1;
}

/*
* What is this Templar's rank
*/
int
query_templar_rank(mixed who)
{
    if (objectp(who)) {
        who = who->query_real_name();
    }
    
    if (!members[who]) {
        return 0;
    }
    
    return members[who][T_RANK];
}


/*
 * Called from shadow at logout etc
 */
 /*
int
update_member_level(object who)
{
    string name;
    
    name = who->query_real_name();
    
    if (!members[name])
        return 0;
    
    members[name][M_LEVEL] = who->query_wohs_level();
    members[name][M_XP] = who->query_wohs_xp();
}
   */ 
/*
 * General Data Saving Routines
 */

/*
 * Function Name: query_data
 * Description  : Returns the data saved under the players "index" key.
 *                This can be any kind of variable.
 * Arguments    : mixed - the player
 *               string - the data index
 */
public mixed
query_data(mixed who, string index)
{
    if (objectp(who))
        who = who->query_real_name();
    
    if (!members[who])
        return 0;

    if (!members[who][T_DATA])
        return 0;
    
    return members[who][T_DATA][index];
}

/*
 * Function Name: set_data
 * Description  : Saves a variable using the index name.
 *                This should be used to save any "non important" data
 *                which is player specific. Such as teleport destinations
 *                and things like that.
 * Arguments    : mixed - the player
 *               string - the data index
 *                mixed - the data to save.
 */
public void
set_data(mixed who, string index, mixed data)
{
    if (objectp(who))
        who = who->query_real_name();
    
    if (!members[who])
        return;
    
    if (!mappingp(members[who][T_DATA]))
        members[who][T_DATA] = ([ ]);
    
    members[who][T_DATA][index] = data;
}

