#pragma strict_types

#include "/d/Shire/sys/defs.h"
#include "sindar_racial.h" 
//#include "/d/Shire/greyhavens/local.h"

inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit "/d/Shire/std/room";


void set_up_skills();

void
create_shire_room()
{
    set_short("A training room");
    set_long("This is the Sindar training room.\n");

        

    create_skill_raise();
    create_guild_support();
    set_up_skills();

    add_exit(SINDAR_RACE_DIR + "start_rm", "east");

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
    "       |   Climb . . . . . . . . . Superior Journeyman     |\n"+
    "       |   Riding. . . . . . . . . Superior Journeyman     |\n"+ 
    "       |   Defence . . . . . . . . Superior Amateur        |\n"+
    "       |   Animal Handling . . . . Superior Layman         |\n"+
    "       |   Knife . . . . . . . . . Superior Layman         |\n"+
    "       |   Herbalism . . . . . . . Superior Journeyman     |\n"+
    "       |   Appraise Enemy. . . . . Superior Journeyman     |\n"+
    "       |   Find & Remove Traps . . Superior Amateur        |\n"+
    "       |   Language. . . . . . . . Superior Acolyte        |\n"+
    "       |   Awareness . . . . . . . Superior Journeyman     |\n"+
    "       |   Trading . . . . . . . . Superior Journeyman     |\n"+
    "       |                                                   |\n"+
    "       |   O                                           O   |\n"+
    "       |                                                   |\n"+
    "       +---------------------------------------------------+\n\n";
}
