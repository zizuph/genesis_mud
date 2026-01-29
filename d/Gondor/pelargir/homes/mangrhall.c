inherit "/d/Gondor/common/room";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

string
read_plaque()
{
    return BSN(
        "The first plaque says 'Beacon of Pelargir', the second "
      + "caption reads 'Pride of Pelargir', and the last painting says "
      + "'Heroes of Pelargir'");
}

void
add_door()
{
    object  door;

    door = clone_object("/std/door");
    door->set_door_id("pel_mansion_1_door");
    door->set_other_room(PELAR_DIR + "homes/mangarden");
    door->set_pass_command(({"s", "south"}));
    door->set_door_desc(BSN(
        "The door leading out of the mansion into the street has "
      + "two wooden wings, both carefully joined and painted. On "
      + "the inside, the door is void of any decorations or carvings."));
    door->set_door_name(({"large door", "door", }));
    door->set_adj(({"large", "two-winged",}));
    door->set_open(0);
    door->set_locked(0);
    door->move(TO);
}

void
create_room()
{
    set_short("in the entry hall of the mansion");
    set_long(BSN("This is the great entry hall of the mansion. A "
      + "beautiful red carpet covers the floor, and wonderful "
      + "paintings grace the walls. The bearskin rug looks a little "
      + "ragged but other than that the vast chamber is kept in "
      + "impeccable order. Someone has even run real lace around the "
      + "border of the room giving the room a feeling of delicacy and "
      + "purity."));
    add_prop(ROOM_I_INSIDE,1);
    add_item(({"rug","carpet","red carpet","bearskin rug","bearskin"}),
       BSN("The red carpet would go much farther in suggesting richness "+
       "and elegance, if it were not for the shaggy bearskin rug. The "+
       "bearskin rug seems to have been walked on about two hundred "+
       "too many times, and has begun to shed quite profusely."));
    add_item("lace",BSN("Looking closer you see that the lace has "+
       "been hung with iron nails and would be impossible to remove. It is "+
       "of a very delicate weave."));
    add_item(({"paintings","pictures"}),BSN("The three paintings were "+
       "definitely done by skilled artists. Each individual painting "+
       "has a little plaque below it with the painting's name, and has its "+
       "own artistic qualities."));
    add_item("first painting",BSN("This is a beautiful painting of "+
       "the riverscape. Riding the waves is a fleet of Gondorian ships, "+
       "using the Pelargir lighthouse as their beacon. The scene "+
       "seems calm and peaceful, very well done. Unfortunately there is "+
       "a small smudge in the rocks below the lighthouse."));
    add_item("second painting",BSN("The second painting seems "+
       "almost familiar. It is a picture of the mansion being "+
       "built. You recognize the background because the painting is "+
       "so lifelike and accurate. Within the painting, some workers are just "+
       "beginning to place the hollow cornerstone, other workers are "+
       "running about with timber. It is quite a busy scene."));
    add_item("third painting",BSN("The third painting is a portrait of "+
       "sorts. In it two young aristocrats stand over the corpse "+
       "of an orc, with proud smiles. Though one of them has an arm "+
       "in a sling, and the other a bandage on his head, you would "+
       "guess that they managed to kill the orc themselves."));
    add_item(({"captions","caption","plaque","plaques"}),
        read_plaque());
    add_cmd_item(({"captions","caption","plaque","plaques"}),
        "read", read_plaque());

    add_exit(PELAR_DIR + "homes/manstudy","north",0);
    add_exit(PELAR_DIR + "homes/mandinhall","east",0);

    add_door();
}

