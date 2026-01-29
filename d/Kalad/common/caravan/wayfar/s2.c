#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_short("Wayfarer boulevard");
    set_long("You are walking along Wayfarer Boulevard, to the west a "+
      "small intersection can be seen, and eastward lies the rest of "+
      "Wayfarer Boulevard and eventually an intersection with "+
      "Caravan Street. You notice that the buildings here are less "+
      "crowded than the ones further east. A wooden building lies just to the "+
      "north. Also, there are less and less "+
      "piles of animal refuse lying around.\n");

    add_item( ({ "buildings", "building" }),
      "The buildings along this stretch of road are less crowded "+
      "together and seem of better quality than the ones to the east.\n");

    add_item(({ "wooden building" }), "It looks like it was just recently "+
      "placed here. A sign hangs in front of it.\n");

    add_item("sign", "@@sign");
    add_cmd_item("sign", "read", "@@sign");

    add_item( ({ "piles", "pile", "refuse" }),
      "There aren't as many animal litterings here, only if you look "+
      "for them specifically can you see them, otherwise they are not "+
      "too noticeable to your eyes, OR nose.\n");

    add_exit(CVAN + "alley_wayfar", "west");
    add_exit(CVAN + "shop/tmp_post", "north");
    add_exit(CVAN + "wayfar/s3", "east");
}

string
sign()
{
    return "Former home of the post office.\n";
}
