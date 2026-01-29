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
 *   // designate a few npcs to be cloned
 *   add_clone("/d/Domain/some_dir/npc/curan", -1, 
 *           "/d/Domain/some_dir/o1");
 *   add_clone("/d/Domain/some_dir/npc/wanderguard", 4);
 *   add_clone("/d/Domain/some_dir/npc/guard", 4, 
 *           ({ "/d/Domain/some_dir/o1", "/d/Domain/some_dir/o2" }),
 *           "A guard wanders in.\n");
 *
 *   // The room /d/Domain/some_dir/o2 should not receive clones
 *   //  unless it is specifically given.
 *   add_excluded_destination("/d/Domain/some_dir/o2");
 *
 *   // give a unique id for this clone_handler **VERY IMPORTANT**
 *   set_clone_handler_id("Some_Dir clone handler");
 * }
 *
 * The above will cause
 * 1)  1 clone of /d/Domain/some_dir/npc/curan to be cloned only when 
 *     the  clone_handler loads; the clone will be deposited in 
 *     /d/Domain/some_dir/o1.
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
 *     of code can be placed in the create_room() of the entrances to your
 *     area (it might also be a good idea to put it in commonly accessed
 *     rooms): 
 *              catch(call_other("/d/path/to/clone_handler", "??"));
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
 * The rather peculiar mechanism for keeping track of npcs was spawned out
 * of a desire to avoid having to maintain a file listing current clones
 * (even though that method would probably be simpler).  Perhaps in the 
 * future a version of the clone_handler that handles both methods would 
 * be a good idea.
 *
 * If you have any questions/comments/suggestions, mail Shiva.
 */

#pragma strict_types
#pragma no_clone

inherit "/std/room";

#include <macros.h>
#include <stdproperties.h>

#define OBJ_M_CLONE_HANDLER_ID "_obj_m_clone_handler_id"
#define OBJ_AO_CLONE_LIST      "_obj_ao_clone_list"
#define OBJ_I_LAST_UPDATE      "_obj_i_last_update"

#define UPDATE_TIME       clone_list->add_prop(OBJ_I_LAST_UPDATE, time())
#define SET_CLONE_LIST(x) clone_list->add_prop(OBJ_AO_CLONE_LIST, x)

static int stopped;
static int startup = 0;
static string *bad_rooms = ({ });
static string *excluded_rooms = ({ });
static object clone_list;
static mapping potential_rooms = ([ ]);
static mapping clones_to_add = ([ ]);

static string *default_area = ({ });
static string clone_handler_id;

varargs object random_room(string *area, int exclude);
object *query_clones();
object get_clone_list();

/* Function name: add_clone
 * Description:   add a clone to those that will be cloned by the 
 *                clone_handler
 * Arguments:     string path   - The path to the clone's file
 *                int how_many  - How many clones to maintain.
 *                                A negative value indicates that 
 *                                ABS(how_many) should be cloned, 
 *                                but only when the clone_handler 
 *                                is first loaded; they will not
 *                                be replenished as the clone_handler
 *                                resets.
 *                mixed where   - The path for the destination of these
 *                                clones.  
 *                                If specified as an array of paths, a
 *                                random destination will be chosen.  
 *                                If unspecified, the clone will be 
 *                                placed in a random room, chosen from
 *                                the default area designated by 
 *                                set_default_area.
 *                string mv_msg - 
 * Returns:       1 - clone added;
 *                0 - clone not added
 */                              
varargs int add_clone(string path, int how_many = 1, 
    mixed destination = 0, string move_msg = 0)
{
  if (path)
  {
    if (stringp(destination))
    {
      destination = ({ destination });
    }

    if (destination && !pointerp(destination))
    {
      return 0;
    }

    clones_to_add[path] = ({ how_many, destination, move_msg });
    return 1;
  }

  return 0;
}

/* Function name: remove_clone
 * Description:   remove a path from those that will be cloned by the 
 *                clone_handler
 * Arguments:     string path - the pathname
 * Returns:       1 - path removed;
 *                0 - path not removed
 */
int remove_clone(string path)
{
  if (clones_to_add[path])
  {
    clones_to_add = m_delete(clones_to_add, path);
    return 1;
  }

  return 0;
}

/* Function name: query_clone_info
 * Description:   get the cloning information used by the clone_handler
 * Returns:       a mapping that maps path names to a two-element array of 
 *                the form ({ (int) how_many, (mixed) destination })--these 
 *                correspond to the final two arguments to add_clone
 */
mapping query_clone_info()
{
  return clones_to_add;
}
  
/* Function name: set_clones
 * Description:   designate what to clone and how many to clone
 * Arguments:     mapping m - a mapping which maps an object's path to
 *                            an array that contains these elements:
 *                            0 - how many objects to clone
 *                            1 - the path to the room where they should
 *                                be moved (0 if random)
 * Returns:       1 - information set; 0 - information not set
 */
int set_clones(mapping m)
{
  if (m)
  {
    clones_to_add = m;
    return 1;
  }

  return 0;
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
  return excluded_rooms;
}

/* Function name: set_clone_handler_id
 * Description:   set the unique id for this clone_handler.  It is _very_
 *                important that this be unique.
 * Arguments:     mixed id - the id for this clone_handler
 * Returns:       1 - id set; 0 - id not set
 */
int set_clone_handler_id(mixed id)
{
  if (id)
  {
    clone_handler_id = id;
    return 1;
  }

  return 0;
}

/* Function name: register
 * Description:   register a clone with this clone_handler.
 * Arguments:     object ob - the clone to register
 * Returns:       1 - clone registered; 0 - clone not registered
 */
int register(object ob)
{
  object *clones = query_clones();

  if (member_array(ob, clones) >= 0)
  {
    return 0;
  }

  SET_CLONE_LIST(clones + ({ ob }));
  UPDATE_TIME;
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
  object *clones = query_clones();

  if (sizeof(clones) != sizeof(clones -= ({ ob })))
  {
    SET_CLONE_LIST(clones);
    UPDATE_TIME;
    return 1;
  }

  return 0;
}

/* Function name: clones_from_filename
 * Description:   Given a filename, get the registered clones cloned from
 *                that file.
 * Arguments:     string file - the path to a file
 * Returns:       an array of matching objects
 */
object *clones_from_filename(string file)
{
  object *clones = query_clones(), *ret_clones = ({ });
  int i;

  for (i = 0; i < sizeof(clones); i++)
  {
    if (clones[i] && (MASTER_OB(clones[i]) == file))
    {
      ret_clones += ({ clones[i] });
    }
  }

  return ret_clones;
}

/* Function name: clone
 * Description:   Given a path and a destination, clone path and move it to
 *                destination
 * Arguments:     string path - the path to the object to clone
 *                mixed where - the path to the destination, an array of 
 *                              destination paths, or the destination 
 *                              object itself.
 * Returns:       1 - cloned and moved; 0 - not cloned or not moved
 */
varargs int clone(string path, mixed where, string how)
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

  if (!(cl = clone_object(path)))
  {
    return 0;
  }

  tell_room(this_object(), "Cloned " + cl->query_name() + "(" +
      file_name(cl) + ")....\nDestination: " + file_name(where) + "\n");

  register(cl);

  if (function_exists("move_living", cl))
  {
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
  object *clones;

  if (clone_list)
  {
    clones = clone_list->query_prop(OBJ_AO_CLONE_LIST);
    return (pointerp(clones) ? (clones - ({ 0 })) : ({ }));
  }

  return ({ });
}

/* Function name: clear_clones
 * Description:   unregister all clones
 */
void clear_clones()
{
  SET_CLONE_LIST(({ }));
  UPDATE_TIME;
}

/* Function name: remove_clones
 * Description:   remove all registered clones
 */
void remove_clones()
{
  query_clones()->remove_object();
  SET_CLONE_LIST(query_clones());
  UPDATE_TIME;
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
int clones_needed(string path)
{
  mixed clone_info;
  int how_many;

  clone_info = clones_to_add[path];

  if (!pointerp(clone_info))
  {
    how_many = clone_info;
  }
  else
  {
    if (!sizeof(clone_info))
    {
      return 0;
    }

    how_many = clone_info[0];

    if (how_many < 0)
    {
      if (!startup)
      {
        return 0;
      }
       
      how_many = -how_many;
    }
  } 

  return MAX(0, how_many - sizeof(clones_from_filename(path)));
}

/* Function name: restore_clones
 * Description:   clone enough new objects to bring the total numbers to
 *                the levels given in set_clones_to_add
 */
void restore_clones()
{
  string *clone_paths, how;
  int i, needed;
  mixed where = 0, *clone_add_list = ({ }), *clone_info;

  clone_paths = m_indices(clones_to_add);

  for (i = sizeof(clone_paths); i--;)
  {
    needed = clones_needed(clone_paths[i]);

    clone_info = clones_to_add[clone_paths[i]];
    if (pointerp(clone_info))
    {
      where = ((sizeof(clone_info) > 1) ? clone_info[1] : 0);
      how   = ((sizeof(clone_info) > 2) ? clone_info[2] : 0);
    }

    while (needed-- > 0)
    {
      clone_add_list += ({ ({ clone_paths[i], where, how }) });
    }
  }

  add_many_clones(clone_add_list);
}

/* Function name: new_clone_list
 * Description:   clone and initialize a new clone_list object
 * Arguments:     object *clones - an array of objects to be used to
 *                                 initialize the list of registered
 *                                 clones
 * Returns:       1 - new clone_list object cloned;
 *                0 - failed to clone new clone_list object
 */
varargs int new_clone_list(object *clones = ({ }))
{
  object ob;

  setuid();
  seteuid(getuid());

  if (ob = clone_object("/std/object"))
  {
    if (clone_list)
    {
      clone_list->remove_object();
    }

    clone_list = ob;
    clone_list->add_prop(OBJ_AO_CLONE_LIST, clones);
    clone_list->add_prop(OBJ_M_CLONE_HANDLER_ID, clone_handler_id);
    UPDATE_TIME;

    return 1;
  }

  return 0;
}

/* Function name: get_clone_list
 * Description:   get the clone_list object.  If one doesn't exist,
 *                create it.
 * Returns:       the clone_list object or 0 if one could not be created.
 */
object get_clone_list()
{
  object ob, *obs;
  int i, latest_time = 0;

  if (clone_list)
  {
    return clone_list;
  }

  ob = find_object("/std/object");
  if (!ob || !sizeof(obs = filter(object_clones(ob),
      &operator(==)(clone_handler_id) @ 
      &->query_prop(OBJ_M_CLONE_HANDLER_ID))))
  { 
    // couldn't find a clone_list...try to create a new one.
    return (new_clone_list() ? clone_list : 0);
  }

  if (sizeof(obs) == 1)
  {  
    clone_list = obs[0];
  }
  else
  {
    for (i = sizeof(obs); i--;)
    {
      // get the most recently updated clone_list
      if (obs[i]->query_prop(OBJ_I_LAST_UPDATE) > latest_time)
      {
        latest_time = obs[i]->query_prop(OBJ_I_LAST_UPDATE);
        clone_list = obs[i];
      }
    }
  }

  if (clone_list)
  {
    UPDATE_TIME;
  }

  return clone_list;
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

  restore_clones();
  reset_clone_handler();
}

/* Function name: create_clone_handler
 * Descripton:    redefine this to configure your clone_handler room
 */
void create_clone_handler() { }

string clone_handler_desc()
{
  return 
      "  To get a list of all active npcs generated by this room:\n" +
      "      Call here query_clones\n" +
      "  To get a list of the environments of active npcs generated by " +
      "this room:\n" +
      "      Call here query_clone_envs\n" +
      "  To remove all npcs generated by this room:\n" +
      "      Call here remove_clones\n" +
      "  To temporarily stop npc generation:\n" +
      "      Call here stop_clones\n" +
      "  To restart npc generation:\n" + 
      "      Call here start_clones\n";
}
  
/* Set up the clone_handler room */
void create_room()
{
  startup = 1;

  set_short("Clone Generator");
  set_long("This room clones and distributes objects throughout an area.\n" +
      clone_handler_desc());

  bad_rooms = ({ MASTER });

  create_clone_handler();

  setuid();
  seteuid(getuid());

  /* create the clone_list object */
  clone_list = get_clone_list();

  /* replenish clones */
  restore_clones();

  startup = 0;
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
  string *rooms = ({ }), *dir_files, *valid_files = ({ }), ran_room,
         fn;
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
      /* we don't want to be searching through directories each time we
       * we look for a random room, so we only do it once for each
       * directory, saving the results in a global mapping, potential_rooms.
       */
      if (potential_rooms[area[i]])
      {
        dir_files = potential_rooms[area[i]];

        if (exclude)
        {
          dir_files -= excluded_rooms;
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
          valid_files -= excluded_rooms;
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
        file_name(ob) + ")....\nDestination: " + file_name(ran_room) + "\n");

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

/* Try to make sure things are safe when removing this object...try
 * to handle any situations where the clones might be lost
 */
void remove_object()
{
  object ob;

  /* Since we rely on object_clones to find the clone_list after this
   * object is destroyed, it is important that the clone_list is cloned
   * from the current /std/object master.  Since /std/object (hopefully)
   * is updated very infrequently, this should occur extremely rarely; if
   * it does, we clone a new clone_list from the current /std/object 
   * master.
   *
   * Note: If this object is destroyed and not loaded immediately, and 
   *       during the time that it is not loaded, /std/object is updated,
   *       the clone_list object cannot be recovered.
   */
  if (clone_list && 
      (ob = find_object("/std/object")) &&
      (member_array(clone_list, object_clones(ob)) < 0))
  {
    new_clone_list(query_clones());
  }

  ::remove_object();
} 
