#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/ship/cabin.c";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/bnumen/lib/bnumen_defs.h"
#include "/d/Gondor/std/tell.c"


int
check_exit()
{
    if (IS_MEMBER(TP))
        return 0;

    write("Only members of the Houses of the Black Numenoreans may proceed here!\n");

    if (TP->query_wiz_level())
    {
        write("But, since you are a wizard, we make an exception.\n");
        return 0;
    }

    return 1;
}

string
long_cabin_level_1(int type = 0)
{
    set_cabin_sound("The lantern sways with the motion of the ship, " +
        "casting strange shadows around the room.\n");
    set_bump_sound("The crew throws the anchor. Splash!\n");
    add_item(({"lanterns", "lantern", "brass lanterns"}),
        "The brass lanterns are highly polished and extend from " +
        "the walls or ceiling suspended on gimbal swivels so that " +
        "they can move with the motion of the ship and not spill " +
        "oil.\n");
    add_item(({"ebony", "shining ebony", "ebony beams"}),
        "The ceiling beams are carved from black ebony and polished to a " +
        "lustre. They are carved with scenes representing sea battles " +
        "and history of the Black Numenoreans.\n");
    switch (type)
    {
    case 0:
            /* starboard side chamber */
        return "The starboard walls curve gracefully outward. Long beams of " +
            "shining ebony support the ceiling. Brass lanterns on gimbal " +
            "swivels swing gently with the motion of the ship. ";
            break;
    case 1:
            /* port side chamber */
        return "The port wall curves gracefully outward. Long beams of shining " +
            "ebony support the ceiling. Brass lanterns on gimbal swivels swing " +
            "gently with the ship's motion. ";
            break;
    case 2:
            /* aft chamber */
        return "Interlocking boards of teak and mahogany in intricate patterns make " +
            "up the walls and floor of this large chamber. The aft walls " +
            "curve gracefully, following the lines of the stern. " +
            "Long beams of shining ebony support the ceiling. Brass lanterns " +
            "on gimbal swivels swing gently with the ship's motion. ";
            break;
    case 3:
            /* fore chamber */
        return "Interlocking boards of teak and mahogany in intricate patterns make " +
            "up the walls and floor of this large chamber. The fore walls " +
            "curve gracefully outward, meeting at a corner near the bow of the ship. " +
            "Long beams of shining ebony support the ceiling. Brass lanterns " +
            "on gimbal swivels swing gently with the ship's motion. ";
            break;
    case 4:
        /* hallway below decks */
        return "This is a narrow hallway below decks extending from stern to bow of " +
            "the barque. Interlocking boards of teak and mahogany in intricate patterns make " +
            "up the walls and floor. Long beams of shining ebony support the ceiling. " +
            "Brass lanterns set into the walls on gimbal swivels swing gently with the " +
            "ship's motion. ";
    default:
        return "Interlocking boards of teak and mahogany in intricate patterns make " +
            "up the walls and floor of this large chamber. " +
            "Long beams of shining ebony support the ceiling. Brass lanterns " +
            "on gimbal swivels swing gently with the ship's motion. ";
            break;
    }


}


varargs void
floor(int i = 0)
{
    switch (i)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            add_item(({"floor", "ground", }), 
                "The floor is constructed from interlocking planks of teak " +
                "and mahogany scoured clean and oiled to preserve the dark-brown " +
                "lustre against the elements of sea, salt, and humidity.\n");
            break;
        default:
            add_item(({"floor", "ground", }), 
                "The floor is constructed from interlocking planks of teak " +
                "and mahogany scoured clean and oiled to preserve its dark-brown " +
                "lustre against the elements of sea, salt, and humidity.\n ");
            break;
    }
}

varargs void
walls(int i = 0)
{
    switch (i)
    {
        case 0:
            add_item(({"wall", "walls", }),
                "Interlocking boards of teak and mahogany in intricate patterns make " +
                "up the walls that curve outward following the lines of the ship. " +
                "The wood is scoured clean and oiled to preserve its " +
                "dark-brown lustre against the elements of sea, salt, and humidity.\n ");
            break;
        case 1:
            add_item(({"wall", "walls", }),
                "Interlocking boards of teak and mahogany in intricate patterns make " +
                "up the walls that curve outward following the lines of the ship. " +
                "The wood is scoured clean and oiled to preserve its " +
                "dark-brown lustre against the elements of sea, salt, and humidity.\n ");
            break;
        case 4:
            add_item(({"wall", "walls", }),
                "Interlocking boards of teak and mahogany in intricate patterns make " +
                "up the walls. The wood is scoured clean and oiled to preserve its " +
                "dark-brown lustre against the elements of sea, salt, and humidity.\n ");
            break;
        default:
            add_item(({"wall", "walls", }),
                "The walls are constructed from interlocking planks of teak " +
                "and mahogany scoured clean and oiled to preserve its dark-brown " +
                "lustre against the elements of sea, salt, and humidity.\n ");
            break;

    }
}

varargs void
ceiling(int i = 0)
{
    switch (i)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            add_item(({"ceiling", "roof", }),
                "The ceiling beams extend gracefully overhead, high enough " +
                "for tall men to stand upright. The beams are " +
                "fashioned from gleaming black ebony and are carved with " +
                "scenes of ships and sea battles.\n"); 
            add_item(({"scenes", "ships", "sea battles"}), "The carved scenes " +
                "depict legends from the history of the Black Numenoreans.\n");
            break;
        default:
            add_item(({"ceiling", "roof", }),
                "The ceiling beams extend gracefully overhead, high enough " +
                "for tall men to stand upright. The beams are " +
                "fashioned from gleaming black ebony and are carved with " +
                "scenes of ships and sea battles.\n"); 
            add_item(({"scenes", "ships", "sea battles"}), "The carved scenes " +
                "depict legends from the history of the Black Numenoreans.\n");
            break;
    }
}

varargs void
other_stuff(int i = 0)
{
    add_item("lantern", "The lantern hangs from the ceiling. "+
	     "It is a large and probably very expensive brass lantern with an "+
	     "oil container that should last quite a while.\n");
    add_item(({"table", "mahogany table"}), "Like so many other "+
	     "things on this ship, the table is made out of finest mahogany "+
	     "despite its small size but it has some faintly visible marks "+
	     "and scratches upon its formerly polished surface, indicating "+
	     "that it is frequently used. On the table are some maps.\n");
    add_item(({"map", "maps"}), "The maps are nautical maps and "+
	     "there seem to be several doublets, some being riddled with marks "+
	     "lines and notations while others seem brand new. Alas, you find "+
	     "no treasure map.\n");
}


