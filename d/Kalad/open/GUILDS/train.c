inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/d/Kalad/room_std";
inherit "/lib/trade";

#include "/d/Kalad/defs.h"
#define NUM sizeof(query_money_types(-1))
#define NUMM sizeof(MONEY_TYPES)
#define CLOSED 0
int closed;
object meditate;
create_room() 
{
   ::create_room();
   closed = CLOSED;
   INSIDE;
   add_prop(ROOM_M_NO_TELEPORT,1);
   set_short("Red Fang Rider Training Area");
   set_long("You are within a giant stone chamber. Along the walls you "+
   "see torches that light up the area. You can train here, and there is "+
   "a soft carpet on the floor to mediate. There is a poster on the "+
   "wall. The smell of food comes from the north. You can see people "+
   "training in this area, mounting wolves, hiding from eachother, "+
   "trying to control thier warwolves, and spinning the swrod with "+
   "stunning ability. You can train here too.\n");

   add_item("poster","Several words have been written upon it.\n");
   add_cmd_item("poster","read","Here you may train in the following skills:\n"+
      "Sword ----------- Superior Journeyman\n"+
      "Hide -----------  Confident Journeyman\n"+
      "Sneak ----------- Confident Journeyman\n"+
      "Wolf Riding ----- Superior Guru\n"+
      "Animal Handling - Superior Craftsman\n"+
      "Wolf Handling --- Supirior Guru\n"+
      "tracking -------- Supirior Journeyman\n"+
      "blind fighting -- Supirior Journeyman\n");
   add_prop(OBJ_S_WIZINFO, "@@wizinfo");
   add_item("carpet","Its a soft carpet, where you can meditate.\n");
   add_exit(CPASS(goblin/guild/riders/rhall),"east",0,-1,1);
   add_exit(CPASS(goblin/guild/riders/rbar),"north",0,-1,1);
   create_guild_support();
   create_skill_raise();
   set_up_skills();
}
wizinfo() {
   return("If there should be any need to close down the guild, do so by\n"+
      "typing: Call here close_guild\n"+
      "This will temporarily prevent mortals from entering. After a\n"+
      "reboot, the guild will be open by default.\n\n /Anth.\n");
}
enter_inv(ob, from) {
   ::enter_inv(ob, from);
   if (!interactive(ob) || !closed)
      return;
   if (ob->query_wiz_level())
      write("\n\nWARNING!\n You shouldn't be here. "+
      "I'm doing some work on the guild.\n");
   else {
      write("The guild is closed. Come back later.\n");
      ob->move("/d/Kalad/common/wild/pass/goblin/guild/joinroom");
   }
}
init() {
   init_guild_support();
   init_skill_raise();
   ::init();
}
    
close_guild() {
   if (closed) {
      closed = 0;
      return "  **The guild is now open**";
   }
   closed = 1;
   return "  **The guild is now closed**";
}
query_closed() {return closed;}
set_up_skills() {
   sk_add_train(SS_WEP_SWORD, train_text(SS_WEP_SWORD), 0,0,50);
   sk_add_train(SS_HIDE, train_text(SS_HIDE), 0,0,45);
   sk_add_train(SS_SNEAK, train_text(SS_SNEAK), 0,0,45);
   sk_add_train(SS_WOLF_RIDING, train_text(SS_WOLF_RIDING),"wolf riding",40,100,0,0); 
   sk_add_train(SS_ANI_HANDL, train_text(SS_ANI_HANDL),0,0,60);
   sk_add_train(SS_WOLF_HANDLING, train_text(SS_WOLF_HANDLING),"wolf handling",40,100,0,0);
   sk_add_train(SS_TRACKING, train_text(SS_TRACKING),0,0,50); 
   sk_add_train(SS_BLIND_COMBAT, train_text(SS_BLIND_COMBAT),0,0,50);
}

train_text(skill) {
   string what;
   switch(skill) {
      case SS_ANI_HANDL:
      what="work with animals better";
      break;
      case SS_WOLF_RIDING:
      what="ride wolves better";
      break;
      case SS_WEP_SWORD:
      what="use a sword better";
      break;
      case SS_HIDE:
      what="hide inside rooms";
      break;
      case SS_SNEAK:
      what="move around more covertly";
      break;
      case SS_WOLF_HANDLING:
      what="Control a wolf in combat, and make it attack correctly";
      break;
      case SS_BLIND_COMBAT:
      what="fight in the dark, or when blinded";
      break;
      case SS_TRACKING:
      what="track an enemy";
      break;
   }
   return what;
}
void
gs_hook_start_meditating()
{
   write("You step onto the carpet, sit down and meditate.\n");
   say(QCTNAME(TP) + " sits on the carpet and meditates.\n");
}

int
gs_hook_rise()
{
   write("As if ascending from a great depth, you rise to the surface\n" +
      "of your consciousness, and get off the corpet.\n");
   say(QCTNAME(TP) + " rises from the carpet.\n");
}
