#pragma save_binary

#include <stdproperties.h>
#include <language.h>
#include "/d/Gondor/common/lib/gems.h"
#include <macros.h>
#include "/d/Gondor/defs.h"
#define G_MAX   sizeof(GEM_TYPES)

int *
split_values(int v)
{
    int *ret, i;
    ret = allocate(sizeof(GEM_VALUES));
    if (v > 0)
	for (i = sizeof(GEM_VALUES) - 1; i >= 0; i--)
	{
	    ret[i] = v / GEM_VALUES[i];
	    v %= GEM_VALUES[i];
	}
    return ret;
}

int
merge_values(int *av)
{
    int v, i;
    if (sizeof(av) != sizeof(GEM_TYPES))
	return 0;
    for (v = 0, i = 0; i < sizeof(av); i++)
	v += av[i] * GEM_VALUES[i];
    return v;
}

object
make_gems(string str, int num)
{
    object gem;
    FIX_EUID
    if (!str)
	return 0;
    gem = clone_object(STDGEM);
    gem->set_heap_size(num);
    gem->set_gem_type(str);
    return gem;
}

int
move_gems(string str, int num, mixed from, mixed to)
{
    object gem, f, t, gf;
    int max, okflag;
    if (!str || (num <= 0))
	return -1;
    if (stringp(from))
    {
	f = find_object(from);
	if (!f)
	    f = find_player(from);
    }
    else if (objectp(from))
	f = from;
    else
	f = 0;
    if (stringp(to))
    {
	t = find_object(to);
	if (!t)
	    t = find_player(to);
    }
    else if (objectp(to))
	t = to;
    else
	t = 0;
    if (f)
	gf = present(str, f);
    else
	gf = make_gems(str, num);
    if (!gf || !(max = gf->num_heap()))
	return -1;
    if (num > max)
	return -1;
    if (t)
    {
	if (num < max)
	    gf->split_heap(num);
	return gf->move(to);
    }
    if (!t && num < max)
	gf->set_heap_size(max - num);
    else
	gf->remove_object();
    return 0;
}

int *
what_gems(mixed ob)
{
    object pl, gn;
    int il, *nums;
    string *gtypes;

    if (objectp(ob))
	pl = ob;
    else if (stringp(ob))
    {
	pl = find_object(ob);
	if (!pl)
	{
	    pl = find_player(ob);
	}
    }
    else
	return 0;
    gtypes = GEM_TYPES;
    nums = allocate(sizeof(gtypes));
    for (il = 0; il < sizeof(gtypes); il++)
    {
	gn = present(gtypes[il], pl);
	if (!gn)
	{
	    nums[il] = 0;
	    continue;
	}
	else
	    nums[il] = gn->num_heap();
    }
    return nums;
}

public int
total_gems(object who)
{
    return merge_values(what_gems(who));
}

public int
give_gems(object who, int amount)
{
    object ob;
    int to_do, i, n_gems, c_flag;
    to_do = amount;
    i = G_MAX;
    c_flag = 0;
    for (i = G_MAX - 1; i >= 0 && to_do; i--)
    {
	n_gems = to_do / GEM_VALUES[i];
	to_do = to_do % GEM_VALUES[i];
	if (n_gems > 0)
	{
	    ob = make_gems(GEM_TYPES[i], n_gems);
	    if ((int) ob->move(who))
	    {
		ob->move(environment(who));
		c_flag = 1;
	    }
	}
    }
    if (c_flag)
    {
	who->catch_msg("You cannot carry this many gems, so you drop "
	  + "some on the ground.\n");
	say(QCTNAME(who) + " drops some gems on the ground.\n", who);
    }
    return 1;
}

public int
take_gems(object who, int amount)
{
    int *gem_list, i, rest, c_flag;
    object *ob_list, ob;
    if (total_gems(who) < amount)
	return 0;
    gem_list = allocate(G_MAX);
    ob_list = allocate(G_MAX);
    for (i = 0; i < G_MAX; i++)
    {
	ob = present(GEM_TYPES[i], who);
	if (ob)
	{
	    ob_list[i] = ob;
	    gem_list[i] = (int)ob->query_prop(OBJ_I_VALUE);
	}
    }
    for (i = 0; i < G_MAX; i++)
    {
	if (amount <= gem_list[i])
	{
	    gem_list[i] -= amount;
	    break;
	}
	else
	{
	    amount -= gem_list[i];
	    gem_list[i] = 0;
	}
    }
    rest = 0;
    for (i = G_MAX -1; i >= 0; i--)
    {
	gem_list[i] += rest;
	rest = gem_list[i] % GEM_VALUES[i];
	gem_list[i] = gem_list[i] / GEM_VALUES[i];
	if (ob_list[i])
	    ob_list[i]->set_heap_size(gem_list[i]);
	else
	{
	    if (gem_list[i] > 0)
	    {
		ob = make_gems(GEM_TYPES[i], gem_list[i]);
		if ((int)ob->move(who))
		{
		    ob->move(environment(who));
		    c_flag = 1;
		}
	    }
	}
    }
    if (c_flag)
    {
	who->catch_msg("You cannot carry this many gems, so you "
	  + "drop some them on the ground.\n");
	say(QCTNAME(who) + " drops some gems on the ground.\n", who);
    }
    return 1;
}

public string
gem_text(int *gems)
{
    string *text = ({ });
    int    total = 0;
    int    index = G_MAX;
    if (sizeof(gems) != G_MAX)
    {
	return "a strange number of gems";
    }
    while (--index >= 0)
    {
	total += gems[index];
	switch(gems[index])
	{
	case 0:
	    break;
	case 1:
	    text += ({ "a " + GEM_TYPES[index] });
	    break;
	default:
	    text += ({ LANG_WNUM(gems[index]) + " " +
		GEM_TYPES[index] });
	}
    }
    if (total == 1)
    {
	return text[0];
    }
    index = sizeof(text);
    switch(index)
    {
    case 0:
	return "no gems at all";
	break;
    case 1:
	return text[0];
	break;
    default:
	return implode(text[0..(index - 2)], ", ") + " and "
	  + text[index - 1];
    }
}

public int
add_gems(object who, int amount)
{
    return (amount < 0 ? take_gems(who, ABS(amount)) : give_gems(who, amount));
}
