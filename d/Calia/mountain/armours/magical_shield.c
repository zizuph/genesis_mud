
/*  
    Magical shield for use in the polymorph quest.

    Coded by Maniac 31/8/95, with many thanks to Aridor for his
    example dragonscale armour from Krynn.

     6/9/98           Remove magic after less time but allow 
                      player to keep possession of decent
                      non-magical shield. Non-recoverable.     Maniac
    13/10/95          Longer before magic burns out            Maniac 

*/

inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "armour.h"
#include POLYMORPH_QUEST

int faded; 

void
create_armour()
{
    set_name("shield");
    add_name(SHIELD_NAME);
    set_adj(({"magical", "steel"}));
    set_short("magical steel shield"); 
    set_long("This is a magnificent shield, made of bright steel which " +
             "to have a strange sheen to it, because of the strange brew " +
             "that was mixed with the ore. At its centre is set a " +
             "sapphire of draining, sparkling away mysteriously.\n");

    add_prop(OBJ_S_WIZINFO, "A magical shield used in the polymorph " +
                            "quest in Calia. It has extremely powerful " +
                            "resistance effects against fire, cold and " +
                            "acid, but the magic runs out " +
                            "one hour after it is created. " +
                            "It cannot be passed on to anyone else " + 
                            "as long as it's magical.\n");

    add_prop(MAGIC_AM_MAGIC, ({75, "enchantment"}));

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);

    add_prop(MAGIC_AM_ID_INFO,
          ({"This shield protects to an amazing level against fire, cold " +
            "and acid when worn. It is very magical indeed.\n", 20}));
    
    set_ac(40);
    set_at(A_SHIELD);
    set_af(this_object());
    set_am( ({ 0, 0, 0 }) );
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_M_NO_INS, 1);
    add_prop(OBJ_M_NO_GIVE, "The magical steel shield seems " +
                            "too important to give away.\n");
    add_prop(OBJ_M_NO_DROP, "The magical steel shield seems " +
                            "too important to drop.\n");
    add_prop(OBJ_M_NO_SELL, "The magical steel shield seems " +
                            "too important to sell.\n"); 
    add_prop(OBJ_M_NO_BUY, 1); 
    faded = 0; 
    set_alarm(3600.0, 0.0, "fade");
}


/* Only protects when worn and before the magic has faded */
varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{
    if (protectee == query_worn() && !faded)
      {
          if ((prop == MAGIC_I_RES_FIRE) || (prop == MAGIC_I_RES_COLD) ||
              (prop == MAGIC_I_RES_ACID)) 
            return ({75, 0});  /* non-additive */
      }
    else
        return ::query_magic_protection(prop, protectee);
}


string
query_recover()
{
    return 0;
}


/* Special wear effect, the magic comes into effect only when the 
   shield is worn */
mixed
wear(object what)
{
    this_player()->add_magic_effect(this_object());
    return 0;
}


/* Shield remove effect, magic stops when shield is removed */
mixed
remove(object what)
{
    wearer->remove_magic_effect(this_object());
    return 0;
}


/* This happens when the magical power in the shield dries up. */
void
fade()
{
    object e = environment(this_object());

    if (!faded && interactive(e))  {
        tell_object(e, "The magical power in the shield fades.\n"); 
        remove_adj("magical"); 
        add_adj("quality"); 
        set_short("quality steel shield"); 
        remove_prop(MAGIC_AM_MAGIC); 
        remove_prop(OBJ_I_IS_MAGIC_ARMOUR); 
        remove_prop(MAGIC_AM_ID_INFO); 
        remove_prop(OBJ_M_NO_GIVE); 
        remove_prop(OBJ_M_NO_SELL); 
        remove_prop(OBJ_M_NO_DROP); 
        remove_prop(OBJ_M_NO_INS); 
        faded = 1; 
    } 
}


void
remove_object()
{
    if (!faded) 
        tell_object(environment(), "The " + short() +  
                    " vanishes in a puff of magic.\n"); 
    ::remove_object(); 
}


void
leave_env(object old, object dest)
{
    if (!faded && dest->query_prop(ROOM_I_IS))
        set_alarm(1.0, 0.0, remove_object);

    ::leave_env(old, dest);
}

