
/*     Training room for the Trickster guild.   */

/*         If the guild is closed you can toggle this by doing,
 *         > Call here close_guild
 *         This is a quick way to close/open it if needed
 */

#pragma save_binary

inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/d/Shire/std/room";
inherit "/d/Shire/lib/training";

#include "/d/Shire/skills.h"
#include "/d/Shire/common/defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"
#include "trickster.h"

#define WRITE_NAME(o)  sprintf("%-11s", capitalize((o)->query_real_name()))
#define TO this_object()
#define TP this_player()
#define LOG_SIZE       25000
#define NUM             sizeof(query_money_types(-1))

#define CLOSED          0       /* 1 = closed,   0 = open.  */

// Prototypes
string train_text(int skill);
void set_up_skills();

int closed;
object meditate;

void
create_shire_room() 
{   
    closed = CLOSED;

    set_short("Tricksters' Training Room");
    set_long("This room has a layer of water coating the floor, "+
      "nearly ankle-deep.  Here Tricksters may train existing skills and "+
      "learn new skills.  The walls are of scorched earth, and a medium-"+
      "sized hole in the southwest wall leads to a moist, poorly lit room." +
      "  As well there is another brightly lit exit towards the southeast, " +
      "from which loud noises can be heard coming from. There is a sign " +
      "on the floor here.\n");


    add_item("sign","While muddled with the mud and water on the "+
      "floor, it is still readable.\n");

    add_item(({"wall","walls","earth","scorched earth"}),
      "The blackened earthen walls have been scorched by intense heat, "+
      "which obviously has escaped the water on the floor.\n");

    add_item(({"medium hole","medium-sized hole","hole","dark room"}),
      "The hole leading to the poorly lid room is big enough to accomodate "+
      "all but the tallest people.\n");

    add_item(({"water","layer","layer of water","floor"}),"The thin "+
      "layer of water that coats the floor is thankfully clear, though "+
      "walking around causes a bit of squishing.\n");

    add_cmd_item("sign","read","This is the training room for the Tricksters.\n");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");


    create_guild_support();
    create_skill_raise();
    set_up_skills();

//    add_exit(TRICK_DIR + "join","north",0,1);
    add_exit(TRICK_DIR + "join.novouching","north",0,1);
    add_exit(TRICK_DIR + "hallway","southeast",0,1);
    add_exit(TRICK_DIR + "boardroom","southwest",0,1);
}


nomask private void
log_guild(string text)
{
    setuid();
    seteuid(getuid());

    if (file_size(TRICKSTER_GUILD_LOG) > LOG_SIZE)
    {
	rename(TRICKSTER_GUILD_LOG, (TRICKSTER_GUILD_LOG + ".old"));
    }

    write_file(TRICKSTER_GUILD_LOG, text);
}

string
wizinfo() 
{
    return ("If there should be due cause to close down the guild, do so by\n"+
      "typing:  Call here close_guild\n"+
      "This will temporarily prevent mortals from entering. After a\n"+
      "reboot, the guild will be open by default. Please send me some\n"+
      "mail if there is anything that needs to be fixed.\n\n   /Igneous.\n");
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!interactive(ob) || !closed)
	return;

    if (ob->query_wiz_level())
	write("\n\nWARNING!\nYou shouldn't be here. "+
	  "I'm doing some work on the guild.\n");
    else {
	write("The guild is closed. Come back later.\n");
	ob->move("/d/Shire/trickster/join");
    }
}

void
init() 
{
    init_guild_support();
    init_skill_raise();
    ::init();
    add_action("do_improve","improve");
}

int
do_improve(string str)
{
    object player = this_player();

    if(!IS_MEMBER(player))
    {
	write("Hey, you're not a Trickster!\n"+
	  "Get out of here before someone kills you!\n");
	log_guild(ctime(time()) + " " + WRITE_NAME(player) +
	  " tried to train this skill: " + str + ".\n");
	return 1;
    }
}


string
close_guild() 
{
    if (closed) 
    {
	closed = 0;
	return "  **The guild is now open**";
    }
    closed = 1;
    return "  **The guild is now closed**";
}

query_closed() { return closed; }

void
set_up_skills() 
{   
    /* Add skill that can be trained. Do not add all skills, and vary a bit */

    sk_add_train(SS_SNEAK,train_text(SS_SNEAK),0,0,60 );
    sk_add_train(SS_WEP_CLUB,train_text(SS_WEP_CLUB),0,0,50 );
    sk_add_train(SS_PARRY,train_text(SS_PARRY),0,0,30 );
    sk_add_train(SS_AWARENESS,train_text(SS_AWARENESS),0,0,60 );
    sk_add_train(SS_TRADING,train_text(SS_TRADING),0,0,60 );
    sk_add_train(SS_HIDE,train_text(SS_HIDE),0,0,40);
    sk_add_train(SS_FR_TRAP,train_text(SS_FR_TRAP),0,0,30);
    sk_add_train(SS_LOC_SENSE, train_text(SS_LOC_SENSE), 0, 0, 50);
    sk_add_train(SS_LANGUAGE, train_text(SS_LANGUAGE), 0, 0, 50);
    sk_add_train(SS_ALCHEMY, train_text(SS_ALCHEMY), 0, 0, 20);

#ifndef NO_TRICKSTER_SHINKICK
    sk_add_train(SS_SHINKICK,train_text(SS_SHINKICK),"shinkick",75,100,
      SS_DEX,100);
#endif
    sk_add_train(SS_DISGUISE,train_text(SS_DISGUISE),"disguise",70,74,
      SS_LAYMAN,100);
}

string
train_text(int skill) 
{
    string what;

    switch(skill) 
    {
    case SS_SNEAK:
	what = "move while concealed";
	break;
    case SS_WEP_CLUB:
	what = "hit enemies over the head with a club";
	break;
    case SS_HIDE:
	what = "conceal oneself";
	break;
    case SS_TRADING:
	what = "trade with higher profit";
	break;
    case SS_PARRY:
	what = "deflect blows in combat";
	break;
    case SS_AWARENESS:
	what = "be aware of the surroundings";
	break;
    case SS_FR_TRAP:
	what = "find and remove traps";
	break;
    case SS_LOC_SENSE:
	what = "know your surroundings";
	break;
    case SS_LANGUAGE:
	what = "understand what others are saying behind your back";
	break;
    case SS_ALCHEMY:
	what = "produce mischievous potions";
	break;
    case SS_SHINKICK:
	what = "shinkick someone really hard";
	break;
    case SS_DISGUISE:
	what = "hide ones true identity from others";
	break;
    }
    return what;
}
