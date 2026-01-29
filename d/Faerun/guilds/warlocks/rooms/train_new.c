/* /d/Faerun/guilds/warlocks/rooms/train.c
 *
 * Warlock training room.
 *
 * Nerull, 2018
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit WARLOCK_STD_ROOM;
inherit "/lib/skill_raise";
inherit "/lib/guild_support";

void set_up_skills();


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */
public void
create_warlock_room()
{
    seteuid(getuid());

    add_prop(ROOM_I_INSIDE, 1);

    set_short("You are inside a narrow humid claystone cavity");

    set_long("You are inside a narrow humid claystone cavity. The "
    +"close proximity of the jagged walls in conjunction with the "
    +"constant torrent of steam emanating from the large iron "
    +"cauldron makes this place very humid and slightly claustrophobic. The "
    +"reek of boiled infant flesh stings in your nostrils, forcing you "
    +"at times to face away from the cauldron and towards the various "
    +"claystone depressions and sharp jagged mold-infested edges that "
    +"are present everywhere. Tiny toes and fingers from various "
    +"humanoid infants hang in hairlike threads anchored to the "
    +"ceiling. Small black candles in several depressions in the "
    +"walls emit some level of illumination to the environment, along "
    +"with flickering shadows. It is possible to <meditate> here.\n");

    create_skill_raise();
    set_up_skills();

    add_item(({"candle", "candles", "black candles",
    "small black candles", "small candles"}), "These are small sticks of "
    +"black wax. They occupy small depressions in the claystone walls, and "
    +"provide the area with some collective illumination.\n");
    
    add_item(({"wooden fire", "fire"}), "Under the cauldron there is "
    +"a burning wooden fire, consisting of various dried branches "
    +"from dead trees. It emanates a lot of heat, maybe enhanced "
    +"by ancient magic to keep it much more intense.\n");
    
    add_item(({"humidity"}), "When you breathe, it's like breathing "
    +"water. Small pearls of water forms on your forehead simply "
    +"for being in this cavity.\n");
    
     add_item(({"shadows", "flickering shadows"}), "The shadows formed "
     +"by jagged edges and "
     +"formations in the cave dance in unison with the flickering of "
     +"the lit candles. You feel slightly dizzy when focusing on them.\n");
    
    add_item(({"cavity", "cave"}), "This cavity seems to be the result "
    +"of erosion from water gone long ago. It's full of jagged edges "
    +"and small depressions.\n");
    
    add_item(({"hairlike threads", "threads"}), "Hmm...they are thin and "
    +"strikingly resembles hair. Actually, when you think of it, the threads "
    +"seem to be made of humanoid hair!\n");
    
    add_item(({"tiny fingers", "fingers", "humanoid fingers",
    "tiny humanoid fingers"}), "The fingers are from various types "
    +"of humanoids; humans, elves, dwarves, drows, hobbits and "
    +"kenders. Some are new, some are old, but they all are "
    +"from infants. They hang dangling tied together with "
    +"thin hairlike threads hanging from the ceiling.\n");
    
    add_item(({"tiny toes", "toes", "humanoid toes",
    "tiny humanoid toes"}), "The toes are from various types "
    +"of humanoids; humans, elves, dwarves, drows, hobbits and "
    +"kenders. Some are new, some are old, but they all are "
    +"from infants. They hang dangling tied together with "
    +"thin hair-like threads hanging from the ceiling.\n");
    
    add_item(({"ceiling", "roof"}), "The ceiling is jagged and filled "
    +"with black spots of mold. At the west side of the ceiling, thin "
    +"hairlike threads anchored to iron bolts hang from the "
    +"ceiling, carrying the weight of numberous tiny humanoid "
    +"fingers and toes. A few satchels filled with various herbs "
    +"hang from the ceiling too, tied to some jagged edges.\n");
    
    add_item(({"wall", "walls", "jagged walls", "jagged wall"}), "Sharp "
    +"jagged claystone edges decorate the rough walls here along with "
    +"many small depressions. They are "
    +"probably a result of erosion.\n");
    
    add_item(({"depression", "depressions", "small depressions"}), "They "
    +"are small natural groves created by erosion, and they are "
    +"everywhere in this cavity. Also, they are put to good use by "
    +"someone as they all have small lit black candles that illuminate "
    +"the room. Cozy.\n");
    
    add_item(({"torrent of steam", "steam", "torrent"}), "The torrent "
    +"is a result of something boiling violently in the large iron "
    +"cauldron. It makes the room steamy and very humid, for not to "
    +"mention adding the reek of boiled infant flesh.\n");
    
    add_item(({"spots", "mold", "black mold"}), "Various black puffy "
    +"spots of poisonous mold pride many of the jagged claystone "
    +"edges. It is probably unhealthy to stay in this environment "
    +"for too long.\n");
    
    add_item(({"edges", "jagged edges", "mold-infested edges"}), "Every "
    +"surface of the walls and the ceiling consists of sharp natural "
    +"claystone edges. They were probably created long ago by "
    +"erosion. Some of them have spots of black mold that is probably "
    +"sustained by the present humidity.\n");

    add_exit(WARLOCK_ROOMS_DIR + "hall01", "east");
    
    room_add_object(WARLOCK_OBJ_DIR + "iron_cauldron");
    
    add_npc(WARLOCK_GUILD_DIR + "npc/whispess", 1);

    reset_faerun_room();
}


public void
init()
{
    init_skill_raise();
    init_guild_support();
    ::init();
}


void
set_up_skills()
{
    string to;

    to = "use air magic";
    sk_add_train(SS_ELEMENT_AIR,        ({ to, to }),  0,0, 50);

    to = "use water magic";
    sk_add_train(SS_ELEMENT_WATER,      ({ to, to }),  0,0, 50);

    to = "use earth magic";
    sk_add_train(SS_ELEMENT_EARTH,      ({ to, to }),  0,0, 50);

    to = "cast abjuration magic";
    sk_add_train(SS_FORM_ABJURATION,    ({ to, to }),  0,0, 50);

    to = "cast enchantment magic";
    sk_add_train(SS_FORM_ENCHANTMENT,    ({ to, to }),  0,0, 50);

     to = "cast conjuration magic";
    sk_add_train(SS_FORM_CONJURATION,    ({ to, to }),  0,0, 50);

     to = "cast transmutation magic";
    sk_add_train(SS_FORM_TRANSMUTATION,  ({ to, to }),  0,0, 50);

    to = "cast illusion magic";
    sk_add_train(SS_FORM_ILLUSION,      ({ to, to }),  0,0, 50);

    to = "cast divination magic";
    sk_add_train(SS_FORM_DIVINATION,    ({ to, to }),  0,0, 50);

    to = "find and locate herbs";
    sk_add_train(SS_HERBALISM,          ({ to, to }),  0,0, 50);

    to = "master spellcraft";
    sk_add_train(SS_SPELLCRAFT,         ({ to, to }), 0, 0, 60);
}


public varargs int
sk_query_max(int snum, int silent)
{
    int day;
    int max_skill = ::sk_query_max(snum, silent);

    setuid();
    seteuid(getuid());

    if (snum == SS_SPELLCRAFT)
    {
	    if (this_player()->query_guild_name_occ() == WARLOCK_NAME)
	    {
            max_skill = MIN(max_skill, 75);
        }
        else
        {
          max_skill = MIN(max_skill, 60);
        } 
    }

    if (snum == SS_ELEMENT_AIR)
    {
	    if (this_player()->query_guild_name_occ() == WARLOCK_NAME)
	    {
            max_skill = MIN(max_skill, 75);
        }
        else
        {
          max_skill = MIN(max_skill, 50);
        } 
    }
    
    if (snum == SS_ELEMENT_EARTH)
    {
	    if (this_player()->query_guild_name_occ() == WARLOCK_NAME)
	    {
            max_skill = MIN(max_skill, 75);
        }
        else
        {
          max_skill = MIN(max_skill, 50);
        } 
    }
    
    if (snum == SS_ELEMENT_WATER)
    {
	    if (this_player()->query_guild_name_occ() == WARLOCK_NAME)
	    {
            max_skill = MIN(max_skill, 75);
        }
        else
        {
          max_skill = MIN(max_skill, 50);
        } 
    }

    return max_skill;
}


private int
can_train_this_skill(string skill, int step)
{
    int s = sk_find_skill(skill);

    /*** we allow to forget anything he wants ***/
    if (step < 0) return 1;
    
    
   
    if (s == SS_SPELLCRAFT)
    {
	    if (this_player()->query_base_skill(SS_SPELLCRAFT) + step > 50)
	    {
	        if (this_player()->query_guild_name_occ() != WARLOCK_NAME)
	        {
		 
		        write("Only occupational archers can train that high!\n");
		    }
            
		    return 0;
                
		       return 0;
	        }
	    }
        
	    return 1;
    }

    return 1;
}


void
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
    string rank, long_str;

    rank = sk_rank(to_lev);

    this_player()->catch_msg("The old gruesome hag teaches you to " 
    + sk_tdesc[snum][0] +" better.\n");

    write("You achieve the rank of " + rank + ".\n");

    say("The old gruesome hag teaches "
    +QCTNAME(this_player()) + " to "
    +sk_tdesc[snum][1] + " better!\n");
}


int
sk_improve(string str)
{
    return ::sk_improve(str);
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
}


/*
 * Function name: gs_hook_start_meditate
 * Description  : This hook is called when player starts to meditate. You can
 *                mask this function to give a different message.
 */
void
gs_hook_start_meditate()
{
    write("You slip into a corner of the mold-infested cavity and "
    +"begins to meditate. While deep in thought, you realize you " 
    +"can <set> your different preferences, and when finished, you can " 
    +"<rise> from the floor.\n");
        
    say(QCTNAME(this_player()) + " slips into a corner of the mold-infested "
    +"cavity and starts meditating.\n");
}


/*
 * Function name: gs_hook_rise
 * Description  : This hook is called when player rises from the meditation.
 *                You can mask this function to give a different message.
 */
void
gs_hook_rise()
{
    write("A feeling of contentment washes over you as you mind returns " 
    +"to reality. You rise from the claystone floor.\n");
        
    say(QCTNAME(this_player()) + " rises from the floor.\n");
}


/*
 * Function name: gs_hook_catch_error
 * Description  : This hook is called when a player tried to do something 
 *                strange while meditating like examining things or leave 
 *                the room. You can mask this function to give a different 
 *                message.
 * Arguments    : string str - Argument the player tried to send to his 
 *                command.
 * Returns      : int 1 - normally.
 */
int
gs_hook_catch_error(string str)
{
    write("You are currently meditating, so it prevents you from "
    +"doing that. However, when you are done, you may <rise> from "
    +"the floor.\n");
    
    return 1;
}
