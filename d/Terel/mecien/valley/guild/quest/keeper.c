/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
#include "/sys/ss_types.h"
#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <wa_types.h>

#define BSN(xx)         break_string(xx + "\n", 70)
#define TP              this_player()
#define TO              this_object()
#define MO_PROP         "_blessed_by_talhurn"
#define MO_KEY          "/d/Terel/mecien/valley/guild/mkey.c"
#define GUILD_NAME      "The Ancient Mystic Order"

#define A_HORN 0
#define A_HOOVES 1
#define A_TAIL 2

#define H_HEAD 0
#define H_BODY 1

init_living()
{
    ::init_living();
    add_action("do_pray", "pray");
}

create_creature()
{
    set_race_name("capricorn");
    set_name("lilequilel");
    add_name("guardian");
    add_name("keeper");
    add_name("creature");
    add_name("keeper of the key");
    set_short("mysterious creature");
    set_adj("mysterious");
    set_long(
      "A mysterious creature, born of myth and of the ages that never were,\n"
     +"and never shall be. Surrounded by a halo of gold light, this creature\n"
     +"has the head and forelegs of a goat, but its hindquarters are that of\n"
     +"a sparkling emerald-green fish. Its horns are somewhat spiralled and\n"
     +"look to be ivory. A power and wisdom abides in this mythic beast.\n"
      );
     
    set_gender(2);
    set_stats(({ 90, 105, 160, 108, 110, 87}));
    set_alignment(612);
    set_appearance(95);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_SPELLCRAFT, 100);
    set_skill(SS_SWIM, 100);
    
    set_hp(9000);
    set_mana(9000);
    
   set_attack_unarmed(A_HORN, 84, 68, W_BLUDGEON, 80, "horns");
   set_attack_unarmed(A_HOOVES, 45, 30, W_BLUDGEON, 40, "kicking hooves");
   set_attack_unarmed(A_TAIL, 70, 55, W_BLUDGEON, 50, "bashing tail");

   set_hitloc_unarmed(H_HEAD, 80, 10, "head");
   set_hitloc_unarmed(H_BODY, 85, 90, "body");
}

do_pray(string how)
{
    int i;
    object *obs, leaf, key;
    string s;

    write("You start to pray.\n");
    say(QCTNAME(TP) + " starts to pray.\n");
    if (!how) how = "for nothing";
    if (sscanf(how, "to %s", s) == 1) how = s;
    if (sscanf(how, "to the %s", s) == 1) how = s;
    if (sscanf(how, "for %s", s) == 1) how = s;
    if (sscanf(how, "for the %s", s) == 1) how = s;
    if (sscanf(how, "in honour of the %s", s) == 1) how = s;
    if (how == "ancient ones" || how == "Ancient Ones" ||
        how == "ancients" || how == "Ancients") {
	obs = FIND_STR_IN_OBJECT("leaf", TP);
	if (sizeof(obs)) {
	    for(i=0; i<sizeof(obs); i++) {
		if (obs[i]->query_prop(MO_PROP) == 2) {
		    leaf = obs[i];
		}
	    }
	}
	write("You pray in honour of the Ancient Ones.\n");
	say(QCTNAME(TP) + " prays in honour of the Ancient Ones.\n");
    }
    if (TP->query_guild_member(GUILD_NAME)) {
	write("Your prayer was heard by the Ancient Ones.\n");
	write("You feel relaxed.\n");
	say(QCTNAME(TP) + " feels relaxed.\n");
	return 1;
    }
    if (TP->query_npc()) return 1;
    if (leaf) {
	write("Your prayer was heard by the Ancient Ones.\n");
    write(BSN("As the Ancient Ones touch you, you feel compelled to " +
        "give the leaf to the Keeper."));
	write("Something of great importance was given to you instead.\n");
	say(QCTNAME(TP) + " has been enlightened.\n");
	key = clone_object(MO_KEY);
	if (key -> move(TP)) {
	    write("Oops! You drop it! Be careful with it!\n");
	    key -> move(environment(TP));
	}
	leaf -> remove_prop(MO_PROP);
        leaf -> move(TO);
        TO -> command("eat leaf");
    } else {
	write("Your prayer remains unheard.\n");
    }
    return 1;
}
