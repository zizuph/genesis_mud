
/* 
 * Scout outside Neidar village.
 */
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include "/d/Krynn/common/defs.h"
inherit "/d/Krynn/tharkadan/std/hill_dwarf_base";

#define HILL_DWARF_ENEMY  "_hill_dwarf_enemy_"

public void remove_descr();
int standing = 1;

public void
create_hill_dwarf()
{
    set_dwarf_level(4);
    remove_name("clan_guard");
    set_name("zirkan");
    set_living_name("zirkan");
    set_title("Ironhammer, Fierce Clansman of the Neidar Clan");

    add_ask(({"village","chieftain"}),"rsay The village is closed to " +
        "all until the chieftain has returned. He has gone north with " +
        "some warriors... a red dragon had been seen flying around " +
        "the ranges.", 1);
    add_ask(({"dragon","red dragon"}),"rsay A red dragon has been seen " +
        "flying around the mountain ranges to the north. Probably " +
        "lairing with the armies entering the trails from Pax Tharkas. " +
        "Our chieftain has gone to hunt it down like our ancestors did " +
        "in the old days!", 1);
    add_ask(({"quest","help","task"}),"rsay Nay, I got nothing for ye " +
        "to do. Maybe the chieftain does have something when he " +
        "returns from his hunt?", 1);
    add_ask(({"prisoners","refugees","humans"}),VBFC_ME("refugee_hint"));
    add_ask(({"plainsmen","abanasinia","plainsmen from abanasinia",
        "tracks"}), VBFC_ME("plainsmen_hint"));
    add_ask(({"mishakal","old gods","gods","elistan","ancient order of " +
        "the stars","clerics","clerics guild","kiri jolith"}),
        VBFC_ME("hoots_hint"));

    trig_new("%w 'introduces' %s","react_to_intro");
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
        command("emote puffs briefly on his long-stemmed pipe " +
            "thoughtfully.");
        set_alarm(1.5,0.0, &command("rsay Well met. I am Zirkan " +
            "Ironhammer, Ogreslayer of the Neidar Clan."));
        set_alarm(2.5,0.0, &command("rsay The village is closed to " +
            "visitors while our Chieftain is away."));
        set_alarm(3.5,0.0, &command("rsay He left with some of our " +
            "warriors on the trail of a red dragon seen flying in " +
            "the ranges to the north."));
        set_alarm(3.5,0.0, &command("emote grunts gruffly."));
    }
} 

void
summon_assistance()
{
    E(TO)->summon_clan_warriors();
    return;
} 

/* Function name: hook_attacked
 * Description  : Hook called when the npc is attacked by someone.
 */
public void
hook_attacked(object enemy)
{
    if ( !enemy->query_prop(HILL_DWARF_ENEMY) )
        enemy->add_prop(HILL_DWARF_ENEMY, 1);
    
    command("emote raises a warhorn and blows it twice, its clarion " +
            "echoing into the valley below.\n\nYou notice dwarven " +
            "warriors arming themselves and heading up towards you " +
            "from the village below.\n\n");
    set_alarm(10.5, 0.0, &summon_assistance());

    return;
}

/*
 * Funtion Name: add_desc
 * Description : Adds extra short description.
 */
public void
add_descr(string description)
{
    add_prop(LIVE_S_EXTRA_SHORT, " " + description);
}

/*
 * Function:	remove_descr
 * Description:	Remove the extra description
 */
public void
remove_descr()
{
    remove_prop(LIVE_S_EXTRA_SHORT);
}

void
attack_object(object ob)
{
    if(!standing)
    {
       remove_descr();
       command("emote puts away his pipe and jumps into a battle stance.");
       command("emote raises a warhorn and blows it twice, its clarion " +
            "echoing into the valley below.\n\nYou notice dwarven " +
            "warriors arming themselves and heading up towards you from " +
            "the village below.\n\n");
       set_alarm(10.5, 0.0, &summon_assistance());
       standing = 1;
     }
    ::attack_object(ob);
}

public void
sit_down()
{
    if(!standing)
        return;

    command("emote sits himself down on a stump, pulls out a long-" +
           "stemmed pipe and begins puffing on it contently.");
    add_prop(LIVE_S_EXTRA_SHORT, " sitting on a stump, puffing " +
           "contently on a long-stemmed pipe");
    standing = 0;
    return;
}


public void
stand_up()
{
    if(standing)
        return;

    remove_descr();
    command("emote taps out his long-stemmed pipe and rises to his feet.");
    standing = 1;
    return;
}

void 
init_living() 
{

    if(CAN_SEE(TO, TP))
      set_alarm(8.0, 0.0, &stand_up());
 
    ::init_living(); 
}

string 
refugee_hint()
{
   if(TP->query_guild_name_occ() == "Priests of Takhisis" ||
      TP->query_guild_name_occ() == "Dragonarmy" ||
      TP->query_guild_name_lay() == "Templars of Takhisis")
   {
       command("rsay Nay, I aint seen anything.");
       command("smile humourless");
       return "";
   }

   command("rsay Some human refugees that escaped the Pax Tharkas " +
       "mining camps came through this way, and have set up a " +
       "camp in a valley southeast of here.");
   command("rsay You may have trouble finding it though... they had " +
       "plainsmen from Abanasinia with them, covering their tracks.");

   return "";
}

string 
plainsmen_hint()
{
   if(TP->query_guild_name_occ() == "Priests of Takhisis" ||
      TP->query_guild_name_occ() == "Dragonarmy" ||
      TP->query_guild_name_lay() == "Templars of Takhisis")
   {
       command("rsay Ye aint getting any answers from me stranger.");
       command("smile stubbornly");
       return "";
   }

   command("rsay Aye, a lot of plainsmen from Abanasinia were among the " +
       "refugees that escaped from the mining camps of Pax Tharkas.");
   command("rsay While they don't know the ranges as well as us hill " +
       "dwarves, they know enough woodsmanship to hide their trails.");
   command("rsay You'll need to be persistent in your searching or a " +
       "good tracker to find them!");

   return "";
}

string 
hoots_hint()
{
   if(TP->query_guild_name_occ() == "Priests of Takhisis" ||
      TP->query_guild_name_occ() == "Dragonarmy" ||
      TP->query_guild_name_lay() == "Templars of Takhisis")
   {
       command("rsay Ye aint getting any answers from me stranger.");
       command("smile stubbornly");
       return "";
   }

   command("emote puffs thoughtfully on his long-stemmed pipe.");
   command("rsay We generally don't have much to do with gods, except " +
       "Reorx.");
   command("rsay Now that you ask, there was one of the human refugees " +
       "that passed through here talking about the Old Gods. Saying " +
       "they are back or some such...");
   command("emote snorts.");
   command("rsay Anyway, ye'd probably find him with the rest of the " +
       "refugees in the valley to the southeast.");

   return "";
}