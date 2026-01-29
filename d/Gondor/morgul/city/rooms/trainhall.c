/*
 *  The Minas Morgul Adventurers' Training Hall
 *
 *  copied mainly from the Edoras trainhall, by Olorin, 31-jul-1993
 *   those parts copied from Sparkle 
 *   adv_guild.c    Styles   Wed Jan 22 1992
 *
 *  Revision History:
 *      Gorboth, 27-Oct-1997, changed description to reflect the
 *               mudlib support for <list guilds>.
 *
 *      Nerull, 21-aug-2016, added 10 in form conjuration in
 *               order to make it compatible with the new
 *               tuvale system.
 */
#pragma strict_types

inherit "/d/Gondor/morgul/city/morgul.c";
inherit "/lib/guild_support";
inherit "/lib/skill_raise";
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
#define HIM(x)		(x)->query_objective()

/* 
 *	Prototypes 
 */
private void set_up_skills();

/*
 *	Global variables:
 */
static int     Closed = CLOSED;
static object  Trainer;

public void
create_morgul_room()
{
    set_extraline(
      "This room looks a little less filthy than others in this city. "
    + "In a corner an old, thick carpet lies. There you can meditate "
    + "and estimate your progress or redefine your personal preferences. "
    + "It is possible to <list guilds>, and "
    + "if one of the uruk-hai is here, you can also learn new skills "
    + "or improve those in which you already have some practice. " 
    + "You can leave to the door leading north.");
    set_road(9);
    set_short_desc("in the training hall of Minas Morgul");
    add_exit(MORGUL_DIR + "city/rooms/boardroom", "north", check_exit);
    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(ROOM_I_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK,1);
    add_prop(ROOM_I_INSIDE,1);
    create_guild_support();
    create_skill_raise();
    set_up_skills();
    add_item(({"rug","carpet"}), BSN(
    "It is a rather old, thick carpet. It looks like it has seen some " +
    "heavy use and was maltreated by booted feet, but it is still probably " +
    "quite comfortable to sit down on it. " +
    "You can do that, if you want to <meditate>. Once you are meditating you will " +
    "be able to <estimate> your progress on your path to wizdom, and to <set> " +
    "your personal preferences. "));

    reset_room();
}

private void
make_trainer()
{
    if (objectp(Trainer))
        return;

    Trainer = clone_object(MORGUL_DIR + "npc/ithil_uruk");
    Trainer->set_long(Trainer->query_long() + BSN( 
      "He looks like he is the veteran of many wars. " +
      "He now earns his bread by training others in the use " +
      "of weapons and some other skills. "));
    Trainer->add_name("_train_uruk");
    Trainer->set_skill(SS_WEP_SWORD,90);
    Trainer->set_skill(SS_WEP_POLEARM,90);
    Trainer->set_skill(SS_WEP_AXE,90);
    Trainer->set_skill(SS_WEP_KNIFE,90);
    Trainer->set_skill(SS_WEP_CLUB,90);
    Trainer->set_skill(SS_PARRY,75);
    Trainer->set_skill(SS_DEFENCE,75);
    Trainer->set_skill(SS_SPELLCRAFT,55);
    Trainer->set_skill(SS_APPR_MON,90);
    Trainer->set_skill(SS_CLIMB,90);
    Trainer->set_skill(SS_LOC_SENSE,90);
    Trainer->set_skill(SS_TRACKING,90);
    Trainer->set_skill(SS_AWARENESS,90);
    Trainer->arm_me();
    Trainer->move_living("down", TO);
}

public void
reset_room()
{
    make_trainer();
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
	ob->move_living("north", MORGUL_DIR+"city/rooms/boardroom");
    }
}

public int
try_skills(string str)
{
    object uruk;

    TP->reveal_me(1);
    if (!objectp(uruk = present("_train_uruk",TO)))
    {
	write("How do you want to do this? There is no one here to train you!\n");
	return 1;
    }
    if (!CAN_SEE(uruk, TP))
    {
	write("The " + uruk->query_nonmet_name() + " cannot see you!\n");
	return 1;
    }
    return 0;
}

public void
init()
{
    ::init();

    init_skill_raise();
    init_guild_support();
    add_action(try_skills, "learn");
    add_action(try_skills, "improve");
}

public string 
close_guild()
{
    Closed = !Closed;
    if (Closed)
	return "  **The guild is now closed**";
    return "  **The guild is now open**";
}

public int    query_closed() { return Closed; }

private void 
set_up_skills()
{
    string me, ot;

    me = "use a sword"; ot = me;
    sk_add_train(SS_WEP_SWORD,     ({ me, ot }),  0, 0, 30 );
    /*
       me = "use a polearm effectively"; ot = me;
       sk_add_train(SS_WEP_POLEARM,({ me, ot }),  0, 0, 30 );
       me = "use a axe effectively";   ot = me;
       sk_add_train(SS_WEP_AXE,    ({ me, ot }),  0, 0, 30 );
       me = "use a knife effectively"; ot = me;
       sk_add_train(SS_WEP_KNIFE,  ({ me, ot }),  0, 0, 30 );
     */
    me = "use a club";  ot = me;
    sk_add_train(SS_WEP_CLUB,      ({ me, ot }),  0, 0, 30 );
    me = "fight unarmed"; ot = me;
    sk_add_train(SS_UNARM_COMBAT,  ({ me, ot }),  0, 0, 30 );
    me = "defend yourself in combat";  
    ot = "defend in combat";
    sk_add_train(SS_DEFENCE,       ({ me, ot }),  0, 0, 20 );
    me = "understand magic";        ot = me;
    sk_add_train(SS_SPELLCRAFT,    ({ me, ot }),  0, 0, 20 );
    me = "find and recognize herbs and plants";
    sk_add_train(SS_HERBALISM,     ({ me, ot }),  0, 0, 20 );
    me = "mix potions from liquids and herbs";
    sk_add_train(SS_ALCHEMY,       ({ me, ot }),  0, 0, 20 );
    me = "use magic based on the element fire"; ot = me;
    sk_add_train(SS_ELEMENT_FIRE,  ({ me, ot }),  0, 0, 20 );
    me = "use magic based on the element air"; ot = me;
    sk_add_train(SS_ELEMENT_AIR,   ({ me, ot }),  0, 0, 20 );
    me = "use magic based on the element death"; ot = me;
    sk_add_train(SS_ELEMENT_DEATH, ({ me, ot }),  0, 0, 20 );
    me = "cast conjuration spells"; ot = me;
	sk_add_train(SS_FORM_CONJURATION, ({ me, ot }), 0, 0, 10);
	me = "learn and speak languages"; ot = me;
    sk_add_train(SS_LANGUAGE,      ({ me, ot }),  0, 0, 30 );
    me = "appraise your opponenent"; 
    ot = "appraise opponents";
    sk_add_train(SS_APPR_MON,      ({ me, ot }),  0, 0, 30 );
    /*
       me = "climb"; ot = me;
       sk_add_train(SS_CLIMB,      ({ me, ot }),  0, 0, 30 );
       me = "find the right way in the wilderness"; ot = me;
       sk_add_train(SS_LOC_SENSE,  ({ me, ot }),  0, 0, 25 );
       me = "follow hidden tracks and paths"; ot = me;
       sk_add_train(SS_TRACKING,   ({ me, ot }),  0, 0, 25 );
     */
    me = "be aware of your surroundings"; 
    ot = "be aware of the surroundings";
    sk_add_train(SS_AWARENESS,     ({ me, ot }),  0, 0, 30 );
    me = "trade and make deals"; ot = me;
    sk_add_train(SS_TRADING,       ({ me, ot }),  0, 0, 30 );
}

string
wizinfo() 
{
  return (
    "If there should be due cause to close down the guild, do so by\n"+
    "typing:  Call here close_guild\n"+
    "This will temporarily prevent mortals from entering. After a\n"+
    "reboot, the guild will be open by default. Please send me some\n"+
    "mail if there is anything that needs to be fixed.\n\n   Olorin.\n");
}

