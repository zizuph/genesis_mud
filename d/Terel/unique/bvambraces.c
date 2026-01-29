/*
 *  Benton's Vambraces   /d/Terel/unique/bvambraces.c
 *
 *     This is an unarmed enhancer with good AC.
 *     It gives slight COLD magic resistance and 
 *     some protection from the Silver Forest Cold.
 *
 *  Created: Lilith Apr/May 2022
 *  Approved: 
 */
#pragma strict_types

// Using Avenir unarmed enhancer since it has some nifty messages.
inherit "/d/Avenir/inherit/unarmed_enhancer";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/std/combat/combat.h"

#define TO     this_object()
#define TP     this_player()
#define MY_AC  45
#define MY_DAM 50
#define MY_RES 10

void
create_unarmed_enhancer()
{

    set_default_enhancer(MY_DAM, MY_DAM, W_BLUDGEON, 
      MY_AC, A_ARMS | A_WRISTS | A_HANDS, ({0, 0, 0 }), 
      this_object());

    set_name ("vambraces");
    set_pname(({"vambraces"}));
    set_short("set of metallic ice-blue vambraces");
    set_pshort("sets of metallic ice-blue vambraces");
    set_adj(({"ice-blue","plate", "platemail"}));
    add_adj(({"gleaming", "blue", "metallic", "alloy",
      "ice-blue", "benton", "benton's", "bentons", "scale"}));	
    add_name(({"set", "armour", "_bentons_vambraces_", "vambracers"}));
    set_long("The vambraces are comprised of armour plates that "+
      "are perfectly shaped to fit along the forearms and wrists. "+
      "The bluish metal has been finished in such a way as to create "+
      "an ornate reptilian scale pattern that shimmers in the light. "+		
      "The interior of the vambraces is lined with thick leather to "+
      "provide padding and some protection against northern "+
      "Terel's everwinter.\n"+		
      "");

    set_af(this_object());
    set_keep(1);

    add_prop(OBJ_I_WEIGHT, 2000);
    add_prop(OBJ_I_VOLUME, 3000);
    add_prop(OBJ_I_VALUE,  1800); 
    // For Silver Forest Cold Protection
    add_prop("_obj_cold_weather_protect", 2);
    add_item(({"strap", "straps" }), "These straps affix the armour "+
      "to your body without interfering with your movement.\n");
    add_item(({"leather", "padding", "leather padding" }),
      "The leather is very thick and yet supple. The plates of the "+
      "vambraces have been affixed to it.\n");
    add_item(({"surface", "scale pattern", "reptilian pattern",
	"pattern", "reptilian scale pattern", "finish"}),
      "The surface of the bluish metal has been finished in a "+
      "an ornate pattern of reptilian scales.\n");
    add_item(({"alloy", "metal"}),
      "The alloy the vambraces are made of has a bluish tint. It "+
      "was formed in the flame of an ice dragon's breath.\n");

    /* Arman gave ok to set values very very negative on unarmed enchancers
     * on 3/3/2022 until such time as the wear-down formulas are updated.
     */
    set_likely_break(-1000); 
    set_likely_cond(-1000);

    // Magical items cannot be bought at a store.
    add_prop(OBJ_M_NO_BUY, 1); 	
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 50, "transmutation" }));

    add_prop(OBJ_S_WIZINFO,
      "The vambraces are unarmed enhancers that give an effective "+
      MY_DAM +"|" + MY_DAM +"hit|pen. They are cloned randomly by "+
      "Benton. The AC is set to "+ MY_AC +
      "and it offers protection against the cold in the Silver "+
      "Forest and "+ MY_RES +" resistance to Cold Magic.\n"+
      "Cloned by: /d/Terel/common/moor/monster/benton at: "+
      "/d/Terel/common/moor/tomb/gore_chamber.\n");		
    add_prop(MAGIC_AM_ID_INFO,  ({ 
      "The icy breath of a dragon formed the alloy that you hold.\n", 10,
      "Worn over wrists and arms they protect you from the cold\n", 20,
      "of Silver Forest and magic enchantments both.\n", 25,
      "Unarmed warriors will find these help with their growth.\n", 30,
      }));
}

/* Add magic res upon wearing. */
mixed
wear(object ob)
{
    TP->add_magic_effect(this_object());

    if (interactive(TP))
	TP->catch_msg("As you strap the "+ short() +" onto your forearms "+
	  "you feel that the power of your wrists and hands has been "+
	  "magically strengthened.\n");

    return 1;
}

int
remove(object ob)
{
    object tp = query_worn();

    tp->remove_magic_effect(this_object());

    tp->catch_msg("The magical invigoration of your wrists and hands "+
      "fades away.\n");
    return 0;
}

void
leave_env(object to,object from)
{
    ::leave_env(to,from);

    if (!living(from))
	return;

    /* Just make sure to remove the magic res */
    from->remove_magic_effect(TO);
}

/*  Add a bit of resistance to Cold elemental magic.  */ 
varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{
    if (prop == MAGIC_I_RES_COLD)
    {
	protectee->catch_msg("The "+ short() +" on your forearms "+
	  "pulse with warmth as if resisting a magical force!\n");
	return ({ MY_RES, 1}); // additive
    }
}
