/* Bruising Boots
*
* This boots are unarmed enhancers, intended to be a magical weapon
* for unarmed users.  When it hits the arms or legs of the target,
* it will cause a temporary skill drain of parry/acrobat.
*
* Author: Zizuph 10-2021
*
*   Lilith, Feb 2022: tweaking set_likely_cond and set_likely_break.
*   Lilith, Feb 2022: added missing MAGIC_AM_MAGIC prop
*/

#include "/d/Avenir/common/city/city.h"

inherit "/d/Avenir/inherit/unarmed_enhancer";

#include <wa_types.h>
#include <stdproperties.h>

void
create_unarmed_enhancer()
{
    set_short("pair of night-black boots");
    set_pshort("pairs of night-black boots");
    set_name(({"boots","pair","boot"}));
    set_pname(({"boots", "pairs", "pairs of boots"}));
    set_adj(({"pair","night-black"}));
    set_long("Dark as night, these boots gleam wickedly with steel accents. "
      +"Made of the thick hide of the reptilian phrynos, the dark scales "
      +"refract light with a hint of irridescence. Steel studs in swirling "
      +"patterns reinforce their protective nature, while also enhancing "
      +"the bruising damage these boots can do when worn by those trained "
	  +"in the arts of unarmed combat. A trefoil has been stamped into the "
      +"heel of each boot.\n");
    
    set_default_enhancer(46, 50, W_BLUDGEON, 40, A_FEET, 0, this_object());
    add_prop(MAGIC_AM_MAGIC, ({ 40, "enchantment"}));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(MAGIC_AM_ID_INFO, ({ 
       "  For those who serve the Hegemon of Sybarus,\n", 10,
       "  A gift of boots to shield their feet and\n", 20,
	   "  When worn by unarmed warriors,\n"+	   
	   "  Make of them clubs dealing bruising damage.\n", 30,
	   "  Lo, by the power of Gods of Sybarus, do these boots\n", 35,
       "  Also impair the abilities of enemies to\n"+
       "  Parry attacks when kicked in the arm, and\n", 40,
       "  Reduce the acrobatic abilities of enemies\n"+
       "  When kicked in the legs.\n", 45 }));	   
    add_prop(OBJ_S_WIZINFO, "These unarmed aids provide 46/50 on the " +
        "feet when worn, and also have a special that can reduce parry " +
        "and acrobat up to a maximum combined total of 30 points, " +
        "temporarily, if the right hitlocs are hit.\n"); 
/*	
 *  Lilith, Feb 2022: Getting feedback from unarmed fighters that these
 *                    boots are wearing down very fast--because they are
 *                    both taking hits and enhancing hits.  I'm going to
 *                    try setting these to negatives to see how it goes.
 *         Arman gave ok to set values very very negative on 3/3/2022
 */
	set_likely_break(-1000); 
	set_likely_cond(-1000);

}


public varargs int
did_hit(int aid, string hdesc, int phurt, object enemy, int dt,
                int phit, int dam)
{
    int result = ::did_hit(aid, hdesc, phurt, enemy, dt, phit, dam);

    if (phurt <= 0)
    {
        return result;
    }

    int leg_hit = 0;
    int arm_hit = 0;
    if (hdesc == "legs")
    {
        leg_hit = 1;
    }
    if (hdesc == "left arm" || hdesc == "right arm")
    {
        arm_hit = 1;
    }

    if (leg_hit || arm_hit)
    {
        object bruise_obj;
        if (!(bruise_obj = present("_bruised_boots_obj", enemy)))
        {
            setuid();
            seteuid(getuid());
            bruise_obj = clone_object(OBJ + "worn/bruise_obj");
            bruise_obj->move(enemy, 1);
        }
        if (leg_hit)
        {
            bruise_obj->leg_hit();
        }
        if (arm_hit)
        {
            bruise_obj->arm_hit();
        }
    }
    return result;
}
                
