/* A dagger  */
#pragma strict_types

inherit "/std/weapon.c";
inherit "/lib/keep.c";

#include <formulas.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

public int     test_give();

static int     Given_Away;

public void
create_weapon()
{
    set_name("dagger"); 
    set_pname("daggers");
    add_name("weapon");
    add_pname("weapons");
    set_short("long leaf-shaped dagger");
    set_pshort("long leaf-shaped daggers");
    set_adj("long");
    add_adj("leaf-shaped");
    set_long(BSN("It is a long, leaf-shaped dagger with "+
	"a keen edge. It seems to be of marvellous workmanship, damasked with "+
	"serpent-forms in red and gold."));

    set_default_weapon(32,35,W_KNIFE,W_SLASH|W_IMPALE,W_ANYH,0);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(32,35)+random(400)+200);
    add_prop(OBJ_I_WEIGHT, 3200);
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({ 30, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO,({ 10, "The long, leaf-shaped dagger radiates magic.\n",
	25, "It is enchanted to improve its effectiveness.\n",
	50, "It was forged many long years ago by Men of Westernesse\n"+
	"It was specially made to work against Evil.\n", }));
    add_prop(OBJ_M_NO_BUY,1);
    add_prop(OBJ_M_NO_GIVE, test_give);
}

public int
test_give()
{
    FIX_EUID;
    Given_Away = 1;
    return 0;
}

public void
enter_env(object to, object from)
{
    ::enter_env(to, from);
    if (!Given_Away) 
	return;
    Given_Away = 0;
    if (living(to) && living(from))
	log_file("items", from->query_name() + 
	  " gave a Numenorean dagger to " + to->query_name() +
	  ". "+ctime(time())+".\n");
}

