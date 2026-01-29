/*
 * Abort Object
 *
 * This object allows one to abort one of the abilities one is using.
 * 
 */
 
#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <language.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <state_desc.h>
#include <cmdparse.h>

// Global Variables
public string      *Ability_files = ({});
public object       Ability_actor;

/*
 * Function name:   create_object
 * Description:     Default object construct
 * Arguments:       None
 * Returns:         Nothing
 */
private void
create_object(void)
{
    setuid();
    seteuid(getuid());

    set_name("timed_ability_master");
    add_name("_timed_master_object");

    // By setting this, players should not know that this is in their
    // inventory.
    set_no_show();
    
    set_short("hidden ability object");
    set_long("This is the object handles aborting of timed abilities, and "
    + "other tidbits.\n");

    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_WEIGHT);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_STEAL, 1);        
} /* create_object */

public object
query_ability_actor()
{
    return Ability_actor;
}

public void 
set_ability_actor(object actor)
{
    Ability_actor = actor;
}

public void
add_concentration(mixed file)
{
    if (stringp(file))
        file = find_object(file);
    
    if (objectp(file) && file->query_ability_concentrate())
        Ability_actor->inc_prop(LIVE_I_CONCENTRATE, 1);
} /* add_concentration */

public void
remove_concentration(mixed file)
{
    if (stringp(file))
        file = find_object(file);
    
    if (objectp(file) && file->query_ability_concentrate() &&
        intp(environment()->query_prop(LIVE_I_CONCENTRATE)) &&
        environment()->query_prop(LIVE_I_CONCENTRATE) > 0)
        environment()->dec_prop(LIVE_I_CONCENTRATE, 1);
} /* remove_concentration */


/*
 * Function name:   query_ability_files
 * Description:     
 * Arguments:       None
 * Returns:         (string *)
 */
public string *
query_ability_files()
{
    return Ability_files;
} /* query_ability_files */

/*
 * Function name:   add_ability_file
 * Description:     
 * Arguments:       (mixed) file
 * Returns:         Nothing
 */
public void
add_ability_file(mixed file)
{
    add_concentration(file);
    if (objectp(file))
        file = file_name(file);
    
    if (stringp(file))
        Ability_files |= ({ file });
} /* add_ability_file */

/*
 * Function name:   remove_ability_file
 * Description:     
 * Arguments:       (mixed) file
 * Returns:         Nothing
 */
public void
remove_ability_file(mixed file)
{
    remove_concentration(file);
    if (objectp(file))
        file = file_name(file);
    
    if (stringp(file))
        Ability_files -= ({ file });
} /* add_ability_file */

/*
 * Function name:   abort_ability
 * Description:     
 * Arguments:       (string) arg
 * Returns:         (int)
 */
public int
abort_ability(string arg)
{
    object *abilities = filter(map(Ability_files, &find_object()), &objectp());
    
    notify_fail("Abort what?\n");
    if (!strlen(arg))
        return 0;
    
    foreach(object ability: abilities)
    {
        if (ability->query_ability_active(this_player()) &&
            ability->query_ability_abort())
        {
            if (member_array(arg, ({ "spell", "prayer" })) > -1
                && ability->query_spell())
                continue;
        
            if (arg == ability->query_ability_name())
                continue;
        }

        abilities -= ({ ability });
    }

    if (!sizeof(abilities))
        return 0;

    // Stop abilities.
    abilities = filter(abilities, &->stop_ability(this_player()));
    // Remove the ability file for all the aborted abilities.
    //filter(abilities, &remove_ability_file());
        
    return 1;
} /* abort_ability */

/*
 * Function name:   init
 * Description:     Add the 'command items' of this object. Note that if
 *                  you redefine this function, the command items will not
 *                  work unless you do ::init(); in your code!
 * Arguments:       None
 * Returns:         Nothing
 */
public void
init()
{
    ::init();

    add_action(abort_ability, "abort");
} /* init */
