/* Pully Gully dwarf by percy*/

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "../xlocal.h"

inherit M_FILE

void
create_krynn_monster()
{
    int i;
    
    set_name("gully dwarf");
    set_race_name("dwarf");
    set_long("It's a dirty, smelly and very ugly gully dwarf."
	     + " It doesn't look particularly bright either.. it seems"
	     + " to be looking after the lifts pully.\n");
    add_name("gully");
    set_adj("dirty");
    add_adj("gully");
    set_pname("gully dwarves");
    add_pname("dwarves");
    set_pshort("dirty gully dwarves");

    for (i = 0; i < 6; i++)
      set_base_stat(i, 10 + random(10));
    
    set_all_attack_unarmed(10, 10);
    set_all_hitloc_unarmed(10);
    set_alignment(50);
    
    set_default_answer("The Gully dwarf says: Me not know that.\n");
    add_ask(({"dragon", "black dragon", "dragons", "black dragons"}),
	    VBFC_ME("dragonhint"));
    add_ask(({"draconian", "draconians", "dragornian", "dragornians"}),
	    VBFC_ME("dracohint"));
    add_ask(({"lift", "basket", "baskets"}), VBFC_ME("lifthint"));
    
    add_act("emote tries to stand on it's head but fails miserably.");
    add_act("emote lies down and moans a bit, you think it is pretending to be " +
	    "dead.");
    add_act("emote looks at you fearfully.");
    add_act("emote eats part of a dead rat.. at least if it wasn't dead, it is " +
	    "now.");
    add_act("emote has a strange grin on it's face.");
    add_act("emote tries to stand on it's head and succeeds!!");
    add_act("emote gulps nervously.");
    set_act_time(22);
    add_chat("Ug.. you here to kill dragon?");
    add_chat("Do you like our lift?");
    add_chat("Theres not more than one dragornian down there, definitely not more " +
	     "than one.");
    set_chat_time(32);
    
    add_prop(NPC_I_NO_RUN_AWAY, 1);
	
}

string
dragonhint()
{
    command("say You don't want to go fight big dragon. Me know. He's"
	    + " bigger and blacker than you. He'll open his mouff and you'll"
	    + " be turned into horrible black puddle on floor like other "
	    + "poor gully dwarfies..");
    return "";
}

string
dracohint()
{
    command("say Dracorgians not smart like us, they need us to get up"
	    + " here wiff our lift.");
    return "";
}

string
lifthint()
{
    command("say Lift take you down, we slow you before you hit ground, "
	    + "me promise.");
    return "";
}

	
