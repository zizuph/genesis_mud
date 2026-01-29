// OBJECT:  backup

    /* Calia Domain

    HISTORY

    [01-12-14] Created by Uhclem from [C:\CALIA\YULEWARE\GINGER\BACKUP.DOC].

    PURPOSE

    This object backs up the construction site array of the holiday room.  If
    anyone should update that room, thereby erasing its memory, it will
    retrieve the necessary information from this object.  */

// INCLUSIONS AND DEFINITIONS

inherit "/std/object";

#include <stdproperties.h>

// GLOBAL VARIABLES

object *Construction_Sites = ({});

// FUNCTIONS

// Function:  backup_gingerbread_memory(object *sites)

/*

Purpose:  make a backup copy of the construction sites array.

Arguments:  array of objects, the rooms in which gingerbread construction is
underway.

Returns: nothing.

*/

void
backup_gingerbread_memory(object *sites)

{

    Construction_Sites = sites;

}

// Function:  *restore_gingerbread_memory()

/*

Purpose:  restores the contents of the construction sites array.

Arguments:  none.

Returns: array of objects, the rooms in which gingerbread construction is
underway.

*/

object
*restore_gingerbread_memory()

{

    return Construction_Sites;

}

// OBJECT DEFINITION

void
create_object()

{

    /*
     *  DESCRIPTION    
     */

    set_short("backup");
    set_name("backup");

    set_long("This object backs up the memory of the Calia" +
        " holiday room. Please do not destruct or" +
        " otherwise disturb it.\n");

    /*
     *  PROPERTIES    
     */

    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
    add_prop(OBJ_I_VALUE, 1);

}
