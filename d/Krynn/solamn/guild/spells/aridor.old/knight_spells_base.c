/*
 * The spellobject for the knights. All sword and rose knights
 * receive the same object, but are allowed to learn only
 * specific spells. Only the check, consider and radiance spell are
 * always castable without learning.
 *
 * Note that the knights don't have spells when they enter the
 * game and have to recollect theirs before they can go
 * adventuring.
 *
 * The recharging of a spell is equivalent to having to use a
 * material component. I suggest this is taken into account
 * when calculating tax.
 *
 * A spell can be recharged up to a number of
 * (40*player_wis/spell_prestige+1). This means
 * that a player can use the spell this many times before having
 * to come back to the spur to recharge. It is possible to use
 * a spell more often without recharging, but a penalty in
 * prestige is charged.
 */

#include "/d/Krynn/common/defs.h"
#include "../../guild.h"
#include "local.h"

inherit SPELLCAST_BASE;

#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>
#include <tasks.h>
#include <cmdparse.h>

/*contains the number of times this spell is castable without penalty */
mapping spell_avail = ([]);

/*contains the prestige penalty for this spell if cast beyond availability */
mapping spell_penalty = ([]);

/* temporary variable. is set at casting of a spell and remains constant
 * during the entire casting process.
 */
int temp_spell_availability = 0;

/* redefinition to allow check_calls! */
void
list_spells()
{
    int i;
    string space;
    string str;
    
    space = "                                                 ";
    for (i = 0 ; i < sizeof(verb_list) ; i++)
      {
	  str = check_call(name_list[i]);
	  write(verb_list[i] + extract(space, 0, 17 - strlen(verb_list[i])) +
		str + extract(space, 0, 31 - strlen(str)) + "\n");
      }
}

void
add_knight_spell(int avail, int penalty, string verb, string func, string name)
{
    if (!spell_avail)
      spell_avail = ([]);
    spell_avail += ([verb:avail]);
    if (!spell_penalty)
      spell_penalty = ([]);
    spell_penalty += ([verb:(penalty > 10000 ? 10000 : penalty)]);
    add_spell(verb, func, name);
}


void
create_knight_spells()
{
}

void
create_spells()
{
    set_name(SPELL_OB_NAME);
    set_no_show();
    
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_I_VOLUME, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    
    create_knight_spells();

    add_knight_spell(0, 0,"consider",   "do_consider",
		     "Consider [enemy].");
    /* Consider is the only spell EVERY knight will get */
}

/* Common code used by all spells. */

/* spell_availability: check if this spell can be cast without penalty.
 * Returns: a negative number if spell cannot be cast at all!
 *          0 if no penalty and ok to cast spell.
 *          a positive number as the amount of prestige to charge
 *               for using this spell
 */
int
spell_availability(string the_spell)
{
    int avail = spell_avail[the_spell];
    int possible = (member_array(the_spell,m_indexes(spell_avail)) > -1);

    /* Not allowed to cast this spell */
    if (!possible)
      return -1;
    
    if (avail > 0)
      return 0;
    else
      spell_avail[the_spell] = 0;
    return spell_penalty[the_spell];
}

/* if the spell was cast (successful or not!), call this to
 * reduce availability. Don't reduce if the spell failed due
 * to typos or something.
 */
int
reduce_spell_availability(string the_spell)
{
    int avail = spell_avail[the_spell];
    int possible = (member_array(the_spell,m_indexes(spell_avail)) > -1);

    /* Not allowed to cast this spell */
    if (!possible)
      return -1;
    
    if (avail > 0)
      spell_avail[the_spell]--;
    if (avail > 0)
      return 0;
    else
      spell_avail[the_spell] = 0;
    return spell_penalty[the_spell];
}

/* this is a check whether the spell has been rehearsed.
 * If it has, the function will return the string: 'rehearsed'
 * otherwise it'll return 'unrehearsed'.
 */
string
spell_avail_string(string the_spell)
{
    int avail = spell_avail[the_spell];
    int possible = (member_array(the_spell,m_indexes(spell_avail)) > -1);

    /* Not allowed to cast this spell */
    if (!possible)
      return "not available";
    
    if (avail > 0)
      return "rehearsed";

    return "unrehearsed";
}

/* spell_meditate_time: give the number (in seconds) needed to relearn the
 *                      spell.
 * Returns: a positive number (seconds) if the spell needs to be learned,
 *          else 0.
 */
int
spell_meditate_time(string the_spell)
{
    return spell_penalty[the_spell] / 200;
}

/* recharge a spell, returns 1 if the spell was recharged, and 0 if it was
 * impossible to recharge the spell.
 */
int
recharge_knight_spell(string spell)
{
    if (member_array(spell,m_indexes(spell_avail)) < 0)
      return 0;
    if (spell_avail[spell] < (40*environment(this_object())->query_stat(SS_WIS)/
			      spell_penalty[spell]+1))
      spell_avail[spell]++;
    else
      return 0;
    return 1;
}

/* Redefine the spell message for the knights */
int
query_spell_mess(string verb, string str)
{
    object pl = this_player();
    string mutter = call_other(TO, verb + "_mutter", str);

    tell_room(E(pl), QCTNAME(pl) + 
        " clasps a platinum medal in " + pl->query_possessive() + " fist " +
        "and mumbles a prayer under " + pl->query_possessive() + " breath.\n", pl); 
    pl->catch_msg("\nYou pray to Paladine and Kiri-Jolith, reciting the words:\n" +
        "\"In my hand your Symbol. In my heart the Oath.\nIn my memory the " +
        "Measure. Upon my lips this plea:\nPray " + mutter + ".\"\n\n");
    return 1;
}

/* Return 1 if the spell should fail */
int
start_spell_fail(string verb, string arg)
{
    object room;
    string no_magic_fail;
    int return_value;

    object pl = this_player();
    int    pres = spell_availability(verb);

    temp_spell_availability = pres;
    
    if (pres < 0)
      {
	  pl->catch_msg("You are not allowed to call upon this prayer. Having done so " +
			"nonetheless calls the wraith of the gods onto you!\n");
	  pl->heal_hp(-200);
	  return 1;
      }

    if (pres > 0)
      {
	  pl->catch_msg("You have strained the wrath of the gods to the limit " +
			"already. You lose some prestige.\n");
	  pl->change_prestige(-pres,1);
	  /* somehow reduce the chance that the spell succeeds in here */
	  if (random(pres) > random(10000))
	    {
		pl->catch_msg("You fail to recall the spell. You should rehearse it better before you try it again.\n");
		pl->add_mana(-20);
		return 1;
	    }
	  /* will this do?? */
      }
    
    if (!P("pal_med", pl))
      {
	  pl->catch_msg("You have no medal, you should seek guidance.\n");
	  return 1;
      }

    return ::start_spell_fail(verb, arg);
}

object *
my_area_of_effect(string str)
{
    object *list;

    if (!str)
      return 0;

    if (!parse_command(str, E(TP), "[the] %i", list))
      return 0;

    list = NORMAL_ACCESS(list,0,0);

    if (!list || !sizeof(list))
      return 0;
    return list;
}


/* Just include the code for each spell here at the end*/
#include SPELL_CONSIDER
