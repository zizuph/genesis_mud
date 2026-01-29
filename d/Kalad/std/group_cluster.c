/* This code is stolen/borrowed by Carnak, so he is the
 * creator of all this.
 * This code allows for npcs to team with each other.
 */

#include <macros.h>

/* Global Variables */
string *gProspectiveGroup = ({ });
int     gGroupMax   = 5,
        gNoGroup    = 0;

/* 
 * Function name:   hook_group_join_refuse
 * Description:     Prints the message for a living object being refused to join
 * Arguments:       (object) who - The living object trying to join
 *                  (object) leader - The current leader of the cluster
 * Returns:         Nothing
 */
public void
hook_group_join_refuse(object who, object leader)
{
} /* hook_group_join_refuse */

/* 
 * Function name:   hook_group_max_capacity
 * Description:     Prints the message for the group reaching max capacity
 * Arguments:       (object) who - The living object trying to join the cluster
 *                  (object) leader - The current leader of the cluster
 * Returns:         Nothing
 */
public void
hook_group_max_capacity(object who, object leader)
{
} /* hook_group_cluster_full */

/* 
 * Function name:   hook_member_has_joined_cluster
 * Description:     Prints the message for a living object joining a group
 * Arguments:       (object) who - The living object joining the cluster
 *                  (object) leader - The current leader of the cluster
 * Returns:         Nothing
 */
public void
hook_member_has_joined_cluster(object who, object leader)
{
    who->tell_watcher(QCTNAME(who) + " joined the team of " + QTNAME(leader)
    + ".\n");
} /* hook_member_has_joined_cluster */

/* 
 * Function name:   hook_cluster_leader_has_changed
 * Description:     Prints the message for the change of leaders
 * Arguments:       (object) new_leader - The leader that will replace the old
 *                  (object) old_leader - The current leader being replaced
 * Returns:         Nothing
 */
public void
hook_cluster_leader_has_changed(object new_leader, object old_leader)
{
    new_leader->tell_watcher(QCTNAME(new_leader) + " became the leader of "
    + QTNAME(old_leader) + "'s team.\n");
} /* hook_cluster_leader_has_changed */

/* 
 * Function name:   hook_member_has_left_cluster
 * Description:     Prints the message for a member leaving the cluster
 * Arguments:       (object) who - The member leaving the cluster
 *                  (object) leader - The current leader of the group
 * Returns:         Nothing
 */
public void
hook_member_has_left_cluster(object who, object leader)
{
    who->tell_watcher(QCTNAME(who) + " leaves the team of " + QTNAME(leader)
    + ".\n", ({ leader, who }));
} /* hook_member_has_left_cluster */

/* 
 * Function name:   hook_leader_has_left_cluster
 * Description:     Prints the message for the leader leaving the cluster
 * Arguments:       (object) new_leader - The leader that will replace the old
 *                  (object) old_leader - The current leader being replaced
 * Returns:         Nothing
 */
public void
hook_leader_has_left_cluster(object new_leader, object old_leader)
{
    old_leader->tell_watcher(QCTNAME(old_leader) + " leaves "
    + old_leader->query_possessive() + " team, appointing "
    + QTNAME(new_leader) + " as the new leader.\n",
    ({ new_leader, old_leader }));
} /* hook_leader_has_left_cluster */

/* 
 * Function name:   query_group_cluster_max
 * Description:     Returns the cluster_group status, if active or inactive
 * Arguments:       None
 * Returns:         (status) 1 - active, 0 - inactive
 */
public int
query_group_cluster_max()
{
    return gGroupMax;
} /* query_group_cluster_max */

/*
 * Function name:   set_group_cluster_max
 * Description:     Sets the maximum amount of allowed members in the group,
 *                  this does not affect non-grouped cluster members.
 * Arguments:       (int) group - Any positive integer
 * Returns:         Nothing
 */
public void
set_group_cluster_max(int group)
{
    gGroupMax = group;
} /* set_group_cluster_max */

/* 
 * Function name:   query_no_cluster_group
 * Description:     Returns the cluster_group status, if active or inactive
 * Arguments:       None
 * Returns:         (status) 1 - active, 0 - inactive
 */
public int
query_no_cluster_group()
{
    return gNoGroup;
} /* query_no_cluster_group */

/*
 * Function name:   set_no_cluster_group
 * Description:     Determines if the living object should form a group. If it
 *                  is active and prospective_cluster is set, it will keep the
 *                  other present living objects matching the prospects in mind
 *                  when it comes to assisting and beneficial abilities.
 * Arguments:       (status) value - either 1 for active or 0 for inactive
 * Returns:         Nothing
 */
public void
set_no_cluster_group(status value)
{
    gNoGroup = value;
} /* set_no_cluster_group */

/* 
 * Function name:   query_prospective_cluster
 * Description:     Returns the prospective group members
 * Arguments:       None
 * Returns:         (string *) - string array of prospects
 */
public string *
query_prospective_cluster()
{
    return gProspectiveGroup + ({});
} /* query_prospective_cluster */

/*
 * Function name:   set_prospective_cluster
 * Description:     Sets the prospects with which to form a group, if set and
 *                  no_cluster_group has been set to 1, it will not form a party
 *                  but will have them in mind when it comes to assisting and
 *                  beneficial abilities.
 * Arguments:       (mixed) str - either a string or an array of strings
 * Returns:         Nothing
 */
public void
set_prospective_cluster(mixed str)
{
    if (!str)
        return;
    
    if (stringp(str))
        str = ({ str });
    
    if (pointerp(str))
        gProspectiveGroup = str;
} /* set_prospective_cluster */

/*
 * Function name:   set_group_cluster_leader
 * Description:     Replaces the specified or current leader with specified
 *                  living, can consume another team if who is a leader.
 * Arguments:       (object) who - living object to make leader
 *                  (object) leader - optional leader to replace
 * Returns:         (status) 1 - success, 0 - failure
 */
public varargs status
set_group_cluster_leader(object who, object leader)
{
    object *members;
    
    if (!objectp(who))
        return 0;
    
    if (!objectp(leader) && !objectp(leader = who->query_leader()))
        return 0;
    
    if (!sizeof(members = leader->query_team()))
        return 0;
    
    /* Fail if who is not leader and the leader to replace isnt who's leader */
    if (objectp(who->query_leader()) && leader != who->query_leader())
        return 0;
    
    /* Remove the members from the current leaders team */
    foreach(object member: members)
    {
        leader->team_leave(member);
    }
    
    /* Replace who with leader in the members list */
    members += ({ leader });
    members -= ({ who });
    
    /* Add the members to the new leader */
    foreach(object member: members)
    {
        who->team_join(member);
    }
    
    return 1;
} /* set_group_cluster_leader */

/*
 * Function name:   add_to_group_cluster
 * Description:     Adds the living object to the party and cluster
 * Arguments:       (object) who - living object to add
 * Returns:         Nothing
 */
static void
add_to_group_cluster(object who)
{
    object *members = ({}),
           *cluster = ({}),
            cluster_ob;
    
    if (!objectp(who) || environment(who) != environment(this_object()))
        return;
    
    if (sizeof(who->query_team_others()))
        return;
    
    members = this_object()->query_team() + ({ this_object() });
    
    foreach(object member: members)
    {
        if (who->query_not_accept_member(member) ||
            member->query_not_accept_member(who))
            continue;
        
        cluster += ({ member });
    }
    
    if (sizeof(cluster) < sizeof(members))
    {
        /* One or more members in the target team resulted in unacceptable
         * team members
         */
        hook_group_join_refuse(who, this_object());
        return;
    }
    
    if (sizeof(this_object()->query_team_others()) >= gGroupMax)
    {
        hook_group_max_capacity(who, this_object());
        return;
    }
    
    if (!gNoGroup)
    {
        this_object()->team_join(who);
        
        /* Resolves the highest average of the joining or the leading entity */
        if (who->query_average_stat() > this_object()->query_average_stat() &&
            set_group_cluster_leader(who, this_object()))
        {
            hook_cluster_leader_has_changed(who, this_object());
            return;
        }
        
        hook_member_has_joined_cluster(who, this_object());
    }
} /* add_to_group_cluster */

/*
 * Function name:   leave_group_cluster
 * Description:     Removes the living object from the group and cluster.
 * Arguments:       (object) who - living object to remove
 *                  (object) new_leader - optional new leader
 *                  (int) silent - silences the hooks, added for do_die
 * Returns:         (status) 1 - success, 0 - failure
 */
public varargs status
leave_group_cluster(object who, object new_leader, int silent = 0)
{
    object cluster, *members = ({});
    
    if (!objectp(who))
        return 0;
    
    if (!sizeof(members = who->query_team()))
    {
        if (!objectp(new_leader = who->query_leader()))
            return 0;
        
        /* Silent for death */
        if (!silent)
            hook_member_has_left_cluster(who, new_leader);
        
        new_leader->leave_team(who);
        return 1;
    }
    
    if (!objectp(new_leader))
    {
        foreach(object member: members)
        {
            if (member->query_average_stat() > members[0]->query_average_stat())
                members[0] = member;
        }
        
        new_leader = members[0];
    }
    
    if (!set_group_cluster_leader(new_leader, who))
        return 0; /* Log this? */
    
    /* Silent for death */
    if (!silent)
        hook_leader_has_left_cluster(who, new_leader);
    
    new_leader->leave_team(who);
    return 1;
} /* leave_group_cluster */

/*
 * Function name:   init_group_cluster
 * Description:     Called upon meeting another living from the init_living,
 *                  this_player() is the met living.
 * Arguments:       None
 * Returns:         Nothing
 */
public void
init_group_cluster()
{
    int     Prospects;
    object  cluster;
    
    if (interactive(this_player()) || !environment(this_object()) ||
        objectp(this_object()->query_leader()) ||
        objectp(this_player()->query_leader()) ||
        !sizeof(gProspectiveGroup) || gNoGroup)
        return;
    
    // Merge teams if they dont surpass the limit.
    if (sizeof(this_player()->query_team()) && sizeof(this_object()->query_team()))
    {
        object  new_leader = this_player(),
                old_leader = this_object(),
               *members = ({}),
               *cluster = ({});
        int     cluster1, cluster2;
        
        cluster1 = sizeof(this_player()->query_team_others());
        cluster2 = sizeof(this_object()->query_team_others());
        
        // switch leader based on average
        if ((this_player()->query_average_stat() + cluster1) <
            (this_object()->query_average_stat() + cluster2))
        {
            new_leader = this_object();
            old_leader = this_player();
        }
        
        members = old_leader->query_team() + ({ old_leader });
    
        foreach(object member: members)
        {
            if (new_leader->query_not_accept_member(member) ||
                member->query_not_accept_member(new_leader))
                continue;
        
            cluster += ({ member });
        }
    
        // One or more members in the target team resulted in unacceptable
        // team members
        if (sizeof(cluster) < sizeof(members))
            return;
        
        if ((cluster1 + cluster2) <= new_leader->query_group_cluster_max())
            new_leader->set_group_cluster_leader(new_leader, old_leader);
        
        return;
    }
    
    Prospects = sizeof(gProspectiveGroup);
    
    while(Prospects--)
    {
        if (this_player()->id(gProspectiveGroup[Prospects]))
        {
            add_to_group_cluster(this_player());
            break;
        }
    }
} /* init_group_cluster */