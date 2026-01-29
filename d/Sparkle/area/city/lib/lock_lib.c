/* 
 * Lock Inheritable Library
 *
 * This implements the lock/unlock/pick functionality for any receptable.
 * It is called by a standard receptacle if set_cf is called.
 *
 *   Example:
 *      inherit "/d/Sparkle/area/city/lib/lock_lib";
 *      set_cf(this_object()); 
 *
 * All Sparkle receptacles can have the possibility of using the
 * new lock technology, guaranteeing a uniform standard of
 * thief technology.
 *
 * Created by Petros, June 2009
 */

#pragma strict_types


/*
 * These functions are called by the receptacle and will be implemented
 * here.:
 *
 *   varargs int open(object ob)
 *   varargs int close(object ob)
 *   varargs int lock(object ob)   Only if the container has a lock
 *   varargs int unlock(object ob) Only if the container has a lock
 *   varargs int pick(object ob)   Only is the lock is pickable
 */


