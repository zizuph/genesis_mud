/*
 * Lowered resistance to 10+random(5). 30 was just a bit much.
 * Removed alignment restriction.
 * Finwe, November 2017
 *
 * Removal of alignment restriction made item unwearable.
 * Blocked out code that harmed players and prevented wearing it.
 * Added recovery functions to rememver add_skill amount.
 * Updated ID info and WIZINFO to reflect changes.
 * Shanoga, November 2018
 *
 */
inherit "/std/armour";
inherit "/lib/keep";

#include <wa_types.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Gondor/defs.h"

  
#define MIN_SKILL       40
 
static int     add_fire;
               
void

create_armour()
{
    set_name("ring");
    set_pname("rings");
	add_name("band");
	add_pname("bands");
    set_short("blackened steel band");
	set_pshort("blackened steel bands");
	add_adj("steel");
	add_adj("blackened");
	add_adj("fire");
	add_adj("hot");
	add_adj("simple");
    set_long("This simple band of steel feels uncomfortably hot to the "
	    + "touch. Its surface has been blackened and it smells of "
		+ "hot cinders.\n");

    set_ac(3);

    set_at(A_R_FINGER);
    set_af(TO);
    
    set_keep();

    add_prop(OBJ_I_VALUE, 2900+random(500));
    add_prop(OBJ_I_VOLUME, 5);
    add_prop(OBJ_I_WEIGHT, 30);
    add_prop(MAGIC_AM_MAGIC,(({60,"enchantment"})));

    add_prop(OBJ_I_IS_MAGIC_ARMOUR,1);
	add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(MAGIC_AM_ID_INFO,
        ({"The steel band burns with magic.\n", 1,
          "It will enhance magical abilities in those skilled enough to "
          + "wear it.\n", 20,
		  "The ability to control and summon flame will be greatly "
		  + "enhanced in any worthy wearer.\n",55}));
    add_prop(OBJ_S_WIZINFO, "This ring enhances the elemental fire skill "
          + "for those able to wear it. Minimum skill requirement of " +
          MIN_SKILL + ", and adds 10-15 to the skill.\n");
}

public int
wear(object arm)
{
    if (TP->query_skill(SS_ELEMENT_FIRE) < MIN_SKILL)
    {
        TP->catch_vbfc("You slip the "+short()+" onto your finger. " +
            "It pulses with warmth for a moment, but you sense somehow " +
            "that something is wrong.\n");
        say(QCTNAME(TP) + " slips a "+short()+" onto " 
			+TP->query_possessive() + " finger.\n");
        return 1;
    }

    if (add_fire < 10 || (TP->query_skill(SS_ELEMENT_FIRE) + add_fire > 100))
    {
        add_fire = min(10 + random(5),
                       100 - (TP->query_skill(SS_ELEMENT_FIRE)));
    }
    
    TP->set_skill_extra(SS_ELEMENT_FIRE,
        TP->query_skill_extra(SS_ELEMENT_FIRE) + add_fire);
    write("You slip the "+short()+" onto your finger. A burning "        
        + "sensation engulfs your hand as flames dance around its "
		+ "blackened surface.\n");
    say(QCTNAME(TP) + " slips a "+short()+" onto " + TP->query_possessive()
		+ " finger. Flames appear on the band as " + TP->query_pronoun() 
		+ " does so.\n");
    return 1;
}  

public int
remove(object arm) 
{
    query_worn()->set_skill_extra(SS_ELEMENT_FIRE,
        (query_worn()->query_skill_extra(SS_ELEMENT_FIRE)-add_fire));
    query_worn()->catch_tell("You remove your " + short() + ". Your hand " +
        "seems a little cooler.\n");
    say(QCTNAME(query_worn()) + " slips " + POSSESSIVE(query_worn()) +
        " " + short() + " from " + query_worn()->query_possessive() +
        " finger.\n");
    return 1; 
}

/*
 * Function name: query_recover
 * Description  : Sets the keep state and the add_fire values so they
 *                are recovered properly.
 * Returns      : string - the recovery string.
 */
public string
query_recover()
{
    return MASTER + ":" + query_arm_recover() + query_keep_recover() +
        "&&" + add_fire;
}

/*
 * Function name: init_recover
 * Description  : Restores the initial add_fire and keep values upon recovery
 * Arguments    : string - the recovery string.
 */
public void
init_recover(string arg)
{
    string *a = explode(arg, "&&");
    
    if (sizeof(a) > 1)
    {
        add_fire = atoi(a[1]);

        init_arm_recover(a[0]);
        init_keep_recover(a[0]);
    }
}
