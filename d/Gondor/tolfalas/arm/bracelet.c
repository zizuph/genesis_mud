
/*

  Palmer 12 Aug 2006
  Quest reward in Tolfalas

*/

inherit "/std/armour";
inherit "/cmd/std/command_driver";

#include "/d/Shire/sys/defs.h"
#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <options.h>
#include <std.h>
#include <stdproperties.h>
#include <wa_types.h>

#define BRACELET_SUBLOC "_bracelet_subloc_"
 

 
public void
create_armour(){
    set_name("bracelet");
    add_adj(({"tarnished", "silver"}));
    set_short("tarnished silver bracelet");
    set_long("This is a tarnished silver bracelet. It has some engravings on it.\n");
    add_item("engravings", "You see several engravings: a heart, a cloud, a skull, a drop of water, a flame and a lightning bolt.\n");
 
    add_prop(OBJ_M_NO_SELL, 1);
 
    remove_prop(OBJ_I_VOLUME);
    remove_prop(OBJ_I_VALUE);
    remove_prop(OBJ_I_WEIGHT);

    set_slots(A_R_HAND);
    set_layers(0);
    set_looseness(0);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 60, "enchantment" }));
     add_prop(MAGIC_AM_ID_INFO,
          ({ "You feel this bracelet posseses a strange power.\n", 10,
             "This bracelet wards off magic and may help you detect what magic tries to harm you.\n", 40 }));
    set_ac(1);  
    set_af(TO);
}

 
 
/*
 * Function name: wear
 * Description  : This function is called when someone tries to wear
 *                this item. 
 * Arguments    : object obj - The armour we want to wear.
 * Returns      : int  0 - The item can be worn normally.
 *                     1 - The item can be worn, but print no messages.
 *                    -1 - The item can't be worn, use default messages.
 *                string - The item can't be worn, use this message.
 */
public int
wear(object obj)
{

    TP->add_magic_effect(this_object());

    write("You slide the " + short() + " onto your right wrist and your arm warms slightly.\n");
    say(QCTNAME(this_player()) + " slides a " + short() + " onto  " +
        this_player()->query_possessive() + " right wrist and shivers.\n");

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
    from->remove_magic_effect(TO);
}

varargs mixed 
query_magic_protection(string prop, object protected = previous_object())
{
    if (protected == query_worn())
    {
        if (prop == MAGIC_I_RES_LIFE)
        {
            protected->catch_msg("The heart engraving on your "+ short()+" glows.\n");
            return ({ 0, 1}); 
        } 
        if (prop == MAGIC_I_RES_DEATH)
        {
            protected->catch_msg("The skull engraving on your "+ short()+" glows.\n");
            return ({ 0, 1}); 
        } 
        if (prop == MAGIC_I_RES_WATER)
        {
            protected->catch_msg("The water drop engraving on your "+ short()+" glows.\n");
            return ({ 0, 1}); 
        } 
        if (prop == MAGIC_I_RES_FIRE)
        {
            protected->catch_msg("The flame engraving on your "+ short()+" glows.\n");
            return ({ 0, 1}); 
        } 
        if (prop == MAGIC_I_RES_MAGIC)
        {
            protected->catch_msg("Your "+ short() +" starts to warm.\n");
            return ({ 10, 1}); 
        } 

    }
            return ::query_magic_protection(prop, protected);
}

