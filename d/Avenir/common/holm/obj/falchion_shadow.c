/* Revisions:
 *      Zizuph, May 2021: falchion removes the perks it added.
 *      Lilith, Sep 2021: updated intox ck to > 50% of max intox
 */
inherit "/std/shadow";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Avenir/include/deities.h"

#define WIELD_PROP   "wielded_avenir_soq_"


object gSword;
int fixed = 0;

void set_sword(object ob) {    gSword = ob;      }
object query_sword()      {    return gSword;    }

/*
 * Function    : remove_falchion_perks
 * Description : Remove the quickeness benefit of the falchion
 *               when player is wearing glove on left hand. 
 */
void 
remove_falchion_perks()
{
    object* weapons = shadow_who->query_weapon(-1);

    int i;
    for (i = 0; i < sizeof(weapons); i++)
    {
        fixed = weapons[i]->remove_falchion_perks();
        if (fixed)
            return;
    }
}

/*
 * Function     : glove_check
 * Description  : This function checks to see if ob is hand
 *                armour that is being worn.
 * Arguments    : obj ob - the object to be tested.
 * Returns      : int 0: Not worn hand armour, 
 *                int 1: worn hand armour.                        
 */
int 
glove_check(object ob)
{
    int     at;

    if (!(ob->query_worn()))
        return 0;

    at = ob->query_at();

    if (at & A_R_HAND)
        return 0;
    else if (at & A_HANDS)
        return 1;
    else
        return 0;
}        

int 
test_falchion_perks()
{
    object *gloves;
    string str;
	int tox_max;

    /* If the sword isn't wielded but player is still shadowed */
    if (!gSword->query_wielded())
    {
        remove_shadow();
        return 0;
    }
  
    /*  If player has already had the good stuff removed */
    if (!fixed)    
    {

        /* Is wielder wearing hand armour? If so, remove the benefits */
        if (sizeof(gloves = filter(all_inventory(shadow_who), 
             "glove_check", this_object())))
        {        
            remove_falchion_perks();
            shadow_who->catch_msg("Your rapport with the falchion fades "+
                "away to nothingness.\n");        
            return 0;
        }

		/* 
		 * Did wielder offer a drink to the Gods? If so,
		 * Limit the benefit to 4 hours
		 */
		if (shadow_who->query_prop(I_DRANK_WITH_SYBARUN_GOD) && (shadow_who->query_prop(I_DRANK_WITH_SYBARUN_GOD) < time()))
		{	
		    shadow_who->remove_prop(I_MADE_OFFERING);
			shadow_who->remove_prop(I_DRANK_WITH_SYBARUN_GOD);
			shadow_who->catch_tell("That blessed feeling wears off.\n");
			shadow_who->command("$unwield sword_of_quickness");
		}
        /* Is wielder too intoxicated? If so, lets play with his mind a little */
		tox_max = shadow_who->intoxicated_max() / 2;	
        if (shadow_who->query_intoxicated() > (tox_max) && (!shadow_who->query_prop(I_DRANK_WITH_SYBARUN_GOD)))
        {
            switch(random(20))
            {
                case 0..4:
                str = "As the alcohol you have imbibed takes effect, "+
                      "your rapport with the falchion begins to fade. ";
                break;
                case 5..9:
                str = "The falchion seems nearly dead in your hand. "+
                      "The rapport has faded to a faint whisper. ";
                break;
                case 10..14:
                {
                    str = "Your rapport with the falchion fades away to "+
                      "nothingness. ";        
                      remove_falchion_perks();
                    break;
                }
                case 15..19:
                {
                    str = "A sense of surprise punctures your alcoholic stupor. ";
                    shadow_who->command("$unwield sword_of_quickness");
                    break;
                }
            }     
            shadow_who->catch_tell(str +"\n");
            return 0;
        }
        return 0;
    }
    return 0;
}


/*
 * Function name:   query_not_attack_me
 * Description:     The intended victim may force a fail when attacked.
 * Arguments:       who: The attacker
 *                  aid: The attack id
 * Returns:         True if the attacker fails hitting us, false otherwise.
 */
/* I AM MASKING THIS FUNCTION TO CAUSE SIDE-EFFECTS FROM USING FALCHION
 * WHILE INTOXICATED OR WEARING GLOVES.
 */
int query_not_attack_me(object who, int aid)
{
    test_falchion_perks();
    return shadow_who->query_not_attack_me(who, aid);
}

void
remove_falchion_shadow(void)
{
    remove_shadow();
}

