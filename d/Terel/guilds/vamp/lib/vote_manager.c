/*
 * Vote Manager for the Vampyrs of Terel
 *
 * Modifications:
 *  - September 2009 - Added vamp favor check for voting requirements.
 *                     This allows a vamp that doesn't have much age to still
 *                     vote if they are favored by the Eldest. (Petros)
 *  - September 2009 - Made it so wizards and junior votes don't count. (Petros)
 */
 
#include "../guild.h"
#include <std.h>
#include <composite.h>


inherit "/d/Emerald/lib/data_manager";

#define VOTES        "votes"
#define SUCCESS      "success"
#define FAILED       "failed"

#define VOTE_TIME    0
#define VOTE_STARTED 1
#define VOTE_FOR     2
#define VOTE_AGAINST 3

#define VOTE_DURATION 86400*30

#define VOTE_LOG (LOG_DIR+"votes")

mapping vote_alarms=([ ]);

public void start_votes();

/*
 * Function name:        create_data_manager
 * Description  :        set up the manager
 */
public void
create_data_manager()
{
    setuid();
    seteuid(getuid());
    set_save_dir(DATA_DIR);
    load_data(VOTES);  
    start_votes();
}

public int can_vote(mixed name)
{
    name=get_id(name);
    if (!SECURITY->exist_player(name))
    {
        return 0;
    }
    if (SECURITY->query_wiz_level(name))
    {
        return 0;
    }
    if (get_id(name)[-2..]=="jr")
    {
        return 1;
    }
    if (!OCC_MANAGER->load_data(name))
    {
        return 0;
    }
    if (OCC_MANAGER->query_unprotected(name))
    {
        return 0;
    }
    return 1;
}

public void add_vote_success(mixed name,mixed vote)
{
    mapping success=get_info(VOTES,SUCCESS);
    if (!success)
    {
        success=([ ]);
    }
    success+=([get_id(name) : get_id(vote) ]);
    set_info(VOTES,SUCCESS,success);
}


public void add_vote_failed(mixed name,mixed vote)
{
    mapping failed=get_info(VOTES,FAILED);
    if (!failed)
    {
        failed=([ ]);
    }
    failed+=([get_id(name) : get_id(vote) ]);
    set_info(VOTES,FAILED,failed);
}


public void resolve_vote(mixed vote)
{
    mixed * data = get_info(VOTES,vote);    
    string * approve = data[VOTE_STARTED] | data [VOTE_FOR];
    string * decline = data[VOTE_AGAINST] + ({ get_id(vote) });
    int for_total;
    int against_total;
    remove_info(VOTES,vote);
    m_delkey(vote_alarms,vote);
    write_file(VOTE_LOG,ctime(time())+" Vote for "+vote+" resolved:\n");
    if (!can_vote(vote))
    {
        write_file(VOTE_LOG,ctime(time())+" "+vote+" is not a member.\n");
        return;
    }
    write_file(VOTE_LOG,ctime(time())+" Started the vote: " +
        COMPOSITE_WORDS(data[VOTE_STARTED])+"\n");
    write_file(VOTE_LOG,ctime(time())+" Voted for: " +
        COMPOSITE_WORDS(data[VOTE_FOR])+"\n");
    write_file(VOTE_LOG,ctime(time())+" Voted against: " +
        COMPOSITE_WORDS(data[VOTE_AGAINST])+"\n");

    foreach (string name : approve)
    {
        if (!can_vote(name))
        {
            continue;
        }
        if (OCC_MANAGER->is_covenmaster(name))
        {
            for_total+=(3+
                sizeof(OCC_MANAGER->query_all_guild_members()))/4;
        }
        for_total++;
    }
    write_file(VOTE_LOG,ctime(time())+" Total score for: "+for_total+"\n");
    foreach (string name : decline)
    {
        if (!can_vote(name))
        {
            continue;
        }
        if (OCC_MANAGER->is_covenmaster(name))
        {
            against_total+=
                sizeof(OCC_MANAGER->query_all_guild_members())/4;
        }
        against_total++;
    }
    write_file(VOTE_LOG,ctime(time())+" Total score against: "+
        against_total+"\n");
        
    //Must have more than half, and at least 3 votes for.    
    if (for_total>against_total && sizeof(approve)>=3)
    {
        write_file(VOTE_LOG,ctime(time())+" Vote passed.\n");
        OCC_MANAGER->set_unprotected(vote,1);
        foreach (string name : data[VOTE_STARTED])
        {
            add_vote_success(name,vote);
        }
    }
    else
    {
        write_file(VOTE_LOG,ctime(time())+" Vote failed.\n");
        foreach (string name : data[VOTE_STARTED])
        {
            add_vote_failed(name,vote);
        }
    }
        
}

public int vote_active(mixed name)
{
    name=get_id(name);
    if (vote_alarms[name])
    {
        return 1;
    }
    return 0;
}

public int has_voted(mixed name,mixed vote)
{
    mixed * data = get_info(VOTES,vote);    
    if (!sizeof(data))
    {
        return 0;
    }
    if (get_id(name)==get_id(vote))
    {
        return 1;
    }
    if (member_array(get_id(name),data[VOTE_FOR])>=0)
    {
        return 1;
    }
    if (member_array(get_id(name),data[VOTE_AGAINST])>=0)
    {
        return 1;
    }
    if (member_array(get_id(name),data[VOTE_STARTED])>=0)
    {
        return 1;
    }
    return 0;
}

public void vote_for(mixed name,mixed vote)
{
    mixed * data = get_info(VOTES,vote);    
    if (!sizeof(data))
    {
        return;
    }
    if (has_voted(name,vote))
    {
        return;
    }
    data[VOTE_FOR]+=({ get_id(name) });
    set_info(VOTES,vote,data);
}


public void vote_against(mixed name,mixed vote)
{
    mixed * data = get_info(VOTES,vote);    
    if (!sizeof(data))
    {
        return;
    }
    if (has_voted(name,vote))
    {
        return;
    }
    data[VOTE_AGAINST]+=({ get_id(name) });
    set_info(VOTES,vote,data);
}

public int has_started(mixed name,mixed vote)
{
    mixed * data = get_info(VOTES,vote);    
    if (!sizeof(data))
    {
        return 0;
    }
    if (member_array(get_id(name),data[VOTE_STARTED])>=0)
    {
        return 1;
    }
    return 0;
}

public string get_started(mixed name)
{
    name=get_id(name);
    foreach (string vote : m_indices(vote_alarms))
    {
        if (has_started(name,vote))
        {
            return vote;
        }
    }
    mapping m=get_info(VOTES,SUCCESS);
    if (m && m[name])
    {
        return m[name];
    }
    m=get_info(VOTES,FAILED);
    if (m && m[name])
    {
        return m[name];
    }
    return 0;
}

public int start_vote(mixed name,mixed vote)
{
    name=get_id(name);
    vote=get_id(vote);
    if (vote==name)
    {
        return 0;
    }
    if (!SECURITY->exist_player(vote))
    {
        return 0;
    }
    if (SECURITY->query_wiz_level(vote))
    {
        return 0;
    }
    if (get_id(vote)[-2..]=="jr")
    {
        return 0;
    }
    if (get_started(name))
    {
        return 0;
    }
    mixed * data = get_info(VOTES,vote);    
    if (!sizeof(data))
    {
        data=({ time()+VOTE_DURATION, ({ name }), ({ }), ({ }) });
        set_info(VOTES,vote,data);
        int alarm_id=set_alarm(itof(data[VOTE_TIME]-time()),0.0,
            &resolve_vote(vote));
        vote_alarms[vote]=alarm_id;
        return 1;
    }
    if (has_voted(name,vote))
    {
        return 0;
    }
    data[VOTE_STARTED]+=({ get_id(name) });
    set_info(VOTES,vote,data);
    return 1;
}

public void cancel_vote(mixed vote)
{
    if (vote_alarms[vote])
    {
        remove_alarm(vote_alarms[vote]);
        m_delkey(vote_alarms,vote);
    }
    remove_info(VOTES,vote);
}

public mapping get_active_votes()
{
    return vote_alarms;
}

public string * get_unvoted(mixed name)
{
    string * unvoted = ({ });
    foreach (string vote : m_indices(vote_alarms))
    {
        if (!has_voted(name,vote))
        {
            unvoted+=({ vote });
        }
    }
    return unvoted;
}


public void start_votes()
{
    mapping m=query_data_map();
    foreach (string key,mixed data : m[VOTES])
    {
        if (key==FAILED)
        {
            continue;
        }
        if (key==SUCCESS)
        {
            continue;
        }
        int alarm_id=set_alarm(itof(data[VOTE_TIME]-time()),0.0,
            &resolve_vote(key));
        vote_alarms[key]=alarm_id;
    }
}

public void handle_result(int result,object player,string vote)
{
    if (!player)
    {
        return;
    }
    if (result==-1)
    {
        player->catch_msg("A thought passes through your mind: "+
            "You have abstained for now.\n");
    }
    
    int bWizOrJunior = 0;
    if (player->query_wiz_level() || IS_JR(player))
    {
        bWizOrJunior = 1;
    }
    if (result==0)
    {
        if (!bWizOrJunior)
        {
            // Wizards and juniors don't affect the actual vote.
            vote_against(player,vote);
        }
        player->catch_msg("A thought passes through your mind: "+
            "Your dissent is noted.\n");
    }
    if (result==1)
    {
        if (!bWizOrJunior)
        {
            // Wizards and juniors don't affect the actual vote.
            vote_for(player,vote);
        }
        player->catch_msg("A thought passes through your mind: "+
            "Your approval is noted.\n");
    }
}

public void inform_finished_votes(object player)
{
    if (!player)
    {
        return;
    }
    if (player->query_ghost())
    {
        return;
    }
    mapping m=get_info(VOTES,SUCCESS);
    if (!m)
    {
        m=([ ]);
    }
    string name=m[get_id(player)];
    if (name)
    {
        player->catch_msg("A thought passes through your mind: "+
            "Your vote against "+CAP(name)+" has succeeded. "+
            CAP(name)+" is no longer under my protection.\n");    
        m_delkey(m,get_id(player));
        set_info(VOTES,SUCCESS,m);    
        set_alarm(60.0,0.0,&inform_finished_votes(player));
        return;
    }
    m=get_info(VOTES,FAILED);
    if (!m)
    {
        m=([ ]);
    }
    name=m[get_id(player)];
    if (name)
    {
        player->catch_msg("A thought passes through your mind: "+
            "Your vote against "+CAP(name)+" has failed.\n");
        player->set_hp(0);
        player->do_die(TO);    
        m_delkey(m,get_id(player));
        set_info(VOTES,FAILED,m);    
        set_alarm(60.0,0.0,&inform_finished_votes(player));
        return;
    }
}

public void inform_needed_votes(object player,string * votes)
{
    if (!player)
    {
        return;
    }
    int age=player->query_vamp_age();
    if (age < MINIMUM_VOTE_AGE && player->query_skill(VAMP_FAVOR) < 1000)
    {
        // Requirements are minimum voting age or vamp favor of over 1000
        // This allows older vamps and those who have been really active
        // to vote.        
        set_alarm(60.0,0.0,&inform_finished_votes(player));
        return;
    }
    if (!sizeof(votes) || !can_vote(player))
    {
        set_alarm(60.0,0.0,&inform_finished_votes(player));
        return;
    }
    object yn=clone_object(OBJ_DIR+"yes_no");
    if (yn->get_answer(player,&handle_result(,player,votes[0]),60.0))
    {
    player->catch_msg("A thought passes through your mind: "+
        "One from your Coven has asked that I remove my protection "+
        "from the vampyr "+CAP(votes[0])+". Do you agree that I "+
        "should allow "+CAP(votes[0])+" to be destroyed and "+
        "removed from immortality? (<accept>/<refuse>)\n");
    }
    set_alarm(120.0,0.0,&inform_needed_votes(player,votes[1..]));
}

public void login_player(object player)
{
    string * votes=get_unvoted(player);
    set_alarm(30.0,0.0,&inform_needed_votes(player,votes));
}

