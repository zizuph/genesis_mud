#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include <ss_types.h>

inherit FOREST_IN;
#define PLAYER_I_PASS_MAZE "_player_i_pass_maze"

object statue, door, key;


void
reset_flotsam_room()
{
    if(!objectp(statue))
    {
	statue = clone_object(FNPC + "golem");
	statue->arm_me();
	statue->add_descr("stands upon a pedestal");
	statue->move(TO);
    }

}

void close_this_door() { door->do_close_door(""); }
create_flotsam_room()
{
    set_short("Flooded silver walled room");
    set_long("@@long_descr");

    add_item(({"silver walled room","room"}),"@@long_descr");
    add_item(({"walls","silver walls"}),
      "The walls of this room are all of silver. Carvings " +
      "of various victorious minotaurs of ages past mark " +
      "each wall.\n");
    add_item("carvings","Carvings of various victorious " +
      "minotaurs of ages past mark each wall.\n");
    add_item(({"wide stone pedestal","stone pedestal",
	"pedestal"}),
      "This sort of pedestal is often used as the base of a " +
      "statue. It is high enough to keep its top clear of " +
      "the water.\n");
    add_item(({"sea water","water"}),
      "Sea water fills this room. You notice with surprise " +
      "that the water level does not change much, at least " +
      "not as high as the top of the pedestal.\n");

    add_cmd_item(({"golem","clay golem"}),"splash","@@melt");

    door = clone_object(FOBJ + "door1b");
    door->move(TO);
    reset_flotsam_room();
}

string
long_descr()
{
    return "You stand in a room with silver walls. A foot " +
    "of sea water covers the floor. A wide stone pedestal " +
    "rises out of the water, the only dry place anyone can " +
    "stand on.\n";
}

string
melt()
{
    if(!objectp(statue))
    {
	return "You cannot splash what isn't there.\n";
    }

    write("You splash the golem.\n" +
      "The sea water makes him begin to soften up and " +
      "melt!\n" +
      "The golem disolves, leaving behind a key.\n");
    statue->remove_object();
    key = clone_object(FOBJ + "chest_key");
    key->move(TO);
    return "";
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(!living(ob))
	return;

    if(ob->query_prop(PLAYER_I_PASS_MAZE))
	return;

    ob->add_prop(PLAYER_I_PASS_MAZE, 1);
}
