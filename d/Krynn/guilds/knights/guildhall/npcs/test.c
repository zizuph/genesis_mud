/*
 * Chert Armstrong
 * modified from Toede.
 * by Teth
 * Jan.12,'97
*/

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include "../../local.h";
#include <macros.h> 
inherit M_FILE /* The Krynn humanoid monster file */

inherit "/std/act/action";

public void
create_krynn_monster()
{
    string str;

    set_name("namewithans");
    set_living_name("chert");
    set_race_name("dwarf");
    set_title("Armstrong of Thorbardin, Famed Blacksmith");
    set_long("This dwarf is well-muscled. A black beard sprouts " +
      "from his chin and cheeks in disarray, while deep black eyes " +
      "glare beneath a sweating forehead. He is obviously a " +
      "blacksmith.\n");
    add_name(({"armstrong","blacksmith","smith"}));
    set_adj("well-muscled");
    add_adj("black-bearded"); 
    set_gender(G_MALE);
    add_prop(CONT_I_HEIGHT, 120);
    add_prop(CONT_I_WEIGHT, 30000);
    add_prop(NPC_I_NO_LOOKS,1);
    set_introduce(1);

    set_stats(({120,90,200,60,60,120}));
    set_skill(SS_DEFENCE,        100);
    set_skill(SS_PARRY,          100);
    set_skill(SS_WEP_CLUB,       100);
    set_skill(SS_BLIND_COMBAT,   100);

    set_alignment(440);
    set_knight_prestige(-2);

    set_default_answer("For some reason, you are ignored.\n");
    add_ask(" [about] 'wax' / 'repair'", "say Read the sign!",1);
    add_ask(" [about] 'task' / 'quest'", "say I've everything " +
      "I need here in Vingaard Keep, thank you very much.",1);
    add_ask(" [about] 'steel'","say Solamnian steel is some of " +
      "the finest in the land! I craft weapons and armours, and " +
      "the store north of here sells them to Knights!",1);

    set_act_time(4);
    add_act("say Steel is a fine metal to work with!");
    add_act("emote looks at his work with appraising glances, ensuring " +
      "quality.");
    add_act("emote hammers a piece of metal repeatedly!\n\nCLANG!\n\n" +
      "CLANG!\n\nCLANG!\n\n\n");
    add_act("emote uses the bellows to stoke the fire.");
    add_act("say One day, I wish my craftsmanship would rival that of " +
      "the ancient dwarves!");
    add_act("shout By Reorx! I'm a fine craftsman!");
    add_act("emote wipes the sweat from his brow.");

    set_cact_time(3);
    add_cact("shout I'll smash your head soft like molten metal!");
    add_cact("shout Someone dares to attack me! Fool!");

}

public void
arm_me()
{
    clone_object(VWEP + "smith_hammer")->move(TO);
    clone_object(VARM + "s_shield")->move(TO);
    command("wield all");
    command("wear all");
}


