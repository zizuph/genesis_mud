/*
 * Reproduction mystic lamp for the npc Gavriel
 * /d/Avenir/common/dark/mon/gavriel.c
 * The former Mystic Cantor, who was blinded and 
 *  wanders the Underdark in a state of eternal grief
 *  over the loss of the Shrine and Valley of the Ancients.
 *  He is about stat av 190. He heals and stuns.
 *
 *  The only things that work in this lamp are bat guano
 *  and coal. The guano does 2 levels of light for 15 mins. 
 *  The coal does -1 level of darkness for 15 mins. This was
 *  cleared by Arman Feb 9, 2022.
 *
 *  Lilith, Feb 2022: -made it a spell_enhancer
 *                    -enabled darkness generation. 
 *                    -added item expiration.
 *                    -added msg when the item inside burns out.
 *  Lilith, Mar 2022: -swapped CONT_I_VOLUME for OBJ_I_VOLUME
 *                    -removed update_light(1);
 *  Lilith, Apr 2022: -got a report that the item recovery
 *                     didn't seem to be counting down. I had
 *                     a look at /lib/item_expiration and added
 *                     some more calls to item expiration funcs.
 * Lilith, May 2022:  added a call to holdable_item_leave_env(from, to);
 *                    added a check for BROKEN.
 */

inherit "/std/receptacle";
inherit "/lib/holdable_item";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";
#include "/d/Avenir/common/dark/dark.h"

int full = 0;

void
do_lamp_light_msg()
{
    tell_room(environment(environment(TO)), "Dappled patterns of light "+
      "are cast in all directions by the "+ short() +".\n");
}

void
do_lamp_dark_msg()
{
    tell_room(environment(environment(TO)), "Inky darkness suddenly "+
      "streams from the "+ short() +" in all directions.\n");	
}	

public int
prevent_enter(object ob)
{
	//Have to explicitly make it not work when broken.
    if (TO->query_prop(OBJ_I_BROKEN))
    {
    write("The "+ short() +" is broken.\n");
	return 1;
    }
	
    if (full)
    {
	write("There is no room in the "+short()+".\n");
	return 1;
    }

    // prevent burnt out items.
    if (ob->query_adj() == "burnt")
    {
	return 1;
    }

    if (ob->id("_avenir_bat_guano"))
    {
	full = 1;
	return 0;
    }

    if (ob->id("_avenir_coal"))
    {
	full = 1;
	return 0;
    }

    write("The "+ ob->short() +" does not belong in the "+ short() +".\n");
    return 1;
}

public int
prevent_leave(object ob)
{

    if (ob->id("_avenir_coal"))
    {    
	ob->extinguish_me();
	ob->set_strength(1);
	return 0;
    }
    if (ob->id("_avenir_bat_guano"))
    {
	ob->extinguish_me();
	ob->set_time(10 +random(30)); 
	return 0;
    }		
}	


void
create_receptacle()
{
    set_name("lamp");
    add_name("gavriels_mystic_lamp");
    add_name("sacred_lamp");
    set_adj("silver");
    set_short("sacred silver lamp");
    set_long("A small ornate silver lamp. It is covered with intricate " +
      "patterns of openings to allow the flow of air and light. "+ 
      "It has a small cover that looks like a tiny crown. "+
      "The cover has a hinge that connects it to the body "+
      "of the lamp so it can be opened and filled without the "+
      "lid being lost. There is a chain attached to the sides "+
      "of the lamp so it can be held without hands getting "+
      "burned.\n");

    set_magic_spellpower(45);  
    add_prop(MAGIC_AM_MAGIC, ({50,"air"}));
    add_prop(MAGIC_AM_ID_INFO, ({	
	"With ancient power this lamp was wrought.\n", 20,
	"It enhances the abilities of those who are taught\n", 25,
	"The ways of magic dark and light.\n", 30,
	"Deep in the underdark lies what you want\n", 35,
	"Mined and scavenged in places unthought\n", 40,		
	"Are coal and guano to change the sight.\n", 45, 
      }));

    add_prop(OBJ_S_WIZINFO, "This belongs to Gavriel "+
      "/d/Avenir/common/dark/mon/gavriel cloned at "+
      "/d/Avenir/common/dark/l2/add/c6\n"+
      "Only coal and guano from the Avenir Underdark "+
      "can be used to fill it. Guano will burn for 15 "+
      "mins at +2 light, while coal will burn for 15 "+
      "mins at -1 light.\n/d/Avenir/common/obj/coal "+
      "and /d/Avenir/common/obj/guano\n");		

    add_prop(CONT_I_TRANSP, 1);
    add_prop(CONT_I_RIGID,  1);
    add_prop(CONT_I_CLOSED, 1);

    //	add_prop(OBJ_I_WEIGHT,  3000);
    //	add_prop(OBJ_I_VOLUME,  3000);
    add_prop(CONT_I_WEIGHT,  3000);
    add_prop(CONT_I_VOLUME,  3000);
    add_prop(CONT_I_MAX_VOLUME,  10000);
    add_prop(CONT_I_MAX_WEIGHT,  10000);

    add_prop(OBJ_I_VALUE,   1000);

    set_keep(1);

    add_item(({"lid", "crown", "cover", "star", "four-pointed star"}), 
      "The cover of the lamp has a four-pointed star encircled "+
      "with runes.\n"); 
    add_item(({"runes" }), "The runes on the cover of the lamp are  "+
      "magical. They provoke thoughts of light and darkness.\n");
    add_item(({"chain", "chains"}), "The chain is the same metal "+
      "as the lamp. It makes it easier to carry the lamp without "+
      "being burned.\n");

    // I didn't know I needed to add this...	
    if (IS_CLONE)
	set_item_expiration();

}

void 
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);
   
    // de-activate item_expiration_combat counter.
    remove_expiration_combat_hook(this_player());
	
    if (full)
	full = 0; 

}

void 
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);	

    // activate the item_expiration_combat counter when it is 
	// being used as a lamp.
	add_expiration_combat_hook(this_player());
	
    // 15 minutes of darkness max but coal usually burns for 30 so
    // need to reduce the time.
    if (ob->id("_avenir_coal"))
    {    
	ob->extinguish_me();
	ob->set_strength(-1);
	if (ob->query_time() > 900)
	    ob->set_time(900);
	ob->light_me();
	set_alarm(1.0, 0.0, do_lamp_dark_msg);		
    }

    // usually burns for 30 seconds unless applied to a torch then it is
    // 5 mins. In this controlled env lets do 15 mins, same as the coal.	
    if (ob->id("_avenir_bat_guano"))
    {
	ob->extinguish_me();
	ob->set_time(900);
	ob->light_me();		
	set_alarm(1.0, 0.0, do_lamp_light_msg);
    }

}

public void   
hook_torch_burned_out(object ob)
{
    if (ob->id("guano"))
    {
	tell_room(ENV(TO), "The bright light cast by the "+ short() +
	  "flickers and dies.\n");
	return;
    }
    if (ob->id("coal"))
    {
	tell_room(ENV(TO), "The darkness emitting from the "+ short() +
	  " withdraws.\n");
	return;
    }     		
}

// need to add this to make sure hel items are released when leaving inventory.
void 
leave_env(object from, object to)
{
    ::leave_env(from, to);
    holdable_item_leave_env(from, to);
}

string
query_recover()
{
    return MASTER + ":" + query_container_recover() + query_item_expiration_recover();
}

void
init_recover(string arg)
{
    init_container_recover(arg);
	init_item_expiration_recover(arg);
}

void appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}

