/*********************************************************************
 * - seated2.c                                                     - *
 * - These are some routines to let you add sitting into           - *
 * - a room. To get this to work, you need to:                     - *
 * -                                                               - *
 * - Include this file.                                            - *
 * - At the end of your long desc,                                 - *
 * - Add a call to seat_desc() (optional)                          - *
 * - Create an add_item and point it to seat_desc() (optional)     - *
 * - Add init_seat() into your init() function. (create if needed) - *
 * - Will allow more than one sitting or seating in a room         - *
 * -                                                               - *
 * - Created by Damaris 12/2001                                    - *
 * - Adapted from Lucius seating code which was modified by Valen  - *
 *********************************************************************/

#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

#define SUBLOC	"_subloc_sitting"
 
/*********************************************************************
 * This holds our data                                               *
 * Went with a mapping instead of props for ease of use and speed.   *
 *                                                                   *
 * mapping seated = ([                                               *
 *     <player> : ({ <int 1|2|3>, <0|player>, <int type>, }),        *
 *                   ])                                              *
 *                                                                   *
 * 1 = sitting.                                                      *
 * 2 = sitting with player in lap.                                   *
 * 3 = sitting in players lap.                                       *
 *                                                                   *
 * type - seating type used by a player                              *
 *                                                                   *
 *********************************************************************/

#define SDESC \
"A large fur is placed before the fireplace with chairs scattered "+ \
"around it.\n"

mixed sdef = ({
({
({"fur","on fur", "in fur"}),
"You slip down onto the fur and sit before the fire.\n",
" slips down onto the fur and sits before the fire.\n",
"You arise from the soft fur.\n",
" arises from the soft fur.\n",
"You are sitting comfortably on the fur before the fire.\n",
"You slides off the fur and sits before the fire.\n",
" sitting comfortably on the fur before the fire",
" sitting comfortably on the fur before the fire.\n",
}),

({
({"chair","in chair", "on chair"}),
"You sit down on one of the chairs.\n",
" sits on one of the chairs.\n",
"You arise from your chair.\n",
" arises from one of the chairs.\n",
"You are seated comfortably on one of the chairs.\n",
"You arise from your chair and leave the room.\n",
" sitting comfortably on one of the chairs",
" sitting comfortably on one of the chairs.\n",
})

});

private mapping seated = ([]);

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (ob && !present(ob) && seated[ob])
    {
	ob->catch_tell(sdef[seated[ob][2]][6]);
	ob->unset_no_show_composite();
	ob->remove_subloc(SUBLOC);

	if (seated[ob][0] == 2 && (to = seated[ob][1]))
	{
	    seated = m_delete(seated, to);
	    to->unset_no_show_composite();
	    to->catch_tell("You are dumped unceremoniously onto the "+
	      "floor.\n");
	    tell_room(this_object(), QCTNAME(to) + " is dumped " +
	      "unceremoniously onto the floor.\n", to);
	}

        if (seated[ob][0] == 3)
        {
            seated[seated[ob][1]] = ({1,0,seated[seated[ob][1]][2]});
        }

	seated = m_delete(seated, ob);
    }
}

public int
do_sit(string str)
{
    object *obs, ob;
    int i;
    
    if (seated[this_player()])
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
	!sizeof(obs = FIND_STR_IN_ARR(str, m_indexes(seated)))) 
    {
	return notify_fail(capitalize(query_verb()) + " where?\n");
    }

    if (sizeof(obs))
    {
	if (sizeof(obs) > 1)
	{
	    return notify_fail("You may only sit in one lap at a time.\n");
	}

	if (objectp(ob = seated[obs[0]][1]))
	{
	    return notify_fail(QCTPNAME(obs[0]) + " lap is already " +
		"occupied.\n");
	}

	seated[this_player()] = ({ 3, obs[0], seated[obs[0]][2] });
	seated[obs[0]] = ({ 2, this_player(), seated[obs[0]][2] });

	this_player()->catch_msg(
	    "You climb onto " + QTPNAME(obs[0]) + " lap.\n");
	obs[0]->catch_tell(this_player()->query_The_name(obs[0]) +
	  " climbs onto your lap.\n");
	say(QCTNAME(this_player()) + " climbs onto " + QTPNAME(obs[0]) +
	  " lap.\n", ({ obs[0], this_player() }));
    }
    else
    {
	seated[this_player()] = ({ 1, 0, i });
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

    if (!pointerp(tmp = seated[this_player()]))
    {
	return notify_fail("But you are not sitting!\n");
    }

    this_player()->unset_no_show_composite();
    this_player()->remove_subloc(SUBLOC);

    if (tmp[0] == 3 && objectp(ob = tmp[1]))
    {
	this_player()->catch_msg(
	    "You climb off of " + QTPNAME(ob) + " lap.\n");
	ob->catch_tell(this_player()->query_The_name(ob) + " climbs off "+
	  "of your lap.\n");
	say(QCTNAME(this_player()) + " climbs off of " + QTPNAME(ob) +
	  " lap.\n", ({ this_player(), ob }));

	seated[ob] = ({ 1, 0, seated[ob][2]});
    }
    else
    {
	write(sdef[tmp[2]][3]);
	say(QCTNAME(this_player()) + sdef[tmp[2]][4]);

	if (tmp[0] == 2 && objectp(ob = tmp[1]))
	{
	    ob->unset_no_show_composite();

	    ob->catch_tell("You are dumped unceremoniously "+
	      "onto the floor.\n");
	    tell_room(this_object(), QCTNAME(ob) + " is dumped "+
	      "unceremoniously onto the floor.\n", ob);

	    seated = m_delete(seated, ob);
	}
    }
    seated = m_delete(seated, this_player());
    return 1;
}

public string
seat_desc()
{
    object *obs = ({}), m;
    string *who = ({}), str;
    int i, j, k, l;

    str = SDESC;

    obs = m_indexes(seated) - ({ 0 });
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
        if (seated[obs[i]][2] != k) continue;

        l++;
        
	if (seated[obs[i]][0] > 2) continue;

        m = obs[i];
         
	if (seated[obs[i]][0] == 2)
	{
	    object ob = seated[obs[i]][1];

	    if (obs[i] == this_player())
	    {
		who += ({ "yourself with " +
		    ob->query_the_name(this_player()) +		   " snuggled up on your lap" });
	    }
	    else
	    {
		who += ({ obs[i]->query_the_name(this_player()) +
		    " with " + (ob == this_player() ? "you" : 
		     ob->query_the_name(this_player())) +
		     " snuggled up on "+ 
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

    if (!pointerp(tmp = seated[on]))
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
	      tmp->query_the_name(on) ) + " snuggled up on " +
	    (for_ob == on ? "your" : on->query_possessive()) +" lap";
	}
	return str + ".\n";
    }

    if (tmp[1] == for_ob)
	return str + " snuggled up on your lap.\n";

    return str + " snuggled up on " + 
        tmp[1]->query_the_name(for_ob) + "'s lap.\n";
}

void
init_seat()
{
    add_action(  do_sit,  "sit"   );
    add_action( do_stand, "stand" );
}
