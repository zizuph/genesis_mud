/* /d/Avenir/common/dead/obj/spectral_d_shadow.c
 * Shadow for the spectral dagger
 * /d/Avenir/common/dead/obj/spectral_dagger.c
 *   
 *  This handles adding and removing the LIVE_I_QUICKNESS
 *   (-10) for the knife
 *    Lilith, Aug 2021
 */
inherit "/std/shadow";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Avenir/include/deities.h"

#define WIELDED   "_Avenir_i_wield_spectral_dagger"

object sDagger;
int fixed = 0;

void set_sword(object ob) {    sDagger = ob;      }
object query_sword()      {    return sDagger;    }

/*
 * Function    : remove_haste_penelty
 * Description : Remove the quickness penelty
 *               when player is wearing glove on left hand. 
 */
void 
remove_haste_penelty()
{
    object* weapons = shadow_who->query_weapon(-1);

    int i;
    for (i = 0; i < sizeof(weapons); i++)
    {
        fixed = weapons[i]->remove_haste_penelty();
        if (fixed)
            return;
    }
}
        
int 
test_dagger_penelty()
{
    object *gloves;
    string str;

    /* If the dagger isn't wielded but player is still shadowed */
    if (!sDagger->query_wielded())
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
            remove_haste_penelty();
            shadow_who->catch_msg("Your rapport with the dagger fades "+
                "away to nothingness.\n");        
            return 0;
        }

		/* 
		 * Did wielder offer a drink to the Gods? If so,
		 * Limit the benefit to 4 hours
		 *    I did this intox limiting back in the days when there 
		 *    were valid alternatives to health re-gen via alcohol, 
		 *    like herbs, but herbs were nuked to 1 per minute and 
		 *    that means that giving up health regen to wield a weapon
		 *    is a stupidly high-cost.
		 */
		if (shadow_who->query_prop(I_DRANK_WITH_SYBARUN_GOD) && (shadow_who->query_prop(I_DRANK_WITH_SYBARUN_GOD) < time()))
		{	
		    shadow_who->remove_prop(I_MADE_OFFERING);
			shadow_who->remove_prop(I_DRANK_WITH_SYBARUN_GOD);
			shadow_who->catch_tell("That blessed feeling wears off.\n");
			shadow_who->command("$unwield sword_of_quickness");
		}
        /* Is wielder intoxicated? If so, lets play with his mind a little */
		if (shadow_who->query_intoxicated() > 50 && (!shadow_who->query_prop(I_DRANK_WITH_SYBARUN_GOD)))
        {
            switch(random(20))
            {
                case 0..4:
                str = "As the alcohol you have imbibed takes effect, "+
                      "your rapport with the dagger begins to fade. ";
                break;
                case 5..9:
                str = "The dagger seems nearly dead in your hand. "+
                      "The rapport has faded to a faint whisper. ";
                break;
                case 10..14:
                {
                    str = "Your rapport with the dagger fades away to "+
                      "nothingness. ";        
                      remove_haste_penelty();
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
/* I AM MASKING THIS FUNCTION TO CAUSE SIDE-EFFECTS FROM USING dagger
 * WHILE INTOXICATED OR WEARING GLOVES.
 */
int query_not_attack_me(object who, int aid)
{
    test_dagger_penelty();
    return shadow_who->query_not_attack_me(who, aid);
}

void
remove_dagger_shadow(void)
{
    remove_shadow();
}

