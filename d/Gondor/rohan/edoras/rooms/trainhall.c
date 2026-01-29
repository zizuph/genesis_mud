/*
 *  The Edoras Adventurer's Guild Training Hall
 *
 *  training and meditating added by Olorin, 26-may-1993
 *   those parts copied from Sparkle
 *   adv_guild.c    Styles   Wed Jan 22 1992
 *
 *  Revision History:
 *  - Olorin, 5 February 1997: Updated skills according to new
 *                             adventurers' guild skill levels
 *                             according to 'man skills'.
 *  - Gorboth, 27-Oct-1997: Changed room description to reflect
 *                          mudlib support for <list guilds>.
 *  - Gorboth, 20-Mar-2009: Reactivated the Javelin skill offering. Not sure
 *                          why it was removed in the first place.
 *    Finwe, May 2020       Deactivated javelin skill since it's no longer
 *                          available
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
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

static int     Closed = CLOSED;

/*
 *	Prototypes
 */
static void    set_up_skills();

public void 
create_gondor()
{
    set_short("Training Hall of the Edoras Adventurers' Guild");
    set_long(BSN(
	"This is the training hall of the Edoras Adventurers' Guild."
	+ " A great banner hangs on the west wall, showing a white horse"
	+ " on a green field. In a corner lies a soft carpet where one"
	+ " may <meditate> to determine progress and personal learning"
	+ " preferences. One may also <list guilds> to gain information"
	+ " regarding membership with various organizations. From a chair"
	+ " in another corner, an aged rohirrim sits quietly, tending"
	+ " to his own affairs. If you would like, he may be able to"
	+ " assist in learning new skills, or training those who already"
	+ " have some knowledge to achieve greater ability. A door"
	+ " leads north to the main room of the guild."));

    add_exit(EDORAS_DIR + "rooms/guild", "north", 0);
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(ROOM_I_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK,1);
    add_prop(ROOM_I_INSIDE,1);
    create_guild_support();
    create_skill_raise();
    set_up_skills();
    add_item(({"wall", "banner", "flag"}), BS(
	"The banner on the wall shows a running white horse on a deep green field. " +
	"You recognize it as the banner of Rohan.\n"));
    add_item(({"carpet"}), BS(
	"It is a thick plush carpet. It must be very comfortable to sit down on it. " +
	"You can do that, if you want to <meditate>. Once you are meditating you will " +
	"be able to <estimate> your progress on your path to wizdom, and to <set> " +
	"your personal preferences.\n"));
    add_item(({"trainer", "veteran", "man", "rohirrim"}), BS(
	"He looks old, but somehow you get the impression that he has seen more than " +
	"his share of the world. He might be able to teach you a lot. You can either " +
	"<learn> new skills or you can <improve> those skills in which you already have " +
	"some knowledge.\n"));
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
	ob->move_living("north", EDORAS_DIR + "guild");
    }
}

public void
init()
{
    ::init();
    init_skill_raise();
    init_guild_support();
}

string
close_guild()
{
    Closed = !Closed;

    if (Closed)
	return "  **The guild is now closed**";
    return "  **The guild is now open**";
}

public int query_closed() { return Closed; }

static void
set_up_skills()
{
    string me, ot;
/*
    me = "use a javelin effectively"; ot = me;
    sk_add_train(SS_WEP_JAVELIN,({ me, ot }),  0, 0, 30 );
*/
    me = "use a sword";
    sk_add_train(SS_WEP_SWORD,      ({ me, me, }),  0, 0, 30);
    me = "use an axe";
    sk_add_train(SS_WEP_AXE,        ({ me, me, }),  0, 0, 30);
    me = "use a club";
    sk_add_train(SS_WEP_CLUB,       ({ me, me, }),  0, 0, 30);
    me = "move with grace and speed";
    sk_add_train(SS_ACROBAT,        ({ me, me, }),  0, 0, 20);
    me = "appraise your opponents"; ot = "appraise " + HIS(TP) + " opponents";
    sk_add_train(SS_APPR_MON,       ({ me, ot, }),  0, 0, 30);
    me = "appraise objects";
    sk_add_train(SS_APPR_OBJ,       ({ me, me, }),  0, 0, 30);
    /*
       me = "move stealthily and silently"; ot = me;
       sk_add_train(SS_SNEAK,      ({ me, ot }),  0, 0, 20 );
     */
    me = "climb";
    sk_add_train(SS_CLIMB,          ({ me, me, }),  0, 0, 30);
    me = "handle animals";
    sk_add_train(SS_ANI_HANDL,      ({ me, me, }),  0, 0, 30);
    me = "find the right way in the wilderness";
    sk_add_train(SS_LOC_SENSE,      ({ me, me, }),  0, 0, 30);
    me = "find and follow hidden tracks and paths";
    sk_add_train(SS_TRACKING,       ({ me, me, }),  0, 0, 30);
    me = "hunt";
    sk_add_train(SS_HUNTING,        ({ me, me, }),  0, 0, 30);
    /*
       me = "trade and make deals";   ot = me;
       sk_add_train(SS_TRADING,    ({ me, ot }),  0, 0, 30 );
     */
}

public string
wizinfo()
{
    return (
      "If there should be due cause to close down the guild, do so by\n"+
      "typing:  Call here close_guild\n"+
      "This will temporarily prevent mortals from entering. After a\n"+
      "reboot, the guild will be open by default. Please send me some\n"+
      "mail if there is anything that needs to be fixed.\n\n   Olorin.\n");
}
