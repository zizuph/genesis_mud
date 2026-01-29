/*
 *  The standard herb.
 *
 *  The original made by Elessar Telcontar of Gondor, 
 *		Genesis, April to July 1992.
 *
 */

inherit "/std/object";

#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/ss_types.h"
#include "/sys/herb.h"


/*
 * Variables
 */
int find_diff, id_diff, decay_time, herb_value, inited_once, dried, dryable;
string id_long, unid_long, ingest_verb, herb_name, poison_file;
mixed *effects;

/*
 * Prototypes
 */
int do_id_check(object player);

/* 
 * Function name: do_tmp_stat
 * Description:   This function is called from the effects if the herb is
 *                stat-affecting. One stat is randomly increased
 *                temporarily, lasting as long as strength * 10. If strength is
 *                negative, the stat is decreased instead.
 * Arguments:     stat     - The number of the stat
 *		  strength - How strong the herb is - time effect will last
 */
void
do_tmp_stat(int stat, int strength)
{
    if (strength > 0)
    {
     	this_player()->add_tmp_stat(stat, random(3) + 1,
		strength / 2 + random(strength));
    	if (stat == SS_STR) write("You feel strengthened.\n");
    	else if (stat == SS_DEX) write("You feel more dexterious.\n");
    	else if (stat == SS_CON) write("You feel healthier.\n");
    	else if (stat == SS_INT) write("You feel brighter.\n");
    	else if (stat == SS_WIS) write("You feel wiser.\n");
    	else if (stat == SS_DIS) write("You feel more secure.\n");
    	else write("You feel more clever.\n");
    }

    if (strength < 0)
    {
    	this_player()->add_tmp_stat(stat, -(random(3) + 1), strength / 2 +
		random(strength));
    	if (stat == SS_STR) write("You feel weakened.\n");
    	else if (stat == SS_DEX) write("You feel slower.\n");
    	else if (stat == SS_CON) write("You feel less healthy.\n");
    	else if (stat == SS_INT) write("You feel stupider.\n");
    	else if (stat == SS_WIS) write("You feel less wise.\n");
    	else if (stat == SS_DIS) write("You feel more insecure.\n");
    	else write("You feel less clever.\n");
    }
}

/*
 * Function name: add_resistance
 * Description:   This function is called from the herb-effects, and adds some
 *                resistance in the player. Max strength is 40.
 *                The resistance added is an additive resistance.
 *                (See /doc/man/general/spells for more info on resistance)
 * Arguments:     res_type - The resistance type
 *		  strength - How strong the herb is
 */
void
add_resistance(mixed res_type, int strength)
{
    object res_obj;
    res_obj = clone_object(RESISTANCE_FILE);
    if (strength > 40)
	strength = 40;
    res_obj->set_strength(strength);
    res_obj->set_time(5 * (40 - strength / 2) + 5 * random(strength));
    res_obj->set_res_type(res_type);
    res_obj->move(this_player());
    write("You feel more resistant.\n");
}

/*
 * Function: special_effect
 * Description: Redefine this when you have done set_effect(HERB_SPECIAL);
 *              to do the effect of your herb.
 */
void
special_effect()
{
  write("You don't feel any effect.\n");
}

/* 
 * Function: do_herb_effects
 * Description: In this function the effect(s) of the herb are resolved.
 *              To define a standard effect, do 
 *              set_effect(herb_type, str, strength); in create_herb(),
 *              where herb_type is one of the herb-types in /sys/herb_types.h,
 *              str is a string for the affect type, and strength is an
 *              integer for the strength of the effect.
 *              Read /doc/man/general/herbs for more information.
 *              One effect per herb should be the norm, but adding one or
 *              two is ok, as long as they don't make the herb too good.
 */
nomask int
do_herb_effects()
{
    int strength, res, i, n, a;
    string type;
    object poison, tp, to, *inv;

    tp = this_player();
    to = this_object();
    i = 0;
    while (i < sizeof(effects) / 3)
    	switch(effects[i])
        {
      	    case HERB_HEALING:
		type = lower_case(effects[i * 3 + 1]);
		strength = effects[i * 3 + 2];
		res = 100 - tp->query_magic_res(MAGIC_I_RES_POISON);
		if (!type || type == "hp")
	  	{
	    	    if (strength < 0) 
	      	    { 
			tp->reduce_hit_point(res * random(-strength) / 100);
			if (tp->query_hp() <= 0)
			{
		  	    write("You die from " + ingest_verb + "ing a " +
				short() + "!\n");
		  	    tp->do_die(to);
		  	    remove_object();
			}
			write("You feel healthier.\n");
	      	    }
	    	    else if (strength > 0)
		    {
	      		tp->set_hp(tp->query_hp() + strength);
	    		write("You feel less healthy.\n");
		    }
	    	    else
			write("You don't feel any effect.\n");
	  	}
		else if (type == "mana")
	  	{
	    	    if (strength < 0)
		    {
	      	        tp->set_mana(tp->query_mana() - res *
				random(-strength) / 100);
			write("You feel mentally weaker.\n");
	    	    }
		    else if (strength > 0)
		    {
	      		tp->set_mana(tp->query_mana() + strength);
	    		write("You feel mentally healthier.\n");
		    }
		    else
	    		write("You don't feel any effect.\n");
	  	}
		else if (type == "fatigue")
	  	{
	    	    if (strength < 0)
		    {
	     		tp->set_fatigue(tp->query_fatigue() - res * 
			   random(-strength) / 100);
			write("You feel more tired.\n");
		    }
		    else
		    if (strength > 0)
		    {
			write("You feel less tired.\n");
	      		tp->set_fatigue(tp->query_fatigue() + strength);
		    }
		    else
			write("You don't feel any effect.\n");
	  	}
		else
	  	    write("You don't feel any effect.\n");
		i += 3;
		break;
	    case HERB_ENHANCING:
		type = lower_case(effects[i * 3 + 1]);
		strength = effects[i * 3 + 2];
		if (!strength || ((strength < 0) && (res > random(100))))
	  	{
	    	    write("You don't feel any effect.\n");
	   	    break;
	  	}
		switch(type)
	  	{
	  	    case "dex":
	    		do_tmp_stat(SS_DEX, strength);
	   		break;
	 	    case "str":
	    		do_tmp_stat(SS_STR, strength);
	    		break;
		    case "con":
	    		do_tmp_stat(SS_CON, strength);
	    		break;
		    case "int":
	    		do_tmp_stat(SS_INT, strength);
	    		break;
		    case "wis":
	    		do_tmp_stat(SS_WIS, strength);
	    		break;
		    case "dis":
	    		do_tmp_stat(SS_DIS, strength);
	    		break;
		    case "acid":
	    		add_resistance(MAGIC_I_RES_ACID, strength);
	    		break;
		    case "cold":
	    		add_resistance(MAGIC_I_RES_COLD, strength);
	    		break;
	 	    case "electr":
	    		add_resistance(MAGIC_I_RES_ELECTRICITY, strength);
	    		break;
		    case "fire":
	    		add_resistance(MAGIC_I_RES_FIRE, strength);
	    		break;
		    case "magic":
	    		add_resistance(MAGIC_I_RES_MAGIC, strength);
	    		break;
		    case "poison":
	    		add_resistance(MAGIC_I_RES_POISON, strength);
	    		break;
	 	    default:
	    		write("You don't feel any effect.\n");
	    		break;
	  	}
		i += 3;
		break;
	    case HERB_POISONING:
		type = lower_case(effects[i * 3 + 1]);
		strength = effects[i * 3 + 2];
		if (poison_file)
	  	{
	 	    poison = clone_object(poison_file);
		    if (!poison)
	  	    {
			write("You don't feel any effect.\n");
			break;
	 	    }
	    	    if (strength)
	      		poison->set_strength(strength);
		    if (type)
	      		poison->set_type(type);
	 	    poison->move(tp);
	 	    poison->start_poison();
	  	}
		else 
	  	{
	 	    poison = clone_object(POISON_FILE);
	 	    poison->set_strength(strength);
		    poison->set_type(type);
		    poison->move(tp);
		    poison->start_poison();
	  	}
		i += 3;
		break;
	    case HERB_CURING:
		type = lower_case(effects[i * 3 + 1]);
		strength = effects[i * 3 + 2];
		inv = all_inventory(tp);
		n = 0;
		a = 0;
		while(n < sizeof(inv))
		{
	 	    if (function_exists("cure_poison", inv[n]) == POISON_FILE)
       			if (inv[n]->cure_poison(type, strength))
			{
			    a++;
			    strength /= 2;
			}
	    	    n++;
	  	}
		if (a <= 0)
		    write("You don't feel any effect.\n");
		i += 3;
		break;
   	    case HERB_SPECIAL:
		special_effect();
		i += 3;
		break;
   	    default:
		write("You don't feel any effect.\n");
		i+=3;
		break;
        }

    return 1;
}

/*
 * Function name: ingest_herb
 * Description:   This is the function that is called from the ingest-action,
 *                which is the one to redefine if you want more than one ways
 *                of ingesting the herb - both eat and smoke, for example,
 *                and you want to make the effects different for each way.
 *                This function checks if the player really meant this herb
 *                to eat, and removes the herb-object after effects are done.
 * Arguments:     str - Any extra string the player sent
 */
int
ingest_herb(string str)
{
    if (!str)
    {
    	write(capitalize(lower_case(ingest_verb)) + " what?\n");
    	return 1;
    }

    if (str == this_object()->query_name() || 
		(str == herb_name && do_id_check(this_player())))
    {
    	if (effects)
	{
	    say(QCTNAME(this_player()) + " " + ingest_verb + "s a " +
		short() + ".\n");
	    do_herb_effects();
	    remove_object();
	    return 1;
	}

    	write("You don't feel any effect.\n");
    	say(QCTNAME(this_player()) + " " + ingest_verb + "s a " +
		short() + ".\n");
    	remove_object();
    	return 1;
    }

    return 0;
}

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
 * Description:   adds the ingest-action to the player, and starts the
 *                decay-call_out. It also handles adding and removing the
 *                real-name of the herb, to implement the realism in that
 *                unskilled players won't be able to 'get athelas' from a
 *                pile of similar-looking but different herbs. :-)
 */
void
init()
{
    ::init(); /* If this isn't added cmd items won't work. */

    add_action("ingest_herb", ingest_verb);
    if (!inited_once)
    {
    	if (decay_time)
	    call_out("decay", decay_time);
    	inited_once = 1;
    }

    remove_name(herb_name);
    if (do_id_check(this_player()))
	add_name(herb_name);
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
 * Many sets and queries
 */
void
set_effect(int herb_type, string affect_type, int strength)
{
    effects = ({ herb_type, affect_type, strength });
}

void
add_effect(int herb_type, string affect_type, int strength)
{
    effects += ({ herb_type, affect_type, strength });
}

mixed *query_effect() { return effects; }

void set_ingest_verb(string str) { ingest_verb = str; }

string query_ingest_verb() { return ingest_verb; }

void set_decay_time(int i) { decay_time = i; }

int query_decay_time() { return decay_time; }

void set_dryable() { dryable = 1; }

int query_dryable() { return dryable; }

void
set_dried()
{
    dried = 1;
    dryable = 0;
    remove_call_out("decay"); 
    call_out("decay", decay_time + random(2 * decay_time));
}

int query_dried() { return dried; }

void set_herb_name(string str) { herb_name = str; }

string query_herb_name() { return herb_name; }

void set_poison_file(string str) { poison_file = str; }

string query_poison_file() { return poison_file; }

void set_id_long(string str) { id_long = str; }

string query_id_long() { return id_long; }

void set_unid_long(string str) { unid_long = str; }

string query_unid_long() { return unid_long; }

void set_id_diff(int i) { id_diff = i; }

int query_id_diff() { return id_diff; }

void set_find_diff(int i) { find_diff = i; }

int query_find_diff() { return find_diff; }

void set_herb_value(int i) { herb_value = i; }

int query_herb_value() { return herb_value; }

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
    if (dryable)
    {
    	dryable = 0;
    	dried = 1;
    	set_short("dried, " + short());
    	call_out("decay", (decay_time + random(2 * decay_time)));
    	return 1;
    }

    write("The " + short() + " slowly turns to dust as it decays.\n");
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
    set_short("unknown herb");
    set_id_long("This herb has not been described by the wizard.\n");
    set_unid_long("This is an undescribed, unknown herb.\n");
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
