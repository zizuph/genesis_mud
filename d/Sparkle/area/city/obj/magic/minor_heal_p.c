#include <poison_types.h>
#include <herb.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>

inherit "/std/potion.c";

public void
create_potion()
{
    set_potion_name("minor healing potion");
    
    set_short("red potion");
    set_pshort("red potions");
    set_adj("red");
    set_id_long("This is a minor healing potion.\n");

    set_unid_long("This is a small glass vial filled with some red-colored fluid.\n");
    set_id_taste("The potion tastes like strawberry and gives a small soothing effect.\n");
    set_unid_taste("Hmm. Tastes rather sweet.\n");
    set_id_smell("A sweet fruity smell fills your nostrils. This is a minor healing potion.\n");
    set_unid_smell("A sweet fruity smell fills your nostrils.\n");
    
    

    set_id_diff(30);
    set_soft_amount(50);
    set_alco_amount(0);
    set_potion_value(300);
    set_effect(HERB_HEALING,"hp",300);
    add_effect(HERB_HEALING,"fatigue",50);


    
    
    seteuid(getuid(this_object()));
    
}
