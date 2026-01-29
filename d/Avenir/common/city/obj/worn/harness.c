#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/std/wearable_pack";
inherit "/lib/keep";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/sys/cmdparse.h"
#include "/sys/composite.h"

#include "/d/Avenir/include/defs.h"

#define MAX_SWORDS  2

string 
query_recover()
{
    return MASTER + ":" + ::query_container_recover();
}  

void 
create_wearable_pack()
{
    set_name("harness");
    add_name(({"armour"}));
    add_adj(({"samite", "harness", "white", "sword"}));
    set_short("white samite harness");
    set_long ("This harness is composed of finger-width bands "+
      "of white webcloth-and-platinum samite intricately woven "+
      "together. It is elegant and sturdy, designed "+
      "to carry two swords close at hand.\n");

    add_prop(OBJ_I_VALUE, 1600 + random(50));
    add_prop(OBJ_M_NO_STEAL, "That is not possible right now.\n");
    add_prop(CONT_M_NO_INS, "@@check_ins@@");
    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_REDUCE_VOLUME, 500);
    add_prop(CONT_I_REDUCE_WEIGHT, 500);
    add_prop(CONT_I_WEIGHT, 500); 
    add_prop(CONT_I_VOLUME, 500); 
    add_prop(CONT_I_MAX_WEIGHT, 500000); 
    add_prop(CONT_I_MAX_VOLUME, 500000); 

    set_mass_storage(1);
    set_looseness(15);
    set_layers(2);
    set_cf(this_object());
    set_slots(A_BACK | A_CHEST);
    set_keep(1); 

    set_alarm(1.0, 0.0, &remove_name("pack"));
}

string 
num_swords()
{
    int num = sizeof(all_inventory(this_object()));

    if (num <= 1)
	return "";

    if (num >= MAX_SWORDS)
	return "The harness already holds two swords butterfly-sheathed.";

    return capitalize(LANG_WNUM(num)) + " of the slots has " +
	"a sword sheathed in it.";
}

/* Skip over /std/receptacle's 'long' and 'short' functions */
public varargs string 
long(object for_obj)
{
    return ::long(for_obj);
}

public varargs string 
short(object for_obj)
{
    int num = sizeof(all_inventory(this_object()));
    string more = "";

    if (num == 1)
    {
	more = " carrying a sword within easy reach just over "+
	    "the shoulder";
    }

    if (num == 2)
    {
	more = " holding two swords butterfly-sheathed over "+
	    "each shoulder";
    }

    if (!query_worn()) 
	more = "";

    return real_short(for_obj) + more;
}

mixed check_ins()
{
    if (sizeof(all_inventory(this_object())) >= MAX_SWORDS)
    {
	return "All " + LANG_WNUM(MAX_SWORDS) + " slots in " +
	    "the harness are full.\n";
    }

    if (query_verb() != "sheathe" && query_verb() != "fill" &&
	query_verb() != "harness")
    {
	return "You can only fill the harness with swords.\n";
    }

    return 0;
}

/* 
 * item_filter, used to filter out certain objects when shifting stuff 
 * in or out of pack, like non-sellables, non-droppables, 
 * containers etc. 
 */
int
item_filter(object ob)
{
    if (!function_exists("create_weapon", ob))
	return 0;

    if (ob->query_wt() != W_SWORD)
	return 0;

    if (ob->query_prop(OBJ_I_BROKEN))
	return 0;

    if (ob->query_wielded())
	return 0;

    return 1;
}

public void
pack_fill_hook(object *moved)
{
    if (!sizeof(moved))
    {
	::pack_fill_hook(moved);
	return;
    }

    write("You sheathe " + COMPOSITE_DEAD(moved) +  " in your "+
      "harness, within easy reach just over your shoulder.\n");
    tell_room(environment(this_player()), QCTNAME(this_player()) + 
      " sheathes " + COMPOSITE_DEAD(moved) + " in the "+
      "white samite harness"+
      ", within easy reach just over "+ POSSESS(TP) +" shoulder.\n",
      this_player());
}

public int
pack_fill_fail()
{
    if (::pack_fill_fail())
    {
	return 1;
    }

    if (sizeof(all_inventory(this_object())) >= MAX_SWORDS)
    {
	write("Both slots in the harness are full.\n");
	return 1;
    }

    return 0;
}

public void
pack_empty_hook(object *moved)
{
    if (!sizeof(moved))
    {
	::pack_empty_hook(moved);
	return;
    }

    write("You reach over your shoulder and draw out " 
      + COMPOSITE_DEAD(moved) +" from the white samite harness.\n");
    tell_room(environment(this_player()), QCTNAME(this_player()) + 
      " reaches over a shoulder and draws out " + 
      COMPOSITE_DEAD(moved) + " from the white samite harness.\n",
      this_player());
}

/* Can't open or close it */
varargs int close(object what)
{
    return 2;
}

varargs int open(object what)
{
    return 2;
}

int harness_it(string str)
{
    object *obs, ob;

    notify_fail("Harness which sword?\n");
    if (!str || !strlen(str))
	return 0;

    if (!parse_command(str, ({}), "[the] %s", str)) 
	return 0;

    obs = FIND_STR_IN_OBJECT(str, TP);
    if (!sizeof(obs))
	return 0;

    if (sizeof(obs) > 1)
    {
	write("You must harness one sword at a time. You can use "
	  +"'fill harness' to fill your harness, and 'empty "
	  +"harness' to empty it.\n");
	return 1;
    }

    ob = obs[0];

    notify_fail(capitalize(LANG_THESHORT(ob)) + " is not a sword!\n");
    if (ob->query_wt() != W_SWORD)
	return 0;

    if (ob->move(this_object()))
    {
	write("What?");
	return 1;
    }

    write("You sheathe " + LANG_THESHORT(ob)+ " in the white "+
      "samite harness, so that it lays with its hilt just above "+
      "your shoulder.\n");
    say(QCTNAME(TP) + " sheathes " + LANG_ASHORT(ob)+ " in " + 
      POSSESS(TP) + " white samite harness, where its hilt is "+
      "visible just over "+ POSSESS(TP) + " shoulder.\n");
    return 1;
}

void 
init()
{
    ::init();

    add_action(harness_it, "harness");
    add_action(harness_it, "sheathe");
    add_action(harness_it, "hsheathe");
//    add_action(harness_it, "hdraw");
}
