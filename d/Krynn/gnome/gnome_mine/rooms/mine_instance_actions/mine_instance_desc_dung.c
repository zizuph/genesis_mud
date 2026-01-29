

/*
* Function name: query_descr
* Description  : The descriptors and items of the dungeons.
*/
//TODO
//all dungeon rooms should have some sort of reward aspect, that could be random
//and all dungeon rooms should have some sort of possible trap.
//so make pretty rooms and then random checks to add generic traps/rewards(with puzzles)

//TODO rewards:
/*
    //TODO awareness check -> see a special tile.
    //pressing the tile, opens a secret compartment with some loot

	//TODO awareness check -> see a lose brick.
	//pull brick out reveling some cache of loot

	//TODO awareness check -> notice simbols engraved on the wall
	//INT check, able to solve the riddle, opens compartment with loot

	//TODO WIS check -> notice what seems to be an engraving that is older than the rest
	//INT check, notice the pattern, follow the pattern to a marked brick, pull brick, cache of loot


*/
//TODO traps:
/*
    //TODO trap, coins or loot, trigger abalanche.
    //awareness check appears as if about to collapse.
    //dextirity check?
    //tunnel collapses
    //50/50 chance of instant death, if dex check fails; body stays under rubble.
    //mine yourself out or with help.


    //TODO trap arrows damage from walls.
    instances_room->add_item(({ "walls", "wall" }),
        "Small holes adorn the walls.\n");

    //TODO trap floor
    awareness check/dextirity check
    fall on the trap
    instant death(50/50)(otherwise stuck, mine yourself out, but cant dig up, so probably stuck)
    trap is one floor below, normal rock, you need to dig into it to find the body. (from outside the dungeon)
*/
//TODO monsters:
/*
	skeleton dragon for the sulfur room/treasure room
	skeleton/mummies/living corpses.... rise from the battle rooms


*/

//TODO loot items:

/*
    description by yani
    The sword is made in silver with the hilt in gold with a lot of engravings and on the edge of the 
    hilt with a shining stone (may be a ruby). In the body of the sword there were engravings pictures 
    that decribing an epic batle and in the other side the name of a man and a woman.

    the sword comes in parts, if you put them together with dragon fire(found in a brazer), 
    you reforge the sword with magical powers to control a skeleton wyrm. 
    (ride him, stomp(stun a few secs), attack)

    perhaps gaunlets instead of sword.

*/

public string       end_dungeon_search(string where, object instances_room);



void
remove_flag(object instances_room)
{
    instances_room->remove_prop("dungeon_looted");
}

void
add_flag(object instances_room)
{
    instances_room->add_prop("dungeon_looted", 1);
}

int
check_flag(object instances_room)
{
    return instances_room->query_prop("dungeon_looted");
}

public void
query_descr_dungeons(object instances_room, int specific)
{
    int z;
    string place;

    if (specific != -1)
    {
        z = specific;
    }
    else
    {
        z = random(10);        
    }

    switch(z)
    {
        case 0:
            instances_room->set_short("A narrow dungeon.");

            instances_room->set_long("Colorful tiles adorn this passage.\n");

            instances_room->set_dungeon("path");
            break;
        case 1:
            instances_room->set_short("A short dungeon.");

            instances_room->set_long("This short dungeon tunnel has a horrible aspect.\n");

            instances_room->add_item(({ "walls", "wall" }),
                "Dark and carved.\n");

            instances_room->set_dungeon("path");
            break;
        case 2:
            instances_room->set_short("A dungeon wall.");

            instances_room->set_long("Old and dusty inscriptions are all over the walls here. " +
                "On the floor, pieces of weapons and armour are scattered around.\n");

            instances_room->set_dungeon("path");
            //TODO loot on search.
            //TODO ghosts possess the armour/weapons and use them if try to loot.
            break;
        case 3:
            instances_room->set_short("A destroyed dungeon.");

            instances_room->set_long("Looks like a battle happened here long ago. Skeletons lie " +
                "on the floor still with their armours and weapons, some are even stabbing " +
                "each other motionless; on a quick glance, you can nearly imagine the end some of them suffered. " +
                "It looks like some of this equipment could be worth something.\n");

            instances_room->set_dungeon("path");

            place = "skeletons";
            instances_room->add_item(({place}),
                    "Nothing particular about it. Perhaps you should search it.\n");

            instances_room->add_delay_cmd_item( ({place}),
                    "search",
                    "searching the "+place,
                    2,
                    "You start searching the "+place+".\n",
                    &end_dungeon_search(place, instances_room));   

            //TODO loot on search.
            //TODO skeletons rise if looted.
            break;
        case 4:
            instances_room->set_short("A dungeon hall.");

            instances_room->set_long("A huge hall stands before you, with many different paths. " +
                "Some seem blocked by doors.\n");

            instances_room->set_dungeon("door");




//test
            place = "skeletons";
            instances_room->add_item(({place}),
                    "Nothing particular about it. Perhaps you should search it.\n");

            instances_room->add_delay_cmd_item( ({place}),
                    "search",
                    "searching the "+place,
                    2,
                    "You start searching the "+place+".\n",
                    &end_dungeon_search(place, instances_room)); 




            //TODO lockpick required
            //or brute force
            //actually both =)
            break;
        case 5:
            instances_room->set_short("A dungeon treasury.");

            instances_room->set_long("Riches abound here but something is amiss. The smell of sulfur suddenly " +
                "fills the room.\n");

            instances_room->set_dungeon("trsr");
            //TODO dragon arrives... treasure...
            break;
        case 6:
            instances_room->set_short("A dungeon floor.");

            instances_room->set_long("A long and narrow dungeon passage.\n");

            instances_room->add_item(({ "walls", "wall" }),
                "There are long forgotten writtings on it.\n");

            instances_room->set_dungeon("path");
            break;
        case 7:
            instances_room->set_short("A large dungeon.");

            instances_room->set_long("You cannot see the roof on this cave, probably a natural formation.\n");

            instances_room->add_item(({ "walls", "wall" }),
                "They rise out of view, into the darkness.\n");

            instances_room->set_dungeon("path");
            break;
        case 8:
            instances_room->set_short("A weird dungeon.");

            instances_room->set_long("The walls here are red, as if tainted by blood.\n");

            instances_room->add_item(({ "walls", "wall" }),
                "Crimson red.\n");

            instances_room->set_dungeon("path");
            //TODO add monster, bloody satanists revived corpses?
            break;
        case 9:
            instances_room->set_short("A dirty dungeon.");

            instances_room->set_long("Rock formations here don't seem to be human carved, more like clawed.\n");

            instances_room->add_item(({ "walls", "wall" }),
                "Clawed into form, probably by a beast.\n");

            instances_room->set_dungeon("path");
            //TODO add monster, giant mole creature?
            break;
    }
}

//TODO generalize this function, pass the end text, monsters types, etc.
public string
end_dungeon_search(string where, object instances_room)
{
    object monster;

	//set room flag
    if (check_flag(instances_room))
    {
        return "There's nothing else of interest here.\n";
    }
    else
    {
        //TODO create skeletons of the same level as the one that searches.
        //with according loot.
        add_flag(instances_room);

        monster = clone_object(NPC_DIR + "skeleton");
        monster->move(instances_room);
        tell_room(instances_room, QCTNAME(monster) + " rises.\n");

        return "As you touch the armour trying to appraise it, the skeleton grabs your hand " +
        	"and his eye sockets start to glow red; You turn to " +
        	"release yourself and notice other skeletons starting to rise as well.\n";
    }
}