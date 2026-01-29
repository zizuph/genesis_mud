 /*
  * alfirin.c
  *
  * Olorin, July 1995
  */
#pragma save_binary
#pragma strict_types

inherit "/std/herb.c";

#include <composite.h>
#include <herb.h>
#include <macros.h>

#include "/d/Gondor/defs.h"

void
create_herb()
{
    set_name("flower");
    set_adj("golden");
    set_herb_name("alfirin");
    set_short("golden flower");
    set_pshort("golden flowers");
    set_ingest_verb("chew");
    set_unid_long("A golden flower.\n");
    set_id_long(BSN("This golden flower is called Alfirin. It is "
      + "most frequent in the fields of Lebennin, but is known "
      + "to grow in Rohan, too. It is said that chewing "
      + "alfirin can cure snake poison."));
    set_herb_value(72);
    set_id_diff(30);
    set_find_diff(3);
    set_effect(HERB_CURING, "snake", 40 + random(41));
    set_decay_time(5400);
    set_dryable();
}

void
consume_text(object *arr, string vb)
{
    string  str;

    if (vb == "chew")
    {
        write("You " + vb + " on " + (str = COMPOSITE_DEAD(arr))
          + " for some time, and then spit out the remains.\n");
        say(QCTNAME(this_player()) + " " + vb + "s on " + str
          + " for some time and then spits out the remains.\n");
    }
    else
    {
        write("You " + vb + " " + (str = COMPOSITE_DEAD(arr)) + ".\n");
        say(QCTNAME(this_player()) + " " + vb + "s " + str + ".\n");
    }
}

