/* An inheritable file used to keep the number
 * Magical objects in the game below a certain number.
*/

#include <stdproperties.h>

int
query_clones(string filename)
{
    object a, *b;

    setuid(); seteuid(getuid());
    if (!(a = find_object(filename)))
    {
	return 0;
    }
    b = object_clones(a);
    // Filter out broken objects
    b = filter(b, &not() @ &->query_prop(OBJ_I_BROKEN));
    b = map(b, environment);
    // Remove all objects that had no environment
    b -= ({0});
    // Filter out items that are in the possession of a wizard
    b = filter(b, &not() @ &->query_wiz_level());
    // Filter out things inside a store room.
    b = filter(b, &not() @ &->query_max_items());

    return sizeof(b);
}

string
unique_clone(string filename, int number, string alternative)
{
    if (query_clones(filename) >= number)
	return alternative;

    return filename;
}
