
 /*    A Triton Magician for the Thalassian City Citadel

    coder(s):    Jaacar

    history:    24.07.03   coded          Jaacar
    
 */

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include "/d/Genesis/gems/gem.h"
#include "defs.h"
#include GLYKDEF
#include RANDOM_HEADER
inherit SEA_CREATURES+"triton";
inherit "/lib/unique";

void
equip_me()
{
    object this, gem, staff;
    string type;

    this = THIS;
    seteuid(getuid(this));
    staff = clone_unique(SEA_WEAPONS+"water_staff",3,
        ({SEA_WEAPONS+"tin_trident",100}),1,100);
    staff->move(this);

    command("wield all");
    clone_object(SEA_ARMOURS+"triton_robe")->move(this);
    command("wear all");
    MONEY_MAKE_GC((random(8)))->move(this);
    if (random(5))
    {
        gem=RANDOM_GEM_BY_RARITY(GEM_SLIGHTLY_COMMON);
        gem->move(this);
    }
}

void
create_triton()
{
    if (!IS_CLONE)
	return;

    ::create_triton();
    set_long("This robed triton looks is human in appearance above "+
        "the waist, but has a large fish-like tail instead of legs. "+
        "His robe covers his body but you can see he long, sharp "+
        "claws on his webbed fingers that he has wrapped around a "+
        "blue quarterstaff. His friendly smile reveals what look "+
        "like very sharp fish teeth.\n");

    set_race_name("triton");
    set_base_stat(SS_INT, (90+random(30)));
    set_base_stat(SS_WIS, (90+random(30)));
    set_base_stat(SS_DIS, (90+random(30)));
    set_base_stat(SS_STR, (90+random(30)));
    set_base_stat(SS_DEX, (90+random(30)));
    set_base_stat(SS_CON, (90+random(30)));
    set_skill(SS_WEP_POLEARM, (65+random(30)));
    set_skill(SS_PARRY, (65+random(30)));
    set_skill(SS_DEFENCE, (65+random(30)));
    set_skill(SS_ELEMENT_WATER, (60+random(30)));
    add_prop(LIVE_I_NEVERKNOWN,1);
    set_alignment(200);
    add_prop(CONT_I_WEIGHT, 75000);
    add_prop(CONT_I_VOLUME, 75000);
    set_random_move(10);
    set_restrain_path(({(THALL),(THALM),(THALC)}));
    set_all_hitloc_unarmed(query_average_stat() / 4);
}

