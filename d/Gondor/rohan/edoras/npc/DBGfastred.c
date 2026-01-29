#pragma strict_types

inherit "/d/Gondor/std/monster.c";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"

#define	INN	(EDORAS_DIR+"DBGstallion")

object  attacker,
       *guard = ({ });
int     n,
        atstats,
        reset_inn_alarm;

public void
create_gondor_monster() 
{
    set_living_name("DBGfastred");
    set_name("fastred");
    add_name( ({ "innkeeper", "barkeeper", "bartender", }) );
    set_race_name("human");
    set_adj( ({ "plump", "talkative", }) );

    set_long(BSN("Fastred, the innkeeper of the Sleeping " + 
    "Stallion, is a plump, talkative Rohirrim with a "+
    "cheerful expression. He seems eager to take your order."));
    default_config_npc(30 + random(20));
    set_base_stat(SS_CON,60);
    set_base_stat(SS_STR,60);
    set_skill(SS_WEP_SWORD, random(10)+40);
    set_skill(SS_DEFENCE, random(10)+40);
    set_skill(SS_PARRY, random(10)+30);
    set_alignment(100+random(100));
    set_whimpy(40);
    set_chat_time(20);
    set_act_time(30);
    add_act("close door");
    add_chat("Can I help you?");
    add_chat("Welcome to the Sleeping Stallion!");
    add_chat("My name is Fastred.");
    add_chat("What may I serve you? Wine? Whiskey? A hot meal?");
    add_chat("Perhaps you want to try our excellent pheasant?");
    add_chat("If only someone would help Funohed!");
    add_cchat("Get out of here, you thieving scoundrel!");
    add_cchat("You won't get away with this, you know!");
    add_cchat("Guards! Help!");

    set_equipment( ({ EDORAS_DIR + "obj/broadsword", 
                      EDORAS_DIR + "obj/leathcoat", }) );

}

void
attacked_by(object ob)
{
    attacker = ob;
    atstats = ob->query_average_stat();
    ::attacked_by(ob);
    command("wield sword");
    command("say You fool! Why did you attack me?");
    command("shout Help! Rohirrim, help me against this " 
        + ob->query_race_name() + "!");
}

void
reset_inn()
{
    int i, i_att;
    
    remove_alarm(reset_inn_alarm);
    i_att = 0;
    for( i = 0; i < n; i++ )
    {
        if (guard[i]->query_attack()) 
            i_att = 1;
    }
    if (i_att)
    {
        reset_inn_alarm = set_alarm(120.0, 0.0, reset_inn);
        return;
    }
    command("unlock door with key");
    ENV(TO)->change_sign(0);
    /*
    environment(TO)->remove_item("sign");
    environment(TO)->add_item("sign","The sign reads:\n" + 
  "\n   Welcome to the Sleeping Stallion!\n" + 
  "          Open day and night!\n" + 
  "          Fastred, Innkeeper\n");
  */
    command("open door");
    command("e");
    command("thank guard");
    for ( i = 0; i < n; i++ )
    {
        guard[i]->end_attack();
    }
    command("get all from corpse");
    command("get all");
    set_chat_time(20);
    set_act_time(60);
}

void
counter_offensive()
{
    int i;
    command("unlock door with key");
    command("shout Guards! Get that " + attacker->query_race_name() + "!");
    for (i = 0; i < n; i++ )
    {
        guard[i]->start_attack(); 
    }
    reset_inn_alarm = set_alarm(120.0, 0.0, reset_inn);
}

void
guard_rescue(int stat)
{
    int i;
    n = 4;
    command("shout Guards! Help! The inn has been attacked!");
    for( i = 0; i < n; i++ )
    {
        guard += ({clone_object(EDORAS_DIR + "npc/DBGinnguard")});
        guard[i]->move(environment(TO));
        say("A guard arrives running.\n");
    }
    set_alarm(20.0, 0.0, counter_offensive);
}

int
leave_inn()
{
    if(!query_attack())
        return 0;

    if (!present("_sleeping_stallion_key", TO))
        clone_object(EDORAS_DIR + "obj/inn_key")->move(TO);
    command("unlock door with key");
    command("open door");
    command("w");
    command("shout I'll get you for this! Just wait until the guard arrives!");
    command("close door");
    command("lock door with key");
    say(QCTNAME(TO) + " puts a new sign on the door.\n");
    ENV(TO)->change_sign(1, LANG_ADDART(attacker->query_nonmet_name()));
    /*
    environment(TO)->remove_item("sign");
    environment(TO)->add_item("sign","The sign reads:\n" + 
      break_string("The Sleeping Stallion is temporarily closed due to "
      + "an attack by " + LANG_ADDART(attacker->query_nonmet_name()) 
      + ".\n",50) + "Fastred, Innkeeper \n");
      */
    set_cact_time(1);
    command("shout Guards! Help! Enemies in Edoras!");
    command("shout Help! There is a killer in the inn!");
    command("shout Where are the guards? Help!");
    add_cact("shout Guards! Help! Enemies in Edoras!");
    add_cact("shout Help! There is a killer in the inn!");
    add_cact("shout Where are the guards? Help!");
    set_alarm(15.0, 0.0, &guard_rescue(atstats));
    return 1;
}

public void
run_away()
{
    object *room_inv;
    int i;
    if ( file_name(ENV()) != INN )
	return;
    command("shout Flee! Everybody flee! We have to call the guard!");
    room_inv = all_inventory(environment(TO));
    command("open door");
    for( i = 0; i < sizeof(room_inv); i++ )
    {
        if(room_inv[i]->query_name() == "Funohed")
        {
            room_inv[i]->leave_home();
        }
        else if(room_inv[i] != TO && room_inv[i]->query_npc())
        {
            room_inv[i]->command("west");
        }
    }
    command("shout This " + TP->query_race_name() + " is too strong, we need help!");
    set_alarm(2.0, 0.0, leave_inn);
}

int
query_attack_stat()
{
    return atstats;
}

object
query_attacker_name()
{
    return attacker;
}

/* solemnian prestige */
int query_knight_prestige() {return (-4);}

void
return_introduce(object pl)
{
    if ((!objectp(pl)) || (objectp(query_attack())))
        return;
    
    command("say Welcome to Edoras' finest inn!");
    command("introduce me to "+pl->query_real_name());
    return;
}

void
add_introduced(string who)
{
    object  pl = find_player(LOW(who));
    
    if ((!objectp(pl)) || (objectp(query_attack())))
        return;
    
    set_alarm(3.0, 0.0, &return_introduce(pl));
    return;
}
