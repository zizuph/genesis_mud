inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/neidar/guild.h"

#define RUNE_ID "ansalon_rune_object"

int worn = 0;

string
query_auto_load()
{
    return MASTER_OB(TO) + ":";
}

void
init_arg(string arg)
{
}

void
create_object()
{
    set_name("rune");
    add_name("chain");
    add_adj("silver");
    set_adj("dwarven");
    add_adj("obsidian");
    add_adj("black");
    add_pname(RUNE_ID + "s");
    add_pname("dwarven runes hanging from silver chains");
    add_name(RUNE_ID);
    set_short("dwarven rune hanging from a silver chain");
    set_long("This is a carefully carved piece of black obsidian, " +
      "formed into the angular form of a dwarven rune. This particular " +
      "rune means in the ancient dwarven dialect 'dwarf friend', " +
      "and while rarely found, it is often a gift to those who have proven " +
      "to be true allies to a dwarven clan. It is believed that these " +
      "runes hold a mystical property that makes one more sensitive " +
      "to the needs of a dwarven community. A fine silver chain " +
      "runs through a hole in the top of the rune, allowing " +
      "the rune to be worn around the neck. " +
      "For those who no longer wish to keep this gift, they " +
      "may discard the rune.\n");
    add_prop(OBJ_M_NO_DROP,"You are unable to drop or give " +
      "away the dwarven rune.\n");
}

string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "You are wearing around your neck a silver " +
	"chain with a black obsidian rune hanging from it.\n";

    if (for_obj == me)
	return "You are wearing a silver chain with a " +
	"black obsidian rune hanging from it, a token from " +
	"the Neidar Clan that marks you as a dwarf friend.\n";
    else
	return C(PRONOUN(me)) + " is wearing around " +
	HIS(me)+ " neck a fine silver chain with a " +
	"black obsidian rune hanging from it.\n";
}


int
query_worn_rune()
{
    return worn;
}


int
wear(string str)
{

    int i;
    mixed oblist;

    if ( !str )
        return 0;
        
    if(query_worn_rune())
    {
	notify_fail("You are already wearing it.\n");
	return 0;
    }

    i = parse_command(str,TP,"[the] %i",oblist);
    if(i != 1 || !oblist || member_array(TO,oblist) < 0 || oblist[0] == 0)
	return 0;

    write("You wear the silver chain with the " +
      "black obsidian rune hanging from it around your neck.\n");
    say(QCTNAME(TP)+ " wears a silver chain around " +HIS(TP)+
      " neck, adjusting the black obsidian rune hanging from " +
      "it for all to see.\n");
    TP->add_subloc("friend_of_the_clan", TO);
    set_no_show_composite(1);
    worn = 1;

    if(sizeof(oblist) > 2)
	return 0;

    return 1;
}


varargs int
remove(string str, object who = TP)
{
    int i;
    mixed oblist;

    if ( !str )
        return 0;
        
    if( !query_worn_rune() )
    {
	notify_fail("You are not wearing it.\n");
	return 0;
    }

    i = parse_command(str,who,"[the] %i",oblist);
    if(i != 1 || !oblist || member_array(TO,oblist) < 0 || oblist[0] == 0)
	return 0;

    who->catch_msg("You remove the silver chain with the " +
      "black obsidian rune hanging from it from your neck.\n");

    tell_room(E(who),QCTNAME(who)+ " removes a silver chain " +
      "with a black obsidian rune hanging from it from around " +
      HIS(who)+ " neck.\n", who);
    who->remove_subloc("friend_of_the_clan");
    set_no_show_composite(0);

    worn = 0;

    if(sizeof(oblist) > 2)
	return 0;

    return 1;
}

void
init()
{
    ::init();
    
    if( !interactive(TP) )
	return;
    
    if( TP->query_race() == "goblin" )
    {
    	set_alarm(3.0, 0.0, "destroy");
    
        if ( TP->test_bit("Ansalon", 3, 13) )
            TP->clear_bit(3, 13);
    }
    
    if( TP->query_guild_member("Dwarven Warriors of the Neidar Clan") )
    {
    	set_alarm(3.0, 0.0, "destroy");
        
        if ( TP->test_bit("Ansalon", 3, 13) )
            TP->clear_bit(3, 13);
    }

    if(!ADMIN_MANAGER->query_is_friend(TP))
    {
        ADMIN_MANAGER->add_friend(TP);
    }
    
    ADA("discard");
    ADA("wear");
    ADA("remove");
}

int
discard(string str)
{
    if(str == "rune" || str == "dwarven rune")
    {
        setuid();
        seteuid(getuid());
  
   /* The person will no longer be considered a Clan friend. 
      22.08.2003, Blizzard */
        
        if ( TP->test_bit("Ansalon", 3, 13) )
            TP->clear_bit(3, 13);

        ADMIN_MANAGER->remove_friend(TP);
  
	set_alarm(1.0,0.0,"destroy3");
	return 1;
    }
    return 0;
}

void
destroy()
{
    tell_object(E(TO), "The black obsidian rune suddenly " +
        "gets very hot! It explodes, crumbling to fine dust.\n");

    ADMIN_MANAGER->remove_friend(TP);   
    remove_object();
}

void
destroy2()
{
    tell_object(E(TO), "The two dwarven runes touch, and " +
      "suddenly merge into one!\n");

    ADMIN_MANAGER->remove_friend(TP); 
    remove_object();
}

void
destroy3()
{
    tell_object(E(TO),"Deciding you no longer wish to keep " +
        "the dwarven rune of friendship, you discard it.\n");

    ADMIN_MANAGER->remove_friend(TP); 
    remove_object();
}

void
check_dest(object ob)
{
    if ( !ob->test_bit("Ansalon", 3, 13) )
        set_alarm(2.0, 0.0, &destroy());

}

enter_env(object dest, object old)
{
    mixed oblist;
    if (dest)
    {
	oblist = FIND_STR_IN_OBJECT("all " + RUNE_ID + "s",dest);
	oblist -= ({ 0, TO });
	
	if ( oblist && sizeof(oblist) > 0 )
	    set_alarm(4.0, 0.0, &destroy2());

        set_alarm(3.0, 0.0, &check_dest(dest));
    }

    ::enter_env(dest,old);
}
