
/*
 * Written by Quis for the Goblin Start Area 920516
 */
#pragma save_binary

inherit "/std/room";

inherit "/lib/guild_support";
inherit "/lib/skill_raise";

#include "/sys/stdproperties.h"
#include "../goblins.h"

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>

#define NF(str)         notify_fail(str)
#define TO              this_object()
#define TP              this_player()
#define NUM             sizeof(query_money_types(-1))
#define OPEN		0	/* 1 = closed,   0 = open.  */
#define CLOSED          0       /* 1 = closed,   0 = open.  */

void set_up_skills();
string *train_text(int skill);

int closed;


create_room()
{
    ::create_room();
    change_prop(ROOM_I_LIGHT,1);
    change_prop(ROOM_I_INSIDE,1);

    set_short("Training room.");

    set_long(break_string(
	"Here you see many goblin warriors, practicing their skills. " +
	"For a fee, you may <improve> your own skills also.  Perhaps you " + 
	"can <learn> a new skill here as well." +
	"\n\n",70));

    add_exit(GOBLIN_STARTLOC,"northwest");

    closed = OPEN; 
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    set_up_skills();
    add_item(({"goblin","warrior","warriors"}),"They look quite fierce.\n");

}

  string
wizinfo()
{
    return ("If there should be due cause to close down the guild, do so by\n" +
      "typing:  Call here close_guild\n" +
      "This will temporarily prevent mortals from entering. After a\n" +
      "reboot, the guild will be open by default. Please send me some\n" +
      "mail if there is anything that needs to be fixed.\n\n   /Styles.\n"
    );
}

void
init()
{
    ::init();
    init_guild_support();
    init_skill_raise();
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
    sk_add_train(SS_UNARM_COMBAT, "fight unarmed", 0, 0, 30); 
    sk_add_train(SS_DEFENCE, ({ "defend yourself", "use defence skill"}), 
      0, 0, 20); 
    sk_add_train(SS_WEP_POLEARM, train_text(SS_WEP_POLEARM), 0, 0, 30);
    sk_add_train(SS_WEP_KNIFE,   train_text(SS_WEP_KNIFE),   0, 0, 30);
    sk_add_train(SS_APPR_OBJ,    train_text(SS_APPR_OBJ),    0, 0, 30);
    sk_add_train(SS_APPR_VAL,    train_text(SS_APPR_VAL),    0, 0, 30);
    sk_add_train(SS_APPR_MON,    train_text(SS_APPR_MON),    0, 0, 30);
    sk_add_train(SS_CLIMB,       train_text(SS_CLIMB),        0, 0, 30);
    sk_add_train(SS_AWARENESS,   train_text(SS_AWARENESS),    0, 0, 30);
    sk_add_train(SS_ANI_HANDL,   train_text(SS_ANI_HANDL),    0, 0, 30);
    sk_add_train(SS_LOC_SENSE,   train_text(SS_LOC_SENSE),    0, 0, 30);
    sk_add_train(SS_RIDING,   train_text(SS_RIDING),    0, 0, 30);
    sk_add_train(SS_TRACKING,   train_text(SS_TRACKING),    0, 0, 30);
    sk_add_train(SS_HUNTING,   train_text(SS_HUNTING),    0, 0, 30);
}

string *
train_text(int skill)
{
    string what, does, *text;

    switch(skill)
    {
    case SS_WEP_POLEARM:
	what = "use a spear";
	does = what;
	break;

    case SS_WEP_KNIFE:
	what = "use a knife";
	does = what;
	break;

    case SS_APPR_OBJ:
	what = "appraise the quality of different objects";
	does = what;
	break;

    case SS_APPR_VAL:
	what = "appraise the value of different objects";
	does = what;
	break;

    case SS_APPR_MON:
	what = "appraise an enemys prowess";
	does = what;
	break;

    case SS_CLIMB:
	what = "climb walls and mountains";
	does = what;
	break;

    case SS_AWARENESS:
	what = "be aware of your surroundings";
	does = "be aware of "+ TP->query_possessive() +" surroundings";
	break;

    case SS_ANI_HANDL:
	what = "handle worgs";
	does = what;
	break;

    case SS_LOC_SENSE:
	what = "know your location";
	does = what;
	break;

    case SS_RIDING:
	what = "ride a beast";
	does = what;
	break;

    case SS_TRACKING:
	what = "track a creature";
	does = what;
	break;

    case SS_HUNTING:
	what = "hunt an enemy";
	does = what;
	break;

    default:
	what = "do nothing. THIS IS A BUG";
	does = "meditate";
	break;
    }
    return ({what, does});
}

