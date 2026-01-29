/*********************************************************************
 * - bathing.c                                                     - *
 * - These are some routines to let you add bathing into           - *
 * - a room. To get this to work, you need to:                     - *
 * -                                                               - *
 * - Include this file.                                            - *
 * - At the end of your long desc,                                 - *
 * - Add a call to seat_desc() (optional)                          - *
 * - Create an add_item and point it to bath_desc() (optional)     - *
 * - Add init_bath() into your init() function. (create if needed) - *
 * - Will allow more than one bathing or bathing in a room         - *
 * -                                                               - *
 * - Created by Damaris 10/2005                                    - *
 * - Adapted from Lucius seating code which was modified by Valen  - *
 *********************************************************************/

#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

#define SUBLOC	"_subloc_sitting"
#define LIVE_I_DIRTY   "_live_i_dirty"   /* how dirty is the player? */
#define IN_WATER       "in_water"        /* living is in water       */ 

/*********************************************************************
 * This holds our data                                               *
 * Went with a mapping instead of props for ease of use and speed.   *
 *                                                                   *
 * mapping bathed = ([                                               *
 *     <player> : ({ <int 1|2|3>, <0|player>, <int type>, }),        *
 *                   ])                                              *
 *                                                                   *
 * 1 = bathing.                                                      *
 * 2 = bathing with player in lap.                                   *
 * 3 = bathing in players lap.                                       *
 *                                                                   *
 * type - bathing type used by a player                              *
 *                                                                   *
 *********************************************************************/

#define SDESC \
"A remarkably generous tub dominates the center of this spacious "+ \
"room yet allows space for a couple of wooden benches.\n"

mixed sdef = ({
({
({"tub","in tub"}),
"You step into the generous tub then sit back and relax.\n",
" steps into the generous tub then sits back relaxing.\n",
"You arise from the generous tub.\n",
" arises from the generous tub.\n",
"You are bathing comfortably in a generous tub.\n",
"You arise from the generous tub and leave the room.\n",
" bathing comfortably in a generous tub",
" bathing comfortably in a generous tub.\n",
}),

({
({"bench","on bench", "on wooden bench"}),
"You sit down on one of the benches.\n",
" sits on one of the benches.\n",
"You arise from your bench.\n",
" arises from one of the bench.\n",
"You are sitting comfortably on one of the benches.\n",
"You arise from your bench and leave the room.\n",
" sitting comfortably on one of the benches",
" sitting comfortably on one of the benches.\n",
})

});

private mapping bathed = ([]);

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (ob && !present(ob) && bathed[ob])
    {
	ob->catch_tell(sdef[bathed[ob][2]][6]);
	ob->unset_no_show_composite();
	ob->remove_subloc(SUBLOC);

	if (bathed[ob][0] == 2 && (to = bathed[ob][1]))
	{
	    bathed = m_delete(bathed, to);
	    to->unset_no_show_composite();
	    to->catch_tell("You are dumped onto the hard wooden "+
	      "floor.\n");
	    tell_room(this_object(), QCTNAME(to) + " is dumped " +
	      "onto the hard wooden floor.\n", to);
	}

        if (bathed[ob][0] == 3)
        {
            bathed[bathed[ob][1]] = ({1,0,bathed[bathed[ob][1]][2]});
        }

	bathed = m_delete(bathed, ob);
    }
}

public int
do_sit(string str)
{
    object *obs, ob;
    int i;
    
    if (bathed[this_player()])
    {
	return notify_fail("But you are already sitting!\n");
    }

    if(str == "down")
        i = random(sizeof(sdef));
    else
    {    
        i = -1;
        while( ++i < sizeof(sdef) && member_array(str, sdef[i][0]) == -1 );
    }
    
    if (i == sizeof(sdef) &&
	!sizeof(obs = FIND_STR_IN_ARR(str, m_indexes(bathed)))) 
    {
	return notify_fail(capitalize(query_verb()) + " where?\n");
    }

    if (sizeof(obs))
    {
	if (sizeof(obs) > 1)
	{
	    return notify_fail("You may only sit in one lap at a time.\n");
	}

	if (objectp(ob = bathed[obs[0]][1]))
	{
	    return notify_fail(QCTPNAME(obs[0]) + " lap is already " +
		"occupied.\n");
	}

	bathed[this_player()] = ({ 3, obs[0], bathed[obs[0]][2] });
	bathed[obs[0]] = ({ 2, this_player(), bathed[obs[0]][2] });
	TP->add_prop(IN_WATER,1);
	this_player()->catch_msg(
	    "You climb onto " + QTPNAME(obs[0]) + " lap.\n");
	obs[0]->catch_tell(this_player()->query_The_name(obs[0]) +
	  " climbs onto your lap.\n");
	say(QCTNAME(this_player()) + " climbs onto " + QTPNAME(obs[0]) +
	  " lap.\n", ({ obs[0], this_player() }));
    }
    else
    {
	bathed[this_player()] = ({ 1, 0, i });
	TP->add_prop(IN_WATER,1);
	write(sdef[i][1]);
	say(QCTNAME(this_player())+ sdef[i][2]);
    }

    this_player()->set_no_show_composite(1);
    this_player()->add_subloc(SUBLOC, this_object());
    return 1;
}

public int
do_stand(string arg)
{
    object ob;
    mixed tmp;

    if (arg != "up")
    {
	return notify_fail("Stand up, maybe?\n");
    }

    if (!pointerp(tmp = bathed[this_player()]))
    {
	return notify_fail("But you are not sitting!\n");
    }

    this_player()->unset_no_show_composite();
    this_player()->remove_subloc(SUBLOC);
	TP->add_prop(IN_WATER,0);
    if (tmp[0] == 3 && objectp(ob = tmp[1]))
    {
	this_player()->catch_msg(
	    "You climb off of " + QTPNAME(ob) + " lap.\n");
	ob->catch_tell(this_player()->query_The_name(ob) + " climbs off "+
	  "of your lap.\n");
	say(QCTNAME(this_player()) + " climbs off of " + QTPNAME(ob) +
	  " lap.\n", ({ this_player(), ob }));

	bathed[ob] = ({ 1, 0, bathed[ob][2]});
    }
    else
    {
	write(sdef[tmp[2]][3]);
	say(QCTNAME(this_player()) + sdef[tmp[2]][4]);

	if (tmp[0] == 2 && objectp(ob = tmp[1]))
	{
	    ob->unset_no_show_composite();
	TP->add_prop(IN_WATER,0);
	    ob->catch_tell("You are dumped onto the hard wooden floor.\n");
	    tell_room(this_object(), QCTNAME(ob) + " is dumped "+
	      "onto the hard wooden floor.\n", ob);

	    bathed = m_delete(bathed, ob);
	}
    }
    bathed = m_delete(bathed, this_player());
    return 1;
}

public string
bath_desc()
{
    object *obs = ({}), m;
    string *who = ({}), str;
    int i, j, k, l;

    str = SDESC;

    obs = m_indexes(bathed) - ({ 0 });
    j = sizeof(obs);

    if (j < 1)
	return str;


    k = -1;
    
    while( ++k < sizeof(sdef))
    {
    
    who = ({});
    i = -1;
    l = 0;
         
    while (++i < j)
    {
        if (bathed[obs[i]][2] != k) continue;

        l++;
        
	if (bathed[obs[i]][0] > 2) continue;

        m = obs[i];
         
	if (bathed[obs[i]][0] == 2)
	{
	    object ob = bathed[obs[i]][1];

	    if (obs[i] == this_player())
	    {
		who += ({ "yourself with " +
		    ob->query_the_name(this_player()) + " on your lap" });
	    }
	    else
	    {
		who += ({ obs[i]->query_the_name(this_player()) +
		    " with " + (ob == this_player() ? "you" : 
		     ob->query_the_name(this_player())) +
		     " on "+ 
		     obs[i]->query_possessive() +" lap" });
	    }
	    continue;
	}

	if (obs[i] == this_player())
	{
	    who += ({ "yourself" });
	}
	else
	{
	    who += ({ obs[i]->query_the_name(this_player()) });
	}
    }

    if ((l == 1) && (m == this_player()))
	str += sdef[k][5];
    else if(l > 0) str += capitalize(COMPOSITE_WORDS(who)) + (l == 1 ? 
	" is" : " are") + sdef[k][8];
    }
  return str;
}

nomask string
show_subloc(string subloc, object on, object for_ob)
{
    string str;
    mixed tmp;

    if (on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS) || subloc != SUBLOC)
	return "";

    if (!pointerp(tmp = bathed[on]))
	return "";

    if (for_ob == on)
	str = "You are";
    else
	str = capitalize(on->query_pronoun()) + " is";

    if (tmp[0] < 3)
    {
	str += sdef[tmp[2]][7];
	if (objectp(tmp = tmp[1]))
	{
	    str += " with " + (tmp == for_ob ? "you" :
	      tmp->query_the_name(on) ) + " on " +
	    (for_ob == on ? "your" : on->query_possessive()) +" lap";
	}
	return str + ".\n";
    }

    if (tmp[1] == for_ob)
	return str + " on your lap.\n";

    return str + " on " + 
        tmp[1]->query_the_name(for_ob) + "'s lap.\n";
}

void
init_bathing()
{
	add_action(  do_sit,  "sit"   );
	add_action( do_stand, "stand" );
}
