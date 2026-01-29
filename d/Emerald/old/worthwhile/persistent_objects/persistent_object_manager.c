/* persistent_object_manager.c
 *
 * In Emerald, we have a desire to create items that can be carried around
 * by players and deposited in rooms of their choice.  These items should
 * then be cloned into those rooms as if they were a permanent part of the
 * room.  This object handles some of the data storage and cloning routines
 * required.
 */

#include <macros.h>

#define PERSISTENT_OBJECT_FILE(r) \
    ("/d/Emerald/log/persistent_object/" + r[11..])

#define PERSISTENT_OBJECT_LIST       "persistent_objects"
#define PERSISTENT_OBJECT_LIST_FILE  0
#define PERSISTENT_OBJECT_LIST_SUBL  1
#define PERSISTENT_OBJECT_LIST_SIZE  2

nomask void
create()
{
    setuid();
    seteuid(getuid());
}

public varargs void
add_persistent_object(mixed pob, mixed room, string subloc)
{
    mapping m;
    mixed *persistent_objects, *new;
    string file, dir, *split;
    int i;

    if (objectp(room))
    {
        room = MASTER_OB(room);
    }

    if (objectp(pob))
    {
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
       
    new = allocate(PERSISTENT_OBJECT_LIST_SIZE);
    new[PERSISTENT_OBJECT_LIST_FILE] = pob;
    new[PERSISTENT_OBJECT_LIST_SUBL] = subloc;

    persistent_objects += ({ new });
    m[PERSISTENT_OBJECT_LIST] = persistent_objects;

    save_map(m, file);
}

public varargs void
remove_persistent_object(mixed pob, mixed room)
{
    mapping m;
    mixed *persistent_objects;
    string file;
    int i;

    if (objectp(room))
    {
        room = MASTER_OB(room);
    }

    if (objectp(pob))
    {
        pob = MASTER_OB(pob);
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

    for (i = (sizeof(persistent_objects) - 1); i >= 0; i--)
    {
        if (persistent_objects[i][PERSISTENT_OBJECT_LIST_FILE] == pob)
        {
            persistent_objects = exclude_array(persistent_objects, i, i);
        }
    }

    m[PERSISTENT_OBJECT_LIST] = persistent_objects;

    save_map(m, file);
}

public void
load_persistent_objects(mixed room)
{
    mapping m;
    mixed *persistent_objects;
    int i;
    object ob;
    string file;

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
        ob = clone_object(persistent_objects[i][PERSISTENT_OBJECT_LIST_FILE]);
        ob->move(room, persistent_objects[i][PERSISTENT_OBJECT_LIST_SUBL]);
    }
}
