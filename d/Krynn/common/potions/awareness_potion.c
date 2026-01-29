#pragma strict_types

inherit "/std/potion.c";

#include <herb.h>

#include "/d/Krynn/common/defs.h"


public void
create_potion()
{
    set_potion_name("astutius potion");
    set_short("golden-hued potion");
    set_pshort("golden-hued potions");
    set_adj("golden");
    add_adj("golden-hued");
    set_id_long("Quaffing this golden-hued potion will clear your mind and heigthen " +
        "your awareness. However it has a side effect of reducing your strength and " +
        "constitution.\n");
    set_unid_long("You are not sure what this golden-hued potion would do "
      + "if you quaffed it.\n");
    set_id_taste("The potion tastes sharp, and you feel your senses tingle after " +
        "trying it.\n");
    set_unid_taste("The potion tastes sharp, making your senses tingle.\n");
    set_id_smell("The potion has a strong sharp smell that clears the nose, however " +
        "is largely indescribable.\n");
    set_unid_smell("The potion smells of something and nothing.\n");
    set_id_diff(100);
    set_soft_amount(50);
    set_alco_amount(0);
    set_potion_value(17000);

    set_effect(HERB_SPECIAL, "awareness increase", 1);

    add_prop(MAGIC_AM_MAGIC,({ 20, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({"This potion has been brewed "+
             "with the use of gnome magic. Quafing it will harden your senses.\n",15}));
}

public void
special_effect()
{
    object  ob;

    seteuid(getuid());
    ob = clone_object("/d/Krynn/common/potions/awareness_object");
    ob->set_duration(600);
    if (ob->move(TP))
        ob->move(TP, 1);
}
