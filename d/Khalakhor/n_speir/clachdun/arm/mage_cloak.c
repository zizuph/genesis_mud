/* File         : /d/Khalakhor/n_speir/clachdun/arm/mage_cloak.c
 * Creator      : Igneous@Genesis
 * Copyright:   : Chad Richardson
 * Date         : April 23rd 1999
 * Purpose      : Magic cloak worn by F'yar a mage npc inside Clach Dun
 * Related Files: ~Khalakhor/n_speir/clachdun/npc/fyar.c
 * Comments     : A powerful artifact created by the Wise during the 
 *                Age of Legends. Should be extremely hard to obtain.
 * Modifications:
 */
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/skills.h"
#include "local.h"
#include <stdproperties.h>
#include <formulas.h>
#include <wa_types.h>
#include <macros.h>
#include <language.h>
#include <composite.h>

inherit CREST_ARMOUR;

#define CLOAK_SHADOW  (ARM_DIR + "mage_cloak_shadow")

/* Function name: create_cloak
 * Description  : This function creates the cloaks apperance and is
 *                used to reset it back to normal.
 */
void
create_cloak()
{
    set_name("cloak");
    set_adj(({"eloquent", "snow-white", "white", "snow"}));
    set_short("eloquent snow-white cloak");
    set_long("The "+short()+" appears as if made from tiny silken "+
      "snowflakes.  The snowflakes have been intricately weaved together "+
      "in a tight pattern, which seems to shift ever so slightly as you "+
      "look at it from a different angle. It appears to be completely "+
      "flawless with no visable wear or tear upon the mysterious fabric. "+
      VBFC("crest_description") + ".\n");

    add_item("crest", VBFC("crest_description") + ".\n");
}

/* Function name: crest_description
 * Purpose      : To have a varied description for the crest
 *                depending on the players Khalakhor lore skill
 * Returns      : The description of the crest
 */
string
crest_description()
{
    string to_write;
    int skill;

    to_write = "Upon the "+short()+" there is a crest of "+query_crest_desc();

    skill = TP->query_skill(SS_KHALAKHOR_LORE);
    if (skill >= 20)
    {
	to_write += ".  The sixteen symbols on the crest represent the "+
	"sixteen different orders of the Wise";
	if (skill >= 50)
	{
	    to_write += ". The prefect circle of the symbols represent the "+
	    "unity of the orders and how they came together to battle and "+
	    "eventually banish the chaos demon";
	    if (skill >= 75)
		to_write += ".  The swirling green is a symbol the land of "+
		"of Khalakhor itself and is placed underneath the circle as "+
		"a reminder that the formation of the Wise was to save "+
		"the very existance of their homeland";
	}
    }
    return to_write;
}

/* Function name: create_crest_armour
 * Description  : The armour constructor function
 */
void
create_crest_armour()
{
    set_crest_desc(WISE_CREST);
    set_crest_id(WISE_ID);

    create_cloak();

    set_keep(1);

    set_likely_break(0);
    set_likely_cond(0);
    set_at(A_ROBE);
    set_ac(52);
    set_am(({-2, 1, 1}));

    // This object is extremely resistant to magical effects
    add_prop(OBJ_I_RES_MAGIC,  40);
    add_prop(OBJ_I_RES_COLD,  100);
    add_prop(OBJ_I_RES_ACID,   10);
    add_prop(OBJ_I_RES_DEATH, 100);
    add_prop(OBJ_I_RES_LIFE,  100);
    add_prop(OBJ_I_RES_EARTH,  20);

    // now we add the required props for magical armours
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 90, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"This "+short()+" has been enchanted "+
	"with a powerful spell. ", 1, "The thousands of snowflakes "+
	"which make up the "+short()+" seemingly have been gifted with "+
	"an inate intelligence which makes the cloak very protective to "+
	"the wearer. ", 15,"As you probe deeper into the magics which "+
	"enchant this "+short()+" you become aware of its protective "+
	"nature verses the cold. ", 40, "The snowflakes seem to "+
	"constantly shift and move about, which makes this cloak nearly "+
	"indestructable and impossible to damage. ", 70}));
    add_prop(OBJ_S_WIZINFO, "This "+short()+" is a magical artifact, "+ 
      "and thus very powerful but it should be extremely hard to get."+
      "If worn, it is the only armour that player can wear as it must "+
      "fit snugly around the wearer. It is also virtually indestructable "+
      "(It can not be damaged and if it breaks for some reason it will "+
      "eventually repair itself).  Also it will add 75% cold resistance "+
      "(non-additive) to the wearer.\n");

    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_ARMOUR(query_ac(),query_at()) / 2);
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT) / 4);
    add_prop(OBJ_I_VALUE, (5 * F_VALUE_ARMOUR(query_ac())) + random(1000));
}

/*
 * Function name: set_condition (MASKED)
 * Description  : This cloak will never become damaged because that
 *                is one of its enchantments
 * Returns      : always 0
 */
int
set_condition(int cond)
{
    return 0;
}

/* Function name: remove_broken (MASKED)
 * Description  : When broken this cloak will repair itself
 */
varargs void
remove_broken(int silent = 0)
{
    ::remove_broken(silent);
    remove_prop(OBJ_I_BROKEN);
}

/*
 * Function name: reform_cloak
 * Description  : Reforms the cloak after it has been broken for some
 *                reason or after its been removed.
 */
void
reform_cloak()
{
    remove_prop(OBJ_M_NO_GET);
    tell_room(environment(), "The "+short()+" collects itself and "+
      "reforms back into the eloquent snow-white cloak.\n");
    remove_name("snowflakes");
    remove_name("pile");
    create_cloak();
}

/*
 * Function name: query_magic_protection
 * Description  : used to print out some messages when magic resistance
 *                is checked and alos to add resistance to cold to the 
 *                player.
 * Arguments    : string prop:  What resistance prop are we checking
 *                object protectee: who are we testing this prop for
 * Returns      : mixed array:
 *                  int   [0]: amount of protection
 *                  int   [1]: additive or non-additive
 */
varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{

    if (protectee == query_worn())
    {
	if (prop == MAGIC_I_RES_COLD)
	{
	    protectee->catch_tell("The "+short()+" compacts itself and "+
	      "wraps tightly around your body, filling you with a strange "+
	      "warmth.\n");
	    tell_room(ENV(protectee), LANG_POSS(QCTNAME(protectee)) +
	      " "+short()+" compacts itself and wraps tightly around "+
	      HIS_HER(protectee)+" body.\n", ({protectee}));
	    // We make the player 75% resistant (non-additive)
	    return ({75, 0});
	}
	if (prop == MAGIC_I_RES_FIRE)
	{
	    protectee->catch_tell("The snowflakes on the "+short()+
	      " scatter choaticly about, then suddenly fall back "+
	      "into their original arrangement.\n");
	    tell_room(ENV(protectee), "The snowflakes on "+
	      LANG_POSS(QTNAME(protectee))+" "+short()+" scatter "+
	      "choaticly about, then suddenly fall back into their "+
	      "original arrangement.\n", ({protectee}));
	    // Since negative resistances aren't supported at the moment
	    // We'll just print out a cool message to make players
	    // think that fire does something strange to this cloak ;-)
	    return ({0, 1});
	}
    }
    else
	return ::query_magic_protection(prop, protectee);
}

/* Function name: filter_armours
 * Description  : A filter to determine if we are wearing any unacceptable
 *                armours
 */
int
filter_armours(object arm)
{
    int at = arm->query_at();

    if (at & A_BACK || at & A_CHEST || at & A_LEGS || at & A_ROBE ||
      at & A_HEAD || at & A_ANY_ARM || at & A_L_ARM || at & A_R_ARM)
	return 1;

    return 0;
}


/* Function name: wear
 * Description  : A defined wear function so we can make our own
 *                messages and add some shadows to the wearer.
 * Arguments    : object arm: the armour we are trying to wear
 * Returns      : int  0 - The armour can be worn normally.
 *                     1 - The armour can be worn, but print no messages.
 *                    -1 - The armour can't be worn, use default messages.
 *                string - The armour can't be worn, use this message.

 */
public mixed
wear(object arm)
{
    object *arms;

    if (sizeof(arms = filter(TP->query_armour(-1), filter_armours)))
	return "The snowflakes scatter around your "+
	COMPOSITE_WORDS(arms->short()) +", then collect "+
	"and reform themselves back into the "+short()+".\n";

    ::wear(arm);
    clone_object(CLOAK_SHADOW)->shadow_me(TP);
    TP->set_cloak_object(TO);
    TP->add_magic_effect(arm); 
    write("The "+short()+" shimmers and you feel a cold shiver tingle "+
      "throughout your body. The tiny snowflakes, which make "+
      "up the "+short()+", collect themselves snugly around you.\n");
    say(LANG_POSS(QCTNAME(TP)) + " "+short()+" shimmers causing "+
      HIM_HER(TP)+" to shiver as it takes form around "+
      HIS_HER(TP)+" body.\n");
    return 1;
}

/* Function name: remove
 * Description  : A redefined remove function so we can remove our extra
 *                stuff this armour added as well as put in some neat 
 *                remove messages
 * Arguments    : object arm:  The armour we are removing
 * Returns      : int  0 - Remove the armour normally.
 *                     1 - Remove the armour, but print no messages.
 *                    -1 - Do not remove the armour, print default message.
 *                string - Do not remove the armour, use this message.
 */
public mixed
remove(object arm)
{
    ::remove(arm);
    query_worn()->remove_clachdun_cloak_shadow();
    query_worn()->remove_magic_effect(arm);
    set_this_player(query_worn());
    write("As you remove the "+short()+" from your body, it collaspes in "+
      "upon itself and forms thousands of individual snowflakes, which fall "+
      "gently about your feet.\n");
    say("As "+QTNAME(TP)+" removes "+HIS_HER(TP)+" "+short()+", it "+
      "collaspes in upon itself and forms thousands of individual snowflakes"+
      ", which fall gently about "+HIS_HER(TP)+" feet.\n");
    // I hate to set this with an alarm but I have to for consistancy
    set_alarm(0.0, 0.0, &set_short("pile of snowflakes"));
    set_name("snowflakes");
    add_name("pile");
    set_long("The pile of snowflakes appears to be made of thousands "+
      "of tiny silken snowflakes that have fallen into a small heap. "+
      "The snowflakes seem to be moving about slowly and seem to be "+
      "collecting themselves into something.\n");
    add_prop(OBJ_M_NO_GET, "Your fingers pass right through the "+
      "snowflakes.\n");

    remove_name("cloak");
    remove_adj(query_adjs());
    remove_item("crest");

    // I have to set this with an alarm otherwise it calls this function twice.
    set_alarm(0.0,0.0, &move(ENV(TP)));
    set_alarm(itof(10 + random(10)), 0.0, reform_cloak);
    return 1;
}
