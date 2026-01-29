/* Rose garden's rooms coded by Shiva
 * Modified by Marisol 03/30/99
 * Modified by Damaris 05/Y2K)
 * to be used in the Telberin's rose garden.*/


#include "../defs.h"


inherit TELBERIN_ROOM;
inherit ROSE_PICK;
inherit "/d/Emerald/lib/room_tell";

#include "/d/Emerald/sys/properties.h"
#include "/d/Emerald/sys/terrain_types.h"
#include <macros.h>

#define TO this_object()
#define TP this_player()
#define ENV environment


void
create_rose_garden()
{
}

nomask void
create_telberin_room()
{

    set_short("A wondrous rose garden");
    add_item("garden",
        "This garden is a miracle of design and beauty. Stunning "+
        "roses ranging from gorgeous deep red to flaming oranges, and "+
        "lustrious pinks in every shade, are located in this garden. "+
        "They are displayed in a way that pleases the eyes and inspires "+
        "the soul. With a quick glance, you can see the garden lay in "+
        "the form of a huge pink flower. You see six huge petals "+
        "made of two-toned pink roses and a marvelous fountain at the "+
        "center of it. The path is covered with gravel, and bordering "+
        "the path is sweet scented grass with more roses which stand "+
        "proud and lovely. The sweetest of fragrances infiltrate the "+
        "air intoxicatingly. A hedge of rhododendron enclose the garden, "+
        "creating a secret place away from the rest of the city.\n");


    add_item(({"hedge", "hedge of rhododendron", "rhododendron"}),
        "This is a tall rhododendron hedge that blocks your view of the "+
        "outside the garden. Emerald leaves and bright pink flowers "+
        "comprise the tall hedge that surrounds the garden.\n");

    add_item(({"ground", "path", "path-lawn", "lawn-path"}),
        "You look closer at the gravel path before you. It has a border "+
        "of soft, sweet smelling grass. This path-lawn surrounds "+
        "two-toned pink petals formation of roses that surrounds an "+
        "ivory fountain. Different colored roses border the path-lawn, "+
        "creating a beautiful interplay of colors and fragrances.\n");

    add_item(({"grass", "sweet grass"}),
        "The grass smells sweet and is a soft pale green color which "+
        "is soothing to look at.\n");

    add_item("buildings",
        "You look up at the tall and graceful buildings that form the royal "+
        "circle which stand proudly above the garden. The royal palace, "+
        "the keeper buildings and the temple rise upwards in a captivating "+
        "benediction of beauty.\n");

    add_item( ({"roses"}),
      "Such wonderous flowers all around you. There are many "+
      "different colored roses.\n");

    add_item(({"pink flower", "petals", "pink roses", "formation"}),
        "The elven gardeners created this beautiful configuration of "+
        "well manicured First Love's roses. They form an illusion of "+
        "petals. Each of the six petals border the gravel's limit of the "+
        "central fountain, creating an even larger ilussion of a huge "+
        "pink flower. The result is simply breathtaking.\n");

    add_item(({"first love", "first love's roses"}),
        "This is a very elegant rose with a distinct two tones of pink "+
        "petals. It has delicate petals that are pointed with a silvery "+
        "sheen. The lower petals are faint pink color and the top petals "+
        "are deep pink which bring a striking and wonderful contrast. "+
        "The  leaves are dark green with further compliments the roses. "+
        "The scent is soft and pleasantly romantic.\n");


    add_prop(ROOM_I_TERRAIN_TYPE, TERRAIN_GARDEN);


    set_tell_time(200);
    add_tell(({
        "You hear the buzzing of bees and other insects all around you.\n",
        "A warm breeze softly caresses your skin.\n",
        "You hear the water singing of mysteries in the fountain.\n",
        "You hear the sweet chirping of a sparrow.\n",
        "A black and yellow buttlefly hovers over your head and "+
        "flies away.\n",
        }));

    create_rose_garden();
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
