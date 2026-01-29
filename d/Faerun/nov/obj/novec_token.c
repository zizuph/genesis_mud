#pragma strict_types
#pragma save_binary

#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>
#include "../nov.h";

inherit "/lib/keep";
inherit "/std/object";


void
create_object()
{
    set_name("hand");
    add_name("_novec_token");
    add_adj("jet-black");
    add_adj("steel");
    set_short("jet-black steel hand");
    set_long("A jet-black steel hand. Every " +
    "council member of the Necromancers of Velsharoon is granted one of these as a token of rulership.\n");

    add_prop(OBJ_I_WEIGHT,5);
    add_prop(OBJ_I_VOLUME,5);
    add_prop(OBJ_I_VALUE,1000);
    add_prop(OBJ_M_NO_SELL,"Uhm........no.\n");
    add_prop(OBJ_M_NO_DROP,"Uhm........nay.\n");
    add_prop(OBJ_M_NO_STEAL,"You cannot seem to steal anything by that description.\n");

    setuid();
    seteuid(getuid());
}


void
enter_env(object env, object from)
{
     ::enter_env(env, from);
    
     
     
     
   /*  if (this_player()->query_guild_name_lay() != GUILDNAME)
     {
     	write("The "+short()+" magically fades away!\n");
     	 set_alarm(0.0, 0.0, remove_object);
     	return;
     }*/
     
     if (this_player()->query_name("tilorop"))
     {
     	write("Ho ho Tilorop!\n");
     	return;
     }

     
     if (!this_player()->query_skill(COUNCIL))
     {
     	write("The "+short()+" magically fades away!\n");
     	 set_alarm(0.0, 0.0, remove_object);
     	return;
     }


     if (sizeof(filter(all_inventory(env),&->id("_novec_token")) - ({ this_object() }))) 
     {
     // One is enough.
     set_alarm(0.0, 0.0, remove_object);
     return;
     }
   
     

}

void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    
}

int
do_nleave(string str)
{
	
	
	if (str != "council")
	{
		write("Leave council, perhaps?\n");
		return 1;
	}
	
    
       if (this_player()->query_guild_name_lay() != GUILDNAME)
       {
        write("You are not a member of the Necromancers of Velsharoon.\n");
        return 1;
       }

       
       if (!this_player()->query_skill(COUNCIL) <= 1)
       {
       	write("You are not a memnber of the Necromancer council.\n");
       	return 1;
       }
       
       tell_object(this_player(),"You step down from the Necromancer council!\n");
       this_player()->remove_skill(COUNCIL);
       write("The "+short()+" magically fades away!\n");
       set_alarm(0.0, 0.0, remove_object);
       return 1;
}

int
do_npunish(string str)
{
	object me;
	
	if (!str)
	{
		write("Punish what member for disobedience?\n");
		return 1;
	}
	
	 me = find_player(str);
    
       if (me->query_guild_name_lay() != GUILDNAME)
       {
        write("That person is not a member of the Necromancers of Velsharoon.\n");
        return 1;
       }

    
       if(!objectp(me))
       {
        write("That person is not present in the realm.\n");
        return 1;
       }

       if (me->query_skill(PUNISHED))
       {
       	write("That member is punished already.\n");
       	return 1;
       }
       
       tell_object(me,"You have been punished by "+this_player()->query_name()+"! You " +
       "are now in disfavour of the Necromancer council!\nThe spells of Velsharoon will not " +
       "be accessible for you unless you are pardoned by the Necromancer council of Velsharoon.");
       write("You punish "+me->query_name()+"!\n"+me->query_name()+" looses the priviliege of " +
       "the spells of Velsharoon!");
       me->set_skill(PUNISHED, 1);
       return 1;
}

int
do_npardon(string str)
{
	object me;
	
	if (!str)
	{
		write("Lift the punishment on what member?\n");
		return 1;
	}
	
       me = find_player(str);
    
       if (me->query_guild_name_lay() != GUILDNAME)
       {
        write("That person is not a member of the Necromancers of Velsharoon.\n");
        return 1;
       }

    
       if(!objectp(me))
       {
        write("That person is not present in the realm.\n");
        return 1;
       }

       if (!me->query_skill(PUNISHED))
       {
       	write("That member is not pubished.\n");
       	return 1;
       }
       
       tell_object(me,"Your punishment has been lifted by "+this_player()->query_name()+"! You " +
       "may now use the spells of Velsharoon again.\n");
       write("You lift the punishment on "+me->query_name()+"!\n"+me->query_name()+" will now " +
       "be able to use the spells of Velsharoon again.");
       me->remove_skill(PUNISHED);
       return 1;
}



int
do_ndemote(string str)
{
	object me;
	
	if (!str)
	{
		write("Demote what council member?\n");
		return 1;
	}
	
       me = find_player(str);
    
       if (me->query_guild_name_lay() != GUILDNAME)
       {
        write("That person is not a member of the Necromancers of Velsharoon.\n");
        return 1;
       }

    
       if(!objectp(me))
       {
        write("That person is not present in the realm.\n");
        return 1;
       }
       
       if (me->query_skill(COUNCIL) == 2)
       {
       	write("The council leader of the Necromancer council have to 'nresign'.\n");
       	return 1;
       }

       if (!me->query_skill(COUNCIL) == 1)
       {
       	write("That member is not a member of the council.\n");
       	return 1;
       }
       
       tell_object(me,"You have been demoted from the Necromancer council by "+this_player()->query_name()+"!\n");
       write("You demote "+me->query_name()+" from the Necromancer council!\n");
       me->remove_skill(COUNCIL);
       
     //  write("The "+short()+" magically fades away!\n");
     //  set_alarm(0.0, 0.0, remove_object);
       return 1;
}

int
do_npromote(string str)
{
	object me;
	
	if (!str)
	{
		write("Promote whom to become a council member?\n");
		return 1;
	}
	
       me = find_player(str);
    
       if (me->query_guild_name_lay() != GUILDNAME)
       {
        write("That person is not a member of the Necromancers of Velsharoon.\n");
        return 1;
       }

    
       if(!objectp(me))
       {
        write("That person is not present in the realm.\n");
        return 1;
       }
       
       if (me->query_skill(COUNCIL) == 2)
       {
       	write("That member is the council leader already.\n");
       	return 1;
       }

       if (me->query_skill(COUNCIL) == 1)
       {
       	write("That member is already a member of the council.\n");
       	return 1;
       }
       
       tell_object(me,"You have been promoted to the Necromancer council by "+this_player()->query_name()+"!\nA "+short()+" " +
       "magically appears in your inventory.");
       write("You promote "+me->query_name()+" to the Banedead council!\n");
       me->set_skill(COUNCIL, 1);
       clone_object(NOV_DIR +"/obj/novec_token")->move(me, 1);
       return 1;
}

int
do_nleader(string str)
{
	object me;
    
       if (this_player()->query_guild_name_lay() != GUILDNAME)
       {
        write("You are not a member of the Necromancers of Velsharoon.\n");
        return 1;
       }


       if (!this_player()->query_skill(COUNCIL) == 2)
       {
       	write("You are not the Necromancer council leader.\n");
       	return 1;
       }
       
       if (!me->query_skill(COUNCIL) == 1)
       {
       	write(me->query_name()+" is not a Necromancer council member.\n");
       	return 1;
       }
       
       if (me->query_skill(COUNCIL) == 2)
       {
       	write(me->query_name()+" is already the Necromancer council leader.\n");
       	return 1;
       }
       
       
       tell_object(me,"You have been promoted to be the Necromancer council leader by "+this_player()->query_name()+"!\n");
       write("You promote "+me->query_name()+" to be the new Necromancer council leader!\n");
       me->add_skill(COUNCIL, 2);
       write("You leave the Necromancer council leader position.");
       this_player()->set_skill(COUNCIL, 1);
       return 1;
}

int
do_nexpel(string str)
{
       object me, token1, token2;	
	
       me = find_player(str);
    
       if (me->query_guild_name_lay() != GUILDNAME)
       {
        write("That person is not a member of the Necromancers of Velsharoon.\n");
        return 1;
       }
       
       if (me->query_skill(COUNCIL) == 2)
       {
        write("No, you cannot expel the council leader of the Necromancers of Velsharoon.\n");
        return 1;
       }
       
       if (me->query_skill(COUNCIL) == 1 && !this_player()->query_skill(COUNCIL) == 2)
       {
        write("Only the Necromancer council leader can expel council members.\n");
        return 1;
       }
       
       tell_object(me,"You have been expelled from the Necromancers of Velsharoon by "+this_player()->query_name()+"!\n");
       write("You expel "+me->query_name()+" from the Necromancers of Velsharoon!\n");
       me->remove_skill(ABILITY1);
       me->remove_skill(ABILITY2);
       me->remove_skill(COUNCIL);
       me->remove_skill(PUNISHED);
       me->remove_guild_lay();
       me->clear_guild_stat(SS_LAYMAN);
       me->remove_cmdsoul(NOV_DIR +"souls/banedead_soul");
       NOV_MANAGER->remove_nov_member(me->query_name());
       me->update_hooks();
   
   if (present("_novtoken", me))
    {
    	token1 = "_novtoken"->query_short();
    	
        me->catch_msg("The "+token1+" vanishes into thin air.\n");
        "_novtoken"->remove_object();
    }
    
    if (present("_novec_token", me))
    {
    	token2 = "_novec_token"->query_short();
    	
        me->catch_msg("The "+token2+" magically disappear.\n");
        "_novec_token"->remove_object();
    }
       return 1;
}

int
do_naccept(string str)
{
        object me, shadow;
        
        me = find_player(str);
	
       if (!str)
       {
		write("Accept whom to join the Necromancers of Velsharoon?\n");
		return 1;
       }
	
	   
      /* if (this_player()->query_guild_name_lay() != GUILDNAME)
       {
        write("You are not a member of the Necromancers of Velsharoon.\n");
        return 1;
       }*/
       
       if(!objectp(me))
       {
        write("That person is not present in the realm.\n");
        return 1;
       }
       
       if (me->query_guild_name_lay() == GUILDNAME)
       {
        write("That person is already a member of the Necromancers of Velsharoon.\n");
        return 1;
       }

             
       if (!this_player()->query_skill(COUNCIL) >= 1)
       {
       	write("You are not a member of the Necromancer council.\n");
       	return 1;
       }
       
       
        shadow = clone_object(NOV_DIR +"shadows/nov_sh.c"); 

        if (shadow->shadow_me(me, "layman", "magic", "necromancers of Velsharoon") != 1)
        {
        write("For some reason, that person cannot join the Necromancers of Velsharoon!\n");
        return 1;
        }
       
       NOV_MANAGER->add_nov_member(me->query_name()); 
       
       
       write("You accept "+me->query_name()+" as a new member of the Necromancers " +
       "of Velsharoon!\n");
       tell_object(me,"Congratulations! You are accepted as a member of the " +
       "Necromancers of Velsharoon by "+this_player()->query_name()+"!\n");
       clone_object(NOV_DIR +"obj/novtoken")->move(me);
       return 1;
}

void
init()
{
    ::init();
    
    if (this_player()->query_skill(COUNCIL) >= 1)
    {
    	add_action(do_npunish, "npunish");
    	add_action(do_npardon, "npardon");
    	add_action(do_npardon, "nleave");
    	add_action(do_nexpel, "nexpel");
    	add_action(do_naccept, "naccept");
    	
    	this_object()->set_long(this_object()->long()+"\nYou have the following " +
    	"extra commands as a councilmember : npunish, npardon, nexpel and naccept.\n");
    	
    }
    
    if (this_player()->query_skill(COUNCIL) == 2)
    {
    	add_action(do_nleader, "nleader");
    	add_action(do_npromote, "npromote");
    	add_action(do_ndemote, "ndemote");
    	
    	this_object()->set_long(this_object()->long()+"\nYou have the following " +
    	"extra commands as the council leader of the Necromancers : nleader, npromote, ndemote.\n");
    }

 
}


string
query_auto_load()
{
    return NOV_DIR +"obj/novec_token"; 
}

