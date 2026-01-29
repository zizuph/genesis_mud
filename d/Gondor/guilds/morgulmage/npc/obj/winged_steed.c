/*
 * Winged steed for the Nazgul NPC. Derived from the player steeds
 */
#pragma strict_types

#include <const.h>
#include <tasks.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include "../../morgulmage.h"
#include <cmdparse.h>
#include <filter_funs.h>
#include <options.h>
#include <living_desc.h>
#include <composite.h>

inherit "/std/creature";
inherit "/std/combat/unarmed";

private int stage = 1;

#define ATT_BEAK  0
#define ATT_CLAWS 1

#define HIT_HEAD  0
#define HIT_BODY  1
#define HIT_LWING 2
#define HIT_RWING 3
#define HIT_LCLAW 4
#define HIT_RCLAW 5

string short_desc();
string long_desc();
string pinion_desc();
mixed no_attack();

public void 
create_creature()
{
    set_name("steed");
    add_name(({ "creature", "bird", "beast", "wyrm", "figure", "shape", "cloud" }));
    set_adj(({ "fell", "black", "winged", "dark", "monstrous", "naked",
        "huge", "distant" }));

    set_race_name("winged steed");
    set_short(short_desc);
    set_long(long_desc);

    set_gender(G_NEUTER);

    add_item(({ "wing", "wings", "pinions", "pinion", }), pinion_desc);
    add_item(({ "creature", "beast", "bird", "winged creature", "steed",
        "winged steed", "fell beast", "wyrm" }), long_desc);

    set_stats(({ 80, 20, 20,  5,  5, 10, }));

    set_skill(SS_UNARM_COMBAT, 10);
    set_skill(SS_DEFENCE, 10);

    set_whimpy(80);
    set_alignment(-700);

    set_attack_unarmed(ATT_BEAK,  10, 10, W_IMPALE,           30, "beak");
    set_attack_unarmed(ATT_CLAWS, 10, 10, W_IMPALE | W_SLASH, 70, "claws");

    set_hitloc_unarmed(HIT_HEAD,  ({ 10, 10,  5, }), 12, "head");
    set_hitloc_unarmed(HIT_BODY,  ({  5,  5,  5, }), 16, "body");
    set_hitloc_unarmed(HIT_LWING, ({ 15,  5, 10, }), 24, "left pinion");
    set_hitloc_unarmed(HIT_RWING, ({ 15,  5, 10, }), 24, "right pinion");
    set_hitloc_unarmed(HIT_LCLAW, ({ 15,  5,  5, }), 12, "left claw");
    set_hitloc_unarmed(HIT_RCLAW, ({ 15,  5,  5, }), 12, "right claw");

    add_prop(CONT_I_VOLUME,      100* 1000);
    add_prop(CONT_I_MAX_VOLUME, 1000* 1000);
    add_prop(CONT_I_WEIGHT,       89* 1000);
    add_prop(CONT_I_MAX_WEIGHT, 1000* 1000);
    add_prop(CONT_I_LIGHT, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_M_NO_ATTACK, no_attack);
    add_prop(MORGUL_I_SULAMBAR_RES, 1);
}

void
set_stage(int newstage)
{
    stage = newstage;
}

mixed
no_attack() 
{
    switch(stage) {
        case 1:
        case 2:
            return "The dark shape is circling high above you, out of "
                + "your reach.\n";
        case 3:
            return "You dare not attack the winged creature with the "
                + "black-robed hooded wraith mounted on it.\n";
        default:
            return 0;
    }
}

string pinion_desc() {
    if (stage < 4) {
        return "The vast pinions are as webs of hide between horned "
            + "fingers, and the mighty beast is beating them restlessly.\n";
    } else {
        return "The vast pinions are as webs of hide between horned "
            + "fingers. Their span must be twenty feet or more.\n";
    }
}

string 
short_desc() {
    switch(stage) {
        case 1: return "distant figure";
        case 2: return "dark shape";
        default:
            return "huge winged beast";
    }
}

string
long_desc() {
    string desc = "A winged creature: if bird, then greater than all other "
        + "birds, and it is naked, bearing neither quill nor feather, and "
        + "its vast pinions are as webs of hide between horned fingers. A "
        + "creature of an older world maybe it is, whose kind, lingering "
        + "in forgotten mountains cold beneath the Moon, outstayed their "
        + "day, and in hideous eyrie bred this last untimely brood, apt to "
        + "evil.";

    switch(stage) {
        case 1:
            return "A distant figure, which needs descriptions.\n";
        case 2:
            return "A dark shape, which needs descriptions.\n";
        case 3:
            return desc + " A black-robed hooded wraith is mounted on it.\n";
        default:
            return desc + "\n";
    }
}

void
dismiss_steed()
{
    // TODO: write message depending on stage
    remove_object();
}