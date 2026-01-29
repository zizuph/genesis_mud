/* persistent_object_manager.c
 *
 * In Emerald, we have a desire to create items that can be carried around
 * by players and deposited in rooms of their choice.  These items should
 * then be cloned into those rooms as if they were a permanent part of the
 * room.  This object handles some of the data storage and cloning routines
 * required.
 */

#include "/d/Emerald/sys/pom.h"
#include <macros.h>

#define DO_POM_LOGGING
#ifdef DO_POM_LOGGING
#  define POM_LOG_FILE (POM_SAVE_DIR + "log")
#  define POM_LOG(t)   log_file(POM_LOG_FILE, time() + " " + t);
#else
#  define POM_LOG(t)
#endif

#define DO_POM_ERROR_LOGGING
#ifdef DO_POM_ERROR_LOGGING
#  define POM_ERROR_FILE (POM_SAVE_DIR + "errors")
#  define POM_ERROR(t)   log_file(POM_ERROR_FILE, time() + " " + t);
#else
#  define POM_ERROR(t)
#endif

nomask void
create()
{
    setuid();
    seteuid(getuid());
}

public string
get_new_pob_id()
{
    return "0";
}

public varargs void
add_persistent_object(mixed pob, mixed room, string subloc)
{
    mapping m;
    mixed *persistent_objects, *new;
    string file, dir, *split, id;
    int i;
    object pob_ob;

    if (objectp(room))
    {
        room = MASTER_OB(room);
    }

    if (objectp(pob))
    {
        pob_ob = pob;
        pob = MASTER_OB(pob);
    }

    file = PERSISTENT_OBJECT_FILE(room);
    if (file_size(file + ".o") < 0)
    {
        dir = "";
        split = explode(file, "/") - ({ "" });
        for (i = 0; i < (sizeof(split) - 1); i++)
        {
            dir += "/" + split[i];
            mkdir(dir);
        }
    }

    m = restore_map(file);
    persistent_objects = m[PERSISTENT_OBJECT_LIST] || ({});
     
    id = get_new_pob_id();
  
    new = allocate(PERSISTENT_OBJECT_LIST_SIZE);
    new[PERSISTENT_OBJECT_LIST_ID]   = id;
    new[PERSISTENT_OBJECT_LIST_FILE] = pob;
    new[PERSISTENT_OBJECT_LIST_SUBL] = subloc;

    persistent_objects += ({ new });
    m[PERSISTENT_OBJECT_LIST] = persistent_objects;

    save_map(m, file);
    POM_LOG("Added " + pob + " [" + id + "] to " + room +
        (subloc ? " (" + subloc + ")" : "") + "\n");

    if (pob_ob)
    {
        pob_ob->add_prop(PERSISTENT_OBJECT_ID, id);
    }
}

public varargs void
remove_persistent_object(string id, mixed room)
{
    mapping m;
    mixed *persistent_objects;
    string file, subloc, pob;
    int i;

    if (objectp(room))
    {
        room = MASTER_OB(room);
    }

    file = PERSISTENT_OBJECT_FILE(room);
    if (file_size(file + ".o") < 0)
    {
        return;
    }

    m = restore_map(file);
    persistent_objects = m[PERSISTENT_OBJECT_LIST];

    if (!sizeof(persistent_objects))
    {
        return;
    }

    for (i = 0; i < sizeof(persistent_objects); i++)
    {
        if (persistent_objects[i][PERSISTENT_OBJECT_LIST_ID] == id)
        {
            pob    = persistent_objects[i][PERSISTENT_OBJECT_LIST_FILE];
            subloc = persistent_objects[i][PERSISTENT_OBJECT_LIST_SUBL];
            persistent_objects = exclude_array(persistent_objects, i, i);
            break;
        }
    }

    if (i >= sizeof(persistent_objects)) // No matching object found
    {
        return;
    }

    m[PERSISTENT_OBJECT_LIST] = persistent_objects;

    save_map(m, file);
    POM_LOG("Removed " + pob + " [" + id + "] from " + room +
        (subloc ? " (" + subloc + ")" : "") + "\n");
}

public void
load_persistent_objects(mixed room)
{
    mapping m;
    mixed *persistent_objects;
    int i;
    object ob;
    string file, err;

    if (objectp(room))
    {
        room = MASTER_OB(room);
    }

    file = PERSISTENT_OBJECT_FILE(room);
    if (file_size(file + ".o") <= 0)
    {
        return;
    }

    m = restore_map(file);
    persistent_objects = m[PERSISTENT_OBJECT_LIST];
 
    for (i = 0; i < sizeof(persistent_objects); i++)
    {
        err = catch(ob =
            clone_object(persistent_objects[i][PERSISTENT_OBJECT_LIST_FILE]));

        if (strlen(err))
        {
            POM_ERROR(err);
            continue;
	}

        ob->add_prop(PERSISTENT_OBJECT_ID,
            persistent_objects[i][PERSISTENT_OBJECT_LIST_ID]);
        ob->move(room, persistent_objects[i][PERSISTENT_OBJECT_LIST_SUBL]);
    }
}
