inherit "/d/Gondor/rohan/entwash/entwash";
#include "/d/Gondor/defs.h"

void reset_room();

object  bug;

void
create_swamp()
{
    set_extra_long("The marsh extends for a some distance in most"
      + " directions here, its muddy banks winding in and amongst"
      + " the streams and pools of water. This area is thick with"
      + " buzzing insects.");

    add_item(({"bank","banks"}), BSN("Most of the banks are litte"
      + " more than overturned clumps of weeds which have collected"
      + " debris from the flowing water."));
    add_item(({"insect","insects"}), BSN("Many of the insects seem"
      + " content to hover in swarming clouds, but a few of the bolder"
      + " ones are a nuisance and grow more annoying by the minute."));

    add_exit(ENTWASH_DIR + "ent2a", "west");
    add_exit(ENTWASH_DIR + "ent3b", "northeast");
    add_exit(ENTWASH_DIR + "ent4a", "east");

    reset_room();
}

void
add_monsters()
{
    if(!objectp(bug))
    {
        bug = clone_object(NPC_DIR + "mosquito");
        bug->set_poison_file(ENTWASH_DIR + "obj/mosquito_sting");
        bug->move_living("from somewhere", TO);
    }
}

void
reset_room()
{
    set_alarm(1.0, 0.0, add_monsters);
}
