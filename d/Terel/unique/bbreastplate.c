/*
 *    Benton's Breastplate  /d/Terel/unique/bbreastplate.c
 *     
 *    This is a high AC armour that covers the A_CHEST only,
 *    instead of the full torso/body.
 *
 *    It gives some protection against the cold of the Silver Forest.
 *    And some resistance to COLD magic.
 *
 *    Created by Lilith Apr/May 2022
 *    Approved by:
 * 
 */

inherit "/std/armour";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>

#define MY_AC  50
#define MY_RES 20
#define TP     this_player()
#define TO     this_object()

void
create_armour()
{
    set_name("breastplate");
    add_name(({"plate", "_bentons_breastplate_"}));
    set_adj(({"gleaming", "ice-blue", "blue", "metallic", "alloy",
	"breast", "benton", "benton's", "bentons", "scale"}));
    set_short("metallic ice-blue breastplate");

    set_long("This is a skillfully sculpted breastplate made of a "+
      "bluish metallic alloy that was formed in the magic flame of "+
      "an ice dragon's breath. "+
      "The metal has been finished in such a way as to create a "+
      "reptilian scale pattern that shimmers in the light. "+		
      "While it only covers the chest, the level of protection "+
      "offered is unparalleled. "+
      "The interior of the breastplate is lined with wool to "+
      "provide padding and some protection against northern "+
      "Terel's everwinter.\n"+		
      "");

    add_item(({"padding", "wool padding", "lining", "wool lining"}),
      "The breastplate is padded with thick wool lining. "+
      "Whoever wears it will stay warm even in the Silver Forest "+
      "of northern Terel.\n");		
    add_item(({"alloy", "metal"}),
      "The alloy the breastplate is made of has a bluish tint. It "+
      "was formed in the flame of an ice dragon's breath.\n");
    add_item(({"strap", "straps" }), "These straps affix the armour "+
      "to your body without interfering with your movement.\n");
    add_item(({"surface", "scale pattern", "reptilian pattern",
      "pattern", "reptilian scale pattern", "finish", 
      "ornate pattern"}),
      "The surface of the bluish metal has been finished in a "+
      "an ornate pattern of reptilian scales.\n");

    set_keep(1);

    set_ac(MY_AC);  
    set_at(A_CHEST);  // chest, not torso

    add_prop(OBJ_I_WEIGHT, 2500);    
    add_prop(OBJ_I_VOLUME, 6000); 

    // For Silver Forest Cold Protection
    add_prop("_obj_cold_weather_protect", 2);
    // Magical items cannot be bought at a store.
    add_prop(OBJ_M_NO_BUY, 1); 		
    add_prop(OBJ_I_VALUE, 1000 + random (200));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 60, "transmutation" }));

    add_prop(OBJ_S_WIZINFO,
      "This armour covers the chest, not the entire torso. It "+
      "is cloned randomly by Benton. The AC is set to "+ MY_AC +
      "and it offers protection against the cold in the Silver "+
      "Forest and "+ MY_RES +" resistance to Cold Magic.\n"+
      "Cloned by: /d/Terel/common/moor/monster/benton at: "+
      "/d/Terel/common/moor/tomb/gore_chamber.\n");		

    add_prop(MAGIC_AM_ID_INFO,  ({ 
      "The icy breath of a dragon formed the alloy that you wear.\n", 10,
      "Sculpted for a mighty chest, it is Benton's armour to bear.\n", 20,
      "Lightweight and strong and padded well\n", 30,
      "It will stave off magical cold for a spell.\n", 40 }));

}

/* Add magic res upon wearing. */
mixed
wear(object ob)
{
    TP->add_magic_effect(this_object());
    return 1;
}

int
remove(object ob)
{
    object tp = query_worn();
    tp->remove_magic_effect(this_object());
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
        protectee->catch_msg("The "+ short() +
        " on your chest suddenly pulses "+
        "with warmth as if resisting a magical force!\n");
        return ({ MY_RES, 1}); // additive
    }
}
