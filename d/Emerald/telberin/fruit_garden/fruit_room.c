/* Fruit garden's rooms. Basic code by Shiva
 * Modified by Marisol 06/21/99
 * Modified by Damaris 05/Y2K
 * to be used in the Telberin's fruit garden.*/


#include "../defs.h"


inherit TELBERIN_ROOM;
inherit FRUIT_PICK;
inherit "/d/Emerald/lib/room_tell";

#include "/d/Emerald/sys/properties.h"
#include "/d/Emerald/sys/terrain_types.h"


void
create_fruit_garden()
{
}

nomask void
create_telberin_room()
{
    set_short("A delightful fruit garden");
    add_item("garden",
        "This garden is a miracle of design and beauty. Fruit "+
        "trees and bushes of many kinds and sizes are spread inside "+
        "the garden. A stone path winds its way around the garden, "+
        "with small outshoots that go between fruitful bushes to the "+
        "center of this enclosure. Between the stone path and the "+
        "bushes, sweet scented grass cover the ground. A tall stone "+
        "wall surround the garden, all covered with green ivy. This is "+
        "a wonderful place to have a pinic away from the noises of the "+
        "city.\n");

    add_item(({"wall", "stone wall", "ivy"}),
        "This is a tall stone wall that blocks your view "+
        "outside the garden. Bright, small green ivy leaves climb "+
        "the wall, creating a beautiful constract of grey and green. "+
        "Above the garden, tall, graceful building rise high in the sky.\n");

    add_item(({"path", "stone path"}),
        "The path is made with hewed grey stone. They are cut so "+
        "perfectly that each piece fit the other without any flaw. The "+
        "path goes around the perimeter of the garden, like a giant "+
        "circle, with small detours to the center of the garden.\n");

   add_item(({"fruit", "fruits"}),
       "Which fruit did you wish to see closer?\n");

   add_item("buildings",
        "Tall and gracefull buildings from the royal circle stand "+
        "proudly above the garden. The royal palace, the keeper "+
        "buildings and the temple rose to the sky like a benediction "+
        "of beauty.\n");

    add_item(({"trees", "tree", "fruit trees"}),
        "There are many kind of trees at this garden. All bear fruits "+
        "all year round. It is as if a magical spell of fruitfulness was "+
        "bestowed to this place by the elven gardeners that tend to it.\n");

    add_item(({"emerald bushes"}),
        "You look closer at the emerald bushes. They are quite lovely to "+
        "the eye. The delicate leaves sparkle like emeralds glistening in "+
        "light. You are so attracted to them you find it difficult to turn "+
        "away.\n");

    add_item((("grass", "ground")),
        "You look closer at the soft supple grass growing like a "+
        "jade-colored carpet. You feel drawn to lie down in its warmth "+
        "and smell the sweet fragrance.\n");

    add_item((("bushes")),
        "You see many bushes in this section. Perhaps you should look "+
        "at one particular bush closer.\n");

    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_GARDEN);

    set_tell_time(100);
    add_tell(({
        "You hear the buzzing of bees and other insects all around you.\n",
        "A soft breeze carries the scent of fruit.\n",
        "You hear the musical trickle of water falling softly in a "+
        "fountain.\n",
        "You hear the sweet chirping of a robin.\n",
        "A blue and black butterfly hovers over your head and flies "+
        "away.\n",
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
        write("The air is filled with the sweet scent of ripe fruits "+
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

