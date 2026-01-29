/*
 * Training room of the Noldor Guild
 * By Finwe, May 2001
 */
 
#pragma strict_types

#include "noldor.h" 
#include "/d/Shire/rivendell/local.h"

inherit BUILDING_BASE;
inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit "/d/Shire/lib/training";

void set_up_skills();

void
create_guild_room()
{
    set_short("A training room");
    set_long("This is where the Noldor come to learn new things " +
        "to make them better travellers. Unlike most races, the " +
        "Noldor concentrate on improving their minds, and so " +
        "most of the skills they teach here follow that path. " +
        "Lamps and @@daylight_desc@@ flowing in from the windows " +
        "fills the room with light. A silver plaque is attached " +
        "to the wall.\n");

    set_extra_wall(" Large windows are set into the south and " +
        "west walls, filling the room with @@daylight_desc@@.\n");

    set_extra_window("The windows are set into the south " +
	    "and west walls.");
    add_item(({"west window", "western window"}),
         "A winding path leads southwest towards the house.\n");
    add_item(({"south window", "southern window"}),
         "A beautiful garden is laid out in front of the " +
         "building, with a large tree in its center.\n");
    add_item("plaque",
        "The plaque is attached to a wall next to the east door. " +
        "It is made of silver and on it is something written " +
        "in fine elvish lettering.\n");
    add_cmd_item("plaque","read","@@read_sign@@");
        

    create_skill_raise();
    create_guild_support();
    set_up_skills();

    add_exit(NOLGLD_DIR + "med_rm", "north");
    add_exit(NOLGLD_DIR + "foyer", "east");

}

void
init() 
{
    ::init();
    init_skill_raise();
    init_guild_support();
}


void
set_up_skills() {
    string me;
    /* Add skill that can be trained. Do not add all skills, and vary a bit */

    me = "travel about more easily";
    sk_add_train(SS_CLIMB,({ me, me }),       0,0,50 );

    me = "speak other languages with ease";
    sk_add_train(SS_LANGUAGE,({ me, me }),    0,0,50 );
    
    me = "buy and sell more effectively";
    sk_add_train(SS_TRADING,({ me, me }),     0,0,50 );
    
    me = "evaluate enemies";
    sk_add_train(SS_APPR_MON,({ me, me }),    0,0,50 );
    
    me = "find and identify plants";
    sk_add_train(SS_HERBALISM,({ me, me }),   0,0,50 );
    
    me = "perceptive of the surroundings";
    sk_add_train(SS_AWARENESS,({ me, me }),   0,0,50 );
    
    me = "ride steeds";
    sk_add_train(SS_RIDING,({ me, me }),      0,0,50 );

// the following skills are not taxed.       
    me = "handle animals";
    sk_add_train(SS_ANI_HANDL,({ me, me }),   0,0,30 );
    
    me = "battle defences";
    sk_add_train(SS_DEFENCE,({ me, me }),     0,0,20 );
        
    me = "find and remove traps";
    sk_add_train(SS_FR_TRAP,({ me, me }),    0,0,20 );

    me = "handle and use knives";
    sk_add_train(SS_WEP_KNIFE,({ me, me }),   0,0,30 );
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
    "       +---------------------------------------------------+\n"+
    "       |                                                   |\n"+
    "       |   O                                           O   |\n"+
    "       |                                                   |\n"+
    "       |   The Noldor are experts in many fields. Below    |\n"+
    "       |   are the skills they offer here:                 |\n"+
    "       |                                                   |\n"+
    "       |   Climb . . . . . . . . . Superior Journeyman     |\n"+
    "       |   Riding. . . . . . . . . Superior Journeyman     |\n"+ 
    "       |   Defence . . . . . . . . Superior Amateur        |\n"+
    "       |   Animal Handling . . . . Superior Layman         |\n"+
    "       |   Knife . . . . . . . . . Superior Layman         |\n"+
    "       |   Herbalism . . . . . . . Superior Journeyman     |\n"+
    "       |   Appraise Enemy. . . . . Superior Journeyman     |\n"+
    "       |   Find & Remove Traps . . Superior Amateur        |\n"+
    "       |   Language. . . . . . . . Superior Journeyman     |\n"+
    "       |   Awareness . . . . . . . Superior Journeyman     |\n"+
    "       |   Trading . . . . . . . . Superior Journeyman     |\n"+
    "       |                                                   |\n"+
    "       |   O                                           O   |\n"+
    "       |                                                   |\n"+
    "       +---------------------------------------------------+\n\n";
}
