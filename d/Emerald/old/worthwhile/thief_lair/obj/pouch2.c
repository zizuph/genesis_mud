 
/*  pouch2.c is cloned by various thiefs in thief_lair/npc/ */
 
/* A money pouch. It contains a bit of money for our thieves. */
/* Coded by Tulix, 24/4/93 */
 
inherit "/std/container";
#include "/d/Emerald/defs.h"
#include "/sys/macros.h"
#include "/sys/money.h"
 
 
void
create_container()
{
    object cop, sil, gol;
 
    seteuid(getuid());
    set_name("pouch");
    set_pname("pouches");
    set_short("money pouch");
    set_pshort("money pouches");
    set_adj("money");
    add_adj("leather");
    set_long("It's a handy leather money pounch.\n");
 
    add_prop(CONT_I_WEIGHT, 100); /* weighs 100g */
    add_prop(CONT_I_MAX_WEIGHT, 3000); /* can hold 2900g */
    add_prop(CONT_I_VOLUME, 50); /* takes up 50ml */
    add_prop(CONT_I_MAX_VOLUME, 1000); /* can take 950ml */
 
    if (IS_CLONE)
    {
    cop=MONEY_MAKE_CC(random(50));
    cop->move(this_object());
 
    sil=MONEY_MAKE_SC(random(20)+10);
    sil->move(this_object());
 
    gol=MONEY_MAKE_GC(random(2));
    gol->move(this_object());
    }
}
