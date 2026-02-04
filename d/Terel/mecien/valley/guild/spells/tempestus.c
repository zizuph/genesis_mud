/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* 
 * tempestus.c
 */

#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>

#define TP      this_player()
#define TO      this_object()
#define ETP     environment(TP)

#define MANA_LIMIT      30
#define CAST_LIMIT      80
#define SPELL_DIR	"/d/Terel/mecien/valley/guild/spells/"
#define CLOUD           SPELL_DIR + "mcloud"
#define CONTROLLER      SPELL_DIR + "storm_con"

/* Function name: tempestus
 * Description:   Will create a storm using the file mcloud.c
 *                It costs equal mana on success or failure.
 * Arguments:     str - the string from the light spell casted, must be 'room'
 * Returns:       1/0
 */
nomask mixed
tempestus(string str)
{
    object cloud, controller;

    if (ETP->query_prop(ROOM_I_INSIDE))
        return "A call to the sky cannot be heard here.\n";

    if (NPMAGIC(TP))
        return "Somehow your spell fails.\n";

    if (TP->query_mana() < MANA_LIMIT)
        return "You do not have the strength.\n";

    TP->add_mana(-MANA_LIMIT);

    if (random(TP->query_skill(SS_ELEMENT_AIR) +
        TP->query_skill(SS_FORM_CONJURATION)) < random(CAST_LIMIT))
        return "Your prayer is not heard.\n";

    write("You reach out to the winds, grasping their strength.\n");
    write("You incant the prayer of mighty skies.\n");
    say(QCTNAME(TP) + " stands tall and reaches out to the skies, "
        + "while incanting an ancient prayer.\n");
   
    seteuid(getuid());

    cloud = clone_object(CLOUD);
    controller = clone_object(CONTROLLER);

    cloud->set_controller(controller);
    controller->set_cloud(cloud);

    cloud->move(ETP);
    controller->move(TP);

    return 1;
}
