/* A handy object for checking out the MAGIC_AM_ID_INFO of another object. */
/* Based on on the identify scroll by Nick. Coded on 25/08/95 by Tulix III */

inherit "/std/object";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <ss_types.h>

/* Global variable */
int skill;

/* Prototype functions */
public int identify_obj(string str);
public int set_id_skill(string str);

public void
create_object()
{
    set_name("widget");
    set_short("identify widget");
    set_adj("identify");
    add_adj("id");
    set_long("The widget gives you the ability to find out id info of " +
	"another object. Just type 'idskill <integer>' to set the skill " + 
	"level used (0-100).\n Use 'id <name>' to get the id info of an " +
	"object (if any is set).\n");

    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_NO_STEAL, 1);

    skill = 100;
}

public void
init()
{
    ::init();
    add_action(identify_obj, "id");
    add_action(set_id_skill, "idskill");
}

public int
identify_obj(string str)
{
    object *obj, ob;
    int i, resist;
    string text;    
    mixed info;

    if (this_player() -> query_wiz_level() == 0)
    {
	write ("Eeks!! The widget explodes in your face!\n");
	remove_object();
	return 0;
    }
    
    notify_fail("Identify which object?\n");
    if (!str)
	return 0;

    notify_fail("Couldn't find '" + str + "'\n");
    if (!strlen(str))
	return 0;

    obj = FIND_STR_IN_OBJECT(str, this_player());
    if (!sizeof(obj))
	obj = FIND_STR_IN_OBJECT(str, environment(this_player()));

    if (!sizeof(obj))
	return 0;

    ob = obj[0];

    resist = ob->query_prop(MAGIC_I_RES_IDENTIFY);

    info = ob->query_prop(MAGIC_AM_ID_INFO);
    for (i = 0; i < sizeof(info) / 2; i++)
	if (skill >= info[i * 2 + 1])
	    text = info[i * 2];

    write("You identify the " + ob->short() + " with skill=" + skill + ".\n");
    if (resist == -1)
	write("The object has no resistance to identification.\n");
    else
	write("The object has " + resist + " resistance to identification.\n");

    if (text)
	write("\t" + text);
    else
	write("You don't discover any special information.\n");

    return 1;
}

public int
set_id_skill(string str)
{
    int new_skill;

    new_skill = atoi(str);
    if (new_skill >= 0)
    {
	skill = new_skill;
	write("Identify skill set to " + skill + ".\n");
	return 1;
    }
    else
    {
	write("Identify skill is currently " + skill + ".\n");
	return 1;
    }

    return 0;
}

/* Make the object auto-loading */
public string
query_auto_load()
{
   return MASTER;
}

/* As this object is auto-loading it is _vital_ that mortals cannot use it. */
public void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);
    
    if (dest->query_wiz_level() == 0)
    {    
	write ("Eeks!! The widget explodes in your face!\n");
	remove_object();
	return 0;
    }
    return;
}
