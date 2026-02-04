/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/* 
* Nubes (mystic fog)
* Mystic can summon a bank of fog in which he will be able
* to hide and escape enemies.
*
 */

#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>
#include "spells.h"

#ifndef TP
#define TP this_player()
#endif

/* Function name: nubes
 */
nomask mixed
nubes(string str)
{
    object fog_room, ob;

    if (this_player()->query_mana() < NUBES_MANA_COST)
        return "You do not have the strength.\n";

    if (random(TP->query_skill(SS_ELEMENT_AIR) +
	       TP->query_skill(SS_FORM_CONJURATION))
	< random(NUBES_CAST_LIMIT))
    {
        TP->add_mana(-NUBES_MANA_COST / 3);
        write("Your prayer is not heard.\n");
        return 1;
    }

    TP->add_mana(-NUBES_MANA_COST);

    write("You call out and beckon in the mysterious shadows.\n");
    say(QCTNAME(this_player()) + " raises a hand and calls out.\n");
    tell_room(environment(TP), "A gloom descends upon this place.\n");
    tell_room(environment(TP), "A eerie fog rolls in and seems to " +
	      "consume " + QCTNAME(TP) + ".\n", TP);
    
    
    
    
    seteuid(getuid(this_object()));

    ob = clone_object(SPELL_DIR + "fog");
    ob->set_duration(DURATION(this_player()->query_stat(SS_WIS), 
        this_player()->query_skill(SS_SPELLCRAFT),
        NUBES_MIN_DURATION));
    ob->move(environment(this_player()));
    
    fog_room = clone_object(SPELL_DIR + "fog_room");
    fog_room->add_exit(file_name(environment(TP)), "back", 0);
    TP->add_prop("_fog_last_room", file_name(environment(TP)));    
    TP->move_living("M", fog_room);


    ob->set_fog_room(fog_room);
    return 1;
}
