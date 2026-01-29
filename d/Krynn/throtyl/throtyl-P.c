#include "local.h"
#include CLOCKH
inherit TDIR + "throtyl_base";

public string
long_desc(string long)
{
    string str, desc;

    str = (gSpecial_short ? gSpecial_short : short()) +
      ". It is " + GET_TIME_STRING + ". ";

    switch (GET_TIMEOFDAY)
    {
        case TOD_DAWN:
              desc = "The light from the rising sun sends weak beams " +
                  "through the dense canopy, barely illuminating your " +
                  "surroundings. " + long;
              break;
	case TOD_DAY:
              desc = "The sun sends weak beams " +
                  "through the dense canopy, barely illuminating your " +
                  "surroundings. " + long;
              break;
	case TOD_TWILIGHT:
              desc = "The sun is sinking below the horizon, causing " +
                  "long shadows to be cast by the gnarled limbs of the " +
                  "trees. " + long;
	      break;
	case TOD_NIGHT:
	      desc = "The pale light from the two moons, " + C(SOLINARI) + 
                  " and " + C(LUNITARI) + ", illuminates your surroundings " +
                  "in a hellish reddish-orange light, as if the trees were " +
                  "glowing with the fires from the Abyss. " + long;
	      break;
    }

    str += desc;

    return str;
}

public void
create_throtyl_room()
{
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    add_prop(ROOM_I_INSIDE, 0);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("A crude trail on the edge of the Stormshire Forest");
    set_long("Thickly overgrown with vegetation, passage through this " +
            "forest is challenging. Few brave souls pass " +
            "through this forest, with rumours of it being infested with " +
            "hobgoblins and other unnatural horrors. To your west the " +
            "forest opens to the vast Solamnian Plains.\n");
    
    add_item(({"crude trail", "trail"}),
        "A crude trail winds through the dark and forbidding Stormshire " +
        "Forest. Clearly few travel this path, as it is overgrown and " +
        "difficult to distinguish.\n");

    add_item(({"solamnian plains","plains"}),
        "To your west the forest opens up to the Solamnian Plains.\n");

    add_item(({"stormshire forest", "forest", "ancient forest", "trees"}),
        "Dark, tall, and ancient. The trees of the Stormshire Forest " +
        "loom over you, casting long shadows.\n");

    add_item(({"vegetation"}),
        "The vegetation grows thick and wild throughout the forest, " +
        "making it difficult to navigate through.\n");

    add_item(({"shadows","dark"}),
        "Long shadows are cast by the thickly clustered trees, " +
        "resembling the bony fingers of the dead.\n");

    add_item(({"hobgoblins","unnatural horrors","horrors"}),
        "Marauding hobgoblins are rumours to infest this forest, along " +
        "with unnatural horrors from beyond the grave. Few travel this " +
        "forest willingly!\n");

    add_exit("/d/Krynn/solamn/eplains/rooms/eplain-23-24-T","west", 0);
    add_std_exits();

    herbs = HERB_MASTER->query_herbs( ({ "mixedforest", }) );
}

