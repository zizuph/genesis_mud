#include "local.h"
#include CLOCKH
inherit TDIR + "throtyl_base";

public string
long_desc(string long)
{
    string str, desc;

    str = "It is " + GET_TIME_STRING + " on " +
        (gSpecial_short ? gSpecial_short : short()) + ". ";

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

    set_special_short("a crude trail within the ancient Stormshire Forest");
    set_short("A crude trail within the ancient Stormshire Forest");

    switch(random(4, (Xx+1)*(Yy+1)))
    {
    case 1:
    	set_long("Thickly overgrown with vegetation " +
            "and dark with shadows, few brave souls pass through " +
            "this forest.\n");
	break;
    case 2:
    	set_long("Densely packed trees loom over you as if in judgement. Few " +
            "brave souls pass through this forest, with rumours of it being " +
            "infested with hobgoblins and other unnatural horrors.\n");
	break;
    default:
    	set_long("Around you looms densely packed trees. Thickly " +
            "overgrown with vegetation, few brave souls pass through " +
            "this forest with rumours of it being infested with " +
            "hobgoblins and other unnatural horrors.\n");
    }

    add_item(({"crude trail", "trail"}),
        "A crude trail winds through the dark and forbidding Stormshire " +
        "Forest. Clearly few travel this path, as it is overgrown and " +
        "difficult to distinguish.\n");

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

    add_std_exits();
}

/* Function name: query_map_fatigue
 * Description:	  Return fatigue value for leaving this room for this_player()
 *		  Redefine it in ROOM base file.
 * Returns:	  int fatigue value
 */
public int
query_map_fatigue()
{
    return 1;
}
