/*
 *  druid.c
 *
 *  This is a druid who inhabits a temple in Mithas, his
 *  skills include summoning treants, causing the treants
 *  to enrage, healing and calling fourth fireflies when 
 *  the room is dark, the fireflies also have a chance of
 *  blinding targets with nightvision in the room.
 *
 *  Created by Carnak, January 2016
 */
 
#pragma save_binary

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"

inherit AM_FILE
inherit AUTO_TEAM
inherit "/lib/unique";

#include "../local.h"

#define ENRAGED     "treant_is_enraged"

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

int gTreants = 0,
    absorb;

void
reset_monster()
{
    gTreants = 0;
}

int
query_absorb()
{
    return absorb;
}

int
add_absorb(int i)
{
    if (i + absorb > 10000)
    {
        absorb = 10000;
    }
	else
    {
        absorb = absorb + i;
    }
}

int
remove_absorb(int i)
{
    if (absorb - i < 0)
    {
        absorb = 0;
    }
	else
    {
      absorb = absorb - i;
    }
}

/*
 * Function     : init_absorb
 * Description  : This effects increases absorb and decreases the 
 *                limit of treants as long as the druid is out of
 *                combat
 * Returns      : nothing
 */
 
int
init_absorb()
{
    if (this_object()->query_relaxed_from_combat()) {
        if (query_absorb()<10000) {
            command("emote lowers his head in silent meditation, absorbing "+
            "energy from nature.");
            
            add_absorb(1200);
            TO->heal_hp(random(TO->query_max_hp()/3));
            
            if (gTreants)
            {
                gTreants -= 1;
            }
        }
    }

    set_alarm(120.0,0.0, &init_absorb());
}

/*
 * Function     : arm_me
 * Description  : Arms the druid and sets spawn rate for the
 *                magical staff
 * Returns      : nothing
 */
void
arm_me()
{
    object *items,
            ob, ob2;

    if (sizeof(all_inventory(this_object())))
        return;
    
    ob      = clone_unique(TWEP + "chislev_staff", 3,
                           TWEP + "false_staff")->move(TO,1);

    ob2     = clone_object(TDIR + "obj/wrap");
    ob2->reset_wrap();
    ob2->move(TO,1);
    
    command("wield staff");
}

void
create_krynn_monster()
{
    if(!IS_CLONE)
        return;

    set_pick_up_team(({"treant"}));
    set_max_team_size_auto_join(6);

    set_name("druid");
    add_name("human");
	
    set_name("_chislev_druid");
    set_living_name("_chislev_druid");

    set_adj("grey-robed");
    add_adj("hooded");
    set_race_name("druid");
    set_gender("G_MALE");
    set_long("This druid seems to be of human descent, but most "+
    "of his appearance is hidden by a grey robe, making it "+
    "difficult to ascertain. The parts of skin you manage to "+
    "glimpse is covered in bark and moss, and jagged pieces of "+
    "wood emerge from his back and shoulders piercing through "+
    "the worn down robe.\n");

    set_stats(({175,180,180,200,200,175}));
	
    set_hitloc_unarmed(0, 80, 100, "bark skin");

    set_alignment(0);
    set_skill(SS_WEP_POLEARM, 90);
    set_skill(SS_PARRY, 75);
    set_skill(SS_DEFENCE, 80);
    set_skill(SS_AWARENESS, 90);
    set_skill(SS_BLIND_COMBAT, 90);
	
    set_skill(SS_ELEMENT_LIFE, 100);
    set_skill(SS_ELEMENT_EARTH, 100);
    
    add_prop(OBJ_I_RES_DEATH, 60);
    add_prop(OBJ_I_RES_POISON, 60);
    add_prop(OBJ_I_RES_FIRE, -50);
	
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    add_ask(({"quest","task","help"}),"emote speaks in a "+
    "calm demeanor: One should always endeavor to face "+
    "the difficulties of life, and not to burden others. "+
    "I may however offer advice if you seek it.",1);
	  
    add_ask(({"chislev","the wild one","wild one"}),"emote "+
    "speaks in a calm demeanor: Chislev is nature incarnate "+
    "and the divine power of instinct, if she peaks your "+
    "interest, you should read the tome in the atrium.",1);
	
    add_ask(({"temple","druids","druid"}),"emote speaks in a "+
    "calm demeanor: This temple was once the home of a great "+
    "order of druids worshipping Chislev, now only I remain.",1);
    
    add_ask(({"advice","guarded","bounty","harvest","herbs",
    ""}), "emote speaks in a calm demeanor: To harvest the "+
    "bounty of nature, one must gain the blessing of Chislev, "+
    "or suffer her wrath.",1);
    
    add_ask(({"blessing"}),"emote speaks in a calm demeanor: "+
    "I can not give you the blessing of Chislev, however if you "+
    "seek out the sanctuary inside the temple, you may earn "+
    "it on your own, should she find you worthy.",1);
    
    add_ask(({"sanctuary"}),"emote speaks in a calm demeanor: "+
    "I am not your guide, young one. If you cannot find what "+
    "you seek, then you are unworthy of her blessing.",1);
	
    init_absorb();

}

/*
 * Function     : add_introduced
 * Description  : Handles how the NPC should act if introduced to.
 * Returns      : nothing
 */
void
add_introduced(string name)
{
    command("emote speaks in a calm demeanor: I have forsaken "+
    "all possessions in devotion to Chislev, I hold no names "+
    "or titles, but you may call me druid if you so wish.");
}

/*
 * Function     : summon_treants
 * Description  : Handles the cloning of treants and their mana
 *                cost.
 * Returns      : nothing
 */
 
void
summon_treants()
{
    object ob;
    
    if (TO->query_mana() < 450)
        return;
    
    ob = clone_object(TNPC + "treant");
    ob->move(environment(TO));
    ob->add_name("_treant_");
    
    TO->add_mana(-450);
    
    tell_room(environment(TO), QCTNAME(ob) + " emerges from the ground.\n");
    ob->command("assist",TO);
}

/*
 * Function     : special_attack
 * Description  : The druid has three special abilities, main one
 *                is the ability to summon treants to aid in combat,
 *                secondary one is the ability to heal which scales
 *                with the recent amount of summoned treants, no
 *                matter if they died, the heal drains absorb and
 *                not mana, third ability is to enrage the treant,
 *                this drains a large amount of absorb
 * Returns      : nothing
 */

int
special_attack(object enemy)
{
    if (!CAN_SEE_IN_ROOM(this_object()) && random(2) &&
        !present("_chislev_swarm",environment(this_object())))
    {
        command("emote calls upon nature.");
        object firefly;
        firefly = clone_object(TOBJ + "firefly");
        firefly->move(environment(this_object()),1);
        firefly->init_lifetime();
    }
    
    foreach(object tmember: query_team())
    {
        if (!tmember->query_target())
        {
            tmember->command("assist",TO);
        }
    }
    
    string str;
    if (random(3) && query_absorb() && gTreants)
    {
        object ob;
        
        if (sizeof(query_team()))
            ob = ONE_OF(query_team());
        
        if (TO->query_hp()<2500)
        {
            int heal = random(250)+350;
            
            if (query_absorb() < heal)
                heal = query_absorb();
            
            remove_absorb(heal);
            TO->heal_hp(heal*(gTreants + 1));
            tell_room(E(TO),QCTNAME(TO) + "'s wounds begin to "+
            "rapidly heal.\n");
            return 1;
        }
        else if (objectp(ob) && ob->query_hp()<2500)
        {
            int heal = random(50)+10;
            if (!random(2) && TO->query_mana() > heal)
            {
                TO->add_mana(-heal);
                ob->heal_hp(heal*gTreants);
                tell_room(E(TO),QCTNAME(TO) + " channels his "+
                "innate energy to heal the " + QTNAME(ob) + ".\n");
            }
        }
    }
	
    if (!random(12) && query_absorb() > 2500 && sizeof(query_team()))
    {
        object *norm,
                ob;
        
        norm    = filter(query_team(),
                  &operator(<)(,1) @ &->query_prop(ENRAGED));
        ob      = ONE_OF(norm);
        
        if (random(sizeof(norm)))
        {
            return 0;
        }
        
        if (!ob->query_prop(ENRAGED))
        {
            tell_room(E(TO),QCTNAME(TO) + " calls out to Chislev to grant "+
            "him aid.\n");
            ob->set_stat_extra(SS_STR, 100);
            ob->set_stat_extra(SS_DEX,  80);
            ob->set_stat_extra(SS_CON,  50);
            ob->heal_hp(ob->query_max_hp() / 10);
            ob->change_prop(LIVE_I_QUICKNESS,
                 query_prop(LIVE_I_QUICKNESS) + 100);
            ob->add_prop(ENRAGED, 1);
                 
            tell_room(E(TO), QCTNAME(ob) + " has become enraged.\n");
            ob->set_short("enraged "+ob->query_short());
            ob->add_adj("enraged");
            ob->heal_hp(ob->query_max_hp());
            remove_absorb(2500);
            return 1;
        }
    }
	
    if (random(4) || gTreants > 3 || sizeof(query_team()) > 2)
        return 0;
	
    if (TO->query_mana() < 450)
        return 0;
    
    gTreants++;
    command("emote lowers his head in a silent prayer.");
	
    set_alarm(2.5, 0.0, &summon_treants());
    
    return 1;
}

/*
 * Function     : init_team_pickup
 * Description  : This is called so that it will join the summoned
 *                treants
 */

void
init_living()
{
    init_team_pickup();
    ::init_living();
}

/*
 * Function     : do_die
 * Description  : This is so we can see who kills him
 */
 
public int
do_die(object killer)
{
    if (file_size(TLOG + "slayerlog") > 100000)
        rename(TLOG + "slayerlog", TLOG + "slayerlog.old");
	
    write_file(TLOG + "slayerlog", 
	"-----------------------------------------\n" + 
    ctime(time()) + "\n" + killer->query_name() + " -" +
    " Average: " + killer->query_average_stat() +
    ", Race: " + killer->query_race_name() +
    ", Health: " + killer->query_hp() + "/" + killer->query_max_hp() +
    ", Team: " + sizeof(killer->query_team()) +
    "\nDruid - Treants: " + gTreants +
    ", Absorb: " + this_object()->query_absorb() +"\n");
	::do_die(killer);
	return 1;
}