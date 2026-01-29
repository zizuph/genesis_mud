
/*     The Guild in Tiriath, original code by Styles, modified by Ged    */

/*	   If the guild is closed you can toggle this by doing,
 *	   > Call here close_guild
 *	   This is a quick way to close/open it if needed
 */

inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit "/std/room";


#include "/d/Roke/common/defs.h"
#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/language.h"
#include "/sys/money.h"


#define NUM		sizeof(query_money_types(-1))

#define CLOSED		0	/* 1 = closed,   0 = open.  */

int closed;
object meditate;


create_room() { 
    object board, box;

    closed = CLOSED; 

    set_short("Adventurer's guild");
    set_long("You are in the Adventurer's Guild in Tiriath.\n"+
       "This is a cosy and very nice place to be. There is a nice log-fire\n"+
       "in a corner and you can see nice pictures on the wall.\n"+
       "Here you can leave messages to your fellow adventurers.\n"+
       "It's also possible to improve your skills and if you want to \n"+
       "change your stat-priorities, you can also meditate here.\n");

    add_item("fire","The fire brings heat to the house.\n");

    add_item(({"paintings","pictures"}),"You see the pictures of two mighty"+
	     " wizards. You see that\nthey are the wizards with the name  "+
	     "Teradeth and Valeria, the famous barbarians.\n");

    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(OBJ_I_HAS_FIRE,1);
 
    add_exit("/d/Roke/valeria/cowfield/meadow1", "north", 0);

    board = clone_object("/std/board");
    board->set_board_name("/d/Roke/valeria/board");
    board->set_num_notes(17);         /* Number of notes         */
    board->set_anonymous(1);          /* You may write anonymous */
    board->set_silent(0);             /* Make noise when reading */
    board->set_show_lvl(0);  
    board->set_remove_lvl(30);         /*Lords or higher  */
    board->set_remove_str("You somehow failed.");
    board->set_use_gedit(0);          /* Don't use that marvellous editor */
    board->move(this_object());

    create_guild_support();
    create_skill_raise();
    set_up_skills();
}

wizinfo() {
   return ("If there should be due cause to close down the guild, do so by\n"+
	   "typing:  Call here close_guild\n"+
	   "This will temporarily prevent mortals from entering. After a\n"+
	   "reboot, the guild will be open by default. Please send me some\n"+
	   "mail if there is anything that needs to be fixed.\n\n   /Ged.\n");
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
	ob->move("/d/Roke/common/gont/re/a5");
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

query_closed() { return closed; }

set_up_skills() {

    /* Add skill that can be trained. Do not add all skills, and vary a bit */

    sk_add_train(SS_SPELLCRAFT, train_text(SS_SPELLCRAFT),    0,0,30 );
    sk_add_train(SS_APPR_MON,	train_text(SS_APPR_MON),      0,0,30 );
    sk_add_train(SS_APPR_OBJ,	train_text(SS_APPR_OBJ),      0,0,30 );
    sk_add_train(SS_LANGUAGE,	train_text(SS_LANGUAGE),      0,0,30 );
    sk_add_train(SS_TRACKING,	train_text(SS_TRACKING),      0,0,50 );   
    sk_add_train(SS_HIDE,	train_text(SS_HIDE),          0,0,50 );
    sk_add_train(SS_SNEAK,	train_text(SS_SNEAK),         0,0,50 );
    sk_add_train(SS_AWARENESS,	train_text(SS_AWARENESS),     0,0,50 );
    sk_add_train(SS_LOC_SENSE,	train_text(SS_LOC_SENSE),     0,0,50 );

}

train_text(skill) {
    string what;

    switch(skill) {
	case SS_SPELLCRAFT:
 	    what="use spellcraft";
	    break;
	
	case SS_APPR_MON:
	    what="appraise your opponents";
	    break;
	case SS_APPR_OBJ:
	    what="appraise different objects";
	    break;
	case SS_LANGUAGE:
	    what="understand foreign languages";
	    break;
	case SS_TRACKING:
	    what="tracking";
	    break;

	case SS_HIDE:
	    what="to hide things";
	    break;
	case SS_SNEAK:
	    what="sneaking around";
	    break;
	case SS_AWARENESS:
	    what="be aware of your surroundings";
	    break;
	case SS_LOC_SENSE:
	    what="sense of location";
	    break;

	default:
	    what="do nothing. THIS IS A BUG";
	    break;
    }
    return what;
}
