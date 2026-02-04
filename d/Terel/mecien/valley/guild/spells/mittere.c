/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include <ss_types.h>
#include <comb_mag.h>
#include "spells.h"
#define TO this_object()
#define TP this_player()

nomask mixed
mittere(string str)
{
    string obj, who, them, msg;
    object *arr, receiver;
    int val, vol, wei, mana;
    int suc;

    if (!strlen(str)) return "Mittere what to who?\n";

    if (sscanf(str, "%s to %s", obj, who) !=2) {
        return "Mittere what to who?\n";
    }
    arr = FIND_STR_IN_OBJECT(obj, TP);
    if (sizeof(arr) == 0) return "Mittere what to who?\n";
    if (sizeof(arr) >= 2) return "Mittere what to who?\n";

    if (environment(TP)->query_prop(ROOM_M_NO_TELEPORT))
	return "The ancient powers are too weak in this room.\n";

    if (living(arr[0])) {
        return "The ancient powers cannot handle living beings.\n";
    }

    if (arr[0]->query_prop(OBJ_M_NO_MAGIC)) {
	return "That object resists the ancient powers.\n";
    }
	
    val = arr[0]->query_prop(OBJ_I_VALUE);
    vol = arr[0]->query_prop(OBJ_I_VOLUME);
    wei = arr[0]->query_prop(OBJ_I_WEIGHT);


    receiver = find_living(lower_case(who));
    if (!receiver) {
        return "The voice seeks but finds no such person.\n";
    }

    if (NPMAGIC(receiver))
	return "The ancient powers can not reach that person.\n";

    suc = random(TP->query_skill(SS_ELEMENT_AIR));
    suc += random(TP->query_skill(SS_SPELLCRAFT));

    if (suc < random(MITTERE_CAST_LIMIT)) {
	TP->add_mana(-MITTERE_MANA_COST/3);
	return "Your prayer is not heard.\n";
    }
		  
		 
    mana = TP->query_mana();
    if (mana < MITTERE_MANA_COST) return "You do not have the strength.\n";

/*
    if (val/10 > TP->query_stat(SS_WIS)) {
        return "The "+arr[0]->short()+" is too valuable for you "+
               "to handle like this.\n";
    }
 */
    if (vol/500 > TP->query_stat(SS_WIS)) {
        return "The "+arr[0]->short()+" is too big for you to handle.\n";
    }
    if (wei/500 > TP->query_stat(SS_WIS)) {
        return "The "+arr[0]->short()+" weighs too much.\n";
    }
    if (arr[0]->move(receiver)) {
        return "The "+arr[0]->short()+" cannot travel through "+
               "time and space.\n";
    }
    write("You invoke the spirits of time and space with a "+
          "mystic blessing.\n");
    write("The "+arr[0]->short()+" disappears in a flash of "+
          "blue light.\n");
    msg = "In a flash of blue light, "+LANG_ASHORT(arr[0])+
          " appears in your hands.\n";
    receiver->catch_msg(msg);
  tell_room(environment(receiver), "A flash of blue light " +
   "emanates from " + QTNAME(receiver) + ".\n", receiver);
    TP->add_mana(-MITTERE_MANA_COST);
  return 1;
}
