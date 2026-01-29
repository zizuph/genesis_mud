/*********************************************************************
 * - laying.c                                                      - *
 * - These are some routines to let you add laying into            - *
 * - a room. To get this to work, you need to:                     - *
 * -                                                               - *
 * - Include this file.                                            - *
 * - At the end of your long desc,                                 - *
 * - Add a call to lay_desc() (optional)                           - *
 * - Create an add_item and point it to lay_desc() (optional)      - *
 * - Add init_lay() into your init() function. (create if needed)  - *
 * - Will allow more than one laying or laying in a room           - *
 * -                                                               - *
 * - Created by Damaris 01/2005                                    - *
 * - Adapted from Lucius laying code which was modified by Valen   - *
 *********************************************************************/

#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

#define SUBLOC	"_subloc_laying"
 
/*********************************************************************
 * This holds our data                                               *
 * Went with a mapping instead of props for ease of use and speed.   *
 *                                                                   *
 * mapping lay = ([                                                  *
 *     <player> : ({ <int 1|2|3>, <0|player>, <int type>, }),        *
 *                   ])                                              *
 *                                                                   *
 * 1 = laying.                                                       *
 * 2 = laying with player in body.                                   *
 * 3 = laying in players body.                                       *
 *                                                                   *
 * type - laying type used by a player                               *
 *                                                                   *
 *********************************************************************/

#define SDESC \
"   Scattered along forming a circle around the fire pit are "+ \
"special cushions that blend so well with the grass that one "+ \
"can barely make out their presence.\n"

mixed sdef = ({
({
({"cushion","on cushion", "long cushion", "soft cushion"}),
"You sink down onto a long soft cushion before the fire.\n",
" sinks onto a long soft cushion before the fire.\n",
"You arise from a long soft cushion.\n",
" arises from a long soft cushion.\n",
"You are laying comfortably on a long soft cushion before the fire.\n",
"You arise from a long soft cushion and leave the area.\n",
" laying comfortably on a long soft cushion before the fire",
" laying comfortably on a long soft cushion before the fire.\n",
}),

({
({"grass","on grass"}),
"You lay down onto the soft grass.\n",
" lays onto the soft grass.\n",
"You arise from the soft grass.\n",
" arises from the soft grass.\n",
"You are laying comfortably stretched out on a blanket of soft grass.\n",
"You arise once you are ready and leave the area.\n",
" laying comfortably stretched out on a blanket of soft grass",
" laying comfortably stretched out on a blanket of soft grass.\n",
})

});

private mapping lay = ([]);

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (ob && !present(ob) && lay[ob])
    {
	ob->catch_tell(sdef[lay[ob][2]][6]);
	ob->unset_no_show_composite();
	ob->remove_subloc(SUBLOC);

	if (lay[ob][0] == 2 && (to = lay[ob][1]))
	{
	    lay = m_delete(lay, to);
	    to->unset_no_show_composite();
	    to->catch_tell("You are dumped unceremoniously onto the "+
	      "grass.\n");
	    tell_room(this_object(), QCTNAME(to) + " is dumped " +
	      "unceremoniously onto the grass.\n", to);
	}

        if (lay[ob][0] == 3)
        {
            lay[lay[ob][1]] = ({1,0,lay[lay[ob][1]][2]});
        }

	lay = m_delete(lay, ob);
    }
}

public int
do_lay(string str)
{
    object *obs, ob;
    int i;
    
    if (lay[this_player()])
    {
	return notify_fail("But you are already laying!\n");
    }

    if(str == "down")
        i = random(sizeof(sdef));
    else
    {    
        i = -1;
        while( ++i < sizeof(sdef) && member_array(str, sdef[i][0]) == -1 );
    }
    
    if (i == sizeof(sdef) &&
	!sizeof(obs = FIND_STR_IN_ARR(str, m_indexes(lay)))) 
    {
	return notify_fail(capitalize(query_verb()) + " where?\n");
    }

    if (sizeof(obs))
    {
	if (sizeof(obs) > 1)
	{
	    return notify_fail("You may only lay on one body at a time.\n");
	}

	if (objectp(ob = lay[obs[0]][1]))
	{
	    return notify_fail(QCTPNAME(obs[0]) + " body is already " +
		"occupied.\n");
	}

	lay[this_player()] = ({ 3, obs[0], lay[obs[0]][2] });
	lay[obs[0]] = ({ 2, this_player(), lay[obs[0]][2] });

	this_player()->catch_msg(
	    "You slip onto " + QTPNAME(obs[0]) + " body.\n");
	obs[0]->catch_tell(this_player()->query_The_name(obs[0]) +
	  " slips onto your body.\n");
	say(QCTNAME(this_player()) + " slips onto " + QTPNAME(obs[0]) +
	  " body.\n", ({ obs[0], this_player() }));
    }
    else
    {
	lay[this_player()] = ({ 1, 0, i });
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

    if (!pointerp(tmp = lay[this_player()]))
    {
	return notify_fail("But you are not laying!\n");
    }

    this_player()->unset_no_show_composite();
    this_player()->remove_subloc(SUBLOC);

    if (tmp[0] == 3 && objectp(ob = tmp[1]))
    {
	this_player()->catch_msg(
	    "You slip off of " + QTPNAME(ob) + " body.\n");
	ob->catch_tell(this_player()->query_The_name(ob) + " slips off "+
	  "of your body.\n");
	say(QCTNAME(this_player()) + " slips off of " + QTPNAME(ob) +
	  " body.\n", ({ this_player(), ob }));

	lay[ob] = ({ 1, 0, lay[ob][2]});
    }
    else
    {
	write(sdef[tmp[2]][3]);
	say(QCTNAME(this_player()) + sdef[tmp[2]][4]);

	if (tmp[0] == 2 && objectp(ob = tmp[1]))
	{
	    ob->unset_no_show_composite();

	    ob->catch_tell("You are dumped unceremoniously "+
	      "onto the grass.\n");
	    tell_room(this_object(), QCTNAME(ob) + " is dumped "+
	      "unceremoniously onto the grass.\n", ob);

	    lay = m_delete(lay, ob);
	}
    }
    lay = m_delete(lay, this_player());
    return 1;
}

public string
lay_desc()
{
    object *obs = ({}), m;
    string *who = ({}), str;
    int i, j, k, l;

    str = SDESC;

    obs = m_indexes(lay) - ({ 0 });
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
        if (lay[obs[i]][2] != k) continue;

        l++;
        
	if (lay[obs[i]][0] > 2) continue;

        m = obs[i];
         
	if (lay[obs[i]][0] == 2)
	{
	    object ob = lay[obs[i]][1];

	    if (obs[i] == this_player())
	    {
		who += ({ "yourself with " +
		    ob->query_the_name(this_player()) +		   " snuggled up on your body" });
	    }
	    else
	    {
		who += ({ obs[i]->query_the_name(this_player()) +
		    " with " + (ob == this_player() ? "you" : 
		     ob->query_the_name(this_player())) +
		     " snuggled up on "+ 
		     obs[i]->query_possessive() +" body" });
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

    if (!pointerp(tmp = lay[on]))
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
	    (for_ob == on ? "your" : on->query_possessive()) +" body";
	}
	return str + ".\n";
    }

    if (tmp[1] == for_ob)
	return str + " snuggled up on your body.\n";

    return str + " snuggled up on " + 
        tmp[1]->query_the_name(for_ob) + "'s body.\n";
}

void
init_lay()
{
    add_action(  do_lay,  "lay"   );
    add_action( do_stand, "stand" );
}