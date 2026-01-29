// file name: d/Avenir/common/outpost/cave2.c
// creator(s):  Kazz    Jan 1995
// last update: June 4 2004 Lilith: updated curse check.
//              May 28 2004 Lilith: updated infidel/enemy check
//              to allow friends to pass even if guild is banned.
// purpose:     access to the fort gate.
// note:
// to-do:  	add a knock function?
//		let a guard wander around cave now and then (3rd guard?)
//		expand western side of cavern a bit, maybe add a spring.
//		water quest: see dw_guard.c in MON directory.

#include "/d/Avenir/common/common.h"
#include "/d/Avenir/common/outpost/outpost.h"
#include "/d/Avenir/common/outpost/cave.h"

inherit "/std/room";

# include "/d/Avenir/smis/sys/statserv.h"
# include "/d/Avenir/include/relation.h"

#define WRATHOBJ  ("/d/Avenir/common/gods/obj/plalgus_hammer")
#define NPC_ROOM  ("/d/Avenir/common/outpost/tower_middle2")
#define LIST      ("/d/Avenir/union/list")
#define ENEMY(x)  (LIST->query_enemy(x))
#define FRIEND(x) (LIST->query_friend(x))
 
static object *guards = allocate(2);
static object merchant;

void
add_guards()
{
    int     i = sizeof(guards);
 
    while(i--)
    {
        if (!objectp(guards[i]))
        {
            guards[i] = clone_object(MON + "dw_guard");
            guards[i]->equip_me();
	    guards[i]->add_gate_talk();
            guards[i]->move(this_object());
        }
    }
    if (!objectp(merchant))
    {
        merchant = clone_object(MON + "food_merch");
        merchant->move(this_object());
    }

} // add_guards()



public void
reset_room()
{
      add_guards();        
}


void
create_room()
{
        object  npc_room;
    
	SHORT("Outside fort gate");
	LONG( "A black stone door looms overhead, granting entrance into the "+
	      "fort. On either side of the path burn huge, scorching pools "+
	      "of liquid. "+
	      "The path leads southwest to a wide chasm, while another "+
	      "leads northwest to a dark opening in the cavern wall.\n" );
	
	add_exit(OUTPOST + "cave1","northwest",0);
	add_exit(OUTPOST + "cave3","southwest",0);
	add_exit(OUTPOST + "fort2","east",0);

//	FORT
        add_item(({"fort", "tall fort", "black fort", "tall black fort"}),
                 "The fort is built with the blackest, smoothest "+
		 "stone and seems very solid.\n" );

//	TOWER
        add_item(({"tower", "lone tower"}), 
                 "The black tower rises high above you, providing a good "+
                 "view of the cavern.\n" );

//	GATE
        add_item(({"gate", "fort gate", "stone gate", "door"}),
                 "The black stone gate is open. It seems to provide the "+
                 "only entrance to the fort. A closed metal window is "+
		 "noticeable on either side of the door, about eight feet "+
		 "off the ground.\n");
	add_item(({"pools", "liquid", "burning liquid"}),
		 "The liquid is barely noticeable through the flame. It "+
		 "might be oil, but the flame is too hot to be sure.\n");
	add_item(({"window", "windows", "metal windows", "metal window"}),
		 "The windows probably allow guards to look out into " +
		 "the cave.\n" );

	FLAME
	CAVERN
	WALL
	PATH
	FLOOR
	ROCKS
	CHASM
	
	add_cmd_item(({"door", "stone door", "on door", "gate", "on gate"}),
		     ({"knock"}),
		     "You knock on the solid stone door, but you don't make "+
		     "much noise.\n");
	LIGHT
	IN

	reset_room();
	
	// load the tomato_quest room to get the npc's moving in the fort
        npc_room = NPC_ROOM->this_room();
	npc_room->load_me();
	if (!objectp( npc_room )) {
	    notify_fail( "The tower_middle2 room cannot be found.\n" );
 	    return 0;
	}


} // create_room()

void
do_curse(object ob)
{
    // I have entered as an infidel or enemy of the Union.
    WRATHOBJ->load_me();         
    WRATHOBJ->mark_enemy(ob);
    // if infidel but not union enemy, add to Union enemy
    // list. Its their job to clean up enemies of Sybarus.
    if (!ENEMY(ob))
        LIST->add_enemy(ob->query_real_name());
    STATSERV_LOG_EVENT("plalgus", "Entered as an enemy and was cursed");
    return;
}

void
enter_inv(object ob, object from)
{
    object curse; 
    string str;

    ::enter_inv(ob, from);
    
    if (!interactive(ob))
        return;

    if (curse = present("_hammer_of_plalgus_has_fallen", ob))
    {
        STATSERV_LOG_EVENT("plalgus", "Entered Sybarus as accursed");
        if(FRIEND(ob))
        {  
            curse->lift_judgement(10);
        }
        return;
    }

    if (IS_INFIDEL(ob) || ENEMY(ob))
    {
        if(FRIEND(ob))
        {
            ob->remove_skill(SS_INFIDEL);
            return;
        }
        else
            do_curse(ob);     
        return;
    }
    // It would be nice if this would work, but it won't
    //    str = ob->query_all_major_guilds());
    // So we will use three checks instead of one.
    // We will mark as Union enemy but not call Plalgus until
    // next time they enter.
    str = ob->query_guild_name_race();
    if (member_array(str, LIST->enemy_guilds()) != -1)
    {
        LIST->add_enemy(ob->query_real_name());
        return;
    }
    str = ob->query_guild_name_occ();          
    if (member_array(str, LIST->enemy_guilds()) != -1)
    {
        LIST->add_enemy(ob->query_real_name());
        return;
    }
    str = ob->query_guild_name_lay();
    if (member_array(str, LIST->enemy_guilds()) != -1)
    {
        LIST->add_enemy(ob->query_real_name());
        return;
    }
}

