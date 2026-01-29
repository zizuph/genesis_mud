/*
 * /w/mirandus/ideas/dewargully/npc/dewar.c
 *
 * Dewar Dwarf for Newbie zone in Krynn
 * Coded by Mirandus with significant help from Leia
 * Help from Mortis with the armament destruction code.
 */

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <money.h>
#include <stdproperties.h>
#include <money.h>
#include "../local.h"
inherit M_FILE

#define AXE WEP+"dewarthanewep"
#define SHIRT ARM+"dewarthane1"
#define PANTS ARM+"dewarthane2"
#define PURSE "/d/Krynn/solamn/pal_gully/purse"
#define COINS MONEY_MAKE_GC(2 + random(6))
#define S_COINS MONEY_MAKE_SC(1 + random(12))

#define TYPE ({"forlorn", "depressed", "dour", "lithe", "grim", "ghastly"})
#define PHYS ({"tiny", "dimunative", "menacing", "gangly","disjointed", "venomous"})
#define EYES ({"bloodthirsty", "black", "grey", "piercing", "yellow", "bloodshot"})
#define FACE ({"stone-faced", "calculating", "bearded", "handsome"})
#define SKIN ({"dark", "pale", "smooth", "pocked", "blemished", "scarred"})
#define HAIR ({"grey", "black", "blood-red", "white", "brown", "blonde", "dirty blonde"})
#define HAIR2 ({"smooth", "greasy", "spiked", "messy", "mohawked", "clean", "slicked"})

object shirt,pants,axe,purse,gold_coins;

int x = 0;
string hishers = "";
string heshe = "";
string himher = "";
string CAPheshe = "";
string gen_type = "";

/*
 * Function name: determine_sex()
 * Description  : Randomly selects the sex of the NPC and sets pronouns.
 */
void determine_sex()
{
        switch(random(2))
        {
                case 0:  set_gender(G_MALE);
                         hishers = "his";
                         heshe = "he";
                         himher = "him";
                         CAPheshe = "He";
                         gen_type = "male";
                         x = 0;
                         break;
                case 1:  set_gender(G_FEMALE);
                         hishers = "her";
                         heshe = "she";
                         himher = "her";
                         CAPheshe = "She";
                         gen_type = "female";
                         x = 1;
                         break;
                default: set_gender(G_NEUTER);
                         break;
        }
}

/*
 * Function name: create_krynn_monster()
 * Description  : Randomly selects monster type and sets the descriptors and
 *                stats for the monster
 */
nomask void create_krynn_monster()
{
        determine_sex();
        string type, phys, eyes, skin, face, hair, hair2;
        int i;

        seteuid(getuid());

        type = one_of_list(TYPE);
        phys = one_of_list(PHYS);
        eyes = one_of_list(EYES);
        skin = one_of_list(SKIN);
        face = one_of_list(FACE);
        hair = one_of_list(HAIR);
        hair2 = one_of_list(HAIR2);

        string npc_name = "dewar";

        add_adj(type);
        add_adj(phys);
        //add_prop(LIVE_I_NEVERKNOWN, 1);
                
        set_race_name("dwarf");
        set_name("Dvordon");
        set_title("the Thane of the Palanthas Dewar Dwarves");
        add_name("dwarf");
        add_name("dewar");
        add_name("thane");
        add_name("dvordon");
        switch(hishers)
        {
                case "his":  set_gender(G_MALE);
                         hishers = "his";
                         heshe = "he";
                         himher = "him";
                         CAPheshe = "He";
                         x = 0;
                         break;
                case "her":  set_gender(G_FEMALE);
                         hishers = "her";
                         heshe = "she";
                         himher = "her";
                         CAPheshe = "She";
                         x = 1;
                         break;
                default: break;
        }
        add_name(npc_name);

        set_short(type + " " + phys + " " +gen_type+ " dewar thane");
        set_pshort(type + " " + phys + " " +gen_type+ " dewar thane");
        set_long("This "+type+" "+phys+" dewar dwarf is most angry of all. "
        +CAPheshe+" "+eyes+" eyes stare directly at you with malicious "
        +"intent. "+CAPheshe+" is the leader of the Dewar Dwarves in these "
        +"caverns and the insanity in "+hishers+" eyes is visible. "
        +""+CAPheshe+" looks tough and likely more difficult to slay than "
        +"the others in this cavern.\n");

        add_prop(CONT_I_WEIGHT, 11100);
        add_prop(CONT_I_HEIGHT, 180);
		add_prop(NPC_I_NO_FEAR, 1);
		add_prop(NPC_I_NO_RUN_AWAY, 1);
        
        for(i = 0; i < 6; i++)
                set_base_stat(i, 30 + random(20));

        set_hitloc_unarmed(1, 10, 15, "head");
        set_hitloc_unarmed(2, 15, 10, "right arm");
        set_hitloc_unarmed(3, 15, 10, "left arm");
        set_hitloc_unarmed(4, 25, 45, "body");
        set_hitloc_unarmed(5, 20, 20, "legs");

        set_skill(SS_WEP_AXE,25);
        set_skill(SS_DEFENCE,15);
        set_skill(SS_AWARENESS,20);
        set_alignment(-300);
        set_introduce(1);
        
        set_act_time(15);
        add_act("say Darn Gully Dwarves.");
        add_act("say I'm gonna kill all those Gully Dwarves.");
        add_act("say I hate Gully Dwarves. Always trying to live!");
        add_act("emote curses the Gully Dwarves for taking "
        +hishers+" refuse dump");
        add_act("emote scowls.");
        add_act("say Where do the Gully Dwarves expect us to put our trash?");
        add_ask(({" [about] 'quest'","quest", "quests", "task", 
        "tasks", "help"}), "say What do I look like to you? Some kind of "
        +"helpful ninny? Get out of here before I kill you.\n",1);
        add_ask(({" [about] 'aghar'","gullies", "gully", 
        "gully dwarves"}), "say Those damn Aghar moved into our refuse "
        +"dump. That mine is ours and they ain't gonna take it from "
        +"us. I'm gonna kill every last one of em!\n",1);
        
        set_alarm(1.0,0.0,"arm_me");
}

/*
 * Function name: arm_me()
 * Description  : Based on monster type, loads the weapons and armours.
 *                
 */
void
arm_me()
{
    
    seteuid(getuid(this_object()));
    shirt = clone_object(SHIRT);
    pants = clone_object(PANTS);
    axe = clone_object(AXE);
    purse = clone_object(PURSE);
    shirt->move(this_object());
    pants->move(this_object());
    purse->move(this_object());
    command("wear all");
    axe->move(this_object());
    command("wield all");

    COINS->move(purse, 1);
    S_COINS->move(purse, 1);  
}

/*
 * Function name: attacked_by()
 * String       : the object attacking (ob)
 * Description  : Determines who is attacking and gives a response.
 *                
 */
void
attacked_by(object ob)
{
    object *arr;
    int i;

    ::attacked_by(ob);

    command("say You're helping those Gullies? I'll Kill You!");

    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
    arr[i]->notify_ob_attacked_me(this_object(), ob);  

}

/* Function:         do_die()
 * What's it do:     Ordinarily initiates death in slain monster.
 * What's it do now: Destroys some to all gold and armaments with a higher
 *                   chance the bigger the player. */
 
void
do_die(object killer)
{
    int goldfactor = 100;
    int kstat = killer->query_average_stat();
    string golddamage = "";
    
	if (kstat > 85)
    {
        golddamage = "Your killing blow destroys your foe's leather purse, "
            + "sending its contents skittering away.";
        purse->remove_object();
    }
    
    if (golddamage != "" && present(killer, E(TO)))
    {
        killer->catch_msg(golddamage + "\n");
    } 
  
    ::do_die(killer);
}

void init_living()
{
        ::init_living();
}
