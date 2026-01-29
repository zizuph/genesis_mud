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
 *  The Hobbiton Adventurer's Guild - only hobbits can improve here.
 */

#pragma save_binary

inherit "/lib/guild_support";
inherit "/lib/skill_raise";
inherit "/std/room";


#include "defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>

#define NF(str)		notify_fail(str)
#define TO		this_object()
#define NUM		sizeof(query_money_types(-1))
#define BS(xxx) 	break_string(xxx,68)
#define CLOSED		0	/* 1 = closed,   0 = open.  */

int closed;
object meditate, poster;


create_room()
{
    object board, box;

    closed = CLOSED;

    add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
    set_short("Adventurer's guild");
    set_long("@@my_long");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");

    add_exit(STAND_DIR + "h_lane3", "west", 0);
    add_exit("/d/Genesis/start/hobbit/v/common", "common", 0);

    board = clone_object("/std/board");
    board->set_board_name(STAND_DIR + "guild_board");
    board->set_num_notes(17);         /* Number of notes         */
    board->set_anonymous(1);          /* You may write anonymous */
    board->set_silent(0);             /* Make noise when reading */
    board->set_show_lvl(0);           /* Full wizards or higher  */
    board->set_remove_lvl(30);         /* Full wizards or higher  */
    board->set_remove_str("You somehow failed.");
    board->set_use_gedit(0);          /* Don't use that marvellous editor */
    board->move(this_object());

    clone_object(STAND_DIR + "ch_box")->move(this_object());

    create_skill_raise();
    create_guild_support();
    set_up_skills();
    reset_room();
}

reset_room()
{
    if (!poster)
    {
        poster = clone_object("/d/Sparkle/guilds/mercs/obj/merc_poster");
        poster->move(this_object());
    }
}

wizinfo() {
    return ("If there should be due cause to close down the guild, do so by\n"+
      "typing:  Call here close_guild\n"+
      "This will temporarily prevent mortals from entering. After a\n"+
      "reboot, the guild will be open by default. Please send me some\n"+
      "mail if there is anything that needs to be fixed.\n\n   /Styles.\n");
}

my_long() {
    /* Only hobbits can improve here, don't tempt the rest */
    if (this_player()->query_race() != "hobbit")
	return "This room is the local meeting place for adventurers. This is where "
	  + "they leave messages of the places they have visited. Here they also "
	  + "trade information on unknown territories, in the hope to be able to "
	  + "explore them further. "
	  + "Someone has added an exit called 'common' here.\n";

    return "This room is the local meeting place for adventurers. This is where "
      + "they leave messages of the places they have visited. Here they also "
      + "trade information on unknown territories, in the hope to be able to "
      + "explore them further. Here you can improve your skills and if you "
      + "want to change your stat-priorities, you can meditate here. "
      + "Someone has added an exit called 'common' here.\n";
}
enter_inv(ob, from) {
    ::enter_inv(ob, from);

    if (!interactive(ob) || !closed)
	return;

    if (ob->query_wiz_level())
	write("\n\nWARNING!\nYou shouldn't be here. "+
	  "I'm doing some work on the guild.\n");
    else {
	write("The guild is closed. Come back later.\n");
	ob->move("/d/Genesis/start/hobbit/v/h_lane3");
    }
}


init() {
    ::init();
    init_skill_raise();
    init_guild_support();
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
    string me, ot;
    /* Add skill that can be trained. Do not add all skills, and vary a bit */

    me = "fight unarmed";
    sk_add_train(SS_UNARM_COMBAT,  ({ me, me }),     0,0,30 );
    me = "defend yourself"; ot = "use defence skill";
    sk_add_train(SS_DEFENCE,  ({ me, ot }),     0,0,20 );
    me = "use a sword";
    sk_add_train(SS_WEP_SWORD,  ({ me, me }),     0,0,30 );
    me = "use a bow and arrows";
    sk_add_train(SS_WEP_MISSILE,({ me, me }),   0,0,30 );
    me = "use a knife";
    sk_add_train(SS_WEP_KNIFE,    ({ me, me }),       0,0,30 );
    me = "use magic";
    sk_add_train(SS_SPELLCRAFT, ({ me, me }),    0,0,20 );
    me = "appraise monsters";
    sk_add_train(SS_APPR_MON,	({ me, me }),      0,0,30 );
    me = "appraise objects";
    sk_add_train(SS_APPR_OBJ,	({ me, me }),      0,0,30 );
    me = "trade and make deals";
    sk_add_train(SS_TRADING,  ({ me, me }),      0,0,30 );
    me = "find tracks";
    sk_add_train(SS_TRACKING, ({ me, me }),     0,0,30 );
    me = "climb";
    sk_add_train(SS_CLIMB, ({ me, me }),         0,0,30 );
    me = "handle animals";
    sk_add_train(SS_ANI_HANDL,	({ me, me }),     0,0,30 );
    me = "be aware of surroundings";
    sk_add_train(SS_AWARENESS,     ({ me, me }),     0,0,30 );
    me = "be aware of locations";
    sk_add_train(SS_LOC_SENSE,	({ me, me }),     0,0,30 );
}

gs_meditate(str) {
    if (this_player()->query_race() != "hobbit")
	return 0;
    return ::gs_meditate(str);
}

sk_improve(str) {
    if (this_player()->query_race() != "hobbit")
	return 0;
    return ::sk_improve(str);
}
