/* /d/Faerun/guilds/fire_knives/rooms/guru.c
 *
 * Guru knife training Hall for Full Members
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

#define SS_FIREKNIVES_SKILLS ({SS_WEP_KNIFE})

void set_up_skills();

static object  ruddock;


/*
 * Function name: create_warlock_room
 * Description  : Constructor, redefine this to configure your room
 */

public void
create_fireknives_room()
{
    add_prop(ROOM_I_INSIDE, 1);

    set_short("A dim cave in the wall");
     
    set_long("A rather large room with rough and unworked walls. The "
    +"light is very low and it seems to come from a glowing ball, "
	+"hanging from the ceiling. The stone is rough and made out of "
	+"granit, a few niches are in the wall containing various things "
	+"and some shelves on the walls. Close to the entrance on the "
	+"right hand side is a table with papers and other items "
	+"scattered on it with a simple chair standing behind it. The "
	+"left hand side has a rather large wardrobe and a chest "
	+"standing beside eachother close to the wall. On a large table "
	+"in the farthest wall from your entrance is a bed and a large "
	+"cage in wich you can barely make out dark eyes watching you.\n");
     
    add_item(({"wall", "walls"}),
    "Rocks made out of rough granite and now that you look closer "
	+"you can't see any traces of ever having been tooled.\n");

    add_item(({"ball", "light"}),
    "The light radiated is quite low though the heat is "
	+"surprisingly high. Inside you can see some swirling fire.\n");
    
    add_item(({"table", "large table"}),
    "A simple brown table made out of rough wood.\n");

    add_item(({"shelf", "shelves", "niches", "niche"}),
    "The shelves and niches contain nothing of interest to you\n");

    add_item(({"chair", "simple chair"}),
    "A simple wooden chair with the symbol of the "
	+"Fireknives on engraved the back.\n");

    add_item(({"wardrobe"}),
    "A large black wardrobe, unadorned and with no lock on it.\n");

    add_item(({"chest"}),
    "A medium sized chest made out of dark wood and black "
	+"iron with no lock on it.\n");

    add_item(({"cage", "bird cage"}),
    "In the darkest part of the room is a cage made from "
	+"wood with many darting eyes just flashing in the "
	+"slight glimts of light now and then, and there must "
	+"be quite a few but its to dark to count them. These "
	+"are Ruddock's crows, and you may <borrow crow> if "
	+"you need one.\n");

    add_item(({"bed", "simple bed"}),
    "A simple bed with a blanket and pillow on it.\n");
	
	add_item(({"floor", "ground"}),
    "The floor is slightly uneven and it has a small lean to it.\n");
	
	add_item(({"roof", "ceiling"}),
    "The ceiling is of plain and somewhat jagged granite. Beside shadows, "
	+"there is nothing to see there.\n");

    create_skill_raise();
    set_up_skills();
    
    add_exit(FIREKNIVES_ROOMS_DIR + "ft", "east");

    reset_faerun_room();
}


public int
do_borrow(string str) 
{
   setuid();
   seteuid(getuid());
    
   object crow;
   
   if ((str != "crow") && (str != "grey crow"))
   {
      notify_fail("Borrow what?\n");
      
      return 0;
   }
   
   crow = clone_object(FIREKNIVES_GUILD_DIR + "obj/crow");
   
   if(crow->move(this_player()))
   {
      notify_fail("You cannot carry that much!\n");
      
      crow->remove_object();
      
      return 0;
   }
   
   write("You open the birdcage and borrow one of Ruddock's "
   +"grey black-headed crows.\n");
   
   say(QCTNAME(this_player()) + " opens the birdcage and "
   +"borrows one of Ruddock's grey black-headed crows.\n");
   
   return 1;
}


public void
init()
{
    init_skill_raise();
    init_guild_support();
    ::init();
	add_action(do_borrow, "borrow",0);
}


void
set_up_skills()
{
    string to;
      
    to = "handling and fighting with shivs, daggers and knives";
    sk_add_train(SS_WEP_KNIFE,         ({ to, to }), 0, 0, 100);
}


void
sk_hook_raise_rank(int snum, int to_lev, int cost)
{
    string rank, long_str;

    rank = sk_rank(to_lev);

    this_player()->catch_msg("The bald muscular male human teaches you to " 
    + sk_tdesc[snum][0] +" better.\n");

    write("You achieve the rank of " + rank + ".\n");

    say("The bald muscular male human teaches "
    +QCTNAME(this_player()) + " to "
    +sk_tdesc[snum][1] + " better!\n");
}


int
sk_improve(string str)
{
    return ::sk_improve(str);
}


varargs int
sk_query_max(int sknum, int silent)
{
    int occup_stat = max(20, this_player()->query_stat(SS_OCCUP));
    
    int learnmax = 100;
    
    if (IN_ARRAY(sknum, SS_FIREKNIVES_SKILLS))
    {
        learnmax = TP->query_stat(SS_DEX);
    }
    
    // Trainees limited to 20 in knife skill. Limitator.
    if (FIREKNIVES_MAPPINGS->query_assassin_rank(this_player()->query_name())
        <= MAX_PROSPECT_RANK)
    {
        learnmax = 21;
    }
    
    /* Fire Knives Guru quest not completed. If for some reason
       member has gained access to this room without completing
       the guru quest, he cant train skills over 20 points.*/
    if (!this_player()->test_bit(DOMAIN, SIGNET_RING_QUEST_GROUP, 
                             SIGNET_RING_QUEST_BIT))
    {
        learnmax = 21;
    }
    
    return min(learnmax, occup_stat, ::sk_query_max(sknum, silent));
}


void
reset_faerun_room()
{
    ::reset_faerun_room();
    
    if (!ruddock)
    {
        ruddock = clone_object(FIREKNIVES_GUILD_DIR + "npc/ruddock_join");
        ruddock->move(this_object(), 1);
    }
}