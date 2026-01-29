inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"
#define CLOSED 0

object ob;
void reset_room();

int closed;
object meditate;
create_room() 
{
   ::create_room();
   closed = CLOSED;
   INSIDE;
   set_short("The Shadow Walkers of Kabal training room");
   set_long("This room is a bit smaller. You see targets, "+
   "stuffed dummies and a rack of weapons. A single torch "+
    "burns on the wall, next to a plaque.\n");
   add_item("torch","It casts dim light in the room.\n");
   add_item("rack","The rack contains old daggers, knives "+
   "and maces.\n");
   add_item("dummies","They all have holes in them.\n");
   add_item("targets","Targets with holes in them.\n");
   add_item("plaque","Several words have been written upon it.\n");

   add_cmd_item("plaque","read","Here you may train in the following skills:\n"+
       "Club OR Knife ---- Superior Journyman\n"+
       "You must 'select' a preferred skill first.\n"+
       "To the west, you can train the other skills.\n");
   add_prop(OBJ_S_WIZINFO, "@@wizinfo");
   add_exit("/d/Kalad/common/guilds/shadow_walkers/train","west",0,-1,1);
   create_guild_support();
   create_skill_raise();
   set_up_skills();
   reset_room();
}

void
reset_room()
{
    if(!ob)
    {
        ob = clone_object("/d/Kalad/common/guilds/shadow_walkers/trainer2");
        ob->arm_me();
        ob->move_living("xxx",TO);
    }
}

wizinfo() {
   return("If there should be any need to close down the guild, do so by\n"+
      "typing: Call here close_guild\n"+
      "This will temporarily prevent mortals from entering. After a\n"+
      "reboot, the guild will be open by default.\n\n /Sarr.\n");
}

enter_inv(ob, from) {
   ::enter_inv(ob, from);
   if (!query_ip_number(ob) || !closed)
      return;
   if (ob->query_wiz_level())
      write("\n\nWARNING!\n You shouldn't be here. "+
      "I'm doing some work on the guild.\n");
   else {
      write("The guild is closed. Come back later.\n");
      ob->move("/d/Kalad/common/guilds/shadow_walkers/t11");
   }
}

init() {
   init_guild_support();
   init_skill_raise();
  add_action("select","select");
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
   sk_add_train(SS_WEP_KNIFE, train_text(SS_WEP_KNIFE), 0,0,50);
   sk_add_train(SS_WEP_CLUB, train_text(SS_WEP_CLUB), 0,0,50);
    sk_add_train(SS_WEP_MISSILE, train_text(SS_WEP_MISSILE), 0,0,50);
}

train_text(skill) {
   string what;
   switch(skill) {
    case SS_WEP_MISSILE:
    what = "use missile weapons better";
    break;
      case SS_WEP_KNIFE:
      what="use a dagger more effectivly";
      break;
      case SS_WEP_CLUB:
      what="use a club more effectivly";
      break;
      default:
      what="do nothing. THIS IS A BUG";
      break;
   }
   return what;
}

/*
 * These are the functions that need to be redefined.
 * Note: This particular training room should train
 * _only_ weapon skill, otherwise the SS_PREF_WEAPON
 * will make it impossible to train any other skill, like
 * alchemy or whatever. It is possible to make the room
 * check if a player is trying to improve a weapon skill
 * or another skill, just a little more complicated.
 */
public varargs int sk_query_max(int snum, int silent)
{
    if(snum == SS_WEP_MISSILE)
        return ::sk_query_max(snum,silent);
  if(snum != TP->query_skill(SS_PREF_WEP))
   return 0;

  return ::sk_query_max(snum, silent);
}

int sk_filter_learn(int sk, int steps)
{
    int tmp;


    if(sk == SS_WEP_MISSILE)
        return ::sk_filter_learn(sk,steps);
    if(TP->query_skill(SS_PREF_WEP) != sk)
      return 0;

    return ::sk_filter_learn(sk, steps);
}

int sk_filter_improve(int sk, int steps)
{
    if(sk == SS_WEP_MISSILE)
        return ::sk_filter_improve(sk,steps);
    if(TP->query_skill(SS_PREF_WEP) != sk)
      return 0;

    return ::sk_filter_improve(sk, steps);
}


int 
select(string str)
{
  NF("Select what? knife or club?");
  if(TP->query_skill(SS_PREF_WEP))
  {
    write("You have already selected your preferred weapon!\n");
    return 1;
  }

  if(str == "knife")
  {
    TP->set_skill(SS_PREF_WEP, SS_WEP_KNIFE);
    write("You select knife as your preferred skill.\n");
    return 1;
  }
  if(str == "club")
  {
    TP->set_skill(SS_PREF_WEP, SS_WEP_CLUB);
    write("You select club as your preferred skill.\n");
    return 1;
  }
  return 0;
}


int
sk_hook_no_list_learn()
{
    if(!TP->query_skill(SS_PREF_WEP))
    {
        write("You must first select a weapon skill. In this room, "+
        "type: select 'weapon' . The weapon may be either knife or "+
        "club.\n");
        return 1;
    }
    write("For you there are no unknown skills in this guild. You might\n" +
	"try to improve some or seek out new guilds elsewhere.\n");
    return 1;
}

/*
 * Function name: sk_hook_no_list_improve
 * Description:   No more skills that the player can improve
 * Returns:	  1
 */
int
sk_hook_no_list_improve()
{
    if(!TP->query_skill(SS_PREF_WEP))
    {
        write("You must first select a weapon skill. In this room, "+
        "type: select 'weapon' . The weapon may be either knife or "+
        "club.\n");
        return 1;
    }
    write("There are no skills you can improve in this guild. Perhaps you\n" +
	"would feel like learning some new skills, or try to find a new\n" +
	"guild elsewhere?\n");
    return 1;
}
