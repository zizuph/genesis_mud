/* Modifications that can't be done via just inherit, by Sarr */

#pragma save_binary
#pragma strict_types

inherit "/std/object";
inherit "/lib/keep.c";
 
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Kalad/defs.h"
 
/*
 * Prototypes:
 */
public void set_strength(int strength);
public void set_value(int value);
public void set_time(int time);
public int torch_value();
public int do_light(string str);
public int do_extinguish(string str);
public void burned_out();

/*
 * Global variables:
 */
private int Torch_Value,	/* The max value of the torch. */
            Light_Strength,	/* How strongly the 'torch' will shine */
            Time_Left;		/* How much time is left? */
static  int Burn_Alarm,		/* Alarm used when torch is lit */
            Max_Time;		/* How much is the max time (start time) */
private object *Fail;

/*
 * Function name: create_torch
 * Description:   The standard create. This has some standard settings on
 *		  long and short descriptions, but don't be afraid to change
 *		  them.
 *                The pshort has to be set to some value, otherwise the short
 *                description of several objects will look ugly.
 */
void
create_torch()
{
    set_name("jack-o-lantern");    
    add_name("lantern");
    set_long("A large pumpkin with a horrible, evil faced carved into "+
    "it. You see 'jack help'. It has a foul, evil odor reeking from it. ");
    set_strength(3);
    set_time(1200);
}

/*
 * Function name: create_object
 * Description:   The standard create routine.
 */
nomask void
create_object()
{
    add_prop(OBJ_I_LIGHT,     0);
    add_prop(OBJ_I_WEIGHT,  700);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE,  torch_value);

    set_time(300);
    set_strength(1);
    set_value(40);

    create_torch();
}

/*
 * Function name: reset_torch
 * Description  : Since you may not mask reset_object() in torches, you have
 *                to redefine this function.
 */
public void
reset_torch()
{
}

/*
 * Function name: reset_object
 * Description:   Reset the object. Since this function is nomasked, you
 *                must redefine reset_torch() to make the torch reset.
 */
public nomask void
reset_object()
{
    reset_torch();
}

/*
 * Function name: torch_value
 * Description:   A VBFC gets here when someone wants to know the value of
 *		  the value of this object, default setting
 * Returns:	  The value
 */
public int
torch_value()
{
    int v;

    if (!Max_Time)
    	return 0;

    if (Burn_Alarm && sizeof(get_alarm(Burn_Alarm)))
	v = ftoi(get_alarm(Burn_Alarm)[2]);
    else
	v = Time_Left;

    return (v * (Torch_Value - 5)) / Max_Time + 5;
}
 
/*
 * Function name: short, pshort, long
 * Description:   We change the short, plural short and long description of
 *		  the torch if it's lit, default settings.
 * Returns:	  The description.
 */
public varargs string
short(object for_obj)
{
    string tmp = ::short(for_obj);
   
    if (Burn_Alarm)
    {
	return tmp + "(burning)";
    }

    return tmp;
}

public varargs string
plural_short(object for_obj)
{
    string tmp = ::plural_short(for_obj);

    if (!stringp(tmp))
    {
	return 0;
    }
    if (Burn_Alarm)
    {
	return tmp + "(burning))";
    }

    return tmp;
}

public varargs string
long(object for_obj)
{
    string tmp = ::long(for_obj);
    
    if (Burn_Alarm)
    {
	return tmp + "There is a burning candle inside, casting eerie yellow "+
        "light.\n";
    }
    if (!Time_Left)
    {
	return tmp + "Inside, it is empty.\n";
    }

    return tmp + "There is a candle inside, unlit.\n";
}

int
do_help(string str)
{
    if(str != "help")
        return 0;
    write("jflicker       ---  Lamp flickers \n"+
          "jcast          ---  Cast light \n"+
          "jlook <person> --- Spook someone\n");
    return 1;
}

int
do_jlook(string str)
{
    object *tars,ob;
    NF("Jspook who?\n");
    tars = PARSE_THIS(str,"[the] %l");
    if(!sizeof(tars))
        return 0;
    ob = tars[0];
    TP->catch_msg("You spook out "+QTNAME(ob)+".\n");
    ob->catch_msg("Maybe its your imagination, but you thought you "+
    "saw the "+short()+" held by "+QTNAME(TP)+" looking at you.\n");
    return 1;
}

int
do_jflicker(string str)
{
    write("Shadows dance around you as the candle in your "+short()+
    " flickers eerily.\n");
    say("Shadows dance around "+QTNAME(TP)+" as the candle in "+
    HIS(TP)+" "+short()+" flickers eerily.\n");
    return 1;
}

int
do_jcast(string str)
{
    write("You thrust forth your "+short()+", illuminating the area "+
    "before you.\n");
    say(QCTNAME(TP)+" thrusts forth "+HIS(TP)+" "+short()+", illuminating "+
    "the area before "+HIM(TP)+".\n");
    return 1;
}


/*
 * Function name: init
 * Description:   Here we add some commands to the player.
 */
public void
init()
{
    ::init();

    add_action(do_light, "light");  
    add_action(do_extinguish, "extinguish");
    add_action(do_help, "jack");
    add_action(do_jflicker,"jflicker");
    add_action(do_jcast,"jcast");
    add_action(do_jlook,"jlook");
}

/*
 * Function name: set_time
 * Description:   Set how long time the torch can burn.
 */
public void
set_time(int time)
{
    Max_Time = time;
    Time_Left = time;
}

/*
 * Function name: query_max_time
 * Description:	  Query the original burn time of the torch
 * Returns:       the time
 */
public int
query_max_time()
{
    return Max_Time;
}

/*
 * Function name: query_time
 * Description:	  Query how long time the torch can burn
 * Argument:      flag: if true, then return the time until the
 *                torch burns out if the torch is lit
 * Returns:       the time left
 */
public int
query_time(int flag = 0)
{
    mixed   alarm;

    if (flag && Burn_Alarm && sizeof(alarm = get_alarm(Burn_Alarm)))
	return ftoi(alarm[2]);
    return Time_Left;
}

/*
 * Function name: query_lit
 * Description:   Query of the torch is lit.
 * Argument:      flag - if set, return id of the alarm to the function
 *                that is called when the torch burns out.
 * Returns:       0        - if torch is not lit,
 *                -1       - if torch is lit,
 *                alarm id - if torch is lit and flag was set.
 */
public int
query_lit(int flag)
{
    if (flag)
	return Burn_Alarm;
    else
	return (!Burn_Alarm ? 0 : -1);
}

/*
 * Function name: set_time_left
 * Description:   Set how long time the torch can burn.
 *                Use this for 'torches' that can be refilled, like oil lamps.
 * Arguments    : int left - the time left.
 */
public void
set_time_left(int left)
{
    Time_Left = ((left < Max_Time) ? left : Max_Time);

    /* If lit, then also update the alarm. */
    if (Burn_Alarm)
    {
	remove_alarm(Burn_Alarm);
	Burn_Alarm = set_alarm(itof(Time_Left), 0.0, burned_out);
    }
}

/*
 * Function name: set_strength
 * Description:   Set the light strength of this 'torch'
 */
public void
set_strength(int strength)
{
    Light_Strength = strength;
}

/*
 * Function name: query_strength
 * Description:   Query how strongly the torch will shine
 */
public int
query_strength()
{
    return Light_Strength;
}

/*
 * Function name: set_value
 * Description:   Set the max value of the torch
 */
public void
set_value(int value)
{
    Torch_Value = value;
}

/*
 * Function name: do_light
 * Description:   The player tries to light something.
 * Arguments:	  str - the string describing what he  wants to light.
 * Returns:	  1/0
 */
public int
do_light(string str)
{
    object *a;
    string str2, vb;

    if (this_player()->query_prop(TEMP_STDTORCH_CHECKED))
        return 0;

    if (environment(this_player())->query_prop(ROOM_I_TYPE) ==
	ROOM_UNDER_WATER)
    {
	notify_fail("You are currently submerged.\n");
	return 0;
    }
 
    vb = query_verb();
    notify_fail(capitalize(vb) + " what?\n");
    if (!strlen(str))
	return 0;

    seteuid(getuid(this_object()));

    Fail = ({});
    a = CMDPARSE_ONE_ITEM(str, "light_one_thing", "light_access");
    if (sizeof(a) > 0)
    {
	str2 = COMPOSITE_DEAD(a);
	say(QCTNAME(this_player()) + " lights the candle in " + QCOMPDEAD + ".\n");
	write("You light the candle in " + str2 + ".\n");
	return 1;
    }

    set_alarm(1.0, 0.0, &(this_player())->remove_prop(TEMP_STDTORCH_CHECKED));
    this_player()->add_prop(TEMP_STDTORCH_CHECKED, 1);
    if (sizeof(Fail))
	notify_fail("@@light_fail:" + file_name(this_object()) + "@@");

    return 0;
}

public string
light_fail()
{
    int i;
    string str;

    str = "";
    for (i = 0; i < sizeof(Fail); i++)
        str += Fail[i]->query_light_fail();

    return str;
}

public string
query_light_fail()
{
    if (!Time_Left)
        return "There is no candle inside to light.\n";

    if (Burn_Alarm)
        return "The candle inside the " + short() + " is already lit.\n";

    return "";
}

public int
light_access(object ob)
{
    if ((environment(ob) == this_player() ||
	    environment(ob) == environment(this_player())))
	return 1;

    return 0;
}

public int
light_one_thing(object ob)
{
    if (!ob->light_me())
    {
	Fail += ({ ob });
	return 0;
    }
    return 1;
}

public int
light_me_after_delay()
{
    add_prop(OBJ_I_LIGHT, Light_Strength);
    add_prop(OBJ_I_HAS_FIRE, 1);
    Burn_Alarm = set_alarm(itof(Time_Left), 0.0, burned_out);
}

public int
light_me()
{
    if (!Time_Left || Burn_Alarm)
	return 0;
    set_alarm(0.0, 0.0, light_me_after_delay);
    return 1;
}

/*
 * Function name: do_extinguish
 * Description:   The player tries to extinguish something
 * Arguments:	  str - The string describing what to extinguish
 * Returns:	  1/0
 */
public int
do_extinguish(string str)
{
    object *a;
    string str2, vb;

    if (this_player()->query_prop(TEMP_STDTORCH_CHECKED))
        return 0;

    vb = query_verb();
    notify_fail(capitalize(vb) + " what?\n");
    if (!str)
        return 0;

    Fail = ({});
    a = CMDPARSE_ONE_ITEM(str, "extinguish_one_thing", "light_access");
    if (sizeof(a) > 0)
    {
        str2 = COMPOSITE_DEAD(a);
        say(QCTNAME(this_player()) + " extinguishes the candle in "+QCOMPDEAD + ".\n");
        write("You extinguish the candle in " + str2 + ".\n");
        return 1;
    }

    set_alarm(1.0, 0.0, &(this_player())->remove_prop(TEMP_STDTORCH_CHECKED));
    this_player()->add_prop(TEMP_STDTORCH_CHECKED, 1);
    if (sizeof(Fail))
        notify_fail("@@extinguish_fail:" + file_name(this_object()) + "@@");
    return 0;
}

public string
extinguish_fail()
{
    int i;
    string str;

    str = "";
    for (i = 0; i < sizeof(Fail); i++)
	str += Fail[i]->query_extinguish_fail();

    return str;
}

public string
query_extinguish_fail()
{
    if (!Burn_Alarm || !sizeof(get_alarm(Burn_Alarm)))
    {
	Burn_Alarm = 0;
	return "The " + short() + " isn't lit.\n";
    }

    return "";
}

public int
extinguish_one_thing(object ob)
{
    if (!ob->extinguish_me())
    {
	Fail += ({ ob });
	return 0;
    }
    return 1;
}

/*
 * Function name: extinguish_me
 * Description:   Extinguish this torch.
 * Returns:       1/0 - success/failure
 */
public int
extinguish_me()
{
    mixed   alarm;

    if (!Burn_Alarm)
        return 0;

    if (sizeof(alarm = get_alarm(Burn_Alarm)))
    {
	Time_Left = ftoi(get_alarm(Burn_Alarm)[2]);
	remove_alarm(Burn_Alarm);
    }
    Burn_Alarm = 0;
    remove_prop(OBJ_I_LIGHT);
    remove_prop(OBJ_I_HAS_FIRE);
    return 1;
}

/*
 * Function name: burned_out
 * Description:	  If this function is called when the torch has burned out.
 */
public void
burned_out()
{
    object ob = environment();
    string tmp = ::short();

    Time_Left = 0;
    Burn_Alarm = 0;

    remove_prop(OBJ_I_LIGHT);
    remove_prop(OBJ_I_HAS_FIRE);

    if (!objectp(ob))
	return;

    if (living(ob))
    {
	tell_object(ob, "The candle inside the "+tmp+" melts away.\n");
	tell_room(environment(ob), "The candle inside the "+tmp+" that " +
		QTNAME(ob) + " is holding melts away.\n", ob);
    }
    else if (ob->query_prop(ROOM_I_IS))
	tell_room(ob, "The candle inside the "+tmp+" melts away.\n");
}

/*
 * Function name: query_torch_recover
 * Description:   Return the recover string for changing tourch values
 * Returns:	  part of recover string
 */
public string
query_torch_recover()
{
    int tmp;

    if (Burn_Alarm && sizeof(get_alarm(Burn_Alarm)))
	tmp = ftoi(get_alarm(Burn_Alarm)[2]);
    else
	tmp = Time_Left;

    return "#t_t#" + tmp + "#t_l#" + query_prop(OBJ_I_LIGHT) + "#";
}

/*
 * Function name: init_torch_recover
 * Description:   Initialize the torch variables at recover.
 * Arguments:     arg - The recover string as recieved from
 *			query_torch_recover()
 */
public void
init_torch_recover(string arg)
{
    string foobar;
    int tmp;

    sscanf(arg, "%s#t_t#%d#%s", foobar, Time_Left, foobar);
    sscanf(arg, "%s#t_l#%d#%s", foobar, tmp, foobar);
    if (tmp > 0)
    {
	add_prop(OBJ_I_LIGHT, tmp);
	add_prop(OBJ_I_HAS_FIRE, 1);
	Burn_Alarm = set_alarm(itof(Time_Left), 0.0, burned_out);
    }
}

/*
 * Function name: query_recover
 * Description:   A default query_recover() for torches.
 * Returns:	  A default recovery string.
 */
public string
query_recover()
{
    return MASTER + ":" + query_torch_recover();
}

/*
 * Function name: init_recover
 * Description:   A default init_recover() for torches.
 * Arguments:	  arg - String with variables to recover.
 */
public void
init_recover(string arg)
{
    init_torch_recover(arg);
}

