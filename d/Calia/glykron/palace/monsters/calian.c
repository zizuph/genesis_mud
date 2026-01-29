/*      
        This is to be inherited into Calian npcs who guard the palace.
        Based partially on Glykron's original calian npc inherit.

    coder(s):   Maniac & Glykron                        
    history:    
                 5/2/2000 moved in team code from rooms      Maniac
                 3/6/96   made various improvements          Maniac
                10/4/96   call_out --> set_alarm             Maniac
                29/9/95   change in attack handling          Maniac
                27/9/95   special_attack for team fighting   Maniac     
                23/5/95   RANDOM_WORD->RANDOM_NAME           Maniac
                10.5.95   Modifications                      Maniac
                 4.5.95   Corrections                        Maniac
                28.4.95   Warning triggered for Calians when 
                          guild under attack                 Maniac
                28.4.95   Calians return to posts            Maniac
                8.12.94   Created                            Maniac

    purpose:    to make calian npcs guard palace intelligently, 
                by running and forming larger teams when they are 
                outmatched.

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

#pragma save_binary
#pragma strict_types

#include <stdproperties.h>
#include <language.h>
#include <macros.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <ss_types.h>
#include "defs.h"
#include MAP_HEADER
#include RANDOM_HEADER
#include CALIAN_HEADER


inherit "/std/monster";

object *met_list;
int return_to_post_alarm;
int avg;

string *rooms_by_rank = ({ ROOM("light_entrance"),
                           ROOM("light_hall"),
                           ROOM("light_training"),
                           ROOM("light_stairs"),
                           ROOM("light_bronze"),
                           ROOM("light_silver"),
                           ROOM("light_gold"),
                           ROOM("light_white") });
 

/* Standard Calian long description */
string
calian_long()
{
     if (!avg) 
         avg = this_object()->query_average_stat();
     if (avg < 51) 
         return "This Calian is one of the regular guards " +
                "of the Crystalline Palace. " +
                capitalize(this_object()->query_pronoun()) + 
                " doesn't look short on confidence though.\n"; 
     else if (avg < 61)
         return "This Calian is one of the middle ranking guards " +
                "of the Crystalline Palace. " + 
                capitalize(this_object()->query_pronoun()) + 
                " looks pretty tough.\n";
     else if (avg < 71)
         return "This Calian is one of the high ranking guards " +
                "of the Crystalline Palace. " + 
                capitalize(this_object()->query_pronoun()) + 
                " looks very capable indeed.\n";
     else return "This Calian is one of the best guards of the " +
                 "Crystalline Palace. " + 
                 capitalize(this_object()->query_pronoun()) + 
                 " looks dangerously skillful and powerful.\n";
}




/* This is a calian npc */
int 
is_calian_npc()
{
      return 1;
}


int
is_calian(object ob)
{
  if (ob->query_guild_name_occ() == GUILD_NAME) 
      return 1;
  else
      return 0; 
}


/* Set up swarm, maul and move behind */
void
set_calian_skills()
{
     if (!avg) 
         avg = this_object()->query_average_stat();
     set_skill(SS_SWARM, avg - 5);
     set_skill(SS_MAUL, avg - 5); 
     set_skill(SS_MOVE_BEHIND, avg - 5);
     set_skill(SS_AWARENESS, avg - 5); 
}


nomask void
add_calian_soul()
{
    add_cmdsoul(SPECIAL("calian_cmdsoul"));
    update_hooks();
    set_calian_skills(); 
}


void
create_calian()
{
    set_race_name(RANDOM_GOOD_RACE);
}


/* Return to post if not being attacked */
void
return_to_post()
{
    string hr; 

    if (objectp(this_object()->query_attack()))
        return;

    hr = this_object()->query_prop(CALIA_S_NPC_HOME_ROOM); 

    if (stringp(hr)) 
        this_object()->move_living("back home", hr); 
}


/* Return to post if enemy left */
void
notify_enemy_gone(object attacked)
{
    if (return_to_post_alarm) 
         remove_alarm(return_to_post_alarm);
    return_to_post_alarm = set_alarm(240.0, 0.0, return_to_post);
}



nomask void
create_calia_npc()
{
    add_name("calian");
    add_prop(LIVE_I_SEE_DARK, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    seteuid(getuid());
    met_list = ({ });
    clone_object(SPECIAL("calian_shadow"))->shadow_me(this_object(), 
        GUILD_TYPE, GUILD_STYLE, GUILD_NAME);
    clone_object(OBJECT("calian_medallion"))->move(this_object());
    set_alarm(0.1, 0.0, add_calian_soul); 
    set_m_out("rushes away"); 
    set_m_in("rushes in"); 
    set_mm_out("rushes away."); 
    set_mm_in("rushes in.");  
    create_calian(); 
}


void
init_living()
{
    object tp = this_player();
    ::init_living();

    if (interactive(tp) && is_calian(tp))
        tp->add_introduced(query_real_name());
}


void
create_monster()
{
  int g;

  set_adj(RANDOM_ADJS);
  if (random(3)) {
      g = G_MALE;
      set_gender(g);
  }
  else {
      g = G_FEMALE;
      set_gender(g);
  }
  set_name(RANDOM_NAME(g));
  create_calia_npc();
}



nomask string
set_calian_title(string special_title)
{
    string calian_title;

    calian_title = special_title ? special_title : "";
    set_title(calian_title);
}

int
is_unmet(object living)
{
    return member_array(living, met_list) == -1;
}


void
add_introduced(string subj)
{
    object *unmet;

    unmet = filter(FILTER_LIVE(all_inventory(environment(this_object()))), 
                   "is_unmet", this_object());

    if (!sizeof(unmet))
        return 0;

    met_list += unmet;
    set_alarm(1.0, 0.0, &command("introduce me"));
}



/*
 * Function name: try_to_move_behind
 * Description  : If necessary this function tries to make the calian warrior
 *                move behind a team member and he will try to do so until
 *                he succeeds in doing so as long as needed.
 * Coded by     : Mercade of Gondor, debugged & tested by Maniac
 *                Check for re-try move behind added by Maniac
 */
void
try_to_move_behind()
{
    object *team_members;
    object best_member, the_attacker;
    int    best_hp;
    int    i;

    team_members = this_object()->query_team_others();
    best_hp = this_object()->query_hp();
    the_attacker = this_object()->query_attack();

    if (!sizeof(team_members) || !objectp(query_attack()))
        return;

    for (i = 0; i < sizeof(team_members); i++)
        if (environment(this_object()) == environment(team_members[i]) &&
            team_members[i]->query_hp() > best_hp)
        {
             best_member = team_members[i];
             best_hp = best_member->query_hp();
        }

    if (objectp(best_member))
        command("move behind " + best_member->query_real_name());
}


/*
 * Function name: team_fight
 * Description  : This function will allow the calian warrior to use its
 *                team skills and swarm an enemy if possible. Also it will
 *                try to move behind a team-member when necessary.
 * Coded by     : Mercade of Gondor, debugged & tested by Maniac.
 *                Checks for move behind and swarm added by Maniac
 */
void
team_fight()
{
    object attacker;
  
    attacker = this_object()->query_attack();

    /* try to move behind if his hp is low and he's in the front line */
    if ((this_object()->query_hp() < (this_object()->query_max_hp() / 5)) &&
        (attacker->query_attack() == this_object()))
        try_to_move_behind();

    /* Every so often, try to swarm if not in the front line */
    if (attacker->query_attack() != this_object())
        command("swarm");
    else
        command("maul"); 
}



/* Function: outmatched_by()
 * Returns 1 if the team which this npc is in is does not stand
 * a good chance of defeating the player who just attacked, 0 if the
 * player who attacked is not too tough.
 */
int
outmatched_by(object attacker)
{
    int team_strength, attacker_strength, i;
    object *the_team;
    
    attacker_strength = attacker->query_average_stat();
    team_strength = 0;

    the_team = this_object()->query_team_others();
    if (sizeof(the_team)) {
        if (sizeof(the_team) >= 4)
            return 0;
        the_team += ({ this_object() });
        for (i=0; i < sizeof(the_team); i++) 
            if (sizeof(the_team[i]->query_team()))
                team_strength += the_team[i]->query_average_stat() - 5;
            else
                team_strength += (the_team[i]->query_average_stat() / 4);
    }
    else
       team_strength = query_average_stat() - 10;

    if (attacker_strength > team_strength) 
        return 1;
    else
        return 0; 
}



/* 
 * Choose the most appropriate room to retreat to. If there
 * isn't any appropriate room, return "".
 */
string
choose_best_room()
{
    int i, j, good_room;
    object a_room;
    
    i = member_array((file_name(environment(this_object())) + ".c"), 
                     rooms_by_rank); 
    if (i == -1) 
        return "";

    good_room = -1;
    j = i + 1; 

    /* try to retreat to rooms with better npcs first */ 
    while ((j < sizeof(rooms_by_rank)) && (good_room < 0)) {
        a_room = find_object(rooms_by_rank[j]); 
        if (!objectp(a_room)) 
            good_room = j;
        else if (sizeof(a_room->query_calian_npcs()))  
                good_room = j;
        j++;
    }
    if (good_room > -1) 
        return rooms_by_rank[good_room];

    /* if that failed, try to retreat to rooms with worse npcs. */ 
    j = i - 1;
    while ((j > -1) && (good_room < 0)) {
        a_room = find_object(rooms_by_rank[j]); 
        if (!objectp(a_room)) 
            good_room = j;
        else if (sizeof(a_room->query_calian_npcs()))  
                good_room = j;
        j--;
    }

    if (good_room > -1) 
        return rooms_by_rank[good_room];

    return "";
}



/* 
 * Retreat to a place with more Calian npcs if possible  
 * and create a stronger force. 
 */
void
retreat()
{
    object *team;
    string br;
    int i;

    br = choose_best_room(); 

    if (!strlen(br)) 
        return;

    team = this_object()->query_team();

    this_object()->move_living("retreating", br); 
    for (i = 0; i < sizeof(team); i++) 
        team[i]->move_living("retreating", br); 
}


/* React to an attack, other team members who aren't fighting will 
   attack the attacking player.  */
void
react_attack(object attacker)
{
    object *team_others;
    int i;

    team_others = this_object()->query_team_others();
    for (i = 0; i < sizeof(team_others); i++) 
        if (!objectp(team_others[i]->query_attack()))
            team_others[i]->command("assist"); 
}


/* Only team leaders or soloers should retreat. */ 
int
i_can_retreat()
{
    if (sizeof(this_object()->query_team()))  
        return 1;

    if (!sizeof(this_object()->query_team_others())) 
        return 1;

    return 0;
}



/* Project out a warning to Calians. */ 
void
do_warn(object attacker)
{
    string pn, s;

    seteuid(getuid());
    if (!(attacker->query_wiz_level()) &&
        !(sscanf(attacker->query_name(), "%sjr", s) == 1)) {
        if (is_unmet(attacker))
             pn = LANG_ADDART(attacker->query_nonmet_name());
        else
             pn = capitalize(attacker->query_real_name());
        WARNING_SIGNAL_OBJECT->another_attack(this_object()->query_name(),
          (environment()->short() + " - our guild is under attack by " + 
           pn + "!"));
    }
}


/* 
 *  This function is called during combat by the cbase.
 *  We use it here to control everything from retreat to
 *  team fighting. 
 */
int
special_attack(object victim)
{
    if (i_can_retreat() && outmatched_by(victim)) 
        retreat();  

    react_attack(victim); 

    do_warn(victim); 

    team_fight();
    return 0;
}


/* 
 * Choose an appropriate leader for a set of calian npcs.
 * The best choice is considered the one with tbe best
 * average stat. The default if they're all the same 
 * strength is the first object in the npc array.
 */
object
identify_leader(object *npcs)
{
    int i, best_npc, best_avg_stat;
    object leader;

    best_npc = 0;
    best_avg_stat = npcs[0]->query_average_stat();

    for (i = 1; i < sizeof(npcs); i++) {
        if (npcs[i]->query_average_stat() > best_avg_stat) {
             best_npc = i;
             best_avg_stat = npcs[i]->query_average_stat();
        }
    }
    return npcs[best_npc];
}


/*
 * Disperse the team that the specified npc is in. 
 */ 
void
disperse_team(object npc)
{
     int i;
     object *team;

     (npc->query_leader())->team_leave(npc);

     team = npc->query_team();
     for (i = 0; i < sizeof(team); i++)
         npc->team_leave(team[i]);
}


/* 
 * Organise a number of npcs into a team with leader 'leader' 
 */
void
organise_team(object *npcs, object leader)
{
    int i;

    /* get rid of any other teams */
    for (i = 0; i < sizeof(npcs); i++)
        disperse_team(npcs[i]);

    /* Join up the new team */
    for (i = 0; i < sizeof(npcs); i++)
       if (npcs[i] != leader)
           leader->team_join(npcs[i]);
}


/* 
 * Join this npc in a team. If it would be the leader of the team, 
 * disperse the old one and form a new one with this npc as leader,
 * otherwise just join the existing one. 
 */
void
join_npc_team(object *npcs)
{
    object leader;

    if (!sizeof(npcs))
        return; 

    leader = identify_leader(npcs);
    if (leader == this_object())
        organise_team(npcs, leader);
    else {
        disperse_team(this_object()); 
        leader->team_join(this_object());
    }
}


/* 
 * Update the specified npcs to no longer consider this npc as part
 * of their team. 
 */
void
update_npc_team(object *npcs)
{
    if (sizeof(npcs))
        organise_team(npcs, identify_leader(npcs));
}


/* 
 * Called when this npc has just entered a new environment 
 * to set up a team.
 */ 
void
just_changed_environment(object dest, object old)
{
    if (sizeof(query_team()))
        update_npc_team(filter(all_inventory(old), 
            &->is_calian_npc())); 
    join_npc_team(
        filter(all_inventory(environment()), &->is_calian_npc())); 
}


/* Called when this npc enters a new environment */ 
void
enter_env(object dest, object old)
{
    ::enter_env(dest, old); 
    set_alarm(0.0, 0.0, &just_changed_environment(dest, old)); 
}


void
remove_object()
{
    object env = environment(); 

    seteuid(getuid());
    RANDOM_FILE->retract_random_name(this_object()->query_real_name());
    if (objectp(env) && sizeof(query_team())) 
        update_npc_team(filter(all_inventory(env), 
                           &->is_calian_npc()) - ({ this_object() })); 
    ::remove_object();
}
