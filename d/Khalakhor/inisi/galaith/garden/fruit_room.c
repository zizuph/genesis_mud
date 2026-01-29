/* Garden rooms
 * Damaris 03/2001
 */


#include "../defs.h"


inherit "/d/Khalakhor/std/room";
inherit FRUIT_PICK;
inherit "/d/Khalakhor/lib/room_tell";

#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/terrains.h"


void
create_fruit_garden()
{
}

nomask void
create_khalakhor_room()
{
    set_short("An enchanting fruit garden");
    add_item(({"garden", "enchanting garden", "fruit garden", "enchanting fruit garden"}),
      "This is a small but quite enchanting fruit garden. It is "+
      "hidden well within the confines of large towering pines. "+
      "There are plenty of different fruits filling the trees and "+
      "bushes in a very appetizing way. A small stone path winds "+
      "its way through various plants and vines.\n");
    add_item(({"grass", "sweet grass"}),
      "The grass dark green in colour and is quite soft with a "+
      "gentle sweet smell.\n");
    add_item(({"pines", "pine tree", "pine trees", "towering pines"}),
      "The large towering pines shoot majestically upward keeping "+
      "this garden well hidden.\n");
    add_item(({"tree", "trees"}),
      "There are many different trees here, which one did you wish "+
      "to examine closer?\n");
    add_item(({"bush", "bushes"}),
      "There are many different bushes here, which one did you wish "+
      "to examine closer?\n");
    add_item(({"sky"}),
      "A small hint of a deep blue sky can be seen through the tops of "+
      "the trees.\n");
    add_item(({"stone path", "path"}),
      "A simple stone path winds its way through the bushes and "+
      "vines throughout the garden.\n");
    add_item(({"vines", "vine"}),
      "There are many different plants and vines climbing upward and "+
      "across the grass in various spots.\n");
    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_GARDEN);

    set_tell_time(100);
    add_tell(({
        "The soft whisper of wind caresses your skin.\n",
        "The scent of sweet fruit lingers with the breeze.\n",
        "You hear the musical sound of birds in the trees.\n",
        "You hear the scurrying of a small animal in the bushes.\n",
        "A tiny elven nymph dragon plucks some fruit from a bush "+
        "then disappears.\n",
        }));

create_fruit_garden();
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (interactive(ob))
    {
       start_room_tells();
    }
}


void
hook_smelled(string str)
{
    if (!strlen(str) || parse_command(str, ({}), "[the] 'air'"))
    {
        write("The air is filled with the delicate scent of fruits "+
        "and sweet grass.\n");
        return;
    }

}

public void
init()
{
    ::init();
    init_fruit();
}

