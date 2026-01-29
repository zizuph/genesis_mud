/* /d/Faerun/guilds/fire_knives/rooms/mc.c
 *
 * Training Hall for trainees.
 * 
 *
 * Nerull 2019
 *
 */

#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include "../guild.h";

inherit FIREKNIVES_STD_ROOM;
inherit "/lib/skill_raise";
inherit "/lib/guild_support";

#define SS_FIREKNIVES_SKILLS ({SS_SNEAK, SS_HIDE,  \
                               SS_BACKSTAB,  SS_2H_COMBAT, \
                               SS_WEP_KNIFE,  SS_AWARENESS, \
                               SS_APPR_MON,  SS_ALCHEMY, \
                               SS_HERBALISM, SS_ART, SS_ACROBAT, \
                               SS_PARRY, SS_DEFENSE   })

void set_up_skills();

static object  trainer;


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("Training Hall");
     
    set_long("Within the ample room the low ceiling is created by "
    +"padded bunks sewn together and maintained in place by "
    +"criss-crossing wooden planks that are supported by the stone "
    +"columns rising from the ground and meeting the ceiling. From the "
    +"various planks, hanging by thick iron chains, are sacks and dummies "
    +"for practice. The floor's rectangular stones are rough and stained "
    +"with old sweat and blood. On it, to the northwestern side is a "
    +"delimited area covered in mats and marked by thick square blocks "
    +"on the floor, while the walls are bare, devoid of any decorations "
    +"save the markings of the passage of time.\n");
     
     
    add_item(({"room","hall"}),
    "The hall is ample enough for various persons to be within it, all "
    +"doing heavy "
    +"movement. The divisions created by the columns don't detract "
    +"from the purpose "
    +"of the space, but rather compartamentalize it.\n");

    add_item(({"bunks"}),
    "The bunks are thick mats filled with a deafening material, keeping "
    +"both the sound "
    +"in and the cold out.\n");
    
    add_item(({"ceiling"}),
    "The ceiling is low, and artificial. The real one being beyond "
    +"the padded bunks that have been sewn together and maintained "
    +"in place by the wooden planks that are "
    +"supported by the stone columns dividing the room in sections.\n");

    add_item(({"stone", "floor","ground","stones"}),
    "The floor is stained with old sweat and what appears to be "
    +"blood. The only protection "
    +"from it is in the sparring area to the northwestern side of "
    +"the room, which is marked "
    +"by a mat on the floor.\n");

    add_item(({"planks"}),
    "From the various planks hang sacks and dummies for practice "
    +"from thick iron chains.\n");

    add_item(({"columns","stone columns"}),
    "The thick colums divide the room in various sections, allowing "
    +"for different training "
    +"sessions to take place at the same time. They are of a "
    +"thick, cold stone.\n");

    add_item(({"chains","iron chains"}),
    "The iron chains fall heavily from the sturdy wooden planks. From "
    +"them hang dummies and "
    +"sacks on which you can practice your skills when you don't have "
    +"a sparring partner.\n");

    add_item(({"sacks", "dummies","training dummies"}),
    "The sacks are full of sand, making them heavy and strong, while "
    +"the dummies are wooden, "
    +"both ideal for their own specific style of fighting being "
    +"practiced. By the chains from "
    +"which they hang you can gather that they could also be swung "
    +"by someone wanting you to "
    +"practice how to protect yourself.\n");

    add_item(({"sweat","blood","stain","stains"}),
    "Darkened blotches are around the stone floor, hinting at past "
    +"sparring sessions that required "
    +"more than just a sharp mind.\n");

    add_item(({"area","delimited area"}),
    "The area to the northwest is delimited by blocks of stone with "
    +"a thick mat in the middle "
    +"making it look like a sparring one. Here you can test out your "
    +"skills against a willing "
    +"partner.\n");

    add_item(({"mat","mats"}),
    "The mats are thick and hard, but still softer than the stone "
    +"floor they cover. Their purpose "
    +"seems clear as does their wear, stained and crusty as they are.\n ");

    add_item(({"block","blocks"}),
    "Thick cubic blocks are placed around the mat delimiting "
    +"the sparring area. They seem to have "
    +"been moved by a considerable effort due to their apparent weight.\n");

    add_item(({"walls"}),
    "The walls are devoid of any decorative traits, their only "
    +"distinguishing markings are those "
    +"of the passage of time.\n");
    
    create_skill_raise();
    set_up_skills();
    
    add_exit(FIREKNIVES_ROOMS_DIR + "o6.c", "east");

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
    
    to = "sneak";
    sk_add_train(SS_SNEAK,         ({ to, to }), 0, 0, 50);
    
    to = "hide";
    sk_add_train(SS_HIDE,         ({ to, to }), 0, 0, 50);
    
    to = "backstab";
    sk_add_train(SS_BACKSTAB,         ({ to, to }), 0, 0, 50);
   
    to = "two handed combat";
    sk_add_train(SS_2H_COMBAT,         ({ to, to }), 0, 0, 50);
    
    to = "parry incoming blows";
    sk_add_train(SS_PARRY,         ({ to, to }), 0, 0, 50);
    
    to = "defend yourself better";
    sk_add_train(SS_DEFENSE,         ({ to, to }), 0, 0, 50);

    to = "handling and fighting with shivs, daggers and knives";
    sk_add_train(SS_WEP_KNIFE,         ({ to, to }), 0, 0, 50);

    to = "be more aware of your surroundings";
    sk_add_train(SS_AWARENESS,         ({ to, to }), 0, 0, 50);
    
    to = "appraise enemy";
    sk_add_train(SS_APPR_MON,         ({ to, to }), 0, 0, 50);
    
    to = "mix and make various chemicals";
    sk_add_train(SS_ALCHEMY,         ({ to, to }), 0, 0, 40);
    
    to = "find and locate herbs";
    sk_add_train(SS_HERBALISM,          ({ to, to }),  0,0, 50);
    
    sk_add_train(SS_ART, "in the Arts of Assassination",
      "arts",50,50,SS_DEX,50);
}


void
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
    string rank, long_str;

    rank = sk_rank(to_lev);

    this_player()->catch_msg("The elderly musclebound male "
	+"human teaches you to " 
    + sk_tdesc[snum][0] +" better.\n");

    write("You achieve the rank of " + rank + ".\n");

    say("The elderly musclebound male human teaches "
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
    
    if (!trainer)
    {
        trainer = clone_object(FIREKNIVES_GUILD_DIR + "npc/trainee_trainer");
        trainer->move(this_object(), 1);
    }
}


/*
 * Function name: gs_hook_start_meditate
 * Description  : This hook is called when player starts to meditate. You can
 *                mask this function to give a different message.
 */
void
gs_hook_start_meditate()
{
    write("You slip into a corner of the training area and "
    +"begins to meditate. While deep in thought, you realize you " 
    +"can <set> your different preferences, and when finished, you can " 
    +"<rise> from the floor.\n");
        
    say(QCTNAME(this_player()) + " slips into a corner of the training area "
    +"and starts meditating.\n");
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
    +"to reality. You rise from the floor.\n");
        
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


varargs int
sk_query_max(int sknum, int silent)
{
    int occup_stat = max(35, this_player()->query_stat(SS_OCCUP));
    
    int learnmax = 100;
    
    if (IN_ARRAY(sknum, SS_FIREKNIVES_SKILLS))
    {
        learnmax = TP->query_stat(SS_DEX);
    }
    
    return min(learnmax, occup_stat, ::sk_query_max(sknum, silent));
}
