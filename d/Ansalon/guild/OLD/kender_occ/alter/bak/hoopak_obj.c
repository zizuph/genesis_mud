#pragma strict_types

inherit "/std/object";

#include <stdproperties.h>
#include <files.h>

#include "defs.h"

/* Global Variables */
public object           obj;
public int              id;

/* Prototypes */
public string           query_recover();
public void             replace();


/*
 * Function name:        create_object
 * Description  :        set up
 */
public void
create_object()
{
    setuid();
    seteuid(getuid());
    set_name("_recover_hoopak");
    add_name("hoopak");
    set_short("altered hoopak");
    set_long("A altered hoopak.\n");
} /* create_object */


/*
 * Function name:        init_recover
 * Description  :        clone object
 */
public void
init_recover(string arg)
{
    mapping hoopak = ([]);
    int     num, id;
    
    if (!mappingp(hoopak = HOOPAK_RECOVERY->get_hoopak(atoi(arg))) ||
        !m_sizeof(hoopak))
    {
        find_player("carnak")->catch_msg("ERROR.\n");
        set_alarm(0.0, 0.0, remove_object);
        return;
    }
    
    /* Clones the recovering item */
    obj = clone_object(hoopak["hoopak"]);

    /* Removes from the recovering item */
    obj->remove_adj(obj->query_adjs());   
    obj->remove_name(obj->query_names());
    obj->remove_pname(obj->query_pnames());
    
    /* Adds to the recovering item */
    if (sscanf(file_name(obj), "#%d"), num)
        obj->add_name("ob_" + num);
    
    obj->add_name(hoopak["names"]);
    obj->set_short(hoopak["short"]);
    obj->set_long(hoopak["long"]);
    obj->set_adj(hoopak["adjs"]);
    obj->init_recover(hoopak["recover"]);
    
    /* Modifies the recoverer */
    add_prop(OBJ_I_WEIGHT, obj->query_prop(OBJ_I_WEIGHT));
    set_short(obj->short());
    set_long(obj->long());
    
} /* init_recover */



/*
 * Function name:        replace
 * Description  :        Replace this object with real item
 */
public void
replace()
{
    obj->move(environment(), 1);
    remove_object();
    
} /* replace */

/*
 * Function name:        enter_env
 * Description  :        mov
 */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest,old);
    
    if (obj)
        replace();

} /* enter_env */

/*
 * Function name: query_recover
 * Description:   Return recover string for anything cloning us
 * Returns:       Recover string for recoverer, not item
 */
public string
query_recover()
{
    return HOOPAK_OBJ + ":" + id;
} /* query_recover */

/*
 * Function:    query_hoopak_id
 * Description: Returns the id of the hoopak recover item.
 */
public int
query_hoopak_id()
{
    return id;
} /* query_hoopak_id */

void
set_hoopak_id(int h_id)
{
    id = h_id;
}