/* cv/lounge.c
 * Lilith Nov 2021
 * Coven Location #2 for the Faerun Vampires.
 * Any changes to these rooms should be discussed
 * by the GM of the Vamps and the Liege of Avenir.
 */

#include "/d/Faerun/defs.h"
#include "/d/Faerun/guilds/vampires/guild.h";
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>

inherit VAMPIRES_STD_ROOM;

#define SEE_CHAMBER ({ "/d/Avenir/common/outpost/cv/room4", \
                       "/d/Avenir/common/outpost/cv/room5", \
                       "/d/Avenir/common/outpost/cv/room6" })

public object *
get_view(string *arr)
{
    object *inv = ({});

    foreach(string path: arr)
    {
        object room = find_object(path);
        if (objectp(room))
            inv += all_inventory(room);
    }

    if (sizeof(inv))
        inv = FILTER_CAN_SEE(FILTER_LIVE(inv), this_player());

    return inv;
}

public string
see_view(void)
{
    object *live = get_view(SEE_CHAMBER);

    if (!sizeof(live))
	return "";

    return "You can see "+ COMPOSITE_LIVE(live) +" in the chamber beyond.";
}



/*
 * Function name: create_vampires_room
 * Description  : Constructor, redefine this to configure your room
 */
 
 
//to-do:
// I would love to put a game board in here, like 
// checkers, chess, othello, or tic-tac-toe

// make a chest to clone to this this room.
public void
create_vampires_room()
{
    seteuid(getuid());
    
    add_prop(ROOM_I_INSIDE, 1);
	add_prop("_not_in_flux_zone", 1); //This prevents Source-related room tells.	
    set_short("Lounge");
    set_long("This corner of the crystal chamber is set aside "
        +"for lounging in luxury. Overhead, a large candelabra casts "
        +"a mellow glow that sets myriad crystal facets on the south "
        +"and east walls aglow with a rainbow of colors. The floor "
        +"is covered in bearskin rugs, while large overstuffed chairs "
        +"and sofas are draped in fox, ermine, and mink furs that "
        +"are a delight to the senses. An old wooden chest with leather "
        +"straps lies near the center of the room, and near it, an "
        +"alabaster urn holding an arrangement of flowers emits an "
		+"intoxicating scent.@@see_view@@\n"); 
   		
    add_exit("room4",  "north");
	add_exit("room6",  "west");
    // non-obvious exits:	
    add_exit("room5", "northwest", 0, 0, 1);

	add_item(({"walls", "wall", "south wall", "east wall", "crystals"}),
        "The west and south walls are made entirely of crytals that "
        +"grew over the eons. They are many colors and many sizes and "
        +"the overall effect is harmonious and wonderous.\n");
    add_item(({"colors", "colours", "rainbow", "hues", "hue" }),
        "The crystals, many of them gemstone-quality, run in a range "
        +"colors of nearly every hue and intensity.\n"); 
    add_item(({"candelabra", "chandelier", "candles","candlelight"}),
        "A massive candelabra is suspended from the cavern ceiling by a "
        +"thick chain. Hundreds of candles cast a muted, mellow light on "
	    +"the cavern beneath it.\n");
    add_item(({"ceiling","stalactites"}),
        "The ceiling of this chamber is draped in darkness that is pierced "
        +"by stalactites formed over the eons. The stalactites glitter "
        +"and gleam in the light of the candelabra.\n");
    add_item(({"dark", "darkness"}), "The darkness is so deep that even "
        +"your eyes cannot penetrate it.\n");	
    add_item(({"floor", "ground", "basalt"}),
        "The basalt floor is chiseled level and polished to a high "
        +"gloss but it is mostly covered in layers of bear and wolf "
		+"pelts.\n");
    add_item(({"bear", "wolf", "bearskin", "wolf pelts"}),
        "These pelts are thick, with a slightly wiry outer layer and "
        +"a softer, mat-like inner layer of fur. Their thickness makes "
        +"them an excellent floor covering.\n");
    add_item(({"fur", "furs", "mink", "ermine", "fox"}),
        "Soft lustrous guard hairs and plush deliciously soft underfur "
        +"are delightful to touch and sink into. The feel of it against "
        +"your skin is indescribably pleasurable.\n");
    add_item(({"flower arrangement", "arrangement of flowers", "urn",
        "alabaster urn", "flowers"}), "The alabaster urn is quite "
        +"large, probably the height of a dwarf, and purest white. "
        +"It holds a large arrangement of flowers, stems, and twigs "
        +"that give off a delicate, harmonious aroma.\n");
    add_item(({"sofa", "sofas", "couch", "couches", "chair", "chairs" }),
        "These are very comfortable places to sit, with plump cushions "
        +"covered in the finest furs.\n");
    reset_faerun_room();
}


/*
 * Function that allows the player to sit at a table or the bar
 */
int action_sit(string str)
{
	
    notify_fail(capitalize(query_verb()) + " on a chair or a sofa?\n");
    if(!strlen(str) || !parse_command(str, ({}), "[on] / [in] [a] / "
        +"[the] 'chair' / 'sofa' / 'couch'"))
    return 0;

    if(this_player()->query_prop("_sitting_in_couch"))
    {
        write("But you are already sitting in one!\n");
        return 1;
    }
    this_player()->catch_msg("You sit down and ease back into the soft "
        +"furs.\n");
    say(QCTNAME(this_player()) + " sits in a comfortable spot.\n");
    this_player()->add_prop("_sitting_in_couch", 1);    
    this_player()->add_prop(LIVE_S_EXTRA_SHORT," who is sitting comfortably");
    return 1;
}


/*
 * Function that allows the player to stand from a table or the bar
 */
int
action_stand(string str)
{
    if(str == "up")
    {
        if(this_player()->query_prop("_sitting_in_couch"))
        {
            this_player()->catch_msg("You get up from your comfy spot.\n");         
            say(QCTNAME(this_player())+" stands up.\n");
            this_player()->remove_prop("_sitting_in_couch");
            this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
            return 1;
        }
    }
    else
    {
        this_player()->catch_msg("Stand? Stand up?\n");
        return 1;
    }
    return 1;
}


/*
 * Function to cleanup props if a player leaves before standing
 */
void leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);
    
    if(!objectp(to) || !objectp(ob))
      return;
                
    if(ob->query_prop("_sitting_in_couch"))
    {
        ob->catch_msg("Get up from your comfy spot before leaving.\n");
        say(QCTNAME(ob) + " stands up.\n");
        ob->remove_prop(LIVE_S_EXTRA_SHORT);
        ob->remove_prop("_sitting_in_couch");
    }
}


void
init()
{
    ::init();
    add_action("action_sit", "sit");
    add_action("action_stand", "stand");
}
