/*
* STS Room 7
* Created by Leia
* May 30, 2005
*/

/*
** Last Updated By:
** Leia
** July 1, 2005
*/

#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <cmdparse.h>

inherit SQUARE_BASE;

object goblin;
string str;
object mix;

void
reset_solace_room()
{
    if(!goblin)
    {
        goblin = clone_object(ZAHRTOK);
        goblin->move(TO);
    }
}

void
create_solace_room()
{
    set_add_trees();
    add_item(({"buildings"}), "You observe several buildings in varying states of ill-repair. One of them seems a bit more demolished than the others.\n");
    add_item(({"building"}), "This building is almost completely leveled. The walls stand only a couple of feet tall and many beams lay splintered and burnt around them.\n");
    add_item(({"walls", "wall"}), "The walls stand only a couple of feet tall and look as though something large broke them apart. In front of one of the walls stands a new looking sign.\n");
    add_item(({"beam", "beams"}), "Most of the beams are broken in half and splintered. The beams also appear to be severely burnt by some massive source of fire.\n");
    add_item(({"sign"}), "The sign reads: Solace General Store has a new location! Visit us in the treetops!\n");
    add_exit(NORTHSTS7, "north");
    add_exit(SOUTHSTS7, "south");
    add_exit(EASTSTS7, "east");
    add_exit(ROOM6, "west");
    add_exit(NESTS7, "northeast");
    add_exit(SESTS7, "southeast");
    add_exit(SWSTS7, "southwest");
    reset_solace_room();
}

void
prepare_mix(object player, int stage)
{
    float time;
    
    set_this_player(player);
    switch(stage)
    {
        case 1:
            if(goblin)
            {
                goblin->command("emote pulls a sack from out of his pants.");
                time = 3.5;
            }
            break;
        case 2:
            if(goblin)
            {
                goblin->command("emote scoops a bunch of dirt off the ground and dumps it into the sack."); 
                time = 3.5;
            }
            break;
        case 3:
            if(goblin)
            {
                goblin->command("emote puts some herbs into the sack and begins to shake it.");
                time = 3.5;
            }
            break;
        case 4:
            if(goblin)
            {
                goblin->command("emote puts some animal dung into the sack and continues to shake it.");
                time = 3.5;
            }
            break;
        case 5:
            if(goblin)
            { 
                goblin->command("emote dumps the beer into the sack and the combination of dirt, herbs, and dung soaks it up.");
                time = 3.5;
            } 
            break;
        case 6:
            if(goblin)
            {
                goblin->command("say Here, dump into fountain. Now it be dirty good.");
                time = 3.5;
            }
            break;
        default:
            if(goblin)
            {             
                write("The slave driver hands you a mix of dirtying.\n");
                say("The slave driver hands " +QTNAME(TP)+ " a mix of some sorts.\n");
             
                if(!present(M_NAME, this_player()))
                {
                    mix = clone_object(MIX);
                    mix->move(player);
                }
        
                else
                    write("You already have a mix of dirtying.\n");
            }
            
            return;
    }
    
    set_alarm(time, 0.0, &prepare_mix(player, ++stage));
}            

int
check_props()
{
    if(TP->query_prop(OFF_DUNG) & TP->query_prop(OFF_BEER) & TP->query_prop(OFF_CRO) & TP->query_prop(OFF_CUR) & TP->query_prop(OFF_POI))
    {
        goblin->command("say Now me make the dirty stuff.");
        set_alarm(5.0,0.0, &prepare_mix(TP, 1));
        return 1;
     }
     
     else
         return 1;
}

void
init()
{
    ::init();
    add_action("determine_item", "offer");
}

int
determine_item(string str)
{
    int s;
    mixed * item;
    str = lower_case(str);
    
    if(!present("zahrtok", this_object()))
    {
        write("Who do you suppose you would offer it to?\n");
        return 1;
    }
    
    if(TP->test_bit("krynn", GROUP, G_BIT))
    {
        goblin->command("say Get away. You help stupid shaman. Me git whip!");
        return 1;
    }
    
    if(TP->test_bit("krynn", GROUP, E_BIT))
    {
        write("The slave driver shakes his head at your offering because you have already completed this task for him.\n");
        return 1;
    }

    if(!strlen(str))
    {
        write("Offer what?\n");
        return 1;
    }
    
    if(!parse_command(str, all_inventory(this_player()), "[the] %i", item))
    {
        write("Offer what?\n");
        return 1;
    }
    
    item = NORMAL_ACCESS(item, 0, 0);
    s = sizeof(item);
    
    if (s > 1)
    {
	    write("You can only offer one item at a time.\n");
	    return 1;
    }

    if (!s)
    {
	    write("Offer what?\n");
	    return 1;
    }

    if(item[0]->query_name() == D_NAME)
    {
        if(TP->query_prop(OFF_DUNG))
        {
            write("You have already supplied the dung.\n");
            return 1;
        }
        
        else
        {
            goblin->command("say Done good!");
            item[0]->remove_object();
            TP->add_prop(OFF_DUNG, 1);
            check_props();
            return 1;
        }
    }
    
    if(item[0]->query_name() == B_NAME)
    {
        if(TP->query_prop(OFF_BEER))
        {
            write("You have already supplied the beer.\n");
            return 1;
        }
        
        else
        {
            goblin->command("say Done good!");
            item[0]->remove_object();
            TP->add_prop(OFF_BEER, 1);
            check_props();
            return 1;
        }
    }
    
    if(item[0]->query_herb_name() == "crocus")
    {
        if(TP->query_prop(OFF_CRO))
        {
            write("You have already supplied the crocus.\n");
            return 1;
        }
        
        else
        {
            goblin->command("say Done good!");
            item[0]->remove_object();
            TP->add_prop(OFF_CRO, 1);
            check_props();
            return 1;
        }
    }
    
    if(item[0]->query_herb_name() == "black currant")
    {
        if(TP->query_prop(OFF_CUR))
        {
            write("You have already supplied the black currant.\n");
            return 1;
        }
        
        else
        {
            goblin->command("say Done good!");
            item[0]->remove_object();
            TP->add_prop(OFF_CUR, 1);
            check_props();
            return 1;
        }
    }
    
    if(item[0]->query_herb_name() == "poison ivy")
    {
        if(TP->query_prop(OFF_POI))
        {
            write("You have already supplied the poison ivy.\n");
            return 1;
        }
        
        else
        {
            goblin->command("say Done good!");
            item[0]->remove_object();
            TP->add_prop(OFF_POI, 1);
            check_props();
            return 1;
        }
    }
    
    else
    {
        write("Sorry, but that is not one of the required items.\n");
        return 1;
    }
}
