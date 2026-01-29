/* This is Avena's finest weapon, a steel dagger she stole from a
   high ranking templar in Urik. It was personally blessed by 
   Hamanu, King of Urik, making it a potent weapon indeed. 
   Code (c) 1998 Damian Horton
   Updated for Raumdor, March 2001

   Updated June 2019, wasn't checking fire resistance properly.
   Replaced query_prop with query_magic_res (Arman).

   Added set_dull to return zero. It is a temporary inclusion
   to mitigate fixes to did_hit that made it dullable.
   This shouldn't be a permanent inclusion - Arman 12 June 2019.
*/

#pragma strict_types
#pragma save_binary

#include "/sys/wa_types.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Cirath/defs.h"

inherit "/std/weapon";
inherit CIRATH_DIR + "lib/pct_hurt";
inherit "/lib/keep"; //this weapon may be kept (by default it is)

#define DEBUG(x)    find_player("arman")->catch_msg("[dagger] " + x + "\n")


//Global variables
string Cold_Long = "This weapon was forged from the finest steel. "+
             "It is copiously ornamented, with 'Marcellus' scripted "+
	     "in small letters into the base of the blade. It is "+
             "curiously warm to the touch.\n"; //long when cold

string Hot_Long = "A molten-hot blade springs forth from the beautifully "+
             "crafted hilt of this steel dagger. Strangely, the hilt,"+
             " though solid metal, is merely warm, and not too hot to "+
             "grasp.\n"; //long description when hot

string Cold_Short = "ornate steel dagger"; //Short Description when cold.
string Hot_Short = "molten-bladed dagger";
int Light_Level = 0; //how much light we cast of our own accord

void create_weapon()
{
    set_name("dagger");
    add_name("_avenas_dagger_");
    set_short(Cold_Short);
    set_long(Cold_Long);

    set_adj ("steel");
    add_adj ("ornate");

    set_hit(33);
    set_pen(20);

    set_wt(W_KNIFE);
    set_dt(W_SLASH|W_IMPALE);
    set_hands(W_ANYH);

    //the magic fire takes its toll over time:
    likely_dull = 20;
    likely_corr = 1;
    likely_break = 20;
    set_keep(1);

    add_prop(OBJ_I_WEIGHT, 1200);
    add_prop(OBJ_I_VALUE,F_VALUE_WEAPON(33,28) + random(200));
    add_prop(OBJ_I_VOLUME, 450);
 
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(MAGIC_AM_MAGIC,( {40, "fire"}));
    add_prop(MAGIC_AM_ID_INFO, ({"Substantial magic has been enchanted into"+
      "this blade.\n", 10, "The blade is imbued with the power of flame.",
      25}));

    //magic resistances
    add_prop(OBJ_I_RES_FIRE, 100);//unaffected by fire
    add_prop(OBJ_I_RES_ELECTRICITY, 40);
    add_prop(OBJ_I_RES_ACID, 20);

    add_prop(OBJ_S_WIZINFO, "Requires sup. journeyman knife skill to "+
	     "wield.\nDoes 100% extra fire damage on a successful hit.");

    set_wf(TO);
    set_keep(1); //weapon is kept by default
}

/* Called when this weapon is wielded by a worthy person. The blade
   literally becomes red-hot. */
void
catch_fire()
{
    set_long(Hot_Long);
    set_short(Hot_Short);
    add_adj("molten");
    add_adj("molten-bladed");
    //make sure the dagger is not already glowing before adjusting the light
    //level
    if (! Light_Level)
    {
	Light_Level++;
	add_prop(OBJ_I_LIGHT, query_prop(OBJ_I_LIGHT) + 1);
    }
    add_prop(OBJ_I_HAS_FIRE, 1);
    //rooms tend to get cast into darkness if this isn't done:
    ENV(TO)->update_light();
    ENV(ENV(TO))->update_light();   
}

/* Called when this weapon is ceased to be wielded. The blade ceases to 
   glow red. */
void
cool_down()
{
    set_long(Cold_Long);
    set_short(Cold_Short);
    remove_adj("molten");
    remove_adj("molten-bladed");
    //make sure the dagger is not already dull (of its own accord), before
    //adjusting anything
    if (Light_Level > 0)
    {
	Light_Level--;
	add_prop(OBJ_I_LIGHT, query_prop(OBJ_I_LIGHT) - 1);
    }
    remove_prop(OBJ_I_HAS_FIRE);
    //rooms tend to get cast into darkness if this isn't done:
    ENV(TO)->update_light();
    ENV(ENV(TO))->update_light();
    
}

/* To wield this weapon you need sup.journeyman (level 50) knife skill.
   Otherwise, you are not worthy of the blade, and it will burn 
   your hand.*/
mixed
wield(object to)
{
    if(ENV(TO)->query_skill(SS_WEP_KNIFE)>49)
    {
	write("As you take the hilt of the ornate steel dagger, "+
	      "the gentle warmth of the dagger flares to a "+
	      "painfully hot level. Gradually, the blade begins to glow "+
	      "first a dull red, then the fiery color of molten metal! "+
	      "Curiously, as the blade becomes increasingly warm, the "+
	      "hilt cools down to a manageable temperature.\n");

	say("As "+QTNAME(TP)+" grasps the hilt of the ornate steel dagger, "+
	    "you notice its blade gradually change color until it is "+
	    "the fiery red of molten steel!\n");
	catch_fire();
	return 0;
    }
    
    else
    {   
	say("The ornate steel dagger flashes a fiery red as "+QTNAME(TP)+
	    " attempts to wield it.\n");
	write("As you try to wield the ornate steel dagger, it becomes "+
	      "red hot!\n");
	TP->command("drop ornate steel daggers");
	TP->heal_hp(-(random(40)));
	
	if (TP->query_hp() < 1)
	{ //burning one's hand can never be fatal
	    TP->set_hp(1);
	}
	return("You burn your hand!\n");
    }
}

mixed
unwield(object to)
{    
    set_this_player(query_wielded()); //needed because NPCs die and
                                      //consequently unwield without being
                                      //this_player()
    ENV(TO)->catch_tell("As you cease to wield the " + short() +
        ", the blade quickly cools to room temperature.\n");
    say("As " + QTNAME(TP) + " ceases to wield the " + short() + 
	", its blade quickly cools down to room temperature.\n");
    cool_down();
    return 1;
}

int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit,
	int dam)
{
    int heatdamage; //additional heat damage caused by the blade
    int resistance; //resistance to fire
    int new_phurt; //percentage hurt including fire damage

    resistance = enemy->query_magic_res(MAGIC_I_RES_FIRE);
    heatdamage = ftoi(itof(dam) * (1.0 - (itof(resistance) / 100.0)));
 
    //    wielder->catch_tell("Heatdamage = " + heatdamage);
    enemy->heal_hp(- heatdamage); //additional damage

    new_phurt = pct_hurt(dam + heatdamage, enemy);

    //DEBUG("Resistance: " +resistance+ ", heatdamage:  "+heatdamage+ ".");

    //give out special messages only if the heat damage was noticed,
    //a substantial wound was dealt		     
    if ((resistance < 70) && new_phurt > 15)
    {
	if (interactive(wielder))
	{
	    switch(new_phurt)
	    {
	    case 15..29:
		wielder->catch_msg("Your " + short() + " leaves a sizzling "+
				 "wound in " + QTPNAME(enemy) + " "+
				 hdesc + ".\n");
		break;
	    case 30..59:
		wielder->catch_msg("Your " + short() + " sears its way "+
				   "through " + QTPNAME(enemy) + " " + 
				   hdesc + "!\n");
		break;
	    default:
		wielder->catch_msg("Your " + short() + " cuts through "+
				   QTPNAME(enemy) + " " + hdesc + 
				   " as if " + HE_SHE(enemy) + 
				   " were made of butter!\n");
	    }
	}
	if (interactive(enemy))
	{
	    switch(new_phurt)
	    {
	    case 15..29:
		enemy->catch_msg(QCTNAME(wielder) + " leaves a sizzling "+
				 "wound in your " + hdesc + " with " +
				 HIS_HER(wielder) + " " + short() + ".\n");
		break;
	    case 30..59:
		enemy->catch_msg(QCTPNAME(wielder) + " " + short() + 
				 " sears its way through your " + 
				 hdesc + "!\n");
		break;
	    default:
		enemy->catch_msg(QCTPNAME(wielder) + " " + short() + 
				 " cuts through your " + hdesc + 
				 " as if it you were made of butter!\n");
	    }
	}
	
	switch(new_phurt)
	{
	case 15..29:
	    wielder->tell_watcher(QCTNAME(wielder) + " leaves a sizzling "+
				  "wound in " + QTPNAME(enemy) + " " + 
				  hdesc + " with " + HIS_HER(wielder) + " " +
				  short() + ".\n", enemy, enemy);
	    break;
	case 30..60:
	    wielder->tell_watcher(QCTPNAME(wielder) + " " + short() +
				  " sears its way through " + QTPNAME(enemy) +
				  " " + hdesc + "!\n", enemy, enemy);
	    break;
	default:
	    wielder->tell_watcher(QCTPNAME(wielder) + " " + short() +
				  " cuts through " + QTPNAME(enemy) + 
				  " " + hdesc + " as if " + HE_SHE(enemy) +
				  " were made of butter!\n", enemy, enemy);
	}
	return 1; //we handled the messages
    }
    return 0; //we did not
}
    

/*
 * Function name: set_dull
 * Description:   Use this to increases the dull status on weapons.
 * Arguments:     cond - The new condition we want (can only be raised)
 * Returns:       1 if new condition accepted
 *
 * Temporarily added this until a new dulling system is added to the game.
 * This dagger is not intended to be non-dullable, but has been for so long
 * that players are invested in its non-dullability.
 * - Arman (AoB)
 */
int
set_dull(int du)
{
    return 0;
}















