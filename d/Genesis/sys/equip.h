/*
 * /d/Genesis/sys/equip.h
 *
 * The code in this definition file may help wizards to control the number
 * of clones of their equipment. This equipment handler will not work on
 * all clones of a particular object. It will only count the clones actually
 * registered with this module. If a wizard manually clones the object as
 * well, this will not add to the number of registered clones. Also, when the
 * object-file is updated, the count is not reset.
 *
 * NOTICE: This .h file and its counterpart .c have been set up to be robust.
 * This may make them slightly less speedy as what might be possible. The
 * module is meant for pieces of equipment of which not many clones should
 * exist.
 *
 * The following macros are defined:
 *
 * int    EQUIP_COUNT(string/object file)
 * void   EQUIP_REGISTER(object obj)
 * void   EQUIP_UNREGISTER(object obj)
 * object EQUIP_CLONE(string file, int number)
 * object EQUIP_ALTERNATIVE(string file, int number, string alternative)
 *
 * Written by Mercade on March 19 1997.
 */

#ifndef _GENESIS_SYS_EQUIP
#define _GENESIS_SYS_EQUIP

#define EQUIP_FILE "/d/Genesis/sys/global/equip"

/*
 * int EQUIP_COUNT(string/object file)
 *
 * The macro returns the number of clones registered in this equipment
 * handler. As argument it needs the filename of a file or objectpointer to
 * a clone. Before the registered clones are counted, their validity is
 * checked, i.e. when an object is destructed, it are automatically
 * unregistered.
 */
#define EQUIP_COUNT(file) (EQUIP_FILE->equip_count(file))

/*
 * void EQUIP_REGISTER(object obj)
 *
 * The macro will register the object "obj" as clone of a certain piece of
 * equipment.
 */
#define EQUIP_REGISTER(obj) (EQUIP_FILE->equip_register(obj))

/*
 * void EQUIP_UNREGISTER(object obj)
 *
 * The macro will "unregister" the "object" as clone of a certain piece of
 * equipment. Strictly speaking this is not necessary to do this because the
 * validity of all registered objects is tested when the number of clones is
 * counted. However, it makes for cleaner code if you unregister it yourself
 * when you destruct it.
 */
#define EQUIP_UNREGISTER(obj) (EQUIP_FILE->equip_unregister(obj))

/*
 * object EQUIP_CLONE(string file, int number)
 *
 * The macro will clone "file" and return its objectpointer if LESS than
 * "number" of clones have already been registered. The clone is automatically
 * registered. If too many clones have already been registered ( >= "number" )
 * then 0 is returned.
 *
 * NOTICE: The euid of the cloning object must be set.
 */
#define EQUIP_CLONE(file, number) (EQUIP_FILE->equip_clone((file), (number)))

/*
 * object EQUIP_ALTERNATIVE(string file, int number, string alternative)
 *
 * The macro will clone "file" and return its objectpointer if LESS than
 * "number" of clones have already been registered. The clone is automatically
 * registered. If too many clones have already been registered ( >= "number" )
 * then the file "alternative" is cloned returned. Note that the alternative
 * is NOT automatically registered.
 *
 * NOTICE: The euid of the cloning object must be set.
 */
#define EQUIP_ALTERNATIVE(file, number, alternative) \
    (EQUIP_FILE->equip_alternative((file), (number), (alternative)))

/* No definitions beyond this line. */
#endif _GENESIS_SYS_EQUIP
