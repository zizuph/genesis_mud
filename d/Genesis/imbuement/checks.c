/*
 *
 */

#pragma strict_types
#include "imbuement.h"
#include "macros.h"
#include "files.h"

//inherit "/std/object";

/* Definitions */

/* Global Variables */
mapping shadows = ([]);

/* Prototypes */
public void load();
public void save();
public void add(object sh, object tar);


public void
allsh(int mode, int dest)
{
    setuid();
    seteuid(getuid());
    string *files = get_dir(SHADOW_DIR);
    object obj, target, *clones;

    if (!IMBUE_MASTER->check_access())
        return;

    load();
    
    foreach (string file: files)
    {
        if (file_size(SHADOW_DIR + file) > 0)
        {
            obj = find_object(SHADOW_DIR + file);
            if (!obj)
                continue;
            write(file + ":\n");
            clones = object_clones(obj);
            if ((mode == 0) && (dest == 1) && (sizeof(clones) == 0))
            {
                obj->remove_object();
                if (obj)
                    SECURITY->do_debug("destroy", obj);
                write("Removed.\n");
            }
            foreach (object clone: clones)
            {
                write(" " + file_name(clone) + "\n");
                add(clone, target);
                if (mode == 1)
                {
                    target = clone->query_shadow_who();
                    if (target)
                        write("  " + file_name(target) + "\n");
                    else
                        if (dest == 1)
                        {
                            clone->remove_object();
                            if (clone)
                                SECURITY->do_debug("destroy", clone);
                            write(" -Removed\n");
                        }
                }
            }
        }
    }
    save();
}

public void
load()
{
    setuid();
    seteuid(getuid());
    shadows=restore_map(IMBUE_DIR + "shadows");
}

public void
save()
{
    setuid();
    seteuid(getuid());
    save_map(shadows, IMBUE_DIR + "shadows");
}

public void
add(object sh, object tar)
{
    if (objectp(sh))
        shadows[file_name(sh)] = sh;
        //shadows[sh] = tar;
}

public mapping
get()
{
    if (!IMBUE_MASTER->check_access())
        return 0;

    return shadows;
}