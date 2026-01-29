#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Wayfarer boulevard");
    set_long("You are walking along Wayfarer Boulevard, which is paved "+
      "in cobblestone like the majority of the main avenues throughout "+
      "the city of Kabal. To the east you can see where Wayfarer "+
      "Boulevard intersects with the heavily travelled Caravan Street. "+
      "To either side of the street you can see many crowded buildings. "+
      "One of the buildings to your north stands out due to its "+
      "impressive marble facade and quartz-lined doorways. "+
      "There seems to be less animal refuse here, although it is not "+
      "completely unnoticeable.\n");

    add_item( ({ "buildings" }),
      "The buildings vary in height from one-story to as high as three "+
      "stories. Most of them are constructed out of wood cut from the "+
      "forests north of Kabal.\n");

    add_item( ({ "north building", "marble building" }),
      "This magnificent building, with fine dwarven crafted walls can "+
      "only be the residence of the wealthy money changer, Turale "+
      "Arcflame.\n");

    add_item( ({ "refuse", "animal refuse" }),
      "There seems to be less of it here, although there is enough "+
      "lying around to make you wrinkle your nose in disgust.\n");

    add_exit(CVAN + "caravan-wayfar", "east");
    add_exit(CVAN + "shop/mchange", "north");
    add_exit(CVAN + "wayfar/s2", "west");
}
