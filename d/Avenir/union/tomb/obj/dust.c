/*
 * Some Dust
 *   Cirion, 28 May
 */
inherit "/std/heap";
#include <stdproperties.h>

public void
create_heap(void)
{
    set_name("dust");
    set_pname("dust");
    add_name("grain");
    add_pname(({"pile","handful","handfull","grains","heap"}));
    set_short("grain of dust");
    set_pshort("grains of dust");
    set_long("This dust is of indeterminate origin.\n");

    add_prop(OBJ_I_HIDE, "@@check_hidden@@");
    add_prop(HEAP_S_UNIQUE_ID, "avenir_dust");

    remove_prop(OBJ_I_WEIGHT);
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_VALUE);
}

/*
 * Grains of dust are difficult to see, the fewer there
 * are, the more difficult.
 */
public int
check_hidden(void)
{
    /* Only hidden if they are in a room */
    if (!environment()->query_prop(ROOM_I_IS))
	return 0;

    return max(0, 100 - num_heap());
}

public varargs string
short(object for_obj)
{
    string dum, str = ::short(for_obj);

    if (sscanf(str, "many %s", dum) || sscanf(str, "huge heap %s", dum))
    {
	if (num_heap() < 100)
	    return "a handful of dust";
	else if (num_heap() < 300)
	    return "a pile of dust";
	else if (num_heap() < 700)
	    return "a large pile of dust";
	else
	    return "a large heap of dust";
    }

    return str;
}
