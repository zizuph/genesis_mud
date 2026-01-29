/*     Created by:      ???
 *     purpose:		
 *     Location:         
 *     Modified:        Toby, 97-09-18 (fixed gs_hook_start_meditating to
 *			gs_hook_start_meditate as it should be to work)
 */

inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/d/Kalad/room_std";
inherit "/lib/trade";

#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/red_fang/default.h"

#define NUM sizeof(query_money_types(-1))
#define NUMM sizeof(MONEY_TYPES)
#pragma strict_types
#pragma save_binary

string train_text(int i);

void
set_up_skills() 
{
    sk_add_train(SS_WEP_KNIFE, train_text(SS_WEP_KNIFE), 0,0,40);
    sk_add_train(SS_CLIMB, train_text(SS_CLIMB), 0,0,50);
    sk_add_train(SS_SNEAK, train_text(SS_SNEAK), 0,0,50);
    sk_add_train(SS_WOLF_RIDING, train_text(SS_WOLF_RIDING),"wolf riding",40,50,0,0); 
    sk_add_train(SS_ANI_HANDL, train_text(SS_ANI_HANDL),0,0,50);
}

void
create_room() 
{
    ::create_room();
    INSIDE;
    set_short("Red Fang Training Area");
    set_long("\n   You are within a giant stone chamber. Allong the walls "+
    "you see torches that light up the area. The ground is dirty and smelling "+
    "of animal dung.\n"+ 
    "   You see many young goblins here training with daggers, "+
    "scaling up walls, practicing stealth, and riding around on wolves. "+
    "There is a plaque on the wall here, and a strange pit in the corner."+
    " There is what appears to be a stable to the southwest.\n\n");

    add_item("plaque","Several words have been written upon it.\n");
   add_cmd_item("plaque","read","Here you may train in the following skills:\n"+
      "Knife ----------- Superior Acolyte\n"+
      "Climb ----------- Superior Journeyman\n"+
      "Sneak ----------- Superiour Journeyman\n"+
      "Wolf Riding ----- Superiour Journeyman\n"+
      "Animal Handling - Superiour Journeyman\n"+
      "You can buy your own wolf for only 5 platinum coins southwest of here.\n");
    add_item("pit","Its a sand pit, where you can meditate.\n");
    add_exit(FANG_DIR(rooms/joinroom),"east",0,-1);
    add_exit(FANG_DIR(rooms/stable),"southwest",0,-1);
    create_guild_support();
    create_skill_raise();
    set_up_skills();
}

void
init() 
{
    ::init();
    init_guild_support();
    init_skill_raise();
}


string
train_text(string skill) 
{
    string what;
    switch(skill) 
    {
        case SS_ANI_HANDL:
        what="work with animals better";
        break;
        case SS_WOLF_RIDING:
        what="ride wolves better";
        break;
        case SS_WEP_KNIFE:
        what="use a dagger better";
        break;
        case SS_CLIMB:
        what="scale surfaces better";
        break;
        case SS_SNEAK:
        what="move around more covertly";
        break;
        default:
        what="do nothing. THIS IS A BUG";
   }
   return what;
}

void
gs_hook_start_meditate()
{
    write("You step into the pit, sit down and meditate.\n" +
	  "You find yourself able to <estimate> your different " +
	  "preferences and <set> them at you own desire. Just " +
	  "<rise> when you are done meditating.\n");
    say(QCTNAME(TP) + " enters the pit and meditates.\n");
}

void
gs_hook_rise()
{
    write("As if ascending from a great depth, you rise to the surface\n"+
      "of your consciousness, and climb out of the pit.\n");
    say(QCTNAME(TP) + " rises from meditation and steps out of the pit.\n");
}
