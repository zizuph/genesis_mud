/*
 *  /d/Gondor/guilds/rangers/obj/ron_holster.c
 *
 *  Most of this code has been ruthlessly stolen from the
 *  Golden Scabbard - /d/Gondor/ithilien/emyn-arnen/obj/scabbard.c
 *
 *  Sorry, not sorry.
 *
 *  Also, big thanks to Lucius for helping to convert 
 *
 *  Varian - May, 2020
 *
 * Adjusted the long description to reflect that this holster stores
 * bows instead of swords, and that it's worn on the back, not the
 * hip.
 * Raymundo, June 2021
 */
 
#include <stdproperties.h>
#include <macros.h>
#include <files.h>
#include <cmdparse.h>
#include <composite.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

inherit "/std/container";
inherit "/lib/wearable_item";
inherit "/lib/keep";

public string short_description();
public string long_description();
string adj;

#define NO_SELL_PROP        "Are you sure you want to sell your holster?\n"
#define ADJ                ({"dark", "light", "mottled", "silvery", \
                               "speckled", "spotted"})
#define BACK_O_SUBLOC       "back_o_subloc"
#define LIVE_AO_BACK_SUBLOC "_live_ao_back_subloc"
#define SCABBARD            "/d/Gondor/guilds/rangers/obj/ron_holster.c"

static object  Worn = 0;

static int     gPropAid;

public void
create_scabbard()
{
}

void
set_scabbard_data()
{

    seteuid(getuid());

    if(!strlen(adj))
    {
        adj = one_of_list(ADJ);
    }

    set_name("holster");
    add_name("ronholster");
    set_adj(adj);
    add_adj("leather");
    add_adj("grey");
    set_short(short_description);
    set_pshort(adj + " leather holsters");
    set_long(long_description);

    add_prop(CONT_I_IN, 1);
    add_prop(CONT_I_RIGID, 0);
    add_prop(CONT_I_TRANSP, 0);
    add_prop(CONT_I_WEIGHT, 1500);
    add_prop(CONT_I_VOLUME, 1500); 
    add_prop(CONT_I_MAX_WEIGHT, 50000); 
    add_prop(CONT_I_MAX_VOLUME, 50000); 
    add_prop(CONT_I_REDUCE_VOLUME, 500);
    add_prop(CONT_I_REDUCE_WEIGHT, 500);
    add_prop(OBJ_I_VALUE, 2000);

    set_slots(A_BACK);
    set_layers(1);
    set_looseness(5);    

    create_scabbard();
}

void
create_container()
{
    set_scabbard_data();
    set_wf(this_object());
}

string short_description()
{
    if (sizeof(all_inventory(TO)))
        return adj + " grey leather holster with a bow stored " +
            "inside";

    return adj + " grey leather holster";
}

string long_description()
{
    string long_desc = "This " + adj + " grey leather holster " +
        "is decorated with a ornate depictions of leaves and vines " +
        "curling gracefully around the words 'Arthor na Forlonnas'. " +
        "It has clearly been designed to be worn on your back, " +
        "allowing you to store a bow inside it.";

    if (query_prop(OBJ_M_NO_SELL))
        long_desc += "At present, you do not want to sell the " +
        adj + "holster.\n";
    else
        long_desc += " It is possible to 'keep' this holster " +
	    "to prevent it from being stolen or inadvertently sold.\n";
        
    long_desc += "You can <store> a bow if the holster is " +
        "empty, or <withdraw> a bow if there is one stored inside.";
    return (long_desc + "\n");
}

public nomask string
query_container_recover()
{
    return ("#c_c#" + query_prop(CONT_I_CLOSED) + "#" +
            "#c_l#" + query_prop(CONT_I_LOCK)   + "#");
}

public nomask void
init_container_recover(string arg)
{
    string foobar;
    int    tmp;
    sscanf(arg, "%s#c_c#%d#%s", foobar, tmp, foobar);
    add_prop(CONT_I_CLOSED, tmp);
    sscanf(arg, "%s#c_l#%d#%s", foobar, tmp, foobar);
    add_prop(CONT_I_LOCK, tmp);
}

static int
filter_weapon(object obj)
{
    return (function_exists("create_object", obj) == "/std/weapon");
}

static int
filter_bow(object obj)
{
    return (obj->query_wt() == W_MISSILE);
}

public int
prevent_enter(object obj)
{
    if (!obj->query_wt() == W_MISSILE)
    {
        write("Only bows may be stored inside your " + 
            query_name() + ".\n");
        return 1;
    }

    return 0;
}

public int
do_store(string str)
{
 int     result;
 object *bow, wearer;

    wearer = this_player();
    
    if (!str)
    {
        bow = wearer->query_weapon(-1);
    }
    else
    {
        bow = filter(FIND_STR_IN_OBJECT(str, wearer), "filter_weapon",
            this_object());
    }
    bow = filter(bow, "filter_bow", this_object());

    if (sizeof(bow) != 1)
    {
        notify_fail("Store which bow?\n");
        return 0;
    }

    if (sizeof( all_inventory( this_object() ) ))
    {
        notify_fail("The " + bow[0]->short() + " cannot be stored " +
        "as " + LANG_ASHORT(all_inventory(this_object())[0]) + " is " +
        "already stored in your " + short() + ".\n");
        return 0;
    }

    if (bow[0]->query_wielded() == wearer)
    {
        bow[0]->unwield_me();
        if (bow[0]->query_wielded() == wearer)
        {
            notify_fail("You cannot unwield your " +
                bow[0]->short()+ ".\n");
               return 0;
        }
    }

    remove_prop(CONT_M_NO_INS);
    if (result = bow[0]->move(this_object()))
    {
        switch (result)
        {
        case 1:
            notify_fail("The " + bow[0]->short() + " is too heavy " +
            "for the " + short() + ". That is unfortunate!\n");
            break;
        case 8:
            notify_fail("The " + bow[0]->short() + " is too large " +
            "for the " + short() + ". That is unfortunate!\n");
            break;
        default:
            notify_fail("Oddly enough, your " + bow[0]->short() + 
                "cannot be stored in the " + short() + ".\n");
            break;
        }
        return 0;
    }
    if(objectp(environment(wearer)))
    {
        environment(wearer)->update_light(1);
    }
    wearer->catch_msg("You store your " + bow[0]->short() + ".\n");
    tell_room( environment(wearer), QCTNAME(wearer) + " stores " +
        wearer->query_possessive() + " " + bow[0]->short() + ".\n", wearer);
    add_prop( CONT_M_NO_INS, 1);

    return 1;
}

public int
do_withdraw(string str)
{
    object *bow, to, wearer, here;
    mixed res;

    wearer  = this_player();
    here = environment(wearer);

    if (!str)
    {
        bow = all_inventory(this_object());
    }
    else
    {
        bow = FIND_STR_IN_OBJECT(str, this_object());
    }
    if (!sizeof(bow))
    {
        if (!str)
        {
            notify_fail("Your " + short() + " is empty!\n");
        }
        else
        {
            notify_fail("There is no " + str + " in your " + short() + 
                "!\n");
        }
        return 0;
    }

    if (this_player()->query_tool(W_BOTH))
    {
        notify_fail("But, both of your hands are occupied already!\n");
        return 0;
    }
    else
    {
        switch (bow[0]->query_hands())
        {
        case W_LEFT:
            if (this_player()->query_tool(W_LEFT))
            {
                notify_fail("Your left hand is already occupied!\n");
                return 0;
            }
            break;
        case W_RIGHT:
            if (this_player()->query_tool(W_RIGHT))
            {
                notify_fail("Your right hand is already occupied!\n");
                return 0;
            }
            break;
        case W_BOTH:
            if ((this_player()->query_tool(W_RIGHT)) || 
                (this_player()->query_tool(W_LEFT)))
            {

                notify_fail("You don't have enough hands to do that!\n");
                return 0;
            }
            break;
        }
    }
    wearer->catch_msg("You withdraw your " + bow[0]->short() + "!\n");
    tell_room(here, QCTNAME(wearer) + " withdraws "+ wearer->query_possessive() + 
        " " + bow[0]->short() + ".\n", wearer);
    if (bow[0]->move(wearer))
    {
        bow[0]->move(wearer, 1);
    }
    
    if (stringp(res = bow[0]->command_wield()))
    {
        write(res);
    }
    return 1;
}

public int
wear(string str)
{
    object wearer;

    if (member_array(LIVE_AO_BACK_SUBLOC, wearer->query_sublocs()) > -1)
    { 
        if (str != "all")
        {
            write("You already wear another scabbard!\n");
            return 1;
        }
        return 0;
    }

    wearer->add_subloc(LIVE_AO_BACK_SUBLOC, this_object());
    add_prop(OBJ_M_NO_DROP, "Remove the scabbard first!\n");
    set_no_show_composite(1);
    return 0;
}

string query_recover()
{
    return MASTER + ":" + query_container_recover() + 
    query_keep_recover() + "&&" + adj;
}

public void
set_keep(int keep = 1)
{
    if (keep)
    {
    	add_prop(OBJ_M_NO_SELL, NO_SELL_PROP);
    }
    else
    {
    	remove_prop(OBJ_M_NO_SELL);
    }
}

void init_recover(string arg)
{
    string *a = explode(arg,"&&");
    
    if (sizeof(a) >= 2)
    {
        adj = a[1];
    }

    init_container_recover(arg);
    init_keep_recover(arg);
    set_scabbard_data(); 
}

public string query_auto_load()
{
    mixed setting;

    if (setting = query_prop_setting(OBJ_M_NO_DROP))
    {
        remove_prop(OBJ_M_NO_DROP);
        gPropAid = set_alarm(0.5, 0.0, &add_prop(OBJ_M_NO_DROP, setting));
    }

    return 0;
}

public int
remove(string str)
{
    object wearer;

    wearer->remove_subloc(LIVE_AO_BACK_SUBLOC);
    remove_prop(OBJ_M_NO_DROP);
    set_no_show_composite(0);
    return 0;
}

public void 
leave_env(object old, object dest)
{
    int iback;
    object *back_cont;

    ::leave_env(old, dest);

    wearable_item_leave_env(old, dest);

    if (!objectp(old) || !living(old) || !query_prop(OBJ_M_NO_SELL))
    return;

    remove_prop(OBJ_M_NO_SELL);
    remove_prop(OBJ_M_NO_DROP);
    remove_alarm(gPropAid);
    back_cont = old->query_prop(LIVE_AO_BACK_SUBLOC);
    if ((iback = member_array(TO, back_cont)) > -1)
        back_cont = exclude_array(back_cont, iback, iback);
    if (sizeof(back_cont))
        old->add_prop(LIVE_AO_BACK_SUBLOC, back_cont);
    else
    {
        old->remove_prop(LIVE_AO_BACK_SUBLOC);
        old->remove_subloc(BACK_O_SUBLOC);
    }
}

public string
show_subloc( string subloc, object on, object for_obj )
{
 string data;

    if (subloc == LIVE_AO_BACK_SUBLOC)
    {
        if (for_obj != on)
        {
            data = capitalize( on->query_pronoun() ) + 
                " is wearing "+ LANG_ASHORT( this_object() )+ ".\n";
        }
        else
        {
            data = "You are wearing "+ LANG_ASHORT( this_object() )+ ".\n";
        }
        return data;
    }
    return 0;
}

public object
query_worn()
{
    return Worn;
}

void
init()
{
    ::init();

    add_action(do_store,       "store");
    add_action(do_withdraw, "withdraw");
    remove_name("pack");
}


