
/*
 * Training room of the Halflings guild
 * Finwe, September 2015
 */

#pragma save_binary
#pragma strict_types

#include "halflings.h"
#include "/d/Faerun/defs.h"
#include <stdproperties.h>
#include <composite.h>
#include <macros.h>
#include <files.h>
#include <ss_types.h>
#include <std.h>

inherit GUILD_ROOMS;
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

void 
set_up_skills();

private 
mapping members;

void 
reset_room()
{
    ::reset_room;
}

void 
create_guild_room()
{
    add_prop(ROOM_S_MAP_FILE,"faerun_map.txt");

    setuid();
    seteuid(getuid());

    set_short("A Training Room");
    set_long("This large room is where Halflings come to learn skills they " +
        "will use in their travels. Mats are scattered around the room for " +
        "them to practice on, and stuffed dummies line a wall. The room is " +
        "well lit with candles. A wooden plaque is fastened to a wall.\n");

    add_item(({"mats", "mat"}),
        "The mats are square shaped and spread around the room. They look well " +
        "used from all the practices done here in the training room.\n");
    add_item(({"dummies", "stuffed dummies"}),
        "The stuffed dummies are shaped like humans. They are used to spar " +
        "with and for halflings to develop their fighting skills.\n");

    add_cmd_item(({"plaque", "sign"}),({"read", "examine", "exa"}),"@@read_sign@@");

    create_skill_raise();
    create_guild_support();
    set_up_skills();

    reset_room();

    add_exit(HALFGLD_DIR + "rm_post", "north");
    add_exit(HALFGLD_DIR + "rm_join", "south");
}

void 
init()
{
    ::init();
    init_skill_raise();
    init_guild_support();
}

int
check_member()
{
   object tp = this_player();

   if((!tp->query_wiz_level()) && (!IS_MEMBER(tp)))
    {
        write("A large, burly halfling blocks you from going there.\n");
        return 1;
   }
   return 0;
}

void
set_up_skills() 
{
    string me;

    me = "handle animals";
    sk_add_train(SS_ANI_HANDL,({ me, me }),     0,0,35 );
    me = "appraise enemies";
    sk_add_train(SS_APPR_MON,({ me, me }),      0,0,35 );
    me = "learn properties of an object";
    sk_add_train(SS_APPR_OBJ,({ me, me }),      0,0,40 );
    me = "learn the value of an object";
    sk_add_train(SS_APPR_VAL,({ me, me }),      0,0,35 );
    me = "be aware of your surroundings";
    sk_add_train(SS_AWARENESS,({ me, me }),     0,0,35 );
    me = "travel more effectively";
    sk_add_train(SS_CLIMB,({ me, me }),         0,0,35 );
    me = "hide better";
    sk_add_train(SS_HIDE,({ me, me }),          0,0,35 );
    me = "know where you are";
    sk_add_train(SS_LOC_SENSE,({ me, me }),     0,0,45 );
    me = "pick locks";
    sk_add_train(SS_OPEN_LOCK,({ me, me }),     0,0,45 );
    me = "pick pockets";
    sk_add_train(SS_PICK_POCKET,({ me, me }),   0,0,45 );
    me = "sneak around better";
    sk_add_train(SS_SNEAK,({ me, me }),         0,0,40 );
    me = "trade better";
    sk_add_train(SS_TRADING,({ me, me }),       0,0,45 );
}

int
sk_improve(string str)
{
    return ::sk_improve(str);
}

string
read_sign()
{
    return "\n\n"+
    "\t+---------------------------------------------------+\n"+
    "\t|                                                   |\n"+
    "\t|   These are the skills the Halflings of Faerun    |\n"+
    "\t|   can train in.                                   |\n"+
    "\t|                                                   |\n"+
    "\t|    * Animal Handling . . . Confident Acolyte      |\n"+
    "\t|    * Appraise Enemies. . . Confident Acolyte      |\n"+
    "\t|    * Appraise Objects. . . Superior Acolyte       |\n"+
    "\t|    * Appraise Value. . . . Confident Acolyte      |\n"+
    "\t|    * Awareness . . . . . . Confident Acolyte      |\n"+
    "\t|    * Climb . . . . . . . . Confident Acolyte      |\n"+
    "\t|    * Hide. . . . . . . . . Confident Acolyte      |\n"+
    "\t|    * Location Sense. . . . Confident Journeyman   |\n"+
    "\t|    * Open Locks. . . . . . Confident Journeyman   |\n"+
    "\t|    * Pick Pocket . . . . . Confident Journeyman   |\n"+
    "\t|    * Sneak . . . . . . . . Superior Acolyte       |\n"+
    "\t|    * Trading . . . . . . . Confident Journeyman   |\n"+
    "\t|                                                   |\n"+
    "\t+---------------------------------------------------+\n\n";
}
