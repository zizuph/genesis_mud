inherit "/cmd/std/command_driver";
#include "../nov.h";
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <tasks.h>
#include <macros.h>

#define TP this_player()
#define NF(xxx)  notify_fail(xxx)

mapping token_spells = ([]);

public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "nov"; }



public mapping
query_cmdlist()
{
    return ([
"nhelp"                             : "s_nhelp",
"nlist"                             : "noved_list",
"Betray"                            : "do_nnleave",
"npunish"                           : "do_npunish",
"npardon"                           : "do_npardon",
"nexpel"                            : "do_nexpel",
"naccept"                           : "do_naccept",
"npromote"                          : "do_npromote",
"ndemote"                           : "do_ndemote",
"nleader"                           : "do_nleader",
"nleave"                            : "do_nleave",    
"ngrab"                             : "do_ngrab",
"nvengeance"                        : "do_nvengeance",
"nstare"                            : "do_nstare",
"nunconcerned"                      : "do_nunconcerned",
"nstand"                            : "do_nstand",
"ndraw"                             : "do_ndraw",
"ntap"                              : "do_ntap",
"nscout"                            : "do_nscout",
"ncackle"                           : "do_ncackle",
"nclutch"                           : "do_nclutch",
"nscary"                            : "do_nscary",
"ngrin"                             : "do_ngrin",
"nadvice"                           : "do_nadvice",
"nadvice2"                          : "do_nadvice2",
"nconvince"                         : "do_nconvince",
"nobserve"                          : "do_nobserve",
"npdraw"                            : "do_npdraw",
"nstop"                             : "do_nstopc",
"ntitles"                           : "do_ntitles",
            ]);
}


int
do_ntitles()
{
	
       write("\n");
       write("\n");
       write("   @-----------------------------------@\n");
       write("   |                                   |\n");
       write("   | Necromancers of Velsharoon:       |\n");
       write("   | ===========================       |\n");
       write("   |                                   |\n");
       write("   | Initiate Student of Velsharoon    |\n");
       write("   | Lesser Student of Velsharoon      |\n");
       write("   | Student of Velsharoon             |\n");
       write("   | Higher Student of Velsharoon      |\n");
       write("   | Master Student of Velsharoon      |\n");
       write("   |                                   |\n");
       write("   | Lesser Arcanist of Velsharoon     |\n");
       write("   | Arcanist of Velsharoon            |\n");
       write("   | Higher Arcanist of Velsharoon     |\n");
       write("   | Master Arcanist of Velsharoon     |\n");
       write("   |                                   |\n");
       write("   | Lesser Corrupter of Velsharoon    |\n");
       write("   | Corrupter of Velsharoon           |\n");
       write("   | Higher Corrupter of Velsharoon    |\n"); 
       write("   | Master Corrupter of Velsharoon    |\n");
       write("   |                                   |\n");
       write("   | Lesser Heretic of Velsharoon      |\n");
       write("   | Heretic of Velsharoon             |\n");
       write("   | Higher Heretic of Velsharoon      |\n");
       write("   | Master Heretic of Velsharoon      |\n");
       write("   |                                   |\n");
       write("   | Lesser Defiler of Velsharoon      |\n");
       write("   | Defiler of Velsharoon             |\n");
       write("   | Higher Defiler of Velsharoon      |\n");
       write("   | Master Defiler of Velsharoon      |\n");
       write("   |                                   |\n");
       write("   | Minor Deathbringer of Velsharoon  |\n");
       write("   | Deathbringer of Velsharoon        |\n");
       write("   | Black Deathbringer of Velsharoon  |\n");
       write("   | Master Deathbringer of Velsharoon |\n");
       write("   |                                   |\n");
       write("   | Council member:                   |\n");
       write("   | ===============                   |\n");
       write("   | High Magus of Velsharoon          |\n");
       write("   |                                   |\n");
       write("   | Head of Council:                  |\n");
       write("   | ================                  |\n");
       write("   | Arch Magus of Velsharoon          |\n");
       write("   |                                   |\n");
       write("   @-----------------------------------@\n");
       write("\n");
       write("\n");



    
    
    return 1;
    
}



int
s_nhelp()
{
	
	if (this_player()->query_skill(COUNCIL) >= 1)
	{
        write("  _____________________________________\n");
	write(" |                                     |\n");
	write(" |    > Temporary Necromancer Help <   |\n");
	write(" |                                     |\n");
	write(" |   Emotes                            |\n");
	write(" |   ------                            |\n");
        write(" |   ngrab                             |\n");
        write(" |   nvengeance                        |\n");
        write(" |   nunconcerned                      |\n");
        write(" |   nstand                            |\n");
        write(" |   ndraw                             |\n");
        write(" |   ntap                              |\n");
        write(" |   nscout                            |\n");
        write(" |   ncackle                           |\n");
        write(" |   nclutch                           |\n");
        write(" |   nscary                            |\n");
        write(" |   ngrin                             |\n");
        write(" |   nadvice                           |\n");
        write(" |   nadvice2                          |\n");
        write(" |   nconvince                         |\n");
        write(" |   nobserve                          |\n");
        write(" |                                     |\n");
        write(" |                                     |\n");
        write(" |   Necromancer commands              |\n");
        write(" |   --------------------              |\n");
	write(" |   nhelp                             |\n");
	write(" |   nlist                             |\n");
	write(" |   ntitles                           |\n");
	write(" |   nstop regeneration/deathcoil      |\n");
	write(" |                                     |\n");
	write(" |                                     |\n");
	write(" |   High Magus commands               |\n");
	write(" |   -------------------               |\n");
	write(" |   npunish                           |\n");
	write(" |   npardon                           |\n");
	write(" |   nleave                            |\n");
	write(" |   nexpel                            |\n");
	write(" |   naccept                           |\n");
	write(" |                                     |\n");
	write(" |   Arch Magus commands               |\n");
	write(" |   -------------------               |\n");
	write(" |   nleader                           |\n");
	write(" |   npromote                          |\n");
	write(" |   ndemote                           |\n");
	write(" |                                     |\n");
	write(" |_____________________________________|\n");
	
	return 1;
        }

	
	write("  _____________________________________\n");
	write(" |                                     |\n");
	write(" |    > Temporary Necromancer Help <   |\n");
	write(" |                                     |\n");
	write(" |   Emotes                            |\n");
	write(" |   ------                            |\n");
        write(" |   ngrab                             |\n");
        write(" |   nvengeance                        |\n");
        write(" |   nunconcerned                      |\n");
        write(" |   nstand                            |\n");
        write(" |   ndraw                             |\n");
        write(" |   ntap                              |\n");
        write(" |   nscout                            |\n");
        write(" |   ncackle                           |\n");
        write(" |   nclutch                           |\n");
        write(" |   nscary                            |\n");
        write(" |   ngrin                             |\n");
        write(" |   nadvice                           |\n");
        write(" |   nadvice2                          |\n");
        write(" |   nconvince                         |\n");
        write(" |   nobserve                          |\n");
        write(" |                                     |\n");
        write(" |                                     |\n");
        write(" |   Necromancer commands              |\n");
        write(" |   --------------------              |\n");
	write(" |   nhelp                             |\n");
	write(" |   nlist                             |\n");
	write(" |   ntitles                           |\n");
	write(" |   nstop regeneration/deathcoil      |\n");
	write(" |                                     |\n");
	write(" |_____________________________________|\n");
	
	return 1;
}







int
do_nstopc(string str)
{
	if (str == "deathcoil")
	{
		
		if (!this_player()->query_prop(I_AM_DCOILING))
		{
			write("You dont have the deathcoil active!\n");
			return 1;
		}
		
		if (this_player()->query_prop(DCOILSTOP))
		{
			write("Yes yes, patience, Necromancer!\n");
			return 1;
		}
		
		
		write("You decide to stop the channeling spell 'deathcoil'.\n");
		this_player()->add_prop(DCOILSTOP, 1);
		return 1;
	}
	
	
	
	if (str == "regeneration")
	{
		
		if (!this_player()->query_prop(I_AM_NREGEN))
		{
			write("You dont have the regeneration active!\n");
			return 1;
		}
		
		
		if (this_player()->query_prop(REGENSTOP))
		{
			write("Yes yes, patience, Necromancer!\n");
			return 1;
		}
		
		
		write("You decide to stop the channeling spell 'regeneration'.\n");
		this_player()->add_prop(REGENSTOP, 1);
		return 1;
	}
	
	
	if (!str)
	{
		write("Nstop what spell? regeneration or deathcoil?\n");
		return 1;
	}
	
	return 1;
}



int
do_nnleave(string str)
{
     object player;
     
        if (str != "the Necromancers")
        {
        	write("'Betray the Nectromancers', perhaps?\n");
        	return 1;
        }
        

        if(this_player()->query_guild_name_lay() != GUILDNAME)
        {
        write("You are not a Necromancer of Velsharoon!\n");
        return 1;
        }

        say(QCTNAME(this_player()) + " leaves the Necromancers!\n");
        write("You leave the Nectromancers!\n");
        this_player()->leave_nguild(); 
        return 1;
}


int noved_list(string str)
{
    string *how;

    how = parse_adverb_with_space(str,".", 0);

    if (strlen(how[0])) {
        notify_fail("Try to rephrase that, if you would.\n");
        return 0;
    }


    write(NOV_MANAGER->print_nov_active());
    return 1;
}





//--------------------------------------------------------------

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

       
       if (!this_player()->query_skill(COUNCIL) >= 1)
       {
       	write("You are not a member of the Necromancer council.\n");
       	return 1;
       }
       
       tell_object(this_player(),"You step down from the Necromancer council!\n");
       this_player()->remove_skill(COUNCIL);
       //write("The "+short()+" magically fades away!\n");
      // set_alarm(0.0, 0.0, remove_object);
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
       
       tell_object(me,"You have been promoted to the Necromancer council by "+this_player()->query_name()+"!\nSomething " +
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
	
	
    
        if (!str)
	{
		write("Make whom to the new leader of the Nercromancers of Velsharoon?\n");
		return 1;
	}
       
    
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
       
       me = find_player(str);
       
       if (me->query_guild_name_lay() != GUILDNAME)
       {
        write("That person is not a member of the Necromancers of Velsharoon.\n");
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
       me->set_skill(COUNCIL, 2);
       write("You leave the Necromancer council leader position.");
       this_player()->set_skill(COUNCIL, 1);
       return 1;
}

int
do_nexpel(string str)
{
       object me, token, token2;	
	
       
    
       if (!str)
	{
		write("Expel whom from the Necromancers of Velsharoon?\n");
		return 1;
	}
    
        
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
       
       token_spells = restore_map(NOV_DIR +"log/token_spells");
       token_spells = m_delete(token_spells, lower_case(me->query_real_name()));
       save_map(token_spells, NOV_DIR +"log/token_spells");
       
       me->remove_skill(ABILITY1);
       me->remove_skill(ABILITY2);
       me->remove_skill(RESEARCH1);
       me->remove_skill(RESEARCH2);
       me->remove_skill(RESEARCH3);
       me->remove_skill(COUNCIL);
       me->remove_skill(PUNISHED);
       me->remove_guild_lay();
       me->clear_guild_stat(SS_LAYMAN);
       me->remove_cmdsoul(NOV_DIR +"souls/nov_soul");
       NOV_MANAGER->remove_nov_member(me->query_name());
       me->update_hooks();
   
       if (objectp(token = present("_novtoken", me)))
       {
        write("Your "+token->query_short()+" crumbles to dust.\n");
        tell_room(environment(me), "The "+token->query_short()+" of "+
            QTNAME(me)+" crumbles to dust.\n", me);
        token->remove_object();
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
		write("Give whom permission to join the Necromancers of Velsharoon?\n");
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

       if (me->query_prop(NACCEPTED))
       {
       	  write("You have granted "+me->query_name()+" to join already!\n");
       	  return 1;
       	}
       	
             
       if (!this_player()->query_skill(COUNCIL) >= 1)
       {
       	write("You are not a member of the Necromancer council.\n");
       	return 1;
       }
       
       write("You give "+me->query_name()+" permission to join the Necromancers " +
       "of Velsharoon!\n");
       tell_object(me,"Congratulations! You have been given permission to join the " +
       "Necromancers of Velsharoon by "+this_player()->query_name()+"!\n");
       
       me->add_prop(NACCEPTED, 1);
       
       return 1;
}

//--------------------EMOTES----------------------------------------------


do_nadvice(string str)
{
    object *oblist;

    if (!str || str == "")
    {
        NF("Advice whom?\n");
        return 0;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        NF("Advice whom?\n");
        return 0;
    }
        
    actor("You advice",oblist," to seek True Power not in life or death but " +
    "somewhere in between.");
    target(" advices you to seek True Power not in life or death but " +
    "somewhere in between.",oblist);
    all2act(" advices ",oblist," to seek True Power not in life or " +
    "death but somewhere in betveen.");
    return 1;
}


int
do_nadvice2(string str)
{
    object *oblist;

    if (!str || str == "")
    {
        NF("Advice whom?\n");
        return 0;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        NF("Advice whom?\n");
        return 0;
    }
        
        
    actor("You advice",oblist," that there is no reason to fight the " +
    "inevitable, "+oblist[0]->query_pronoun()+" might as well welcome "+oblist[0]->query_possessive()+" fate.");
    target(" advices you that there is no reason to fight the " +
    "inevitable, as you may as well welcome your fate.",oblist);
    all2act(" advices ",oblist," that there is no reason to fight the " +
    "inevitable, "+oblist[0]->query_pronoun()+" might as well welcome "+oblist[0]->query_possessive()+" fate.");
    return 1;
}




int
do_nconvince(string str)
{
    object *targ;
    NF("Convince who?\n");
    targ = parse_this(str,"[the] %l");
    if(!sizeof(targ))
        return 0;
    actor("You try to convince",targ," to take part of one of your " +
    "experiments.");
    targetbb(" tries to convince you to take a part of one " +
    "of "+this_player()->query_possessive()+" experiments.",targ);
    all2actbb(" tries to convince ",targ," to take a part of one of "+this_player()->query_possessive()+" experiments.");
    return 1;
}

int
do_nobserve(string str)
{
    object *targ;
    NF("Observe whom?\n");
    targ = parse_this(str,"[the] %l");
    if(!sizeof(targ))
        return 0;
    actor("You observe",targ," as if taking measure of "+targ[0]->query_possessive()+" body-parts " +
    "for your private collection.");
    targetbb(" observes you, as if taking measure of your body-parts " +
    "for "+this_player()->query_possessive()+" private collection.",targ);
    all2actbb(" observes ",targ," as if taking measure of "+targ[0]->query_possessive()+" body-parts " +
    "for private collection.");
    return 1;
}

int
do_ngrin(string str)
{
    object *targ;
    NF("Grin at whom?\n");
    targ = parse_this(str,"[at] %l");
    if(!sizeof(targ))
        return 0;
    actor("You grab hold of the back of your hair pulling hard, outlining the " +
    "features of your skull as you grin broadly at",targ,".");
    targetbb(" grabs hold of the back of "+this_player()->query_possessive()+" hair " +
    "pulling hard, outlining the features of "+this_player()->query_possessive()+" skull as "+this_player()->query_pronoun()+" grins " +
    "broadly at you.",targ);
    all2actbb(" grabs hold of the back of "+this_player()->query_possessive()+" hair " +
    "pulling hard, outlining the features of "+this_player()->query_possessive()+" skull as "+this_player()->query_pronoun()+" grins " +
    "broadly at",targ,".");
    return 1;
}

int
do_ngrab(string str)
{
    object *targ;
    NF("Grab whom?\n");
    targ = parse_this(str,"[the] %l");
    if(!sizeof(targ))
        return 0;
    actor("You grab",targ," angrily, forcing "+targ[0]->query_objective()+" to look straight into " +
    "your eyes, where "+targ[0]->query_pronoun()+" sees hundreds of previous victims " +
    "tortured to death by your hand.");
    targetbb(" grabs you angrily, forcing you to look straight " +
    "into "+this_player()->query_possessive()+" eyes, where you see hundreds of " +
    "previous victims tortured to death by "+this_player()->query_possessive()+" hands.",targ);
    all2actbb(" grabs",targ," angrily, staring furiously into "+targ[0]->query_possessive()+" eyes.");
    return 1;
}


int
do_nscary()
{
    write("What you just did was simply too scary.\n");
    all(" just did something that is certainly not for the children's books.\n");
    return 1;
}

int
do_nclutch()
{
    write("You clutch your hand into a grim fist, woving eternal damnation!\n");
    all(" clutches his hand into a grim fist, woving eternal damnation!\n");
    return 1;
}



int
do_ncackle()
{
    write("You throw back your head and break out in a terrifying cackle.\n");
    all(" throws back "+this_player()->query_possessive()+" head and break out in a terrifying cackle.\n");
    //(People in the room shiver)
    
    return 1;
}

int
do_nscout()
{
    write("You poke out your right eye inserting it in a skull you got from " +
    "your pocket.\nYou throw the skull up high in the air to see what lies up ahead.\n");
    all(" pokes out "+this_player()->query_possessive()+" right eye, inserting it in " +
    "a skull "+this_player()->query_pronoun()+" got from "+this_player()->query_possessive()+" pocket " +
    "and throws it up high in the air to see what lies up ahead.\n");
    return 1;
}

int
do_ntap()
{
    write("You break the silence by tapping your fingers impatiently against a skull in your pocket!\n");
    all(" breaks the silence by tapping "+this_player()->query_possessive()+" fingers " +
    "impatiently against a skull in "+this_player()->query_possessive()+" pocket!\n");
    return 1;
}



int
do_nstand()
{
    write("You stand as if completely unaffected by the situation.\n");
    all(" stands as if "+this_player()->query_pronoun()+" is completely unaffected " +
    "by the situation.\n");
    return 1;
}


int
do_ndraw()
{
    write("You draw a crowned laughing lich skull on a hexagon in the dirt.\n");
    all(" draws a crowned laughing lich skull on a hexagon in the dirt.\n");
    // will add drawing
    return 1;
}

int
do_nunconcerned()
{
    write("You are totally unconcerned with the fate of the lesser creatures.\n");
    all(" is totally unconcerned with the fate of the lesser creatures.\n");
    return 1;
}

int
do_nvengeance()
{
    write("You call out: Vengeance will be MINE! MUHAHAHAH!\n");
    all(" calls out: Vengeance will be MINE! MUHAHAHAH!\n");
    return 1;
}









