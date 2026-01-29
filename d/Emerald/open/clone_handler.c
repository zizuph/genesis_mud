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
 *   // give a unique id for this clone_handler **VERY IMPORTANT**
 *   set_clone_handler_id("Some_Dir clone handler");
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

#pragma no_clone

inherit "/d/Emerald/std/clone_handler";
