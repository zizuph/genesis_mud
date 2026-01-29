/*
 * Function name: clone_npc
 * Description:   Clone one npc into this room and arm it.
 * Arguments:     npc  - the object pointer to the npc.
 *                file - the file name of the npc.
 *                restrain_path (optional) -
 *                       set the monster restrain path.
 *                setup (optional) - function to be 
 *                called in the npc before arm_me is called.
 * Returns:       the object pointer to the npc.
 * Usage:
 *
 * inherit "/d/Gondor/std/room.c";
 *
 * #include "/d/Gondor/defs.h"
 *
 * #define NPC_FILE     ("/d/Gondor/common/npc/orc")
 *
 * // Global variables
 * object  Npc;
 * 
 * void
 * reset_room()
 * {
 *     Npc = clone_npc(Npc, NPC_FILE);
 * }
 * 
 */
public varargs object
clone_npc(object npc, string file, mixed restrain_path, function setup)
{
    if (objectp(npc))
        return npc;

    npc = clone_object(file);
    if (functionp(setup))
        setup();
    npc->arm_me();
    if (stringp(restrain_path))
        restrain_path = ({ restrain_path });
    if (pointerp(restrain_path) && sizeof(restrain_path))
        npc->set_restrain_path(restrain_path);
    npc->move_living("from the void", this_object());

    return npc;
}

/*
 * Function name: clone_npcs
 * Description:   Clone more than one npc into this room and arm it.
 * Arguments:     npcs  - the array of object pointers to the npcs.
 *                file  - the file name of the npc.
 *                delay - how long until the next npc is cloned,
 *                        if <= 0.0, no set_alarm
 *                c     - counter, how many times has clone_npcs been
 *                        called since reset? 
 *                restrain_path (optional) -
 *                      - set the monster restrain path.
 *                setup (optional) - function to be called before arm_me
 * Returns:       -1 if delay > 0 and a npc was cloned,
 *                 0 if no npc was cloned,
 *                 n if delay == o and n npcs were cloned.
 * Usage:
 *
 * inherit "/d/Gondor/std/room.c";
 *
 * #include "/d/Gondor/defs.h"
 *
 * #define NPC_FILE     ("/d/Gondor/common/npc/orc")
 *
 * // Global variables
 * object *Npcs = allocate(3 + random(3));
 * 
 * void
 * reset_room()
 * {
 *     set_alarm(4.0, 0.0, &clone_npcs(Npcs, NPC_FILE, 10.0));
 * }
 *
 */
public varargs int
clone_npcs(object *npcs, string file, float delay, mixed restrain_path, int c =
0, function setup = 0)
{
    int     i, s,
            count = 0;

    for (i = c, s = sizeof(npcs); i < s; i++)
    {
        if (!objectp(npcs[i]))
        {
            count++;
            if (restrain_path && functionp(setup))
                npcs[i] = clone_npc(npcs[i], file, restrain_path, setup);
            else if (restrain_path)
                npcs[i] = clone_npc(npcs[i], file, restrain_path);
            else if (functionp(setup))
                npcs[i] = clone_npc(npcs[i], file, 0, setup);
            else
                npcs[i] = clone_npc(npcs[i], file);
            if ((delay > 0.0) && (++c < s))
            {
                set_alarm(delay + delay * rnd(), 0.0, 
                          &clone_npcs(npcs, file, delay, restrain_path, c,
setup));
                return -1;
            }
        }
    }

    return count;
}
