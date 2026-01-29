/*
 * File         : /d/Genesis/new/start/goblin/town/training_hall.c
 * Creator      : Nite@Genesis
 * Copyright    : John Griffin
 * Date         : October 5, 1999
 * Modifications: 
 * Purpose      : The Kalerus Training Hall
 * Related Files: 
 * Comments     : 
 * TODO         : 
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

object gremulak;

/*
 * Prototypes
 */
void set_up_skills();
void reset_room();

void
create_room()
{
    set_short("You are in the Kalerus Training Hall");

    set_long("You are in the Kalerus Training Hall.\n"+
      "This is where you can go when you wish to advance your " +
      "skills. You can <learn> new skills or <improve> the ones " +
      "you already have. With <list guilds> you can which guilds " +
      "you are a member of.\n\n" +
      "Seven shields hang above a shimmering blue door in the " +
      "south wall.\n"+
      "The exit onto the courtyard is to the east.\n");

    add_item(({"shield","shields" }),
      "These shields symbolize the attributes of human life.\n"+
      "In fact, they represent the essence of life itself. These are the\n"+
      "attributes one has to conquer to achieve wizardhood. As you look at\n"+
      "the shields you instinctively recognize the symbols of,\n"+
      "\n"+
      "     Health     Love and Compassion    Knowledge\n"+
      "     Courage    Strength    Stealth    Power.\n"+
      "\n"+
      "You also notice that the eighth shield, the shield of death,\n"+
      "is missing.\n");

    add_item(({"door","blue door"}),"The shimmering around the door seems to be some kind of\n"+
      "force field. It is most likely a wizard entrance.\n"+
      "");

    add_exit("cavern_c2", "east");
    add_exit("/d/Genesis/wiz/domain", "south", "@@sblock");

    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);
    set_noshow_obvious(1);

    create_skill_raise();
    set_up_skills();

    reset_room();
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

    me = "defend yourself"; ot = "use defence skill";
    sk_add_train(SS_DEFENCE,  ({ me, ot }),     0, 0, 20 );
    me = "fight unarmed"; ot = me;
    sk_add_train(SS_UNARM_COMBAT,  ({ me, ot }),     0, 0, 30 );
    me = "use a sword"; ot = me;
    sk_add_train(SS_WEP_SWORD,  ({ me, ot }),     0, 0, 30 );
    me = "use a knife"; ot = me;
    sk_add_train(SS_WEP_KNIFE,  ({ me, ot }),     0, 0, 30 );
    me = "use a club"; ot = me;
    sk_add_train(SS_WEP_CLUB,   ({ me, ot }),       0, 0, 30 );
    me = "trade and make deals"; ot = me;
    sk_add_train(SS_TRADING,	({ me, ot }),       0, 0, 30 );
    me = "appraise the quality of different objects"; ot = me;
    sk_add_train(SS_APPR_OBJ,	({ me, ot }),      0, 0, 30 );
    me = "appraise the value of different objects"; ot = me;
    sk_add_train(SS_APPR_VAL,	({ me, ot }), 0, 0, 30 );
    me = "swim"; ot = me;
    sk_add_train(SS_SWIM,  ({ me, ot }), 0, 0, 30 );
    me = "be aware of your surroundings"; ot = "his awareness";
    sk_add_train(SS_AWARENESS, ({ me, ot }),     0, 0, 30 );
    me = "find and identify herbs"; ot = me;
    sk_add_train(SS_HERBALISM, ({ me, ot }),     0, 0, 20 );
    me = "hunt wild game"; ot = me;
    sk_add_train(SS_HUNTING,	({ me, ot }), 0, 0, 30 );
}

void
reset_room()
{
    seteuid(getuid());

    if (!gremulak || !present(gremulak, this_object())) {
	gremulak = clone_object(NPC_DIR + "gremulak");
	gremulak->move_living("east", this_object());
    }
}

void
init()
{
    ::init();

    init_skill_raise();
    add_action(gs_list    , "list");
}
