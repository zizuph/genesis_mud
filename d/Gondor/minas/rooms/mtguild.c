/*   
 *   Minas Tirith Adventurers Guild - modified by Elessar, from:
 *   adv_guild.c    Styles   Wed Jan 22 1992
 *
 *   NOTE.
 *         The player can't advance more than one level at the time.
 *         This is intentional and not a bug. The players should
 *         experience the effort of gaining each level. Thus they
 *         will recieve each new rank that comes along with the level.
 *
 *         If the guild is closed you can toggle this by doing,
 *         > Call here close_guild
 *         This is a quick way to close/open it if needed
 *
 *         /Styles.
 *
 * Revision history:
 *  - Mercade, 11 October 1993, Evil players cannot train here.
 *  - Olorin, 5 February 1997: Updated skills according to new
 *                             adventurers' guild skill levels
 *                             according to 'man skills'.
 +  - Gorboth, 27-Oct-1997: Changed the room description to reflect
 *                          mudlib support for <list guilds>.
 */
#pragma strict_types

inherit "/d/Gondor/std/room.c";
inherit "/lib/guild_support.c";
inherit "/lib/skill_raise.c";
inherit "/d/Gondor/minas/lib/minas_fof.c";
inherit "/d/Shire/lib/training";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

/* 1 = closed,   0 = open.  */
#define CLOSED          0
#define HIM(x)		(x)->query_objective()

/*
 *	Prototypes:
 */
public  int    wiz_block();
public  void   tour_done(object player);
private void   set_up_skills();

/*
 *	Global variables:
 */
static int     Closed = CLOSED;

public void
create_gondor()
{
    set_short("Minas Tirith Adventurers' Guild");
    set_long(BSN("This is the adventurers training hall in Minas Tirith. " +
	"By the north wall is a large tray from which smoke is rising, " +
	"filling the hall with the smell of incense. By this tray you " +
	"may <meditate> and redefine your personal priorities. You may " +
	"also <learn> new skills, <improve> the skills you already have, " +
	"or <list guilds> to gain information about your affiliations. " +
	"On the wall behind the smoking tray you see a painting " +
	"of the White Tree. There is a set of stairs leading up, and a " +
	"guard stands by them. The exit to the street is south."));

    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(ROOM_I_INSIDE, 1);

    add_exit("/d/Gondor/workroom", "up", wiz_block);
    add_exit(MINAS_DIR + "s2crc2", "south", 0, 0);

    create_guild_support();
    create_skill_raise();
    set_up_skills();

    add_item("tray", BSN(
	"The tray is filled with burning incense, spreading a special " +
	"smell in the hall. By the tray, you may <meditate> to assess " +
	"your growth and to redefine your personal priorities."));
    add_item("stairs",
      "The stairs probably lead up to the guild-room of the leaders of Gondor.\n");
    add_item("guard", BSN("This is one of the members of the " +
	"cityguard. He is posted here to keep trespassers away from " +
	"the private rooms of the leaders."));
    add_item(({"painting","white tree","tree"}), BSN(
	"This is a painting of the White Tree of Gondor, " +
	"standing in the Citadel of Minas Anor, where Isildur planted it " +
	"in memory of his brother Anarion, that fell during the War of " +
	"the Last Alliance against Sauron at the end of the Second Age. " +
	"The White Tree was grown from a sapling of the White Tree " +
	"that Isildur had planted in Minas Ithil, where it was burned by Sauron " +
	"in the sack of that city. This sapling Isildur had rescued from the Fall " +
	"of Numenor, and it came from a fruit of Nimloth the Fair, scion of " +
	"Celeborn on Eressea, scion of Galathilion, High Tree of the Elves, that " +
	"blossoms in Tirion upon Tuna in Eldamar in Aman. Galathilion was made " +
	"by Yavanna Kementari into a lesser image of Telperion the White, " +
	"Eldest of Trees, as a gift to the Eldar in Tirion."));
}

public int
wiz_block()
{
    if (TP->query_wiz_level()) 
    {
	write ("\nYou sense the magic at work all around you as you walk"+
	  " up the steps.\n"+
	  "The guard bows before you, letting you pass.\n\n");
	return 0;
    }
    write("A strong guard prevents you from going up the stairs.\n"+
      "The guard says: Only Royals and Wizards may go up there.\n");
    return 1;
}

string
wizinfo()
{
    return ("If there should be due cause to close down the guild, do so by\n"+
      "typing:  Call here close_guild\n"+
      "This will temporarily prevent mortals from entering. After a\n"+
      "reboot, the guild will be open by default. Please send me some\n"+
      "mail if there is anything that needs to be fixed.\n\n   Olorin.\n");
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
	ob->move_living("south", MINAS_DIR + "s2crc2");
    }
}

private void
test_tour(object player)
{
    object note;

    if (!objectp(note = present("Minas_Tirith_Tour_Note", player)))
	return;

    if (note->query_tour_no() != 2) 
	return;
    note->set_tour_done();
    set_alarm(5.0, 0.0, &tour_done(player));
}

public void
init()
{
    test_tour(TP);
    add_action(gs_meditate, "meditate");
    add_action(gs_list, "list");
    init_skill_raise();
    ::init();
}

public void
tour_done(object player)
{
    tell_object(player,"This is the place that the Master of Advice told you to find.\n"+
      "You can now return to him.\n");
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

    string  me,
    ot;

    /*
       me = "use a knife";
       sk_add_train(SS_WEP_KNIFE,  ({ me, me }),        0,0,30 );
       me = "use a polearm";
       sk_add_train(SS_WEP_POLEARM,({ me, me }),        0,0,24 );
     */
    me = "use a sword";
    sk_add_train(SS_WEP_SWORD,     ({ me, me, }),        0, 0, 30);
    me = "fight unarmed";
    sk_add_train(SS_UNARM_COMBAT,  ({ me, me, }),        0, 0, 30);
    me = "defend yourself in combat";	
    ot = "defend " + HIM(TP) + "self in combat"; 
    sk_add_train(SS_DEFENCE,       ({ me, ot, }),        0, 0, 20);
    me = "understand and use magic";
    sk_add_train(SS_SPELLCRAFT,    ({ me, me, }),        0, 0, 20);
    me = "recognize herbs and plants";
    sk_add_train(SS_HERBALISM,     ({ me, me, }),        0, 0, 20);
    me = "mix potions from herbs and liquids";
    sk_add_train(SS_ALCHEMY,       ({ me, me, }),        0, 0, 20);
    me = "use magic based on the element life";
    sk_add_train(SS_ELEMENT_LIFE,  ({ me, me, }),        0, 0, 20);
    me = "use magic based on the element water";
    sk_add_train(SS_ELEMENT_WATER, ({ me, me, }),        0, 0, 20);
    me = "use magic based on the element earth";
    sk_add_train(SS_ELEMENT_EARTH, ({ me, me, }),        0, 0, 20);
    me = "speak and understand languages";
    sk_add_train(SS_LANGUAGE,      ({ me, me, }),        0, 0, 30);
    me = "appraise the quality of objects";
    sk_add_train(SS_APPR_OBJ,      ({ me, me, }),        0, 0, 30);
    me = "appraise the value of objects";
    sk_add_train(SS_APPR_VAL,      ({ me, me, }),        0, 0, 30);
    /*
       me = "swim";
sk_add_train(SS_SWIM,       ({ me, me }),        0,0,30 );
       me = "hide and conceal";
       sk_add_train(SS_HIDE,       ({ me, me }),        0,0,20 );
     */
    me = "be aware of surroundings";
    sk_add_train(SS_AWARENESS,     ({ me, me, }),        0, 0, 30);
    me = "trade and make deals";
    sk_add_train(SS_TRADING,       ({ me, me, }),        0, 0, 30);
}


void
gs_hook_start_meditate()
{
    write("Slowly you sit down by the smoking tray of incense, and\n"+
      "close your eyes. As the trance-inducing incense reaches into\n"+
      "your mind, a feeling of great ease and self control falls upon you.\n"+
      "You block off your senses and concentrate solely upon your\n"+
      "own mind. You find yourself able to <estimate> your different\n"+
      "preferences and <set> them at your own desire.\n"+
      "Just <rise> when you are done meditating.\n");
}

void
gs_hook_rise()
{
    write("As if ascending from a great depth, you rise to the surface\n"+
      "of your consciousness. You exhale and feel very relaxed as\n"+
      "you get up and walk away from the tray.\n");
}

static int
sk_improve(string str)
{
    if (query_friend_or_foe(TP) < 0)
    {
	write("The guard says: You are an evil creature. Leave or get slain!\n" +
	  "The guard kicks you out.\n");
	say("The guard kicks " + QTNAME(TP) + " out.\n");
	TP->command("$s");
	return 1;
    }

    return ::sk_improve(str);
}
