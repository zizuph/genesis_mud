inherit "/d/Cirath/std/armwep";
#include "/d/Cirath/common/defs.h"
#include <wa_types.h>

create_weapon()
{
    ::create_weapon();
    set_dt(W_SLASH);
    add_prop(OBJ_I_WEIGHT,8500);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE, 3000);
   set_hit(32);
    set_pen(33);
    set_ac(27);
    set_at(A_SHIELD);
    set_wt(W_AXE);
    set_hands(W_NONE);
    set_name("axe");
    set_adj("forearm");
    add_adj("obsidian");
    set_short("obsidian forearm axe");
    set_long("A large double sided axe head made of dull black "
    	+"obisidian makes up the majority of this item.  At first "
    	+"you can't tell how to use this or even what it really "
    	+"is.  A large reinforced cyclinder with what appears to "
    	+"be a handle.  The cyclinder looks much too large for any "
    	+"traditional axe haft, though.  It does look as if you "
    	+"could slip your arm into the cyclinder and grip the "
    	+"handle at the end.  By doing this you would be able to "
    	+"use the massive weight of the slick black obsidian, as "
    	+"well as use its blade as a rudimentary shield.\n");
}

