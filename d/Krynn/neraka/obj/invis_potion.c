/*
 *	/d/Krynn/neraka/obj/ipotion.c
 *
 *	Olorin, December 1995
 */
#pragma strict_types

inherit "/std/potion.c";

#include <herb.h>

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/neraka/local.h"

public void
create_potion()
{
    set_potion_name("invisibility potion");
    set_id_long("Quaffing this potion will make you invisible "
      + "for a few seconds.\n");
    set_unid_long("You are not sure what this potion would do "
      + "if you quaffed it.\n");
    set_id_taste("The potion tastes of nothing.\n");
    set_unid_taste("The potion tastes of nothing.\n");
    set_id_smell("The potion smells of nothing.\n");
    set_unid_smell("The potion smells of nothing.\n");
    set_id_diff(100);
    set_soft_amount(50);
    set_alco_amount(0);
    set_potion_value(72);

    set_effect(HERB_SPECIAL, "invisibility", 1);
}

public void
special_effect()
{
    object  ob;

    if (TP->query_invis())
    {
        write("Nothing seems to happen.\n");
        return;
    }

    seteuid(getuid());
    ob = clone_object(OBJ + "invis_object");
    ob->set_duration(25);
    if (ob->move(TP))
        ob->move(TP, 1);
}
