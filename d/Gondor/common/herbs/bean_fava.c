 /*
  * bean_fava.c
  *
  * zephram 951105
  *
  * Olorin, April 1993
  *
  * 31-Aug-98, Gnadnar: changed the player-visible name (but not the file 
  *	name) to "broad bean", so that we get fewer mistaken typo reports.
  *	the species really is "faba" with a 'b', but when the visible name
  *	is "fava", players understandably think "faba" a typo.
  *	with elessar's permission, removed the code to make humans & elves flee,
  *
  */
#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"

#define PANIC_HEAL 10

void
create_herb()
{
    set_name("bean");
    set_adj(({"light","brown","small"}));
    set_herb_name("broad bean");
    set_short("small light brown bean");
    set_pshort("small light brown beans");
    set_ingest_verb("eat");
    set_unid_long("This is a small, light brown bean.\n");
    set_id_long(BSN("This small, light brown bean is known as the " 
      + "broad bean, or field bean. It is said to have been brought to "
      + "Rhovanion and Eriador by dwarves of forgotten houses fleeing "
      + "the depredations of the Warlord Fankil at the end of the Third "
      + "Age of the Chaining of Melkor, but it now may be found under "
      + "cultivation in many lands."));
    set_herb_value(60);
    set_id_diff(10);
    set_find_diff(5);
    set_effect(HERB_HEALING, "panic", PANIC_HEAL);
    set_decay_time(7200);
    set_dryable();
    set_amount(1);
    add_prop(OBJ_I_WEIGHT, 1);
    add_prop(OBJ_I_VOLUME, 1);
}


int
command_eat()
{
    int     result;

    result = ::command_eat();

    if (result)
    {
        setuid();
        seteuid(getuid());
        clone_object(HERB_DIR + "stench_bean")->move(TP, 1);
    }

    return result;
}
