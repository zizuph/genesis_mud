
// Albus' (pale near-albino goblinoid creatures in the underdark)
// creator(s): Casca, 11/26/99
// purpose:    Populate the underdark
// note:       
// bug(s):     
// to-do: 
   
inherit "/d/Avenir/inherit/monster.c";
#include "/d/Avenir/common/common.h"
#include "/d/Genesis/gems/gem.h"
#include </sys/ss_types.h>
#include <cmdparse.h>

#define FIXEUID         setuid(); seteuid(getuid())
#define QUICK           50
#define ABILITY        80

string *randadjl;
string *randadjs;
string albus_long();
void equip_me();
void albi_props();

void
create_monster()
{
    if(!IS_CLONE)
       return;

    randadjl = ({"lumpy", "ugly", "large", "gangly", "pink-eyed",
                 "short", "stumpy", "long-haired", "slender", 
                 "bald", "short-legged", "white-haired",
                 "long-nosed", "pale-skinned", "clear-eyed",
                 "snowy-haired", "squat", "graceless", "warty",
                 "scarred", "one-eyed", "freakish"});

    randadjs = ({"angry", "simple", "grinning", "fierce", "calm", 
                 "unhappy", "queer", "sad", "mean", "cold",
                 "frightened", "fretful", "moping", "sulky"});

    ::create_monster();

    set_name("albus");
    add_name("avenir_albi_leader");
    set_race_name("albus");
    set_gender(G_MALE);

    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    set_aggressive(1);

    set_adj(randadjl[random(sizeof(randadjl))]);
    add_adj(randadjs[random(sizeof(randadjs))]);

    set_long(albus_long);

    set_stats(({ 80+random(20), 90+random(20), 80+random(30),
                 50+random(10), 50+random(10), 80+random(30) }));
 

    NEVERKNOWN;
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_SEE_DARK, ABILITY);
    add_prop(LIVE_I_QUICKNESS, QUICK);

    set_skill(SS_BLIND_COMBAT, ABILITY );
    set_skill(SS_WEP_CLUB, 75);
    set_skill(SS_DEFENCE, 40 + random (30));
    set_skill(SS_AWARENESS, 50);
    set_skill(SS_WEP_AXE, 75);        

    /* rest combat prop values */
    albi_props();

        set_act_time(8 + random (6));
    add_act("assist");
    add_act("@@light_cry@@");
    add_act("@@check_for_fights@@");
    add_act("light fire");
    add_act("emote stirs the contents of a pot over a fire.");
    add_act("emote paces back and forth.");
    add_act("peer curiously goblin");
    add_act("emote stares into the fire.");
    add_act("whisper avenir_albus_id Whos the ugly one?");
    add_act("say Why you here?");
    add_act("say Go away.");
    add_act("twirl club");
    add_act("swing axe");
    add_act("squint");

        set_cact_time(9 + random (20));
    add_cact("assist");
    add_cact("snicker");
    add_cact("spit enemy");
    add_cact("scream");
    add_cact("cackle .");
    add_cact("glare angr enemy"); 
    add_cact("say The Odd one will destroy you!");
    add_cact("twirl club");
    add_cact("swing axe");

    add_ask(({"odd-one","Odd_one","oddone","Oddone","odd one","Odd one",
        "leader","massive red-eyed albus", "massive albus"}),
        "say He is our leader, he make us able to fight back against "+
        "the large ones.", 1);
    add_ask(({"cavern", "home"}),
        "say The Odd one find this place for us and make it our home "+
        "he teach us how to live better.", 1);
    add_ask(({"trash","tunnel","junk"}),
        "say Our leader tell us to put all the trash away from "+
        "our home. But its to dangerous to go very far away.", 1);
    add_ask(({"miners","trolls","foreman","foremen","shadow-elves"}),
        "say We use things they no longer want, good tools for "+
        "for breaking rocks and food they dont need.", 1);

}

string
albus_long()
{
    string  str;

    /* Adding the adjectives to the long */
    str =  capitalize(this_object()->query_pronoun()) +" is "+ 
           LANG_ADDART(implode(query_adjs(), " ")) +" "+
           query_race_name()+".\n";

    str += "He is a bizarre little creature.\nWhile he looks "+
           "something like a goblin, his skin is a very pale "+
           "white tinged with a hint of pink.\n"+
           "Despite his small size, he appears to be rather "+
           "strong.\n"+
          "This fellow meets your eyes in a way the others "+
          "do not.\n";

    return str;
}

void
equip_me()
{
    object pickaxe, club, gem;
    int i;
    FIXEUID;

    gem = RANDOM_GEM_BY_RARITY(GEM_RARE);
    gem->move(this_object());              
    gem->set_heap_size(2);  

    i = random(10);
    if (i < 5)
    {
        club = clone_object(DARK + "obj/sclub");
        club->move(TO);
    }
    if (i > 5)
    {
        pickaxe = clone_object(DARK + "obj/t_pickaxe");
        pickaxe->move(TO);                
    }

    command("wear all");
    command("wield all");
}

void
albi_props()
{
        /*Default combat-related prop values */
    if  (this_object()->query_prop(LIVE_I_SEE_INVIS))
        remove_prop(LIVE_I_SEE_INVIS);
    if (this_object()->query_prop(LIVE_I_QUICKNESS))
    {
         remove_prop(LIVE_I_QUICKNESS);
         add_prop(LIVE_I_QUICKNESS, QUICK);
    }
    if (this_object()->query_prop(LIVE_I_SEE_DARK))
    {
         remove_prop(LIVE_I_SEE_DARK);
         add_prop(LIVE_I_SEE_DARK, ABILITY);
    }
    if (this_object()->query_skill_extra(SS_BLIND_COMBAT))
        set_skill_extra(SS_BLIND_COMBAT, 0);      

}

void
check_for_fights()
{
    if (!objectp(query_attack()))
        albi_props();
}


/*
 * Function name:   light_cry
 * Description:     This function is called when the albi enter rooms
 *                  or meet other livings. It makes them panic and 
 *                  leave when the light is too bright.
 */
void
light_cry()
{
    int i;

    i = random(9);

    if (environment(this_object())->query_prop(OBJ_I_LIGHT) < 5)
        return;    

    switch (i)
    {
        case 0: command("emote covers his eyes with one arm."); 
                break;
        case 1: command("cries in pain from the brightness of the light.");
                break;
        case 2: command("drop weapon");
                break;
        case 3: command("shout They bring Light! RUN!");
                break;
        case 4: command("say O most foul, the brightness! My eyes!");
                break;
        case 5: command("emote blinks eyes filled with tears at the "+
                "brightness of the light.");    
                break;
        case 6: command("say Another time, darkling.");
                break;
        case 7: command("emote appears blinded by the light.");           
                break;
        case 8: command("say You invade our home with your blinding "+
                "light!  I am no fool to stand and fight.");
                break;
    }
    run_away();
    run_away();      
}

/*
 * Function name:   light_special
 * Description:     This function is called in the special_attack.
 *                  It determines how the light-level of a room 
 *                  affects the combat abilities of the albi.
 * Arguments:       object victim: the victim of the special attack
 */
int
light_special(object victim)
{
    int l = (int)environment(this_object())->query_prop(OBJ_I_LIGHT);
    
    switch(l)
    {
        case -100..-2:
        {
            /* set to defaults */
            albi_props();
            /* It is nice and dark, give a bonus to blind fighting */
            set_skill_extra(SS_BLIND_COMBAT, ABILITY);
        }
        break;
        case -1..2:
        {
            /* set to defaults */
            albi_props();             
        }
        break;
        case 3..9:
        {
             /* It is too bright so I have a slowness penelty */      
             remove_prop(LIVE_I_QUICKNESS);
             add_prop(LIVE_I_QUICKNESS, QUICK * -1); 
            /* It is too bright so I am blinded */
             add_prop(LIVE_I_SEE_INVIS, -1);
            /* It is too bright, so my blind-fighting is affected */
             set_skill_extra(SS_BLIND_COMBAT, ABILITY * -1);
        }
        break; 
        case 10..100:
             /* It is way to bright and I am smart enought to run away */
             light_cry();
        break;
    }

    return 1;
}

/*
 * Function name:   light_target
 * Description:     This function is called in the special_attack.
 *                  It allows the albi to steal light sources and 
 *                  extringuish them.
 * Arguments:       object victim: the victim of the special attack
 */
void
light_target(object victim)
{
    object *all;
    int i, rnd;

    rnd = random(3);
    if (rnd == 0)
       return;

    all = all_inventory(victim);

    for (i=0; i<sizeof(all); i++) 
    {
        if (!function_exists("create_torch", all[i])) 
            continue;
        if (all[i]->query_prop(OBJ_I_HAS_FIRE)) 
        {
            victim->catch_msg(QCTNAME(this_object())+
                " darts under your guard. His blunt, powerful hands "+
                "reach frantically for your " + all[i]->short() + 
                " and rip it from your grasp.\n");
            tell_room(ENV(this_object()), QCTNAME(this_object())+
                " darts under "+ QCTNAME(victim) + "'s guard and "+
                 " steals "+ LANG_ASHORT(all[i]) +"!\n", victim);
            all[i]->move(this_object());
//            all[i]->do_extinguish();
            command("extinguish all");
            return;
        }
    }
}

       
void
force_assist()
{
    object *obs, albi;

    obs = FIND_STR_IN_OBJECT("avenir_albus_id", environment(this_object()));
    if (!sizeof(obs))
    {
        command("shout Come and fight! We're under attack!");
        return;
    }

    command("shout Stand and fight!");

    albi = obs[0];
    albi->command("assist");   
}  


/*
 * Function name: special_attack
 * Description:   Called from the external combat object's heart_beat
 *                routine. By redefining this, monsters can easily attack
 *                with spells or take special actions when engaged
 *                in combat.
 * Arguments:     victim (the one we are fighting right now)
 * Returns:       0 - if we want the round to continue
 *                1 - if we are done with this round
 * Note:          By always returning 1 the mobile is unable
 *                to do an ordinary attack.
 */
int
special_attack(object victim)
{
    if (ENV(victim) != ENV(TO) || victim->query_ghost())
    {
        TO->stop_fight(victim);
	return 1;
    }

    switch (random(5))
    {
        case 0: light_target(victim);
            return 1;        
        case 1: light_special(victim);
            return 1;
        case 2: 
        {
            command("emote kicks dirt into the campfire.");
            command("extinguish all");
             return 1;
        }
        case 3:  force_assist();
            return 1;
        default: 
    }
    return 0;
}

/*
 * Function name:   add_introduced
 * Description:     Add the name of a living who has introduced herself to us
 * Arguments:       str: Name of the introduced living
 */
public void
add_introduced(string name)
{
    command("shrug");
}

/*
 * Function name: enter_env
 * Description  : This function is called whenever this object enters a new
 *                environment. We add the LIVE_I_ALWAYSKNOWN property to
 *                the environment if the environment is a wizard.
 * Arguments    : object inv  - the environment this object is entering.
 *                object from - the possible place this object came from.
 */
void
enter_env(object inv, object from)
{
    ::enter_env(inv, from);
    
    /* Test for entering a place with bright light */
    set_alarm(1.0 + itof(random(5)), 0.0, light_cry);      
}
     
/*
 * Function name: init_living
 * Description:   This function is called when this object encounters a 
 *                new living.
 */
void
init_living()
{
    ::init_living();

    /* If a player, light_cry and do not proceed */
    if (interactive(this_player()))
    {
        set_alarm(1.0 + itof(random(5)), 0.0, light_cry);      
        return;
    }

    /* If living is an albi, make a team */
    if (this_player()->id("avenir_albus_id"))
    {
        team_join(this_player());
        this_player()->set_leader(this_object());
        return;
    }           
}
