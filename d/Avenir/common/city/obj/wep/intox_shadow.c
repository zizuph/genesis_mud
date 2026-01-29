// This shadow is used by sybarun weapons to test the intox levels.
// Revisions:
//             Lilith Sep 2021: Updated intox ck to >50% of max intox.

inherit "/std/shadow";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>


#include "/d/Avenir/include/deities.h"

object gSword;

void set_khopesh_sword(object ob) {    gSword = ob;      }
object query_khopesh_sword()      {    return gSword;    }


int 
test_intox()
{
    string str;
	int tox_max;

    /* If the sword isn't wielded but player is still shadowed */
    if (!gSword->query_wielded())
    {
        remove_shadow();
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
	}
	
    /* Is wielder >50% intoxicated? If so, lets play with his mind a little */
	tox_max = shadow_who->intoxicated_max() / 2;
	if (shadow_who->query_intoxicated() > (tox_max) && (!shadow_who->query_prop(I_DRANK_WITH_SYBARUN_GOD)))
	{
        switch(random(20))
        {
            case 0..4:
            str = "As the alcohol you have imbibed takes effect, "+
                  "your ability to control your sword arm begins "+
                  "to fade. ";
            break;
            case 5..9:
            str = "The sybarun sword seems little more than a "+
                  "poker in your hand.";
			break;
            case 10..14:
            {
                str = "You seem better suited to bar brawls "+
                      "than swordplay. "; 
				shadow_who->command("$unwield kopis");
				break;
            }
            case 15..19:
            {
                str = "A sense of surprise punctures your alcoholic stupor. ";
                shadow_who->command("$unwield kopis");
                break;
            }
        }     
        shadow_who->catch_tell(str +"\n");
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
/* I AM MASKING THIS FUNCTION TO CAUSE SIDE-EFFECTS FROM USING SWORD
 * WHILE INTOXICATED.
 */
int query_not_attack_me(object who, int aid)
{
    test_intox();
    return shadow_who->query_not_attack_me(who, aid);
}

public int
remove_khopesh_intox_shadow(void)
{
    remove_shadow();
}
