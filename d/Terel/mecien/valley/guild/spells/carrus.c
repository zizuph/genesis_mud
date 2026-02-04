/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#include <ss_types.h>
#include <stdproperties.h>
#include <comb_mag.h>
#include <macros.h>

#define TP            this_player()
#define ETP           environment(TP)
#define EN environment
#define MANA_LIMIT    150  
#define CAST_LIMIT    90

#define SPELLDIR "/d/Terel/mecien/valley/guild/spells/"
#define TO this_object()

/* Function name: carrus
 * Description:   transport mystic and passenger to locations
 * Arguments:     location
 * Returns:       1/0 - or failure string
 */
nomask mixed
carrus(string str)
{
    int suc;
    object room;
    object chariot;
    object chariot_room;
    object sorgum;
    
    if (NPMAGIC(TP) || NPTELEPORT(TP))
        return "Somehow you fail to cast this spell here.\n";

    room = environment(TP);
    if (room->query_prop(ROOM_I_INSIDE))
	return "You are not outside.\n";
    
    /*
     * Can't be cast during combat
     */

    if (TP->query_attack())
	return "You are too distracted by the combat to cast this " +
	    "spell.\n";
    
    if (TP->query_mana() < MANA_LIMIT)
        return "You do not have the strength.\n";

  if(!present("mystic_storm", EN(TP))) return "No storm is present.\n";

    TP->add_mana(-MANA_LIMIT);

    suc  = random(TP->query_skill(SS_FORM_ABJURATION));
    suc += random(TP->query_skill(SS_SPELLCRAFT));
    if (suc < random(CAST_LIMIT))
        return "Your prayer is not heard.\n";

    write("You cry out to the Ancients.\n");
   write("The Ancients hear your call.\n");
  say(QCTNAME(TP) + " points to the sky, beckoning to some distant power.\n");
   set_alarm(2.0, -1.9, "flash", TP);
    seteuid(getuid());
  chariot = clone_object(SPELLDIR + "chariot");
  chariot_room = clone_object(SPELLDIR + "chariot_room");
  chariot_room->set_chariot(chariot);
   chariot->set_chariot_room(chariot_room);
    chariot->set_cast_room(environment(TP));
    chariot->set_dest_room("/d/Terel/sorgum/tomb/dop_room");
    chariot->start_chariot();
    
    return 1;
}

flash(){
  tell_room(EN(TP), "There is a frightful and amazing streak of lightning flashes, followed by roaring thunder. All about things crackle with electricity.\n");
}

