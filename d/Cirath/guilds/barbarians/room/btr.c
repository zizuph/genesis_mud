/*         If the guild is closed you can toggle this by doing,
 *         > Call here close_guild
 *         This is a quick way to close/open it if needed
 */

inherit "/std/room";
inherit "/d/Cirath/std/shiva_train.c";
#include "defs.h"


void
set_up_skills()
{
    create_skill_raise();
    sk_add_train(SS_SLAYING, "slay your enemy", "slaying", 100, 70);
    sk_add_train(SS_BONKING, "bonk your enemies with your fist/weapon", "bonking", 100, 70);
    sk_add_train(SS_CHOPPING, "chop your enemy", "chop enemy", 100, 70);
    sk_add_train(SS_HOLDING, "stop your enemy from running away", "hold enemy", 100, 70);
    sk_add_train(SS_STABBING, "stab your enemy", "stab enemy", 100, 70);
    sk_add_train(SS_BLOCKING, "block your enemies from hitting you", "block enemy", 100, 70);
    sk_add_train(SS_APPR_MON, "appraise enemies", "appraise enemy", 0, 60);
    sk_add_train(SS_WEP_SWORD, "fight with a sword","sword", 0, 70);
    sk_add_train(SS_WEP_CLUB, "fight with a club","club", 0, 70);
    sk_add_train(SS_WEP_AXE, "fight with an axe", "axe", 0, 70);
    sk_add_train(SS_PARRY, "parry blows", "parry", 0, 70);
    sk_add_train(SS_DEFENCE, "avoid attacks", "defence", 0, 70);
    sk_add_train(SS_BLIND_COMBAT, "fight in dark", "blind fighting", 0, 50);
    sk_add_train(SS_UNARM_COMBAT, "fight unarmed", "unarmed combat", 0, 30);

}    

void
create_room()
{  
    set_short("Training tent");
    set_long("This is the tent where the barbarians improve their "+
             "skills in combat. Many barbarians are training here.\n");

    INSIDE;
 
    set_up_skills();
    add_exit(BARB_ROOM +"br4","west");
    reset_room();    
}

init()
{
    init_skill_raise();
    ::init();
    add_action("help","help");
}
