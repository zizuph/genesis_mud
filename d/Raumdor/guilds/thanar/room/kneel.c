/*********************************************************************
 * - kneel.c                                                       - *
 * - These are some routines to let you add kneelting into           - *
 * - a room. To get this to work, you need to:                     - *
 * -                                                               - *
 * - Include this file.                                            - *
 * - At the end of your long desc,                                 - *
 * - Add a call to seat_desc() (optional)                          - *
 * - Create an add_item and point it to seat_desc() (optional)     - *
 * - Add init_seat() into your init() function. (create if needed) - *
 * - Will allow more than one kneeling or seating in a room         - *
 * -                                                               - *
 * - Created by Damaris 12/2001                                    - *
 * - Adapted from Lucius seating code which was modified by Valen  - *
 *********************************************************************/

#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <stdproperties.h>

#define SUBLOC	"_subloc_kneeling"
 
/*********************************************************************
 * This holds our data                                               *
 * Went with a mapping instead of props for ease of use and speed.   *
 *                                                                   *
 * mapping kneeling = ([                                             *
 *     <player> : ({ <int 1|2|3>, <0|player>, <int type>, }),        *
 *                   ])                                              *
 *                                                                   *
 * 1 = kneeling.                                                     *
 * 2 = kneeling next to player.                                      *
 * 3 = kneeling with player.                                         *
 *                                                                   *
 * type - seating type used by a player                              *
 *                                                                   *
 *********************************************************************/

#define SDESC \
"\n    The sanctuary is lined with plush pews that have plush "+ \
"kneelers to kneel upon. The altar is specially designed to allow "+ \
"faithful members to kneel in reverence before it as well.\n"

mixed sdef = ({
({
({"altar","before altar"}),
"You reverently kneel before the altar.\n",
" reverently kneels before the altar.\n",
"You arise from kneeling.\n",
" arises from kneeling.\n",
"You are kneeling reverently before the altar.\n",
"You stand up from kneeling before the altar and leave the sanctuary.\n",
" kneeling before the altar",
" kneeling before the altar.\n",
}),

({
({"kneeler", "on kneeler", "plush kneeler", "on plush kneeler", "pew", "plush pew"}),
"You reverently kneel on one of the plush kneelers.\n",
" reverently kneels on one of the plush kneelers.\n",
"You arise from your plush kneeler.\n",
" arises from one of the plush kneelers.\n",
"You are kneeling reverently on one of the plush kneelers.\n",
"You arise from one of the plush kneelers and leave the sanctuary.\n",
" kneeling on one of the plush kneelers",
" kneeling on one of the plush kneelers.\n",
})

});

private mapping kneeling = ([]);

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    if (ob && !present(ob) && kneeling[ob])
    {
	ob->catch_tell(sdef[kneeling[ob][2]][6]);
	ob->unset_no_show_composite();
	ob->remove_subloc(SUBLOC);

	if (kneeling[ob][0] == 2 && (to = kneeling[ob][1]))
	{
	    kneeling = m_delete(kneeling, to);
	    to->unset_no_show_composite();
	    to->catch_tell("You quickly stand up.\n");
	    tell_room(this_object(), QCTNAME(to) + " quickly stands up.\n", to);
	}

        if (kneeling[ob][0] == 3)
        {
            kneeling[kneeling[ob][1]] = ({1,0,kneeling[kneeling[ob][1]][2]});
        }

	kneeling = m_delete(kneeling, ob);
    }
}

public int
do_kneel(string str)
{
    object *obs, ob;
    int i;
    
    if (kneeling[this_player()])
    {
	return notify_fail("But you are already kneeling!\n");
    }

    if(str == "down")
        i = random(sizeof(sdef));
    else
    {    
        i = -1;
        while( ++i < sizeof(sdef) && member_array(str, sdef[i][0]) == -1 );
    }
    
    if (i == sizeof(sdef) &&
	!sizeof(obs = FIND_STR_IN_ARR(str, m_indexes(kneeling)))) 
    {
	return notify_fail(capitalize(query_verb()) + " where?\n");
    }

    if (sizeof(obs))
    {
	if (sizeof(obs) > 1)
	{
	    return notify_fail("You may only kneel close to one person "+
	      "at a time.\n");
	}

	if (objectp(ob = kneeling[obs[0]][1]))
	{
	    return notify_fail(QCTPNAME(obs[0]) + " is already kneeling "+
	      "next to someone.\n");
	}

	kneeling[this_player()] = ({ 3, obs[0], kneeling[obs[0]][2] });
	kneeling[obs[0]] = ({ 2, this_player(), kneeling[obs[0]][2] });

	this_player()->catch_msg(
	    "You reverently kneel next to " + QTPNAME(obs[0]) + " right.\n");
	obs[0]->catch_tell(this_player()->query_The_name(obs[0]) +
	  " reverently kneels next to you.\n");
	say(QCTNAME(this_player()) + " reverently kneels next to "+
	  "" + QTPNAME(obs[0]) + " right.\n", ({ obs[0], this_player() }));
    }
    else
    {
	kneeling[this_player()] = ({ 1, 0, i });
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

    if (!pointerp(tmp = kneeling[this_player()]))
    {
	return notify_fail("But you are not kneeling!\n");
    }

    this_player()->unset_no_show_composite();
    this_player()->remove_subloc(SUBLOC);

    if (tmp[0] == 3 && objectp(ob = tmp[1]))
    {
	this_player()->catch_msg(
	    "You quickly stand up.\n");
	ob->catch_tell(this_player()->query_The_name(ob) + " quickly "+
	  "stands up.\n");
	say(QCTNAME(this_player()) + " quickly stands "+
	  "up.\n", ({ this_player(), ob }));

	kneeling[ob] = ({ 1, 0, kneeling[ob][2]});
    }
    else
    {
	write(sdef[tmp[2]][3]);
	say(QCTNAME(this_player()) + sdef[tmp[2]][4]);

	if (tmp[0] == 2 && objectp(ob = tmp[1]))
	{
	    ob->unset_no_show_composite();

	    ob->catch_tell("You quickly stand up.\n");
	    tell_room(this_object(), QCTNAME(ob) + " quickly "+
	    "stands up.\n", ob);

	    kneeling = m_delete(kneeling, ob);
	}
    }
    kneeling = m_delete(kneeling, this_player());
    return 1;
}

public string
kneel_desc()
{
    object *obs = ({}), m;
    string *who = ({}), str;
    int i, j, k, l;

    str = SDESC;

    obs = m_indexes(kneeling) - ({ 0 });
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
        if (kneeling[obs[i]][2] != k) continue;

        l++;
        
	if (kneeling[obs[i]][0] > 2) continue;

        m = obs[i];
         
	if (kneeling[obs[i]][0] == 2)
	{
	    object ob = kneeling[obs[i]][1];

	    if (obs[i] == this_player())
	    {
		who += ({ "yourself with " +
		    ob->query_the_name(this_player()) + " are" });
	    }
	    else
	    {
		who += ({ obs[i]->query_the_name(this_player()) +
		    " with " + (ob == this_player() ? "you" : 
		     ob->query_the_name(this_player())) +
		     " are" });
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
	" is" : "") + sdef[k][8];
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

    if (!pointerp(tmp = kneeling[on]))
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
	      tmp->query_the_name(on) ) + " by " +
	    (for_ob == on ? "your" : on->query_possessive()) +" side";
	}
	return str + ".\n";
    }

    if (tmp[1] == for_ob)
	return str + " reverently kneeling together.\n";

    return str + " reverently kneeling with " + 
        tmp[1]->query_the_name(for_ob) + ".\n";
}

void
init_kneel()
{
    add_action(do_kneel, "kneel");
    add_action(do_stand, "stand");
}
