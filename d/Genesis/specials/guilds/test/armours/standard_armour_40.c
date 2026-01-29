#pragma strict_types
inherit "/std/armour.c";


#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#define TO this_object()
#define TP this_player()


void
create_armour()
{
    set_name(({"mail"}));
    add_name("chainmail");
    set_adj(({"shiny"}));
    set_short("shiny chainmail");
    set_long("A standard 40ac armour that covers everything.\n");
    set_at(A_TORSO|A_L_ARM|A_R_ARM|A_LEGS|A_HEAD);
    set_ac(40);
}

public int
set_condition(int cond)
{
    return 1;
}
