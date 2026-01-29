/*
 * - /d/Avenir/union/lib/visions.c
 *
 * This is code to support the 'vision' command in
 * ~union/room/council.c - There is quite a lot of it
 * so it was split from the main room file.
 *
 * -Lucius, August 2017
 *
 * Revisions:
 */
#pragma strict_types
#include "../defs.h"

#include <files.h>
#include <composite.h>

private string *vis_exclude = ({ "alcintaron" });


static int
valid_vision(string vis)
{
    string *list = LIST->query_vision_list();
    // Exclude these visions from manual assignation
    return (member_array(vis, list - vis_exclude) != -1);
}

static int
assign_vision(string name, string vis)
{
    string *args = ({ });
    mapping spheres = LIST->sphere_members();

    if (!strlen(name) || !strlen(vis))
	return 0;

    if ((name != "all") && !LIST->query_is_member(name) && !spheres[name])
	return NF("'"+ name +"' is not a member or sphere of the Union.\n");

    if (!valid_vision(vis))
	return NF("No vision named '"+ vis +"' is available.\n");

    if (name == "all")
    {
	write("Skipping Isolation and Training Spheres...\n"+
	    "Visions must be assigned to those Spheres directly.\n\n");

	foreach(string sph, string *whom: spheres)
	{
	    if (sph == SPH_ISOLATION || sph == SPH_TRAINING)
		continue;

	    foreach(string who: whom)
	    {
		if (SECURITY->query_wiz_level(who))
		    continue;

		if (LIST->assign_vision(who, vis))
		    args += ({ CAP(who) });
	    }
	}

	if (sizeof(args))
	{
	    LOG_COUNC(NM(TP) + " sent all Warriors vision: "+ vis);
	    write("These Warriors will be sent vision:  "+
		upper_case(vis) +".\n    "+
		COMPOSITE_WORDS(sort_array(args)) +"\n");
	}
	else
	{
	    write("No Warriors were eligible to receive a vision.\n");
	}
    }
    else if (spheres[name])
    {
	foreach(string who: spheres[name])
	{
	    if (SECURITY->query_wiz_level(who))
		continue;

	    if (LIST->assign_vision(who, vis))
		args += ({ CAP(who) });
	}

	name = CAP(name);
	if (sizeof(args))
	{
	    LOG_COUNC(NM(TP) +" sent the "+ name +
		" Sphere vision: "+ vis);
	    write("These Warriors in the "+ name +" Sphere will be "+
		"sent vision:  "+ upper_case(vis) +".\n    "+
		COMPOSITE_WORDS(sort_array(args)) +"\n");
	}
	else
	{
	    write("No Warriors in the "+ name +" Sphere "+
		"were eligible to receive a vision.\n");
	}
    }
    else
    {
	name = CAP(name);
	if (LIST->assign_vision(name, vis))
	{
	    LOG_COUNC(NM(TP) +" sent "+ name + " vision: "+ vis);
	    write(name + " will be sent vision:  "+
		upper_case(vis) +".\n");
	}
	else
	{
	    write("Unable to send a vision to: "+ name +".\n");
	}
    }
    return 1;
}

static int
list_vision(string name)
{
    mapping data;
    string str = "";

    if (!strlen(name))
	return TP->more(read_file(VISIONS + "VISIONS"));

    if ((name != "all") && !LIST->query_is_member(name))
	return NF("'"+ name +"' is not a member of the Union.\n");

    if (name == "all")
    {
	data = filter(LIST->get_union_visions(), m_sizeof);
	if (!m_sizeof(data))
	{
	    write("There are no pending visions to list.\n");
	    return 1;
	}

	write("These are the following visions which are pending:\n\n");
	foreach(string who: sort_array(m_indices(data)))
	{
	    str = "";
	    foreach(int key, string vis: data[who])
	    {
		str += sprintf("%15s :: %s\n",
		    upper_case(vis), ctime(key));
	    }
	    write(sprintf("%17s:%-#45.1s\n", CAP(who), str) + "\n");
	}
    }
    else
    {
	data = LIST->query_union_visions(name);
	if (!m_sizeof(data))
	{
	    write("There are no pending visions to list.\n");
	    return 1;
	}

	write("The following visions are pending for: "+
	    CAP(name) +"\n\n");

	foreach(int key, string vis: data)
	{
	    str += sprintf("%15s :: %s\n",
		upper_case(vis), ctime(key));
	}
	write(str + "\n");
    }

    return 1;
}

static int
clear_vision(string name)
{
    if (!strlen(name))
	return 0;

    if ((name != "all") && !LIST->query_is_member(name))
	return NF("'"+ name +"' is not a member of the Union.\n");

    LIST->clear_union_visions(name);
    if (name == "all")
    {
	LOG_COUNC(NM(TP) + " cleared all pending visions.");
	write("All pending visions have been cleared.\n");
    }
    else
    {
	name = CAP(name);
	LOG_COUNC(NM(TP) + " cleared visions for: "+ name);
	write("Pending visions have been cleared for: "+ name +"\n");
    }

    return 1;
}

static int
remove_vision(string name, string vis)
{
    if (!strlen(name) || !strlen(vis))
	return 0;

    string cname = CAP(name);

    if (!LIST->query_is_member(name))
	return NF("'"+ name +"' is not a member of the Union.\n");

    if (LIST->remove_vision(name, vis))
    {
	LOG_COUNC(NM(TP) +" removed vision '"+ vis +"' from: "+ cname);
	write("Removed pending vision '"+ vis +" from: "+ cname +"\n");
    }
    else
    {
	write("Unable to remove vision '"+ vis +"' from: "+ cname +"\n");
    }
    return 1;
}
