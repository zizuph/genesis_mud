// updated by Lilith Dec 2021: moved from Sorgum's dir to Terel/common
//    updated to Terel std room, etc
//   
//   Lilith Feb 2022:
//       -doing a resolve_unique with Benton instead of his gear.
//       -doing an 'objectp' test instead of 'present' in case he
//        gets wimpied out of the room.
//   Lilith April 2022: Got reports of multiple Bentons in the room
//       removing objectp test and just going with boss.
//   Zizuph April 2022: boss was storing the result of move(), not
//       clone_object.  This is why he having multiple bosses.
//       FIxing so the actual boss object is stored.
//   Lilith, May 2022: fixed issue with double equip_me call.
//       Made enable_reset interval ~6 hours.
//       Made room  ROOM_M_NO_HIDE. The way to get to it is 
//       through a river via a move_living. People should not
//       be able to sneak into or hide in this room :( 

/* from the imagination of Lord Sorgum ;)  */
#include "/d/Terel/include/Terel.h"
inherit MOOR_DIR +"tomb/tomb_base";
inherit "/lib/unique";
#include "../local.h"
#define BENTON_LOG      "/d/Terel/log/benton_clones"

object boss;

void
reset_room()
{
    // He should only clone 10 times each Armageddon, because the code in 
    // /d/Genesis/sys/global/unique	assumes that half of unique clones 
    // carry over from previous Arma (if I've read it correctly).
    // Cloning an npc from a room instead of an object from an npc
    // may cause some unexpected results. Logging clones to see 
    // how it goes.
	//  As of May 26 2022 he cloned 6 times in May.
    if (!boss)
    {
	string unique = resolve_unique(MOBDIR +"benton", 20);
	if (unique)
	{
	    boss = clone_object(MOBDIR +"benton");
        boss->move(TO);
	    boss->equip_me();
	    write_file(BENTON_LOG, ctime(time()) +" Benton ("+ 
	      boss->query_average_stat() +") cloned to Gore Chamber.\n");
		return;
	}
	else
	    write_file(BENTON_LOG, ctime(time()) +" resolve_unique = 0.\n");	
    }		
}	

void
create_room()
{
    ::create_room();

    add_npc(MOBDIR +"dweller4", 2);	

    set_short("Gore chamber");
    set_long("You feel as if you have stepped into a fresh Hell.\n "+
      "The room is filled with grotesque, crippled, carved up carcasses. "+
      "Bloody torsos are suspended from hooks in the ceiling by their "+
      "own intestines. The floor is littered with an upheaval of human "+
      "entrails. Chewed limbs dripping with pus and wretched chunks of "+
      "bleeding flesh are scattered everywhere. To the south is the "+
      "writhing mass of mire you swam through to get here. It is so "+
      "disgusting you have no interest in going back that way.\n"
    );

    add_item(({"carcasses", "torsos", "corpses", "limbs", "hooks"}), 
      "Decayed and shredded, corpses hang from hooks like so much "+
      "butchered meat. The most disturbing thing is " +
      "the teeth marks and nibbled look about them.\n"
    );

    add_item(({"entrails", "pus", "chunks", "intestines", "flesh"}), 
      "Don't look too closely, or you might toss your cookies.\n"
    );

    add_item(({"floor", "entrails"}), "The stone floor is covered "+
      "in blood and gore.\n"
    );

    add_item(({"ceiling", "hooks", "chains" }),
      "The ceiling arches above, dripping filth. "+
      "From it, numerous chains with hooks are suspended.\n"
    );

    add_item(({"grime", "mire", "river"}), 
      "It looks just awful, this river of grime. "+
      "Part of you wants to dive in and explore, "+
      "but some instinct is warning you that something "+
      "terrible might happen to you if you do.\n"
    );

    add_exit("grime_river", "mire", 0);
 
    // There is no hiding here. 
    add_prop(ROOM_I_HIDE, -1);  	
	
	// once every 6 hours (90 * (100/25) = 360 mins)
	// added by Lilith May 27 2022	 
	enable_reset(25);
	
    reset_room();

}
