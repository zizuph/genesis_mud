#pragma strict_types
/*
 * Shadow for the Union of the Warriors of Shadow
 * Loosley based on Mercade's Rockfriends shadow.
 *   Copyright (c) Marc Prud'hommeaux (Lord Cirion) April 1996
 *                 Cirion@Genesis
 *
 * Revisions:
 *   Cirion, Nov 1996: Added support for the different Spheres of Intelligence.
 *   Cirion, Apr 1997: Added support for the Union virtues
 *   Cirion, Dec 1997: Added messages for when a virtue is lost
 *   Lilith, Mar 2004: Added cloning of Voice tablet
 *   Lilith, Jun 2004: Added cloning of scarf
 *   Lilith, Jun 2004: Updated sybarite and faithful checks
 *   Lucius, Apr 2005: Changed query_armour -> query_clothing
 *   Lucius, Apr 2005: Added npc sphere setting/querying
 *   Lucius, May 2007: Added new corpse stuff
 *   Lucius, Jul 2007: Added virtue loss for stealing
 *   Lucius, Nov 2007: Changed subloc to split union and eye bits
 *   Lucius, Nov 2007: Removed bounded_array_val and virtue_text functions
 *   Lucius, Dec 2007: More minor cleanups
 *   Lucius, May 2008: Added logic so Jadestone's poison only affects virtues once.
 *   Lucius, Feb 2009: Changed cmdsoul handling and status checks.
 *   Lucius, Apr 2016: Removed never used Elect code
 *   Lucius, May 2016: Fixed up OCC_LEVEL settings, reformated revisions list.
 *   Lucius, Aug 2017: Various fixups - Re-code.
 *   Lilith, Aug 2021: Limited alcohol consumption based on recode restrictions.
 *                     See notes on drink_alco function below for more info.
 * 
 */
inherit "/std/guild/guild_occ_sh";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "lib/titles.h"
#include "defs.h"

#define QSW		shadow_who
#define EYE_ADJ		"dark-eyed"
#define STD_SOUL	"/d/Genesis/cmd/soul_cmd_"

public string query_union_sphere(void);
public string query_union_sphere_title(void);
public void check_union_occ_status(void);
public int adjust_union_virtue(int which, int how_much);

private static int last_virtue_gain, union_npc;
private static string union_sphere, title, title2;
private static string *u_titles = UNION_TITLES;
private static mapping  spheres = SPHERES,
			u_sphere_titles = U_SPHERE_TITLES;

private static string *race_sway = ({
	"speaks in a hollow, distant voice",
	"murmurs in a trance-like tone",
	"sings with a musical breath",
	"cries out with fervor",
});
private static string *actor_sway = ({
	"speak in a hollow, distant voice",
	"murmur in a trance-like tone",
	"sing with a musical breath",
	"cry out with fervor",
});
private static string *msg_sounds = ({
	"A soft voice whispers: ",
	"From the depths of the shadows, a low voice grates: ",
	"Voices can be heard all around: ",
	"A woman's voice sighs: ",
	"Flames and shadows speak: ",
	"The air is full of whispers: ",
	"A deep moan arises from the depths of the world: ",
	"Aged and crackling voices speak: ",
});

/* Constructer */
>>(void)
{
    setuid();
    seteuid(getuid());
}

/*
 * Function name:  query_guild_trainer_occ
 * Description:    a list of all the rooms in the union a
 *                 player can train in.
 * Returns:        an array of training objects
 */
public mixed *
query_guild_trainer_occ(void)
{
    string *places;

    /* If the player is being punished with "decay",    */
    /* return 0 here so his skills will begin to decay  */
    if (U_IS_PUNISHED(QSW, U_PUNISHED_DECAY))
	return 0;

    places = ({ TRAINER, ALCOVE, WHITE, LIBRARY, FORGE });

    if (QSW->test_bit("Avenir", GUILD_GROUP, TRAINING))
	places += ({ ELITE });

    return places;
}

/*
 * Function name:  query_guild_tax_occ
 * Description:    Guild Tax
 * Returns:        The occupational guild tax
 */
public nomask int
query_guild_tax_occ(void)
{
    return OCC_TAX;
}

/*
 * Function name:  query_guild_style_occ
 * Description:    The style of the Guild
 * Returns:        Fighter
 */
public nomask string
query_guild_style_occ(void)
{
    return OCC_STYLE;
}

/*
 * Guild name.
 */
public nomask string
query_guild_name_occ(void)
{
    return OCC_NAME;
}

/*
 * This so you can't leave combat to enter the sway
 * again.
 */
public void
adjust_combat_on_move(int leave)
{   /*
     * This dosen't really have anything to do with
     * adjusting combat, but it will be called externally
     * every time the player moves. Thus, the player
     * loses some dignity any time he sneaks anywhere.
     */
    if (leave && TP->query_prop(LIVE_I_SNEAK))
	adjust_union_virtue(US_DIGNITY, -10);

    QSW->adjust_combat_on_move(leave);

    if (present(QSW->query_attack(), environment(QSW)))
	QSW->add_prop(UNION_I_MOVE, time());
}

public void
do_triumph(void)
{
    object corpse = present("corpse", environment(QSW));
    string *kill = corpse->query_prop(CORPSE_AS_KILLER);

    if (CAN_SEE_IN_ROOM(QSW) &&
	objectp(corpse) && sizeof(kill) &&
	kill[0] == QSW->query_real_name())
    {
	QSW->command("$triumph corpse");
    }
}

public void
notify_you_killed_me(object enemy)
{
    QSW->remove_prop(UNION_I_MOVE);
    QSW->notify_you_killed_me(enemy);

    // Need to do it in an alarm, otherwise the corpse isn't there yet!
    if (!random(4))
	set_alarm(0.5, 0.0, do_triumph);

    if (enemy->query_average_stat() > QSW->query_average_stat())
	adjust_union_virtue(US_PRIDE, 10);

    /* If the enemy is humanoid, stain the clothes of the
     * Union member with blood, according to the CON
     * of the enemy.
     */
    if (enemy->query_humanoid())
    {
	object *obs = QSW->query_clothing(-1);
	obs->union_stain_with_blood(random(enemy->query_stat(SS_CON)));
    }
}

/*
 * Function name:  query_union_level
 * Description:    returns a numer from 1 - the MAX_SS_OCCUP to
 *                 determine the rank of the player withing the
 *                 guild.
 * Returns:        The rank of the player.
 * Note:           This function taken from the Rockfriend shadow
 *                 by Mercade.
 */
public nomask int
query_union_level(void)
{
    int size  = sizeof(u_titles),
	level = query_shadow_who()->query_stat(SS_OCCUP);

    level = ((level * size) / MAX_SS_OCCUP) - 1;
    return ((level >= size) ? (size - 1) : ((level < 0) ? 0 : level));
}

/*
 * returns 1 if the player is in a team of all other union members.
 */
public int
team_is_union(void)
{
    object *others = shadow_who->query_team_others();

    if (!sizeof(others))
	return 0;

    if (sizeof(filter(others, not @ &->query_is_union_member())))
	return 0;

    return 1;
}

public nomask string *
possible_union_titles(void)
{
    int gender, level;
    string *titles = ({ });
    /*
     * If a member is punished with "title", their only choice of
     * title will be the default punished title.
     */
    if (U_IS_PUNISHED(QSW, U_PUNISHED_TITLE))
	return ({ BAD_TITLE });

    level  = query_union_level();
    gender = (QSW->query_gender() == 1 ? 1 : 0);

    if (pointerp(u_titles[level]))
	titles += ({ u_titles[level][gender] });
    else if (stringp(u_titles[level]))
	titles += ({  u_titles[level] });

    if (VALID_GURU(QSW) == -1)
	titles += ({ GURU_TITLE });

    if (team_is_union())
	titles += ({ TEAM_TITLE });

    foreach(mixed one: u_sphere_titles[query_union_sphere()])
    {
	if (pointerp(one))
	    titles += ({ one[gender] });
	else if (stringp(one))
	    titles += ({ one });
    }

    return titles;
}

/*
 * Function name:  query_guild_title_occ
 * Description:    The guild title based on the SS_OCCUP stat, or
 *                 a special title if you are punished or a member
 *                 of the council.
 * Returns:        The title
 */
public nomask string
query_guild_title_occ(void)
{
    if (U_IS_PUNISHED(QSW, U_PUNISHED_TITLE))
	return BAD_TITLE;

    string *titles = possible_union_titles();

    // Sanity check
    if (!sizeof(titles))
	titles = ({ "Shadow Warrior" });

    if (strlen(title) && (member_array(title, titles) != -1))
    {
	if (strlen(title2) && (member_array(title2, titles) != -1))
	    return title + ", " + title2;
	else
	    return title;
    }

    return titles[0];
}

public nomask varargs string
set_union_title(string str, int index = 1)
{
    int which;
    string *titles = possible_union_titles();

    if (!strlen(str))
	return 0;

    // allow for choosing a random title
    if (lower_case(str) == "random")
	str = one_of_list(titles);

    // allow for unsetting a title
    if (lower_case(str) == "none")
    {
	if (index == 1)
	{
	    return title = titles[0];
	}
	else
	{
	    title2 = "";
	    return "nothing";
	}
    }

    // Allow for selecting the actual title string, case insenstive
    if ((which = member_array(lower_case(str), map(titles, lower_case))) >= 0)
    {
	if (index == 1)
	    return title = titles[which];
	else
	    return title2 = titles[which];
    }

    which = 0;

    // Allow for selecting "1", "one", or "first", index on that - 1
    sscanf(str, "%d", which);
    if (which || (which = LANG_NUMW(str)) || (which = LANG_ORDW(str)))
    {
	if (which <= 0)
	{
	    if (index == 1)
		return title = titles[which];
	    else
		return title2 = "";
	}

	if (which > sizeof(titles))
	{
	    notify_fail("You do not have that many titles "+
		    "to choose from.\n");
	    return 0;
	}
	else
	{
	    which--;

	    if (index == 1)
		return title = titles[which];
	    else
		return title2 = titles[which];
	}
    }

    return title = titles[0];
}

public int
query_guild_leader_occ(void)
{
    return MEMBER_SPHERE(QSW, SPH_VOICE) ||
	   MEMBER_SPHERE(QSW, SPH_MENTOR);
}

public string
query_eyes_colour(void)
{
    string str = "grey";

    if (query_union_sphere() == SPH_TRAINING)
	return str;

    switch(QSW->query_stat(SS_OCCUP))
    {
    case 0 .. 10:     str = "dusk"; break;
    case 11 .. 20:    str = "sable"; break;
    case 21 .. 30:    str = "soot"; break;
    case 31 .. 40:    str = "raven"; break;
    case 41 .. 50:    str = "coal"; break;
    case 51 .. 60:    str = "inky"; break;
    case 61 .. 70:    str = "ebony"; break;
    case 71 .. 80:    str = "pitch"; break;
    case 81 .. 90:    str = "midnight"; break;
    case 91 .. 100:   str = "jet"; break;
    case 101 .. 120:  str = "cimmerian"; break;
    default:          str = "abysmally"; break;
    }

    return str + "-black";
}

public string
query_eyes_type(void)
{
    if (query_union_sphere() == SPH_TRAINING)
	return "dark";

    if (!find_object(HOME))
	return "dull";

    switch(STATE)
    {
    case -10000..0:  return "lifeless";
    case    1..500:  return "vacant";
    case  501..1000: return "withered";
    case 1001..1500: return "feeble";
    case 1501..2000: return "weakened";
    case 2001..2500: return "dull";
    case 2501..3000: return "cloudy";
    case 3001..3500: return "strong";
    case 3501..4000: return "powerful";
    case 4001..4500: return "stormy";
    case 4501..5000: return "intense";
    case 5001..5500: return "vital";
    case 5501..6000: return "potent";
    case 6001..6500: return "compelling";
    case 6501..7000: return "dreadful";
    case 7001..7500: return "fell";
    case 7501..8000: return "dire";
    case 8001..8500: return "terrifying";
    case 8501..9000: return "torrential";
    default:         return "lethal";
    }
}

public string
query_eyes(void)
{
    return query_eyes_type() + " " + query_eyes_colour();
}

public string
show_subloc(string subloc, object me, object viewer)
{
    string ret = "";

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return me->show_subloc(subloc, me, viewer);

    if (subloc == "eyes")
    {
	return (viewer == me ? "Your" : capitalize(me->query_possessive())) +
	    " eyes are " + query_eyes() + (me->query_attack() ?
		", and seem to flicker with an angry blue flame" :
		"") + ".\n";
    }

    if (subloc != "union")
	return me->show_subloc(subloc, me, viewer);

    if (present(SWAY_ID, me))
    {
	if (viewer == me)
	    ret += "You are deep within the Sway.\n";
	else
	{
	    ret += capitalize(me->query_pronoun()) + " moves with "+
		"eerie, flowing motions, as if "+
		me->query_pronoun() +" were in a trance.\n";
	}
    }

    if (strlen(query_union_sphere()))
    {
	if (viewer == me)
	{
	    ret += "You are of the Sphere of " +
		query_union_sphere_title() + ".\n";
	}
	else if (IS_MEMBER(viewer))
	{
	    ret += capitalize(me->query_pronoun()) + " is of the Sphere of "+
		query_union_sphere_title() + ".\n";
	}
    }

    return ret;
}

public nomask void
init_occ_shadow(string str)
{
    QSW->add_subloc("union", this_object());

    /* Only act as the 'eyes' subloc if it doesn't exist. */
    if (!objectp(QSW->query_subloc_obj("eyes")))
	QSW->add_subloc("eyes", this_object());

    /* macros defined in /d/Avenir/include/relation.h */
    QSW->add_prop(SYBARITE, SYB_OCC);

    // make sure a player with the soul is on the member list
    if (query_interactive(QSW))
    {
	switch(LIST->add_member(QSW))
	{
	case 1:
	    LOG_ERR(QSW->query_name() +
		" logged in and was not a member -- readding.");
	    break;
	case 0:
	    LOG_ERR(QSW->query_name() +
		" logged in and was not a member -- readdition failed.");
	    break;
	}
    }
    else union_npc = 1;

    set_alarm(2.0, 0.0, check_union_occ_status);

#if 0
    /* Give the different sphere-specific objects to the player */
    string ob_name = SPHERE_OBJECTS[query_union_sphere()];

    if (strlen(ob_name))
	clone_object(ob_name)->move(QSW, 1);
#endif

    // register that this member is currently in the realms.
    LIST->add_present_member(QSW);
}

/*
 * We have our own PO
 */
public string
query_def_post(void)
{
    return POST;
}

/*
 * Function name:  query_guild_skill_name
 * Description:    When a players uses the skills command
 *                 he should get the
 *                 the skill names, not the 'special' string.
 * Arguments:      type - the number of the skill
 * Returns:        0 if no skill of mine, else the string.
 */
public string
query_guild_skill_name(int type)
{
    switch(type)
    {
    case SS_SWAY:
	return "the sway";
    case SS_SLASH:
	return "slashing attack";
    case SS_FLING:
	return "fling knife";
    case OCC_LEVEL:
	if (TP->query_wiz_level())
	    return "Union Level";
	else
	    return "";
    case US_DIGNITY:
	if (TP->query_wiz_level())
	    return "Union Dignity";
	else
	    return "";
    case US_PRIDE:
	if (TP->query_wiz_level())
	    return "Union Pride";
	else
	    return "";
    case US_GRACE:
	if (TP->query_wiz_level())
	    return "Union Grace";
	else
	    return "";
    case US_PURITY:
	if (TP->query_wiz_level())
	    return "Union Purity";
	else
	    return "";
    default:
	return (string)0;
    }
}

/*
 * Function name:   do_glance
 * Description:     This is the routine describing rooms to livings
 * Arguments:       brief: if true, do write the short-description,
 *                  else write the long-description.
 * Returns:         always 1.
 */
public int
do_glance(int brief)
{
    if (!brief && present(SWAY_ID, QSW) && CAN_SEE_IN_ROOM(QSW))
    {
	QSW->catch_tell("Everything seems to be moving slowly, "+
	    "as if some vital aspect of the world around you had "+
	    "been altered. ");
    }
    else if (!brief && present(SWAY_ID, QSW))
    {
	QSW->catch_tell("The Darkness itself seems to throb with "+
	    "a life of its own, the shadows enshroud you in their "+
	    "warmth. ");
    }

    return QSW->do_glance(brief);
}

/*
 * Function name: query_guild_keep_player
 * Description  : Tests whether we want to keep a player
 *                 if he logs in.
 * Arguments    : player - the player to check
 * Returns      : 0 - if the player will be kicked out
 *                1 - the player will remain
 * Nb           : This function checks the LIST object to
 *                see if the player has been expelled, as well
 *                as expelling for a forbidden guild,
 *                or forbidden race.
 */
public int
query_guild_keep_player(object player)
{
    if (!objectp(player))
	return 1;

    if (sizeof(LIST->query_expelled(player)))
    {
	if (player->query_wiz_level())
	{
	    /* Avoid the fuss on wizards. */
	    LIST->leave(player);
	    return 0;
	}

	player->catch_tell("You have been expelled from the Union.\n");
	LOG_EVENT(player->query_name()+" logged on and was expelled.");
	LIST->remove(player);

	/* Shadow will be removed after this return. */
	return 0;
    }

    if (member_array(player->query_race(), DENY_RACES) != -1)
    {
	player->catch_tell("The Union disallows the presence "+
	    "of " +LANG_ADDART(player->query_race()) +".\n");
#ifdef VERBOSE
	LOG_EVENT(player->query_name() +" changed race to "+
	    player->query_race() +" and was removed.");
#endif
	LIST->remove(player);
	return 0;
    }

    if (member_array(player->query_guild_name_lay(),  DENY_GUILDS) != -1 ||
	member_array(player->query_guild_name_race(), DENY_GUILDS) != -1)
    {
	player->catch_tell("Your guild is forbidden by the Union.\n");
#ifdef VERBOSE
	LOG_EVENT(player->query_name() +" joined a forbidden guild "+
	    "and was removed.");
#endif
	LIST->remove(player);
	return 0;
    }

    return ::query_guild_keep_player(player);
}

/*
 * Function name:   add_soul_at_top
 * Description:     add given soul at the top of the cmdsoul list
 * Arguments:       soul: filename of soul to be added
 *                  who:  player the soul must be added to
 */
static void
add_soul_at_top(string soul)
{
    string *soul_arr = QSW->query_cmdsoul_list();

    QSW->remove_cmdsoul(soul);

    foreach(string one_soul : soul_arr)
	QSW->remove_cmdsoul(one_soul);

    QSW->add_cmdsoul(soul);

    foreach(string one_soul : soul_arr)
	QSW->add_cmdsoul(one_soul);

    QSW->update_hooks();
}

/* Check for 'undignified' objects. */
static void
undignified_stuff(void)
{
    int stuff;

    foreach(object ob : all_inventory(QSW))
    {
	/* Gelan tattoo's. */
	if (ob->id("_stexxs_tattoo_object"))
	    stuff += sizeof(ob->query_tattoos());

	/* Kalad piercings. */
	if (ob->query_prop("_kalad_ring_hole"))
	    stuff++;
    }

    if (!stuff)
	return;

    stuff *= 10;

    adjust_union_virtue(US_PURITY,  -stuff);
    adjust_union_virtue(US_DIGNITY, -stuff);

    QSW->catch_tell(
	"You feel a loss of virtue due to your body decorations.\n");
}

/*
 * Is the player promoted or demoted? Is the player punished?
 * If he is in the council or higher, clone the suitable object and
 * move it to his inventory. Add the cmdsoul here as well. Does the
 * player lose dignity because of objects in his/her inventory?
 */
public void
check_union_occ_status(void)
{
    object ob;
    string sphere_soul;

    // check to see if ther sphere-specific soul exists, and
    // if so, add it.
    sphere_soul = UNION + "spheres/" + query_union_sphere() + "_soul";

    if (file_size(sphere_soul + ".c") > 0)
    {
	// try to load it if it is not already
	if (!find_object(sphere_soul))
	    catch(sphere_soul->teleldensanka());

	if (find_object(sphere_soul))
	    QSW->add_cmdsoul(sphere_soul);
    }

    set_alarm(0.5, 0.0, &add_soul_at_top(OCC_SOUL));

    if (LEVEL(QSW) >= NORMAL)
    {
	ob = clone_object(OBJ+"combat_veil");
	ob->move(QSW, 1);
    }

    /* NPC's do not need to process the following. */
    if (union_npc)
	return;

    set_alarm(10.0, 0.0, undignified_stuff);

    /* Check the LIST against the player's guild skill in descending
     * order to see if he has been demoted while he was away.
     */
    if (IS_ELDER(QSW) && !LIST->query_is_elder(QSW))
    {
	QSW->catch_tell("You are no longer an Elder.\n");
	QSW->set_skill(OCC_LEVEL, NORMAL);

	// In case of demotion
	if (ob = present("av_e_folio", QSW))
	    ob->remove_object();
    }

    if (!IS_ELDER(QSW) && LIST->query_is_elder(QSW))
    {
	QSW->catch_tell("You have attained the status of an Elder.\n");
	QSW->set_skill(OCC_LEVEL, ELDER);
    }

#if 0
    if (IS_ELDER(QSW))
    {
	ob = clone_object(OBJ + "e_tablet");
	ob->move(QSW, 1);
    }
#endif

    /* Give them the elder soul, if appropriate */
    if (IS_ELDER(QSW) || IS_GMASTER(QSW))
	QSW->add_cmdsoul(ELDER_SOUL);

#if 0
    if (query_union_sphere() == SPH_VOICE)
    {
	ob = clone_object(OBJ + "v_tablet");
	ob->move(QSW, 1);
    }
#endif

    /* Fixup the OCC_LEVEL */
    if (LEVEL(QSW) == NOVICE &&
	query_union_sphere() != SPH_TRAINING)
    {
	QSW->set_skill(OCC_LEVEL, NORMAL);
    }

    /* Obtain the messages for the player from the LIST */
    foreach(string msg: LIST->get_union_messages(QSW))
	QSW->catch_tell(one_of_list(msg_sounds) + msg);
}

/*
 * Function name:   attack_object
 * Description:     logs a player attacking a member of the Union
 * Arguments:	    The object to attack
 */
public void
attack_object(object enemy)
{
    if (QSW->query_prop(OBJ_I_HIDE))
    {
	adjust_union_virtue(US_DIGNITY, -20);

	QSW->catch_tell(
	    "Attacking while hidden is an undignified thing to do.\n");
    }

    QSW->attack_object(enemy);
}

private static int snd_idx = 0;
private static string snd_str = "";

public string
race_sound(void)
{
    if (strlen(snd_str))
	return snd_str;

    return QSW->race_sound();
}

public string
actor_race_sound(void)
{
    object List = LIST->get_this_object();

    if (present(SWAY_ID, QSW))
    {
	snd_idx = random(sizeof(actor_sway));
	snd_str = race_sway[snd_idx];
	return actor_sway[snd_idx];
    }

    if (List->query_union_option(QSW, UOPT_LSHORT))
    {
	snd_str = "lilts";
	return "lilt";
    }

    if (List->query_union_option(QSW, UOPT_LLONG))
    {
	snd_str = "says with a lilting accent";
	return "say in a lilting accent";
    }

    snd_str = "";
    return QSW->actor_race_sound();
}

public string
query_union_sphere(void)
{
    if (strlen(union_sphere))
	return union_sphere;
    else if (union_npc)
	return DEFAULT_SPHERE;
    else
	return LIST->query_union_sphere(QSW);
}

public string
query_union_sphere_title(void)
{
    return spheres[query_union_sphere()];
}

public int
set_union_sphere(string which)
{
    if (!spheres[which])
	return 0;

    if (!union_npc && !LIST->set_union_sphere(QSW, which))
	return 0;

    union_sphere = which;
    return 1;
}

/*
 * query_is_union_player() returns 1 if the player has this shadow
 * and is not a wizard or a jr.
 */
public int
query_is_union_player(void)
{
    return !QSW->query_wiz_level() &&
	   !wildmatch("*jr", QSW->query_real_name());
}

public int
query_is_union_member(void)
{
    return 1;
}

public int
query_is_union_npc(void)
{
    return union_npc;
}

/* Support for the virtues */
public void
set_union_virtue(int which, int how_much)
{
    if (which != US_DIGNITY && which != US_PRIDE &&
	which != US_GRACE   && which != US_PURITY)
    {
	return;
    }

    int new = how_much;

    if (new < US_VIRTUE_MIN)
	new = US_VIRTUE_MIN;
    else if (new > US_VIRTUE_MAX)
	new = US_VIRTUE_MAX;

    QSW->set_skill(which, new);
}

public int
query_union_virtue(int which)
{
    if (which != US_DIGNITY && which != US_PRIDE &&
	which != US_GRACE   && which != US_PURITY)
    {
	return 0;
    }

    int virt = QSW->query_skill(which);

    if (virt > US_VIRTUE_MAX)
	virt = US_VIRTUE_MAX;
    else if (virt < US_VIRTUE_MIN)
	virt = US_VIRTUE_MIN;

    return virt;
}

/* It is harder to gain virtue than to lose it */
public int
adjust_union_virtue(int which, int how_much)
{
    string virtue_str;
    int current, new = QSW->query_skill(which);

    if (which == US_DIGNITY)
	virtue_str = "dignity";
    else if (which == US_PRIDE)
	virtue_str = "pride";
    else if (which == US_GRACE)
	virtue_str = "grace";
    else if (which == US_PURITY)
	virtue_str = "purity";
    else
	virtue_str = "";

    current = query_union_virtue(which);
    how_much = ((current <= 0 || how_much <= 0 ) ? how_much :
	max(how_much / max((current / 100), 1), 1));

    if (how_much < 0 && strlen(virtue_str))
	QSW->catch_tell("You sense a loss of " + virtue_str + ".\n");

    set_union_virtue(which, new + how_much);

    /* Log virtues or virtue losses based on the defines  */
    /* outlined in /d/Avenir/union/defs.h                 */
    if ((LOG_VIRTUES || (LOG_VIRTUE_LOSSES && how_much < 0)) &&
	how_much && query_verb() && query_interactive(QSW))
    {
	write_file(GUILDLOG + "virtues", QSW->query_name() +
	    (how_much < 0 ? " lost " : " gained ") + how_much +
	    " "+ virtue_str +" (verb=" + query_verb() + ")\n");
    }

    return query_union_virtue(which);
}

/*
 * Some emotions will adjust a Union members virtue, but
 * there needs to be a time stamp on it, so that members
 * do not do 1,000 emotions in a row to pump up their
 * virtues.
 */
public int
emote_adjust_union_virtue(int which, int how_much)
{
    int res;

    if (time() < last_virtue_gain && how_much > 0)
	return 0;

    if (res = adjust_union_virtue(which, how_much))
	last_virtue_gain = time() + 10 + random(1600);

    return res;
}

/* 
 *   Lilith, Aug 2021: Union is allowed up to 25% intox before abilities are 
 *                     negatively impacted.  Putting a cap in the shadow to 
 *                     limit alcohol consumption based on recode restrictions
 *                     so the guild can get a little bit of hp regen boost from
 *                     what little alcohol they are allowed to drink w/o blowing
 *                     up their specials.
 */
public varargs int
drink_alco(int strength, int ask)
{
    if ((QSW->query_intoxicated() + strength) * 100 >
        QSW->query_prop(LIVE_I_MAX_INTOX) * 25) 
    {
        return 0;
    }
    return QSW->drink_alco(strength, ask);
}

public void
enter_inv(object ob, object from)
{
    QSW->enter_inv(ob, from);

    /* Bizarre, but happens. */
    if (!objectp(ob))
	return;

    /* Purity is decreased by having poison in the system */
    if (MASTER_OB(ob) == "/std/poison_effect")
	adjust_union_virtue(US_PURITY, -20);
}

private static int rcount = 0;

private nomask void
reset_run_away(void)	{ rcount = 0; }

/* loose some pride for running away */
public void
run_away(void)
{
    QSW->run_away();

    if (!rcount)
	adjust_union_virtue(US_PRIDE, -10);

    if (MASTER_OB(calling_object()) == (BAZAAR + "Obj/misc/j_poison"))
    {
	if (++rcount == 1)
	    set_alarm(1.0, 0.0, reset_run_away);
    }
}

/*
 * Drive home the idea that alignments are in the eye of
 * the Beholder.
 */
public string
query_align_text(void)
{
    string str = "";

    /* i.e., player did "vitals" */
    if (QSW == TP)
	str = "seen by the outside world as being ";

    return str + QSW->query_align_text();
}

/*
 * Function name:   add_introduced
 * Description:     Add the name of a living who has introduced herself to us.
 *                  This is masked in the Union to allow the "registering"
 *                  of guilds who will become 'known' to the rest of the guild.
 * Arguments:       str: Name of the introduced living
 *
 */
public void
add_introduced(string str)
{
    object who;
    string occ, lay, race;

    QSW->add_introduced(str);

    /* all_introduced() will almost always add the name
     * of this_player(). Do some extra checks to make sure.
     */
    who = TP;

    if (!who || !living(who) || (who->query_real_name() != lower_case(str)))
	return;

    /* Wizards are always working on test guilds. Don't log these. */
    if (who->query_wiz_level() ||
	wildmatch("*jr", who->query_real_name()))
	return;

    /* Get all guild names, provided they are not incognito */
    if (!who->query_guild_incognito_occ())
    {
	if (strlen(occ = who->query_guild_name_occ()))
	    LIST->add_known_guild(occ, "occ");
    }

    if (!who->query_guild_incognito_lay())
    {
	if (strlen(lay = who->query_guild_name_lay()))
	    LIST->add_known_guild(lay, "lay");
    }

    if (!who->query_guild_incognito_race())
    {
	if (strlen(race = who->query_guild_name_race()))
	    LIST->add_known_guild(race, "race");
    }
}

// Give some more interesting mm_in/out messages.
public string
query_mm_in(void)
{
    // wizards get the message of their choosing
    if (QSW->query_wiz_level())
	return QSW->query_mm_in();

    return one_of_list(({"materializes", "emerges", "appears" })) +
	" from a wreathe of dark-blue fires.";
}

public string
query_mm_out(void)
{
    // wizards get the message of their choosing
    if (QSW->query_wiz_level())
	return QSW->query_mm_out();

    set_alarm(1.0, 0.0,
	&tell_room(environment(QSW), "The flames die away.\n"));

    return "vanishes in a swirl of deep-blue flame.";
}

// Allow for some custom adverbs.
public string
full_adverb(string str)
{
    string adverb = UADVERBS_FILE->full_adverb(str);

    if (strlen(adverb))
	return adverb;

    return QSW->full_adverb(str);
}

// Defines what happens to the player after death.
public void
death_sequence(void)
{
    if (!QSW->query_ghost())
	return;

    clone_object(UNION_DEATH)->move(QSW, 1);
}

// Corpse we leave behind on death.
public object
make_corpse(void)
{
    object corpse = clone_object(UNION_CORPSE);

    corpse->set_died(QSW, union_npc);
    corpse->set_name(QSW->query_real_name());

    return corpse;
}

// The Faithful shouldn't be stealing.
public int
hook_thief_steal_bonus(object victim, object place, object item)
{
    adjust_union_virtue(US_GRACE,   -200);
    adjust_union_virtue(US_PRIDE,   -200);
    adjust_union_virtue(US_DIGNITY, -200);

    QSW->catch_tell(
	"\nTo thwart the Gods' providence is the way of the sin'ur.\n");

    // Don't return a value, just affect virtues.
    return 0;
}
