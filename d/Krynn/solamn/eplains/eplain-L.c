#include "local.h"
inherit TDIR+"eplain_base";

public void
create_eplains_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_special_short("Foot of the mountains before a large cave");
    set_short("Foot of the mountains before a large cave");
    set_long("You are standing at the reaches of the Dargaard Mountains " +
                "which rise up high to your east. It is impossible to travel the " +
                "rugged cliffs and step slopes of these mountains. However, you do " +
                "notice a great rift in the face of the cliff that opens up to your " +
                "east. Steam snakes out of the entrance of this cave, making " +
                "it seem dark and sinister. Still, it is an opening you would be able " +
                "to enter easily if you dared. To you north " +
                "and west, the Plains of Solamnia stretch out as far as you can " +
                "see, the higher elevation at the foot of the mountains allow " +
                "a view across the landscape.\n");

    add_cmd_item(({"opening","rift","great rift","large cave","cave"}),"enter",
      "@@enter_tunnel");

}

string
enter_tunnel()
{

    write("You pass through the steam into the cave...\n");
    TP->move_living("passes through the steam into the cave",
      "/d/Krynn/solamn/eplains/dragon_lair",1,0);
    return "";
}