/*
 * Creator: Shadowlynx
 * Date   : December 4/99
 * File   : train_wep.c
 * File   : /d/Genesis/start/human/sparkle/town/train_wep.c
 * Desc   : The weapon training guild in new Sparkle.
 * Purpose: To train specific weapon skills.
 * Updated: 
 * By Whom: 
 */

#pragma save_binary
#pragma strict_types

inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit "/std/room";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>

#include "../defs.h"

/*
 * Prototypes
 */
void set_up_skills();

void
create_room()
{
set_short("Weapon Training Center");
    set_long("\n"+
             "This is the adventurers guild of Sparkle.\n"+
             "The center of the hall is occupied by a large carpet where you may sit\n"+
             "down and relax. The walls are covered with trophies brought back to the\n"+
             "guild by bold adventurers. This is where you have to go when you wish to\n"+
             "advance your skills and attributes. You may choose to <meditate> and \n"+
             "redefine your personal priorities. You can also <learn> new skills or\n"+
             "<improve> the ones you already have. With <list guilds> you can find out\n" +
             "information about the guilds you are a member of.\n" +
             "\n"+
             "Seven shields hang above a shimmering blue door in the south wall.\n"+
             "The exit onto the street is to the north.\n"+
             "");

    add_item(({"door","blue way" }),"The shimmering around the door seems to be some kind of\n"+
    "force field. It is most likely a wizard entrance.\n"+
    "");
    add_item(({"carpet" }),"It has the symbol of courage woven into the thick soft fabric.\n"+
    "People tend to sit down and meditate on this carpet.\n"+
    "");
    add_item(({"shield","shields" }),"\n"+
    "These shields symbolize the attributes of human life.\n"+
    "In fact, they represent the essence of life itself. These are the\n"+
    "attributes one has to conquer to achieve wizardhood. As you look at\n"+
    "the shields you instinctively recognize the symbols of,\n"+
    "\n"+
    "     Health     Love and compassion    Knowledge\n"+
    "     Courage    Strength    Stealth    Power.\n"+
    "\n"+
    "You also notice that the eighth shield, the shield of death,\n"+
    "is missing.\n"+
    "\n"+
    "");
    add_item(({"trophy","trophys" }),"The trophys include many different objects. It is quite clear\n"+
    "though that none of them could have been easy to obtain.\n"+
    "");
    add_item(({"symbol" }),"The symbol on the carpet is the symbol of courage. There can be no\n"+
    "true adventurer without a courageous heart. Regardless of race or\n"+
    "gender, age or ideas, this is what binds them all together.\n"+
    "");
    add_item(({"room" }),"");

    add_exit(TOWN_DIR + "road3","north");
    add_exit("/d/Genesis/wiz/domain", "south", "@@sblock");

    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    set_noshow_obvious(1);

    create_skill_raise();
    set_up_skills();
}

nomask void
make_wiz()
{
    "/secure/master"->create_wizard(TI->query_real_name());
    TI->update_hooks();
}

nomask int
sblock()
{
    object ob;

    if (TP->query_wiz_level() && !TP->query_prop("walk_backwards"))
    {
	write ("\nYou sense the magic at work all around you as you step"+
               "through the door.\n\n");
	return 0;
    }
    if (!TP->query_wiz_level() && TP->query_prop("walk_backwards") &&
	(ob = present("dust of contrariness", TP)) &&
	ob->query_rubbed() && (TP->query_average_stat() >= 100))
    {
	/* Promote the player to apprentice and tell everyone about
           the happy event */
	ob->remove_object(); /* get rid of contrariness */
	TP->move_living("south", "/d/Genesis/wiz/volcano_centre");
	write("Welcome to wizardhood.\n");
	map(users(), "wtell", this_object());
	make_wiz();
	
	TP->command("save");
	return 1;
    }
    write("A strong force field prevents you from going that way.\n");
    return 1;
}

void
wtell(object ob)
{
    if (ob != TP)
	ob->catch_msg("There is a flash of pure magic, and suddenly "+
		      "you realise that\n"+ QNAME(TP) +" has been accepted "+
		      "in to the ranks of wizards.\n");
}

void
leave_inv(object ob, mixed to)
{
    ::leave_inv(ob, to);
    gs_leave_inv(ob, to);
}

void
set_up_skills()
{
    string me, ot;

    me = "fight unarmed"; ot = me;
    sk_add_train(SS_UNARM_COMBAT,  ({ me, ot }),     0, 0, 30 );
    me = "defend yourself"; ot = "use defence skill";
    sk_add_train(SS_DEFENCE,  ({ me, ot }),     0, 0, 20 );
    me = "use a sword"; ot = me;
    sk_add_train(SS_WEP_SWORD,  ({ me, ot }),     0, 0, 25 );
    me = "use a knife"; ot = me;
    sk_add_train(SS_WEP_KNIFE,  ({ me, ot }),     0, 0, 30 );
    me = "use a club"; ot = me;
    sk_add_train(SS_WEP_CLUB,   ({ me, ot }),	 0, 0, 25 );
    me = "use spellcraft"; ot = me;
    sk_add_train(SS_SPELLCRAFT, ({ me, ot }),    0, 0, 20 );
    me = "appraise the quality of different objects"; ot = me;
    sk_add_train(SS_APPR_OBJ,	({ me, ot }),      0, 0, 30 );
    me = "appraise the value of different objects"; ot = me;
    sk_add_train(SS_APPR_VAL,	({ me, ot }), 0, 0, 30 );
    me = "swim"; ot = me;
    sk_add_train(SS_SWIM,	({ me, ot }), 0, 0, 50 );
    me = "climb"; ot = me;
    sk_add_train(SS_CLIMB,	({ me, ot }), 0, 0, 40 );
    me = "hunt wild game"; ot = me;
    sk_add_train(SS_HUNTING,	({ me, ot }), 0, 0, 30 );
    me = "be aware of your surroundings"; ot = "his awareness";
    sk_add_train(SS_AWARENESS, ({ me, ot }),     0, 0, 40 );
    me = "trade and make deals"; ot = me;
    sk_add_train(SS_TRADING,	({ me, ot }),       0, 0, 30 );
}

static int
walk(string str)
{
    notify_fail("How or where do you want to walk?\n");
    if (!str)
	return 0;
    
    if (str == "backwards")
    {
	TP->add_prop("walk_backwards", 1);
	write("You are now walking backwards.\n");
	say(QCTNAME(TP) + " turns around and starts walking backwards.\n");
	return 1;
    }

    if (str == "forwards")
    {
	TP->add_prop("walk_backwards", 0);
	write("You are now walking forwards.\n");
	say(QCTNAME(TP) + " turns around and starts walking forwards.\n");
	return 1;
    }

    if (parse_command(str, this_object(), "'backwards' 'through' [the] 'portal' / 'curtain' / 'curtains'"))
    {
	TP->add_prop("walk_backwards", 1);
	write("You walk back first towards the portal.\n");
	say(QCTNAME(TP) + " walks back first towards the portal.\n");
	return !sblock();
    }
    return 0;
}

void
init()
{
    ::init();

    init_skill_raise();
    init_guild_support();

//    add_action(walk, "walk");
//    add_action(walk, "go");
}
