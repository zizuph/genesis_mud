#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Harvest way");
    set_long("You are travelling along Harvest Way, which stretches to "+
      "the west and east. Crowded buildings line the roadway to the north "+
      "and south. Animal refuse litters the ground here.\n");

    add_item(({ "harvest way", "roadway" }),
      "The street is paved in slate-grey cobblestones that appear worn and "+
      "slightly cracked, though still in good condition for such a heavily "+
      "used road.\n");

    add_item(({ "buildings" }),
      "Small wooden structures that are a mixture of shops and homes, they "+
      "probably serve the many farmers that use Harvest Way.\n");

    add_item(({ "animal refuse", "refuse" }),
      "The remnants of droppings left behind by many kinds of animals, with "+
      "horses and oxen being most prominent.\n");

    add_exit(CVAN + "road1-harvest", "west");
    add_exit(CVAN + "road2-harvest", "east");
}
