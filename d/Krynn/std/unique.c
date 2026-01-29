/* All special items in Krynn can only have a limited number of
 * instances in the game at any time.
 *
 * Inherit this file additionally to allow only a limited number
 * of copies in the game.
 *
 * To set the number of copies allowed, use set_copies(3); in the
 * create_*() function. The default is 1.
 */

#include <stdproperties.h>
#include <macros.h>


int max_copies = 1;

/* prototypes*/
void set_copies(int num);
int query_copies();
int query_max_copies();
int check_copies();


/* You can only set the max copy number in the master object
 * all other calls to this function will be ignored.
 * Returns 0 if the object was successfully cloned.
 * Returns 1 if it failed.
 * There should be an alternative object to clone in case
 * this object failed.
 * Maybe add a second (optional) arg to set_copies with a filename
 * to clone alternatively?
 */
int
set_copies(int num)
{
    if (!IS_CLONE)
    {
	max_copies = num;
	return 0;
    }
    return check_copies();
}

int
query_copies()
{
    mixed* clones = object_clones(find_object(MASTER));
    clones = clones->query_prop(OBJ_I_BROKEN);
    clones -= ({ 1 });
    return sizeof(clones);
}

int
query_max_copies()
{
    if (IS_CLONE)
      return MASTER->query_max_copies();
    else
      return max_copies;
}

/* Check the copies of an object in the game and don't allow
 * cloning the there's too many copies in the game.
 * Returns 1 if cloning fails, 0 on success.
 */
int
check_copies()
{
    if (query_copies() > query_max_copies())
    {
	set_alarm(1.0,0.0,"remove_object");
	/*this_object()->remove_object();*/
	return 1;
    }
    return 0;
}
