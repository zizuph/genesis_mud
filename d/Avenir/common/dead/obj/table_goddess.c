/* Table for Mascarvin's Throne room.
 * This is full of treasures, some of them magical.
 * This table is a trap. Greedy players who take from
 * this table without the permission of the Goddess 
 * Herself will lose everything. Everything as in
 * everything on their person, as well as their lives.
 * Remember, Mascarvin despises Nitikas, god of avarice.
 *   Lilith June 2021
 *
 * Revisions: Lilith, Mar 2022: fixed runtime error with paralyze.
 */

#include "/d/Avenir/common/dead/mascarvin/defs.h"
inherit "/std/container";
// inherit "/d/Avenir/inherit/logrotate";   -- this is causing an error :(
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "/d/Genesis/gems/gem.h"

#define WRITE_THIS_LOG(file, msg) \
             (write_file(file, ctime(time()) + " " + \
             this_player()->query_name() + "(" + \
             this_player()->query_average_stat() + ") " + \
             (msg)))
			 
object vase, rose, kmask, gem, pom, pep, straw, truf, torch, neck, bryn, para, poison, coin;

public int
special_sort(object a, object b)
{
    int v1, v2;

    v1 = a->query_prop(OBJ_I_VOLUME);
    v2 = b->query_prop(OBJ_I_VOLUME);

    if (v1 == v2)
	return 0;
    if (v1 < v2)
	return 1;
    if (v1 > v2)
	return -1;
}

public object *
largest_ten(object *obs)
{
    return sort_array(obs, special_sort)[0 .. min(5, sizeof(obs) - 1)];
}

public string
external_within(void)
{
    object *stuff;
    string str = " Near the throne of skulls is a lacquered wood table";

    stuff = FILTER_DEAD(all_inventory(TO));
    if (!sizeof(stuff))
	return str + ".";
    else if (sizeof(stuff) <= 5)
	return str + ", upon which lies " + COMPOSITE_DEAD(stuff) + ".";
    else
	return str + ", upon which many things are neatly arranged, including "+
	COMPOSITE_DEAD(largest_ten(stuff)) + ".";
}

public string
within(void)
{
    object *stuff;

    if (!query_prop(CONT_I_CLOSED))
	return "";

    stuff = FILTER_DEAD(all_inventory(TO));
    if (!sizeof(stuff))
	return " The mirror-like surface of the lacquered tabletop is bare.";
    else
	return " Lying atop the mirror-like surface of the lacquered table is "+ 
	COMPOSITE_DEAD(stuff) + ".";
}

/* Fill this table up with tempting goodies.
 * If player steals from Mascarvin they will 
 * regret it.
 */
public void
reset_container(void)
{
    int size;

    // make a vase, fill it with flowers
    if (!objectp(vase))
    {
	object obj;

	vase = clone_object(OBJ + "vase_goddess");
	vase->move(TO, 1);

	// Mascarvin's Magical Rose. This is player's one chance to get one.
	// Hidden in plain sight in a vase with other flowers.
    if (!objectp(rose))
    {	
        rose = clone_object(FLAME_ROSE);
	    rose->set_petals(5);
	    rose->move(vase, 1);
    }
	size = 3;
	while(size--)
	{
	    if (!catch(obj = clone_object(BAZAAR + "Obj/flower/single")))
	    {
		obj->set_colour(one_of_list(({"blue-black","blood-red","pinkish-white"})));
		obj->set_type(one_of_list(({"orchid","lily","peony"})));
		obj->create_flower();
		obj->move(vase, 1);
	    }
	}

    }

    // kesoit death mask
    if (!objectp(kmask))
    {	
    kmask = clone_object(OBJ +"kesoit_mask_mascarvin");
	kmask->move(TO,1);
    }

    // Naiad's necklace. Most players got it long ago and 
    // doing the Bury Bones Quest and lost it at logout 
    // without ever getting a chance to put it to use.
    // Here is a second chance at it.
    if (!objectp(neck))
    {	
	neck = clone_object(OBJ +"necklace");
	neck->move(TO,1);
    }

    // She keeps her favorite gems on the table.
    if(!objectp(gem))
    {
	gem = clone_object("/d/Genesis/gems/obj/diamond_black");
	gem->set_heap_size(6 +(random(10)));
	gem->move(TO,1); 
    }		

    // A goddess can be vain, yes?	
    if (!objectp(pom))
    {
	pom = clone_object("/d/Avenir/common/city/zigg/obj/pomade");
	pom->move(TO, 1);
    }
    // Beautiful torches
    if (!objectp(torch))
    {
	size = random(5) + 2;
	while(size--)
	{
	    torch = clone_object("/d/Avenir/union/tomb/obj/ivory_torch");
	    torch->move(TO, 1);
	}
    }
    // love the treats from the ziggurat, let's add some here.
    if(!objectp(pep))
    {
	gem = clone_object("/d/Avenir/common/city/zigg/food/drop");
	gem->set_heap_size(10 +(random(10)));
	gem->move(TO,1); 
    }		
    if(!objectp(straw))
    {
	gem = clone_object("/d/Avenir/common/city/zigg/food/cstrawberry");
	gem->set_heap_size(6 +(random(8)));
	gem->move(TO,1); 
    }		
    if(!objectp(truf))
    {
	gem = clone_object("/d/Avenir/common/city/zigg/food/truffle");
	gem->set_heap_size(6 +(random(8)));
	gem->move(TO,1); 
    }		
    coin = clone_object("/d/Avenir/common/obj/syb_coin");
    coin->set_heap_size(3+random(5));
    coin->move(TO, 1);
}

public void
create_container()
{
    if (!IS_CLONE)
	return;

    seteuid(getuid(TO));

    set_name(({"table", "_mascarvin's_table"}));
    set_adj(({"lacquered","wood","kesoit"}));
    set_short("lacquered kesoit table");
    set_long("A large table, smooth and sleek with layers of lacquer. "
      +"It is made of the wood of the kesoit tree, dark reddish-black "
      +"with a fine red-gold grain. It is crafted with such precision you "
      +"wonder if it isn't made from a single block of wood.@@within@@ ");

    remove_prop(CONT_I_TRANSP);
    add_prop(CONT_I_MAX_WEIGHT, 500000);
    add_prop(CONT_I_MAX_VOLUME, 500000);
    add_prop(CONT_I_WEIGHT, 100000);
    add_prop(CONT_I_VOLUME, 100000);
    add_prop(OBJ_I_VALUE, 1906);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "It is far too heavy to move.\n");
    add_prop(CONT_I_ATTACH, 1);

    set_no_show_composite(1);
    reset_container();
}

void
caught_red_handed(object tp)
{	
    object para; 
	
    // Add thief prop, update quest stage,
    tp->add_prop(BAAAD_MORTAL, 1);
    tp->set_skill(SS_MASQ_STAGE, STAGE_6_THIEF);

    // Poison them to give them a scare and make
    // sure they cannot evade Mascarvin by quitting.	
    poison=clone_object(POISON)->move(tp, 1);
    poison->start_poison();

    // Paralyze them until Mascarvin done with them.
    // para=clone_object(PARA)->move(tp, 1);
	para = clone_object("/std/paralyze");
    para->set_stop_verb("");
    para->set_remove_time(300); // 5 mins
    para->set_stop_fun("unparalyze");
    para->set_stop_message("The paralysis wears off.\nYou can move again.\n");
    para->set_fail_message("You are paralyzed! You can't do that right now.\n");
    para->move(tp);

    // Get them out of the primary quest room.
    // Move them to the room with the thief sequence.
    tp->move_living("X", RAGING, 1, 1);
}

/*
 * This function should help determine who is a thief 
 * that would dare steal from a goddess, and who has
 * manners and is willing to wait for an invitation.
 */
public int
prevent_leave(object ob)
{
    if (!interactive(TP))
	return 0;

    // Did the player finish the Meet Mascarvin Quest properly?
    if (CHECK_QUEST_MASQ(TP))
    {
	WRITE_THIS_LOG(MASQ_GET_LOG, "took "+ob->short() +".\n");
	return 0;
    }
    // If player uses command 'get all' this should reduce 
    // spamming of messages.
    if (present(PARA_ID, TP))
	return 1;

    // No? Oh mortal, you should be afraid. Very afraid.
    write("A deathly-cold spectral hand grips you from behind, "+
      "freezing you in place.\n");
    write("The voice of Mascarvin reverberates in your mind: "+
      "You will regret trying to steal from me!\n");
    say(QCTNAME(TP)+" starts to reach for something on "+
      "the "+ short()+", but freezes in place.\n");
    WRITE_THIS_LOG(MASQ_GET_LOG, "tried to take "+
      ob->short() +" from Her table.\n");
    // Consequences.		
    caught_red_handed(TP);	
    return 1;
}
