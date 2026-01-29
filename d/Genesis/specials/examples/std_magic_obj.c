/*
 *  std_magic_obj.c
 *
 *  Inherit this to create objects that can make use of spell
 *  effects using the spell system - such as scrolls, grimoires, or wands.
 *
 *  Created by Carnak June 2017
 *
 * * * * * * * * * * * * * * * * * *
 *
 *  Example code:
 *
 *  inherit "/d/Genesis/specials/examples/std_magic_obj";
 *
 *  #include <macros.h>
 *  #include <wa_types.h>
 *  #include <ss_types.h>
 *  #include <stdproperties.h>
 *
 *  public void
 *  create_magic_obj()
 *  {
 *      set_name("tome");
 *      add_adj("leather-bound");
 *      set_long("This is a thin delicate leather-bound tome covered in " +
 *      "runes.\n");
 *
 *      add_prop(OBJ_I_WEIGHT,20);
 *      add_prop(OBJ_I_VOLUME,20);
 *      add_prop(OBJ_I_VALUE, 100);
 *      add_prop(MAGIC_AM_MAGIC,({20,"enchantment"}));
 *      add_prop(MAGIC_AM_ID_INFO,
 *      ({ "This is a rune-clad tome granting you magic.. yadayada.\n", 20 }));
 *        
 *      set_keep(1);
 *
 *      set_holdable(0);
 *
 *      set_magic_spellbook(1);
 *    
 *      add_magic_obj_spell("[the] [leather-bound] 'tome' / 'book'",
 *                          ({ "touch" }),
 *                          "/d/Genesis/specials/std/spells/light.c");
 *      add_magic_obj_spell("'with' [the] [leather-bound] 'tome' / 'book'",
 *                          ({ "pray" }),
 *                          "/d/Genesis/specials/std/spells/calm.c");
 *      set_magic_obj_effect("_light_object_");
 *  }
 *
 * * * * * * * * * * * * * * * * * *
 *
 *  Comments:
 *
 */

#pragma save_binary
#pragma no_clone

inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/lib/keep";
inherit "/d/Genesis/specials/examples/std_magic_lib";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

int     holdable, magic_spellbook;

/*
 * Function:    hook_magic_obj_hold
 * Description: The string hook for successfully holding the object.
 */
public string
hook_magic_obj_hold()
{
    // Add hold description
} /* hook_magic_obj_hold */

/*
 * Function:    hook_magic_obj_release
 * Description: The string hook for successfully releasing the object.
 */
public string
hook_magic_obj_release()
{
    // Add release description
} /* hook_magic_obj_release */

/*
 * Function:    hook_must_be_held
 * Description: The string hook for action requiring item to be held.
 */
public string
hook_must_be_held()
{
    return "You must hold the " + short() + " to proceed.\n";
} /* hook_must_be_held */

/*
 * Function:    set_holdable
 * Description: Determines if the object is holdable or not
 * Argument:    int hold - 1: holdable, 0: not holdable
 */
public void
set_holdable(int hold)
{
    holdable = hold;
} /* set_holdable */

/*
 * Function:    query_holdable
 * Description: Returns the objects holdable status.
 * Returns:     int holdable - 1: holdable, 0: not holdable
 */
public int
query_holdable()
{
    return holdable;
} /* query_holdable */

/*
 * Function:    set_magic_spellbook
 * Description: Makes the object react on environment, adding
 *              spells when entering the inventory
 * Argument:    int spellbook - 1: reacts to inventory,
 *                              0: does not add spells
 */
public void
set_magic_spellbook(int spellbook)
{
    magic_spellbook = spellbook;
} /* set_magic_spellbook */

/*
 * Function:    query_magic_spellbook
 * Description: Returns the objects reaction to environment.
 * Returns:     int spellbook - 1: reacts to inventory,
 *                              0: does not add spells
 */
public int
query_magic_spellbook()
{
    return magic_spellbook;
} /* query_magic_spellbook */

/*
 * Function:    create_magic_obj
 * Description: The magic object constructor.
 */
public void
create_magic_obj()
{
    // Mask this function to customize the magic obj.
} /* create_magic_obj */

/*
 * Function:    create_object
 * Description: The standard object constructor.
 */
public nomask void
create_object()
{
    setuid();
    seteuid(getuid());
    
    set_name("_magic_object_");
    set_long("This is a magic object.\n");

    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 100);
    add_prop(MAGIC_AM_MAGIC,({20,"enchantment"}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({ "This is a magic object.\n", 20 }));
        
    set_slots(W_ANYH);
    set_holdable(0);
    
    set_keep(1);
    
    set_magic_obj_effect(({""}));
    set_magic_obj_soul("");
    set_magic_obj_shadow("");
    
    // Call the create_magic_obj function for customization purposes
    create_magic_obj();
} /* create_object */

/*
 * Function name: hold
 * Description  : Called when the person wants to hold an item. This function
 *                may allow or disallow the object to be held, and it may
 *                print its own messages.
 * Returns      : string / int -
 *                 0 - The item can be held, print default messages.
 *                 1 - The item can be held, print no messages.
 *                     Messages were printed within the function.
 *                -1 - The item cannot be held. Print default messages.
 *                string - The item cannot be held. The string contains the
 *                         fail message.
 */
public nomask mixed
hold()
{
    if (!query_holdable())
        return "You seem unable to hold that.\n";
    
    hook_magic_obj_hold();
    
    /* Required to add magic obj effects to the item */
    add_magic_obj_effects(this_player());

    return 0;
} /* hold */

/* 
 * Function name: release
 * Description  : Called when the person wants to release the item. This
 *                function may allow or disallow the object to be released,
 *                and it may print its own messages.
 * Returns      : string / int -
 *                 0 - The item can be relased, print default messages.
 *                 1 - The item can be relased, print no messages.
 *                     Messages were printed within the function.
 *                -1 - The item cannot be released. Print default messages.
 *                string - The item cannot be relased. The string contains the
 *                         fail message.
 */
public nomask mixed
release()
{
    if (!query_holdable())
        return "You seem unable to release that.\n";
    
    hook_magic_obj_release();
    
    /* Required to remove the previously added effects to the item */
    remove_magic_obj_effects(this_player());
    return 0;
} /* release */

/*
 * Function:    leave_env
 * Description: Standard leave_env, removes magic effects and
 *              handles holdable object.
 * Arguments:   object from - the environment we are leaving.
 *              object to   - the environment we are entering.
 */
void
leave_env(object env, object to)
{
    /* Required to remove the previously added effects to the item */
    remove_magic_obj_effects(env);
    
    ::leave_env(env, to);
    holdable_item_leave_env(env, to);
} /* leave_env */


/*
 * Function:    leave_env
 * Description: Standard enter_env, adds magic effects if the
 *              environment is living and the magic_spellbook
 *              has been set.
 * Arguments:   object env  - the environment we are entering.
 *              object from - the environment we are leaving.
 */
void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    
    /* Required to add magic obj effects to the item */
    if (magic_spellbook)
        add_magic_obj_effects(env);
} /* enter_env */

void
init()
{
    ::init();
    
    /* required to use spell_commands from the std_magic_lib */
    init_spell_commands();
}