#pragma strict_types
 
inherit "/std/monster";
inherit "/d/Wiz/quetzl/open/react_trigs";
 
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <state_desc.h>
#include <composite.h>
#include <formulas.h>
#include <cmdparse.h>
#include "/d/Genesis/login/login.h"
 
#define ADJGIVE "/d/Wiz/quetzl/adj_getter"
 
int query_align_for_title(string title);
void enable_intro();
void create_rmonster();
void make_scars(int i);
 
static string race;
static mapping bist = ([]);
    static int scars,
           prestige;
static mapping subs = ([]);
 
/*
 * Function name: set_bit
 * Description:   sets quest bits so that special items may be used by npc.
 * Arguments:     domain - the domain the bit is in
 *                group - what group, bit - what bit number
 */
 
public void
set_bit(string domain, int group, int bit)
{
    if (!pointerp(bist[domain]))
        bist += ([ domain: allocate(5) ]);
    if (!pointerp(bist[domain][group]))
        bist[domain][group] = allocate(20);
    bist[domain][group][bit] = 1;
}
 
/*
 * Function name: clear_bit
 * Description:   Clears the selected quest bit
 * Arguments:     same as set_bit
 */
 
public void
clear_bit(string domain, int group, int bit)
{
    if (!pointerp(bist[domain]))
        return;
    if (!pointerp(bist[domain][group]))
        return;
    bist[domain][group][bit] = 0;
}
 
/*
 * Function name: test_bit
 * Description:   check to see if a bit is set
 * Arguments:     same as set_bit and clear_bit
 * Returns:       1 if bit is set
 */
 
public int
test_bit(string domain, int group, int bit)
{
    if (!pointerp(bist[domain]))
        return 0;
    if (!pointerp(bist[domain][group]))
        return 0;
    return bist[domain][group][bit];
}
 
/*
 * Function name: set_race_real
 * Description:   Makes the npc truly this race
 * Arguments:     arg - the race name
 */
 
public void
set_race_real(string arg)
{
    race = arg;
}
 
/*
 * Function name: query_race
 * Description:   returns the race - always the same as query_race_name()
 * Returns:       the race
 */
 
public string
query_race()
{
    return race;
}
 
/*
 * Function name: set_race_name
 * Description:   set the race name and set the real race name
 * Arguments:     arg - the name of the race
 */
 
public void
set_race_name(string arg)
{
    ::set_race_name(arg);
    set_race_real(arg);
}
 
/*
 * Function name: set_height_title
 * Description:   adds the appropriate props for a specific race's height
 * Arguments:     title - the height title (e.g. tall, short)
 */
 
public void
set_height_title(string title)
{
    int i;
    i = member_array(title, HEIGHTDESC);
    if (i < 0)
        return;
    if (member_array(race, RACES) == -1)
        return;
    add_prop(CONT_I_HEIGHT, RACEATTR[race][0] * SPREAD_PROC[i] / 100);
    return;
}
 
/*
 * Function name: set_width_title
 * Description:   set the height and volume props to yield a specific width
 *                description for current race, only pc races
 * Arguments:     title - the desired height description
 */
 
public void
set_width_title(string title)
{
    int i;
    i = member_array(title, WIDTHDESC);
    if (i < 0)
        return;
    if (member_array(race, RACES) == -1)
        return;
    i = RACEATTR[race][1] * SPREAD_PROC[i] / 100 * 1000;
    add_prop(CONT_I_WEIGHT, i);
    add_prop(CONT_I_VOLUME, i);
    return;
}
 
/*
 * Function name: create_monster
 * Description:   the construction function, also adds skin
 */
public void
create_monster()
{
    add_leftover("/d/Roke/common/carisca/obj/skin", "skin", 1, "", 1, 1);
    create_rmonster();
}
 
/*
 * Function name: race_sound
 * Description:   returns the communication sound from this object to ob
 * Arguments:     ob - the object we are communicating with.
 * Returns:       the sound
 */
 
public string
race_sound(object ob)
{
    reset_euid();
    if (!RACESOUND[race])
        return "says";
    if (!RACESOUND[race][ob->query_race()])
        return "says";
    return RACESOUND[race][ob->query_race()];
}
 
/*
 * Function name: communicate
 * Description:   say something to someone else
 * Arguments:     str - what to say
 * Returns:       always 1
 */
 
public int
communicate(string str)
{
    int i;
    object *peop;
    if (extract(query_verb(), 0, 0) == "'")
        if (strlen(str))
            str = extract(query_verb(), 1) + " " + str;
        else
            str = extract(query_verb(), 1);
    peop = FILTER_LIVE(all_inventory(environment()));
    i = sizeof(peop);
    while(i--)
        peop[i]->catch_msg(QCTNAME(this_object()) + " " + race_sound(peop[i]) +
            ": " + str + "\n");
    return 1;
}
 
/*
 * Function name: title_stats
 * Description:   give the stat value for a mortal experience title
 * Arguments:     title - the desired title
 * Returns:       the necessary stat average
 */
 
public int
title_stats(string title)
{
    int i, high, low;
    i = member_array(title, SD_AV_TITLES);
    if (i == -1)
        return 7 + random(5);
    low = 100 * i / sizeof(SD_AV_TITLES);
    high = 100 * (i + 1) / sizeof(SD_AV_TITLES);
    i = high - low;
    return low + random(i) + 1;
}
 
/*
 * Function name: set_stats_to_title
 * Description:   sets all the stats to the average needed for an exp title
 * Arguments:     title - the desired exp title
 */
 
public void
set_stats_to_title(string title)
{
    int i;
    i = title_stats(title);
    set_stats(({ i, i, i, i, i, i }));
    stats_to_acc_exp();
    update_acc_exp();
    refresh_mobile();
}
 
/*
 * Function name: set_stats_to_title_r
 * Description:   set that stats to one in a range of titles
 * Arguments:     title1, title2 - the range of titles
 */
 
public void
set_stats_to_title_r(string title1, string title2)
{
    int i, j;
    i = title_stats(title1);
    j = title_stats(title2);
    i = i + (random(j + 1));
    set_stats(({ i, i, i, i, i, i }));
    stats_to_acc_exp();
    update_acc_exp();
    refresh_mobile();
}
 
/*
 * Function name: shift_stats
 * Description:   change the stat values based on a set of preferences -
 *                retroactive, the most this will alter average stat is
 *                + 5/6
 * Arguments:     prefs - array of 6 ints of stat preferences
 */
 
public void
shift_stats(int *prefs)
{
    int i, a;
    set_learn_pref(prefs);
    i = sizeof(query_learn_pref(-1));
    a = query_average_stat();
    while(i--)
        set_base_stat(i, MAX(1, query_learn_pref(i) * 6 * a / 100));
    stats_to_acc_exp();
    refresh_mobile();
}
 
/*
 * Function name: set_pc_adj
 * Description:   sets an adjective available to pcs.
 * Arguments:     type - one or more of the types(TYPE TYPE), defined in
 *                /d/Genesis/login/attributes, or ALL
 * Returns:
 */
 
public varargs void
set_pc_adj(string type)
{
    if (!strlen(type))
        type = "ALL";
    reset_euid();
    set_adj(ADJGIVE->get_adj(type));
}
 
/*
 * Function name: add_pc_adj
 * Description:   same as set_pc_adj, but adjective is added instead of set.
 * Arguments:     same as set_pc_adj
 */
 
public varargs void
add_pc_adj(string type)
{
    if (!strlen(type))
        type = "ALL";
    reset_euid();
    add_adj(ADJGIVE->get_adj(type));
}
 
/*
 * Function name: set_align_to_title
 * Description:   sets the alignment to an alignment description
 * Arguments:     title - the desired description
 */
 
public void
set_align_to_title(string title)
{
    set_alignment(query_align_for_title(title));
}
 
/*
 * Function name: set_align_to_title_r
 * Description:   set the alignment somewhere in the range
 * Arguments:     title1, title2 - the two ends of the range
 */
 
public void
set_align_to_title_r(string title1, string title2)
{
    int a, b, diff;
    a = query_align_for_title(title1);
    b = query_align_for_title(title2);
    set_alignment(MIN(a, b) + random(ABS(a - b) + 1));
}
 
/*
 * Function name: query_align_for_title
 * Description:   returns an alignment number which will yield the desired
 *                alignment description.
 * Arguments:     title - the desired alignment description
 * Returns:       the alignment necessary
 */
 
public int
query_align_for_title(string title)
{
    int i, align, step, evil;
    string *a_names;
    if (member_array(title, SD_EVIL_ALIGN) == -1)
        if (member_array(title, SD_GOOD_ALIGN) == -1)
        {
            evil = random(2);
            i = 0;
            a_names = ({ SD_GOOD_ALIGN, SD_EVIL_ALIGN })[evil];
        }
        else
        {
            evil = 0;
            i = member_array(title, SD_GOOD_ALIGN);
            a_names = SD_GOOD_ALIGN;
        }
    else
        if (member_array(title, SD_GOOD_ALIGN) == -1)
        {
            evil = 1;
            i = member_array(title, SD_EVIL_ALIGN);
            a_names = SD_EVIL_ALIGN;
        }
        else
        {
            evil = random(2);
            i = 0;
            a_names = ({ SD_GOOD_ALIGN, SD_EVIL_ALIGN })[evil];
        }
 
    step = F_KILL_NEUTRAL_ALIGNMENT * 100 / sizeof(a_names);
    align = i * step + random(step);
    return (evil ? -align : align);
}
 
/*
 * Function name: return_introduce
 * Description:   introduces to the player introduced if the player does not
 *                know them and is interactive.
 * Arguments:     s1, s2 - s1 is all in the intro string before the word
 *                introduces, s2 is all after.
 * Returns:       1 if a real intro of a player, otherwise 0
 */
 
public int
return_introduce(string s1, string s2)
{
    object who;
    string *stuff;
    stuff = explode(s2, " as:\n");
    if (sizeof(stuff) != 2)
        return 0;
    stuff = explode(stuff[1], " ");
    who = find_player(lower_case(stuff[0]));
    if (!who)
        who = find_player(lower_case(stuff[1]));
    if (!who)
        return 0;
    if (who->query_met(this_object()))
        return 1;
    stuff[0] = "introduce myself to " + who->query_real_name();
    set_alarm(1.0, 0.0, "command", stuff[0]);
    return 1;
}
 
/*
 * Function name: enable_intro
 * Description:   adds the necessary trig for introductions
 */
public void
enable_intro()
{
    trig_new("%s 'introduces' %s", "return_introduce");
}
 
/*
 * Function name: disable_intro
 * Description:   removes the intro trigger.
 */
 
public void
disable_intro()
{
    trig_delete("%s 'introduces' %s");
}
 
/*
 * Function name: reason_not_attack
 * Description:   returns an int signifying why this object can't attack victim
 * Arguments:     victim - the object to attack
 * Returns:       1 - room prevents it, 2 - object prevents it,
 *                3 - not enough dis, 0 - can attack normally
 */
 
public int
reason_not_attack(object victim)
{
    if (environment(this_object())->query_prop(ROOM_M_NO_ATTACK))
        return 1;
    if (victim->query_prop(OBJ_M_NO_ATTACK))
        return 2;
    if (!F_DARE_ATTACK(this_object(), victim))
        return 3;
    return 0;
}
 
/*
 * Function name: react_to_attack
 * Description:   What shall we do when attacked?
 * Arguments:     enemy - who attacked us.
 */
public void
react_to_attack(object enemy)
{
    object *team;
    team = (object *)query_team_others();
    if (!sizeof(team))
        return;
    team->help_team(enemy, this_object());
}
 
/*
 * Function name: attacked_by
 * Description:   set_alarm for react_to_attack, this is called when attacked
 * Arguments:     enemy - who attacked us
 */
 
public void
attacked_by(object enemy)
{
    set_alarm(0.3, 0.0, "react_to_attack", enemy);
}
 
/*
 * Function name: help_how
 * Description:   how do we help out an attacked teammate?
 * Arguments:     enemy - the enemy, friend - our teammate
 */
 
public void
help_how(object enemy, object friend)
{
    command("kill " + enemy->query_real_name());
}
 
/*
 * Function name: help_team
 * Description:   sets alarm for help_how
 * Arguments:     enemy - who attacked our teammate, friend - the teammate
 * Returns:
 */
 
public void
help_team(object enemy, object friend)
{
    set_alarmv(0.3, 0.0, "help_how", ({ enemy, friend }));
}
 
/*
 * Function name: create_rmonster
 * Description:   redefine this - this is an example monster
 */
 
public void
create_rmonster()
{
    set_race_name(RACES[random(sizeof(RACES))]);
    set_height_title(HEIGHTDESC[random(sizeof(HEIGHTDESC))]);
    set_width_title(WIDTHDESC[random(sizeof(WIDTHDESC))]);
    set_pc_adj("ALL");
    add_pc_adj("ALL");
    set_align_to_title_r("evil", "good");
    enable_intro();
    set_stats_to_title_r("apprentice", "veteran");
    set_gender(random(2));
    make_scars(random(3));
    shift_stats(({ 1 + random(2), 1 + random(2), 1 + random(2), 1 + random(2),
        1 + random(2), 1 + random(2) }));
}
 
/*
 * Function name: make_scar
 * Description:   give us another scar, taken from the death sequence.
 */
 
public void
make_scar()
{
    int i;
    i = query_scar();
    if (query_average_stat() < 10)
       return;
    set_scar(query_scar() | (1 << random(F_MAX_SCAR)));
    if (i != query_scar())
        scars++;
}
 
/*
 * Function name: num_scar
 * Description:   necessary for scar subloc
 * Returns:       the number of scars we have
 */
 
public int
num_scar()
{
    return scars;
}
 
/*
 * Function name: do_die
 * Description:   reteam our members if we were a leader
 * Arguments:     killer - who killed us
 */
 
public void
do_die(object killer)
{
    int i;
    object leader, *team;
    team = (object *)query_team_others();
    if (!query_leader() && sizeof(team))
    {
        i = sizeof(team);
        while(i--)
            team[i]->set_leader(0);
        i = sizeof(team) - 1;
        leader = team[i];
        while(i--)
            leader->team_join(team[i]);
    }
    ::do_die(killer);
}
 
/*
 * Function name: desc_scar
 * Description:   return a description of the scars we have for subloc.
 * Returns:       a description of our scar(s)
 */
 
public string
desc_scar()
{
    int i, j, scar;
    string *scar_desc, *my_scars;
    scar_desc = F_SCAR_DESCS;
    scar = query_scar();
    j = 1;
    my_scars = 0;
    while(i < F_MAX_SCAR)
    {
        if (scar & j)
        {
            if (my_scars)
                my_scars = my_scars + ({ scar_desc[i] });
            else
                 my_scars = ({ scar_desc[i] });
    }
    j *= 2;
    i += 1;
    }
    if (!my_scars) return 0;
    if (sizeof(my_scars) == 1)
        return my_scars[0];
    if (sizeof(my_scars) == 2)
        return implode(my_scars, " and ");
    return implode(slice_array(my_scars, 0, sizeof(my_scars) - 2), ", ") +
        " and " + my_scars[sizeof(my_scars) - 1];
}
 
/*
 * Function name: make_scars
 * Description:   make up to a certain number of scars
 * Arguments:     i - the number of new scars to make
 * N.B.:          not all calls to make_scar result in a new scar, thus it is
 *                possible to get fewer scars than i, also npcs with average
 *                stat below 10 will not receive scars
 */
 
public void
make_scars(int i)
{
    while (i--)
        make_scar();
}
 
/*
 * Function name: add_a_sub
 * Description:   give us a new subloc
 * Arguments:     name - the subloc name, sub - the string to use: if the
 *                first character of sub is # it will be treated as a 
 *                function to be called when the subloc is need, it should
 *                return the string.
 */
 
public void
add_a_sub(string name, string sub)
{
    if (subs[name])
        subs[name] = sub;
    else
    {
        add_subloc(name, this_object());
        subs += ([ name: sub ]);
    }
}
 
/*
 * Function name: delete_a_sub
 * Description:   remove one of the subs set with add_a_sub
 * Arguments:     sub - the name of the subloc to remove
 */
 
public void
delete_a_sub(string sub)
{
    if (!subs[sub])
        return;
    subs = m_delete(subs, sub);
}
 
/*
 * Function name: show_subloc
 * Description:   show a specific subloc
 * Arguments:     subloc - the name, me - who am I?, for_who - who are you?
 * Returns:       the describing string
 */
 
public string
show_subloc(string subloc, object me, object for_who)
{
    if (!subs[subloc])
        return "";
    if (extract(subs[subloc], 0, 0) == "#")
        return call_otherv(this_object(), extract(subs[subloc], 1),
            ({ me, for_who }));
    return subs[subloc];
}
 
/*
 * Function name: query_knight_prestige
 * Description:   return the value for a knights prestige, used by Krynn.
 * Returns:       a number calculated by the below formula, if there is a
 *                better formula, let me know.
 */
 
public int
query_knight_prestige()
{
    int i, j;
    j = query_alignment();
    if (j > 0)
        return (j > 200 ? -1 : 0);
    i = query_average_stat();
    return i * i * j * -1 / 10000;
}

/*
 * Function name: pop_adj
 * Description:   just a kludge to get adjectives.
 */

public string
pop_adj(string type)
{
    reset_euid();
    return ADJGIVE->get_adj(type);
}

/*
 * Function name: add_skill
 * Description:   add a skill and set it to a decent value
 * Arguments:     skill - the skill
 * Returns:       the value the skill was set to
 */

public int
add_skill(int skill)
{
    int i;
    i = query_average_stat() - 5 + random(10);
    set_skill(skill, i);
    return i;
}

/* Function name: add_skills
 * Description:   add an array of skills
 * Arguments:     skills - the skill array
 * Returns:       an array of values set
 */

public int *
add_skills(int *skills)
{
    int i;
    i = sizeof(skills);
    while(i--)
        skills[i] = add_skill(skills[i]);
    return skills;
}

/*
 * Function name: tell_watcher
 * Description:   tell those watching a fight a message
 * Arguments:     str - the string, enemy - the enemy, exclude - don't tell
 */

public void
tell_watcher(string str, object enemy, mixed exclude)
{
    int i;
    object *whom;
    if (!pointerp(exclude))
        exclude = ({ exclude });
    exclude += ({ enemy });
    exclude -= ({ 0 });
    whom = FILTER_LIVE(all_inventory(environment(this_object())));
    whom -= exclude + ({ this_object() });
    i = sizeof(whom);
    while(i--)
        if (whom[i]->query_see_blood())
            whom[i]->catch_msg(str);
}
