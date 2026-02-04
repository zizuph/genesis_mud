/*
 * Farm2c.c   Tomas  -- Jan 2000
 *
 * Lucius - Feb 2021
 *    Cleaned and modernized.
 */
#include "farm.h"
inherit FARMRM;

public void
create_terel_room()
{
    set_short("courtyard");
    set_long("You stand at the entrance to a small fenced courtyard. " +
      "Three small houses face the courtyard connected by " +
      "a short rock and mortar fence. In the middle of the courtyard " +
      "is a well. The road leads back towards the southwest.\n");

    add_item(("well"),"The rock and mortar well looks to be the main " +
      "source of water for the small community.\n");

    add_item(("fence"),"The short fence looks like it was built to keep " +
      "the animals out of the living areas of the farm.\n");

    add_item(({"track"}), "It's a small track, but it appears to be used " +
      "every now and then.\n");

    add_item(({"farm"}), "The farm consists of three separate " +
      "houses, placed around a courtyard.\n");

    add_item(({"field", "fields"}), "The fields are now covered" +
      " with snow, but still, some kind of rye grow there.\n");

    add_item(({"snow"}), "It's pure snow.\n");

    add_item(({"rye"}), "This kind of rye must be quite tough " +
      "since it endures this harsh climate.\n");

    add_item(({"farmhouses","farmhouse","houses","house"}),
      "The three small houses are similiar in build and size. " +
      "The walls are constructed of waddle, thatch and mortar. " +
      "The roofs are wooden framed covered in sod. Each house " +
      "looks to be one or two rooms in size.\n");

    add_item(("path"),"The small cobbled path leads to a coupe behind " +
      "the houses.\n");

    add_exit(CFARMS + "farm2b","southwest",0,1);

    room_add_object(CFARMS + "obj/farm2d_door");
    room_add_object(CFARMS + "obj/farm2e_door");
    room_add_object(CFARMS + "obj/farm2f_door");

    add_npc(CFARMS + "npc/farmer_farm2");
    add_npc(CFARMS + "monsters/horse");
    add_npc(CFARMS + "monsters/farm2_dog");
}
