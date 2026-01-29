/*   adv_guild.c    Styles   Wed Jan 22 1992
 *
 *   NOTE.
 *	   The player can't advance more than one level at the time.
 *         This is intentional and not a bug. The players should
 *	   experience the effort of gaining each level. Thus they
 *         will receive each new rank that comes along with the level.
 *
 *	   If the guild is closed you can toggle this by doing,
 *	   > Call here close_guild
 *	   This is a quick way to close/open it if needed
 *
 *	   /Styles.
 */

/*
 *  Bree Adventurer's Guild - all players can improve here.
 */

inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit "/d/Shire/std/room";


#include "/d/Shire/common/defs.h"
#include "defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"
#include <std.h>

#define NUM		sizeof(query_money_types(-1))
#define CLOSED		0	/* 1 = closed,   0 = open.  */

int closed;
object meditate;

void set_up_skills();

public void
create_room() 
{ 
    object board, box;

    closed = CLOSED; 

    set_short("Adventurer's guild");
    set_long("@@my_long");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");

    add_exit(BREE_DIR + "middle","east",0,1);
    add_exit(BREE_DIR + "common","common",0,1);

    board = clone_object(BREE_DIR + "obj/bree_board");
    board->move(this_object());

    clone_object(BREE_DIR + "ch_box")->move(this_object());

    create_skill_raise();
    create_guild_support();
    set_up_skills();
}

string
wizinfo() 
{
    return ("If there should be due cause to close down the guild, do so by\n"+
      "typing:  Call here close_guild\n"+
      "This will temporarily prevent mortals from entering. After a\n"+
      "reboot, the guild will be open by default. Please send me some\n"+
      "mail if there is anything that needs to be fixed.\n\nJaypeg\n"+
      "It is also possible for mortal members of the Rangers of the North\n"+
      "to remove notes and post notes using their nicknames here.\n"+
      "Questions may be directed at Elessar.\n");
}

string
my_long() 
{
    return break_string(
      "This room is the local meeting place for adventurers. This is where "
      + "they leave messages of the places they have visited. Here they also "
      + "trade information on unknown territories, in the hope to be able to "
      + "explore them further. Here you can improve your skills and if you "
      + "want to change your stat-priorities, you can meditate here. "
      + "Someone has added an exit called 'common' here.\n",70);
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
	ob->move(BREE_DIR + "middle");
    }
}

void
init() 
{
    ::init();
    init_skill_raise();
    init_guild_support();
}

string
close_guild() 
{
    if (closed) {
	closed = 0;
	return "  **The guild is now open**";
    }
    closed = 1;
    return "  **The guild is now closed**";
}

int
query_closed() { return closed; }

void
set_up_skills() {
    string me;
    /* Add skill that can be trained. Do not add all skills, and vary a bit */

    me = "appraise the value of things";
    sk_add_train(SS_APPR_VAL,({ me, me }),   0,0,30 );
    me = "barter more effectively";
    sk_add_train(SS_TRADING,({ me, me }),   0,0,30 );
    me = "use an axe";
    sk_add_train(SS_WEP_AXE,    ({ me, me }),       0,0,27 );
    me = "use magic";
    sk_add_train(SS_SPELLCRAFT, ({ me, me }),    0,0,10 );
    me = "appraise objects";
    sk_add_train(SS_APPR_OBJ,	({ me, me }),      0,0,30 );
    me = "hide inside rooms";
    sk_add_train(SS_HIDE,	({ me, me }),      0,0,20 );
    me = "handle animals";
    sk_add_train(SS_ANI_HANDL,	({ me, me }),     0,0,30 );
    me = "be aware of surroundings";
    sk_add_train(SS_AWARENESS,     ({ me, me }),     0,0,30 );
    me = "be aware of locations";
    sk_add_train(SS_LOC_SENSE,	({ me, me }),     0,0,30 );
    me = "pick pockets";
    sk_add_train(SS_PICK_POCKET,({ me, me }),     0,0,10 );
    me = "defend oneself";
    sk_add_train(SS_DEFENCE,({me,me}),0,0,15);
    me = "find and remove traps";
    sk_add_train(SS_FR_TRAP,({me,me}),0,0,20);
    me = "do backflips and other acrobatic feats";
    sk_add_train(SS_ACROBAT,({me,me}),0,0,14);
}

int
gs_meditate(string str) 
{
    return ::gs_meditate(str);
}

int
sk_improve(string str) 
{
    return ::sk_improve(str);
}
