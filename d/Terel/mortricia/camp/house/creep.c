/* A creep. Mortricia 920927 */
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()
#define CAMP_DIR        MORTRICIADIR + "camp/"
#define HAUN_DIR        CAMP_DIR + "house/"
#define EQUIP_DIR       HAUN_DIR + "equip/"

#define ALIGN           500
#define NO_OF_ADJS      5

#define H_HEAD          0
#define H_BODY          1
#define H_LEGS          2

#define A_JAWS          0
#define A_CLAW          1

void
create_creature()
{
    int i, j;
    string *adj, *kadj;
    object knife;

    adj  = ({"ugly","slimy","awful","nasty","shabby"});
    kadj = ({"red", "blue", "green","white","black"});

    if (!IS_CLONE)
        return;

    set_name("creep");
    i = random(NO_OF_ADJS);
    set_long(BSN(
        "It's a little " + adj[i] + " creep. It's impossible " +
        "to tell what it really is. All you see is a hairy body, " +
        "a small head with three staring eyes, and, at least, " +
        "six legs."
        ));
    set_short(adj[i] + " creep");
    set_adj(adj[i]);
    set_race_name("creep");
    set_gender(2);

    add_item("body", BSN(
        "The body is almost spherical, with lots of dirty hair " +
        "on it."
        ));
    add_item("head", BSN(
        "The head is quite small, and one of its tree eyes " +
        "keeps stares at you. You also " +
        "notice a mouth with some sharp teeth."
        ));
    add_item("eyes", BSN(
        "Two of the eyes scan the room for intruders, the third " +
        "is staring at you."
        ));
    add_item("legs", BSN(
        "The legs are quite thin, but each is ended by some " +
        "nasty looking claws."
        ));

    set_stats(({15+i,15+i,15-i,15+i,15-i,15-i}));
    set_hp(9999);
    set_mana(9999);
   set_alignment(-random(ALIGN));
    set_whimpy(30);
    set_skill(SS_DEFENCE, 15);
    set_skill(SS_UNARM_COMBAT, 15);
    set_skill(SS_AWARENESS, 15);

    set_hitloc_unarmed(H_HEAD, ({ 5, 10, 10}), 20, "head");
    set_hitloc_unarmed(H_BODY, ({20, 20, 20}), 50, "body");
    set_hitloc_unarmed(H_LEGS, ({20, 10, 15}), 30, "legs");

    set_attack_unarmed(A_JAWS, 20, 20, W_IMPALE,   80, "bite");
    set_attack_unarmed(A_CLAW, 10, 10, W_BLUDGEON, 20, "claws");

    j = random(NO_OF_ADJS);
    knife = clone_object(EQUIP_DIR + "knife_c");
    knife -> set_short(kadj[j] + " knife");
    knife -> set_pshort(kadj[j] + " knives");
    knife -> set_adj(kadj[j]);
    knife -> set_long(BSN(
             "It is a simple looking " + kadj[j] + " knife."
             ));
    knife -> move(TO);

    MONEY_MAKE_SC(3) -> move(TO);
}
