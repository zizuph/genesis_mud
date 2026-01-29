/*  An npc in the WoHS test.
 */

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/guilds/wohs/defs.h"
#include "/d/Krynn/common/defs.h"

inherit "/d/Krynn/std/monster";
inherit AUTO_TEAM

#define SWORD    "/d/Krynn/guilds/wohs/test/obj/wohs_test_greatsword"
#define ARMOUR   "/d/Krynn/guilds/wohs/test/obj/wohs_test_platemail"
#define LEGGINGS "/d/Krynn/guilds/wohs/test/obj/wohs_test_leggings"
#define HELMET   "/d/Krynn/guilds/wohs/test/obj/wohs_test_helmet"
#define GLOVES   "/d/Krynn/guilds/wohs/test/obj/wohs_test_gauntlets"
#define CAPE     "/d/Krynn/guilds/wohs/test/obj/wohs_test_cape"

#define TELL(x)         tell_room(E(TO), x, ({ TO }), TO)

#define SECOND_TASK     "_wohs_test_given_second_task"
#define OBSERVE_PROP    "_wohs_test_successful_observe"
#define SCRY_PROP       "_wohs_test_successful_scry"
#define THIRD_TASK      "_wohs_test_given_third_task"

#define ENGAGED_ERGOTHIANS "_wohs_test_engaged_city_siegers"
#define KILLED_DUKE        "_wohs_test_killed_duke"

#define DMG_TAKEN       "_wohs_test_damage_taken"

int max_hp;

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_pick_up_team(({"cavalier", "scout", "presbyter"}));
    set_max_team_size_auto_join(20);

    set_name("serl");
    add_name("duke");
    set_living_name("serl");
    set_title("Kar-thon, Duke of Ergoth, Praetor-General of the " +
        "Imperial Armies");
    set_race_name("human");
    set_adj("tall");
    add_adj("hoary-bearded");
    set_short("tall hoary-bearded human");
    set_gender(G_MALE);
    set_long("Before you stands a tall warrior built like an ox, wearing "+
        "the finest imperial armour and trappings of nobility of a very "+
        "senior rank. His helm is open and reveals a face covered with "+
        "a hoary-beard that doesn't quite cover a fresh angry red scar "+
        "that runs down his face.\n");

    set_stats(({280,280,280,280,280,280}));
    set_hp(query_max_hp());
    set_aggressive(1);

    add_prop(CONT_I_WEIGHT, 82000);
    add_prop(CONT_I_HEIGHT, 185);

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 80);

    set_all_hitloc_unarmed(40);

    set_alignment(0);

    set_act_time(0);
    add_act("assist");

    trig_new("%w 'introduces' %s","react_to_intro");
    set_default_answer("say I have no word for you magi! My blade will " +
        "talk for me!", 1);

}

void
react_to_intro(string who,string garbage)
{
    set_alarm(2.0,0.0,"return_intro",who);
}

void
return_intro(string who)
{
    who = L(who); 
    if (P(who,E(TO)))
    {          
           command("smile merciless");
           command("say Yes, you should know the name of the one about "+
               "to destroy your last bastions of safety!");
           set_alarm(1.5,0.0, &command("introduce myself"));
    }
}

void
arm_me()
{
    equip( ({ SWORD, ARMOUR, LEGGINGS, HELMET, GLOVES, CAPE }));
}

public void
attack_object(object ob)
{
    max_hp = ob->query_hp();

    ::attack_object(ob);
}

public void
do_die(object killer)
{
    int hp = killer->query_hp();
    int dmg_taken = killer->query_prop(DMG_TAKEN);

    dmg_taken = dmg_taken + (max_hp - hp);

    killer->add_prop(DMG_TAKEN, dmg_taken);
    killer->add_prop(KILLED_DUKE, 1);
    WOHS_MANAGER->add_wohs_test_props(killer, KILLED_DUKE, 1);
    WOHS_MANAGER->add_wohs_test_props(killer, DMG_TAKEN, dmg_taken);


    ::do_die(killer);
}

int
special_attack(object enemy)
{
    object wep;
    mixed hitres;
    string how, weapon, how1, how2;
    int strength = this_object()->query_stat(SS_STR);

    if(random(5)) /* we do ordinary attack now */
	return 0;

    hitres = query_weapon(-1);
    if(!sizeof(hitres)) /* no weapon wielded */
	return 0;

    wep = hitres[0];
    weapon = hitres[0]->query_short();

    if ( wep->id("mace")  )
        hitres = enemy->hit_me((strength * 3) + random(strength), 
            W_BLUDGEON, TO, hitres[0]->query_attack_id());
    else
        hitres = enemy->hit_me((strength * 3) + random(strength), 
            W_SLASH, TO, hitres[0]->query_attack_id());

    if (hitres[0] < 0)
	hitres[0] = 0;

    switch(hitres[0])
    {
    case 0:
	how1 = "his " + weapon + " just missing";
	how2 = "his " + weapon + " just missing";
	break;
    case 1..10:
        how1 = "his " + weapon + " bruising the skin of";
	how2 = "his " + weapon + " grazing the skin of";
	break;
    case 11..20:
        how1 = "slamming his " + weapon + " hard into";
        how2 = "slicing his " + weapon + " deeply into";
	break;
    case 21..40:
        how1 = "his " + weapon + " crushing";
	how2 = "his " + weapon + " deeply penetrating";
	break;
    case 41..60:
        how1 = "smashing his " + weapon + " powerfully into";
	how2 = "burying his " +weapon+ " deeply into";
	break;
    default:	
        how1 = "his " + weapon + " splattering blood everywhere " +
            "as he almost pulverises";
        how2 = "his " + weapon + " splattering blood everywhere " +
            "as he almost removes";
    }

    if ( wep->id("mace") )
        how = how1;
    else 
        how = how2;
        
    enemy->catch_msg(QCTNAME(TO) + " swings at " +
      "you forcefully, " + how + " your " + hitres[1] + ".\n");

    tell_watcher(QCTNAME(TO) + " swings at " + QCTNAME(enemy)
      + " in a forcefully, " +how+ " " +QTNAME(enemy)+ "'s" +
      " " + hitres[1] + ".\n", enemy);

    if (enemy->query_hp() <= 0)
    {
	enemy->do_die(TO);
    }
    return 1;
}

void
attack_intruder(object enemy, string race)
{
    if(!CAN_SEE(TO, enemy))
    {
	return;
    }

    if(TO->query_attack())
      return;

    command("kill " +enemy->query_real_name());
    return;
}

void
tree_scene(object enemy)
{
    command("emote bends over and tends to the ground with a dirk.");
    set_alarm(1.5,0.0, &TELL("The ground begins to bubble and rise, " +
        "like a boil or blister, then explodes - showering dirt " +
        "everywhere.\n"));
    set_alarm(5.5,0.0, &command("emote curses and wipes dirt from his " +
        "face, pausing in surprise as a sapling sinuously begins to " +
        "rise out of the ground."));
    set_alarm(9.5,0.0, &TELL("You notice that the unnatural sapling " +
        "rising from the ground is one of black needles, black bark, " +
        "and a sticky black sap oozing from its trunk.\n"));
    set_alarm(13.5,0.0, &command("emote swears reverently: Blood of a " +
        "thousand wyrms!"));
    set_alarm(18.5,0.0, &TELL("The pine trees of the grove closest to " +
        "the black pine suddenly groan, and begin twisting away from " +
        "it... even uprooting themselves in their eagerness to shy " +
        "away.\n"));
    set_alarm(24.5,0.0, &command("emote whoops!"));
    set_alarm(26.5,0.0, &command("shout Men! Ready yourself! A path " +
        "opens to the Tower!"));
    set_alarm(31.5,0.0, &TELL("Ergothian cavaliers and presbyters " +
        "cheer valiantly, and ready themselves to enter the grove!\n"));
    set_alarm(35.5,0.0, &enemy->add_prop(OBSERVE_PROP, 1));
    set_alarm(35.5,0.0, &WOHS_MANAGER->add_wohs_test_props(enemy, 
        OBSERVE_PROP, 1));
    set_alarm(35.5,0.0, &write("\nYou should return to the Tower " +
        "swiftly and report back what you have discovered, and " +
        "forewarn the impending attack!\n\n"));
}

void
prepare_reaction(object enemy)
{
    if(enemy->query_npc())
        return;
    if(enemy->query_wiz_level())
        return;

    if(!CAN_SEE_IN_ROOM(TO))
    {
         command("say Magical darkness! Break out the torches "+
               "and lanterns!");

         setuid();
         seteuid(getuid());
         object torch = clone_object("/d/Krynn/guilds/wohs/test/obj/wohs_test_torch");
         torch->move(TO, 1);
         torch->move(TO, 1);
         command("light all");
         set_alarm(1.5, 0.0, &attack_intruder(TP));
         return;
    }

    if(!CAN_SEE(TO, enemy))
    {
        if(enemy->query_prop(OBSERVE_PROP) || enemy->query_prop(SCRY_PROP))
        {
            return;
        }
        if(enemy->query_prop(SECOND_TASK))
        {
            set_alarm(4.0, 0.0, &write("Hidden from sight, you observe " +
                "the Ergothian forces laying siege to the Tower of " +
                "High Sorcery...\n"));
            set_alarm(7.5, 0.0, &tree_scene(TP));
        }

	return;
    }

    set_alarm(0.5, 0.0, &attack_intruder(TP));
    return;
}


void 
init_living() 
{
    set_alarm(0.5, 0.0, &prepare_reaction(TP));
    init_team_pickup(); 
    ::init_living(); 
}
