// file name:   /d/Avenir/common/outpost/tomato_quest/tomato.c
// creator(s):  Kazz
// thanks:	Glindor showed me how to handle a good drop via leave_env()
//		instead of my do_drop()
// last update: April 1995
//		Denis, May'96: Changed the usage of tomato_misc to statserv.
// purpose:     To be dropped from the upper tower window in small quest.
// note:  	do_throw() is from common/bazaar/Obj/food/tom.c, but
//        	altered to fail for snob_elf.
// bug(s):
// ideas:       * should the target get to know who threw the tomato?
//		* move tomato_stain into anybody hit with tomato?
//		* add a random chance of the tomato not splatting
//		* check awareness & dex for not being hit or catching tomato?

# include <macros.h>
# include <stdproperties.h>
# include "/d/Avenir/common/common.h"
# include "/d/Avenir/common/outpost/outpost.h"
# include "tomato_drop.h"				// quest header
# include "/d/Avenir/smis/sys/statserv.h"

inherit "/std/object";

// the tomato-npc who cannot be hit by these tomatoes.
# define TARGET_NPC_NAME 	"Pompour"
# define TOMATO_BRAT_NAME 	"Gritor"

int do_eat(string str);
int do_throw(string str);

void create_object()
{
  set_name ("tomato");
  set_pname("tomatoes");
  set_short ("tomato");
  set_pshort ("tomatoes");
  add_name(TOMATOQ_QUEST_ID);
  set_long ("A very soft, rotten tomato.\n" );
  add_prop (OBJ_I_WEIGHT, 10);
  add_prop (OBJ_I_VOLUME, 50);
  add_prop (OBJ_I_VALUE, 5);
  seteuid(getuid());	// to allow it to clone tomato_mush
}

void init ()
{
  ::init();
  add_action (do_eat,   "eat");
  add_action (do_throw, "throw");
}

int do_eat( string str )
{
    notify_fail( "Eat what?\n" );

    if (str != "tomato")
    	return 0;

    TP->catch_msg( "The tomato is too rotten to eat.\n" );
    return 1;   
}

// copied from tomato in common/bazaar/Obj/food/tom.c
// but changed to not hit the tomato-quest npc.
int do_throw( string arg )
{
    object ob, *obs;
    mixed exits, exit, target;
    int i;

    notify_fail( "Throw what?\n" );
    
    if (!arg)
	return 0;
    
    obs = FILTER_LIVE(all_inventory(environment(this_player())));
    exits = environment(this_player())->query_exit();
    if (pointerp(exits))
	for (i=0 ; i<sizeof(exits) ; i+=3) {
	    exit = environment(this_player())->check_call(exits[i]);
	    if (stringp(exit))
		exit = find_object(exit);
	    if (objectp(exit))
		obs += FILTER_LIVE(all_inventory(exit));
	}
    
    notify_fail("Throw what at whom?\n");
    if (!parse_command(arg, obs + all_inventory(this_player()),
		       "%o 'at' %l", ob, target))
	return 0;
    if (ob != this_object())
	return 0;
    
    notify_fail("Throw " + LANG_THESHORT(this_object()) + " at whom?\n");
    if (sizeof(target) != 2 || !objectp(target[1]))
	return 0;

    // added for the tomato-quest
    if (target[1]->query_name() == TARGET_NPC_NAME) {
	this_player()->catch_msg(
	      "You throw " + LANG_ASHORT(this_object()) +
	      " at " + QTNAME(target[1]) + ", but he " +
	      "dodges it and sneers at you.\n" +
	      "He dodged it so easily, you realize this may not work.\n" );
	say(QCTNAME(this_player()) + " throws a rotten tomato at " +
		QCTNAME(target[1]) +
		", but he dodges and sneers.\n",
	    	({ target[1], this_player() }));
	STATSERV_LOG_EVENT("outpost", "Tried to tomato the snob via throwing");
	remove_object();
	return 1;
    }
    
    this_player()->catch_msg("You throw " + LANG_ASHORT(this_object()) +
			     " at " + QTNAME(target[1]) + ".\n");
    say(QCTNAME(this_player()) + " throws a rotten tomato at " +
	QCTNAME(target[1]) +
	".\n", ({ target[1], this_player() }));
    // should the target get to know who threw the tomato?
    target[1]->catch_msg("You are struck by a rotten tomato. SPLAT!!!\n");
    tell_room(environment(target[1]), QCTNAME(target[1]) + " is hit by "+
	      LANG_ASHORT(this_object()) + ".\n", target[1]);

    if (target[1]->query_name() == TOMATO_BRAT_NAME) {
	tell_room(environment(target[1]),
		  QCTNAME(target[1]) + " laughs merrily.\n");
    }
    
    seteuid(getuid());
    if (ob->move(environment(target[1]), 0))
	ob->remove_object();
    
    remove_object();
    return 1;
    
}

void replace_tomato(object this_room)
{
    object tomato_mush;

    tell_room(this_room, "The tomato bursts with a loud splat.\n");
    tomato_mush = clone_object(TOMATOQ_DIR + "tomato_mush");
    tomato_mush->move(this_room);
    remove_object();
}

// to handle splatting the tomato when dropped and
// replacing with tomato_mush 
void leave_env( object from, object to )
{
  if (living(from) && to == environment(from))
      set_alarm(0.5, 0.0, &replace_tomato(environment(from)));
  ::leave_env(from, to); 
}
