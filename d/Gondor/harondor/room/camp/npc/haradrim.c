/* Name      : /d/Gondor/harondor/room/camp/npc/haradrim.c
 * Purpose   : The standard haradrim warrior fro the camp.
 *             These will be alot harder then the ones in
 *             the corsair camps to justify the good
 *             equipment they will carry.
 * Created by: Sir Toby, Gondor Domain, 2005-11-23
 *
 *   Modified: Sir Toby, Gondor Domain, 2006-10-19
 *                       Added a special attack borrowed
 *                       the code from:
 *                       /d/Gondor/arnor/npc/massive_troll.c
 *
 *             Sir Toby, Gondor Domain, 2006-11-02
 *                       Fixed a space typo in special attack
 *             Eowul, 2008-10-12
 *                       Changed the haradrim race to human
 *             Cotillion, 2021-09-16
 *                       Switch to equip
 */

/*
 prestige awarded in Ithilien

 object                     alignment  prestige
 Haradrim Captain (Army)   -350..-600      1200
 Haradrim Warrior (Army)   -200..-400       800
 Mordor Orc                -100..-300       575
 Mordor Orc Captain        -200..-450       800

 Camp:
 Uruk                      -200..-400       600
 Orc                       -100..-300       370
 Haradrim                  -200..-440       500
 Cook                      -250..-406       500
 
 Harondor:
 Haradrim                  -300..-500      1000

 */


inherit "/std/monster";
inherit "/d/Gondor/harondor/room/camp/npc/npc_intro";

#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/harondor/room/camp/defs.h"
#include "/d/Gondor/common/lib/logkill.c"


string			lookadj();
string          harad_title();
string          harad_name();
void			help_friend(object ob);
public varargs int	move_living(string how, mixed to_dest,
				    int dont_follow, int no_glance);
public void		destroy_eyes();

void
create_monster()
{
   string adj_desc = lookadj();
   string title_desc = harad_title();
   string har_name = harad_name();

   set_name(har_name);

   add_name(({"warrior","southron","man", "haradrim", "haradrim warrior"}));
   add_name("_harad_warrior_");
   
   set_pname("haradrim");
   add_pname(({"warriors", "southrons", "men", "haradrim", "haradrim warriors"}));
   set_living_name(har_name);
   set_title(title_desc); 
  
   set_alignment(-300-random(200));  

   set_adj(adj_desc);
   add_adj("dark-skinned");
   set_race_name("human");
   set_short(adj_desc + " dark-skinned male haradrim");

   set_gender(G_MALE);

   set_long("A " + adj_desc + " and dark-skinned male haradrim. " +
         "His deep-set almost-black eyes staring intensly at " +
         "you, almost unblinking, from under his helmet like " +
         "twin caves from within another cave. Well-built " +
         "arms and stout hands tightly grip both weapon " +
         "and shield.\n");



   default_config_npc(110+random(10));    
   set_base_stat(SS_CON,             140 + random(10));
   set_base_stat(SS_DIS,             130 + random(10));
   set_skill(SS_WEP_SWORD,           85 + random(10));
   set_skill(SS_WEP_POLEARM,         85 + random(10));
   set_skill(SS_PARRY,               90 + random(5));
   set_skill(SS_DEFENCE,             90 + random(5));
   set_skill(SS_AWARENESS,           45 + random(5));
   set_skill(SS_UNARM_COMBAT,        50 + random(10));
   set_skill(SS_PROTECT_TEAM_MEMBER, 80 + random(5));   
   add_prop(CONT_I_HEIGHT,   185+random(15));
   add_prop(CONT_I_WEIGHT, 80000+random(5000));
   add_prop(CONT_I_VOLUME, 75000+random(15000));    
   add_prop(LIVE_I_NEVERKNOWN, 1);
   
   set_chat_time(200+random(10));
   add_chat("Where are these ridiculous Dunedain? Did they all flee?");
   add_chat("What news from the north? That seems to be the eternal question!");
   add_chat("Why did I sign up on this mission?");
   add_chat("I wish I had something to fight, I hate this waiting!");
   
   set_cchat_time(50+random(15));
   add_cchat("Take this, you worm!");
   add_cchat("Stand still and fight, you coward!"); 
   add_cchat("Let me kill you quickly, maggot, it will hardly hurt!");
   
   set_act_time(300+random(50));
   add_act("glare");
   add_act("hiss");
   add_act("grin");
   
   set_cact_time(30+random(10));
   add_cact("scream"); 
   add_cact("growl");
   add_cact("shout Die, you stinking child of a troll!");
   

   add_prop(OBJ_M_HAS_MONEY, ({ 10 + random(30), 2 + random(5) }));
   
   equip(HAR_RM_WEP_DIR + one_of_list(({"seax", "framea", "hc_scimitar"})));
   equip(HAR_RM_ARM_DIR + "bhauberk");
   
   if(random(100) > 50) {
      equip(HAR_RM_ARM_DIR + "luna");
   }
   
   equip("/d/Gondor/ithilien/forest/harad_earring");
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
   object *arr;
   int i;
   
   ::attacked_by(ob);
   
   arr = (object *)query_team_others();
   for (i = 0; i < sizeof(arr); i++)
      arr[i]->notify_ob_attacked_me(this_object(), ob);
}

/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *                attacker - The attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
   if (query_attack())
      return;
   
   if (random(10))
      set_alarm(rnd()*5.0, 0.0, &help_friend(attacker));
}

int
query_show_list(object x)
{
    return !((x->query_no_show()) || (x->query_prop(OBJ_I_INVIS)));
}


/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */
void
help_friend(object ob)
{
   object *loot_list;

   if (ob &&
       !query_attack() &&
       interactive(ob) &&
       ENV(ob) == ENV(TO))
   {
      loot_list = filter(all_inventory(ob), query_show_list);
      if (sizeof(loot_list))
      {
        command("say I will aid you in killing "+OBJECTIVE(ob)+", I want to have "+
	  POSSESSIVE(ob) + " " + 
	  (ONE_OF_LIST(loot_list))->short() + "!");
      }
      else
      {
        command("say I will aid you in killing "+OBJECTIVE(ob)+"!");
      }
      command("kill " + lower_case(ob->query_real_name()));
      command("growl " + lower_case(ob->query_real_name()));
   }
}

string lookadj() 
{
   return one_of_list(({"grim", "tall", "angry", "beastly", "mean", 
                        "dirty", "foul", "brutal", "battered", 
                        "sinister","wicked","savage", "ugly"}));
}

/* See titles listen in full in:
   ../docs/Haradrim_Military_Rankings.txt
 */
string harad_title()
{
   return one_of_list(HARAD_TITLE);
}

string harad_name()
{
   return one_of_list(HARAD_NAMES) + 
          " ahn toh " +
          one_of_list(HARAD_SURNAMES);
}

int query_knight_prestige() { return 1000; }


/*
 * Function name:	move_living
 * Description	:	mask parent so we can check new env for spying eyes
 * Arguments	:	string how -- direction of travel, etc
 *			mixed to_dest -- destination
 *			int dont_follow -- flag re group movement
 *			int no_glance -- flag re looking in new room
 * Returns	:	int -- 0 on success, non-0 on failure
 */
public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int rval;
    rval = ::move_living(how, to_dest, dont_follow, no_glance);

    if (objectp(present("eye", ENV(TO))))
    {
	set_alarm(2.0, 0.0, destroy_eyes);
    }
    return rval;
} /* move_living */

/*
 * Function name:	destroy_eyes
 * Description	:	smash any spying eyes in env
 */
public void
destroy_eyes()
{
    object	*eyes;
    int		s;

    s = sizeof(eyes = filter(all_inventory(ENV(TO)), &->id("eye")));
    if (s > 0)
    {
	command("emote smashes the glass eye" +
	    (s > 1 ? "s." : "."));
	eyes->remove_object();
    }
} /* destroy_eyes */

/*
 * Function name: kill_victim
 * Description:   Called from special_attack to handle if the player dies.
 * Arguments:     victim (the one we are fighting right now)
 * Returns:       Nothing
 * Note:          
 */
void
kill_victim(object victim)
{
    if (victim->query_hp() < 0)
    {
        victim->command("wail");
        victim->command("emote falls heavily to the ground, head first.\n");
        victim->command("emote twitches convulsively a few times, then " +
                        "lay utterly still.\n");
        victim->do_die(this_object());
    }
    return;
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
    int hurt, whimp;
    int rate;
    int RAN = 5;
    int haradrim_str = query_stat(SS_STR);
    int haradrim_dex = query_stat(SS_DEX);
    object *others = victim->query_team_others();
    object next_victim;
    int i;
    string race, gender;
    string hitspot = one_of_list( ({"face", "head", "chest", "groin",
                          "shoulder", "chin", "stomach", "shins", }) );
    string elbowhit = one_of_list( ({"face", "head", "chest", "throat",
                          "ear", "mouth", "nose", "eyebrow", }) );

    // Make a shield slam: 1 round in 5

    if (random(100) < 65)
        return 0;

    rate = RAN;
    hurt = random(haradrim_str + haradrim_dex)/rate + 25 + random(100);

    if (hurt >= victim->query_hp())
        hurt = (victim->query_hp())/rate + random(100) ;

    object arm;
    object *shields = filter(query_armour(-1), &->id("shield"));
    if (sizeof(shields))
        arm = shields[random(sizeof(shields))];

    // Shield attack
    if ((random(10) < 6) && arm->id("shield"))
    {

        // occasionally strafe the entire team if there is a team
        if (sizeof(others) && random(10) < 5)
        {
            others += ({ victim });
            for (i = 0; i < sizeof(others); i++)
            {
               // no crits with special and hit enemies only
                if (present(others[i], environment(this_object())))
                {
                    if (hurt >= others[i]->query_hp())
                        hurt = (others[i]->query_hp())/rate + random(75);
                    others[i]->heal_hp(-hurt);

                    others[i]->catch_msg("The haradrim take a quick " +
                        "backstep before charging into you. Holding out his shield " +
                        "the haradrim savagely strafes you, " +
                        "slamming you hard in the " + hitspot + 
                        " with his " + arm->short() + ".\n");
                    tell_room(environment(this_object()), "The haradrim " + 
                        "takes a quick backstep before charging into " +
                        QNAME(others[i])+ ". Holding out his shield the haradrim " +
                        "savagely strafes " +QNAME(others[i])+ " slamming " +
                        others[i]->query_objective()+ " hard in the " +hitspot+ ".\n", others[i]);

                    whimp = ftoi(itof(others[i]->query_hp()) / 
                        itof(others[i]->query_max_hp()) * 100.0);

                    if (whimp < others[i]->query_whimpy())
                    {
                        others[i]->add_panic(hurt/2);
                        if (present(others[i], environment(this_object())))
                            others[i]->run_away();
                        race = others[i]->query_race_name();

                        if (!stringp(race))
                            race = "";
                        else
                            race = " " + race;
                        command("shout You little maggot" + race + "! " +
                            "Come back here you miserable cur!");
                    }
                    kill_victim(others[i]);
                    hurt = random(haradrim_str + haradrim_dex)/rate;
                }
            }
            command("growl");
            return 1;
        } // if sizeof others

        // else if player is fighting solo
        victim->heal_hp(-hurt);
        victim->catch_tell("Holding his " +arm->query_short()+ 
            " in front of himself the " +short()+ " savagely " +
            "slams you hard in the " +hitspot+ ".\n");
        tell_room(environment(this_object()), "The " +short() + " holds his  " +
            arm->query_short()+ " in front of himself savagely " +
            "slamming " +QNAME(victim)+ " hard in the " +hitspot+ ".\n", victim);
        kill_victim(victim);
        return 1;
    }

    // no crits with special
    if (hurt > victim->query_hp())
        hurt = (victim->query_hp())/rate + random(50);

    switch (hurt)
    {
    case 0..30:
        victim->catch_tell("The haradrim lashes out with his elbow, all of a sudden, hitting you in the " +
                elbowhit + ".\n");
        victim->heal_hp(-hurt);
        break;
    case 31..100:
        victim->catch_tell("The haradrim suddenly lashes out, rather hard, with his elbow hitting you in the " +
                elbowhit + ". You feel a bit dizzy from the impact.\n");
        victim->add_attack_delay(1 + random(2));
        victim->add_mana(-hurt/4);
        victim->heal_hp(-hurt);
        break;
    case 101..150:
        victim->catch_tell("The haradrim suddenly lashes out, quite fiercely, with his elbow hitting you in the " +
                elbowhit + ". You feel quite dizzy from the impact.\n");
        victim->add_attack_delay(3 + random(2));
        victim->add_mana(-hurt/2);
        victim->heal_hp(-hurt);
        break;
    default:
        victim->catch_tell("The haradrim suddenly lashes out with his elbow striking you in the " +
                elbowhit + ".\n");
        break;
    }
    
    tell_room(environment(this_object()), "The haradrim suddenly lashes out " +
              "with his elbow hitting " +QNAME(victim)+ " in the " +
                elbowhit + ".\n", victim);

    kill_victim(victim);

    /* occasionally switch randomly to another teammate
       to keep the team off balance */
    if (random(10) > (RAN))
    {
        others += ({ victim });
        // next_victim = others[random(sizeof(others))];
        next_victim = one_of_list(others);

        if (present(next_victim, environment(this_object())))
        {
             command("kill " + next_victim->query_real_name());
             command("grin broad " + next_victim->query_real_name());
        }
    }
    return 1;
}
