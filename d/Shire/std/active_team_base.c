/*
 */

inherit "/std/monster.c";
inherit "/d/Shire/std/group_cluster.c";

#include <macros.h>

/* Global Variables */
mapping specials        = ([]);
string *active_souls    = ({}),
       *active_shadows  = ({});
object  active_living;

/*
 * Function name:   safely_load_master_file
 * Description:     This safely loads the master file if it hasn't already
 *                  been loaded. Otherwise, it just returns the existing
 *                  master file. If the file is not loadable, then it
 *                  simply returns 0
 * Argument:        Filename of the file to load
 * Returns:         (object)  : Loaded master file
 */
public object
safely_load_master_file(string filename)
{
    object master_obj;
    if (!objectp(master_obj = find_object(filename)))
    {
        LOAD_ERR(filename);
        master_obj = find_object(filename);
    }
    
    return master_obj;
} /* safely_load_master_file */

/*
 * Function name:   query_specials
 * Description:     Returns the living objects specials.
 * Argument:        None
 * Returns:         (string *) : String array of specials
 */
public string *
query_specials()
{
    if (!m_sizeof(specials))
        return ({});

    return m_indexes(specials);
} /* query_specials */

/*
 * Function name:   set_specials
 * Description:     Sets the living objects specials.
 * Argument:        (mapping) Mapping of specials
 *                            index - ability name
 *                            value - ability filename
 * Returns:         Nothing
 */
public varargs void
set_specials(mapping special)
{
    if (!mappingp(special))
        special = ([]);
    
    specials = special;
} /* set_specials */

/*
 * Function name:   add_special
 * Description:     Adds specials to the living objects list of specials.
 * Argument:        (mapping) Mapping of specials
 *                            index - ability name
 *                            value - ability filename
 * Returns:         (int) 1 : Always returns succeeds
 */
public int
add_special(mapping special)
{
    if (!mappingp(special))
        return 0;
    
    specials += special;
    return 1;
} /* add_special */

/*
 * Function name:   remove_special
 * Description:     Remove specials from the living objects list of specials.
 * Argument:        (string) special index
 * Returns:         (int) 1 : Always returns succeeds
 */
public int
remove_special(string special)
{
    m_delkey(specials, special);
    
    return 1;
} /* remove_special */

/*
 * Function name:   query_active_souls
 * Description:     Returns the living objects souls.
 * Argument:        None
 * Returns:         (string *) : String array of souls
 */
public string *
query_active_souls()
{
    if (!pointerp(active_souls))
        active_souls = ({});

    return active_souls;
} /* query_active_souls */

/*
 * Function name:   set_active_souls
 * Description:     Sets the living objects souls.
 * Argument:        (string *) : String array of souls
 * Returns:         Nothing
 */
public varargs void
set_active_souls(string *souls)
{
    if (stringp(souls))
        souls = ({ souls });
    
    if (!pointerp(souls))
        souls = ({});
    
    active_souls = souls;
} /* set_active_souls */

/*
 * Function name:   query_active_shadows
 * Description:     Returns the living objects shadows.
 * Argument:        None
 * Returns:         (string *) : String array of shadows
 */
public string *
query_active_shadows()
{
    if (!pointerp(active_shadows))
        active_shadows = ({});

    return active_shadows;
} /* query_active_shadows */

/*
 * Function name:   set_active_shadows
 * Description:     Sets the living objects shadows.
 * Argument:        (string *) : String array of shadows
 * Returns:         Nothing
 */
public varargs void
set_active_shadows(string *shadows)
{
    if (stringp(shadows))
        shadows = ({ shadows });
    
    if (!pointerp(shadows))
        shadows = ({});
    
    active_shadows = shadows;
} /* set_active_shadows */


/*
 * Function name:   init_active_cmdsouls
 * Description:     Adds cmd souls and sets the special ability map.
 * Argument:        None
 * Returns:         Nothing
 */
nomask void
init_active_cmdsouls()
{
    if (!sizeof(active_souls))
        return;
    
    object  soul_ob;
    mapping abilities;
    
    foreach(string soul: active_souls)
    {
        if (!objectp(soul_ob = safely_load_master_file(soul)) ||
            !this_object()->add_cmdsoul(soul))
        {
            active_souls -= ({ soul });
            /* Log error */
            continue;
        }
        
        if (mappingp(abilities = soul_ob->query_ability_map()))
            add_special(abilities);
    }
    
    this_object()->update_hooks();
} /* init_active_cmdsouls */

/*
 * Function name:   init_active_shadows
 * Description:     Adds and initializes shadows.
 * Argument:        None
 * Returns:         Nothing
 */
nomask void
init_active_shadows()
{
    string *shadows_list;
    object  shadow_ob;
    
    if (!sizeof(shadows_list = active_shadows))
        return;
    
    foreach(string s_shadow: shadows_list)
    {
        if (!objectp(safely_load_master_file(s_shadow)) ||
            !objectp(shadow_ob = clone_object(s_shadow)) ||
            !shadow_ob->shadow_me(this_object()))
        {
            active_shadows -= ({ s_shadow });
            /* Log error */
            continue;
        }
        
        shadow_ob->init_active_shadow();
    }
} /* init_active_shadows */

/*
 * Function name:   query_active_cluster
 * Description:     Returns this living objects personal cluster object
 * Argument:        None
 * Returns:         (object) - returns cluster object
 */
nomask object
query_active_cluster()
{
    return active_living;
} /* query_active_cluster */

/*
 * Function name:   create_active_monster
 * Description:     The constructor for a standard active living monster
 * Arguments:       None
 * Returns:         Nothing
 */
void
create_active_monster()
{
} /* create_active_monster */

/*
 * Function name:   create_monster
 * Description:     The constructor for a basic monster
 * Arguments:       None
 * Returns:         Nothing
 */
 
/*
nomask void
create_monster()
{
    setuid();
    seteuid(getuid());
    
    if(!IS_CLONE)
        return;
    
    set_race_name("monster");
    set_name("monster");
    //set_prospective_cluster(({ "_active_monster_base" }));
    
    create_active_monster();
    
    init_active_cmdsouls();
    init_active_shadows();
} /* create_monster */

/*
 * Function name:   do_special_attack
 * Description:     Activates the living objects special abilities.
 * Arguments:       victim (the one we are fighting right now)
 * Returns:         (status) 1 - if the attack was successful
 *                  (status) 0 - if the attack was unsuccessful
 */
public status
do_special_attack(object victim)
{
    return 0;
} /* do_special_attack */

/*
 * Function name: notify_attack_on_team
 * Description  : This is called when someone attacks a team member of mine.
 * Arguments    : object friend - my team member
 *                object attacker - the attacker
 */
public void
notify_attack_on_team(object friend, object attacker)
{
    /* Already busy. */
    if (this_object()->query_attack())
        return;
    
    set_alarm((rnd() + 1.0), 0.0, &aggressive_attack(attacker));
} /* notify_attack_on_team */

/*
 * Function name:   attacked_by
 * Description:     This routine is called when we are attacked.
 * Arguments:       object attacker - the attacker.
 */
public void
attacked_by(object attacker)
{
    ::attacked_by(attacker);
    map(query_team_others(), &->notify_attack_on_team(this_object(), attacker));
    do_special_attack(attacker);
} /* attacked_by */

/*
 * Function name:   attack_object
 * Description:     Start attacking, the actual attack is done in heart_beat
 * Arguments:       The object to attack
 */
public int
attack_object(object ob)
{
    ::attack_object(ob);
    map(query_team_others(), &->notify_attack_on_team(this_object(), ob));
    do_special_attack(ob);
} /* attack_object */


/*
 * Function name:   id
 * Description:     This function is masked to check the group prospective ids,
 *                  but returns ::id to be compatible with non-active living
 * Arguments:       string str - the id you want to test.
 * Returns:         int 1/0 - true if the name is indeed used.
 */
public int
id(string str)
{
    if ((member_array(str, query_prospective_cluster()) > -1))
        return 1;
    
    return ::id(str);
} /* id */

/*
 * Function name:   do_die
 * Description:     Called from enemy combat object when it thinks we died.
 * Arguments:       object killer: The enemy that caused our death.
 */
public void
do_die(object killer)
{
    leave_group_cluster(this_object(), 0, 1);
    ::do_die(killer);
} /* do_die */

/*
 * Function name:   init_active_living
 * Description:     Substitute to be masked instead of init_living if needed
 */
public void
init_active_living()
{
    init_active_living();
    init_group_cluster();
} /* init_active_living */

/*
 * Function name:   init_living
 * Description:     Tells us of new players in our neigbourhood and checks if
 *                  they want to join our team
 
nomask void
init_living()
{
    init_active_living();
    init_group_cluster();
    
    ::init_living();
} /* init_living */