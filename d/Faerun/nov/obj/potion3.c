
#include <poison_types.h>
#include <herb.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "../nov.h";

inherit "/std/potion.c";

public void
create_potion()
{
    set_potion_name("chrimin");
    add_name("_brew3");
    set_short("dark-blue potion");
    set_pshort("dark-blue potions");
    set_adj("dark-blue");
    set_id_long("This is the black brew known as the " +
    "Tear of Bane, which is a main component in the dark ritual that " +
    "Bane's high Imperceptors execute when creating a Banedead.\n");
    set_unid_long("This is a small glass vial filled with some black " +
    "brew. The vial is freezing cold.\n");
    set_id_taste("The potion's brew tastes like nothing you have tasted " +
    "before. You can feel your tongue begins to partically freeze as the first " +
    "drops of the brew touches it.\n");
    set_unid_taste("The potion's brew tastes like nothing you have tasted " +
    "before. You can feel your tongue begins to partically freeze when the first " +
    "drops of the brew touches it.\n");
    set_id_smell("Rigid frost forces its way up your nostrils! You cannot smell anything.\n");
    set_unid_smell("Rigid frost forces its way up your nostrils! You cannot smell anything.\n");
    set_id_diff(100);
    set_soft_amount(50);
    set_alco_amount(5);
    set_potion_value(8000);
    set_effect(HERB_POISONING, "hp", 5);
    set_poison_file(NOV_DIR +"obj/brew3_pois");
    
    
    seteuid(getuid(this_object()));
    
}




