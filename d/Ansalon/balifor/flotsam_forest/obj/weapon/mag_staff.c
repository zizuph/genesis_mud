/* Created by ???
 * 31.10.2000 Fixed by Milan
 *
 * Navarre November 5th 2011: Fixed stat info to match duration.
 *                            Increased duration of enchantment.
 *                            Added query_chant_str function for fermammon to use to chant.
 *                              After the random chant string was created fermammon no
 *                              longer enchanted his staff as was intended.
 *                            Fixed formatting.
 *                            Fixing bug with multiple alarms being created with unwield/wield+enchant
 */
inherit "/std/weapon";
inherit "/d/Genesis/specials/new/lib/spell_enhancer";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"
#include <filter_funs.h>
#include <options.h>

inherit "/lib/keep";

int staff_enchanted = 0;
int skill_bonus = 25;

string chant_str;
int dispel_alarm = 0;

#include "staff_special.h"

void
init_chant_str()
{
    string aaa = "aeiouy", bbb = "bcdfghjklmnpqrstvwxz";
    int i = random(6);
    chant_str = aaa[i..i];
    i = random(20);
    chant_str += bbb[i..i];
    i = random(6);
    chant_str += aaa[i..i];
    i = random(20);
    chant_str += bbb[i..i];
    chant_str += "s";
}

string
query_chant_str()
{
	return chant_str;
}

void
create_weapon()
{
    init_chant_str();

    set_name("staff");
	add_name("_ferm_magic_staff_");
    set_pname("staves");
    set_adj("wooden");
    add_adj("gnarled");
    set_short("gnarled wooden staff");
    set_pshort("gnarled wooden staves");
    set_long("This two-handed wooden staff is long and well " +
      "balanced for quick handling, while thick enough to cause " +
      "a headache for anyone at the receiving end of it. Two "+
      "gold bands cap each end of this staff. @@extra_descr@@\n");

    set_default_weapon(40,20,W_POLEARM,W_BLUDGEON,W_BOTH);
    set_magic_spellpower(40);

    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(OBJ_S_WIZINFO, "This staff raises ones polearm skill to "+
      "a maximum of 50, alters its pen from 20 to 40-45 depending on " +
      "ones SS_FORM_ENCHANTMENT skill. It also has a minor special attack. " +
      "This ability drains mana when called upon, "+
      "and only those with a SS_FORM_ENCHANTMENT skill greater "+
      "than 70 will it work for. The ability lasts for "+
      "around 20 minutes.\n");
    add_prop(MAGIC_AM_ID_INFO, ({50, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"This staff is a mana receptical for mages "+
	"with a high ability with enchantments. Mana is drained from the wielder "+
	"when the proper chant is uttered, fueling the staff into a powerful " +
	"weapon that enhances the caster's spellpower.",30,
        "The staff also confers some skill with polearms to the unskilled "+
	"user.\n",40,"The chant to enchant this staff is '"+chant_str+"'.\n",80}));
    add_prop(OBJ_I_VOLUME, 2000);
    add_prop(OBJ_I_WEIGHT, 2500);
    set_wf(TO);

    seteuid(getuid(TO));
}

string
extra_descr()
{
    if (!staff_enchanted)
	{
		return "";
	}

    if (!objectp(wielder))
	{
		return "";
	}

    if (TP->query_skill(SS_FORM_ENCHANTMENT) > 69)
    {
	    if (wielder->query_alignment() < -300)
		{
			return "The length of it seems to glow with a demonic "+
		           "purple-black flame.";
		}
    	else
		{
	        return "The length of it seems to glow with a mystical "+
		           "soft azure flame.";
		}
    }
    return "";
}

void
remove_enchantment()
{
    if (staff_enchanted)
    {
	    set_pen(20);
	    staff_enchanted = 0;

		if (!objectp(wielder))
	    {
			return;
		}
	    wielder->catch_tell("The flames surrounding the staff suddenly "+
	            		    "dim and die out.\n");
    	tell_room(E(wielder),"The flames surrounding " +QTNAME(wielder)+
	                         "'s staff suddenly dim and die out.\n", wielder);
 	    wielder->set_skill_extra(SS_WEP_POLEARM, 
                wielder->query_skill_extra(SS_WEP_POLEARM) - skill_bonus);

            set_magic_spellpower(40);

	    wielder->update_weapon(TO);
		remove_alarm(dispel_alarm);
    }
}

void
invoke_enchantment()
{
    int pen_bonus = 40 + wielder->query_skill(SS_FORM_ENCHANTMENT) /10;
    
    wielder->set_skill_extra(SS_WEP_POLEARM,
	wielder->query_skill_extra(SS_WEP_POLEARM) + skill_bonus);

    set_pen(pen_bonus - 5);
    set_magic_spellpower(pen_bonus);

    staff_enchanted = 1;
    wielder->update_weapon(TO);
    dispel_alarm = set_alarm(1200.0, 0.0, remove_enchantment);
}

void
stage_two(object tp)
{
    string flame_align;

    if (!objectp(tp) || tp != wielder)
	{
		return;
	}
    if (tp->query_alignment() < -300)
	{
		flame_align = "a demonic black flame";
	}
	else
	{
		flame_align = "a soft azure flame";
	}
    tp->catch_tell("The staff is engulfed in "+flame_align+"!\n");
    tell_room(E(tp), "The gnarled wooden staff " +
                     "held by " +QTNAME(tp)+ " is suddenly engulfed "+
                     "in "+ flame_align+ "!\n", tp);
    invoke_enchantment();
}

void
stage_one(object tp)
{
    if(!objectp(tp) || tp != wielder)
	{
		return;
	}
    tp->catch_tell("You suddenly feel a surge of energy transfer from "+
                   "yourself to the staff, awakening its latent powers!\n");
    tp->add_mana(-100);
    set_alarm(2.0, 0.0, &stage_two(tp));
}

int
chant(string str)
{
    if (!str)
	{
	    return 0;
	}
    
	if (str != chant_str)
	{
		return 0;
	}

    if (TP != wielder)
    {
	    NF("You must be wielding the staff to work the "+
	       "enchantment properly.\n");
    	return 0;
    }
    
	if (wielder->query_skill(SS_FORM_ENCHANTMENT) < 70)
    {
	    NF("Your chant does not somehow sound right...\n");
	    return 0;
    }

    if (wielder->query_mana() < 100)
    {
	    NF("You are too mentally tired to chant properly.\n");
	    return 0;
    }

    if (staff_enchanted)
    {
	    NF("The staff is presently enchanted, and cannot be further powered.\n");
	    return 0;
    }

    write("You raise the gnarled wooden staff above your head, "+
          "and intone: "+C(chant_str)+"! Uro Edonevanti!\n");
    tell_room(E(wielder), QCTNAME(wielder)+ " raises the gnarled wooden staff " +
              "above " +HIS(wielder)+ " head, and intones: "+C(chant_str)+"! Uro Edonevanti!\n", wielder);
    set_alarm(3.0, 0.0, &stage_one(wielder));
    return 1;
}

void
init()
{
    ::init();
    add_action(chant, "chant");
}

mixed
wield(object what)
{
    return 0;
}

mixed
unwield(object what)
{
    remove_enchantment();
    return 0;
}

void 
appraise_object(int num)
{
    ::appraise_object(num);
    write(item_spellpower_desc());
}

string 
stat_object() 
{
    return ::stat_object() + stat_object_spellpower();
}