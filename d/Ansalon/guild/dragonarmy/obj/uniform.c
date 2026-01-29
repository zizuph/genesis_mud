/*
 * Uniform for Dragonarmy members.
 * Coded by Arman 30/1/99
 *
 * Rewriten by Milan.
 *
 */
#pragma strict_types
#pragma save_binary

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <formulas.h>
#include "../guild.h"

#define SOLDIER_I_WEAR_UNIFORM "_soldier_i_wear_uniform_"
#define ONE_OF(x)     ((x)[random(sizeof(x))])

private string colour = "blue";
private int dalevel = 0;
private string uni_desc = "";
private object shadow;
private int kills = 0;
private string chosen_short = "";
private string* states = ({"repaired",
			  "fresh new",
			  "new",
			  "used",
			  "little worn down",
			  "worn down",
			  "damaged",
			  "badly damaged",
			  "ravaged",
			  "cut to ribbons"});

/* Prototypes */
void set_colour(string str);
void set_uni_desc();
int no_steal();

public nomask void
create_object()
{
    set_wf(TO);
    seteuid(getuid());

    set_name("uniform");
    set_long("@@long_desc");
    add_adj(({colour, "dragonarmy"}));
    set_uni_desc();

    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_NO_STEAL, no_steal);
    add_prop(OBJ_I_WEIGHT, 250);
    add_prop(OBJ_I_VOLUME, 150);
    add_prop(OBJ_I_VALUE, 0);

    set_slots(A_ROBE);
    set_looseness(20);
    set_layers(1);
    set_keep(1);
}

int
query_dragonarmy_uniform()
{
    return 1;
}

void
set_uni_desc()
{
    switch(dalevel)
    {
    case 1:
	uni_desc = "Its sleeves are marked with silver military stripes. "+
                   "It is the standard issue for soldiers of the Dragonarmies";
	break;
    case 2:
	uni_desc = "It is marked with regalia indicating "+
	           "the wearer is an officer of the Dragonarmies.";
	break;
    case 3:
	uni_desc = "This smart looking uniform has the "+
	           "insignia of a silver hawk holding a black star "+
		   "pinned on the collar, marking the wearer as a "+
		   "member of the Dragonarmy High Command.";
	break;
    case 4:
	uni_desc = "This impressive uniform has the insignia "+
		   "of a silver hawk holding a black star pinned on " +
		   "the collar, and five golden studs decorate "+
		   "its right sleeve, marking the wearer as a " +
		   "General of one of the five Dragonarmies.";
	break;
    default:
	uni_desc = "It looks fairly plain and worn, a "+
		   "hand-me-down, for new recruits.";
    }
}

int
no_steal()
{
    return (query_worn() ? 1 : 0);
}


string
long_desc()
{
    return "A "+colour+" dragonarmy uniform. "+uni_desc+"\n";
}

public varargs string
short(object for_obj)
{
    string myshort;

    switch(dalevel)
    {
    case 4:
	myshort = "uniform of a General of "+C(colour)+" Dragonarmy";
	break;
    case 3:
	myshort = colour+" uniform of a dragonarmy High Officer";
	break;
    case 2:
	myshort = colour+" uniform of a dragonarmy officer";
	break;
    case 1:
	myshort = colour+" uniform of a dragonarmy soldier";
	break;
    default:
        myshort = colour+" uniform of a dragonarmy recruit";
    }

    if (query_prop(OBJ_I_BROKEN))
	return "scrap of "+myshort;

    if(chosen_short == "")
    {
	chosen_short = ONE_OF(states);
    }

    return chosen_short + " " + myshort;
}

void
init()
{
    ::init();
    ADA("adjust");
    ADA("discard");
    ADA("play");
    ADA("wipe");
}

int
adjust(string str)
{
    if(query_worn() != TP || str != "uniform")
	return 0;
    write("You adjust your "+short()+ " neatly on your shoulders.\n");
    say(QCTNAME(TP)+ " adjusts " +HIS(TP)+ " " +short()+
	" neatly on " +HIS(TP)+ " shoulders.\n");
    return 1;
}

int
discard(string str)
{
    if(str != "uniform" || E(TO) != TP)
	return 0;
    if(query_worn() == TP)
    {
	write("Remove uniform first!\n");
	return 1;
    }
    write("You discard your "+short()+".\n");
    TO->remove_object();
    return 1;
}

int
play(string str)
{
    if(query_worn() != TP || str != "with uniform")
	return 0;
    write("You play with your " +short()+ " nervously.\n");
    say(QCTNAME(TP)+" plays with "+HIS(TP)+" "+short()+" nervously.\n");
    return 1;
}

int
wipe(string str)
{
    if(query_worn() != TP || str != "uniform")
	return 0;
    write("You wipe the blood from your latest kill off your " +
    short()+ " in disgust.\n");
    say(QCTNAME(TP) + " wipes the blood from " +HIS(TP)+
	" latest kill off "+HIS(TP)+ " " +short()+
	" in disgust.\n");
    return 1;
}

void
set_colour(string new_colour)
{
    remove_adj(colour);
    colour = new_colour;
    set_short(0);
    set_adj(colour);
}

void set_color(string c) { set_colour(c); }
string query_colour() { return colour; }
void set_dalevel(int i) { dalevel = i; set_uni_desc(); }
int query_dalevel() { return dalevel; }

/*
 * Function name: wear
 * Description  : Called from the armour when worn
 * Arguments    : what - The object worn.
 * Returns      : True if it went ok, a string or -1 otherwise
 */
public mixed
wear(object what)
{
    if (what != TO)
        return -1;

    if (TP->query_prop(SOLDIER_I_WEAR_UNIFORM))
        return "You cannot wear two uniforms at once.\n";

    if (!objectp(shadow))
    {
	setuid();
	seteuid(getuid());
	shadow = clone_object(DRAGONARMY_SH + "uniform_sh");
	shadow->set_uniform(TO);

	if (!shadow->shadow_me(TP))
	{
	    shadow->remove_shadow();
	}
    }

    TP->add_prop(SOLDIER_I_WEAR_UNIFORM, 1);
    return 0;
}


/*
 * Function name: remove
 * Description  : Called when the robe is removed
 * Arguments    : what - The object being removed
 * Returns      : False or -1.
 */
public mixed
remove(object what)
{
    object tp = this_player();

    if (what != TO)
        return -1;
    tp->remove_prop(SOLDIER_I_WEAR_UNIFORM);

    shadow->remove_shadow();
    return 0;
}

/*
 * Function name: leave_env
 * Description  : Called when the robe leaves its environment.
 */
public void
leave_env(object from, object to)
{
    ::leave_env(from, to); 
    wearable_item_leave_env(from, to);
    // The following line causes an infinite recursion when impale
    // deals a death to a person wearing this uniform.
//    from->update_actions();
}

void
appraise_object(int num)
{
    ::appraise_object(num);
    appraise_wearable_item();
}


string
query_recover()
{
    return 0;
}

string
query_auto_load()
{
    if(!IS_MEMBER(E(TO)))
	return 0;
    return MASTER+":"+query_keep_recover()+"#DAU#"+dalevel+"#"+colour+"#";
}

public void
init_arg(string arg)
{
    string foobar;
    init_keep_recover(arg);
    sscanf(arg, "%s#DAU#%d#%s#%s", foobar, dalevel, colour, foobar);
    set_colour(colour);
    set_uni_desc();
}

/* uniform will never break */
void
remove_broken(int silent = 0)
{
}

int
add_prop_obj_i_broken(mixed x)
{
    return 1;
}

