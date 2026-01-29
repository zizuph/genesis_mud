/*
 * range.h
 * 
 * Definitions to define the range of a spell.
 *
 * If a bit is set, it is considered a or, i.e.:
 *   RBIT_SELF | RBIT_INVENTORY
 * means, target may be the caster itself, or 
 * an item in the caster's inventory.
 */

#ifndef RANGE_H
#define RANGE_H

/* Target's locations. */
#define RBIT_SELF	1	/* May be cast on the caster.          */
#define RBIT_INVENTORY  2       /* May be cast on inventory.           */
#define RBIT_ROOM       4       /* May be cast on room itself.         */
#define RBIT_PRESENT    8       /* May be cast on objects in room.     */
#define RBIT_LOCS       16      /* May be cast on a room's location.   */
#define RBIT_ROOMS      32      /* May be cast on several rooms.       */

/* Target's state. */
#define RBIT_LIVE        64     /* May be cast on living objects.      */
#define RBIT_DEAD       128     /* May be cast on dead objects.        */
#define RBIT_UNSEEN     256     /* May be cast on unseen objects.      */

/* Target's relation with caster. */
#define RBIT_TEAM       512     /* Target must be in caster's team.    */
#define RBIT_ENEMY      1024    /* Target must be an enemy of caster.  */

/* Some shorthands. */
#define RANGE_SELF		    (RBIT_SELF | RBIT_LIVING)
#define RANGE_INVENTORY             (RBIT_INVENTORY | RBIT_DEAD)
#define RANGE_PRESENT_LIVE          (RBIT_SELF | RBIT_PRESENT | RBIT_LIVE)
#define RANGE_PRESENT_OTHER_LIVE    (RBIT_PRESENT | RBIT_LIVE)
#define RANGE_PRESENT_DEAD          (RBIT_PRESENT | RBIT_DEAD)
#define RANGE_PRESENT               (RBIT_PRESENT | RBIT_LIVE | RBIT_DEAD)



#define RANGE_TEAM		    (RBIT_TEAM)
#define RANGE_OTHER_TEAM	    (RBIT_TEAM | RBIT_OTHER)
#define RANGE_PRESENT_TEAM	    (RBIT_TEAM | RBIT_PRESENT)
#define RANGE_PRESENT_OTHER_TEAM    (RBIT_TEAM | RBIT_OTHER | RBIT_PRESENT)
#define RANGE_NOT_TEAM		    (RBIT_NOT_TEAM)

#define RANGE_FRIENDS		    (RBIT_LIVING | RBIT_FRIEND)
#define RANGE_ENEMIES		    (RBIT_LIVING | RBIT_ENEMY)

#define RANGE_PRESENT_ENEMIES	    (RBIT_LIVING | RBIT_ENEMY | RBIT_PRESENT)
#define RANGE_PRESENT_FRIENDS	    (RBIT_LIVING | RBIT_FRIEND | RBIT_PRESENT)

#define RANGE_PRESENT_ATTACK	    (RBIT_ATTACK | RBIT_PRESENT)
#define RANGE_PRESENT_OTHER_ATTACK  (RBIT_NOT_ATTACK | RBIT_PRESENT | RBIT_LIVING)

#endif
