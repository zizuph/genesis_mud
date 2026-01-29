// file name:  /d/Avenir/common/holm/jadestone/load_room.c
// creator(s): Lilith, June 2022
// purpose:    A pre-load room for Jadestone Doll. 
// note:       Too many logical inconsistencies with Jadestone
//             being in the Bazaar and killed/not avenged by the Union
//             whilst other NPCS are. Also, she was there from 1995-2022.
//             That is a good run.  Shaking things up a bit by making it
//             appear the Hegemon finally released her from her duty and
//             has given her free-reign on the Holm.
//
//             This room is preloaded by the domain_link.c and will set her 
//             wandering around the Park and Holm dirs.
// revisions:

# pragma strict_types

inherit "/std/room";

#define CLONE_LOG "/d/Avenir/log/jadestone_clones"

object boss;

void
reset_room()
{
    if (!boss)
    {
	    boss = clone_object("/d/Avenir/common/holm/jadestone/jadestone_holm");
        boss->move(this_object());
	    boss->equip_me();
		boss->command("south");
	    write_file(CLONE_LOG, ctime(time()) +" Jadestone cloned by load room.\n");
	}
}

void
create_room()
{
    set_short("Jadestone's load room");
    set_long("This is the room where Jadestone is pre-loaded by the "
        +"domain_link.c file. It will set her lose in the Park and "
        +"Holm areas. The exit will change each Armageddon/reload.\n "
        +"If, for some reason, you reload this room, make sure "
        +"there isn't a duplicate of Jadestone running around. "
        +"You can 'goto jadestone' if needed.\n");
   
    // This will change each Armageddon, or when the room is reloaded.
    add_exit(one_of_list(({"/d/Avenir/common/park/s_path2",
                           "/d/Avenir/common/park/e_path6",
						   "/d/Avenir/common/holm/jungle/hf1",
                           "/d/Avenir/common/holm/jungle/lf4"})), "south",0);
   
	reset_room();
}

