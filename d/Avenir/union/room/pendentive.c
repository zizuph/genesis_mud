/*
 * The joinroom for the Shadow Union. Modelled after
 * the Rockfriend joinroom by Mercade.
 *    Cir. 032096
 *
 * Revisions:
 *    Lilith, Jul 2001: Updated guild tax info from one fifth
 *                      to more than one fourth
 *    Lilith, Sep 2003: Restricting new members in join function
 *                      wasn't working. Put in separate function
 *                      called via set_alarm 5secs after joining. 
 *    Lucius, Aug 2017: Cleaned up.
 */
#pragma strict_types
#include "../defs.h"
#include "../lib/bits.h"

inherit BASE;
inherit "/lib/guild_support";
inherit "/d/Avenir/inherit/quest";

#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include <stdproperties.h>


public int
exit_block(void)
{
    /* See if player is anything other than the desired people */
    if (!IS_MEMBER(TP))
    {
	write("Such authority does not yet lie within you, that you "+
	  "can command the cold grey mist to let you pass.\n");
	return 1;
    }

    /* Return 0 to allow the player to exit */
    write("The roiling mists part to let you pass.\n");
    return 0;
}

public void 
union_room(void)
{
    set_short("large cavern off the hallway");
    set_long("This is a massive, open cavern filled with cold "+
	"grey mist. The ceiling of this chamber is lost in the "+
	"gloom, and the floor is mostly obscured as well. The "+
	"walls are rough and unformed, being naturally formed, "+
	"and are dripping with moisture.\nIn the centre of the "+
	"room stands a pillar about three feet high, and atop the "+
	"pillar is a spherical black stone.\n");

    add_item(({"mist","fog","grey mist"}),
	"The grey mist all about seems to cling to everything.\n");
    add_item(({"ceiling"}),"The ceiling is lost in the gloom.\n");
    add_item(({"floor","ground"}),
	"Although mostly obscured by the grey mist, the floor can "+
	"be made out in places. It appears to be smooth and flat, "+
	"unlike the walls of the cavern.\n");
    add_item(({"wall","walls","cave","cavern"}),
	"The walls of the cavern rise up into the gloom, rough and "+
	"unhewn. In many places, small rivulets of water trickle along "+
	"it to the floor, moisture from the mist all about.\n");
    add_item(({"pillar"}),
	"The pillar rises up in the centre of the room to about waist "+
	"height. It is made of white rock, in stark contrast to the "+
	"dark stone that rests on the top.\n");
    add_item("stone", "At first glance, the stone atop the pillar seems "+
	"to be completely opaque, but within can be made out hundreds of "+
	"tiny points of light, almost like stars, swirling in a chaotic "+
	"maelstrom.@@check_guild@@At the base of the stone is an "+
	"inscription.\n");
    add_item(({"inscription","runes"}),
	"It reads:\n  Reach within the stone and you shall become one "+
	"with Us.\n  We shall take no less than one fourth of all your "+
	"experience in return for our powers.\n"+
	"    Death shall come to those who betray us.\n");

    add_cmd_item(({"the inscription","inscription","writing",
	    "the writing","runes","the runes"}), "read",
	"  Reach within the stone and you shall become one "+
	"with Us.\n  We shall take no less than one fourth of all your "+
	"experience in return for our powers.\n"+
	"    Death shall come to those who betray us.\n");

    add_exit("hall_w1", "south");
    add_exit("novlib0", "north", exit_block, 1, 1);

    add_prop(ROOM_I_NO_CLEANUP,       1);
    add_prop(ROOM_I_NO_ATTACK,        1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK,  1);

    create_guild_support();

    /* Wiz info for stat_object */
    add_prop(OBJ_S_WIZINFO, "This is one of the training halls "
      +"for the Union of the Warriors of Shadow. If a problem "
      +"occurs and you find it necessary to shut down the "
      +"guild, do 'Call /d/Avenir/union/list close_guild' (NOT "
      +"Call here close_guild). Note that this will shut down "
      +"ALL of the training rooms in the guild, as well as "
      +"prevent people from joining or leaving the guild,"
      +", and it will "
      +"remain so until someone calls open_guild (ie, it will "
      +"last through reboots). In other words, make sure you "
      +"have a good reason for doing it!\n");
}

public string
check_guild(void)
{ 
    if (STATE)
	return " ";

    return " A long and vicious crack runs down the middle of the stone, "+
	"as if a massive hand had tried to crush it. ";
}

public int
solve(string str)
{
    int pr;
    object qob, ob;

    if (!strlen(str) ||
	!parse_command(str, TP, "[the] %o [back] [to] [the] %s", ob, str))
    {
	return NF(CAP(query_verb())+" what?\n");
    }

    if (TP->test_bit("Avenir", GUILD_GROUP, QUEST_BIT))
    {
	write("You have already passed the test.\n");
	return 1;
    }

    if (!(pr = ob->query_prop(QUEST_OB)) || (pr != QNUM(TP)))
    {
	write("It is not accepted.\n");
	return 1;
    }

    write("You hold out "+ LANG_THESHORT(ob) +" to the mist, and "+
	"a long tedril of white fog wraps around it and takes it.\n");
    say(QCTNAME(TP) +" holds something out to the mist, and "+
	"shifting movements can be seen all around.\n");

    ob->remove_object();
    reward_quest("Union entrance Quest", TP, GUILD_GROUP, QUEST_BIT, 500);
    LOG_EVENT(TP->query_name() +" solved the entrance quest.");
    return 1;
}

public void
remove_blind(object who)
{
    if (!objectp(who))
	return;

    who->add_prop(LIVE_I_BLIND,
	who->query_prop(LIVE_I_BLIND) - 10);

    if (who->query_prop(LIVE_I_BLIND))
	return 0;

    who->catch_tell("You eyes finally clear, and you "+
	"are able to see again.\n");
}

// New members are restricted 
private void
restrict_me(object me)
{   
    LIST->add_union_punishment(me, U_PUNISHED_NOBUY);
    LIST->add_union_punishment(me, U_PUNISHED_LIBRARY);
    LIST->add_union_punishment(me, U_PUNISHED_NOCASE);
    LIST->add_union_punishment(me, U_PUNISHED_NOSTART);
}

private void init_occ_shadow(object player)
{
    player->init_occ_shadow();
}

public int
join_guild(string str)
{
    int result, qnum;
    object shadow, qob;
    string guild, *badguild;

    if (!strlen(str) || !parse_command(str, ({}),
	    "[with] [my] [hand] 'within' [the] 'stone' / 'pendentive'"))
	return NF("Reach where?\n");

    if (!STATE)
	return NF("The broken stone is hard and unyielding.\n");

    if (GUILD_CLOSED)
    {
	write("Problems have arisen with the Union, making it "+
	    "currently impossible to do that.\nPlease try again "+
	    "later, and perhaps the problem will have been fixed.\n");
	return 1;
    }
    // Player is an enemy of the guild!
    if (ENEMY(TP))
    {
	write("You reach out to touch the stone.\n"+
	    "All you see is a flash of blinding light, and "+
	    "you are thrown to the ground in agony.\n");
	say(QCTNAME(TP)+" reaches out a hand to touch the stone, "+
	    "and without warning a blast of light from "+
	    "nowhere knocks "+ HIM(TP) +" to the ground.\n");

	TP->add_prop(LIVE_I_BLIND,
	    TP->query_prop(LIVE_I_BLIND) + 10); // blind him...

	set_alarm(100.0, 0.0, &remove_blind(TP));
	TP->add_fatigue(10000);
	TP->heal_hp(-1500); // hurt him, but don't kill him
	LOG_EVENT(NM(TP) +" tried to join, but was an enemy of the guild.");
	return 1;
    }

    if (TP->test_bit("Avenir", GUILD_GROUP, PROHIBIT))
    {
	if (FRIEND(TP))
	    TP->clear_bit(GUILD_GROUP, PROHIBIT);
	if (LIST->query_hopeful(TP->query_real_name()))
	    TP->clear_bit(GUILD_GROUP, PROHIBIT);
	if (LIST->query_accepted(TP->query_real_name()))
	    TP->clear_bit(GUILD_GROUP, PROHIBIT);

	write("The shadows breathe: What you wish has yet to "+
	    "be decided. Your renewed quest for oneness begins with the "+
	    "Elders.\n");

	LOG_EVENT(NM(TP)+" tried to join, but had once been a member.");
	return 1;
    }

    if (IS_MEMBER(TP))
    {
	write("You are already one with Us.\n");
	return 1;
    }

    if (member_array(TP->query_race(), DENY_RACES) != -1)
    {
#ifdef VERBOSE
	LOG_EVENT(NM(TP)+" tried to join, but was a "+
	  TP->query_race());
#endif
	write("The "+ TP->query_race_name() +" is a graceless "+
	    "creature.\nYou are denied.\n");
	return 1;
    }

    if (TP->query_guild_member(OCC_TYPE))
    {
#ifdef VERBOSE
	LOG_EVENT(NM(TP)+" tried to join, but already had an occ guild:"+
	    TP->query_guild_name_occ());
#endif
	write("You already belong to another guild of this type.\n");
	return 1;
    }

    badguild = ({ });
    guild = TP->query_guild_name_race();
    if (member_array(guild, DENY_GUILDS) != -1)
	badguild += ({ guild });
    guild = TP->query_guild_name_lay();
    if (member_array(guild, DENY_GUILDS) != -1)
	badguild += ({ guild });
    guild = TP->query_guild_name_occ();
    if (member_array(guild, DENY_GUILDS) != -1)
	badguild += ({ guild });

    if (sizeof(badguild))
    {
	guild = COMPOSITE_WORDS(badguild);
	write("The "+ OCC_NAME +" forbids members of "+ guild +
	    " from joining.\n");
	LOG_EVENT(NM(TP)+" tried to join, but was a member of "+
	    guild);
	return 1;
    }

    if (!LIST->query_accepted(TP->query_real_name()))
    {
	write("You must first be chosen.\n");
	LOG_EVENT(NM(TP)+" tried to join but was not chosen.");
	return 1;
    }

    if (!TP->test_bit("Avenir", GUILD_GROUP, QUEST_BIT) &&
	!TP->query_wiz_level())
    {
	if (TP->query_prop("heard_the_union_quest"))
	{
	    write("A hollow voice screeches from the shadows: "+
		"You know what you must do! Begone!\n");
	    return 1;
	}

	qnum = QNUM(TP);
	write("A hollow voice whispers from the shadows: You must "+
	    "first prove yourself.\n");

	switch(qnum)
	{
	case 1: str = "Return the shard that was lost in "+
		"the tunnels. Within the element of Hizarbin "+
		    "shall it be found.\n";
		break;
	case 2: str = "A sliver of gemstone was lost upon "+
		"the high place, beneath which the dead walk. "+
		    "Return it to us.\n";
		break;
	case 3: str = "A forgotten Elder lost his token "+
		"in a distant garden. Bring it back to us.\n";
		break;
	case 4: str = "The ashes of the first Elect have been "+
		"lost within the green island. Return them to us.\n";
		break;
	case 5: str = "The green stone of the flame was lost "+
		"deep beneath the waters of the winds. Return this.\n";
		break;
	case 6: str = "Along sorrowful times the ring of the "+
		"mighty Elder was lost. It lies deep in the water "+
		"surrounded by the stone.\n";
		break;
	default: str = "A sallow light of forgotten lore you must "+
		 "return to us, else all be lost.\n";
		 LOG_ERR(TP->query_name() +" had a bad quest number: "+
		     qnum);
		 break;
	}
	write("The voice speaks: "+ str);
	TP->add_prop("heard_the_union_quest", 1);
	return 1;
    }

    /* ******* SUCCESS ******* */
    write("You reach out to the stone, and find that "+
	"your hand passes right into it.\n");
    say(QCTNAME(TP) +" reaches "+ HIS(TP) +" hand into the stone.\n");
    LOG_EVENT(NM(TP) +" joined the guild.");

    foreach(object who : users())
    {
	if (!IS_MEMBER(who))
	    continue;

	who->catch_tell("You feel strengthened, for "+
	    TP->query_the_name(who) +" has become one with shadow.\n");
    }

    shadow = clone_object(OCC_SHADOW);
    result = shadow->shadow_me(TP, OCC_TYPE, OCC_STYLE, OCC_NAME);

    if (result != 1)
    {
	LOG_ERR("ERR "+ TP->query_name() + " failed to have the "+
	    "shadow added. Result code was "+ result);

	shadow->remove_shadow();
	write("Something has gone wrong!\nYour shadow quivers and "+
	    "seems to fade slightly.\n");
	return 1;
    }

    write("Something enters your soul and you feel strengthened.\n");
    TP->set_union_sphere(SPH_TRAINING);
    set_alarm(0.5, 0.0, &init_occ_shadow(TP));

    if (TP->query_wiz_level())
    {
	write("Since you are a wizard, you will need to do the following:\n"+
	    "Call me add_autoshadow /d/Avenir/union/shadow.c:\n"+
	    "Call me add_cmdsoul /d/Avenir/union/occ_soul\n"+
	    "newhooks\n");
    }

    write("'help union' gives some commands available.\n"+
	"A small obsidian sphere materializes from the mist "+
	"in your hand.\nThe cold grey mist parts for a moment, "+
	"revealing an exit to the north.\n");

    clone_object(TOKEN_OBJ)->move(TP, 1);

    TP->add_cmdsoul(OCC_SOUL);
    TP->update_hooks();

    TP->clear_guild_stat(SS_OCCUP);
    TP->set_guild_pref(SS_OCCUP, OCC_TAX);
    TP->set_skill(OCC_LEVEL, NOVICE);

    /* Make sure the other skills are clear */
    TP->remove_skill(SS_SWAY);
    TP->remove_skill(SS_SLASH);
    TP->remove_skill(SS_FLING);

    LIST->add_member(TP);

    /* Now add some initial restrictions to the new member.  */
    set_alarm(0.5, 0.0, &restrict_me(TP));
    return 1;
}

public int
leave_guild(string str)
{
    if (!IS_MEMBER(TP))
	return 0;

    if (!strlen(str) || !parse_command(str, ({}),
	    "[the] [my] [shadow] 'union' / 'shadow' / 'guild'"))
    {
	return NF(CAP(query_verb()) + " what?\n");
    }

    if (GUILD_CLOSED)
    {
	write("Problems have arisen with the Union, making it "+
	    "currently impossible to do that.\nPlease try again "+
	    "later, and perhaps the problem will have been fixed.\n");
	return 1;
    }

    /* Place this first in case of errors. */
    LIST->leave(TP);
    LOG_EVENT(TP->query_name() +" voluntarily left the guild.");

    // That player cannot join the guild again any time soon.
    TP->set_bit(GUILD_GROUP, PROHIBIT);

    write("You betray the Union of Shadow.\n");
    say(QCTNAME(TP)+" betrays the Union of Shadow.\n");

    /* Since he left voluntarily, kill him */
    write("The mist engulfs you, dragging you into the void "+
	"and crushing you.\n");
    say(QCTNAME(TP) +" is grabbed by a long tendril of mist and "+
	"dragged screaming into the darkness.\n");

    TP->move(VOID, 1);
    TP->heal_hp(-(TP->query_max_hp()));
    TP->do_die(TO);
    return 1;
}

/*
 * Description: This is where we refresh any lost items that
 *              the player may be missing. Call it from
 *              enter_inv, perhaps.
 * Returns:     The number of items restored into the player's
 *              inventory.
 */
public void
refresh_items(object who)
{
    if (!present(who) || !IS_MEMBER(who) || present(TOKEN_ID, who))
	return;

    who->catch_tell("A tiny obsidian sphere forms from the mist "+
	"in your hand.\n");

    clone_object(TOKEN_OBJ)->move(who, 1);
#ifdef VERBOSE
    LOG_EVENT(who->query_name() +" was given a new sphere "+
	"at the pendentive.");
#endif
}

public void
leave_inv(object obj, object to)
{
    ::leave_inv(obj, to);
    gs_leave_inv(obj, to);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (IS_MEMBER(ob))
	set_alarm(1.0, 0.0, &refresh_items(ob));
}

/*
 * Stuff for meditation - guild support hooks
 */

/*
 * Function name: gs_hook_start_meditate
 * Description  : Gives a nice description when someone starts to meditate.
 */
public void
gs_hook_start_meditate(void)
{
    write("You place both hands upon the black stone and concentrate "+
	"your will upon it.\nThe room around you quickly loses focus, "+
	"and it is as if you were looking into your own soul.\n");
    say(QCTNAME(TP) +" places both hands around the black stone "+
	"and closes "+ HIS(TP) +" eyes.\n");

    TP->add_prop(LIVE_S_EXTRA_SHORT, "'s hands are wrapped around the "+
	"dark stone, concentrating deeply");
}

/*
 * Function name: gs_hook_rise
 * Description  : Gives a nice description when someone is done meditating.
 */
public void
gs_hook_rise(void)
{
    write("As you release your hands from around the stone, the "+
	"world brutally snaps back into focus.\nYou gasp from "+
	"the shock.\n");
    say(QCTNAME(TP) +" releases "+ HIS(TP) +
	" hands from the stone.\n" + QCTNAME(TP) +
	" gasps in shock.\n");
}

/*
 * Function name: gs_hook_already_meditate
 * Description  : Gives a nice message when someone tries to meditate
 *                when (s)he is already mediating.
 */
public int
gs_hook_already_meditate(void)
{
    write("You are already deep in meditation. You may "+
	"\"estimate\" your different preferences for "+
	"concentration and \"set\" them to new values "+
	"if you please. To relax and get back to the "+
	"outside world, just \"rise\".\n");
    return 1;
}

public void
init(void)
{
    ::init();
    init_guild_support();

    add_action(join_guild,   "reach");
    add_action(leave_guild,  "betray");
    add_action(solve,        "return");
    add_action(solve,        "give");
}
