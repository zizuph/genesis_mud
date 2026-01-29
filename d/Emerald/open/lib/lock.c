#include <ss_types.h>
#include <language.h>
#include <macros.h>

static int locked = 1;
static int pick_diff;
static mixed key_id;
static mixed other_side;
static object locked_ob = this_object();
static object other_lock;
static mixed lock_id;

public void set_pick_difficulty(int diff);

/*
 * Function name: set_locked
 * Description:   Lock the lock.  It is recommended that you use lock()
 *                instead, since this will not correctly lock both sides
 *                of a double-sided lock.
 */
public void
set_locked()
{
    locked = 1;
}

/* 
 * Function name: set_unlocked
 * Description:   Unlock the lock.  It is recommended that you use unlock()
 *                instead, since this will not correctly unlock both sides
 *                of a double-sided lock.
 */
public void
set_unlocked()
{
    locked = 0;
}

/*
 * Function name: lock
 * Description:   Lock the lock.  This will also lock the other side
 *                of a double-sided lock.
 */
public void
lock()
{
    set_locked();
    other_lock->set_locked();
}

/*
 * Function name: unlock
 * Description:   Unlock the lock.  This will also unlock the other side
 *                of a double-sided lock.
 */
public void
unlock()
{
    set_unlocked();
    other_lock->set_unlocked();
}

/*
 * Function name: query_locked
 * Returns:       1 - lock locked
 *                0 - lock unlocked
 */
public int
query_locked()
{
    return locked;
}

/*
 * Function name: set_pick_difficulty
 * Description:   Indicate how difficult it is to pick the lock.
 * Arguments:     int diff - either -1 (to indicate an unpickable lock) or
 *                           a value 0 - 100 to indicate the difficulty in
 *                           picking the lock (0 easy, 100 extr. difficult).
 */
public void
set_pick_difficulty(int diff)
{
    pick_diff = diff;
}

/*
 * Function name: query_pick_difficulty
 * Returns:       The difficulty level for picking the lock.  -1 indicates
 *                that the lock cannot be picked.
 */
public int
query_pick_difficulty()
{
    return pick_diff;
}

/*
 * Function name: set_key
 * Description:   Designate the id for the key that opens this lock
 * Arguments:     mixed key - the id of the key that unlocks this lock
 */
public void
set_key(mixed key)
{
    key_id = key;
}

/*
 * Function name: query_key
 * Returns:       The id for the key that opens this lock.
 */
public mixed
query_key()
{
    return key_id;
}

/*
 * Function name: set_locked_object
 * Description:   Designate the object that is being locked by this lock
 * Arguments:     object ob - the locked object 
 */
public void
set_locked_object(object ob)
{
    locked_ob = ob;
}

/*
 * Function name: query_locked_object
 * Returns:      The object that is locked by this lock
 */
public object
query_locked_object()
{
    return locked_ob;
}

/*
 * Function name: set_other_side
 * Description:   For a double-sided lock, set the room on the other side
 *                that should be notified of the lock being locked, picked,
 *                etc.
 * Arguments:     mixed side - the filename of the other side or the object
 *                             pointer to the other side.
 */
public void
set_other_side(mixed side)
{
    other_side = side;
}

/*
 * Function name: query_other_side
 * Returns:       The room on the other side of the lock
 */
public mixed
query_other_side()
{
    return other_side;
}

/*
 * Function name: set_other_lock
 * Description:   For a double-sided lock, designate the other side 
 */
public void
set_other_lock(object lock)
{
    other_lock = lock;
}

public object
query_other_lock()
{
    return other_lock;
}

public void
set_lock_id(mixed id)
{
    lock_id = id;
}

public mixed
query_lock_id()
{
    return lock_id;
}

public int
pick_test(object picker)
{
    int skill;

    picker->add_mana(-10); /* Cost 10 mana to try to pick a lock.*/

    if (pick_diff < 0)
    {
        return 0;
    }

    skill = random(picker->query_skill(SS_OPEN_LOCK));

    if (skill > pick_diff)
    {
        set_unlocked();
        return 1;
    }

    return (skill - pick_diff - 1);
}

public int
try_pick_lock(object picker)
{
    int success;

    if (!query_locked())
    {
	picker->catch_tell("Much to your surprise, you find it unlocked " +
            "already.\n");
        return 0;
    }

    if (picker->query_mana() < 10)
    {
        picker->catch_tell("You can't concentrate enough to pick the lock.\n");
        return 0;
    }


    picker->catch_tell("You try to pick the lock.\n");
    tell_room(environment(picker), 
        QCTNAME(picker) + " tries to pick the lock.\n", picker);

    if (!locked_ob->pick(this_object()))
    {
        return 0;
    }

    success = pick_test(picker);

    if ((success == 0) || (success < -50))
    {
	picker->catch_tell("You failed to pick the lock. It seems " +
            "unpickable to you.\n");
        return 0;
    }

    if (success > 0)
    {
        picker->catch_tell("You get very satisfied when you hear a soft " +
            "'click' from the lock.\n");
        tell_room(environment(picker), "You hear a soft 'click' from the " +
            "lock.\n", picker);

        if (other_side)
	{
            tell_room(other_side, "You hear a soft 'click' from " +
                LANG_THESHORT(other_lock->query_locked_object()) + ".\n");
	}

        return 1;
    }

    picker->catch_tell("You failed to pick the lock.\n");
    return 0;
}

public int
match_key(object key)
{
    if (key)
    {
        if (!key_id)
	{
            write("You realize that the " + this_object()->short() + 
                " doesn't require a key.\n");
            return 0;
	}

        if (key_id != key->query_key())
	{
            write(capitalize(LANG_THESHORT(key)) + " doesn't fit.\n");
            return 0;
	}
    }
    else if (key_id)
    {
        write("You need something with which to " + query_verb() + 
            " the " + this_object()->short() + ".\n");
        return 0;
    }

    return 1;
}

public void
fail_lock_hook()
{
    write("The " + this_object()->short() + " is already locked.\n");
}

public void
lock_hook()
{
    write("Ok.\n");
    say(QCTNAME(this_player()) + " locks the " + this_object()->short() + ".\n");
    if (other_side)
    {
        tell_room(other_side, "You hear a soft 'click' from " +
            LANG_THESHORT(other_lock->query_locked_object()) + ".\n");
    }
}

public int
try_lock(object key)
{
    if (!match_key(key))
    {
        return 0;
    }

    if (locked)
    {
        fail_lock_hook();
        return 0;
    }

    if (!locked_ob->lock(this_object(), key))
    {
        return 0;
    }

    lock();
    lock_hook();
    return 1;
}
 
public void
fail_unlock_hook()
{
    write("The " + this_object()->short() + " is already unlocked.\n");
}

public void
unlock_hook()
{
    write("Ok.\n");
    say(QCTNAME(this_player()) + " unlocks the " + this_object()->short() + ".\n");

    if (other_side)
    {
        tell_room(other_side, "You hear a soft 'click' from " +
            LANG_THESHORT(other_lock->query_locked_object()) + ".\n");
    }
}

public int
try_unlock(object key)
{
    if (!match_key(key))
    {
        return 0;
    }

    if (!locked)
    {
        fail_unlock_hook();
        return 0;
    }

    if (!locked_ob->unlock(this_object(), key))
    {
        return 0;
    }

    unlock();
    unlock_hook();
    return 1;
}
