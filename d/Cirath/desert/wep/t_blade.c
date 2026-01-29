inherit "/d/Cirath/std/armwep";
#include "/d/Cirath/common/defs.h"
#include <wa_types.h>

create_weapon()
{
    ::create_weapon();
    set_dt(W_SLASH|W_IMPALE);
    add_prop(OBJ_I_WEIGHT,5500);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE, 3000);
    set_hit(36);
    set_pen(33);
    set_ac(30);
    set_at(A_SHIELD);
    set_wt(W_SWORD);
    set_hands(W_NONE);
    set_name("blade");
    set_pname("blades");
    set_adj("tortoise");
    set_short("tortoise blade");
    set_pshort("tortoise blades");
    set_long("Composed of a large turtle shell attached to "
    	+"what appears to be a short sword made of flaked "
    	+"obsidian, this creation offers both protection and "
    	+"offensive capability.  The tortoise shell acts as a "
    	+"buckler for you while still giving you the range of "
    	+"motion necessary to use the extremely sharp obsidian "
    	+"blade with skill.\n");
    add_prop(OBJ_S_WIZINFO,"This item functions as both a shield "
    	+"and a sword.  It is a sword with 36/33 hit/pen and a"
    	+"shield with an AC of 30.");
    	
    set_wf(TO);
}

mixed
wield(object ob)
{
    object wr = TP;
    write("You slide your forearm into the leather straps on the "
    	+"inside of the shell part of the tortoise blade.  The shell "
    	+"now covers your arm like a small shield would.\n");
        return 1;
}

public mixed
unwield(object wep)
{
   object wr = TO->query_wielded();
   write("You slip your arm from the strapping on the tortoise blade, "
   	+"removing the shielding from your arm.\n");
       return 1;
}


