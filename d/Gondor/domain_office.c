/*
 * /d/Gondor/domain_office.c
 *
 * December 1996, Olorin
 *
 * Copyright (c) 1996 by Christian Markus
 *
 * Modification log:
 *
 *  2008-04-23, Toby: Added the quest orb.
 *
 */
#pragma strict_types

#include "/d/Genesis/start/human/town/tower.h"

inherit TOWER_OFFICE; 

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

static object  Envoy;

public void
reset_room()
{
    object quest_orb;
    
    if (objectp(Envoy))
        return;

    Envoy = clone_object(PROJECT_DIR + "ambassador");
    Envoy->arm_me();
    Envoy->move_living("down", TO);

    if (!present("_genesis_quest_orb"))
    {
        quest_orb = clone_object(QUEST_ORB);
        quest_orb->set_orb_domain("Gondor");
        quest_orb->set_extra_line("It is hovering next to the office's desk.");
        quest_orb->move(this_object(), 1);
    }    
}

static string
read_sign()
{
    return "Engraved onto the plaque are the following words:\n"
      +    "\n"
      +    "wizards              - List the wizards of Gondor.\n"
      +    "projects gondor      - List the projects of Gondor.\n"
      +    "projects <wizard>    - List the projects of a particular wizard.\n"
      +    "\n";
}

public void
create_tower_office()
{
    set_long("The office of the ambassador of Gondor to Sparkle.\n"
      + BSN("By order of the Steward of the realm, Gondor has opened "
          + "an embassy in Sparkle. Behind the desk of the ambassador, "
          + "a bronze plaque is hanging on the wall, supplying the "
          + "visitor with information."));

    add_item(({"desk", }),
	BSN("The large wooden desk is almost empty. "
      + "Only a few empty sheets of paper are lying on top of the "
      + "desk. Obviously the ambassador is quite efficient in "
      + "completing his paperwork."));
    add_item(({"plaque", "sign", }), read_sign());
    add_cmd_item(({"plaque", "sign", }), "read", read_sign());

    set_project_path(PROJECT_DIR);
    disable_logged_in_display();

    add_tower_link("tower");

    reset_room();

    add_prop(ROOM_S_MAP_FILE, "domain_office.txt");
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_ATTACK, "The embassy is protected by "
      + "diplomatic immunity. Fights are not permitted here!\n");
}

