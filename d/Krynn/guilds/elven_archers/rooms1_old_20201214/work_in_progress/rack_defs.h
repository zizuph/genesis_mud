/* Defines */
#define RACK_MANAGER            OPTIONS_MANAGER

/* Defines: store_room */
#define ADDED_TO_ARCHERS_ARMORY "_added_to_archers_armory"
#define T_LIMIT                 2592000

/* Defines: rack_item */
#define MENU                    0
#define COMMAND                 1
#define ST_DO_CO_CMD            11
#define FILTER                  2

/* Defines: rack_room */
#define RACK_ITEM               (GUILD_OBJ + "rack_item.c")


/* Shared Functions */

/*
 * Function:    master_ob
 * Description: Returns the master file name of an object.
 * Argument:    object item - item from which to get filename
 * Returns:     string - filename of item
 */
public string
master_ob(object item)
{
    return MASTER_OB(item);
} /* master_ob */

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
 * Function:    safely_load_array_files
 * Description: This safely loads the master files in an array if they
 *              have not already been loaded. Otherwise, it just returns
 *              the existing master files. If the files are not loadable,
 *              then it simply returns 0
 * Argument:    filename of the file to load
 */
public object *
safely_load_array_files(string *files)
{
    object obj, *new_files = ({});
    
    foreach(string file: files)
    {
        if (objectp(obj = safely_load_master_file(file)))
            new_files += ({ obj });
    }
    
    return new_files;
} /* safely_load_array_files */


/*
 * Function name: is_container
 * Description  : Container filter
 * Arguments    : ob - the object to test
 * Returns      : 0 when not a container, 1 when it is
 */
public int
is_container(object ob)
{
    return IS_CONTAINER_OBJECT(ob);
} /* is_container */

/*
 * Function name: is_armour
 * Description  : Armour filter
 * Arguments    : ob - the object to test
 * Returns      : 0 when not an armour, 1 when it is
 */
int
is_armour(object ob)
{
    return IS_ARMOUR_OBJECT(ob);
} /* is_armour */

/*
 * Function name: is_weapon
 * Description  : weapon filter
 * Arguments    : ob - the object to test
 * Returns      : 0 when not an weapon, 1 when it is
 */
int
is_weapon(object ob)
{
    return IS_WEAPON_OBJECT(ob);
} /* is_weapon */

/*
 * Function name: get_player_name
 * Description  : Returns the player name in string form
 * Arguments    : mixed player - either string or object player
 * Returns      : string - the name of the player or empty string
 */
public string
get_player_name(mixed player)
{
    if (stringp(player))
        return player;
    
    if (!objectp(player))
        return "";
    
    return interactive(player) ? player->query_real_name() : OB_NAME(player);
} /* get_player_name */

