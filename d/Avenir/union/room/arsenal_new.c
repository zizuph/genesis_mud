/*
 * Drop room for the Union
 *  Cirion 032096
 *
 * Lilith, Mar 2022: The Elders asked for better options
 *    for organizing their stuff. Neatness, organization,
 *    etc are BFD in this guild. Added some more racks.
 */
#pragma strict_types

#include "../defs.h"
inherit BASE;
inherit "/lib/help";
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
    set_short("arsenal of the Shadow Union");
    set_long("This is the Arsenal of the Halls of Shadow. "
      +"It is here where the guild's armaments are carefully tended "
      +"to and placed at the ready for when the need arises."
      +"@@table_inv@@ The west wall is lined with "
      +"a rack where the distinctive garb of the Warriors "
      +"resides. An armour stand takes up the entire "
      +"east wall. "
      +"Along the south wall is a case made from dark metal and "
      +"leaded glass@@case_inv@@.\n");

    add_item(({"floor","ground"}),"The floor is flat and smooth, "+
      "made from hard, undressed granite.\n");
    add_item(({"wall","walls","limestone"}),"The walls are pale "+
      "white and powdery limestone, glowing softly with the light.\n");
    add_item(({"east wall", "east"}), "A wall of pale limestone "+
      "with an armour stand lining the length of it.\n");
    add_item(({"south wall", "south"}), "A wall of pale limestone "+
      "with an adamantine case lining the length of it.\n");
    add_item(({"west wall", "west"}), "A wall of pale limestone "+
      "with a uniform rack lining the length of it.\n");
    add_item(({"north wall", "north", "doorway"}), 
      "A narrow doorway leads toward a juncture with a beautiful "+
      "mosaic on the floor.\n");

    add_exit("crossing", "north");

    add_object(OBJ + "case");
    add_object(OBJ + "food_table");
    add_object(OBJ + "rack_uniform");
    add_object(OBJ + "stand_armour");


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

public void
init(void)
{
    ::init();

    if (IS_MEMBER(TP))
    {
	add_help_topic("here",    "/d/Avenir/union/help/room/arsenal.help");
	add_help_topic("arsenal", "/d/Avenir/union/help/room/arsenal.help");	
	add_help_topic("case",    "/d/Avenir/union/help/room/case.help");
	add_help_topic("rack",    "/d/Avenir/union/help/room/rack.help");
	add_help_topic("stand",   "/d/Avenir/union/help/room/stand.help");
	add_help_topic("table",   "/d/Avenir/union/help/room/table.help");
	add_help_topic("shelf",   "/d/Avenir/union/help/room/shelf.help");
    }
}
