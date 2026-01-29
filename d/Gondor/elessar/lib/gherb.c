/*
 *  The standard herb.
 *
 *  The original made by Elessar Telcontar of Gondor, 
 *		Genesis, April to July 1992.
 *
 *  Modified by Nick
 *
 *  Modified by Glindor
 */

inherit "/std/object";
inherit "/lib/herb_support";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <composite.h>
#include <stdproperties.h>
#include <language.h>
#include <cmdparse.h>
#define STDHERBFILE "/d/Roke/glindor/open/herb"

/*
 * Variables
 */
int 	find_diff, id_diff, decay_time, herb_value, inited_once;
int     food_amount, dried, dryable, ate_it;
string	id_long, unid_long, ingest_verb, herb_name;
object  *gFail;

/*
 * Function name: do_id_check
 * Description:   This little function is called each time the herb is referred
 *                to by a player, to check if (s)he identifies it or not.
 * Arguments:	  player - The player
 * Returns: 1 for identification, else 0.
 */
varargs int
do_id_check(object player)
{
    if (!player)
	player = this_player();

    if (player && id_diff <= player->query_skill(SS_HERBALISM))
	return 1;
    else
	return 0;
}

/*
 * Function name: init
 * Description:   adds the ingest-action to the player
 */
void
init()
{
    ::init(); /* If this isn't added cmd items won't work. */

    add_action("ingest_it", ingest_verb);
}


void
leave_env(object from, object to)
{
    if (from && living(from))
	remove_name(herb_name);

    ::leave_env(from, to);
}

/* Start the decay when the herb enters a living,  i.e when it's picked. */

void
enter_env(object dest, object old)
{
    if (dest && living(dest) && do_id_check(dest))
	add_name(herb_name);

    if (dest && living(dest) && !inited_once)
    {
    	if (decay_time)
	    call_out("decay", decay_time);
    	inited_once = 1;
    }

    ::enter_env(dest, old);
}

/*
 * Function name: long_func
 * Description:   This is an VBFC function for the set_long in the herb, which
 *                tests if the player examining it can identify it, before
 *                returning the appropriate long-description. To make this work,
 *                you must be sure to do set_id_long(str) and set_unid_long(str)
 *                from the create_herb() function.
 */
nomask string
long_func()
{
    if (do_id_check(this_player()))
	return id_long;
    return unid_long;
}

/*
 * Function name: set_ingest_verb
 * Description:   Set what verb the player should type to be able to ingest 
 * 		  the herb. Default is "eat"
 * Arguments:     str - The verb
 */
void
set_ingest_verb(string str) { ingest_verb = str; }

/*
 * Function name: query_ingest_verb
 * Description:   What verb is required to ingest this herb?
 * Returns:	  The verb;
 */
string
query_ingest_verb() { return ingest_verb; }

/*
 * Function name: set_decay_time
 * Description:	  Set how long time it takes for the herb to decay
 * Argumetns:	  i - The time (in seconds)
 */
void
set_decay_time(int i) { decay_time = i; }

/*
 * Function name: query_decay_time
 * Description:   How long time does it take for the herb to decay?
 * Returns:	  The time in seconds
 */
int
query_decay_time() { return decay_time; }

/*
 * Function name: set_dryable
 * Description:   Calling this function makes the herb dryable
 */
void
set_dryable() { if (!dried) dryable = 1; }

/*
 * Function name: query_dryable
 * Description:   Is the function dryable?
 * Returns:       1 if it is dryable
 */
int
query_dryable() { return dryable; }

/*
 * Function name: dry
 * Description:   This function is called when a herb dries, to allow
 *                different effects for dried herbs.
 */
void
dry() {}

/*
 * Function name: set_dried
 * Description:   Force the herb to dry
 */
void
set_dried()
{
    if (!dried)
      {
	dried = 1;
	dryable = 0;
	dry();
	remove_call_out("decay"); 
	call_out("decay", decay_time + random(2 * decay_time));
	inited_once=1;
      }
}

/*
 * Function name: query_dried
 * Description:   Is the herb dried?
 * Returns:	  1 if dried
 */
int
query_dried() { return dried; }

/*
 * Function name: set_herb_name
 * Description:   Set the true name of the herb
 * Arguments:	  str - The name
 */
void
set_herb_name(string str) { herb_name = str; }

/*
 * Function name: query_herb_name
 * Description:   What is the true name of the herb
 * Returns:	  The name of the herb
 */
string
query_herb_name() { return herb_name; }

/*
 * Function name: set_id_long
 * Description:   Set the long description you see if you know what herb it
 *		  is.
 * Arguments:     str - The description
 */
void
set_id_long(string str) { id_long = str; }

/*
 * Function name: query_id_long
 * Description:   The long description if you can id the herb
 * Returns:       The long description
 */
string query_id_long() { return id_long; }

/*
 * Function name: set_unid_long
 * Description:   Set the long description you see if you cannot identify the 
 *		  herb.
 * Arguments:     str - The long description
 */
void
set_unid_long(string str) { unid_long = str; }

/*
 * Function name: query_unid_long
 * Description:   Query the long description you get if you cannot identify
 *		  the herb.
 * Returns:   	  The unidentified long description
 */
string
query_unid_long() { return unid_long; }

/*
 * Function name: set_id_diff
 * Description:   Set how hard it is to identify a herb
 * Arguments:     i - The skill needed to know the herb
 */
void
set_id_diff(int i) { id_diff = i; }

/*
 * Function name: query_id_diff
 * Description:   How hard is it to identify this herb
 * Returns:  	  The difficulty
 */
int
query_id_diff() { return id_diff; }

/*
 * Function name: set_find_diff
 * Description:   Set how hard it is to find the herb
 * Arguments:     i - Difficulty (suggested range is 0 - 10)
 */
void
set_find_diff(int i) { find_diff = i; }

/*
 * Function name: query_find_diff
 * Description:   How hard is it to find this herb
 * Returns: 	  The difficulty to find the herb in the nature
 */
int
query_find_diff() { return find_diff; }

/*
 * Function name: set_herb_value
 * Description:   Set the value of the herb when dealing with a herb specialist
 * Arguments:     i - The value
 */
void
set_herb_value(int i) { herb_value = i; }

/*
 * Function name: query_herb_value
 * Description:   The value of the herb when dealing with a specialist
 * Returns:	  The value
 */
int
query_herb_value() { return herb_value; }

/*
 * Function name:       set_amount
 * Description:         sets the amount of food in this herb (in grams)
 * Arguments:           a: The amount of food
 */
public void
set_amount(int a) 
{ 
    food_amount = a; 
    add_prop(OBJ_I_VOLUME, a / 10);
    add_prop(OBJ_I_WEIGHT, a);
}

/*
 * Function name:       query_amount
 * Description:         Gives the amount of food in this herb
 * Returns:             Amount as int (in grams)
 */
public int
query_amount() { return food_amount; }

/* this is called if this herb is eaten and the ingest_verb!="eat" */
void
set_ate_it() { ate_it=1; }

/*
 * Function name: ate_non_eat_herb
 * Description:   This function is called in stead of do_herb_effect
 *                if you eat a herb that isn't supposed to be eaten
 */
ate_non_eat_herb()
{
    write("You don't feel any effect.\n");
}

/* 
 * Function name: decay
 * Description:   This function is called with a call_out, and simulates the
 *                somewhat rapid decay of herbs - herbs lose their effect
 *                soon after being picked, if they don't dry and last longer.
 *                To make a herb dry, do set_dryable() from create_herb().
 *                set_dried() can be used to dry the herb immediately.
 */
int
decay()
{
    object env;
    string mess;

    if (dryable)
    {
    	dryable = 0;
    	dried = 1;
    	set_short("dried, " + short());
	dry();
    	call_out("decay", (decay_time + random(2 * decay_time)));
    	return 1;
    }

    if (env = environment())
    {
	mess = "The " + short() + " slowly turns to dust as it decays.\n";
	if (living(env))
	    tell_object(env, mess);
	else if (env->query_prop(ROOM_I_IS))
	    tell_room(env, mess);
    }
	    
    remove_object();
    return 1;
}

/*
 * Function name: create_herb
 * Description:   This is the create-function of the herb, which you should
 *                redefine and setup the herb from.
 */
void
create_herb() {}

nomask void
create_object()
{
    set_name("herb");
    set_short("unknown herb");
    set_id_long("This herb has not been described by the wizard.\n");
    set_unid_long("This is an undescribed, unknown herb.\n");
    set_herb_name("xortion");
    set_amount(2);
    set_decay_time(300);
    set_id_diff(20);
    set_find_diff(5);
    set_herb_value(10);
    set_ingest_verb("eat");

    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 25);
    add_prop(OBJ_I_VOLUME, 25);
    create_herb();
    set_long("@@long_func");
}

nomask void
reset_object() { this_object()->reset_herb(); }

void
consume_text(object *arr, string vb)
{
    say(QCTNAME(this_player()) + " " + vb + "s " + COMPOSITE_DEAD(arr) +".\n");
}

/*
 * Function name:	ingest_it
 * Description:		Ingests the objects described as parameter to the
 *                      ingest_verb. It uses command parsing to find which
 *                      objects to ingest.
 * Arguments:		str: The trailing command after 'ingest_verb ...'
 * Returns:		True if command successfull
 */
public int
ingest_it(string str)
{
    object 	*a, *foods;
    int		il;
    string str2, vb;
    
    if (this_player()->query_prop(TEMP_STDHERB_CHECKED))
	return 0;

    gFail = ({ });
    vb = query_verb(); 
    
/* If you type "eat all" and the command comes to a herb first
 * it would cause all eatable herbs to be eaten but no food.
 * This is to prevent this. (How often do you want to eat all herbs?)
 */
    if (vb=="eat" && str=="all")
      {
	notify_fail("You must specify which herb to eat.\n");
	return 0;
      }

    notify_fail(capitalize(vb) + " what?\n");  /* access failure */
    
    a = CMDPARSE_ONE_ITEM(str, "ingest_one_thing", "ingest_access");
    if (sizeof(a) > 0)
    {
	consume_text(a, vb);
	for (il = 0; il < sizeof(a); il++)
	    a[il]->destruct_object();
	return 1;
    }
    else
    {
	call_out("tp_remove_temp", 1, this_player());
	this_player()->add_prop(TEMP_STDHERB_CHECKED, 1);
	if (sizeof(gFail))
	    notify_fail("@@ingest_fail:" + file_name(this_object()));
	return 0;
    }
}

void
tp_remove_temp(object tp)
{
    tp->remove_prop(TEMP_STDHERB_CHECKED);
    remove_call_out("tp_remove_temp");
}

string
ingest_fail()
{
    string str;

    str = "You try to " + ingest_verb + " " + COMPOSITE_DEAD(gFail) +
        "but fail.\n";
    say(QCTNAME(this_player()) + " tries to " + ingest_verb + " " +
        QCOMPDEAD + " but fails.\n");
    tp_remove_temp(this_player());
    return str;
}

int
ingest_access(object ob)
{ 
    string vb;

    vb=query_verb();

    if ((environment(ob) == this_player()) &&
	(function_exists("create_object", ob) == STDHERBFILE) &&
	(vb==ob->query_ingest_verb() || vb=="eat"))
	return 1;
    else
	return 0;
}

int
ingest_one_thing(object ob)
{
    int am;
    string vb;

    vb=query_verb();
    am = (int) ob->query_amount();
    
    if (vb=="eat")
      {
        if (!this_player()->eat_food(am))
	  {
	    write(capitalize(LANG_ADDART(ob->short())) +
		  " is too much for you.\n");
	    gFail += ({ ob });
	    return 0;
	  }
	if (vb!=ob->query_ingest_verb())
	  ob->set_ate_it();
	return 1;
      }
    
    return 1;
}

void
destruct_object()
{
    if (ate_it && ingest_verb !="eat")
      {
	ate_non_eat_herb();
      }
    else
      {
	do_herb_effects();
      }
    call_out("remove_object", 1);
}

