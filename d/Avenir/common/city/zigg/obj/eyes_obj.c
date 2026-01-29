// file name: ~eyes_obj.c
// creator(s): Lucius + Zielia
// last update:
// purpose: Cloned by various objects to serve as a master subloc object
//     for various eye modification available in the ziggurat.
// note: Also works with eyes from /d/Calia/gelan if the player has them.
//     Move to the living before adding references.
/*
 * Usage:
 *
 *  Adding: 
 *
 *    object ob = present(EYES_NAME, Player);
 *
 *    if (!objectp(ob))
 *    {
 *        ob = clone_object(EYES_OBJ);
 *        ob->move( Player );
 *    }
 *
 *    ob->add_ref("what to add (see refs mapping)");
 *
 *  Removing:
 *
 *    object ob = present(EYES_NAME, Player);
 *
 *    ob->rem_ref("what to remove (see refs mapping)");
 *
 *    NOTE: Object will self-remove if there are no more active types.
 *
 *  Querying:
 *
 *    object ob = present(EYES_NAME, Player);
 *
 *    ob->query_ref("what to check (see refs mapping)");
 *
 *   -- OR --
 *
 *    ob->query_refs();  // Will return a stringform of what is active.
 *
 *
 *  NOTE:
 *
 *   Do not hinge things on the gelan shadow, as this will interfere
 *   with other things that might shadow the yes, like the Union
 *   guild shadow.
 *
 */
inherit "/std/object";

#include "zigg.h"
#include <macros.h>
#include <stdproperties.h>

#define EYES_SUBLOC "eyes"

private static int types;
private static string *eyes;
private static object eye_sub;
private static mapping refs = ([
	"lashes"  : 1,
	"cateyes" : 2,
	"passion" : 4,
]);

public void
create_object(void)
{
    set_no_show();
    set_name(EYES_NAME);
    add_prop(OBJ_I_NO_DROP, 1);
}

public void
remove_object(void)
{
    if (IS_CLONE)
    {
	/* Remove our subloc */
	ENV(TO)->remove_subloc(EYES_NAME);

	/* Add old eye-shadow one back */
	if (objectp(eye_sub))
	    ENV(TO)->add_subloc(EYES_SUBLOC, eye_sub);
    }

    ::remove_object();
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    eye_sub = to->query_subloc_obj(EYES_SUBLOC);

    /* Remove old eyes subloc */
    if (objectp(eye_sub))
	to->remove_subloc(EYES_SUBLOC);

    /* Add our new eyes subloc */
    to->add_subloc(EYES_NAME, TO);
}

/* Generates our custom eyes description. */
public int
update_eyes(void)
{
    string heat;
    object on = environment();

    if (!types)
    {
	/* No references left, remove. */
	set_alarm(0.0, 0.0, remove_object);
	return -1;
    }

    eyes = allocate(2);
    heat = one_of_list(({ "passionate", "carnal" }));

    if (!objectp(eye_sub))
    {
	/* For non-gelan eyes. */
	switch(types)
	{
	case 1: /* lashes  */
	    eyes[0] = "You have long, dark eyelashes.\n";
	    eyes[1] = CAP(HE(on)) +" has long, dark eyelashes.\n";
	    break;
	case 2: /* cateyes */
	    eyes[0] = "You have slitted, cat-like eyes.\n";
	    eyes[1] = CAP(HE(on)) +" has slitted, cat-like eyes.\n";
	    break;
	case 4: /* passion */
	    eyes[0] = "Your eyes burn with "+ heat +" heat.\n";
	    eyes[1] = CAP(HIS(on)) +" eyes burn with "+ heat +" heat.\n";
	    break;

	case 3: /* lashes  + cateyes */
	    eyes[0] = "Your eyes are slitted like a cat's and "+
		"framed by long, dark lashes.\n";
	    eyes[1] = CAP(HIS(on)) +" eyes are slitted like a cat's and "+
		"framed by long, dark lashes.\n";
	    break;
	case 5: /* lashes  + passion */
	    eyes[0] = "Your darkly-lashed eyes smoulder with "+
		heat +" heat.\n";
	    eyes[1] =  CAP(HIS(on)) +" darkly-lashed eyes smoulder with "+
		heat +" heat.\n";
	    break;
	case 6: /* cateyes + passion */
	    eyes[0] = "Your cat-like eyes smoulder with "+
		heat +" heat.\n";
	    eyes[1] = CAP(HIS(on)) +" cat-like eyes smoulder with "+
		heat +" heat.\n";
	    break;
	case 7: /* lashes  + cateyes + passion */
	    eyes[0] = "Your cat-like eyes smoulder with "+
		heat +" heat.\nYou have long, dark eyelashes.\n";
	    eyes[1] = CAP(HIS(on)) +" cat-like eyes smoulder with "+
		heat +" heat.\n"+ CAP(HE(on)) +
		" has long, dark eyelashes.\n";
	    break;
	}
    }
    else
    {
	/* For gelan-style eyes. */
	switch(types)
	{
	case 1: /* lashes  */
	    eyes[0] = "Your eyes are %s"+
		" and framed by long, dark lashes.\n";
	    eyes[1] = CAP(HIS(on)) +" eyes are %s" +
		" and framed by long, dark lashes.\n";
	    break;
	case 2: /* cateyes */
	    eyes[0] = "Your eyes are %s" +
		" and slitted like a cat's.\n";
	    eyes[1] = CAP(HIS(on)) +" eyes are %s" +
		" and slitted like a cat's.\n";
	    break;
	case 4: /* passion */
	    eyes[0] = "Your %s eyes burn with "+
		heat +" heat.\n";
	    eyes[1] = CAP(HIS(on)) +" eyes burn with "+
		heat +" heat.\n";
	    break;

	case 3: /* lashes  + cateyes */
	    eyes[0] = "Your eyes are %s" +
		" and slitted like a cat's.\n"+
		"You have long, dark eyelashes.\n";
	    eyes[1] = CAP(HIS(on)) +" eyes are %s" +
		" and slitted like a cat's.\n"+
		CAP(HE(on)) +" has long, dark eyelashes.\n";
	    break;
	case 5: /* lashes  + passion */
	    eyes[0] = "Your eyes are %s" +
		" and framed by long, dark lashes.\n"+
		"You are flushed with Passion.\n";
	    eyes[1] = CAP(HIS(on)) +" eyes are %s" +
		" and framed by long, dark lashes.\n"+
		CAP(HE(on)) +" is flushed with Passion.\n";
	    break;
	case 6: /* cateyes + passion */
	    eyes[0] = "Your eyes are %s" +
		" and slitted like a cat's.\n"+
		"You are flushed with Passion.\n";
	    eyes[1] = CAP(HIS(on)) +" eyes are %s" +
		" and slitted like a cat's.\n"+
		CAP(HE(on)) +" is flushed with Passion.\n";
	    break;
	case 7: /* lashes  + cateyes + passion */
	    eyes[0] = "Your eyes are %s" +
		" and slitted like a cat's.\n"+
		"You have long, dark eyelashes.\n"+
		"You are flushed with Passion.\n";
	    eyes[1] = CAP(HIS(on)) +" eyes are %s" +
		" and slitted like a cat's.\n"+
		CAP(HE(on)) +" has long, dark eyelashes.\n"+
		CAP(HE(on)) +" is flushed with Passion.\n";
	    break;
	}
    }

    return 1;
}

/* Adds a reference for describing custom eyes. */
public int
add_ref(string str)
{
    int val = refs[str];

    if (!val)
	return 0;

    if (types & val)
	return 0;

    types |= val;

    return update_eyes();
}

/* Removes a reference for describing custom eyes. */
public int
rem_ref(string str)
{
    int val = refs[str];

    if (!val)
	return 0;

    if (!(types & val))
	return 0;

    types ^= val;

    return update_eyes();
}

/* Check if a ref is applied or not. */
public int
query_ref(string str)
{
    int val = refs[str];

    if (!val)
	return 0;

    return (types & val);
}

/* Stringform listing of applied refs. */
public string
query_refs(void)
{
    string *arr = ({});

    foreach(string what, int val : refs)
    {
	if (types & val)
	    arr += ({ what });
    }

    return implode(sort_array(arr), ", ");
}

/* No recovery. */
public nomask string
query_recover(void)	{ return 0; }

/* No recovery. */
public nomask string
query_auto_load(void)	{ return 0; }

/* Displays our custom eyes. */
public string
show_subloc(string sub, object on, object for_obj)
{
    if (!types)
    {
	set_alarm(0.0, 0.0, remove_object);
	return "";
    }

    if ((sub != EYES_NAME) ||
	on->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
	return "";
    }

    if (on == for_obj)
	sub = eyes[0];
    else
	sub = eyes[1];

    string eyes = on->query_eyes();
    if (!stringp(eyes))
    {
        eyes = "eyes";
    }
	return sprintf(sub, eyes);
}
