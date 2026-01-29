/*
 *  /d/Emerald/telberin/trainhall.c
 *
 *  This is the training hall offering skills for those
 *  who wish to improve their abilities in Telberin.
 *
 *  Copyright (c) April 2003 by Cooper Sherry (Gorboth)
 *
 *    Copied from the Minas Morgul Training Hall in
 *    Gondor which was created by Olorin
 */
#pragma strict_types

inherit "/d/Emerald/telberin/telberin_room";
inherit "/lib/guild_support";
inherit "/lib/skill_raise";

#include <language.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

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


/*
 * Function name:        create_telberin_room
 * Description  :        set up the room
 */
public void
create_telberin_room()
{
    set_short("a training hall in Telberin");
    set_em_long("This is one of the training halls in Telberin.\n");

    add_prop(OBJ_S_WIZINFO, "@@wizinfo");
    add_prop(ROOM_I_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK,1);
    add_prop(ROOM_I_INSIDE,1);

    create_guild_support();
    create_skill_raise();
    set_up_skills();

    add_item(({"rug","carpet"}),
    "It is a rather old, thick carpet. It looks like it has seen some " +
    "heavy use and was maltreated by booted feet, but it is still probably " +
    "quite comfortable to sit down on it. " +
    "You can do that, if you want to <meditate>. Once you are meditating you will " +
    "be able to <estimate> your progress on your path to wizdom, and to <set> " +
    "your personal preferences.\n");

    reset_room();
}

private void
make_trainer()
{
    if (objectp(Trainer))
        return;

    Trainer = clone_object("/d/Emerald/telberin/npc/telberin_elf.c");
    Trainer->set_long(Trainer->query_long() +  
      "He looks like he is the veteran of many wars. " +
      "He now earns his bread by training others in the use " +
      "of weapons and some other skills.\n");
    Trainer->add_name("_train_elf");
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
    Trainer->move_living("down", this_object());
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
	ob->move_living("north",
            "/d/Emerald/telberin/arts/cantors_plaza");
    }
}

public int
try_skills(string str)
{
    object elf;

    this_player()->reveal_me(1);
    if (!objectp(elf = present("_train_elf", this_object())))
    {
	write("There is no one present who could train you.\n");
	return 1;
    }
    if (!CAN_SEE(elf, this_player()))
    {
	write("The " + elf->query_nonmet_name() + " cannot see you!\n");
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
    {
        return "  **The guild is now closed**";
    }

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
    me = "understand and speak languages"; ot = me;
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
    "mail if there is anything that needs to be fixed.\n\n   Gorboth.\n");
}


