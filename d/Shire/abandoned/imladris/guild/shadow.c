/*
 *  The Spellmaster-guild shadow
 *
 */

inherit "/std/guild/guild_occ_sh";

#include "/sys/ss_types.h"
#include "/sys/stdproperties.h"
#include "/sys/const.h"
#include "/sys/language.h"
#include "defs.h"
#include "guild.h"
#include "lists.h"
#include "/d/Shire/skills.h"

#define FOOBAR setuid(); seteuid(getuid())
#define PO previous_object()
#define SPELLMASTER_SUBLOC "_spellmaster_subloc_"

/* Saved variables. */

int *spell_list_ids;   /* A list over known spell lists. */
int *spell_list_exp;   /* Experience obtained in each spell list. */
int *spell_list_learn; /* How big a fraction each spell list should take? */
int chanting_time;     /* How long chanting time? */
int relative_chanting; /* Relative to normal time? */

static object me;

string query_guild_style_occ() { return GUILD_STYLE; }
string query_guild_name_occ()  { return GUILD_NAME; }

object
qme()
{
    return me;
}

/*
 * Called from shadow_me to set guild pref.
 */
query_guild_tax_occ()
{
    int tax = GUILD_BASE_TAX;
    //int i;

    // This has to change.

    //for(i=0;i<sizeof(spell_list_ids);i++)
	//tax += LIST_TAX[spell_list_ids[i]];
	tax += 33;
    return tax;
}

/*
 * Function name: query_guild_keep_player
 * Description:   Test if we want to keep the player in the guild.
 *                If we discover a goblin we will keep him, just to throw him
 *                out the proper way later.
 * Arguments:     ob - the player.
 * Returns:       1 if keeping, 0 if not.
 */
int
query_guild_keep_player(object ob)
{
    ob->add_subloc(SPELLMASTER_SUBLOC, this_object());
    return 1;
}

/*
 * Keep our guild tax updated
 */
query_learn_pref(int stat)
{
    int val, *learn_pref;

    if (stat == SS_OCCUP)
	return query_guild_tax_occ();

    if (stat == -1)
    {
	learn_pref = query_shadow_who()->query_learn_pref(-1);
	learn_pref[SS_OCCUP] = query_guild_tax_occ();
	return learn_pref;
    }
    return query_shadow_who()->query_learn_pref(stat);
}

int
query_spell_level()
{
    object who; 
	int stat;
		who = query_shadow_who();  
		stat = (who->query_base_stat(SS_OCCUP)/4 + 1);
    	return stat;
}

/***************************************************************************
 *
 *   Spellmaster-specific stuff
 *
 * Ideas for titles:
 *
 *   Tiro Guardian of Heavens.
 *
 *   Title dependant on the best spell list.
 */

#define SUB_TITLE \
   ({ "Adept", "Gleaming", "Valiant", "Exalted", "Most Exalted", \
      "Great", "Brilliant", "Glorious", "Golden", "Sparkling" })

#define TITLE ({ \
    "Hope", "Light", "Fire", "Jewel", "Star", \
    "Star of Hope", "Star-Light", "Star of Radiance", \
    "Star-Fire", "Star-Jewel", "Star-Dome" })

string
title(int stat)
{
    if (stat >= 110)
	stat = 110;

    return SUB_TITLE[stat%10] + " " + TITLE[stat/10];
}

/*
 * A fancy title.
 */
query_guild_title_occ()
{
    int stat;
    object who;
    string o_title;

    who = query_shadow_who();

    //o_title = who->query_title();

    /* Wizards get to keep their own title */
    if (who->query_wiz_level())
	return who->query_title();

    stat = who->query_base_stat(SS_OCCUP);

    if (stat < 1)
	stat = 1;

    if (stat <= 100)

    if (!strlen(o_title))
	return title(stat) + " of Imladris";
    else
	return o_title + " and " + title(stat) + " of Imladris";
}

int
is_member()
{
    return 1;
}


#define PROUDNESS ({ \
    "novice", "fresh", "developing", "adept", "known", "widely known", \
    "grand", "major", "superb", "extra-ordinary" })

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *                me      - I
 *                for_obj - The looker
 * Returns:       The string the looker shall see
 */
string
show_subloc(string subloc, object who, object for_obj)
{
   string str;
    int tmp;

   if (subloc != SPELLMASTER_SUBLOC)
      return query_shadow_who()->show_subloc(subloc, who, for_obj);

   if (who->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";

   if (for_obj == who)
      str = "You are ";
   else
      str = capitalize(who->query_pronoun()) + " is ";

   if (who->query_wiz_level())
      str += "a master";
   else
   {
      tmp = who->query_base_stat(SS_OCCUP) / 10;
      if (tmp > 9)
	tmp = 9;
      str += LANG_ADDART(PROUDNESS[tmp]);
   }

   return str + " Healer of Imladris.\n";
}

void
init_occ_shadow(string arg)
{
    string name, fname;

    seteuid(getuid());

    me = query_shadow_who();
    name = me->query_real_name();

    fname = PL_SAVE + name;

    restore_object(fname);
}

void
init_spell_souls()
{
    int i;
    setuid(); seteuid(getuid());

    query_shadow_who()->add_cmdsoul(GUILD_SOUL);

    for(i=0;i<sizeof(spell_list_ids);i++)
	if (catch(query_shadow_who()->
                add_cmdsoul(LIST_FILES[spell_list_ids[i]])))
	    log_file("guild.ERR",
		CAP(query_shadow_who()->query_real_name())+" got : "+
		"Could not load: "+LIST_FILES[spell_list_ids[i]]+"\n");

    query_shadow_who()->update_hooks();
}

int
save_character()
{
    string name;

    query_shadow_who()->save_character();

    name = me->query_real_name();
    save_object(PL_SAVE + name);
    return 1;
}

/*
 * remove_all_sula_stuff
 *
 * Remove all stuff, shadows, souls, autoloading objects...
 */
static nomask void
remove_all_sula_stuff()
{
    object guildob;
    string name, data;

    me->clear_bit(1, 0);   /* Clear the guild bit. */

    me->remove_autoshadow(GUILD_SHADOW+":");
    me->remove_cmdsoul(GUILD_SOUL);

    name = me->query_real_name();
    save_character();
    data = read_file(PL_SAVE + name + ".o");
    write_file(PL_SAVE + name + ".o.old", data);
    rm(PL_SAVE + name + ".o");
    guildob = present("_sula_imladris_", me);
    if (objectp(guildob))
	guildob->remove_object();
}

/*
 * remove_member
 *
 * Remove everything. Can only be executed from the soul object.
 */
void
remove_member()
{
/*
    if (function_exists("query_cmdlist", PO) != GUILD_SOUL)
	return;
*/
    remove_all_sula_stuff();
    ::remove_shadow();
}

void
resolve_exp(int val)
{
    int i, sum = 0;
    for(i=0;i<sizeof(spell_list_learn);i++)
	sum += spell_list_learn[i];
    if(sum==0)
	return;

    log_file("guild.log", ctime(time())+
	":EXP:"+query_shadow_who()->query_name()+":\n");
    for(i=0;i<sizeof(spell_list_exp);i++) {
	spell_list_exp[i] += val*spell_list_learn[i]/sum;
	log_file("guild.log",
	    sprintf("%2d = %4d (%d/%d) ",
	    spell_list_ids[i], val*spell_list_learn[i]/sum,
	    spell_list_learn[i], sum));
    }
    log_file("guild.log", "\n");
}

void
add_exp(int e, int battle)
{
    int old_exp;
    string name;

    shadow_who->catch_msg("Elrond's appearance forms in front of you!\n");
    old_exp = shadow_who->query_acc_exp(SS_OCCUP);
    shadow_who->add_exp(e, battle);
    shadow_who->catch_msg("Elrond says: Greetings! Nicely done!\n");
    resolve_exp(shadow_who->query_acc_exp(SS_OCCUP) - old_exp);

    name = me->query_real_name();
    save_object(PL_SAVE + name);
    shadow_who->catch_msg("Elrond's appearance disappears.\n");
}

void
learn_spell_list(int index)
{
    if(member_array(index, spell_list_ids)>=0)
	return;
    if(!sizeof(spell_list_ids))
    {
	spell_list_ids = ({ index });
	spell_list_exp = ({ 0 });
	spell_list_learn = ({ 100 });
    }
    else
    {
	spell_list_ids += ({ index });
	spell_list_exp += ({ 0 });
	spell_list_learn += ({ 100 });
    }
    init_spell_souls();
}

int
forget_spell_list(int spell_ind)
{
    int i;
    if((i=member_array(spell_ind, spell_list_ids))==-1)
	return 0;

    spell_list_ids = exclude_array(spell_list_ids, i, i);
    spell_list_exp = exclude_array(spell_list_exp, i, i);
    spell_list_learn = exclude_array(spell_list_learn, i, i);
}

int *
query_spell_list_ids()
{
    return spell_list_ids;
}

int *
query_spell_list_exp()
{
    return spell_list_exp;
}

int *
query_spell_list_learn()
{
    return spell_list_learn;
}

void
set_spell_list_learn(int *to_what)
{
    spell_list_learn = to_what;
}

/*
 * Function name:   set_chanting_time
 * Arguments:	    time
 */
void
set_chanting_time(int time)
{
    chanting_time = time;
}

/*
 * Function name:   query_chanting_time
 * Returns:	    The set casting time.
 */
int
query_chanting_time()
{
    return chanting_time;
}

/*
 * Function name:   set_relative_chanting_time
 * Arguments:	    1 - Relative to normal.
 *		    0 - Absolute time.
 */
void
set_relative_chanting_time(int rel)
{
    relative_chanting = rel;
}

/*
 * Function name:   query_relative_chanting_time
 * Returns:	    If relative chanting time.
 */
int
query_relative_chanting_time()
{
    return relative_chanting;
}

string
query_guild_skill_name(int type)
{
	if (type == SS_FUMBLE)
		return "fumble";
	shadow_who->query_guild_skill_name(type);
}

