/*         If the guild is closed you can toggle this by doing,
 *         > Call here close_guild
 *         This is a quick way to close/open it if needed
 *
 *	Karath - Feb 17th 1997 - lowered sneak, hide to 20
 *				 and location_sense to 30
 *
 */
 
#pragma save_binary
 
inherit "/d/Emerald/lib/train";
inherit "/std/room";
 
#include "/d/Emerald/defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"
 
#define NUM             sizeof(query_money_types(-1))
 
#define CLOSED          0       /* 1 = closed,   0 = open.  */
 
int closed;
 
 
create_room() { 
 
    closed = CLOSED; 
 
    set_short("Training room of Telseron");
    set_long("   You have entered the training room of Telseron. " +
        "All around here you hear sounds grunting and occaisonal " +
        "scream of agony. Despite it all, you notice this is a "+
        "busy place. The walls are covered with pads so that the " +
        "visitors aren't injured while they improve their mind " +
        "body. You notice that for a small fee, you can also " +
        "learn some valuable skills here.\n" +
        "A small banner is draped across the wall here.\n\n");
 
    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
 
    add_item("banner", "Maybe you should read it.\n");
    add_cmd_item("banner", "read", "@@read_sign@@");

    add_exit(TOWNSHIP_DIR + "rd17", "out");
 
    create_skill_raise();
    set_up_skills();
}
 
enter_inv(ob, from) {
    ::enter_inv(ob, from);
 
    if (!query_ip_number(ob) || !closed)
        return;
 
    if (ob->query_wiz_level()) 
        write("\n\nWARNING!\nYou shouldn't be here. "+
              "I'm doing some work on the guild.\n");
    else {
        write("The guild is closed. Come back later.\n");
        ob->move("/d/Roke/common/gont/monks/entr");
    }
}
 
init()
{
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
 
query_closed() { return closed; }
 
set_up_skills() {
 
    /* Add skill that can be trained. Do not add all skills, and vary a bit */
 
    sk_add_train( SS_CLIMB,      train_text( SS_CLIMB),         0,0,50);
    sk_add_train( SS_SNEAK,      train_text( SS_SNEAK),         0,0,20);
    sk_add_train( SS_HIDE,       train_text( SS_HIDE),          0,0,20);
    sk_add_train( SS_LANGUAGE,   train_text( SS_LANGUAGE),      0,0,50);
    sk_add_train( SS_AWARENESS,  train_text( SS_AWARENESS),     0,0,50);
    sk_add_train( SS_LOC_SENSE,  train_text( SS_LOC_SENSE),     0,0,30);
    sk_add_train( SS_TRADING,    train_text( SS_TRADING),       0,0,30);
    sk_add_train( SS_WEP_SWORD,  train_text( SS_WEP_SWORD),     0,0,30);
}
 
string
tp_objective()
{
  return this_player()->query_objective();
}
 
train_text(skill) {
    string what;
 
    switch(skill) {
 
    case SS_CLIMB:
        what="climb rocky terrain";
        break;
        
    case SS_SNEAK:
        what="sneak into rooms better";
        break;
 
    case SS_LANGUAGE:
        what="speak other languages better";
        break;
 
    case SS_AWARENESS:
        what="be aware of your surroundings";
        break;
       
    case SS_LOC_SENSE:
        what="know your surrounds better";
        break;
 
    case SS_TRADING:
        what="make a better profit when selling";
        break;
        
    case SS_WEP_SWORD:
        what="use swords more effectively";
        break;
        
    case SS_HIDE:
        what=({"hide things or yourself",
               "hide things or "+VBFC_ME("tp_objective")+"self"});
        break;
        
    default:
        what="do nothing. THIS IS A BUG :----)";
        break;
    }
    return what;
}
/*
int
sk_no_train(object who)
{
  int steps;
 
  seteuid(getuid());
 
  if((SECRET)->is_banished(who->query_real_name()))
    {
    who->catch_msg("Too bad.  You've been banished by the council and can't
train here.\n");
      return 1;
    }
 
  if (IS_MEMBER(TP)) 
    {
        return 0;
    }
  
  write("You must be a member to train here.\n");
  return 1;
}
*/

string
read_sign()
{
    return"\n" +
        "           _____________________________________          \n" +
        " _________|                                     |________ \n" +
        " \\        |                                     |       / \n" +
        "  \\       | * You may 'learn' some new          |      /  \n" +
        "   \\      |   skills here.                      |     /   \n" +
        "    \\     |                                     |    /    \n" +
        "     >    | * You may 'improve' your skills      |   <     \n" +
        "    /     |   here.                             |    \\   \n" +
        "   /      |                                     |     \\  \n" +
        "  /       |_____________________________________|      \\ \n" +
        " /___________)                               (__________\\\n";
}
