//-*-C++-*-
// file name: ~Avenir/common/dark/obj/tooth_knife
// creator(s):  Boriska
// last update: Jan 1995
// purpose:  a weapon that can be made from worm's leftover
// note: 
//       The knife requires something identified as 'glove' or 'gloves'
//       be worn on right hand. The glove cannot be removed while
//       the knife is wielded. This is implemented by calling set_af()
//       in the glove and defining remove() function in the knife
//       code. Precaution is taken not to miss old set_af that could
//       be in the gloves. All this pain to ensure that all kinds
//       of gloves will do and not some special ones :)
/*
 * Revisions:
 * 	Cirion, Feb 1996: Added combat messages and some pretty extra
 * 			  descriptions. Also removed the high skill
 * 			  requirements to wield the knife.
 *	Lilith, Jun 2014: Updated MAGIC_ID info, mistakenly stated weapon
 *			  was not blocked by armor. This changed when
 *			  MAGIC_DT was disallowed.
 *	Lucius, Aug 2017: Removed death on failure to wield.
 *			  Also removed unnecessary names/pnames.
 *      Arman, Feb 2020:  Reduced pen from 43 to 40, as maximum pen for
 *                        a magical knife is 40.
 *
 */
inherit "/d/Avenir/inherit/weapon";

#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include <macros.h>
#include <filter_funs.h>
#include "/d/Avenir/common/common.h"

static object wear_func = 0;
static object to = this_object();
static object glove;

void
create_weapon ()
{
    set_name ("tooth-knife");
    add_name (({"knife","blade"}));
    add_name("_avenir_tooth_knife");
    set_pname ("tooth-knives");
    add_pname (({"knives","blades"}));
    add_adj (({"white", "glimmering", "acid-etched","tooth"}));

    set_short ("glimmering acid-etched blade");

    set_long ("This strange and marvelous weapon resembles the "+
        "huge, curving tooth of some great, mythical beast. Its "+
        "pale, milk-white surface is etched with random lines "+
        "that cascade fluidly down to the impossibly sharp tip. "+
        "The edge is sharper and finer than any steel could "+
	"possibly hold, and the simple handle pulses with a "+
	"glimmering glow that is echoed faintly in the unetched "+
	"portions of the blade.\n");

    add_prop (OBJ_M_NO_BUY, "The "+ short() +" is not for sale.\n");
    add_prop (OBJ_I_WEIGHT, 2000);
    add_prop (OBJ_I_VOLUME, 2000);
    add_prop (OBJ_I_VALUE, 3500);

    //Not sure how mudlib will react to negative values :(
    //It is vulnerable to acid.
    add_prop (PRE_OBJ_MAGIC_RES + MAGIC_I_RES_ACID, -50);
    add_prop (OBJ_I_RES_ACID, -50);

    add_prop (OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop (MAGIC_AM_MAGIC, ({40, "enchantment"}));
    add_prop (MAGIC_AM_ID_INFO,
             ({ "An enchanted tooth from an enchanted beast\n", 20, 
                "Transformed in an enchanted place\n", 30,
                "Its only bane, acid.\n", 60 }));

    add_prop(OBJ_S_WIZINFO, "This knife, made from the tooth "
          +"of the Great Worm of Avenir, is enchanted to have a high "
          +"hit/pen (35/40). The knife "
          +"requires that a glove is worn on the hand that wields it, "
          +"and that the wielded has a decent knife/animal handling "
          +"skill before it can be wielded.\n\n");

    set_hit(35);
    set_pen(40);
    set_wt(W_KNIFE);
    set_dt(W_IMPALE); 
    set_hands(W_RIGHT);
    set_wf(to);
}

mixed
wield(object weap)
{
    object tp = this_player();
    object *gloves;
  
    // have to wear a glove on right hand
    if (!sizeof (gloves =
	 filter (all_inventory(tp), "worn_glove", to)))
    {
        tp->heal_hp (-random(300));
        return "The handle of the "+ short() +
               " cuts deeply into your unprotected hand!\n";
    }

    if (tp->query_skill (SS_WEP_KNIFE) < 30)
    {
        tp->add_mana (-random(100));
        return "The "+ short() +" resists you. You feel a "+
               "loss of mental energy.\n";
    }

    // and animal handling skill to handle the beast :)
    if (tp->query_skill (SS_ANI_HANDL) < 25)
    {
        tp->add_fatigue (-random(30));
        return  "The " +short() +" seems alive in your hand and "+
                "refuses to surrender to your grasp.\n"+
                "The struggle tires you out.\n";
    }
    tp->catch_msg ("The "+ short() +" struggles like a living "+
        "thing against your grasp, but you manage to keep "+
        "hold of it.\n");
    tp->add_mana (-random(100));
    tp->add_fatigue (-random(30));

    // make sure that player cannot remove glove while wielding the tooth
    glove = gloves[0];
    wear_func = glove->query_af(); // gloves may have their own wear_func
    glove->set_af (to);
    glove->add_prop(OBJ_M_NO_DROP,
	  "You cannot drop the glove while wielding the tooth-knife.\n");
    return 0;
}

// any glove worn on right hand will do.
// sometimes gloves made as one piece worn on both hands
int
worn_glove (object ob)
{
    return (ob->id("glove") &&
        ob->query_worn() && (ob->query_at() & A_R_HAND)) ||
        (ob->id("gloves") &&
        ob->query_worn() && (ob->query_at() & A_HANDS));
}

mixed
unwield(object weap)
{
    object tp = query_wielded();

    tell_object(tp,"As you loosen your grip on the "+ short() +
        ", a pale light ripples down its length.\n" );
    tell_room(environment(tp), "You see a sudden flash of "+
        "light in the corner of your eye.\n", tp);

    // nothing good is ever free...
    tp->add_mana (-random (100));
 
    if (wear_func)
        glove->set_af(wear_func); // restore old glove's wear_func

    glove->remove_prop(OBJ_M_NO_DROP);
    wear_func = 0; 
    return 0;
}

// called from gloves when player tries to remove them.
mixed
remove(object armour)
{
    if (query_wielded())
    {
       this_player()->catch_msg("You cannot remove your glove "+
           "while wielding that blade.\n");
       return -1;
    }
  
  // should not never get here
  // gloves might have their own wear_func set, don't skip it
    if (wear_func)
        return wear_func->remove(armour);
    return 0;
}

// sanity check, in case the knife is dested w/o unwielding
// should not happen :)
void
remove_object()
{
    if (wear_func)
        glove->set_af(wear_func); // restore old glove's wear_func
    wear_func = 0;
    ::remove_object();
}
