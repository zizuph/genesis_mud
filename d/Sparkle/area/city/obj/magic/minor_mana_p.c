#include <poison_types.h>
#include <herb.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>


inherit "/std/potion.c";

public void
create_potion()
{
    set_potion_name("minor mana potion");
    
    set_short("blue potion");
    set_pshort("blue potions");
    set_adj("blue");
    set_id_long("This is a minor mana potion.\n");

    set_unid_long("This is a small glass vial filled with some blue-colored fluid.\n");
    set_id_taste("The potion tastes like blueberry and gives a slight mindresting effect.\n");
    set_unid_taste("Hmm. Tastes rather sweet.\n");
    set_id_smell("A sweet fruity smell fills your nostrils. This is a minor mana potion.\n");
    set_unid_smell("A sweet fruity smell fills your nostrils.\n");
    
    

    set_id_diff(50);
    set_soft_amount(50);
    set_alco_amount(0);
    set_potion_value(3000);
    set_effect(HERB_HEALING,"mana",1000);
    


    
    
    seteuid(getuid(this_object()));
    
}
