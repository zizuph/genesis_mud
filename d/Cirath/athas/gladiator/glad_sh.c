/* glad_sh.c: The Gladiator-Guild Shadow: Mylos & Anton, 10-8-93.
 *     Redone for guild revision: Shiva, 1/15/95.
 *     Redone for reopening: Serpine, 4/26/95.
 *     Efficeincy and bug fixes: Astro & Serpine, 11/26/95.
 *     Only clear start location if it's currently the gladiator 
 *          start room: Petros, August 2009
 */
#pragma strict_types
#pragma save_binary

inherit "/std/guild/guild_occ_sh";
#include "defs.h"
#include <const.h>

#define START_ROOM (GLAD_ROOM + "mainhall")
#define LEVEL_BY_GUILD_STAT
#define QSW query_shadow_who()
#define SET(x, y) if (QSW->query_skill(x) > y) \
      (y < 1 ? QSW->remove_skill(x) : QSW->set_skill(x, y))


// Declaration
varargs void kick_out_glad(int spare);


/* Standard functions for any occupational guild */
int
query_guild_tax_occ()	{ return GUILD_TAX; }

string
query_guild_style_occ()	{ return GUILD_STYLE; }

string
query_guild_name_occ()	{ return GUILD_NAME; }

string
query_def_post()	{ return (GLAD_ROOM + "post"); }

public string *
query_guild_trainer_occ()
{
    return ({ "/d/Cirath/athas/gladiator/room/training" });
}

public void
remove_gladiator_shadow()
{
    remove_shadow();
}

void
check_glad(object obp)
{
    string name = obp->query_real_name();

    if (CHECK_PUNISHMENT(name, PUN_EXPEL))
    {
	obp->catch_tell("The violence within your dreams has been "+
	  "visited upon you, for you have been Expelled from "+
	  "the Gladiators of Athas!\n");
	kick_out_glad();
	return;
    }

    obp->catch_tell("You awake from nightmares of slavery and violence "+
      "only to face them in reality: Such is your path, the path of "+
      "a warrior of Athas.\n");

    if(!present(CUIR_ID, obp))
	clone_object(GLAD_OBJ + "cuirasse")->move(obp);

    obp->add_cmdsoul(GLAD_SOUL);
    obp->update_hooks();
    obp->catch_tell("Hail, oh Gladiator!\n");
}

int
query_guild_keep_player(object ob)
{
    setuid(); seteuid(getuid());
    ob->add_subloc("gladiator_subloc", this_object());
    set_alarm(1.0, 0.0, &check_glad(ob));
    return 1;
}

/* Function name: query_gladiator_level
 * Description:   Get the players numerical guild level
 * Returns:       The numeric guild level
 */
int
query_gladiator_level()
{
#ifdef LEVEL_BY_GUILD_STAT
    return shadow_who->query_base_stat(SS_OCCUP) / 5;
#else
    return shadow_who->query_base_skill(SS_GLAD_LEVEL);
#endif
}

/*
 * Function name: query_guild_title_occ
 * Description:   Gives the guild title.
 * Returns:       Guess what.
 */
string
query_guild_title_occ()
{
    int position = POSITION(shadow_who);
    int gender, cnslot;

    if(position >= 0 && position < sizeof(OVERSLOTS))
    {
        return capitalize(OVERSLOTS[position]) + GLAD_OVER_TITLE;
    }

	 if(CHECK_PUNISHMENT(shadow_who, PUN_TITLE))
	     return DISGRACED_TITLE;

    int stat = query_gladiator_level();
    int max_stat = sizeof((gender = shadow_who->query_gender()) == G_FEMALE ?
	  FEMALE_TITLES : MALE_TITLES) - 1;

	if (stat < 0)
	    stat = 0;
	else if (stat > max_stat)
	    stat = max_stat;

	return (gender == G_FEMALE ? FEMALE_TITLES[stat] :
	  MALE_TITLES[stat]) + GLAD_TITLE;
}

string
show_subloc(string subloc, object me, object for_obj)
{
    if (subloc != "gladiator_subloc")
	return shadow_who->show_subloc(subloc, me, for_obj);

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    return (for_obj == me ? "You have" : CAP(me->query_pronoun()) +
      " has") + " the brutal scars of a Gladiator.\n";
}


/* Function name: query_guild_skill_name
 * Description:   When a players uses the skills command he should get the
 *                the skill names, not the 'special' string.
 * Arguments:     type - the number of the skill
 * Returns:       0 if no skill of mine, else the string.
 */
mixed
query_guild_skill_name(int type)
{
    switch(type)
    {
    case SS_CHARGE:
	return "charge";
    case SS_BERSERK:
	return "berserk";
    case SS_GLAD_COMPARE:
	return "gcompare";
    case SS_GLAD_LEVEL:
	return "";
    default:
	return 0;
    }
}

varargs void
kick_out_glad(int spare)
{
    object cuir;
    string str;
    int i;

    CLEAR_GBIT(shadow_who, GLAD_MEMBER);

    while(cuir = present(CUIR_ID, shadow_who))
	cuir->remove_object();

    shadow_who->remove_cmdsoul(GLAD_SOUL);
    shadow_who->update_hooks();

    SET(SS_BERSERK, 0);
    SET(SS_CHARGE, 0);
    SET(SS_GLAD_COMPARE, 0);
    SET(SS_GLAD_LEVEL, 0);

    if(!shadow_who->query_wiz_level() &&
      extract(str = shadow_who->query_real_name(), -2) != "jr")
    {
	WRITE_LOG(LOG_QUIT, shadow_who, "has just left the guild.");
    }

    MANAGER->remove_member(str);
    MANAGER->remove_overseer(str);

    shadow_who->catch_tell("You are no longer a Gladiator of Athas.\n");    

    shadow_who->clear_guild_stat(SS_OCCUP);
    // Only clear the default start location if it's set to the gladiators
    if (shadow_who->query_default_start_location() == START_ROOM)
    {
        shadow_who->set_default_start_location(shadow_who->query_def_start());
    }

    if(!spare)
	MANAGER->snuff_gladiator(shadow_who);

    remove_guild_occ();
}

#ifndef LEVELS_BY_GUILD_STAT
int 
set_skill(int skill, int level)
{
    if (skill == SS_GLAD_LEVEL && !IS_WIZ(previous_object()) && 
      !previous_object()->query_glad_challenge())
	return 0;

    return shadow_who->set_skill(skill, level);
}
#endif
