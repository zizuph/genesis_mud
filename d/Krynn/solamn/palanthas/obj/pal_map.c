/* Created by Mortis 08.2005 */

inherit "/std/object";

#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

create_object()
{
	seteuid(getuid(TO));

    set_name("map");
    set_adj("new");
	set_adj("crisp");
    LONG("Freshly scribed in black ink upon crisp, beige parchment is "
	+ "a map of a circular city.  You may study it or study its first "
	+ "or second page.  You may also read it to peruse it top to bottom "
	+ "at your own pace.\n");

    add_prop(OBJ_I_VALUE, 200);
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 400);

	CMD("map", "study", "@@study_map");
	CMD(({"first page", "page 1"}), "study", "@@study_first");
	CMD(({"second page", "page 2"}), "study", "@@study_second");
	CMD("map", "read", "@@read_map");

}

public int
study_map()
{
	write("You study your map of Palanthas closely.\n\n");

	cat(OBJ + "palanthas.txt");

	say(QCTNAME(TP) + " studies a crisp piece of parchment.\n");
	return 1;
}

public int
study_first()
{
	write("You study your map of Palanthas closely.\n\n");

	cat(OBJ + "palanthas.txt", 1, 60);

	say(QCTNAME(TP) + " studies a crisp piece of parchment.\n");
	return 1;
}

public int
study_second()
{
	write("You study your map of Palanthas closely.\n\n");

	cat(OBJ + "palanthas.txt", 64, 36);

	say(QCTNAME(TP) + " studies a crisp piece of parchment.\n");
	return 1;
}

public int
read_map()
{
	string file = OBJ + "palanthas.txt";

	write("You begin reading your map of Palanthas closely.\n\n");

    TP->more(read_file(file, 1, 50000));

	say(QCTNAME(TP) + " reads a crisp piece of parchment.\n");
	return 1;
}
