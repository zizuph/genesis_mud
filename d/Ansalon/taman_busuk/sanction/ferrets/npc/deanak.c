/*
 * deanak.c
 * Retired Dragonarmy Officer
 * Gives hints in the Ferret Name Quest. Also can buy items from him.
 * 
 * Ares, July 2004
 *
 */

#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <money.h>
#include "/d/Krynn/common/defs.h"
#include "../defs.h"

/*
 * Grabbed this from kalaman's pigeon seller, changed everything
 * to ferrets. 
 */

inherit M_FILE
inherit "/d/Ansalon/common/cheater";
inherit "/d/Krynn/std/equip.c";

object helmet, leggings, shield, shortsword, uniform;

void
create_krynn_monster()
{
    set_name("deanak");
    set_race_name("human");
    set_living_name("deanak");
    set_title("Jonikus, the Retired Dragonarmy Officer");
    set_adj("dirty");
    add_adj("odd-smelling");
    set_gender(G_MALE);
    set_long("This dirty odd-smelling man has set up a shack here "+
    "in Sanction after he retired from the Dragonarmy. Once a famous "+
    "officer, he now spends his life breeding, cooking and selling ferrets. \n");
    set_stats(({120,120,120,70,70,100}));
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_UNARM_COMBAT, 90);
    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 90);

    set_all_hitloc_unarmed(10);
    set_act_time(9);
    add_act("say Ferrets don't bite, they're just happy to see you.");
    add_act("emote grabs a toothpick from the jar and picks some dried "+
    "ferret meat out of his teeth.");
    add_act("emote hums a boring tune.");
    add_act("emote smiles as he remembers his former life in the Dragonarmies.");
    add_act("emote goes into the backroom for a moment then reappears "+
    "with a fresh plate of ferret meat for his customers.");
    add_act("emote grins to himself as he hears the flapping wings of a "+
    "nearby dragon outside.");
    add_act("say Want some tasty ferret meat?");
    add_act("say A drastic change in my life caused my retirement.");
    add_act("emote begins to clean the ferret cages, sweeping the "+
    "waste onto the floor.");
    add_act("say I have many pikes I need to get rid of, they're antique "+
    "pikes, worth a bundle!");
    add_act("say Hey, you look like the lonely type! A ferret could change "+
    "that you know!");
    add_act("say Ariakas will do great things, the Emperor is a smart man.");
    add_act("say I eat cooked ferret myself, but the draconians eat them "+
    "fur and all!");
    add_act("say That boy is obsessed with those dead ferts! I wish he'd "+
    "shut up about it and focus on his training.");
    add_act("shout Dante! You better have that backroom clean by supper!");
    
    add_ask(({"death certificate","death certificates","certificate"}),"say I used "+
    "to get those certificates after my poor Slick died, but I wasn't pulling "+
    "in enough coin to get one for every fert.",1);

    add_ask(" [about] 'price'", "say The sign has all the prices, "+
      "I'm tired of repeating myself!",1);
      
    add_ask(" [about] 'prices'", "say The sign has all the prices, "+
      "I'm tired of repeating myself!",1);
      
    add_ask(" [about] 'ferret'", "say Ferrets are wonderful "+
      "creatures. I've trained these not only to be your best friend, "+
      "but to also deliver messages to people it knows.",1);
      
    add_ask(" [about] 'ferrets'", "say Ferrets are wonderful "+
      "creatures. I've trained these not only to be your best friend, "+
      "but to also deliver messages to people it knows.",1);
      
    add_ask(" [about] 'ferts'", "say Ferts are ferrets, I guess I'm "+
       "the only one who calls them ferts anymore.",1);
      
    add_ask(" [about] 'pike'", "say They're pikes, good for impaling "+
       "things on, preferably your enemies.",1);

    add_ask(" [about] 'pikes'", "say They're pikes, good for impaling "+
       "things on, preferably your enemies.",1);
       
    add_ask(" [about] 'crosses'", "say Those were my favourite ferrets, "+
       "even if I can't remember their names. They're also the ones I "+
       "couldn't sell, nobody wanted them! May they rest in peace, those "+
       "furry little critters.",1);
       
    add_ask(({" [about] 'names'","name","ferret names"}), "say The names of "
       +"my dead ferrets? They're on their graves, or were. There might be "
	   +"some clues to names around the house. Oh, I remember I once tricked "
	   +"the barkeeper in town by tipping him with a ferret name tag. I bet "
	   +"he still hasn't figured it out!",1);
       
    add_ask(" [about] 'grandson'", "say His name is Dante and he's in the "+
       "backroom if you want to talk to him. The more you keep him occupied "+
       "the less I have to put up with him!",1);
       
    set_introduce(1);
    equip ("/d/Krynn/solamn/splains/obj/bhelmet.c");
    equip ("/d/Krynn/solamn/splains/obj/bleggings.c");
    equip ("/d/Krynn/solamn/splains/obj/bshield.c");
    equip ("/d/Krynn/solamn/splains/obj/bshortsword.c");
    equip (OBJ_DIR + "uniform");

}


void
init_living()
{
    ::init_living();
    ADA("buy");
}

buy(str)
{
    object ferret,who;
    NF("Buy what did you say?\n");
    if(!str  || (str != "ferret"))
        return 0;

    if (check_cheater(TP, TO))
        return 1;
    NF("The man says: This is my way of making a living here! "+
    "Go earn enough money and come back when you have it! \n");
    if(!MONEY_ADD(TP, -99))
        return 0;


    write("You pay the man, and he gets a ferret from one of the cages "+
    "and hands it to you.\n");
    say(QCTNAME(TP) + " buys a cute pet ferret. \n");

    who = TP;
    ferret = clone_object(OBJ_DIR + "ferret");
    ferret->set_owner(who);
    if (ferret->move(who) != 0)
    {
        write("Noticing that you are too burdened to carry the ferret, "+
        "the man places the critter on the ground before you. \n");
        say("The man places a ferret on the ground before " + QCTNAME(TP) +
".\n");
        /* ferret?? */
        ferret->move(environment(who));
    }
 
    /*
    ferret->move(who);
    */
    return 1;

}
