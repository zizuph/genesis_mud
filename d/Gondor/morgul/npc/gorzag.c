#pragma strict_types

inherit "/d/Gondor/morgul/npc/ithil_monster.c";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define SEQ_PICK  "_mon_pick"

public void
create_ithil_monster() 
{
    set_living_name("gorzag");
    set_name("gorzag");
    add_name(({"shopkeeper","owner","shopowner",}));
    set_race_name("orc");
    set_adj(({"filthy","dark-skinned"}));
    set_long(BSN(
        "This is Gorzag the shopkeeper, who runs the Armoury in Minas Morgul. "+
        "He is probably quite competent with numbers, even though he is an orc - " +
        "trade is his speciality, but he likes cheating and stealing, too!"));
    default_config_npc(62);
    set_base_stat(SS_CON,95);
    set_base_stat(SS_STR,95);
    set_skill(SS_WEP_SWORD, random(10)+90);
    set_skill(SS_AWARENESS, random(10)+90);
    set_skill(SS_DEFENCE, random(10)+90);
    set_skill(SS_PARRY, random(10)+90);
    set_skill(SS_TRADING, random(10)+90);
    set_alignment(-100-random(200));
    set_chat_time(12);
    add_chat("What do you want?");
    add_chat("Gimme your coins and be gone!");
    add_chat("Me Gorzag, you what?");
    add_chat("You got any nice weapons to sell?");
    add_chat("You want to buy mighty good things?");
	add_chat("You here to trade, or to use the forge?");
	add_chat("This place stinks worse than normal since that forge was opened.");
    add_cchat("Get out of here, you stinking thief!");
    add_cchat("I'll eat your corpse really soon now!");
    add_cchat("Come here, you orcs! Fresh meat!");
    add_chat("Give back what you have stolen!");  

    remove_prop(LIVE_I_NEVERKNOWN);

    set_pick_up(0);
}

public void
arm_me()
{
    FIX_EUID
    clone_object(MORGUL_DIR + "obj/ithilsword")->move(TO);
    command("wield sword");
    clone_object(MORGUL_DIR + "obj/ltunic")->move(TO);
    command("wear armour");

    seq_delete(SEQ_PICK);
}

/* solamnian prestige */
public int query_knight_prestige() { return -3; }

