/*
 * West bank of bruinen ford
 * Finwe, August 1998
 *
 * moved NO_CROSS_PROP to local.h to make it more global.
 * -- Finwe, feburary 2002
 *
 * Cleaned the thing up, removed Mrpr's comments, and added some
 * additional information to warn players about the dangers.
 * -- Gorboth, February 2010
 *
 * Last updated
 * -- 2010/11/29
 *
 * Fixed race detection, guild detection, added message in destination.
 * -- Lavellan, 2011/07/19
 */
#pragma save_binary
#pragma strict_types

#include "local.h"


inherit SHORE_BASE;
inherit IS_ELF_GR_TRAVELLER;

int check_player(string str);

static string  patrol_dir = "northeast";
public void    set_patrol_dir(string s) { patrol_dir = s; }
public string  query_patrol_dir(object ob) { return patrol_dir; }

void
create_shore_room()
{
    set_extraline("A large ford is to the east. " +
        "The forest surrounds you and is peaceful " +
        "here. The river flows along past you. It looks calm " +
        "but there is evidence that it overflows its banks as " +
        "there are washed up logs, sticks, and debris on the " +
        "banks here.\n");

    add_item(({"forest","oak forest","trees"}),
        "The ancient oaks look ominous and gloomy as they grow " +
        "here. They tower over you as they reach for the sky.\n");
    add_item(({"mountains", "misty mountains", "foothills"}),
        "The tops of the Misty Mountains rise up before you. " +
        "They look forbidding and dangerous as they stand in " +
        "the distance. The foothills appear sporadically " +
        "between the trees on the other side of the river.\n");
    add_item(({"path", "paths"}),
        "A path leads west back to the Great East Road.\n");
    add_item(({"river", "river bruinen", "bruinen"}),
        "The river flows east out of the mountains south here. " +
        "There is a shallow place here that allows for " +
        "travellers to enter and cross when the river is low.\n");
    add_item(({"ford", "river ford", "ford of bruinen",
        "ford of the river bruinen"}),
        "The ford is a shallow place in the river allowing " +
        "travellers to enter and cross the river into the forest " +
        "beyond. It looks " +
        "like the river would come up to the knees of an " +
        "average human. An occasional boulder stands in the river.\n");
    add_item(({"debris"}),
        "You notice broken logs and branches, sticks, leaves, " +
        "and large rocks washed up on the bank, evidence that " +
        "the river gets violent on occasion.\n");
    add_item(({"broken branches", "broken branch"}),
        "The broken branches look like they have been ripped or " +
        "broken from trees. Their ends are shattered and " +
        "splintered.\n");
    add_item(({"stump", "stumps"}),
        "You don't see any here.\n");
    add_item(({"large rocks", "large rock"}),
        "They are scattered about the banks of the river.\n");
    add_item(({"bank", "banks"}),
        "The bank is covered in short grass and gently slopes " +
        "down to the river's edge.\n");
    add_item(({"grass"}),
        "The grass is a healthy green and short. It grows all " +
        "the way to the edge of the river.\n");

    add_prop(ROOM_I_TYPE,ROOM_IN_WATER);

    reset_shire_room();

    add_exit(RIVER_DIR + "shore06", "north",0, 2);
    add_exit(RIVER_DIR + "shore05", "south",0, 2);
    add_exit(WR_DIR + "imladris_connect", "west", "@@tree_west@@", 2);

}

void
init()
{
    ::init();
    add_action("drink_it", "drink");
    add_action("check_player", "enter");
}


public void
enter_inv(object ob, object from)
{
    // Move IS_ELF_GR_TRAVELLER traveller
    string *names;
    ::enter_inv(ob, from);
    
    names = ob->query_names();

    if(ob->id(npc_name))
    { 
      if (!move_alarm || !sizeof(get_alarm(move_alarm)))
      {
         move_alarm = set_alarm(50.0 + rnd() * 20.0, 0.0, &move_patrol(ob));
      }
      return;
    }
}

int
block_river()
{
    if (this_player()->query_wiz_level())
    return 0;

    write("The river boils and churns as you enter the ford.\n"+
      "It tosses you about violently and drags you under.\n" +
      "You swim hard back to the river bank and manage to survive.\n");
    return 1;
}

void
reset_shire_room()
{

}


int check_player(string str)
{
    if ((str == "river") || (str == "ford") || (str == "bruinen"))
    {

// CAN_ENTER is defined in local.h. The routine called is
// query_allowed_enter_rivendell in rivendell/master.c
        if (CAN_ENTER(TP) || this_player()->query_wiz_level())
        {
//            TP->move_living("M", "/d/Shire/rivendell/room/river/in_ford",1);
            if (TP->query_prop("_live_o_steed"))
            {
                log_file("cross_ford", ctime(time()) +" "+ TP->query_cap_name() +
                " ("+TP->query_alignment()+") tried crossing the ford on a steed:\n");
                log_file("cross_ford", file_name(TP->query_prop_setting("_live_o_steed")) + "\n");
                TP->move_living("M", "/d/Shire/rivendell/room/river/in_ford",1);
            }
            else 
            {
               log_file("cross_ford", ctime(time()) +" "+ TP->query_cap_name() +
                " ("+TP->query_alignment()+") crossed the ford.\n");

// noldor enter ford
                //if (TP->query_guild_member_race("noldor"))
                if (IS_NOLDOR(TP))
                {
                    write("A feeling of excitement fills you as you prepare " +
                    "to return to Imladris.\n");
                }

// rangers enter ford
                //if (TP->query_guild_member_occ("ranger"))
                if (IS_RANGER(TP))
                {
                    write("Your worries seem to wash away as you prepare " +
                    "to visit Imladris.\n");
                }

                write("You head east into the ford.\n");
                say(QCTNAME(TP)+ " leaves east into the ford.\n");
                TP->move_living("M", "/d/Shire/rivendell/room/river/in_ford",1);
                tell_room("/d/Shire/rivendell/room/river/in_ford",
                    QCTNAME(TP)+ " wades in.\n", TP);
            }
            return 1;
        }

    if(!TP->query_prop(NO_CROSS_PROP))
        {
            //if (TP->query_race() == "goblin")
            if (TP->query_race_name() == "goblin")
            {
                write("\nThe river boils and churns before you,"
                  + " as if to warn you of impending doom, or"
                  + " even death, if you should enter the ford."
                  + " Something within your goblin mind stirs,"
                  + " and you can feel an ancient hatred from"
                  + " the river at your very presence here. You"
                  + " step back as you consider your options.\n\n");
            }
            else
            {
                write("\n" +
              "The river boils and churns before you, as if to " +
              "warn you of impending doom, or even death, if you " +
              "enter the ford. You step back as you consider " +
              "your options.\n\n");
            }

            say("The river boils and churns suddenly.\n");
            TP->add_prop(NO_CROSS_PROP,1);
            return 1;
        }

        write("You enter the ford to the east.\n");
        say(QCTNAME(TP)+ " leaves east into the ford.\n");
        TP->move_living("M", "/d/Shire/rivendell/room/river/in_ford",1);
        log_file("cross_ford", ctime(time()) +" "+ TP->query_cap_name() + 
        " ("+TP->query_alignment()+") crossed the ford, barred.\n");
        if (TP->query_prop("_live_o_steed"))
            log_file("cross_ford", file_name(TP->query_prop_setting("_live_o_steed")) + "\n");

        return 1;
    }

    notify_fail("Enter what, the ford?\n");

}

int drink_it(string s)
{

    int amount;

    if(s == "water" || s == "water from river")
    {
    amount = TP->query_prop(LIVE_I_MAX_DRINK) / 20;
    if (TP->drink_soft(amount))
    {
        TP->catch_msg("You kneel before the river, dipping " +
              "your cupped hands into the river and get a " +
              "drink of the clear icy water. Its taste " +
              "refreshes your mind and body.\n");

        say(QCTNAME(TP)+" kneels before the river and gets a " +
                "drink.\n");

    }
    else
    {
        write("You cannot drink more water.\n");
    }

    return 1;
    }
    else
    NF("Drink what?\n");
}

int
block_me()
{
    if (this_player()->query_wiz_level()) return 0;

    write("The river has flooded its banks, making it " +
      "impossible to cross. Eventually, though, the river " +
      "should recede and allow passage across it.\n");
    return 1;
}

void tree_west()
{
    tell_room("/d/Shire/eastroad/eastern/riv_bushes.c", QCTNAME(TP) +
    " headed west away from the river Bruinen.\n");
}
