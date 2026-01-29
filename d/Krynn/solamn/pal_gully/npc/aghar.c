/*
 * /w/mirandus/ideas/dewargully/npc/aghar.c
 *
 * Aghar (Gully) Dwarf for Newbie zone in Krynn
 * Coded by Leia, Modified from Mirandus' Dewar File
 * Help from Mortis with the armament destruction code.
 *
 * Removed the armament destruction... wasn't necessary,
 * added the possibility of a low value gem that gets 'lost'
 * if people over certain stat average kill the target.
 */

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <money.h>
#include <stdproperties.h>
#include "../local.h"
#include "/d/Genesis/gems/gem.h"
inherit M_FILE

 
#define CLUB WEP+"agharwep"
#define SHIRT ARM+"aghararmour"
#define PANTS ARM+"aghararmour2"
#define GEM RANDOM_GEM(GEM_EXTREMELY_COMMON)


#define TYPE ({"scared", "gullible", "slow", "dimwitted", "smiling", \
"careful"})
#define PHYS ({"small", "sickly", "chubby", "big-nosed","whiskered", "stubby"})
#define EYES ({"innocent", "blue", "green", "brown", "big", "curious"})
#define FACE ({"puffy", "red", "long", "tired"})
#define SKIN ({"soft", "beige", "fair", "dirty", "unwashed", "dry"})
#define HAIR ({"grey", "black", "silver", "white", "brown", "blonde", \
"dirty blonde"})
#define HAIR2 ({"disheveled", "matted", "poorly cut", "filthy", "grimy", \
"bristly", "frizzy"})

object shirt,pants,club, gem;

int x = 0;
string hishers = "";
string heshe = "";
string himher = "";
string CAPheshe = "";
string CAPhisher = "";

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
                         CAPhisher = "His";
                         x = 0;
                         break;
                case 1:  set_gender(G_FEMALE);
                         hishers = "her";
                         heshe = "she";
                         himher = "her";
                         CAPheshe = "She";
                         CAPhisher = "Her";
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
        string type, phys, eyes, skin, face, hair, hair2, gen_type;
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
        add_prop(LIVE_I_NEVERKNOWN, 1);
		add_prop(NPC_I_NO_FEAR, 1);
		add_prop(NPC_I_NO_RUN_AWAY, 1);
                
        set_race_name("dwarf");
        add_name("aghar");
        switch(hishers)
        {
                case "his":  set_gender(G_MALE);
                         hishers = "his";
                         heshe = "he";
                         himher = "him";
                         CAPheshe = "He";
                         CAPhisher = "His";
                         gen_type = "male";
                         x = 0;
                         break;
                case "her":  set_gender(G_FEMALE);
                         hishers = "her";
                         heshe = "she";
                         himher = "her";
                         CAPheshe = "She";
                         CAPhisher = "Her";
                         gen_type = "female";
                         x = 1;
                         break;
                default: break;
        }
        add_name(npc_name);

        set_short(type + " " + phys + " " +gen_type+ " aghar");
        set_pshort(type + " " + phys + " " +gen_type+ " aghar");
        set_long("This "+type+" "+phys+" Aghar dwarf seems content "
        +"just surviving in these caverns. "+CAPhisher+" "+eyes+" eyes glance "
        + "nervously about the room looking out for any invading dewar. "
        +""+CAPheshe+" is one of the Aghar who have moved into these caverns "
        + "after they were abandoned. Forced to live in places no other "
        +"dwarf would live, they seem happy to be here. "+CAPhisher+" "+hair
        +" hair is "+hair2+" and "+hishers+" "+face+" face shows "
        +""+hishers+" nervous and innocent nature.\n");

        add_prop(CONT_I_WEIGHT, 11100);
        add_prop(CONT_I_HEIGHT, 180);
        
        for(i = 0; i < 6; i++)
                set_base_stat(i, 20 + random(20));

        set_hitloc_unarmed(1, 10, 15, "head");
        set_hitloc_unarmed(2, 15, 10, "right arm");
        set_hitloc_unarmed(3, 15, 10, "left arm");
        set_hitloc_unarmed(4, 25, 45, "body");
        set_hitloc_unarmed(5, 20, 20, "legs");

        set_skill(SS_WEP_CLUB,15);
        set_skill(SS_DEFENCE,15);
        set_skill(SS_AWARENESS,20);
        set_alignment(100);

        set_act_time(15);
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

    gem = GEM;
    gem->move(this_object());
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
    int kstat = killer->query_average_stat();
    
	if ((kstat > 85) && objectp(gem))
    {
        gem->remove_object();
        killer->catch_msg("Something shiny drops from the corpse of your foe " +
           "and rolls away into the darkness.\n");
    }
    
    ::do_die(killer);
}

void init_living()
{
        ::init_living();
}