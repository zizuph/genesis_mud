#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <herb.h>
#include <language.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("leaf");
    set_short("green leaf");
    set_pshort("green leaves");
    set_adj("green");
    set_id_long(BSN("This is one of the illegal Angurth leaves, used to "
      + "produce addictive and dangerous drugs. You guess it would be a "
      + "bad idea to eat it."));
    set_unid_long("This green leaf smells quite strange. You wonder "
      + "what it is for.\n");
    set_herb_name("angurth");
    set_id_diff(35);
    set_find_diff(5);
    set_herb_value(144);
    set_effect(HERB_POISONING,"fatigue",50);
    set_decay_time(7200);
    set_dryable();
}

// for Fredor's quest
int     is_quest_herb() { return 1; }

int
do_smell(string str)
{
    if (!strlen(str) || !id(str))
    {
	NF("Smell what?\n");
        return 0;
    }
    write("You smell at the "+short()+".\n"
	  + "The smell is very strong and makes you a bit dizzy.\n"
	  + "It reminds you of glue and of rotten corpses.\n");
    say(QCTNAME(TP) + " smells at "+LANG_ADDART(short())+".\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(do_smell, "smell");
}

