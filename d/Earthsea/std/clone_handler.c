/* This file helps to handle cloning and distributing clones throughout
 * an area.  When configured, it will attempt to maintain a given number
 * of specified clones in a given area.
 *
 * Example usage:
 *
 * inherit "/d/Domain/std/clone_handler";
 *
 * void create_clone_handler()
 * {
 *   // give a default directory to use for distributing clones
 *   set_default_area("/d/Domain/some_dir/");
 *
 *   // Designate a few npcs to be cloned
 *   // add_clone() takes 5 arguments:
 *   //     arg 1 - The file from which to clone
 *   //     arg 2 - A unique id for the clones
 *   //     arg 3 - How many clones to maintain
 *   //     arg 4 - Where to deposit the clones (optional)
 *   //     arg 5 - A special message to give when the clones
 *   //             arrive at their destinations (optional)
 *   add_clone("/d/Domain/some_dir/npc/curan", 1, 1, 
 *           "/d/Domain/some_dir/o1");
 *   add_clone("/d/Domain/some_dir/npc/wanderguard", 2, 4);
 *   add_clone("/d/Domain/some_dir/npc/guard", 3, 4, 
 *           ({ "/d/Domain/some_dir/o1", "/d/Domain/some_dir/o2" }),
 *           "A guard wanders in.\n");
 *
 *   // The room /d/Domain/some_dir/o2 should not receive clones
 *   // unless it is specifically given.
 *   add_excluded_destination("/d/Domain/some_dir/o2");
 *
 * }
 *
 * The above will cause
 * 1)  1 clone of /d/Domain/some_dir/npc/curan to be cloned and 
 *     deposited in /d/Domain/some_dir/o1.
 * 2)  4 clones of /d/Domain/some_dir/npc/wanderguard to be cloned and
 *     distributed randomly through the default area, which is the
 *     directory /d/Domain/some_dir/, but not the room
 *     /d/Domain/some_dir/o2.  Whenever the clone_handler resets,
 *     it will replenish missing wanderguards.
 * 3)  4 clones of /d/Domain/some_dir/npc/guard to be cloned and dis-
 *     tributed randomly between /d/Domain/some_dir/o1 and 
 *     /d/Domain/some_dir/o2.  Whenever the clone_handler resets, it
 *     will replenish missing guards.  The message "A guard wanders
 *     in." will be printed in the destination room.
 *
 * 
 * Loading the clone_handler:
 *     It is important that the clone_handler be loaded as soon as players
 *     enter the clone_handler's area.  To manage this, the following line
 *     of code can be placed in the init() of the entrances to your area
 *     (it might also be a good idea to put it in commonly accessed
 *     rooms): 
 *              if (interactive(this_player()))
 *                  catch(call_other("/d/path/to/clone_handler", "??"));
 *
 * NB: When directories are specified for clone destinations, it is im-
 *     portant that those directories contain as few invalid destination
 *     files as possible.  The reason for this is that the clone_handler
 *     will attempt to load random files in the directory as it searches
 *     for an acceptible room; the more invalid files in a directory,
 *     the greater the chance that one of them will be loaded unecessarily
 *     by the clone_handler.  Also note, though, that a file that cannot
 *     be loaded by the clone_handler will be ignored after the first
 *     attempt to load it, so while invalid files can waste cpu, they only
 *     do it once.
 *
 * If you have any questions/comments/suggestions, mail Shiva.
 */

#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

static int stopped;
static string clone_file;
static string *bad_rooms = ({});
static string *excluded_rooms = ({});
static object clone_list;
static mapping potential_rooms = ([]);
static mapping clones_to_add = ([]);

mapping clone_map = ([]);

static string *default_area = ({});

varargs object random_room(string *area, int exclude);
object *query_clones();


mapping clean_map(mapping m)
{
    mapping m2 = ([]);
    object *indices = (object *)m_indices(m) - ({ 0 });
    int i;

    for (i = 0; i < sizeof(indices); i++)
    {
        m2[indices[i]] = m[indices[i]];
    }

    return m2;
}

/* Function name: add_clone
 * Description:   add a clone to those that will be cloned by the 
 *                clone_handler
 * Arguments:     string path   - The path to the clone's file
 *                mixed id      - A unique id for the clone
 *                int how_many  - How many clones to maintain.
 *                mixed where   - The path for the destination of these
 *                                clones.  
 *                                If specified as an array of paths, a
 *                                random destination will be chosen.  
 *                                If unspecified, the clone will be 
 *                                placed in a random room, chosen from
 *                                the default area designated by 
 *                                set_default_area.
 *                string mv_msg - A special message to give when the
 *                                clone arravies at its destination.
 *                                If unspecified, the standard "<npc> arrives."
 *                                message will be given for npcs and no message
 *                                will be given for non-livings.
 * Returns:       1 - clone added;
 *                0 - clone not added
 */                              
varargs int add_clone(mixed path, mixed id, mixed how_many = 1, 
    mixed destination = 0, mixed move_msg = 0)
{
    if (stringp(path) || functionp(path))
    {
        if (stringp(destination))
        {
            destination = ({ destination });
        }

        if (destination && !pointerp(destination))
        {
            return 0;
        }
 
        clones_to_add[id] = ({ how_many, destination, move_msg, path });
        return id;
    }

    return 0;
}

/* Function name: remove_clone
 * Description:   stop further cloning of the group of clones identified
 *                by the given id (see add_clone())
 * Arguments:     mixed id - An identifier previously given in add_clone()
 * Returns:       1 - removed;
 *                0 - not removed
 */
int remove_clone(mixed id)
{
    int size = m_sizeof(clones_to_add);
    clones_to_add = m_delete(clones_to_add, id);
    return (size != m_sizeof(clones_to_add));
}


/* Function name: query_clone_info
 * Description:   get the cloning information used by the clone_handler
 * Returns:       a mapping that maps clone ids to an array of clone
 *                information as specified in add_clone()
 */
mapping query_clone_info()
{
    return clones_to_add + ([]);
}

  
/* Function name: set_clone_file
 * Description:   Designate a file to use to store the clone_handler's
 *                data.
 * Arguments:     The filename
 * Returns:       1
 */
int set_clone_file(string file)
{
    clone_file = file;
    return 1;
}

/* Function name: set_default_area
 * Description:   Give the directories and/or files from which random rooms 
 *                will be chosen for destinations for clones
 * Arguments:     mixed area - an array of files and/or directories from
 *                             which to select destinations
 * Returns:       1 - set; 0 - not set
 */
int set_default_area(mixed area)
{
    if (stringp(area))
    {
        area = ({ area });
    }

    if (!pointerp(area)) 
    {
        return 0;
    }

    default_area = area;
    return 1;
}

/* Function name: set_excluded_destinations
 * Description:   Give those rooms which should not be considered
 *                for destinations for the clone_handler's clones.
 *                This is only considered when a directory is given
 *                as a destination; if an excluded room is specifically
 *                given, a clone will be placed there regardless.
 *                Note that any valid wildmatch() pattern can be used
 *                to specify a destination or group of destinations.
 * Arguments:     mixed dests - An array of room paths
 * Returns:       1 - set; 0 - not set
 */                              
int set_excluded_destinations(string *dests)
{
    excluded_rooms = (dests ? dests : ({ }));
    return 1;
}

/* Function name: add_excluded_destination
 * Description:   Designate that a room should not be considered
 *                as a destination for the clone_handler's clones.
 *                This is only considered when a directory is given
 *                as a destination; if an excluded room is specifically
 *                given, a clone will be placed there regardless.
 *                Note that any valid wildmatch() pattern can be used
 *                to specify a destination or group of destinations.
 * Arguments:     string dest - the path to the room file
 * Returns:      1 - added; 0 - not added
 */
int add_excluded_destination(string dest)
{
    if (!dest)
    {
        return 0;
    }

    excluded_rooms += ({ dest });
    return 1;
}

/* Function name: remove_excluded_destination
 * Description:   Remove a room from the list of rooms designated
 *                as invalid destinations for clone_handler clones.
 * Arguments:     string dest - the path to the room file to be removed
 * Returns:       1 - removed; 0 - not removed;
 */
int remove_excluded_destination(string dest)
{
    int size = sizeof(excluded_rooms);
  
    excluded_rooms -= ({ dest });
    return (size != sizeof(excluded_rooms));
}

/* Function name: query_excluded_destinations
 * Description:   Get the rooms which are not considered for
 *                destinations for the clone_handler's clones
 * Returns:       an array of paths to excluded rooms
 */
string *query_excluded_destinations()
{
    return excluded_rooms + ({});
}

/* Function name: set_clone_handler_id
 * Description:   OBSOLETE.  This is here for backward-compatibility.
 */
int set_clone_handler_id(mixed id) { return 1; }


/* Function name: register
 * Description:   register a clone with this clone_handler.
 * Arguments:     object ob - the clone to register
 * Returns:       1 - clone registered; 0 - clone not registered
 */
int register(object ob, int id)
{
    if (member_array(ob, query_clones()) >= 0)
    {
        return 0;
    }

    clone_map[ob] = id;
    return 1;
}

/* Function name: unregister
 * Description:   unregister a clone that is registered with this 
 *                clone_handler
 * Arguments:     object ob - the clone to unregister
 * Returns:       1 - clone unregistered; 0 - clone not unregistered
 */
int unregister(object ob)
{
    if (member_array(ob, query_clones()) < 0)
    {
        return 0;
    }

    clone_map = m_delete(clone_map, ob);
    return 1;
}

/* Function name: clones_from_id
 * Description:   Given an id, get the registered clones cloned from
 *                that file.
 * Arguments:     string file - the path to a file
 * Returns:       an array of matching objects
 */
object *clones_from_id(int id)
{
    object *clones = query_clones();
    return filter(clones, &operator(==)(id) @ &operator([])(clone_map));
}

/* Function name: clone
 * Description:   Given a path and a destination, clone path and move it to
 *                destination
 * Arguments:     mixed id    - the id of the clones to create
 *                mixed where - the path to the destination, an array of 
 *                              destination paths, or the destination 
 *                              object itself.
 *                mixed how   - A message to give when a clone arrives
 *                              at its destination
 *                mixed path  - the path to the object to clone
 *
 * Returns:       1 - cloned and moved; 0 - not cloned or not moved
 */
varargs int clone(mixed id, mixed where, mixed how, mixed path)
{
    object cl;
    int ret;

#ifdef NO_CLONES
    return 0;
#endif

    if (stopped)
    {
        return 0;
    }

    where = check_call(where);
    if (where)
    {
        if (stringp(where))
        {
            where = ({ where });
        }
  
        if (!pointerp(where))
        {
            return 0;
        }

        where = random_room(where);
    }    
    else
    {
        where = random_room(default_area);
    }

    if (!objectp(where))
    {
        return 0;
    }   

    setuid();
    seteuid(getuid());

    path = check_call(path);
    if (!strlen(path) || !(cl = clone_object(path)))
    {
        return 0;
    }

    tell_room(this_object(), "Cloned " + cl->query_name() + "(" +
        file_name(cl) + ")....\nDestination: " + file_name(where) + "\n");

    register(cl, id);

    if (function_exists("move_living", cl))
    {
        how = check_call(how);
        if (how)
        {
            ret = cl->move_living("M", where);
     
            if (!ret)
            {
                tell_room(where, how);
            }

            return !ret;
        }

        return !cl->move_living("exit", where);
    }

    return !cl->move(where, 1);
}

/* Function name: query_clone_envs
 * Description:   get the environments of the registered clones
 * Returns:       a mapping which maps cloned objects to environments  
 */
mapping query_clone_envs()
{
    object *clones = query_clones();
    return mkmapping(clones, map(clones, environment));
}

/* Function name: query_clones
 * Description:   get the clones registered with this clone_handler
 * Returns:       an array of cloned objects
 */
object *query_clones()
{
    return filter(m_indices(clone_map), &operator(!=)(0));
}

mapping query_clones_map()
{
    clone_map = clean_map(clone_map);
    return clone_map + ([]);
}

/* Function name: clear_clones
 * Description:   unregister all clones
 */
void clear_clones()
{
    clone_map = ([]);
}

/* Function name: remove_clones
 * Description:   remove all registered clones
 */
void remove_clones()
{
    query_clones()->remove_object();
    clear_clones();
}

/* Function name: stop_clones
 * Description:   stop cloning of new objects
 * Returns:       1 - cloning stopped (was not previously stopped);
 *                0 - cloning stopped (was previously stopped)
 */
int stop_clones()
{
    int old_stopped = stopped;
    return (old_stopped != (stopped = 1));
}

/* Function name: start_clones
 * Description:   start cloning of new object
 * Returns:       1 - cloning started (was previously stopped)
 *                0 - cloning started (was not previously stopped)
 */
int start_clones()
{
    int old_stopped = stopped;
    return (old_stopped != (stopped = 0));
}

/* Function name: add_many_clones
 * Description:   slowly add a group of clones to avoid too much
 *                processing at once and problems should one object
 *                be buggy
 * Arguments:     mixed clone_add_list - an array of arrays that can be
 *                passed
 *                to clone via applyv
 */
void add_many_clones(mixed *clone_add_list)
{
    if (!sizeof(clone_add_list))
    {
        return;
    }

    set_alarm(0.5, 0.0, &add_many_clones(clone_add_list[1..]));

    applyv(clone, clone_add_list[0]);
}

/* Function name: clones_needed
 * Description:   return how many clones are needed to bring the
 *                total number of clones to the value given in 
 *                add_clones
 * Arguments:     string path - a pathname for the objects to clone
 * Returns:       how many clones are needed (int)
 */
int clones_needed(int id)
{
    mixed clone_info;
    int how_many;

    clone_info = clones_to_add[id];

    if (!pointerp(clone_info))
    {
        return 0;
    }
    else
    {
        if (!sizeof(clone_info))
        {
            return 0;
        }

        how_many = check_call(clone_info[0]);
    } 

    return MAX(0, how_many - sizeof(clones_from_id(id)));
}

/* Function name: restore_clones
 * Description:   clone enough new objects to bring the total numbers to
 *                the levels given in set_clones_to_add
 */
void restore_clones()
{
    string how;
    int i, needed, *ids;
    mixed where = 0, *clone_add_list = ({ }), *clone_info;

    ids = m_indices(clones_to_add);

    for (i = sizeof(ids); i--;)
    {
        needed = clones_needed(ids[i]);

        clone_info = clones_to_add[ids[i]];
        if (pointerp(clone_info))
        {
            while (needed-- > 0)
            {
                clone_add_list += ({ ({ ids[i], clone_info[1],
                    clone_info[2], clone_info[3] }) });
            }
        }

    }

    /* do in an alarm so that buggy files don't cause any problems
     * for the clone_handler
     */
    set_alarm(0.0, 0.0, &add_many_clones(clone_add_list[1..]));
}

/* Function name: reset_clone_handler
 * Description:   ...called when the clone_handler resets.  Redefine this
 *                for whatever reset functionality you want.
 */
void reset_clone_handler() { }

/* clones are restored every time the room resets */  
void reset_room()
{
    tell_room(this_object(), "Resetting " + short() + ".\n");

    reset_clone_handler();
    restore_clones();
}

/* Function name: create_clone_handler
 * Descripton:    redefine this to configure your clone_handler room
 */
void create_clone_handler() { }

string clone_handler_desc()
{
  return 
      "  To get a list of all active clones generated by this room:\n" +
      "      Call here query_clones\n" +
      "  To get a list of the environments of active clones generated by " +
      "this room:\n" +
      "      Call here query_clone_envs\n" +
      "  To remove all clones generated by this room:\n" +
      "      Call here remove_clones\n" +
      "  To temporarily stop clone generation:\n" +
      "      Call here stop_clones\n" +
      "  To restart clone generation:\n" + 
      "      Call here start_clones\n";
}
  
/* Set up the clone_handler room */
void create_room()
{
    setuid();
    seteuid(getuid());

    set_short("Clone Generator");
    set_long("This room clones and distributes objects throughout an area.\n" +
        clone_handler_desc());

    bad_rooms = ({ file_name(this_object()) });

    create_clone_handler();

    if (!strlen(clone_file))
    {
        string *split = explode(file_name(this_object()), "/");
        clone_file = implode(split[..(sizeof(split) - 2)], "/") + 
            "/clone_handler";
    }

    restore_object(clone_file);

    if (!mappingp(clone_map))
    {
        clone_map = ([]);
    }
    else
    {
        clone_map = clean_map(clone_map);
    }

    /* replenish clones */
    restore_clones();
 
    add_prop(ROOM_I_NO_CLEANUP, 1);
}

mixed exclude_rooms(string filename)
{
    int i;

    if (wildmatch("*.c", filename))
    {
        filename = extract(filename, 0, -3);
    }

    for (i = 0; i < sizeof(excluded_rooms); i++)
    {
        if (wildmatch(excluded_rooms[i], filename))
        {
            return 0;
        }
    }

    return filename;
}

/* Function name: random_room
 * Description:   choose a random room from those given
 * Arguments:     string *area - an array of pathnames to rooms or
 *                               directories.  If directories are given,
 *                               a random room will be chosen from rooms in
 *                               the directory.
 *                int exclude - if true, rooms in the excluded_rooms list
 *                              will not be returned.
 * Returns:       the room object or 0 if no room was found
 */
varargs object random_room(string *area, int exclude = 1)
{
    string *rooms = ({ }), *dir_files, *valid_files = ({ }), ran_room, fn;
    object room;
    int i, j;

    if (!area)
    {
        return 0;
    }

    setuid();
    seteuid(getuid());

    for (i = 0; i < sizeof(area); i++)
    {
        if (file_size(area[i]) == -2)
        {
            /* we don't want to be searching through directories each 
             * time we look for a random room, so we only do it once for
             * each directory, saving the results in a global mapping,
             * potential_rooms.
             */
            if (potential_rooms[area[i]])
            {
                dir_files = potential_rooms[area[i]];

                if (exclude)
                {
                    dir_files = map(dir_files, exclude_rooms) - ({ 0 });
                }

                rooms += dir_files;
            }
            else
            {
                dir_files = get_dir(area[i]);
                for (j = 0; j < sizeof(dir_files); j++)
                {
                    fn = area[i] + dir_files[j];
                    if (wildmatch("*.c", fn) && (file_size(fn) > 0))
                    {
                        valid_files += ({ fn[..-3] });
                    }
                }

                potential_rooms[area[i]] = valid_files;

                if (exclude)
                {
                    valid_files = map(valid_files, exclude_rooms) - ({ 0 });
                }

                rooms += valid_files;
            }
        }
        else
        {
            rooms += ({ area[i] });
        }
    }

    // remove any files that are already known to be invalid
    rooms -= bad_rooms;

    // get a random room from the rooms array
    while (1)
    {
        if (!sizeof(rooms))
        {
            return 0;
        }

        ran_room = rooms[random(sizeof(rooms))];
        if (!(room = find_object(ran_room)))
        {
            // attempt to load the file
            if (stringp(catch(call_other(ran_room, "??"))) ||
                !(room = find_object(ran_room)))
            {
                /* the file could not be loaded, so we add it to the
                 * bad_rooms array so that it doesn't have to be checked
                 * again in the future.
                 */
                bad_rooms += ({ ran_room });
                rooms -= ({ ran_room });
                continue;
            }
        }

        if (!room->query_prop(ROOM_I_IS))
        {
            // the object loaded is either not a room or not a valid room
            bad_rooms += ({ ran_room });
            rooms -= ({ ran_room });
            continue;
        }

        break;
    }

    return room;
}

/* Send non-interactive objects that enter this room out the random exit */
void enter_inv(object ob, object from)
{
    object ran_room;

    ::enter_inv(ob, from);

    if (interactive(ob))
    {
        return;
    }

#ifndef NO_MOVE
    if (ran_room = random_room(default_area, 1))
    {
        tell_room(this_object(), "Moving " + ob->query_name() + "(" +
           file_name(ob) + ")....\nDestination: " + 
           file_name(ran_room) + "\n");

        if (function_exists("move_living", ob))
        {
            ob->move_living("exit", ran_room);
        }
        else
        {
            ob->move(ran_room, 1);
        }
    }
#endif
}

void save()
{
    if (strlen(clone_file))
    {
        save_object(clone_file);
    }
}

/* Try to make sure things are safe when removing this object.
 */
void remove_object()
{
    save();
    ::remove_object();
} 
