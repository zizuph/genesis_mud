/* This is a basfile to inherit into all chapels/churches/
 * prayerrooms of the good gods in Krynn. It is intended
 * to give knights (maybe others later on as well?) the
 * opportunity to relearn spells. The knight spell system
 * is based on the assuption that once you have used
 * a spell, you tend to forget it. To regain the spell, the
 * knight must meditate on the spell again and relearn it.
 * This should be possible only in special rooms, and these
 * should be chapels devoted to the good gods of Krynn.
 *
 * The command to learn a spell again is 'focus on <spell name>'
 * Obviously it will take some time to learn the spell,
 * and the player will be in some kind of trance in between.
 * The time to learn depends on the difficulty of the spell.
 *
 *
 * created by Aridor, 06/95
 *
 *
 * To use this code in a room, you have to do the following 2 things:
 *    - inherit this file into the room (in addition to other inherits
 *                                       you already have there).
 *    - define the function init() like this:
 *
 *       void
 *       init()
 *       {
 *            init_chapel();
 *            ::init();
 *       }
 *
 *       or add the line 'init_chapel();' to an existing init() function.
 */

#include <macros.h>


void
init_chapel()
{
    add_action("focus","focus");
    add_action("focus", "contemplate");
}

/* returns an id number */
int
allowed_to_focus_here(object who)
{
    /* Player is a knight */
    if (who->query_guild_member("Solamnian Knights"))
      return 1;

    /* Anyone else? Please add here. */
    /* if (...) return 2; */

    /* The rest shouldn't! */
    return 0;
}

string *
query_all_spells(object who)
{
    int i;
    string *spls = ({});
    object *objs = who->query_spellobjs();
    for(i=0;i<sizeof(objs);i++)
      spls += m_indexes(objs[i]->query_cmdlist());

    return spls;
}

int
start_focus(object who, string spl, int id)
{
    int tme = -1;
    string find;
    object spell_obj;
    object para;
    
    /* depending on the id number of the player, the correct spell
     * object is searched for.
     */
    if (id == 1) /* a knight */
      find = "solamnian_spells";
    else
      return -1;
    spell_obj = present(find, who);
    if (!spell_obj)
      return -1;
    
    if (id == 1) /* a knight */
      tme = spell_obj->spell_meditate_time(spl);
    if (tme == 0)
      return -1;
    
    who->catch_msg("You offer a prayer to Paladine to grant you " +
		   "wisdom. Then you start to focus on '" + spl + "'.\n");
    tell_room(this_object(),
	      QCTNAME(who) + " starts to meditate.\n", who);
    /* clone a paralyze here that paralyzes for 'tme' seconds */
    
    seteuid(getuid(this_object()));
    para = clone_object("/std/paralyze");
    para->set_standard_paralyze("meditating");
    para->set_stop_fun("break_focus");
    para->set_remove_time(tme);
    para->move(who,1);
    return tme;
}


varargs int
break_focus(mixed arg)
{
    int i;
    mixed *calls = get_all_alarms();

    if (!objectp(arg))
      for(i=0;i < sizeof(calls); i++)
	if (calls[i][1] == "end_focus" &&
	    calls[i][4][0] == this_player())
	  {
	      remove_alarm(calls[i][0]);
	      break;
	  }
    return 0;
}

void
end_focus(object who, string spl, int id)
{
    string find;
    object spell_obj;

    /* Player ld'd? */
    if (!who)
      return;

   /* depending on the id number of the player, the correct spell
     * object is searched for.
     */
    if (id == 1) /* a knight */
      find = "solamnian_spells";
    else
      return;
    
    spell_obj = present(find, who);
    if (!spell_obj)
      return;
    
    tell_room(this_object(),
	      QCTNAME(who) + " rises from a deep trance.\n", who);
    if (id == 1) /* a knight */
      {
	  if (spell_obj->recharge_knight_spell(spl))
	    who->catch_msg("Having rehearsed and recollected your spell '" +
			   spl + "' you get up relaxed and more " +
			   "knowledgable.\n");
	  else
	    who->catch_msg("You fail at your task of rehearsing and " +
			   "recollecting your spell '" + spl + "'. You get " +
			   "up, more relaxed.\n");
	  
	  if (who->query_prop("_knight_i_devotion") < who->query_age() + 1000)
	    who->add_prop("_knight_i_devotion", who->query_age() + 1000);
      }
}

int
focus(string str)
{
    string spl;
    int tme, spell_type;

    /* Command is not present for anyone else */
    notify_fail("What?\n");
    spell_type = allowed_to_focus_here(this_player());
    if (!spell_type)
      return 0;

    notify_fail("Focus on what?\n");
    if (!str)
      return 0;
    
    if (sscanf(str, "on %s", spl) != 1)
      return 0;

    notify_fail("Focus on what? No such spell found.\n");
    if (member_array(spl, query_all_spells(this_player())) < 0)
      return 0;

    tme = start_focus(this_player(), spl, spell_type);
    if (tme < 0)
      write("There is no need to focus on " + spl + ".\n");
    else
      set_alarm(itof(tme),0.0,"end_focus",this_player(), spl, spell_type);
    return 1;
}
