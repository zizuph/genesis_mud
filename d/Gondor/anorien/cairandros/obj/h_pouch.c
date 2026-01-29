/*
 *  /d/Gondor/anorien/cairandros/obj/h_pouch.c
 *
 *  Modified from /d/Gondor/common/obj/herbpouch.c 
 *
 *  Just a herb pouch that can be worn on the hip. It also
 *  has the White Tree of Gondor embroidered onto it.
 *
 *  Varian - April, 2020
 */
 
#include <stdproperties.h>
#include <macros.h>
#include <files.h>
#include <cmdparse.h>
#include <composite.h>
#include <wa_types.h>
#include "/d/Gondor/defs.h"

inherit "/d/Genesis/std/pack.c";
inherit "/lib/wearable_item";
inherit "/lib/keep.c";

public string short_description();
public string long_description();
string adj;

#define NO_SELL_PROP "You don't want to sell this pouch, do you?\n"
#define ADJ ({"grey", "green", "brown", "black", "silver", "white"})

#define BELT_O_SUBLOC         "belt_o_subloc"
#define LIVE_AO_BELT_SUBLOC   "_live_ao_belt_subloc"

static int     gPropAid;

public void
create_wearable_pack()
{
}

void
set_pack_data()
{

    seteuid(getuid());

    if(!strlen(adj))
    {
        adj = one_of_list(ADJ);
    }

    set_name("pouch");
    add_name("beltpouch");
    set_adj(adj);
    add_adj("belt");
    set_short(short_description);
    set_pshort(adj + " belt pouches");
    set_long(long_description);

    add_prop(CONT_I_CLOSED, 0);
    add_prop(CONT_I_IN, 1);
    add_prop(CONT_I_RIGID, 0);
    add_prop(CONT_I_TRANSP, 0);
    add_prop(CONT_I_WEIGHT, 200);
    add_prop(CONT_I_VOLUME, 200);
    add_prop(CONT_I_REDUCE_WEIGHT, 200);
    add_prop(CONT_I_REDUCE_VOLUME, 200);
    add_prop(CONT_I_MAX_WEIGHT, 7500);
    add_prop(CONT_I_MAX_VOLUME, 7500);
    add_prop(OBJ_I_VALUE, 72);
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);
    
    set_mass_storage(1);

    set_slots(A_ANY_HIP);
    set_layers(15);
    set_looseness(8);    
    create_wearable_pack();
}

void
create_pack()
{
    set_pack_data();
    set_wf(this_object());
}

string short_description()
{
    if (sizeof(all_inventory(TO)))
        return adj + " belt pouch filled with herbs";

    return adj + " belt pouch";
}

string long_description()
{
    string long_desc = "This " + adj + " belt pouch is embroidered " +
        "with the White Tree of Gondor. It can be worn on your hip " +
        "and it looks perfect for storing herbs in. ";

    if (query_prop(OBJ_M_NO_SELL))
        long_desc += "At present, you do not want to sell this " +
        "belt pouch.\n";
    else
        long_desc += "It is possible to 'keep' this belt pouch " +
	    "to prevent it from being stolen or inadvertently sold.\n";
        
    long_desc += "You can <fill> or <empty> the " + adj + "pouch.";
    return (long_desc + "\n");
}

void
appraise_object(int num)
{
    ::appraise_object(num);

    appraise_wearable_item();
}

string query_recover()
{
    return MASTER + ":" + query_container_recover() + 
    query_keep_recover() + "&&" + adj;
}

public int
prevent_enter(object obj)
{
    if (!IS_HERB_OBJECT(obj))
    {
        write("You can only put herbs in the " + query_name() + ".\n");
        return 1;
    }

    return 0;
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
    set_pack_data(); 
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

public void leave_env(object old, object dest)
{
    int ibelt;
    object *belt_cont;

    ::leave_env(old, dest);

    wearable_item_leave_env(old, dest);

    if (!objectp(old) || !living(old) || !query_prop(OBJ_M_NO_SELL))
	return;

    remove_prop(OBJ_M_NO_SELL);
    remove_prop(OBJ_M_NO_DROP);
    remove_alarm(gPropAid);
    belt_cont = old->query_prop(LIVE_AO_BELT_SUBLOC);
    if ((ibelt = member_array(TO, belt_cont)) > -1)
        belt_cont = exclude_array(belt_cont, ibelt, ibelt);
    if (sizeof(belt_cont))
        old->add_prop(LIVE_AO_BELT_SUBLOC, belt_cont);
    else
    {
        old->remove_prop(LIVE_AO_BELT_SUBLOC);
        old->remove_subloc(BELT_O_SUBLOC);
    }
}

public void
init()
{
    ::init();

    remove_name("pack");
}

int item_filter(object obj) {
    return IS_HERB_OBJECT(obj);
}

int sort_objects_by_short(object *a, object *b)
{
    string aname = a[0]->query_herb_name ();
    string bname = b[0]->query_herb_name ();

    if (aname < bname) return (-1);
    if (aname > bname) return (1);
    return 0;
}

void describe_herbs(object *herbs, object for_obj)
{
    if (sizeof(herbs) == 0) return;
    
    int quantity = 0;
    foreach(object herb : herbs) quantity += herb->num_heap() || 1;

    string herb_description = herbs[0]->singular_short();
    string herb_name = herbs[0]->do_id_check(for_obj) 
        ? herbs[0]->query_herb_name() : "";
    
//    for_obj->catch_tell(sprintf("| %-:39s | %-:19s | %5d |\n",
//        herb_description, herb_name, quantity));

    for_obj->catch_tell(sprintf("| %,5d | %-:20s | %-:43s |\n",
        quantity, herb_name, herb_description));
}

void describe_contents(object for_obj, object *obarr)
{
    if (sizeof(obarr) == 0)
    {
        for_obj->catch_tell("  " + "The " + this_object()->short() +
            " is empty.\n");
        return;
    }

    mixed *sorted_objects = sort_array(unique_array(obarr, "query_herb_name"), 
        sort_objects_by_short);
    
    for_obj->catch_tell(
"+----------------------------------------------------------------------------+\n" +
"| Qty   | Herb Name            | Description                                 |\n" +
"|=======+======================+=============================================|\n"
);
    
    foreach(object *herbs : sorted_objects) {
        describe_herbs(herbs, for_obj);
    }    
    
    for_obj->catch_tell(
"+----------------------------------------------------------------------------+\n");
}

