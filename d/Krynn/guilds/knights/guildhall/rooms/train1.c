/* Weapon Master Training Room. Where Knights train weapon skills. */
/* Taken from Teth's adventurer's guild and the old Keep training  */
/* Rooms. By Morrigan, Jan 97                                      */

#include <macros.h>
#include <ss_types.h>
#include "../../guild.h"

inherit TRAIN_BASE;
inherit IN_BASE;

#include "/d/Genesis/specials/debugger/debugger_tell.h"

/* Global variables */
object kn1, kn2, kn3;

void
set_up_skills()
{
    sk_add_train(SS_WEP_SWORD,  "fight with a sword",    0, 0, 90 );
    sk_add_train(SS_WEP_POLEARM,"fight with a polearm",  0, 0, 90 );
    sk_add_train(SS_WEP_CLUB,   "fight with a club",     0, 0, 90 );
    sk_add_train(SS_2H_COMBAT,  "fight with two weapons",0, 0, 75 );
    sk_add_train(SS_KATTACK, "attack an enemy", "kattack", 100, 100 );
}

public void
init()
{
    init_skill_raise();
    ::init();
}

public void
reset_vin_room()
{
    object trainer;
    
    trainer = query_guild_trainer();
    if (!objectp(trainer))
    {
        trainer = clone_object(VNPC + "marlin.c");
        set_guild_trainer(trainer);
        trainer->move(TO);
    }

    if (!kn1)
    {
    	kn1 = clone_object(NPCSTD + "vin_knight_base");
    	kn1->move(TO);
    }
    if (!kn2)
    {
    	kn2 = clone_object(NPCSTD + "vin_knight_base");
    	kn2->move(TO);
    }
    if (!kn3)
    {
    	kn3 = clone_object(NPCSTD + "vin_knight_base");
    	kn3->move(TO);
    }

}

string
long_desc()
{
    string str;
    string description = "This is where the Squires train in the arts of "+
    "warfare and battle.";

    if (!P(kn1, TO) && !P(kn2, TO) && !P(kn3, TO))
    {
	str = " There are currently no Squires or Knights training, "+
	      "a bad sign indeed!";
    }
    else
    {
	str = " The courtyard rages with Squires in mock combat, sparring "+
	      "each other, occasionally sparring the Knights who instruct "+
              "them. You see Squires using a variety of weapons. Most use "+
              "swords, but a fair amount are using the heavy maces and "+
              "halberds that Knights favour.";
    }

    if (!P(query_guild_trainer(), TO))
    {
	return description + str +" Oddly, you see no trainer here...\n";
    }

    return description + str + " "+gTrainer->query_The_name(TP)+" keeps "+
           "an eye on the Squires here, making sure no fights break out between "+
           "two angry Squires.\n";
}

public void
create_vin_room()
{
    set_short("In the Inner Courtyard of Vingaard");
    set_long("@@long_desc");

    AE(VROOM + "west_train1", "west", 0);
    AE(VROOM + "inner_court", "east",0);

    add_prop(ROOM_M_NO_TELEPORT, "The walls of Vingaard Keep prevent " +
            "teleportation in this area... or is it something else?\n");

    create_skill_raise();
    set_up_skills();

    reset_vin_room();
}

private int
query_max_skill_for_all_trainers(object player, int snum)
{
    object oldtp;
    mixed obs, otmp;
    int max_level;
    
    oldtp = this_player();
    set_this_player(player);
    
    obs = ({});
    otmp = player->query_guild_trainer_occ();
    obs += pointerp(otmp) ? otmp : ({ otmp });
    otmp = player->query_guild_trainer_race();
    obs += pointerp(otmp) ? otmp : ({ otmp });
    otmp = player->query_guild_trainer_lay();
    obs += pointerp(otmp) ? otmp : ({ otmp });
    otmp = player->query_guild_trainer_craft();
    obs += pointerp(otmp) ? otmp : ({ otmp });
    obs -= ({ 0 });
    
    // We have a list of all the trainers, now get all their skills
    max_level = 0;
    foreach (object trainer : obs)
    {
        if (max_level < trainer->sk_query_max(snum, 1))
        {
            max_level = trainer->sk_query_max(snum, 1);
        }
    }
        
    set_this_player(oldtp);
    
    return max_level;
}

public varargs int
sk_improve(string str)
{
    string skillname;    
    int improve_amt, snum, secondary, tertiary_max, tertiary_base;
    int train_success;
    
    if (!str)
    {
        return ::sk_improve(str);
    }
        
    // Knights can select a secondary weapon. However, if they
    // select a different secondary weapon, they must wait for
    // skill decay in order to allow them to train their new
    // secondary weapon choice.
    if (sscanf(str, "%s %d", skillname, improve_amt) == 2)
    {
    }
    else if (sscanf(str, "%s", skillname))
    {
        improve_amt = 1;
    }
    else
    {
        return ::sk_improve(str);
    }
    
    if (skillname != "club" && skillname != "polearm")
    {
        return ::sk_improve(str);
    }
    
    if (skillname == "club")
    {
        snum = SS_WEP_CLUB;
    }
    else if (skillname == "polearm")
    {
        snum = SS_WEP_POLEARM;
    }
    
    if (improve_amt < 0)
    {
        // We allow them to decrease their training.
        return ::sk_improve(str);
    }
        
    train_success = ::sk_improve(str);

    if (!train_success)
    {
        return train_success;
    }
    
    secondary = SKILLS_MANAGER->query_secondary_weapon_choice(this_player());
    switch (secondary)
    {
    case SS_WEP_POLEARM:
        tertiary_max = query_max_skill_for_all_trainers(this_player(), SS_WEP_CLUB);
        tertiary_base = this_player()->query_base_skill(SS_WEP_CLUB);
        if (tertiary_base > tertiary_max)
        {
            if (tertiary_base - improve_amt < tertiary_max)
            {
                this_player()->set_skill(SS_WEP_CLUB, tertiary_max);
            }
            else
            {
                this_player()->set_skill(SS_WEP_CLUB, tertiary_base - improve_amt);
            }
            this_player()->catch_tell("As you concentrate on improving "
                + "your knowledge of the use of the polearm, you find "
                + "that your new training displaces some of your "
                + "previous training in the club.\n");
        }        
        break;
    case SS_WEP_CLUB:
        tertiary_max = query_max_skill_for_all_trainers(this_player(), SS_WEP_POLEARM);
        tertiary_base = this_player()->query_base_skill(SS_WEP_POLEARM);
        if (tertiary_base > tertiary_max)
        {
            if (tertiary_base - improve_amt < tertiary_max)
            {
                this_player()->set_skill(SS_WEP_POLEARM, tertiary_max);
            }
            else
            {
                this_player()->set_skill(SS_WEP_POLEARM, tertiary_base - improve_amt);
            }
            this_player()->catch_tell("As you concentrate on improving "
                + "your knowledge of the use of the club, you find "
                + "that your new training displaces some of your "
                + "previous training in the polearm.\n");
        }            
        break;
    }    
    
    return train_success;
}
