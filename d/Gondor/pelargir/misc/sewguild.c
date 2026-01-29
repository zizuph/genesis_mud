/*   
 *   Minas Tirith Adventurers Guild - modified by Elessar, from:
 *   adv_guild.c    Styles   Wed Jan 22 1992
 *
 *   NOTE.
 *         If the guild is closed you can toggle this by doing,
 *         > Call here close_guild
 *         This is a quick way to close/open it if needed
 *
 *         /Styles.
 *
 *  - Olorin, 5 February 1997: Updated skills according to new
 *                             adventurers' guild skill levels
 *                             according to 'man skills'.
 * - Finwe, March 2019: Added sign so players know what skills 
 *                      can be trained here, and added location sense 
 *                      back at adv guild levels.
 */
#pragma strict_types

inherit "/d/Gondor/pelargir/sewers/sewer.c";
inherit "/lib/guild_support.c";
inherit "/lib/skill_raise.c";
inherit "/d/Shire/lib/training";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

/* 1 = closed,   0 = open.  */
#define CLOSED          0
#define HIS(x)		(x)->query_possessive()

/* 
 *	Prototypes:
 */
private void    set_up_skills();

/*
 *	Global variables:
 */
static  int     Closed = CLOSED;

public void
create_sewer()
{
    set_short("Pelargir Adventurers' Guild");
    set_extra_long("Hidden here in the sewers seems to be some sort of "
      + "training room for the denizens below Pelargir. The only real "
      + "furniture here is a practice dummy and a small table "
      + "with a book chained to it, though "
      + "there is a torch permanently ensconced in the wall.");
    add_item(({"table", "small table"}),
        "The table is made of wood and looks like it has been here for " +
        "many years. An open book sits on it.\n");
    add_item(({"book" }), 
        "This book looks worn and tattered. " +
        "It sits open on the table and contains instructions on what can " +
        "be learned here. You might <improve> your knowledge in any of " +
        "these areas or <learn> something entirely new to you.\n");
    add_item(({"practice dummy","dummy"}),
        "The dummy "+
      "is really a large wooden carving of a man which some people "+
      "choose to come here and practice their knife skills "+
      "on. It seems that someone has painted the uniform of "+
      "a guard of Pelargir on it.\n");
    add_item("torch",
        "The torch here is a permanent "+
      "fixture, and has been permanently attached to the wall.\n");

    add_item("book", "It lays open on the table and is worn and tattered. " +
        "Still, it looks like it could be read.\n");
    add_cmd_item("book", "read", "@@read_book@@");

    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(ROOM_I_LIGHT, 1);
    add_exit(PELAR_DIR + "sewers/dock", "southeast",0);
    create_guild_support();
    create_skill_raise();
    set_up_skills();
}

string
wizinfo()
{
   return ("If there should be due cause to close down the guild, do so by\n"+
           "typing:  Call here close_guild\n"+
           "This will temporarily prevent mortals from entering. After a\n"+
           "reboot, the guild will be open by default. Please send me some\n"+
           "mail if there is anything that needs to be fixed.\n\n   /Elessar.\n");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob) || !interactive(ob) || !Closed)
        return;

    if (ob->query_wiz_level())
        write("\n\nWARNING!\nYou shouldn't be here. "+
              "I'm doing some work on the guild.\n");
    else 
    {
        write("The guild is closed. Come back later.\n");
        ob->move_living("southeast", PELAR_DIR + "sewers/dock1");
    }
}

public void
init()
{
    init_guild_support();
    init_skill_raise();

    ::init();
}

public string
close_guild()
{
    Closed = !Closed;

    if (Closed)
	    return "  **The guild is now closed**";
    return "  **The guild is now open**";
}

public int query_closed() { return Closed; }

private void
set_up_skills() 
{
    string me, ot;

    me = "use a knife";
    sk_add_train(SS_WEP_KNIFE,    ({ me, me, }),  0, 0, 30);
    me = "find the right way in the wilderness";
    sk_add_train(SS_LOC_SENSE,({ me, me }),       0,0,30 );
    me = "fight in darkness";
    sk_add_train(SS_BLIND_COMBAT, ({ me, me, }),  0, 0, 20);
    me = "pick locks";
    sk_add_train(SS_OPEN_LOCK,    ({ me, me, }),  0, 0, 20);
    me = "pick pockets";
    sk_add_train(SS_PICK_POCKET,  ({ me, me, }),  0, 0, 20);
    me = "find and remove traps";
    sk_add_train(SS_FR_TRAP,      ({ me, me, }),  0, 0, 20);
    me = "hide and conceal";
    sk_add_train(SS_HIDE,         ({ me, me, }),  0, 0, 20);
    me = "move without being seen";
    sk_add_train(SS_SNEAK,        ({ me, me, }),  0, 0, 20);
    me = "appraise your opponents"; ot = "appraise " + HIS(TP) + " opponents";
    sk_add_train(SS_APPR_MON,     ({ me, ot, }),  0, 0, 30);
}


void
gs_hook_start_meditate()
{
    write("Slowly you sit down on the planks in the middle of the sewer "
      + "and close your eyes. Inspite of the unpleasant smells down here "
      + "in the sewers, a feeling of great ease and self control falls "
      + "upon you. You block off your senses and concentrate solely upon "
      + "your own mind. You find yourself able to <estimate> your "
      + "different preferences and <set> them at your own desire." 
      + "Just <rise> when you are done meditating.\n");
}

void
gs_hook_rise()
{
    write("As if ascending from a great depth, you rise to the surface "
      + "of your consciousness. You exhale and feel very relaxed as you "
      + "get up.");
}

string read_book()
{
    return "\n" + 
    "\t+------------------------------------------------------+\n" +
    "\t||                                                     |\n" +
    "\t||   but, the Guards have been trying to get rid of    |\n" +
    "\t||   us, but they will fail. We shall rise up again    |\n" +
    "\t||   and remove the despots who rule Pelargir. They    |\n" +
    "\t||   discovered us down here and are trying to destroy |\n" +
    "\t||   They shall not suceed! If you want to join us,    |\n" +
    "\t||   these are the skills we offer. Power to the       |\n" +
    "\t||   People!                                           |\n" +
    "\t||                                                     |\n" +
    "\t||       Appraise Enemies . . . . Superior Layman      |\n" +
    "\t||       Blind Combat . . . . . . Superior Layman      |\n" +
    "\t||       Find & Remove Traps. . . Superior Amateur     |\n" +
    "\t||       Hide . . . . . . . . . . Superior Amateur     |\n" +
    "\t||       Knife. . . . . . . . . . Superior Layman      |\n" +
    "\t||       Location Sense . . . . . Superior Layman      |\n" +
    "\t||       Open Locks . . . . . . . Superior Amateur     |\n" +
    "\t||       Pick Pockets . . . . . . Superior Amateur     |\n" +
    "\t||       Sneak. . . . . . . . . . Superior Amateur     |\n" +
    "\t||                                                     |\n" +
    "\t+------------------------------------------------------+\n\n";
}
