/*
 * Cleaned up code and added hint to use beam to prop ceiling
 * Finwe, August 2017
 *
 * Added an error message if a player tries to prop the ceiling
 * but doesn't have a beam.
 * Raymundo, April 2021
 */

inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

object player_beam, room_beam, spoon;
int fallen;
int notpropped;

#define MIN_DEX 45

void
reset_room()
{
    spoon = 0;
    notpropped = 1;
    room_beam->remove_object();
    fallen = 0;
}

void
create_room()
{
    add_prop(ROOM_S_MAP_FILE, "michel_delving.txt");
    set_short("An abandoned hobbit-hole");
    set_long("This abandoned hobbit-hole looks very unsafe, and might " +
        "collapse at any moment! A pile of rubble is all there is here, " +
        "except for the shaky roof and unsure walls.\n");

   add_item(({"pile","rubble"}),
      "The pile of rubble has lots of things in it.\n");

   add_item(({"wall","walls"}),"The walls are very unstable and look in " +
        "danger of collapsing.\n");

   add_item(({"roof", "ceiling", "up"}),
        "In some places, you can see right through the roof. Hopefully it " +
        "won't fall on you. There must be a way to prop it up.\n");

   add_prop(ROOM_I_LIGHT, 1);
   add_prop(ROOM_I_INSIDE,1);
   add_prop("_obj_s_search_fun","do_search");

   add_exit(MICH_DIR + "farmrd3","south","@@check_fallen");

   reset_room();
}

void
init()
{
    ::init();
   add_action("prop","prop");
   add_action("prop","support");
   add_action("do_get_beam","get");
}

int
prop(string str)
{
    if(!str)
    {
        write("What?\n");
        return 1;
    }
    if((str != "ceiling with beam"))
    {
        write("Prop what? The ceiling? With what?\n");
        return 1;
    }

    if (player_beam = present("_shire_door_beam_",TP))
    {
        write("You prop up the sagging ceiling with the beam.\n");
        say(QCTNAME(TP)+ " props the ceiling up with a beam.\n");
        room_beam = clone_object("/d/Shire/michel/obj/room_beam");
        player_beam->remove_object();
        room_beam->move(TO);
        notpropped = 0;
        return 1;
    }
    else
    {
        write("But you don't have a beam to prop the ceiling with!\n");
        say(QCTNAME(TP) + " looks for a way to prop the ceiling but can't find one.\n");
        return 1;
    }
}

int
do_get_beam(string str)
{
    if (!str)
        return 0;
    else if (str != "beam")
        return 0;
    else
    {
        if (room_beam = present("_shire_room_beam_",TO))
        {
            write("You carefully remove the beam.\n");
            say(QCTNAME(TP) + " carefully removes the beam.\n");
            player_beam = clone_object("/d/Shire/michel/obj/beam");
            room_beam->remove_object();
            player_beam->move(TP);
            return 1;
        }
        else
            return 0;
    }
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if(fallen)
    {
        if(!ob->query_wiz_level())
        {
            ob->catch_msg("As you step in the abandoned hole, you notice " +
                "it has fallen in and you wouldn't get out if you " +
                "managed to enter it.\n");
            ob->move(from);
            return;
        }
        ob->catch_msg("This room is designed to be a trap. If a player " +
            "is stuck in here, do not trans them out. They must take their " +
        "chances on escaping the normal way. This is part of a quest. " +
        "Do not interfere!\nDunstable\n");
    }
}

int
check_fallen()
{
    int ran = random(100);

    if(fallen)
    {
        if(ran > 50)  /* 50/50 chance of making it */
        {
            write("As you struggle to leave the fallen in hole, the roof "+
                "trembles again!\n");
            set_alarm(4.0,0.0,"collapse",TP);
            return 1;
        }
    }
return 0;
}


int
collapse(object player)
{
    if(!present(player, this_object()))  /* Escaped! */
    {
        player = 0;
        return 1;
    }

    player->catch_msg("The earthen roof comes crashing in on you!\n");
    fallen = 1;

    player->heal_hp(-30000);
    player->catch_msg("You slowly asphyxiate as the hobbit hole collapses " +
        "in on you.\n");
    say(QCTNAME(player) + " has a large section of room fall on top of " +
        HIM_HER(player) + "!\n" + capitalize(HE_SHE(player)) + " is crushed!\n");
    player->do_die(this_object());
    return 1;
}



int
falling(object player)
{
// Let's give everyone equal time to get out. Everyone has 30 seconds
// or they die - Finwe, August 2017
/*
    int ran;
    ran = random(100);
    if(ran > 75)
    {
        set_alarm(10.5,0.0,"collapse",player);
        tell_room(TO, "A loud rumbling sound comes from above.\n"+
            "Dirt, rocks, and debris start falling down on you as the " +
            "hole begins to collapse on you.\n" +
            "It might be a good idea to get out of here before it's " +
            "too late.\n");
      return 1;
   }

   if(ran > 50)
      {
      set_alarm(20.0,0.0,"collapse",player);
      tell_room(TO,"A very loud rumbling sound comes from above.\n"+
      "Dirt, rocks, and debris start falling down on you as the " +
        "hole begins to collapse on you.\n" +
      "It might be a good idea to get out of here before it's " +
        "too late.\n");
      return 1;
   }

   if(ran > 25)
      {
      set_alarm(30.0,0.0,"collapse",player);
      tell_room(TO,"You hear a great rumbling coming from above.\n" +
      "Dirt, rocks, and debris start falling down on you as the " +
        "hole begins to collapse on you.\n" +
      "It might be a good idea to get out of here before it's " +
        "too late.\n");
      return 1;
   }

   if(ran > 0)
      {
      return 1;
   }
*/

    set_alarm(30.0,0.0,"collapse",player);
    tell_room(TO,"You hear a great rumbling coming from above.\n" +
        "Dirt, rocks, and debris start falling down on you as the " +
        "hole begins to collapse on you.\n" +
        "It might be a good idea to get out of here before it's " +
        "too late.\n" + 
        "Too bad the ceiling wasn't taken care of.\n");
      return 1;
}



string
do_search(object searcher, string str)
{
    int dexterity;

    dexterity = searcher->query_stat(SS_DEX);
//
//    if(dexterity < MIN_DEX + random(MIN_DEX))
//    {
//        if(notpropped)
//        {
//            set_alarm(0.3,0.0,"falling",TP);
//            return 0;
//        }
//        return 0;
//    }

    if(notpropped)
    {
        if(dexterity < MIN_DEX + random(MIN_DEX))
        {
            searcher->catch_msg("You're not dextrous enough to search the rubble here, but who knows what will happen!!!\n\n");
        }
        searcher->catch_msg("While you were searching the rubble, you " +
            "accidentally bumped the walls, causing them to shudder ...\n\n");
        set_alarm(0.3,0.0,"falling",TP);
        return 0;
    }



    if(!str || (str!= "rubble" && str != "pile")) 
        return 0;

    if(spoon) 
        return 0;

    seteuid(getuid(TO));
    spoon = clone_object(MICH_DIR + "obj/spoon");
    spoon->move(searcher,1);
    say(QCTNAME(searcher)+ " finds something in the rubble.\n");
    searcher->add_prop("_i_got_the_mixing_spoon_",1);
    return "You get a "+spoon->short()+" from the rubble.\n";
}
