#include "../default.h"
inherit CVAN_ROOM;

void
create_cvan_room()
{
    set_hear_bell(1);

    add_prop(ROOM_I_INSIDE, 1);

    set_short("Inside the white building");
    set_long("You are inside a lavishly decorated room. White fruffed "+
      "drapes frame the glass windows while an elegant red carpet covers "+
      "the marble floor. Hanging from the ceiling are delicate crystalline "+
      "chandeliers. Gazing south, you see another room.\n");

    add_item(({ "drapes" }), "Beautiful curtains that adorn the glass "+
      "windows.\n");

    add_item(({ "windows" }), "They have been meticulously polished to such "+
      "crystal clear clarity, you almost swear there is no glass there. "+
      "Looking outside you can see Wayfarer Boulevard.\n");

    add_item(({ "carpet" }), "A finely textured rug, it feels almost as smooth "+
      "as silk.\n");

    add_item(({ "floor" }), "The ground is covered in marble tiles of such "+
      "a brilliant white color you are nearly blinded from looking at them.\n");

    add_item(({ "chandeliers" }), "Made of the finest crystal, they tinkle "+
      "ever so slightly, producing a soothing melody.\n");

    add_exit(CVAN + "wayfar/s1", "out");
    add_exit(CVAN + "wayfar/w1", "south");

    clone_object(OBJ + "chair")->move(TO);
}
