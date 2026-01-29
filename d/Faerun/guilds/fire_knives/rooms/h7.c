/* /d/Faerun/guilds/fire_knives/rooms/h7.c
 *
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;

public int
block_check()
{
    if (FIREKNIVES_MAPPINGS->query_assassin_rank(this_player()->query_name()) <= MAX_PROSPECT_RANK)
    {
        if (!this_player()->query_wiz_level())
        {
            write("The guard dogs slowly pace until "
            +"they stand in front of you "
            +"while growling softly, their eyes focused on yours. You decide "
            +"to reconsider your option and take a few steps backwards.\n");

            tell_room(environment(this_player()), QCTNAME(this_player()) 
            +" steps backwards from the dogs as they move in front of "
            + this_player()->query_possessive()
            +", blocking the way.\n", this_player());

            return 1;
        }
    }
      
    write("The guard dogs raise their heads to look at you, then look down "
    +"and turn around in a submissive gesture.\n");
    
    tell_room(environment(this_player()), QCTNAME(this_player())
    +" receives a furtive glance from the dogs before they lower "
    +"their head and turn around in a submissive gesture.\n", this_player());
        
    return 0;
}


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Circling the marble column");
    
    set_long("The passageway extends around the base "
    +"of the wide marble column "
    +"which dominates the center of the floor. From here, "
    +"it extends towards the "
    +"northeast and to the south, while to the "
    +"west a narrow passage leads into "
    +"what appears to be a training room from "
    +"where the sizzling sounds of clashing "
    +"blades can be heard. Around the bend in "
    +"the hall the walls to the northwest "
    +"turn sharply maintaining their contour. "
    +"Soft carpets cover the otherwise cold, "
    +"stone floor. A pair of guard dogs is resting here.\n");

    add_item(({"column","thick column","marble column",
    "thick marble column"}),
    "Before you directly to the east rises from "
    +"the bottom of the floor a tall "
    +"and wide marble column that claims all "
    +"around it to itself. It seems to "
    +"protrude from the very stone as if it "
    +"had grown from it or the halls in "
    +"which you walk around in were carved "
    +"out of it with absolute precision. "
    +"Its smooth surface bears no markings "
    +"whatsoever, appearing instead to be "
    +"waxed and polished by hard-working hands. "
    +"The width makes it impossible "
    +"to see what lies on the various sides "
    +"around it, reflecting instead "
    +"the light of the flickering torches, "
    +"illuminating the area. Following its "
    +"surface reaching upwards is impossible, its "
    +"top reach obscured by the "
    +"enveloping shadows in the ceiling. \n");
    
    add_item(({"dog", "dogs", "guard dog", "guard dogs", 
    "vicious guard dogs", "vicious dogs"}),
    "These pair of vicious wolf-like grey dogs paces about the "
    +"area, sniffing and carefully watching the movements "
    +"of any nearby creature. They appear to be guarding "
    +"the entrance to the west.\n");

    add_item(({"passageways","passageway","passage","hallway"}),
    "The passageways are formed by the split "
    +"around the marble column. "
    +"They extend from this point to the south and northeast, while "
    +"to the west a narrow passage leads into a training room.\n");

    add_item(({"sconces","sconce"}),
    "The sconces are placed at an equal distant "
    +"to each other along the wall to the "
    +"northwest. Inside each one of them are torches.\n");

    add_item(({"torch","torches"}),
    "Inside each one of the sconces along the wall "
    +"is a torch, currently lit.\n");

    add_item(({"floor","carpet", "carpets"}),
    "The floor is covered in soft carpets muffling the sound of steps and "
    +"isolating the cold, stone floor.\n");

    add_item(({"wall","walls"}),
    "The stone cold walls seem smooth and clean, the "
    +"distances between its parts "
    +"marked only by equidistant sconces in which "
    +"torches are placed. In between "
    +"them is a thickly framed high portrait.\n");

    add_item(({"portrait","portaits"}),
    "Between the two sconces on the wall to your "
    +"northwest is a portrait depicting "
    +"a squared jawed male blonde, sporting a "
    +"goatee and short hair parted in the "
    +"middle.\n"
    +"Underneath the portrait is a copper plaque.\n");

    add_item(({"plaque","plaques"}),
    "There is a single copper plaque underneath the "
    +"portrait to your northwest.\n"
    +"It reads: Acaelus.\n");

    add_exit(FIREKNIVES_ROOMS_DIR + "ft.c", "west", block_check);
    add_exit(FIREKNIVES_ROOMS_DIR + "h2.c", "northeast");
    add_exit(FIREKNIVES_ROOMS_DIR + "h6.c", "south");


    reset_faerun_room();
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}
