 /*
  *  /d/Sparkle/common/herbs/cattail.c
  *
  *  A herb one can find. It doesn't have any special effect, but it
  *  does serve as a nice meal in a pinch.
  *
  *  Created by Cooper Sherry (Gorboth), May 2009
  */
#pragma save_binary
#pragma strict_types

inherit "/std/herb";

#include <herb.h>
#include <macros.h>

/* Prototypes */
public void        create_herb();


/*
 * Function name:        create_herb
 * Description  :        the constructor for the herb object
 */
public void
create_herb()
{
    set_name("plant");
    add_name( ({ "leaf" }) );
    set_adj(({"handful", "of", "threadlike", "fine"}));

    set_herb_name("cattail");

    set_short("tall reedlike marsh plant");

    set_ingest_verb("eat");

    set_unid_long("This is a tall reedlike marsh plant - the sort commonly"
      + " seen growing along the edges of rivers or lakes.\n");
    set_id_long("These tall, reedlike marsh plants are commonly referred to"
      + " as cattails (Typha Latifolia) and are known to grow in very"
      + " wet areas where water either runs gently or is still. Long,"
      + " sword-shaped leaves are capped by dense, cylindrical clusters"
      + " of minute brown flowers, which are quite edible. In fact,"
      + " this particular variety which is native to Sparkle is widely"
      + " recognized as an excellent and filling meal in a pinch.\n");

    set_amount(350); /* These are a bit of a meal. */

    set_id_diff(10);
    set_find_diff(2);
    set_decay_time(5400);
    set_herb_value(36);
    set_dryable();
} /* create_herb */
