/* A magic shield to keep Enzalcaspin safe. Based mainly on the examples. */
/* Tulix III, recoded 15/12/95.                                           */
/* This armour is used by /d/Emerald/cave/npc/wise_old_mage.c             */


inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>                               

/* Prototypes */
public void remove_magic_shield();

public void
create_armour()
{
    set_name("shield");
    add_name("enz_magic_shield");
    set_adj("magical");
    add_adj("magic");
   
    set_short("magical shield");
    set_long("A magical shield that protects you from damage.\n");
   
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(OBJ_S_WIZINFO, "This shield is not for use by mortals...\n");
   
    set_default_armour(90, A_MAGIC);
   
    set_alarm( 600.0, 0.0, remove_magic_shield); /* Lasts 10 mins. */
}

public void
enter_env(object dest, object old)
{
    wearer = dest;
    worn = 1;
   
    if (living(dest))
    {    
        tell_object(dest, "You become surrounded my a magical shield.\n");
        tell_room(environment(dest), "A magical shield forms around " +
            QTNAME(dest) + ".\n", dest);
    }
    else
        remove_object();
        
    wearer->wear_arm(this_object());
}

public void
leave_env(object old, object dest)
{
    remove_me();
}

public int *
query_shield_slots()
{
    return ({ A_HEAD, A_BODY, A_L_ARM, A_R_ARM, A_LEGS});
}

public void
remove_magic_shield()
{
    if (living(wearer))
    {
        tell_room(environment(wearer), "The magical shield around " +
            QTNAME(wearer) + " fades away.\n", wearer);
    }
    
    remove_object();
}
