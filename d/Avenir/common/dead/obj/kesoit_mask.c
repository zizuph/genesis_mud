
// file name:  /d/Avenir/common/dead/obj/kesoit_mask.c
// creator(s): Lilith, June 2021
// purpose:    Magical death mask of the Hegemons
// note:       The wearer of this mask is a master of life and death:
//             They resist death magic, scrys, and they don't need food
//             while wearing it.
//             Hunger is deferred until the mask is removed
//             and then their stuffed levels drop to what they 
//             should be. This is done via a shadow:
//             /d/Avenir/common/dead/obj/kesoit_mask_sh.c
//             Mask is cloned by /d/Avenir/common/dead/obj/sarcophagus in
//             /d/Avenir/commmon/dead/catacombs/crypt_s* rooms 
//             It is also available as a quest reward when the 
//             player meets Mascarvin.
//             The wearer also gets easier access to the Isle of 
//             the Dead and the Catacombs via DMASK_PROP like 
//             with the regular death masks.
//         Cost to wear: add_panic equivalent to 1/5 stat average.
//         Cost to remove: 1/10 max fatigue.
// note:       This is some work to get -- must kill the 
//             undeadguardians in the crypt_s* rooms to
//             get one, random chance.   
//
// updates:    Zizuph, July 2021  Helped with shadow.
//             Lilith, Oct 2021  Modified panic costs to be based on stat av.
//                     Updated check for no_scry props so we don't override
//                     props that may already be there or remove them in error.
//             Zizuph, Nov 2021 Move no_scry protection into the shadow.  This
//                     will play better with other no-scry effects.
//             Lilith, Nov 2021  Updated looseness so you can't wear multiples.
//             Lilith, Feb 2022  Added the ogre wear prop.
//             Lilith, Apr 2022  Changed scry immunity to partial resistance.
//                  When scried, the immune/vulnerable status remains in effect
//                  for 5 minutes at a time, and that status is stored so that
//                  it remains across logouts and wear/removal.



inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/lib/keep";
inherit "/lib/item_expiration";
#include "../dead.h"
#include <files.h>
#include <macros.h>
#include <wa_types.h>


int scry_strength;
int scry_random_time;
int scry_random_value;

public int get_scry_strength()
{
    return scry_strength;
}

public void set_scry_strength(int val)
{
    scry_strength = val;
}

void
create_object()
{
    set_short("wooden death mask");
    set_long("This is the death mask of one of the Hegemons of "
      +"Sybarus. It is carved from a burl of precious kesoit "
      +"wood and polished to a silken sheen so that the deep "
      +"red-black color of the wood and the swirling red-gold "
      +"grain within it seem to pulse with life. "
      +"The wood itself has an unusual scent, woodsy and "
      +"sweet, if somewhat faded, as if the mask was fashioned "
	  +"long ago and has lost some potency over time.\n"
      +"A trefoil shape has been burned into the "
      +"wood on the inside of the mask, alongside "
      +"an elvish script.\n");

    add_item(({"elvish script", "script" }),
      "    Blessed of Mascarvin art thou,\n    O master of life and death!\n");
    add_cmd_item(({"elvish script", "script" }), "read",
      "    Blessed of Mascarvin art thou,\n    O master of life and death!\n");
    add_item(({ "wood", "kesoit", "grain" }),
      "The wood of the mask is known as kesoit, a very "
      +"rare tree of the acacia family that grows only "
      +"under the light of the Source in Sybarus. When "
      +"polished, it is dark reddish-black in color, with a "
      +"thick red-gold grain.\n");
    add_cmd_item(({ "wood", "kesoit", "mask", "kesoit mask"}), "smell",
      "What a divine scent! Woodsy and sweet, with "
      +"hints of anise and ginger, it would mask even the "
      +"scent of death and decay.\n");
    set_name("_Avenir_magic_death_mask");
    add_name(({"mask"}));
    set_adj("death");
    add_adj(({"kesoit", "polished", "silken", "hegemon", "wood", 
	"wooden", "hegemon's", "face"}));
    config_wearable_item(A_BROW, 1, 3, this_object());

    if (IS_CLONE)
	set_item_expiration();

    /* Half life and death, for Mascarvin, goddess of death and rebirth */
    add_prop(MAGIC_AM_MAGIC, ({ 50, "life" }));
    add_prop(MAGIC_AM_MAGIC, ({ 50, "death" }));
    add_prop(MAGIC_AM_ID_INFO, ({
	"  The kesoit death mask glows with the power of magick\n", 10,
	"  bestowed by Mascarvin herself, the Sybarun Goddess\n", 15,
	"  of death and rebirth\n.", 20,
	"  Designed to sustain a Hegemon through his journey to rebirth\n", 25,
	"  the wearer is blessed with resistance to death magicks, and\n", 30,
	"  resistant to the need for food.\n", 35,
	"  The one so blessed to wear it is somewhat shielded from eyes "+
	"  prying from afar with magicks.\n", 40 }));

    add_prop(OBJ_S_WIZINFO,
      "This death mask was made for one of the Hegemons of Sybarus, "
      +"to sustain him in death and help hasten his rebirth.\n"
      +"It is found randomly in the sarcophagi in the catacombs.\n"
      +" Location: /d/Avenir/commmon/dead/catacombs/crypt_s*.c  \n"
      +" Cloned by: /d/Avenir/common/dead/obj/sarcophagus.c \n"
      +"It will resist death magic (20), resist scrying, and make \n"
      +"it so the wearer does not grow hungrier, using a shadow:\n"
      +"/d/Avenir/common/dead/obj/death_mask_sh\n");

    /* Very rare and special wood mask. Lightweight and valuable */
    add_prop(OBJ_I_VALUE, 2000);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop("_aod_wear_prop", 1); // so ogres can use it. 

    set_keep(); 
    set_wf(this_object()); 
    seteuid(getuid()); 	
    set_scry_strength(50);
}

/* Mask confers death magic resistance */
mixed 
query_magic_protection(string prop, object what)
{
    if (what == query_worn() && prop == MAGIC_I_RES_DEATH)
    {
	query_worn()->catch_msg("By the power of Mascarvin, "
	  +"Sybarun Goddess of Death and Rebirth, you resist "
	  +"the death magicks cast against you.\n");
	return ({ 20, 1 });
    }

    return ::query_magic_protection(prop, what);
}

// Wearing mask costs panic on the level of player's stat av.
mixed
wear(object ob)
{
    object wearer = ENV(TO);

    if (ob != this_object() || !living(wearer))
	return -1;	
    if (wearer->query_prop(DMASK_PROP))
    return -1;
 
    object shadow = clone_object(OBJ +"kesoit_mask_sh");
    shadow->setup_death_mask_shadow(wearer, get_scry_strength(),
        this_object());
    wearer->add_magic_effect(this_object());	
    wearer->catch_msg("A divine energy pulses through you as "
      +"the kesoit mask molds to your face. You feel "
      +"immune to hunger and resistant to the effects of " 
      +"death magick.\n");

    // Cost to wear - you feel panicky from the feeling of 
    // it molding to your face.	
    wearer->add_panic(wearer->query_average_stat()/5); 	
    wearer->add_prop(DMASK_PROP, 1);
	
    return 0;

}

// Removing mask costs 1/10 of max fatigue
mixed       
remove(object ob)
{
    object wearer = query_worn();

    if (wearer) 
    {	
	wearer->remove_prop(DMASK_PROP);
	wearer->remove_death_mask_shadow();
	wearer->remove_magic_effect(this_object());
	wearer->catch_msg("Your body mourns the loss of divine "
	  +"protection. You find yourself feeling a bit tired and "
	  +"craving a good meal.\n");
	// Costs 1/10 of player's max fatigue.
	wearer->add_fatigue(-(wearer->query_max_fatigue() / 10));
    // some players may have no_scry from something else, 
	// so don't remove unless we added it.
    }
    return 0;
}

void
leave_env(object from, object to)
{
    wearable_item_leave_env(from, to);
    from->remove_magic_effect(this_object());
    ::leave_env(from, to);

}

/* 300 seconds  = 5 minutes */
int get_scry_random_value()
{
    if (scry_random_time < time() - 300)
    {
        scry_random_time = time();
        scry_random_value = random(100);
    }
    return scry_random_value;
}

void
appraise_object(int num)
{
    appraise_wearable_item();
    ::appraise_object(num);
}

void
init_arm_recover(string arg)
{
    string dummy;
    sscanf(arg, "%s#SCRY#%d:%d#SCRY#%s", dummy,
       scry_random_time, scry_random_value, dummy);
    init_item_expiration_recover(arg);
}

/*
 * Function name: query_recover
 * Description  : Called to check whether this armour is recoverable.
 *                If you have variables you want to recover yourself,
 *                you have to redefine this function, keeping at least
 *                the filename and the armour recovery variables, like
 *                they are queried below.
 *                If, for some reason, you do not want your armour to
 *                recover, you should define the function and return 0.
 * Returns      : string - the default recovery string.
 */
public string
query_recover()
{
    return MASTER + ":" + sprintf("#SCRY#%d:%d#SCRY#", scry_random_time,
        scry_random_value) + query_item_expiration_recover();
}

public void
init_recover(string arg)
{
    init_arm_recover(arg);
}
