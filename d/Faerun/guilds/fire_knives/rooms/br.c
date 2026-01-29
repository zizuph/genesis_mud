/* /d/Faerun/guilds/fire_knives/rooms/br.c
 *
 * Board room for applicants. The board are scrolls and notes
 * inserted between the jagged protrusions from the walls, and
 * which act as applications to the council. The person writing
 * one can only see the ones they've written, not the others.
 * 
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;


/*
 * Function name: create_fireknives_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_LIGHT, 1);

    set_short("A grotto within the cellar");
    
    set_long("The passage widens into what is easily "
    +"interpreted as a grotto "
    +"within the tunnels. Round and a tad "
    +"more spacious than the passage to the "
    +"northwest, this spherical place is like "
    +"a safe haven from the harshness "
    +"of the cave-like cellar. Jagged walls "
    +"with stone ouward protrusions create "
    +"a ruggedy atmosphere which houses moisture "
    +"within its rents. Echoes of drops "
    +"heavily falling on puddles echo in the "
    +"distance to the northwest past a "
    +"darkness impenetrable by the naked eye "
    +"which is the only way out of here. You "
    +"notice a wooden board at the south end "
    +"of the grotto that hangs adjacent to a "
    +"plaque.\n");
    
    add_item(({"grotto"}),
    "This spherical area at the end of the tunnels "
    +"seems like a grotto, allowing "
    +"for rest and time to find your bearings "
    +"amidst the tunnels.\n");
    
    add_item(({"plaque"}),
    "This is a bronze plaque with elegant ornamental "
    +"carvings that are highlighted with black enamel "
    +"to make them stand out even more.\nYou can read it.\n");
    
    add_item(({"tunnel", "tunnels"}),
    "The tunnel extends into a passage to the "
    +"northwest past a thick darkness "
    +"through which nothing can be discerned from here.\n");
    
    add_item(({"passage", "northwestern passage", "passage to the northwest"}),
    "The passage widens into the grotto where you "
    +"find yourself in, narrowing "
    +"again to the northwest through a passage back into the tunnels.\n");
    
    add_item(({"walls", "wall","jagged walls", "jagged wall"}),
    "The walls emanate a coldness which has "
    +"turned the little air transiting "
    +"through this tunnel into moisture due "
    +"to the lack of ventilation. They "
    +"accumulate lightly underneat the walls' "
    +"protrusions.\n");
    
    add_item(({"protrusions","protrusion"}),
    "Jagged stones protrude from the walls in a zigzag "
    +"motion. Lodged between "
    +"them you find rolled up scrolls and the trace "
    +"of others which have been "
    +"there before. It becomes apparent that the "
    +"ones here will be picked up "
    +"as the ones before were.\n");
    
    add_item(({"atmosphere"}),
    "The atmosphere is calm and quiet. The passage "
    +"of time is undiscernable here.\n");
    
    add_item(({"rents", "rent"}),
    "The rents are formed by the jagged protrusions "
    +"forming zigzags across the walls, "
    +"and in which you find rolled up scrolls lodged within.\n");

    add_item(({"moisture"}),
    "The moisture accumulates from the cold "
    +"emanating from the walls and the poor "
    +"ventilation in the tunnels. Although not "
    +"as visible here, drops of liquid "
    +"are heard splashing into puddles in the "
    +"distance. Their sound somewhat lulling "
    +"to the senses in its constant rhythmn.\n");

    add_item(({"puddles"}),
    "The puddles aren't visible from here, but your "
    +"sense of hearing forms a clear "
    +"picture of them gathering on the floor of the tunnels.\n");

    add_item(({"floor", "ground"}),
    "The floor of the tunnel is well-worn in and "
    +"seems to be frequented rather "
    +"than isolated from life. The patches of moss, "
    +"dirt, and pebbles bear the "
    +"form of what appear to be footsteps.\n");
    
    add_item(({"footstep","footsteps","dirt","pebble","pebbles"}),
    "Found on the ground and marked caked in the "
    +"dirt and moss are what appear to be "
    +"footsteps leading to the northwest.\n");

    add_item(({"darkness"}),
    "The darkness is all around you, swallowing the "
    +"surroundings within it to some degree, but you "
    +"can still see some details.\n");
    
    room_add_object(FIREKNIVES_BOARDS_DIR + "applic_board");
       
    add_exit(FIREKNIVES_ROOMS_DIR + "g0.c", "northwest");

    reset_faerun_room();
}


int
do_rplaque(string str)
{
	if (str == "plaque")
	{
        write("  ___________________________________________\n");
        write(" |                                           |\n");
        write(" |  o                                     o  |\n");
        write(" |                                           |\n");
        write(" |                    ___                    |\n");
        write(" |            $      |___|           $       |\n");
        write(" |    $   $           | |        $      $    |\n");
        write(" |              __    | |    __              |\n");
        write(" |     $       |  |___|_|___|  |             |\n");
        write(" |       $  $  |_______________|     $       |\n");
        write(" |              $    | | |    $  $   $       |\n");
        write(" |      $        $$  | | |  $$     $         |\n");
        write(" |           $   $$$ | | | $$$       $       |\n");
        write(" |         $     $$$$| | |$$$$     $         |\n");
        write(" |          $$$    $$$$$$$$$ _  $$$          |\n");
        write(" |           $$$$$  $$$$$$$  $$$$$           |\n");
        write(" |             $$$$$$$$$$$$$$$$$             |\n");
        write(" |                $$$$$$$$$$$                |\n");
        write(" |                   $$$$$                   |\n");
        write(" |                    $$$                    |\n");
        write(" |                     $                     |\n");
        write(" |                                           |\n");
        write(" |                                           |\n");
        write(" | In this place you are able to write down  |\n");
        write(" | your intention to join the Brotherhood of |\n");
        write(" | the Fire Knives. Know that by doing so    |\n");
        write(" | you are unveiling your intention but this |\n");
        write(" | does not mean your wishes will come       |\n");
        write(" | true. Come to know that by revealing your |\n");
        write(" | desires you will be marked as one who     |\n");
        write(" | has forfeited his past life and wishes to |\n");
        write(" | be reborn anew.                           |\n");
        write(" |                                           |\n");
        write(" | Everything you know and everything you    |\n");
        write(" | love will be gone, and you will be the    |\n");
        write(" | one charged with eradicating it all       |\n");
        write(" | from your memory and that of the world.   |\n");
        write(" | Your life and that of your known and      |\n");
        write(" | loved ones will no longer be yours, and   |\n");
        write(" | should you be accepted to be trained and  |\n");
        write(" | fail, we will claim what is ours.         |\n");
        write(" |                                           |\n");
        write(" | In the unlikely event of your success,    |\n");
        write(" | your life will be in our hands as ours    |\n");
        write(" | in yours. We are a Brotherhood of         |\n");
        write(" | Assassins and we demand, and give,        |\n");
        write(" | complete loyalty.                         |\n");
        write(" |                                           |\n");
        write(" |  o                                     o  |\n");
        write(" |___________________________________________|\n");
    
        return 1;
    
    }
    
    write("Read what?\n");
    
    return 1;
}


void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    if (interactive(ob))
    {
        if (ob->query_wiz_level())
        {
            WIZARD_ENTRY_APP_BOARD_LOG("wizard_entry_app_board_log",
            "The immortal " +ob->query_name() 
            +" entered the Fire Knives application board room.\n");
            
            ob->catch_tell(" >>> YOUR ENTRY HAS BEEN LOGGED. UNLESS YOU HAVE BUSINESS "
            +"HERE, PLEASE IMMEDATELY MOVE ELSEWHERE! <<<\n");
        } 
    }
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


void
init()
{
    ::init();
    add_action(do_rplaque, "read");
}
