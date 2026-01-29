/* Gully dwarf by percy*/

#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "../xlocal.h"

inherit M_FILE

int secret;

void
create_krynn_monster()
{
    int i;
    set_living_name("bupu");
    set_name("bupu");
    set_race_name("dwarf");
    set_long("She is a dirty, smelly and very ugly gully dwarf. She "+
	     "doesn't look particularly bright either but she looks like " +
	     "she may be a leader of some sort.\n");
    add_name("gully");
    add_name("gully dwarf");
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
    set_gender(G_FEMALE);
    
    set_default_answer("The Gully dwarf says: Me not know that.\n");
    add_ask(({"dragon", "black dragon", "dragons", "black dragons"}),
	    VBFC_ME("dragonhint"));
    add_ask(({"draconian", "draconians", "dragornian", "dragornians"}),
	    VBFC_ME("dracohint"));
    add_ask(({"lift", "basket", "baskets"}),
	    VBFC_ME("lifthint"));
    add_ask(({"door", "secret door", "secret"}),
	    VBFC_ME("secret"));
    
    add_act("emote rumages around in a small cloth bag.");
    add_act("emote lies down and moans a bit, you think it is pretending " +
	    "to be dead.");
    add_act("emote looks at you fearfully.");
    add_act("emote gets a dead rat from her bag and waves it in your face.");
    add_act("emote has a strange grin on her face.");
    add_act("emote tries to stand on her head and succeeds!!");
    add_act("emote gulps nervously.");
    set_act_time(42);
    add_chat("gulp.. you here to kill dragon?");
    
    set_chat_time(42);
    
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
	    + "me promise. But you not want to go that way, lots and lots of"
	    + " nasty dragonians eat you. I know a secret way...");
    return "";
}

string
secret()
{
    command("say No I will not tell you about the secret door leading"
	    + " to the hole in floor is near here. So Hah!");
    command("emote struts about obviously pleased with herself.");
    return "";
}
