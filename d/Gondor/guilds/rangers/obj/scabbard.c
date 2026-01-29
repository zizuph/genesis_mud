/*
 *  /d/Gondor/guilds/rangers/obj/scabbard.c
 *
 *  Most of this code has been ruthlessly stolen from the
 *  Golden Scabbard - /d/Gondor/ithilien/emyn-arnen/obj/scabbard.c
 *
 *  Sorry, not sorry.
 *
 *  Also, big thanks to Lucius for helping to convert 
 *
 *  Varian - May, 2020
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

#define NO_SELL_PROP       "Are you sure you want to sell your scabbard?\n"
#define ADJ                ({"dark", "light", "mottled", "dusty", \
                               "speckled", "spotted"})
#define HIP_O_SUBLOC       "hip_o_subloc"
#define LIVE_AO_HIP_SUBLOC "_live_ao_hip_subloc"
#define SCABBARD           "/d/Gondor/guilds/rangers/obj/scabbard.c"

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

    set_name("scabbard");
    add_name("rangerscabbard");
    set_adj(adj);
    add_adj("leather");
    add_adj("brown");
    set_short(short_description);
    set_pshort(adj + " brown leather scabbards");
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

    set_slots(A_L_HIP);
    set_layers(5);
    set_looseness(1);    

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
        return adj + " brown leather scabbard with a sword sheathed " +
            "inside";

    return adj + " brown leather scabbard";
}

string long_description()
{
    string long_desc = "This " + adj + " brown leather scabbard " +
        "is decorated with a silvery image of the White Tree of " +
        "Gondor and Seven Stars painted upon it. It has clearly " +
        "been designed to be worn on your hip, allowing you to " +
        "sheathe a sword inside it.";

    if (query_prop(OBJ_M_NO_SELL))
        long_desc += "At present, you do not want to sell the " +
        adj + " brown leather scabbard.\n";
    else
        long_desc += " It is possible to 'keep' this scabbard " +
	    "to prevent it from being stolen or inadvertently sold.\n";
        
    long_desc += "You can <rsheathe> a sword if the scabbard is " +
        "empty, or <rdraw> a sword if there is one sheathed inside.";
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
filter_sword(object obj)
{
    return (obj->query_wt() == W_SWORD);
}

public int
prevent_enter(object obj)
{
    if (!obj->query_wt() == W_SWORD)
    {
        write("Only swords may be sheathed inside your " + 
            query_name() + ".\n");
        return 1;
    }

    return 0;
}

public int
do_sheathe(string str)
{
    int     result;
    object *sword, wearer;

    wearer = this_player();
    
    if (!str)
    {
        sword = wearer->query_weapon(-1);
    }
    else
    {
        sword = filter(FIND_STR_IN_OBJECT(str, wearer), "filter_weapon",
            this_object());
    }
    sword = filter(sword, "filter_sword", this_object());

    if (sizeof(sword) != 1)
    {
        notify_fail("Sheathe which sword?\n");
        return 0;
    }

    if (sizeof(all_inventory(this_object())))
    {
        notify_fail("The " + sword[0]->short() + " cannot be sheathed " +
        "as " + LANG_ASHORT(all_inventory(this_object())[0]) + " is " +
        "already sheathed in your " + short() + ".\n");
        return 0;
    }

    if ( sword[0]->query_wielded() == wearer )
    {
        sword[0]->unwield_me();
        if ( sword[0]->query_wielded() == wearer )
        {
            notify_fail("You cannot unwield your " +
                sword[0]->short() + ".\n");
               return 0;
        }
    }

    remove_prop(CONT_M_NO_INS);
    if (result = sword[0]->move(this_object()))
    {
        switch (result)
        {
        case 1:
            notify_fail("The " + sword[0]->short() + " is too heavy for " +
            "the " + short() + ". That is unfortunate!\n");
            break;
        case 8:
            notify_fail("The " + sword[0]->short() + " is too large for " +
            "the " + short() + ". That is unfortunate!\n");
            break;
        default:
            notify_fail("Oddly enough, your " + sword[0]->short() + 
                "cannot be sheathed in the " + short() + ".\n");
            break;
        }
        return 0;
    }
    if(objectp(environment(wearer)))
    {
        environment(wearer)->update_light(1);
    }
    wearer->catch_msg("You sheathe your " + sword[0]->short() + ".\n");
    tell_room(environment(wearer), QCTNAME(wearer) + " sheathes "+
        wearer->query_possessive() + " " + sword[0]->short() + ".\n", wearer);
    add_prop(CONT_M_NO_INS, 1);

    return 1;
}

public int
do_draw(string str)
{
 object *sword, to, wearer, here;
 mixed res;


    wearer  = this_player();
    here = environment(wearer);

    if (!str)
    {
        sword = all_inventory(this_object());
    }
    else
    {
        sword = FIND_STR_IN_OBJECT(str, this_object());
    }
    if (!sizeof( sword ))
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
        switch (sword[0]->query_hands())
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

                notify_fail("You don't have enough hands to do " +
                    "that!\n");
                return 0;
            }
            break;
        }
    }
    wearer->catch_msg("You draw your " + sword[0]->short() + "!\n");
    tell_room(here, QCTNAME(wearer) + " draws " + wearer->query_possessive() + 
        " " + sword[0]->short() + ".\n", wearer);
    if (sword[0]->move( wearer ))
    {
        sword[0]->move( wearer, 1 );
    }
    
    if (stringp(res = sword[0]->command_wield()))
    {
        write(res);
    }
    return 1;
}

public int
wear(string str)
{
    object wearer;

    if (member_array(LIVE_AO_HIP_SUBLOC, wearer->query_sublocs()) > -1)
    { 
        if (str != "all")
        {
            write("You already wear another scabbard!\n");
            return 1;
        }
        return 0;
    } 

    wearer->add_subloc(LIVE_AO_HIP_SUBLOC, this_object());
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

    wearer->remove_subloc(LIVE_AO_HIP_SUBLOC);
    remove_prop(OBJ_M_NO_DROP);
    set_no_show_composite(0);
    return 0;
}

public void 
leave_env(object old, object dest)
{
    int ihip;
    object *hip_cont;

    ::leave_env(old, dest);

    wearable_item_leave_env(old, dest);

    if (!objectp(old) || !living(old) || !query_prop(OBJ_M_NO_SELL))
    return;

    remove_prop(OBJ_M_NO_SELL);
    remove_prop(OBJ_M_NO_DROP);
    remove_alarm(gPropAid);
    hip_cont = old->query_prop(LIVE_AO_HIP_SUBLOC);
    if ((ihip = member_array(TO, hip_cont)) > -1)
        hip_cont = exclude_array(hip_cont, ihip, ihip);
    if (sizeof(hip_cont))
        old->add_prop(LIVE_AO_HIP_SUBLOC, hip_cont);
    else
    {
        old->remove_prop(LIVE_AO_HIP_SUBLOC);
        old->remove_subloc(HIP_O_SUBLOC);
    }
}

public string
show_subloc(string subloc, object on, object for_obj)
{
 string data;

    if (subloc == LIVE_AO_HIP_SUBLOC)
    {
        if (for_obj != on)
        {
            data = capitalize(on->query_pronoun()) + 
                " is wearing " + LANG_ASHORT(this_object()) + ".\n";
        }
        else
        {
            data = "You are wearing " + LANG_ASHORT(this_object()) + ".\n";
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

    add_action(do_sheathe, "rsheathe");
    add_action(do_draw,    "rdraw"   );
    remove_name("pack");
}


