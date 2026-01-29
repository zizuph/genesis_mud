/* Navarre December 2005, added magical property. */

#pragma strict_types

inherit "/std/potion.c";

#include <herb.h>

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"

public void
create_potion()
{
    set_potion_name("potion of swimming");
    add_name("_bishon_quest_potion");
    set_short("sea-green potion");
    set_pshort("sea-green potions");
    set_adj("sea-green");
    add_adj("green");
    set_id_long("Quaffing this sea-green potion will allow you to swim more "
      + "proficiently for a few minutes.\n");
    set_unid_long("You are not sure what this sea-green potion would do "
      + "if you quaffed it.\n");
    set_id_taste("The potion tastes of the sea.\n");
    set_unid_taste("The potion tastes of the sea.\n");
    set_id_smell("The potion smells of sea water.\n");
    set_unid_smell("The potion smells of sea water.\n");
    set_id_diff(100);
    set_soft_amount(50);
    set_alco_amount(0);
    set_potion_value(72);

    set_effect(HERB_SPECIAL, "swim increase", 1);

    add_prop(MAGIC_AM_MAGIC,({ 20, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This potion has been brewed "+
             "by the sea-elves. It is used to provide their "+
             "friends living on land a way to visit them in "+
             "their home.\n",15}));
}

public void
special_effect()
{
    object  ob;

    seteuid(getuid());
    ob = clone_object(BOBJ + "swim_object");
    ob->set_duration(1200);
    if (ob->move(TP))
        ob->move(TP, 1);
}
