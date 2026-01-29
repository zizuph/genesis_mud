/*
 *  std_magic_lib.c
 *
 *  Inherit this to create objects that can make use of spell effects from the
 *  spell system. This is used in the std_magic_obj to create wands, grimoires
 *  and spellbooks, but if you inherit this you are not limited to using it on
 *  just standard objects.
 *
 *  This function is required to use spell_commands from the std_magic_lib, it
 *  is called from init.
 *      init_spell_commands();
 *
 *  To add the spell effects and so on, you must put these functions inside
 *  wear/wield/hold and remove/unwield/release.
 *      add_magic_obj_effects(object player)
 *      remove_magic_obj_effects(object player)
 *
 *  Remember to setuidgetuid your object to make sure it has an euid.
 *      setuid();
 *      seteuid(getuid());
 *
 *  Created by Carnak October 2017
 *  - The code was removed from std_magic_obj to allow armours to use it.
 *
 */
#include <macros.h>

#define MANA_SHADOW     "/d/Genesis/specials/guilds/shadows/mana_shadow"
#define SPELL_MANAGER   "/d/Genesis/specials/guilds/souls/spell_manager_soul"

/* Global Variables */
static mapping  gSpell_cmd_map = ([ ]);
static mixed    gSpell_cmds = ({ }), 
                gSpell_cmd_parse = ({ });

object  magic_obj_shadow,
        mana_shadow;
string *magic_obj_effect,
        magic_obj_soul,
        magic_obj_shadow_loc;

/* Prototypes */
public void     add_magic_obj_effects(object player);
public void     remove_magic_obj_effects(object player);

/*
 * Function:    safely_load_master_file
 * Description: This safely loads the master file if it hasn't already
 *              been loaded. Otherwise, it just returns the existing
 *              master file. If the file is not loadable, then it
 *              simply returns 0
 * Argument:    filename of the file to load
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
 * Function:    add_magic_obj_spell
 * Description: Adds spells that the object grans its user, this function
 *              can not add spells to the spell list, and must use commands
 *              to be executed.
 * Argument:    string parse - the parse for the command
 *              mixed cmd - the verb to use for casting
 *              string spell - The directory of the spell to be cast
 *              string option - (optional) spell command
 *                  eg. cmd spell <drake> parse
 *                      cast polymorph drake
 */
public varargs void
add_magic_obj_spell(string parse, mixed cmd, string spell, string option)
{
    int size, size2, i = -1;

    if (!pointerp(cmd))
        cmd = ({ cmd });

    gSpell_cmd_parse += ({ ({ parse, spell, option }) });

    size = sizeof(cmd);

    size2 = sizeof(gSpell_cmd_parse) - 1;

    while (++i < size)
        if (!pointerp(gSpell_cmd_map[cmd[i]]))
            gSpell_cmd_map += ([ cmd[i]:({ size2 }) ]);
        else
            gSpell_cmd_map[cmd[i]] += ({ size2 });

    if (size)
        gSpell_cmds = gSpell_cmds + (cmd - (cmd & gSpell_cmds));
} /* add_magic_obj_spell */

/*
 * Function name:   verify_magic_obj_spell_cast
 * Description:     
 * Arguments:       (string) arg - the argument which has been parsed
 *                  (object) spell - the spell object being cast
 * Returns:         (status) 1 - successfully attempting the spell
 *                           0 - the spell has been hindered
 */
public status
verify_magic_obj_spell_cast(string arg, object spell)
{
    return 1;
} /* verify_magic_obj_spell_cast */

/*
 * Function:    cmd_parse_spell_action
 * Description: Parses actions for spell commands and targets to trigger
 *              spells added to the item.
 * Argument:    string arg - the argument which is parsed
 */
public int
cmd_parse_spell_action(string arg)
{
    string  vb, desc, tar = "";
    int    *nr_arr, size, i = -1;
    mixed   spell;
    object  caller = previous_object();
    
    if (!arg)
        return 0;
    
    if (objectp(caller) && caller->query_holdable() && !caller->query_held())
    {
        notify_fail(caller->hook_must_be_held());
        return 0;
    }

    nr_arr = gSpell_cmd_map[query_verb()];
    size = sizeof(nr_arr);

    while (++i < size)
    {
        if (parse_command(arg, ({}), gSpell_cmd_parse[nr_arr[i]][0] + " [at] %s", tar) ||
            parse_command(arg, ({}), gSpell_cmd_parse[nr_arr[i]][0]))
        {
            desc = caller->check_call(gSpell_cmd_parse[nr_arr[i]][1]);
            
            if (stringp(gSpell_cmd_parse[nr_arr[i]][2]))
                tar = gSpell_cmd_parse[nr_arr[i]][2] +
                      (strlen(tar) ? " " + tar : "");
            
            if (stringp(desc) && objectp(spell = safely_load_master_file(desc)))
            {
                if (verify_magic_obj_spell_cast(arg, spell))
                    spell->do_ability(tar);
                
                return 1;
            }
            else
            {
                if (!desc)
                    continue;
                else
                    return 1;
            }
        }
    }
    return 0;
} /* cmd_parse_spell_action */

/*
 * Function:    init_spell_commands
 * Description: Adds actions to trigger spells to the object.
 */
void
init_spell_commands()
{
    int size, i = -1;

    size = sizeof(gSpell_cmds);

    if (!size)
        return;

    while (++i < size)
        add_action("cmd_parse_spell_action", gSpell_cmds[i]);
} /* init_spell_commands */

/*
 * Function:    set_magic_obj_effect
 * Description: Sets effect names for the effects of the spells.
 * Argument:    mixed effect - array of strings
 */
public void
set_magic_obj_effect(mixed effect)
{
    if (!pointerp(effect))
        effect = ({ effect });
    
    magic_obj_effect = effect;
} /* set_magic_obj_effect */

/*
 * Function:    query_magic_obj_effect
 * Description: Returns the specified effect names.
 * Returns:     string *magic_obj_effects - array of strings
 */
public string *
query_magic_obj_effect()
{
    return magic_obj_effect;
} /* query_magic_obj_effect */

/*
 * Function:    set_magic_obj_soul
 * Description: Sets the soul associated with the item, most commonly a
 *              spell soul.
 * Argument:    string soul - the souls master_ob
 */
public void
set_magic_obj_soul(string soul)
{
    magic_obj_soul = soul;
} /* set_magic_obj_soul */

/*
 * Function:    query_magic_obj_soul
 * Description: Returns the specified soul master_ob
 * Returns:     string magic_obj_soul - soul file_name
 */
public string
query_magic_obj_soul()
{
    return magic_obj_soul;
} /* query_magic_obj_soul */

/*
 * Function:    set_magic_obj_shadow
 * Description: Sets the shadow associated with the item.
 * Argument:    string shadow - the shadow master_ob
 */
public void
set_magic_obj_shadow(string shadow)
{
    magic_obj_shadow_loc = shadow;
} /* set_magic_obj_shadow */

/*
 * Function:    query_magic_obj_shadow
 * Description: Returns the specified shadow master_ob
 * Returns:     string magic_obj_shadow_loc - shadow file_name
 */
public mixed
query_magic_obj_shadow()
{
    if (objectp(magic_obj_shadow))
        return magic_obj_shadow;
    
    return magic_obj_shadow_loc;
} /* query_magic_obj_shadow */


/*
 * Function:    is_valid_spell_obj
 * Description: Checks if there are any valid spell objects
 * Argument:    object caster, object obj - object to check
 * Returns:     1 - success, 0 - failure
 */
public int
is_valid_spell_obj(object caster, object obj)
{
    string *effects = ({});
    
    if (!sizeof(magic_obj_effect) || !objectp(obj))
        return 0;
    
    foreach(string effect: magic_obj_effect)
    {
        if (obj->id(effect))
            effects += ({ effect });
    }
    
    if (!sizeof(effects))
        return 0;
    
    return 1;
} /* is_valid_spell_obj */

/*
 * Function:    add_magic_obj_effects
 * Description: Adds the soul, shadow and mana shadow to the target
 * Argument:    object player - target to shadow
 */
public void
add_magic_obj_effects(object player)
{
    if (!living(player))
        return;
    
    if (strlen(magic_obj_soul) && player->add_cmdsoul(magic_obj_soul))
        player->update_hooks();
    
    if (strlen(magic_obj_shadow_loc) && safely_load_master_file(magic_obj_shadow_loc))
    {
        magic_obj_shadow = clone_object(magic_obj_shadow_loc);
        magic_obj_shadow->shadow_me(player);
        magic_obj_shadow->add_shadow_effects();
    }
    
    if (!player->has_mana_shadow())
    {
        mana_shadow = clone_object(MANA_SHADOW);
        mana_shadow->shadow_me(player);
        
        if (player->add_cmdsoul(SPELL_MANAGER))
            player->update_hooks();
    }
} /* add_magic_obj_effects */

/*
 * Function:    remove_magic_obj_effects
 * Description: Removes the soul and shadows from the target, also dispels
 *              any active spell object.
 * Argument:    object player
 */
public void
remove_magic_obj_effects(object player)
{
    if (strlen(magic_obj_soul) && player->remove_cmdsoul(magic_obj_soul))
        player->update_hooks();
    
    if (objectp(magic_obj_shadow))
        magic_obj_shadow->remove_shadow_effects();
    
    if (objectp(mana_shadow))
    {
        mana_shadow->remove_mana_shadow();
        
        if (player->remove_cmdsoul(SPELL_MANAGER))
            player->update_hooks();
    }
    
    if (!objectp(player) && !living(player = environment(this_object())))
        return;
    
    object *spell_obj;
    spell_obj = filter(all_inventory(player), &is_valid_spell_obj(player,));

    if(sizeof(spell_obj))
    {
        foreach(object s_obj : spell_obj)
        {
            s_obj->set_dispel_time(1);
        }
    }
} /* remove_magic_obj_effects */
