inherit "/d/Khalakhor/std/npc/human";
inherit "/d/Shire/common/auto_teaming";

#include <const.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <wa_types.h>
#include <formulas.h>
#include <tasks.h>
#include "/d/Gondor/defs.h"

/*#define ADJ ({"muscular", "thundering", "elite", "savage", "smelly","hairy","rough", "experienced", "bitter", "handsome", "ugly", "cruel"})
#define ADJ2 ({"thick-armed", "hawk-eyed","focused","red-haired", "chaos-seeking","green-eyed","well-trained"})*/

/* The define COOLDOWN determines how often it can occur, in seconds */
#define COOLDOWN    15

/* This integer is set so the time of the last ability is stored somewhere */
int cooldown = 0;

string physlook();
string emotelook();
string guardname();
 
 


void
create_khalakhor_human()
{
    /*string adj = one_of_list(ADJ);
    string adj2 = one_of_list(ADJ2);*/
	
    set_name(({guardname()}));
    add_name(({"guard"}));
    set_adj(({emotelook(),physlook()}));
    set_long("This is a tough-looking barbaric guard, who stands as a"
        +"silent sentry, equipped with the training and experience "
        +"to convey his feeling of chaos and bloodthirst to his unlucky "
        +"foes. He looks absolutely barbaric, and doesn't seem to want "
        +"anything more than to personally bash your head in. He is wearing "
        +"the read and black colours of the clan Baran, and his kilt  "
        +"displays his rank being that of a footman of the clan.\n");
			
    set_gender(G_MALE);
    set_stats(({ 100, 100, 100 + random(10), 100, 100, 200 }));
    
    set_pick_up_team(({"guard"}));
    
    set_alignment(-500);

    set_skill(SS_WEP_SWORD, 70);
    set_skill(SS_WEP_CLUB, 70);
    set_skill(SS_WEP_POLEARM, 70);
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 60);
    
    // Emotes with 50sec interval
    set_act_time(50);
    add_act("emote dutifully cleans his armours, removing "
        +"blood and gore from sight and mind.");
    add_act("emote straightens up the room, fixing the "
        +"tent stakes, shields resting against the tent, "
        +"and other equipment that has fallen over recently.");
    add_act("emote adjusts his kilt, greaves, and bracers.");
    add_act("emote describes the rough life accompanying "
        +"the warriors of the clan Baran.");
    
    // Combat emotes with 8sec interval
    set_cact_time(8);
    add_cact("shout Annoying fiend! It's to the death if you're lucky weak-armed joke of a warrior!");
    add_cact("emote growls menacingly");
    add_cact("asay dark So you call yourself a warrior? I'll beat you until "
        +"you can't even see me beating you anymore!");
 
    
    add_prop(OBJ_I_RES_POISON, 10);
    add_prop(OBJ_I_RES_FIRE,  -10);
    
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    
    equip("/w/stark/celtcamp/kguard_items/Csword");
    equip("/w/stark/celtcamp/kguard_items/Cshield");
    equip("/w/stark/celtcamp/kguard_items/Chelm");
    equip("/w/stark/celtcamp/kguard_items/Cgreaves");
    equip("/w/stark/celtcamp/kguard_items/Ckilt");
    equip("/w/stark/celtcamp/kguard_items/Cbracers");
	
}

int
special_attack(object enemy)
{
    int pen, task;
    object *shield;
    mixed hitres;
    
    /* This is somewhat of a difficult function, takes some practics to use.
     * What this does is, it filters all the items in query_armour(-1), and
     * the operator checks if &->query_at() == A_SHIELD
     * If any of the items are any shields in the armour list, they are stored
     * in the 'object *shield' array.
     */
    shield = filter(query_armour(-1), &operator(==)(, A_SHIELD)
             @ &->query_at());

    
    /* Checks if the shield array has any shields in it. */
    if (!sizeof(shield))
        return 0;
    
    /* Ive added a cooldown here, current time - old time < COOLDOWN */
    if ((time() - cooldown) < COOLDOWN)
        return 0;
    
    /* Resolve_task checks values against target values and determines if
     * the action was a success based on the TASK_. There are several TASK
     * values, TASK_ROUTINE, TASK_DIFFICULT and so on..
     
     */
    if (task = resolve_task(TASK_ROUTINE, ({SS_DEFENCE, TS_DEX, TS_STR}),
                                   enemy, ({SS_DEFENCE, TS_DEX, TS_WIS})))
    {
        /* This sets the time from when the cooldown starts counting */
        cooldown = time();
        
        /* If task is less than 1, it means the slam has failed */
        if (task < 1)
        {
            write("The shield slam failed.\n");
            return 1;
        }
        
        /* Damage is now based on the shields armour value and the guards
         * defence skill if its low, you can change it, or multiply it :)
         * (figured a shield slam might aswell go on defence skill as
         *  its required skill, as there is no proper shield skill)
         */
        pen = F_PENMOD(shield[0]->query_ac(), enemy->query_skill(SS_DEFENCE));
        
        /* The hit results is stored in hitres: 
         * hitres[0] - 0-100, incurred damage as percentage of
         *             victim HP, or -1 = dodge, -2 = parry.
         * hitres[1] - description of the location that was hit.
         * hitres[2] - randomized value of the weapon penetration
         * hitres[3] - dealt damage in hitpoints
         */
        hitres = enemy->hit_me(pen, W_BLUDGEON, this_object(), -1);
    
        /* I dont think hit_me is be able to return 0 damage, but as coders
         * we should always prepare for things we dont know, so lets
         * stop the hit here if it returns 0.
         */
        if (!hitres[3])
            return 0;

        /*
         * Switch is a good function that switches between a value,
         * instead of using several if (a = 1), if (a = 2), you can
         * use switch(a) { case 1: write("hmm\n"); break; }}
         *
         * (I use this function to check how many percent of the enemy's 
         *  total health the attack has caused.)
         */
        switch(enemy->query_max_hp() / hitres[3])
        {
            case 0..1:
                write("ALL HIS HEALTH!\n");
                    break;
            case 2..3:
                write("HALF to ONE THIRD HIS HEALTH!\n");
                    break;
            case 4..5:
                write("21-17% SOO MUCH DAMAGE!!\n");
                    break;
            case 6..9:
                write("16-11% of his total health, still so much!\n");
                    break;
            case 10..20:
                write("10-5% of his total health, still alot!\n");
                    break;
            case 21..50:
                write("5-2% of his total health, getting closer to normal!\n");
                    break;
            case 51..100:
                write("2-1% of his total health, closer to normal!\n");
                    break;
            
            /* If none of the above, return default */
            default:
                write("From here on its below 1%! It hit " + hitres[1] + "\n");
                    break;
        }

        
    /********* Should remove this, just an example **********/
        write("Damage done: " + hitres[3] + " to " + hitres[1] + "\n");
        
        if (hitres[1] == "head")
        {
            /* Hits the head, steal mana? Theme is up to Cherek to approve */
            enemy->add_mana(-hitres[3]);
            enemy->catch_msg("You feel mentally disoriented from the hit " +
            "to your head.\n");
        }
        
        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(this_object());
        }

        return 1;
    }

    /* I hope this helped in some way. */
    return 0;
}

string
guardname()
{
    string *guardname;
    guardname = ({"gillebeart", "raibeart", "ailean", "padruig", "dohmnull",
        "prainnseas", "tomag", "martainn", "ringean", "sachairi", "deistean",
        "bearnard", "frang", "goiridh", "gilleasbuig", "darren", "raghnall",
        "labhrann", "torcadall", "benneit", "micheil", "diarmad", "daidh",
        "comhnall","simidh","colum", "griogair", "oisean", "cathal", "cadwgan",
        "sandaidh", "dremidydd", "brys", "cadman", "maelog", "ifan", "seth",
        "nest", "treharne", "mabbet", "hewitt", "owens", "powles", "roderick",
        "brickell", "pedr", "dyfed", "dacus", "maddix", "moor", "Alwyn", "luc",
        "peairs", "badham", "Beddoe", "seith", "gwent", "huarwar","glas", "morcan",
        "tristram", "geddings", "harry", "uilliam", "matho", "fearadhach",
        "dualtach"});
    return guardname[random(sizeof(guardname))];
}

string
physlook()
{
    string *physlooks;
    physlooks = ({"tall", "blue-eyed", "grey-eyed", "brown-eyed", "imposing",
        "black-haired", "brown-haired", "grey-haired", "green-eyed", "bald",
        "long-legged", "lithe", "muscular", "slender", "strong", "massive",
        "burly", "bearded", "clean-shaven", "strong-armed", "barrel-chested", 
        "lean", "large", "thick-armed", "sturdy"});
    return physlooks[random(sizeof(physlooks))];
}

string
emotelook()
{
    string *emotelooks;
    emotelooks = ({"stern", "fierce", "stoic", "malevolent", "untrustworthy",
        "articulate", "frowning", "grim", "experienced", "deadly", "dangerous",
        "wary", "alert", "rash", "silent", "watchful", "fierce",
        "formidable", "unsympathetic", "greedy", "arrogant", "unreliable",
        "handsome", "cruel", "ugly"});
    return emotelooks[random(sizeof(emotelooks))];
}

void
init_living()
{
    init_team_pickup();
    ::init_living();
}

void
add_introduced(string str)
{
    if (!interactive(TP) || TP->query_met(query_name()))
        return;

    command("introduce me to " + TP->query_real_name() + "");
}
