/*
 * Drop room for the Union
 *  Cirion 032096
 */
#pragma strict_types

#include "../defs.h"
inherit BASE;

#include <stdproperties.h>

static object box, table;

public void
reset_room(void)
{
    table->reset_container();
}

public void
union_room(void)
{
    set_short("bare room");
    set_long("This is a small, bare and lonely room, surrounded "
      +"on all four sides by flat limestone walls, with only "
      +"a narrow doorway leading north to a juncture. Along "
      +"the south wall is bracketed a case, long enough to "
      +"span the entire wall, and made from dark metal and "
      +"leaded glass@@case_inv@@.@@table_inv@@\n");

    add_item(({"floor","ground"}),"The floor is flat and smooth, "+
	"made from hard, undressed granite.\n");
    add_item(({"wall","walls","limestone"}),"The walls are pale "+
	"white and powdery, glowing softly with the light.\n");

    add_exit("crossing", "north");

    add_object(OBJ + "case");
    add_object(OBJ + "food_table");
}

static void
update_vars(void)
{
    box = present("_union_case");
    table = present("_union_table");
}

public string
case_inv(void)
{
    if (!box || !sizeof(all_inventory(box)))
	return "";

    return ", within which can be seen "+ box->external_within();
}

public string
table_inv(void)
{
    if (!table) return "";
    return table->external_within();
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (!box->query_prop(CONT_I_CLOSED))
    {
	ob->catch_tell("As you leave, you notice that the case "+
	  "is left open. Perhaps you should go back and close it?\n");
    }
}
