/*
 * magic resistance amulet
 * The amulet provides resistance according to gem inserted.
 * The gem dissolves after some time and amulet starts to shine
 * After amulet stops to shine, player will be able to insert another gem
 * If no gem inserted for some time, amulet itself will dissolve
 * - Boreaulam, Sep 2014
 */
inherit "/std/armour";

#include "defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>

#define GEM_DISSOLVE_WARN_TIME 3000.0
#define GEM_DISSOLVE_TIME 600.0
#define LIGHTS_OUT_TIME 3600.0
#define AMULET_DISSOLVE_TIME 14400.0

#define FILLED_STATE 0
#define EMPTY_STATE 1
#define FLASHING_STATE 2

#define AMULET_POWER 10


string *gems = ({"ruby", "emerald", "diamond", "topaz", "sapphire"});
int amulet_state;
int alarm_id; 
int gem_index;


void start_disolving();
void warn_dissolving_gem();
void dissolve_gem();
void lights_out();
void dissolve_amulet();

/*
 * Function name:        create_armour
 * Description  :        constructor for the object
 */
void
create_armour()
{
    set_name("amulet");
    set_short("golden amulet");
    set_adj("golden");
	add_adj("gold");
    set_long("@@get_long");
	set_default_armour(1, A_NECK, 0, this_object());
	
	gem_index = 0;
	
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_WEIGHT, 1000);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO, ({
        "This amulet is enchanted.\n", 5,
        "The enchantment is different and temporary.\n", 40, 
        "The enchantment will give some elemental resistance.\n", 50, 
        "The elemental resistance depends on a gem inside.\n", 60}));
                                 
    add_prop(MAGIC_AM_MAGIC, ({50, "enchantment"}));
} /* create_armour */

/*
 * Function name:        init
 * Description  :        inits and adds commands
 */
void
init()
{
    ::init();
    add_action("pry_gem", "pry", 0);
	add_action("insert_gem", "insert", 0);
} /* init */

/*
 * Function name:        get_long
 * Description  :        returns long descriptions depends on state and gem type
 */
string
get_long()
{
	string out = "This amulet is hanging from a massive golden chain. ";
	if(amulet_state == EMPTY_STATE)
		return  out + "The central part of the amulet contains an empty socket."
		            + " You might be able to insert a gem into socket.\n";
	if(amulet_state == FLASHING_STATE)
		return  out + "The central part of the amulet contains an empty socket."
		            + " It radiates some light.\n";

	return out + "The central part of the amulet contains a " + gems[gem_index] + ".\n";
} /* get_long */

/*
 * Function name:        start_disolving
 * Description  :        starts timer to dissolving sequence
 */
void
start_disolving()
{
    alarm_id = set_alarm(GEM_DISSOLVE_WARN_TIME, 0.0, &warn_dissolving_gem());
} /* start_disolving */

/*
 * Function name:        warn_dissolving_gem
 * Description  :        warns player about gem to be resolved and starts timer to dissolve gem
 */
void 
warn_dissolving_gem()
{
	write("The gem in the amulet starts to appear a little less solid.\n");
    alarm_id = set_alarm(GEM_DISSOLVE_TIME, 0.0, &dissolve_gem());
} /* warn_dissolving_gem */

/*
 * Function name:        dissolve_gem
 * Description  :        dissolves gem in amulet, adds light and starts timer to remove light
 */
void
dissolve_gem()
{
	amulet_state = FLASHING_STATE;
	write("Suddenly a golden amulet starts to vibrate. The gem inside the " +
        "socket turns to dust that is quickly absorbed back into amulet. " +
        "The golden amulet starts to shine. \n");
    add_prop(OBJ_I_LIGHT, query_prop(OBJ_I_LIGHT) + 2);   
    alarm_id = set_alarm(LIGHTS_OUT_TIME, 0.0, &lights_out());
} /* dissolve_gem */

/*
 * Function name:        lights_out
 * Description  :        removes light and starts timer to dissolve amulet
 */
void 
lights_out()
{
	write("A golden amulet has one last bright flash of light before it " +
        "goes dark.\n");
	amulet_state = EMPTY_STATE;
    add_prop(OBJ_I_LIGHT, query_prop(OBJ_I_LIGHT) - 2);   
    alarm_id = set_alarm(AMULET_DISSOLVE_TIME, 0.0, &dissolve_amulet());
} /* lights_out */

/*
 * Function name:        dissolve_amulet
 * Description  :        dissolves amulet
 */
void 
dissolve_amulet()
{
	write("A golden amulet disappears in a flash of light.\n");
    remove_object();
} /* dissolve_amulet */

/*
 * Function name:        pry_gem
 * Description  :        removes gem from amulet and starts timer to dissolve amulet
 */
int 
pry_gem(string arg)
{
    notify_fail("Pry what?\n");
    if((arg!="gem") && (arg != gems[gem_index]))
        return 0;
		
	amulet_state = EMPTY_STATE;
	remove_alarm(alarm_id);
	write("With a mighty effort, you pull the gem out of its socket.\n" +
        "The gem quickly crumbles into dust in your hand.\n");
    alarm_id = set_alarm(AMULET_DISSOLVE_TIME, 0.0, &dissolve_amulet());
	return 1;
} /* pry_gem */

/*
 * Function name:        insert_gem
 * Description  :        inserts gem into amulet and starts dissolving sequence
 */
int 
insert_gem(string arg)
{
    notify_fail("Insert what?\n");
	object gem = present(arg, this_player());
	if(!gem)
		return 0;
	string gem_name = gem->query_name();
	gem_index = member_array(gem_name, gems);
    if(gem_index == -1) 
	{
		write("You cannot seem to fit the " + gem_name + " inside your " +
            "gold amulet. It is almost as if there is some magical force " +
            "rejecting it.\n");
		return 1;
	}
	if(amulet_state != EMPTY_STATE)
	{
		write("There is a gem inside the amulet already.\n");
		return 1;
	}
	
	// inserting gem
	amulet_state = FILLED_STATE;
	gem->remove_object();
	
	remove_alarm(alarm_id);
	write("You insert a " + gem_name + " into the open socket and the " +
        "golden amulet suddenly flashes brightly.\n");
	start_disolving();
	return 1;	
} /* insert_gem */

/*
 * Function name:        query_magic_protection
 * Description  :        returns resistance based on gem type
 */
mixed
query_magic_protection(string prop, object what)
{
    if (what == query_worn() && amulet_state == FILLED_STATE)
    {
		if(gems[gem_index] == "ruby" && (prop == MAGIC_I_RES_FIRE || prop ==  MAGIC_I_RES_LIFE))
			return ({ AMULET_POWER, 1 });
		if(gems[gem_index] == "sapphire" && (prop == MAGIC_I_RES_COLD || prop ==  MAGIC_I_RES_WATER))
			return ({ AMULET_POWER, 1 });
		if(gems[gem_index] == "emerald" && (prop == MAGIC_I_RES_POISON || prop ==  MAGIC_I_RES_ACID))
			return ({ AMULET_POWER, 1 });
		if(gems[gem_index] == "diamond" && (prop == MAGIC_I_RES_DEATH || prop ==  MAGIC_I_RES_AIR))
			return ({ AMULET_POWER, 1 });
		if(gems[gem_index] == "topaz" && (prop == MAGIC_I_RES_ELECTRICITY || prop ==  MAGIC_I_RES_EARTH))
			return ({ AMULET_POWER, 1 });
    }

    return ::query_magic_protection(prop, what);
} /* query_magic_protection */

/*
 * Function name:        wear
 * Description  :        applies magic effect
 */
public mixed
wear(object ob)
{
    object  tp = this_player();
	
    // sanity checks.
	if ((ob != this_object()) || (tp != environment(this_object())))
        return -1;

    tp->add_magic_effect(this_object());
    return 0;
} /* wear */

/*
 * Function name:        remove
 * Description  :        removes magic effect
 */
public mixed
remove(object ob)
{
    object  tp = this_player();

    // sanity checks.
    if ((ob != this_object()) || (tp != query_worn()))
        return -1;

    if (!living(tp)) 
        return 0;

    tp->remove_magic_effect(this_object());
	return 0;
} /* remove */

