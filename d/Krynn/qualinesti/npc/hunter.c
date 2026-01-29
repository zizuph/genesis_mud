/* hunter.c
 * Jakey, a half-elf hunter.
 *
 * Blizzard  2/05/2003
 */

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>
#include "/d/Krynn/common/defs.h"
#include "../local.h"

inherit  M_FILE
inherit  "/d/Krynn/std/equip";

string   def_answer();

void
create_krynn_monster()
{
    set_name("jakey");
    add_name("hunter");
    set_living_name("jakey");
    set_race_name("half-elf");
    set_title("the Hunter");
    set_adj("lean");
    add_adj("weather-beaten");
    set_long("This weather-beaten half-elf has blond hair and piercing " +
       "green eyes. His skin is tanned and rough, and covered in many " +
       "small scars. He appears experienced and when he looks you up " +
       "and down, you get the impression that he is evaluating your " +
       "abilities.\n");
    
    set_gender(G_MALE);
    set_introduce(0);
    
    set_stats( ({ 80, 100, 100, 70, 70, 100 }) );
    
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_WEIGHT, 80000);
    add_prop(CONT_I_HEIGHT, 180);
    
    set_skill(SS_DEFENCE, 70);
    set_skill(SS_PARRY, 60);
    set_skill(SS_WEP_POLEARM, 70);
    set_skill(SS_UNARM_COMBAT, 50);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_BLIND_COMBAT, 30);
         
    set_act_time(4);
    
    add_act("emote looks around searchingly.");
    add_act("emote drinks some wine.");
    add_act("emote peers in your direction.");
    add_act("say Those wild dogs are nasty, but their pelts make " +
        "good cloaks.");
    add_act("say Would you believe? I almost caught a kender in a snare " +
        "last time!");
    add_act("cough");
    add_act("say There are not many animals left to hunt in this area. " +
        "I should move south, closer to Qualinesti.");
    add_act("say Because of all those draconians I can't hunt much here.");
    add_act("say I think the elves are a bit afraid of the dragonarmy.");
    add_act("say Be careful if you approach Qualinesti. The elves " +
        "do not like intruders in their forest.");
    
    set_cact_time(4);
    add_cact("glare");
    add_cact("say I usually hunt wild animals, but I see I have no choice!");
    add_cact("say Stop that and you will live.");
    
    set_knight_prestige(-5);
    set_alignment(200);
    
    set_default_answer(VBFC_ME("def_answer"));
    add_ask(({ "dog", "dogs" }), 
        "say You mean the wild dogs? Those elven hounds are nasty to kill, " +
        "but their pelts make excellent cloaks.", 1);
    add_ask(({ "elf", "elves" }),
        "say Well, it seems they are afraid of draconians. I see many of " +
        "them sneaking through the forests recently. They seem to be " +
        "watching every road.", 1); 
    add_ask(({ "kender", "kenders" }),
        "say Eh, what can I say. I just wish you not to meet one on your " +
        "path. Otherwise, you may find your pouches empty in a blink " +
        "of an eye.", 1);
    add_ask(({ "draconians", "draconian", "dragonarmy", "dragonarmies" }),
        "say Curse them! Because of them, most animals left the local " +
        "forests!", 1);
    add_ask(({ "forest", "forests" }),
        "say What forest? If you are planning a hunt you should try " +
        "Qualinesti.", 1);
    add_ask(({ "Qualinesti", "qualinesti" }),
        "say Well, that's a good place for hunting. Unless you meet an elf, " +
        "that decides to hunt you!", 1);
    add_ask(({ "Qualinost", "qualinost" }),
        "say I hear it's a beautiful city. I have not bad a chance to " +
        "see it, though.", 1);
    add_ask(({ "animal", "animals", "hunting", "hunt" }),
        "say It's nearly impossible to find wild animals here nowdays! " +
        "If you are going for a hunt, better visit Qualinesti.", 1);    

    seteuid(getuid(TO));
    equip(({ WEP + "spear", ARM + "elven_boots", ARM + "tunic" }));
}

string
def_answer()
{
    switch ( random(3) )
    {
    case 0:
        command("say What do you need? Let me rest, please. I have just " +
            "returned from the hunt in Qualinesti.");
    break;
    case 1:
        command("say What do you want from me? Speak up or let me rest!");
    break;
    case 2:
        command("say What?");
    break;
    }
    
    return "";
}

