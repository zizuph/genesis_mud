// file name: /d/Avenir/common/herbs/mittikna.c
// creator(s): Ilyian, 7 April, 1995
// last update: Lilith, 27 Feb 2002:
//      per conversation with AoB (Goldberry), mittikna
//      as a non-stop light-source is too powerful, as
//      we do not have a fractional light system. I have
//      made it so the light wanes after 30 minutes, but 
//      the herb may be eaten to see in the dark for 15mins
//      within Avenir's Utterdark.
//
//  * Lucius Mar 2009: Changed to no longer emit light and
//           reduced darkvision effect. Also made it useable
//           anywhere.
//
//  * Cotillion, Apr 2015: Reduced nightvision effect to sane
//           values. Further change must be AoB approved
// purpose: origional herb, meant to be found on park island.
// note:
// bug(s):
// to-do:
#pragma strict_types

inherit "/std/herb";

#include <herb.h>
#include <stdproperties.h>
#include "/d/Avenir/include/paths.h"

public void
create_herb(void)
{
    set_name("vine");
    set_short("slender luminous vine");
    set_adj(({"slender","luminous"}));

    set_herb_name("mittikna");
    set_id_long("This slim vine is known as Mittikna, or Light-Vine, so "
      +"named because while it lives, it gives off a pale, luminescent "
      +"glow. It is also known to grant the ability to see in the dark.\n");
    set_unid_long("This is a long, translucent vine. It seems to glow with "
      +"a pale inner light.\n");

    set_id_diff(30);
    set_find_diff(3);
    set_decay_time(200);
    set_herb_value(450);

    set_ingest_verb("eat");
    set_effect(HERB_SPECIAL, "", 10);
}

public void
special_effect(void)
{
    object ob = clone_object(HERB + "special/mittikna_see");
    // 1.5 - 3 minutes.
    ob->set_time(90 + random(90));
    ob->move(this_player(), 1);
}
