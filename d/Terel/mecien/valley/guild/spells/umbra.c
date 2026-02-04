/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
 * This spell turns the player into an animal.
 */

#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP            this_player()
#define TO            this_object()
#define CAST_LIMIT    50
#define MANA_COST	100
#define IMMUTO_DIR "/d/Terel/mecien/valley/guild/spells/immuto/"
nomask mixed
umbra()
{
    object animal, control, room, who;
    int mana_limit, suc, dur;
    string dum;


  who = TP;
    if (TP->query_mana() < mana_limit)
        return "You do not have the strength.\n";

    suc  = random(TP->query_skill(SS_FORM_TRANSMUTATION));
    suc += random(TP->query_skill(SS_ELEMENT_LIFE));
    if (suc < random(CAST_LIMIT)) {
        TP->add_mana(-mana_limit / 3);
        return "Your call is not heard.\n";
    }

    TP->add_mana(-mana_limit);
    write("You invoke the ancient spirits.\n");
    say(QCTNAME(TP) + " intones a mystic chant.\n");

    seteuid(getuid(TO));
    control = clone_object(IMMUTO_DIR + "transf_npc");
    animal  = clone_object(IMMUTO_DIR + "shadow");
    room    = clone_object(IMMUTO_DIR + "void");

    dur = 240 + TP->query_stat(SS_INT) + TP->query_stat(SS_WIS) +
          random(10);
    control->set_duration(dur);
    control->set_void_room(room);

  animal->set_animal_soul(IMMUTO_DIR + "soul_shadow");
  animal->set_player_link(who, control);
    
    return 1;
}
