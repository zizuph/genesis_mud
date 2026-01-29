#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>
#include "../nov.h"

inherit NOV_DIR +"temple/std_room";

mapping token_spells = ([]);

public int 
blocknonmembers()
{
      
      
    
 
    
     if (this_player()->query_guild_name_lay() == GUILDNAME)
    {
        write("Welcome home, Necromancer "+this_player()->query_name()+"!\n\n");
        return 0;
    }

  
    write("Only Necromancers may go further up!\n");
        return 1;
}

 
 
void
create_nov_room()
{
                   
    set_name("In the chamber of joining");
    add_name( ({ "room", "hall", "corridor" }) );

    set_short("You stand in the initiation room in the temple of Necromantic studies.");
    set_long("You stand in the initiation room in the great temple of Necromantic studies. " +
    "Students come here to spend their days in necromantic research, seeking " +
    "to understand and expand the collective knowledge of life and death. They " +
    "will be gaining access to arcane tomes of vile dark magic. A " +
    "long scroll hangs on the wall here.\n");

    add_exit(NOV_DIR + "temple/ncentral",   "up", blocknonmembers);
    add_exit(NOV_DIR + "temple/nport",   "down");
    
    add_item(({"scroll"}),
        "Its an old scroll with alot of writings on it.\n"); 
        
    
    
    setuid();
    seteuid(getuid());
        
    
}


int
do_rsign(string str)
{
	
	
	
	if (str == "scroll")
	{
	
	
	write("    0----------------------------------0\n");
        write("    |                                  |\n");
        write("    |                                  |\n");
	write("    |         :::!~!!!!!:.             |\n");
        write("    |      .xUHWH!! !!?M88WHX:.        |\n");
        write("    |    .X*#M@$!!  !X!M$$$$$$WWx:.    |\n");
        write("    |   :!!!!!!?H! :!$!$$$$$$$$$$8X:   |\n");
        write("    |  !!~  ~:~!! :~!$!#$$$$$$$$$$8X:  |\n");
        write("    | :!~::!H!<   ~.U$X!?R$$$$$$$$MM!  |\n");
        write("    | ~!~!!!!~~ .:XW$$$U!!?$$$$$$RMM!  |\n");
        write("    |   !:~~~ .:!MmT#$$$$WX??#MRRMMM!  |\n");
        write("    |   ~?WuxiW*`   `'#$$$$8!!!!??!!!  |\n");
        write("    |     M$$$$    O  `hT#$T~!8$WUXU~  |\n");
        write("    |     ~#$$$m:        ~!~ ?$$$$$$   |\n");
        write("    |      ~T$$$$8xx.  .xWW- ~hh##*'   |\n");
        write("    |   !    ~?T#$$@@W@*?$$  O   /`    |\n");
        write("    |  !!     .:XUW$W!~ `h~:    :      |\n");
        write("    |  !H:   !WM$$$$Ti.: .!WUn+!`      |\n");
        write("    |   ?H.!u h$$$B$$$!W:U!T$$M~       |\n");
        write("    |    ?@WTWo(h*$$$W$TH$! `          |\n");
        write("    |     ?$$$B$Wu(h**$RM!             |\n");
        write("    |      ~$$$$$B$$en:``              |\n");
        write("    |        ~h##*$$$$M~               |\n");
        write("    |           wwwww                  |\n");
	write("    |                                  |\n");
	write("    |                                  |\n");
	write("    | For those who seek the Darkness  |\n");
	write("    | ===============================  |\n");
	write("    |                                  |\n");
	write("    | Hopefuls may, if they dare, to   |\n");
	write("    | 'njoin necromancers' if they     |\n");
	write("    | wish to probe into the vile      |\n");
	write("    | and uncontested darkness of      |\n");
	write("    | negative energies.               |\n");
	write("    |                                  |\n");
	write("    | Beware though, the dark          |\n");
	write("    | knowledge you may gain here is   |\n");
	write("    | entirely on your own risk, and   |\n");
	write("    | that it may never be a way back  |\n");
	write("    | once you dig too deep into the   |\n");
	write("    | forbidden.                       |\n");
	write("    |                                  |\n");
	write("    | Thus, any race and guild is      |\n");
	write("    | welcome here to study if they    |\n");
	write("    | have a dark heart, for the       |\n");
	write("    | knowledge of the forbidden       |\n");
	write("    | corrupts, and it may twist or    |\n");
	write("    | wreak your soul...Forever.       |\n");
	write("    |                                  |\n");
	write("    | Should a student decide to       |\n");
	write("    | withdraw from the opportunity to |\n");
	write("    | study the Vile Darkness,         |\n");
	write("    | 'nleave necromancers' is what    |\n");
	write("    | you must do.                     |\n");
	write("    |                                  |\n");
	write("    | Beware that every necromancer    |\n");
	write("    | must obey, follow and heed       |\n");
	write("    | a set of rules, or else the      |\n");
	write("    | High Maguses will swiftly deal   |\n");
	write("    | with those who fails to do so.   |\n");
	write("    |                                  |\n");
        write("    |                                  | \n");
        write("    0----------------------------------0 \n");
	write("\n");
	write("\n");
	
	return 1;
	
       }

     if (!str)
     {
     write("What ?\n");
     return 1;
     }

  return 0;

}


int
do_njoin(string str)
{
        object shadow;

        if (str != "necromancers")
        {
        	write("njoin necromancers, perhaps?\n");
        	return 1;
        }
        
    
        if ( (!this_player()->query_prop(NACCEPTED)) || (!this_player()->query_prop(NDIDQUEST)) )
        {
        	write("You must either be invited to join the Necromancers of Vile Darkness by " +
        	"a High Magus, or have fulfilled the access trial!\n");
        	return 1;
        }
        


        if (this_player()->query_guild_name_lay() == GUILDNAME)
       {
        write("You are already a member of the Necromancers of Vile Darkness.\n");
        return 1;
       }
       
        if (this_player()->query_guild_name_lay())
       {
        write("You are already a member of a layman guild.\n");
        return 1;
       }

     	shadow = clone_object(NOV_DIR +"shadows/nov_sh.c"); 

        if (shadow->shadow_me(this_player(), "layman", "magic", "necromancers of Vile Darkness") != 1)
        {
        write("For some reason, you cannot join the Necromancers of Vile Darkness!\n");
        return 1;
        }
       
        NOV_MANAGER->add_nov_member(this_player()->query_name()); 
       
       
       write("You join the Necromancers of Vile Darkness!\n");
       tell_object(environment(this_player()), this_player()->query_name()+" joins the " +
       "Necromancers of Vile Darkness!\n");
       clone_object(NOV_DIR +"obj/novtoken")->move(this_player());
       this_player()->remove_prop(NACCEPTED);
       this_player()->update_hooks();
       
       return 1;
}


int
do_nleave(string str)
{
	object token;
	
	if (str != "necromancers")
	{
		write("nleave necromancers, perhaps?\n");
		return 1;
	}
	
       if (this_player()->query_guild_name_lay() != GUILDNAME)
       {
        write("You are not a member of the Necromancers of Vile Darkness.\n");
        return 1;
       }

       
       write("You leave the Necromancers of Vile Darkness!\n");
       
       token_spells = restore_map(NOV_DIR +"log/token_spells");
       token_spells = m_delete(token_spells, lower_case(this_player()->query_real_name()));
       save_map(token_spells, NOV_DIR +"log/token_spells");
       
       this_player()->remove_skill(ABILITY1);
       this_player()->remove_skill(ABILITY2);
       this_player()->remove_skill(RESEARCH1);
       this_player()->remove_skill(RESEARCH2);
       this_player()->remove_skill(RESEARCH3);
       this_player()->remove_skill(COUNCIL);
       this_player()->remove_skill(PUNISHED);
       this_player()->remove_guild_lay();
       this_player()->clear_guild_stat(SS_LAYMAN);
       this_player()->remove_cmdsoul(NOV_DIR +"souls/nov_soul");
       NOV_MANAGER->remove_nov_member(this_player()->query_name());
       this_player()->update_hooks();
   
   
   
       if (objectp(token = present("_novtoken", this_player())))
       {
        write("Your "+token->query_short()+" crumbles to dust.\n");
        tell_room(environment(this_player()), "The "+token->query_short()+" of "+
            QTNAME(this_player())+" crumbles to dust.\n", this_player());
        token->remove_object();
       }

   
       
    
   
       return 1;    
}


       
void
init()
{
    ::init();   
    
      add_action(do_njoin, "njoin"); 
      add_action(do_nleave, "nleave"); 
      add_action(do_rsign, "read"); 
}
