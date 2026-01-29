/*
 * /w/mirandus/ideas/dewargully/npc/agharhighbulp.c
 *
 * Highbulp of the Aghar Dwarves for Newbie zone in Krynn
 * Coded by Leia, modified from Dewar Dwarf by Mirandus
 * Updated to allow introduction
 * Help from Mortis with the armament destruction code.
 */
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <money.h>
#include <stdproperties.h>
#include "../local.h"
inherit M_FILE

#define CLUB WEP+"highbulpwep"
#define SHIRT ARM+"highbulp1"
#define PANTS ARM+"highbulp2"

#define TYPE ({"scared", "gullible", "slow", "dimwitted", "smiling", "careful"})
#define PHYS ({"small", "sickly", "chubby", "big-nosed","whiskered", "stubby"})
#define EYES ({"innocent", "blue", "green", "brown", "big", "curious"})
#define FACE ({"puffy", "red", "long", "tired"})
#define SKIN ({"soft", "beige", "fair", "dirty", "unwashed", "dry"})
#define HAIR ({"grey", "black", "silver", "white", "brown", "blonde", \
"dirty blonde"})
#define HAIR2 ({"disheveled", "matted", "poorly cut", "filthy", "grimy", \
"bristly", "frizzy"})

object shirt,pants,club;

int x = 0;
string hishers = "";
string heshe = "";
string himher = "";
string CAPheshe = "";
string CAPhisher = "";

/*
 * Function name: create_krynn_monster()
 * Description  : Randomly selects monster type and sets the descriptors and
 *                stats for the monster
 */
nomask void create_krynn_monster()
{
        set_gender(G_FEMALE);
        hishers = "her";
        heshe = "she";
        himher = "her";
        CAPheshe = "She";
        CAPhisher = "Her";
        x = 1;
    
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

        string npc_name = "aghar";

        add_adj(type);
        add_adj(phys);
                        
        set_race_name("dwarf");
        set_name("Dupu");
        set_title("the Highbulp of the Palanthas Aghar Dwarves");
        add_name("dwarf");
        add_name("aghar");
        add_name("highbulp");
        add_name("dupu");
        add_name(npc_name);

        set_short(type + " " + phys + " female aghar highbulp");
        set_pshort(type + " " + phys + " female aghar highbulp");
        set_long("This "+type+" "+phys+" aghar dwarf appears to be less "
        +"nervous than most. "+CAPhisher+" "+eyes+" eyes look you over curiously. "
        +CAPheshe+" is the leader of the Aghar Dwarves in these caverns "
        +"and "+heshe+" does "+hishers+" best to keep the aghar living. "
        +CAPheshe+" looks a bit tougher than the other aghar, and is "
        +"likely to be no pushover.\n");

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

        set_skill(SS_WEP_CLUB,25);
        set_skill(SS_DEFENCE,15);
        set_skill(SS_AWARENESS,20);
        set_alignment(100);
        set_introduce(1);
        
        set_act_time(10);
        add_act("say Why dewar not leave us alone?");
        add_act("say Aghar just want to live.");
        add_act("say We not hate Dewar. Why they hate us?");
        add_act("emote peers nervously around, looking for invaders.");
        add_act("emote gulps.");
        add_act("say Dewar throw out all the best things.");
        add_ask(({" [about] 'quest'","quest", "quests", "task", 
        "tasks", "help"}), "say What that? Me not know.\n",1);
        add_ask(({" [about] 'dewar'","dark dwarves", 
        "darks"}), "say Dewar not like Aghar, but we not know how come. "
         +"We find nice caverns empty and we move in. We happy here. "
         +"Much nice stuff.\n",1);
        
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
    club = clone_object(CLUB);
    shirt->move(this_object());
    pants->move(this_object());
    command("wear all");
    club->move(this_object());
    command("wield all");
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

    command("say No! No help Dewar! Let Aghar live!");

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
        goldfactor = 65;
        golddamage = "Your killing blow destroys your foe sending bits "
            + "of bone and metal flying away.";
    }
    if (kstat > 100)
    {
        goldfactor = 45;
        golddamage = "Your killing blow massacres your foe spraying the "
            + "area with bits of metal and blood.";
    }
    if (kstat > 115)
    {
        goldfactor = 20;
        golddamage = "Your mighty killing blow overpowers the dwarf's "
            + "body destroying it along with most of "+hishers+" belongings "
            + "in a haze of metal and blood.";
    }
    if (kstat > 130)
    {
        goldfactor = 0;
        golddamage = "Your massive killing blow turns the dwarf into red "
            + "mist along with nearly all of its belongings.";
    }

    // Reduce armaments dropped by goldfactor as a % of destruction
    if (present(shirt, TO))
    {
        if (random(109) >= (goldfactor + 10))
        {
            shirt->remove_object();
        }
    }
    if (present(club, TO))
    {
        if (random(109) >= (goldfactor + 10))
        {
            club->remove_object();
        }
    }
    if (present(pants, TO))
    {
        if (random(109) >= (goldfactor + 10))
        {
            pants->remove_object();
        }
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