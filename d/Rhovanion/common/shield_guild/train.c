/*     The Guild in Re Albi, original code by Styles, modified by Ged    */

/*     If the guild is closed you can toggle this by doing,
 *     > Call here close_guild
 *     This is a quick way to close/open it if needed
 */

#pragma save_binary

inherit "/lib/skill_raise";
inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include "guild.h"

/*
 * Global variables
 */
int closed;

/*
 *  Prototypes
 */
void set_up_skills();

void create_room()
{
  closed = 0; /* open by default */

  set_short("training room");
  set_long("This is the training room for Angmar's army. You see many "+
    "warriors practising their skills over and over again and hence "+
    "trying to achieve perfection.\n"+
    "   Most of them are practising fighting using shield and club. You "+
    "spy one warrior swinging his club in an extremely dangerous way. "+
    "You are relieved that you are not taking the place of his opponent "+
    "who skillfully defends himself against this assault with his shield. "+
    "Some of the warriors are even fighting blindfolded. They are "+
    "probably preparing for a night attack somewhere.\n"+
    "   Not everyone is fighting here. Some of them are playing a "+
    "strange game. They are guessing the strength or wisdom of "+
    "each other and then by solving riddles or lifting weights they can "+
    "find out whose guess was the best. Another group is playing yet "+
    "another game. They are hiding different things or themselves for "+
    "others to try and find.\n\n"+
    "Ouch!!!\nOne soldier scared you to death! You did not see him "+
    "arrive... He suddenly appeared right in front of you!\n\n"+
    "You also notice a piece of paper pinned to the wall.\n");

  add_item(({"warrior","warriors"}),
            "You see many warriors doing strange things.\n");
  add_item(({"list","paper"}), "It is only a piece of paper but there are "+
                "some words written on it.\n");
  add_cmd_item(({"list","paper"}), "read", "@@list@@");

  add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
  add_prop(OBJ_S_WIZINFO, "@@wizinfo");

  add_exit(THIS_DIR+"chapel", "north");
  add_exit(THIS_DIR+"start", "west");
  add_exit(THIS_DIR+"c1", "south");
  add_exit(THIS_DIR+"priv", "east");

  create_skill_raise();
  set_up_skills();
}

string wizinfo()
{
   return "If there is a reason you can close/open guild by typing:\n"+
       "     Call here close_guild\n"+
       "This will temporarily prevent mortals from entering. "+
       "After a reboot the guild is open by default.\n\n   Milan\n";
}

void enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);

  if(!query_ip_number(ob) || !closed)
  {
    if(ob->query_member_killer() == 2)
    {
      set_alarm(0.0, 0.0, "punish_him", ob);
    }
    return;
  }

  if(ob->query_wiz_level())
    write("\nWARNING!\nI'm doing some work on the guild.\n");
  else
  {
    write("The guild is closed. Come back later.\n");
    ob->move(THIS_DIR+"c1");
  }
}

void punish_him(object who)
{
  who->make_him_pay();
}

void init()
{
  init_skill_raise();
  ::init();
}

string close_guild()
{
  if(closed)
  {
    closed = 0;
    return "*** The guild is now open ***\n";
  }
  closed = 1;
  return "*** The guild is now closed ***\n";
}

int query_closed() { return closed; }

mixed train_text(int skill)
{
  mixed what;

  switch(skill)
  {
    case SS_WEP_CLUB:
        what="fight with clubs";
        break;
    case SS_PARRY:
        what="parry blows when wielding a weapon";
        break;
/*
    case SS_DEFENCE:
        what=({"defend yourself","defend "+HIM(TP)+"self"});
        break;
*/
    case SS_BLIND_COMBAT:
        what="fight in the dark";
        break;
    case SS_SMASH:
        what="smash enemy with a club";
        break;
    case SS_SHIELD:
        what="to use shield for dodging blows";
        break;
    case SS_AWARENESS:
        what="be aware of surrounding";
        break;
    case SS_APPR_MON:
        what="be able estimate a possible oponent";
        break;
/*
    case SS_HIDE:
        what=({"hide things or yourself", "hide things or "+HIM(TP)+"self"});
        break;
*/
    case SS_SNEAK:
        what="sneak somewhere";
        break;
    default:
        what="do nothing. THIS IS A BUG :----)";
        break;
  }
  return what;
}

void set_up_skills()
{
  sk_add_train(SS_WEP_CLUB,     train_text(SS_WEP_CLUB),     0,0,100 );
  sk_add_train(SS_PARRY,        train_text(SS_PARRY),        0,0,50 );
  sk_add_train(SS_DEFENCE,  ({"defend yourself","defend "+HIM(TP)+"self"}),
                                                             0,0,80 );
  sk_add_train(SS_BLIND_COMBAT, train_text(SS_BLIND_COMBAT), 0,0,60 );

  sk_add_train(SS_SMASH, train_text(SS_SMASH),  "smash",75,100,SS_STR, 90);
  sk_add_train(SS_SHIELD,train_text(SS_SHIELD),"shield",85,100,SS_DEX,110);

  sk_add_train(SS_AWARENESS,    train_text(SS_AWARENESS),    0,0,60 );
  sk_add_train(SS_APPR_MON,     train_text(SS_APPR_MON),     0,0,70 );

  sk_add_train(SS_HIDE,
   ({"hide things or yourself", "hide things or "+HIM(TP)+"self"}),
                                                             0,0,58 );
  sk_add_train(SS_SNEAK,        train_text(SS_SNEAK),        0,0,57 );
}

int can_train_this_skill(object who, string skill, int step)
{
  int allow, s = sk_find_skill(skill);

  if(step < 0) return 1;  /* we allow to forget anything he wants */
  if(who->query_alignment() > 50)
  {
    who->catch_msg("We do not allow 'goodies' to train here!\n");
    return 0;
  }
  if(who->query_prop(S_C_PUN))
  {
    who->catch_msg("You are banned from training here!\n");
    return 0;
  }
  if(step > 1)
  {
    who->catch_msg("Ho, ho!!! Training is hard process! One step at a time!\n");
    return 0;
  }
  if(who->query_guild_name_occ() != GUILD_NAME)  /* layman */
  {
    switch(s)
    {
      case SS_WEP_CLUB:
      case SS_DEFENCE:
        if(who->query_base_skill(s) < 50) allow = 1;
        break;
      case SS_BLIND_COMBAT:
        if(who->query_base_skill(s) < 20) allow = 1;
        break;
      case SS_HIDE:
        if(who->query_base_skill(s) < 50) allow = 1;
        break;
      case SS_SNEAK:
        if(who->query_base_skill(s) < 50) allow = 1;
        break;
      default: allow = 1;
    }
    if(!allow)
      who->catch_msg("Those levels are only for occupational warriors!\n");
    if(allow && (10*who->query_skill(s) >
                 (who->query_s_c_stat() -
                  (who->query_alignment()>0 ? who->query_alignment() : 0)
      )         ))
    {
      allow = 0;
      who->catch_msg("Your position in army is too low for that!\n");
    }
    return allow;
  }
  if(s == SS_WEP_CLUB) /* guru quest */
  {
    if((who->query_base_skill(SS_WEP_CLUB) < 90) ||
       present("_club_sup_guru_", who))
      return 1;
    who->catch_msg("You must be worthy to be able train so high!\n");
    return 0;
  }
  if(10*who->query_skill(s) >
     (who->query_s_c_stat() -
      (who->query_alignment()>0 ? who->query_alignment()/2 : 0)
    ))
  {
    who->catch_msg("Your position in army is too low for that!\n");
    return 0;
  }
  return 1;
}

int sk_improve(string str)
{
  int steps;
  string skill;

  if(str)
    if(!sscanf(str, "%s %d", skill, steps))
      if(!sscanf(str, "%d", steps))
        sscanf(str, "%s", skill);

  if(!skill) return sk_list(steps);

  if(TP->query_guild_member(GUILD_NAME))
  {
    if(can_train_this_skill(TP, skill, steps))
    {
      return ::sk_improve(str);
    }
    return 1;
  }
  write("You must be a member of the army to be able to train here.\n");
  return 1;
}

string list()
{
  sk_list(-1);
  return "\n"+
         "    Layman members are restricted in these skills:\n"+
         "    ----------------------------------------------\n"+
         "      club .............. superior journeyman\n"+
         "      defence ........... superior journeyman\n"+
         "      blindfighting ..... superior amateur\n"+
         "      hide .............. superior journeyman\n"+
         "      sneak ............. superior journeyman\n";
}

public varargs int sk_query_max(int snum, int silent)
{
  if(TP->query_prop(S_C_PUN)) return 0;

  if(TP->query_guild_name_lay() == GUILD_NAME)  /* layman */
    switch(snum)
    {
      case SS_HIDE:
      case SS_SNEAK:
      case SS_WEP_CLUB:
      case SS_DEFENCE:
        return 50;
      case SS_BLIND_COMBAT:
        return 20;
    }

  if((snum == SS_WEP_CLUB) && (!present("_club_sup_guru_", TP)))
    return 90;

  return ::sk_query_max(snum, silent);
}
