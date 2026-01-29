/*
 * people.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/* standard knights */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <ss_types.h>
#include <macros.h>

#define NO_OF_TYPES 6
#define ANT_WEAPONS 5
#define ANT_ARMOURS 6

int type;

/*
 * Prototypes
 */
string d_short(int no);
string d_name(int no);
string d_long(int no);
string d_adj(int no);

void
create_monster()
{
    int i;
    string str;

    set_random_move(30);
    set_pick_up(30);

    type = random(NO_OF_TYPES);
 
    set_name("human");
    set_race_name("human");
    set_living_name("human");

    if (type>4)
    {
        type = random(NO_OF_TYPES);
        
        set_short(d_short(type));
        set_long(d_long(type) + "\n");
        if ((str = d_adj(type)) != "")
            set_adj(str);
        set_alignment((50 + random(type * 40)));

        add_name(d_name(type));

        add_ask("ogion",QCTNAME(TO)+" says: Ogion lives in the forest.\n");
        add_ask("mayor",QCTNAME(TO)+" says: The mayor needs a brave hero.\n");
        add_ask("gresolle",QCTNAME(TO)+" shivers from fear.\n");
        add_ask("ged",QCTNAME(TO)+" says: Rumours has it that he moved to the dark zone.\n");
        add_ask("quest",QCTNAME(TO)+" says: There are many quests around here. Try the Mayor's office.\n");
        
        set_act_time(3);
        add_act("emote tends his armour.");
        add_act("say What are you doing here?");
        add_act("emote walks restlessly around you.");
        add_act("emote mumbles: The undead have returned to Carisca...");
        add_act("say The woodpecker knows where the healer is.");
        add_act("say The healer can cure almost all diseases.");
        set_cact_time(10);
        add_cact("laugh");
        add_cact("say Fool! You are as good as dead!\n");
    }
    else
    {
        set_alignment(-10-type*20);
        add_act("emote makes a weird sign.");
        add_act("bounce");
        add_act("emote pokes your belly.");
        set_act_time(15);
        set_cact_time(5);
        add_cact("say I'll tell Luigi about this!");

        add_name("bystander");
        add_adj("innocent");
        set_short("innocent bystander");
        set_long("This looks like one of the guys that usually frequent " +
                 "Sloppy Joe's bar.\n");
    }

    add_cact("finger all");
    add_cact("say You're dead meat!\n");

    for (i = 0; i < 6; i++)
        set_base_stat(i, 20 + type * 4 + random(type * 5));
    set_skill(SS_DEFENCE, 20 + type * 7 + random(type * 5));

    for (i = 0; i < 7; i++)
        set_skill(i, 50 + type * 5);

    NEVERKNOWN;

    set_all_attack_unarmed(20 + type * 2, 10 + type * 2);
    set_all_hitloc_unarmed(16 + type * 2);
    
    ::create_monster();

    set_restrain_path(NYREESEDIR + "cadu");
    set_monster_home(NYREESEDIR + "cadu_q5");
}

void
equip_me()
{
    object arm, wep;
    int tmp;

    seteuid(getuid(this_object()));

    tmp = (type + random(NO_OF_TYPES - 3)) / 2;
    if (tmp < 0)
        tmp = 0;
    if (tmp > ANT_WEAPONS)
        tmp = ANT_WEAPONS - 1;

    wep = clone_object(ROKEDIR + "wep/weapon");
    wep->set_up(tmp);
    wep->move(this_object());
    
    tmp = (type + random(NO_OF_TYPES - 2)) / 2;
    if (tmp < 0)
        tmp = 0;
    if (tmp > ANT_ARMOURS)
        tmp = ANT_ARMOURS - 1;

    arm = clone_object(ROKEDIR + "arm/armour");
    arm->set_up(tmp);
    arm->move(this_object());

    command("wear armour");
    command("wield weapon");
}

string
d_short(int no)
{
    string *draco_short;
  
    draco_short = ({
        "young child", "small fisherman", "young guard",
        "dirty merchant", "adventurer", "city guard",
        "smiling fisherman", "experienced knight" });

    return draco_short[no];
}

string
d_long(int no)
{
    string *draco_long;

    draco_long = ({
        "The child is playing in the streets.",
        "The fisherman smells BAD!",
        "He's trying to protect the city from pickpockets.",
        "The merchant is selling farm products.",
        "He's seeking for fame and fortune in foreign countries.",
        "The city guards are keeping law and order in Re Albi.",
        "The fisherman is headed for the inn to sell his daily catch.",
        "This knight is clearly someone you don't want to mess with."});

    return draco_long[no];
}

string
d_name(int no)
{
    string *draco_name;
    
    draco_name = ({ "child", "fisherman", "guard", "merchant", "adventurer", 
                    "guard", "fisherman", "knight" });

    return draco_name[no];
}

string
d_adj(int no)
{
    string *draco_name;

    draco_name = ({ "young", "small", "young", "dirty", "", "city",
                    "smiling", "experienced" });

    return draco_name[no];
}
