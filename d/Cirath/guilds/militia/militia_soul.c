/*
* Created by: Luther
* Date: Dec 2001
*
* File: /d/Cirath/guilds/militia/militia_soul.c
* Comments: Militia Soul
*/

#pragma save_binary
#pragma strict_types

inherit "/cmd/std/command_driver";
#include "m_shield.c"
#include <stdproperties.h>
#include <macros.h>
#include <tasks.h>
#include <ss_types.h>
#include <wa_types.h>
#include <formulas.h>
#include <cmdparse.h>
#include <language.h>
#include <composite.h>
#include <options.h>
#include <std.h>
#include <filter_funs.h>
#include "defs.h"
#include <files.h>
#include <adverbs.h>
#define BALDRIC "_militia_baldric_"

string
get_soul_id()
{
    return MILITIA_GUILD_NAME;
}

int
query_cmd_soul()
{
    return 1;
}

// Commands start here.........

int
mhelp(string str)
{
    string filename;

    if(!str)
	str="help";   

    filename = MILITIA_HELP + str;
    if(file_size(filename) > 0)
    {
	setuid();
	seteuid(getuid());
	cat(filename);
	write("\n");
	return 1;
    }

    NF("No help available on that subject.\n");
    return 0;
}

int
mleave(string str)
{
    object tp = this_player();
      object baldric;
    
    if (!objectp(tp))
         return 0;

    if (str != "militia")
    {
        notify_fail("The correct syntax is 'mleave militia'.\n");
        return 0;
    }

    if (!IS_TYR_MILITIA(tp)) 
    {
        notify_fail("You are not in the militia!\n");
        return 0;
    }

    if (!tp->query_prop(MILITIA_I_CONFIRM_LEAVE)) 
    {
        write("Type the 'mleave militia' command again to confirm.\n");
        tp->add_prop(MILITIA_I_CONFIRM_LEAVE, 1);
        return 1;
    }
   
    setuid();
    seteuid(getuid());
    tp->remove_layman_member();
    TP->remove_skill(142004);
    TP->remove_skill(142005);
    write("You decide to leave the Militia!\n");
    say(QCTNAME(TP) + " leaves the Militia!\n");
    write_file(MILITIA_LEAVE,TP->query_name() + " left the "
       +"Tyrian Militia.\n");
    tp->remove_prop(MILITIA_I_CONFIRM_LEAVE);

    if (tp->query_default_start_location() == (MILITIA_ROOM + "startroom"))
    {
       if (tp->set_default_start_location(tp->query_def_start()))
        {
   write("You will no longer begin your travels from within the "
            +"halls of the Tyrian Militia.  Instead, you will start from "
+"your race's standard location.\n");
        }
    }


    while(objectp(baldric = present(BALDRIC, ({ TP }) + deep_inventory(TP))))
    {
        baldric->remove_object();
    }

    return 1; 
}

int
mlist()
{
    mixed list;

    list = filter(users(),&operator(==)(MILITIA_GUILD_NAME) @
        &->query_guild_name_lay());
    list = filter(list, &operator(!=)(100) @ &->query_invis());
    list = sort_array(map(list, &->query_presentation()));  
    list = implode(map(list, &operator(+)("- ",)), "\n");  

    this_player()->more("The following Militia are currently playing:\n"+
                        list + "\n"); 
    return 1;
}

int
mspear(string str)
{
    object ob, *obj, *oblist;
    string how;

    if(member_array(W_POLEARM, TP->query_weapon(-1)->query_wt()) < 0 )
    	{
		NF("You have no weapon wielded! You can not do that!\n");
		return 0;
    	}
    	
    /* What are we attacking anyway? */
    if (strlen(str))
    {
	if (!sizeof(obj = parse_this(str, "[the] %l")))
	{
	    notify_fail("Choose a more appropriate target.\n");
	    return 0;
	}
	ob = obj[0];
    }
    /* if the player doesn't specify a target, we assume the player's
     * current enemy.
     */
    else if (!(ob = this_player()->query_attack()))
    {
	notify_fail("But you are not in battle with anyone!\n");
	return 0;
    }
    
    /* A good aligned guild, therefor you lose ability to spear
       if you are evil aligned */
    if(TP->query_alignment() < -100)
    {
	write("The nobles prefer you not kill the innocent!\n");
	return 1;
    }

    /* Is the attacker already busy? */
    if(TP->query_spear())
    {
	write("Patience! You have not yet recovered from your " +
	  "last attack!\n");
	return 1;
    }   
    
    /* Are we even allowed to attack it?  Use can_attack_with_layman_special(),
     * which is defined in m_spear.h, to find out.
     */
    if (stringp(how = this_player()->can_attack_with_layman_special(ob, "spear")))
    {
	write(how);
	return 1;
    }

    /* The m_spear.h takes care of the rest */
    this_player()->spear(ob);

    return 1;
}

// Commands stop here........

// Emotes start here.......

int
mchange(string str)
{
	string weapon_short;
	object tp = this_player(), *oblist;	
	
	if(member_array(W_POLEARM, tp->query_weapon(-1)->query_wt()) < 0 )
    	{
		NF("You have no polearm to change grip.\n");
		return 0;
    	} 
    	else
    	{
	weapon_short = tp->query_weapon(-1)[0]->short();
	
    	write("You subtly change your grip upon the " + weapon_short + 
    		" in preperation to use it.\n");     
        allbb(" subtly changes " + HIS_HER(TP) + " grip upon the " + weapon_short + 
        	" in preperation to use it."); 
        return 1;    
	}	
}

int
mcircle(string str)
{
	string shield_short;
	object tp = this_player(), *oblist, obj;	
		
	if(member_array(A_SHIELD, tp->query_armour(-1)->query_at()) < 0)
    	{
		NF("You can not circle someone without a shield.\n");
		return 0;
    	}
	
	oblist = parse_this(str, "[the] %l");
    	if (!sizeof(oblist))
    	{
		NF("Circle who?\n");
		return 0;
    	}
	
	if(tp->query_armour(W_RIGHT)->query_at() == A_SHIELD)
    	{
		shield_short = tp->query_armour(W_RIGHT)->short();
    	}
    	else if(tp->query_armour(W_LEFT)->query_at() == A_SHIELD)
    	{
		shield_short = tp->query_armour(W_LEFT)->short();
    	}
    	
	obj = oblist[0];
	actor("You circle around", oblist,", " + shield_short + " kept between you " +
		"and " + HIM_HER(obj) + " as you search for an opening in " + 
		HIS_HER(obj) + " defences.");  
        targetbb(" circles around you, " + shield_short + " kept between you and " +
      		HIM_HER(TP) + " as " + HE_SHE(TP) + " searches for an " +
      		"opening in your defences.", oblist);
      	all2actbb(" circles around", oblist, ", " + shield_short + " kept " +
      		"between them as " + HE_SHE(TP) + " searches for an opening in " +
      		HIS_HER(obj) + " defences.");
        return 1;
}

int
mcircle2(string str)
{
	string shield_short;
	object tp = this_player(), *oblist, obj;	
		
	if(member_array(A_SHIELD, tp->query_armour(-1)->query_at()) < 0)
    	{
		NF("You can not circle someone without a shield.\n");
		return 0;
    	}
	
	oblist = parse_this(str, "[the] %l");
    	if (!sizeof(oblist))
    	{
		NF("Circle who?\n");
		return 0;
    	}
	
	if(tp->query_armour(W_RIGHT)->query_at() == A_SHIELD)
    	{
		shield_short = tp->query_armour(W_RIGHT)->short();
    	}
    	else if(tp->query_armour(W_LEFT)->query_at() == A_SHIELD)
    	{
		shield_short = tp->query_armour(W_LEFT)->short();
    	}
    	
	obj = oblist[0];
	actor("You circle around", oblist," warily, keeping your " + shield_short + 
		" between you and " + HIM_HER(obj) + ".");  
        targetbb(" circles around you, warily keeping " + HIS_HER(TP) + 
      		" " + shield_short + " between " + HIM_HER(TP) + "self and you.", oblist);
      	all2actbb(" circles around", oblist, " warily, keeping " + HIS_HER(TP) + 
      		" " + shield_short + " between them.");
        return 1;
}

int
mcrouch(string str)
{
	string shield_short, weapon_short;
	object tp = this_player(), *oblist;	
	
	if(member_array(A_SHIELD, tp->query_armour(-1)->query_at()) < 0)
    	{
		NF("You cannot crouch without a worn shield!\n");
		return 0;
    	}

	if(member_array(W_POLEARM, tp->query_weapon(-1)->query_wt()) < 0 )
    	{
		NF("You cannot crouch without a wielded polearm!\n");
		return 0;
    	} 
	weapon_short = tp->query_weapon(-1)[0]->short();
	
    	if(tp->query_armour(W_RIGHT)->query_at() == A_SHIELD)
    	{
		shield_short = tp->query_armour(W_RIGHT)->short();
    	}
    	else if(tp->query_armour(W_LEFT)->query_at() == A_SHIELD)
    	{
		shield_short = tp->query_armour(W_LEFT)->short();
    	}
	    		 
        write("You crouch down behind your " + shield_short + " and prepare to " +
        	"stab any foe who gets near you with your " + weapon_short + ".\n");     
        allbb(" crouches down behind " + HIS_HER(TP) + " " + shield_short +
         	" and prepares to stab any foe who gets near " + HIM_HER(TP) + 
         	"with " + HIS_HER(TP) + " " + weapon_short + "."); 
        return 1;    
        
}

int
mdraw(string str)
{
	string weapon_short;
	object tp = this_player(), *oblist;	
	
	if(member_array(W_POLEARM, tp->query_weapon(-1)->query_wt()) < 0 )
    	{
		NF("You are not wielding a polearm to draw anyones attention.\n");
		return 0;
    	} 
    	
    	weapon_short = tp->query_weapon(-1)[0]->short();
	    	
    	if(!strlen(str))
    	{
    	write("You tap the butt of your " + weapon_short + " on the ground three times, "+
          	"drawing the attention of everyone towards you.\n");
    	all(" taps the butt of " + HIS_HER(TP) + " " + weapon_short + " on the ground three times, "+
        	"drawing your attention towards " + HIM_HER(TP) + ".");
    	return 1;
    	}
    	
    	oblist = parse_this(str, "[the] %l");
    	if (!sizeof(oblist))
    	{
		NF("Draw attention to whom?\n");
		return 0;
    	}
	
    	actor("You tap the butt of your " + weapon_short + " on the ground three times, " +
    		"drawing the attention of", oblist," towards you.");
    	target(" taps the butt of " + HIS_HER(TP) + " " + weapon_short + " on the ground three times, " +
      		"drawing your attention towards " + HIM_HER(TP) + ".", oblist);
    	all2act(" taps the butt of " + HIS_HER(TP) + " " + weapon_short + " on the ground three times, " +
    		"drawing the attention of", oblist," towards " + HIM_HER(TP) + ".");
        return 1;  	
}

int
mfondle(string str)
{
	string weapon_short;
	object tp = this_player(), *oblist;	
	
	if(member_array(W_POLEARM, tp->query_weapon(-1)->query_wt()) < 0 )
    	{
		NF("You have no polearm to fondle.\n");
		return 0;
    	} 
    	else
    	{
	weapon_short = tp->query_weapon(-1)[0]->short();
	
    	write("You fondle the shaft of your " + weapon_short + " nervously.\n");     
        allbb(" fondles the shaft of " + HIS_HER(TP) + " " + weapon_short + 
        	" nervously."); 
        return 1;    
	}	
}

int
mgreet(string str)
{
    	object *oblist;
    	string weapon_short;
    	
    	if(!strlen(str) || !sizeof(oblist = parse_this(str, "[the] %l")))
    	{
		NF("Greet whom?\n");
		return 0;
    	}

    	if (member_array(W_POLEARM, TP->query_weapon(-1)->query_wt()) < 0 )
    	{
	actor("You nod your head towards", oblist,", in an "+
          	"informal greeting.");
    	targetbb(" nods " + HIS_HER(TP) + " head towards you, in an " +
      		"informal greeting.", oblist);
    	all2actbb(" nods " + HIS_HER(TP) + " head towards", oblist,", "+
      		"in an informal greeting.");
    	return 1;
    	}
	else
	{
	weapon_short = TP->query_weapon(-1)[0]->short();
    	actor("You tip your " + weapon_short + " towards", oblist,", in a "+
          	"formal tyrian militia greeting.");
    	targetbb(" tips " + HIS_HER(TP) + " " + weapon_short + " towards you, in a " +
      		"formal tyrian militia greeting.", oblist);
    	all2actbb(" tips " + HIS_HER(TP) + " " + weapon_short + " towards", oblist,", "+
      		"in a formal tyrian militia greeting.");
    	return 1;
	}
	NF("Greet whom?\n");
	return 0;
}

int
mgrip(string str)
{
	string weapon_short;
	object tp = this_player(), *oblist;	
	
	if(member_array(W_POLEARM, tp->query_weapon(-1)->query_wt()) < 0 )
    	{
		NF("You have no polearm to grip.\n");
		return 0;
    	} 
    	else
    	{
	weapon_short = tp->query_weapon(-1)[0]->short();
	
    	write("You grip the shaft of your " + weapon_short + " tentatively.\n");     
        allbb(" grips the shaft of " + HIS_HER(TP) + " " + weapon_short + 
        	" tentatively."); 
        return 1;    
	}	
}

int
mhalt(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "commandingly", 0);

    if(!strlen(how[0]))
    {
    write("You raise your hand"+how[1]+", shouting: Halt in the name "+
          "of House Minthor!\n");
    all(" raises "+HIS_HER(TP)+ " hand"+how[1]+", shouting: Halt in the "+
        "name of House Minthor!");
    return 1;
    }

    oblist = parse_this(how[0], "[the] %l");
    if (!sizeof(oblist))
    {
	NF("Halt whom?\n");
	return 0;
    }

    actor("You raise your hand"+how[1]+" at", oblist,", shouting: "+
          "Halt in the name of House Minthor!");
    targetbb(" raises "+HIS_HER(TP)+" hand"+how[1]+" at you, shouting: " +
      "Halt in the name of House Minthor!", oblist);
    all2actbb(" raises "+HIS_HER(TP)+" hand"+how[1]+" at", oblist,", "+
      "shouting: Halt in the name of House Minthor!");
    return 1;
}

int 
minspect(string str)
{
	object *to, *oblist, ob, obj, *oblist2 = ({});
        int i;
	
	oblist = parse_this(str, "[the] %l");
    	if (!sizeof(oblist))
    	{
		NF("Inspect whom?\n");
		return 0;
    	}
	
	if (ENV(TP)->query_domain() == "Cirath")
	{
	 	obj = oblist[0];
    		to = deep_inventory(obj);    		  
    		    		
    		for(i=0; i<sizeof(to); i++)
    		{
			ob = to[i];			
	    		oblist2 += ({ ob });
    		}
    		actor("You order", oblist, " to assume the position " +
	  	"as you conduct an inspection of " + HIS_HER(obj) + 
	  	" equipment, " + HE_SHE(obj) + " is in possession of the folowing.");	
    		   		
    		for(i=0; i<sizeof(oblist2); i++)
    		{
		ob = oblist2[i];
		write("\n" + C(ob->short()));
    		}
    		if (!sizeof(oblist2))
    		{
			write("\nNo equipment.\n");
    		}
    		write("\n"); 
		target(" orders you to assume the position as " + HE_SHE(TP) +
		" conducts an inspection of your equipment.", oblist);
		all2act(" orders", oblist, " to assume the correct position " +
	  	"so " + HE_SHE(TP) + " can conduct a proper inspection of " +
	  	HIS_HER(obj) + " equipment.");
	return 1;
	}
	
	actor("You consider doing an inspection of", oblist, "'s equipment, " +
	  	"but then realize you are not in Tyr.");	
    	target(" considers doing an inspection of your equipment" +
		" but then realizes " + HE_SHE(TP) + " is not in Tyr.", oblist);
	all2act(" considers doing an inspection of", oblist, "'s equipment, " +
	  	"but then realizes " + HE_SHE(TP) + " is not in Tyr.");
	return 1;	   		
}	

int
mknuckle(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "anxiously", 0);

    if(!strlen(how[0]))
    {
    write("You crack your knuckles"+how[1]+".\n");
    all(" cracks "+HIS_HER(TP)+ " knuckles"+how[1]+".");
    return 1;
    }
   
	NF("Knuckle how?\n");
	return 0;
}

int
mlean(string str)
{
	string shield_short, weapon_short;
	object tp = this_player(), *oblist;	
		
	if (str == "shield")
	{
	if(member_array(A_SHIELD, tp->query_armour(-1)->query_at()) < 0)
    	{
		NF("You are not wearing any shield to lean on.\n");
		return 0;
    	}
	else
	{
		if(tp->query_armour(W_RIGHT)->query_at() == A_SHIELD)
    		{
		shield_short = tp->query_armour(W_RIGHT)->short();
    		}
    		else if(tp->query_armour(W_LEFT)->query_at() == A_SHIELD)
    		{
		shield_short = tp->query_armour(W_LEFT)->short();
    		}

	write("You lean on your " + shield_short + " watching your " +
         	"surroundings closely.\n");     
        allbb(" leans on " + HIS_HER(TP) + " " + shield_short + 
        	" watching " + HIS_HER(TP) + " surroundings closely."); 
        return 1;    
	}
	}
	
	if (str == "weapon")
	{
	if(member_array(W_POLEARM, tp->query_weapon(-1)->query_wt()) < 0 )
    	{
		NF("You prefer to lean on polearms.\n");
		return 0;
    	} 
    	else
    	{
	weapon_short = tp->query_weapon(-1)[0]->short();
	
    	write("You lean on your " + weapon_short + " pretending to be " +
         	"tired from this long day.\n");     
        allbb(" leans on " + HIS_HER(TP) + " " + weapon_short + 
        	" wary from the long day."); 
        return 1;    
	}
	}
        notify_fail("Lean on what?\n"); 
        return 0;	
}

int
mlower(string str)
{
	string weapon_short;
	object tp = this_player(), *oblist;	
	
	if(member_array(W_POLEARM, tp->query_weapon(-1)->query_wt()) < 0 )
    	{
		NF("You have no polearm to lower.\n");
		return 0;
    	} 
    	else
    	{
	weapon_short = tp->query_weapon(-1)[0]->short();
	
    	write("You lower your " + weapon_short + ".\n");     
        allbb(" lowers " + HIS_HER(TP) + " " + weapon_short + "."); 
        return 1;    
	}	
}

int
mplant(string str)
{
	string weapon_short;
	object tp = this_player(), *oblist;	
	
	if(member_array(W_POLEARM, tp->query_weapon(-1)->query_wt()) < 0 )
    	{
		NF("You you have no polearm to plant.\n");
		return 0;
    	} 
    	else
    	{
	weapon_short = tp->query_weapon(-1)[0]->short();
	
    	write("You plant the base of your " + weapon_short + " solidly into the " +
         	"ground in preperation to receive a charge.\n");     
        allbb(" plants the base of " + HIS_HER(TP) + " " + weapon_short + 
        	" solidly in the ground in preperation to receive a charge."); 
        return 1;    
	}	
}

int
mpolish(string str)
{
	string shield_short, weapon_short;
	object tp = this_player();
	
	if((member_array(A_SHIELD, tp->query_armour(-1)->query_at()) < 0) &&
	   (member_array(W_POLEARM, tp->query_weapon(-1)->query_wt()) < 0 ))
    	{
		NF("You have nothing present to 'mpolish'.\n");
		return 0;
    	}
	
	if (str == "weapon" && !(member_array(W_POLEARM, tp->query_weapon(-1)->query_wt()) < 0 )) 
	{ 
	 weapon_short = tp->query_weapon(-1)[0]->short();
		
         write("You start to polish your " + weapon_short + " with the scuff " +
         	"of your shirt.\n");     
         allbb(" starts to polish " + tp->query_possessive() + " " + 
         	weapon_short + " with the scuff of " + tp->query_possessive() + 
         	" shirt."); 
         return 1;
    	} 
    	
    	if (str == "shield" && !(member_array(A_SHIELD, tp->query_armour(-1)->query_at()) < 0)) 
	{
    	if(tp->query_armour(W_RIGHT)->query_at() == A_SHIELD)
    	{
		shield_short = tp->query_armour(W_RIGHT)->short();
    	}
    	else if(tp->query_armour(W_LEFT)->query_at() == A_SHIELD)
    	{
		shield_short = tp->query_armour(W_LEFT)->short();
    	}
	 write("You start to polish your " + shield_short + " with the scuff " +
         	"of your shirt.\n");     
         allbb(" starts to polish " + tp->query_possessive() + " " + 
         	shield_short + " with the scuff of " + tp->query_possessive() + 
         	" shirt."); 
         return 1;
    	} 

        notify_fail("Polish what?\n"); 
        return 0;
}

int
mtap(string str)
{
	string shield_short, weapon_short, *how = parse_adverb_with_space(str, "loudly", 0);
	object tp = this_player(), *oblist;	
	
	if(member_array(A_SHIELD, tp->query_armour(-1)->query_at()) < 0)
    	{
		NF("You cannot tap without a worn shield!\n");
		return 0;
    	}

	if(member_array(W_POLEARM, tp->query_weapon(-1)->query_wt()) < 0 )
    	{
		NF("You cannot tap without a wielded polearm!\n");
		return 0;
    	} 
	weapon_short = tp->query_weapon(-1)[0]->short();
	
    	if(tp->query_armour(W_RIGHT)->query_at() == A_SHIELD)
    	{
		shield_short = tp->query_armour(W_RIGHT)->short();
    	}
    	else if(tp->query_armour(W_LEFT)->query_at() == A_SHIELD)
    	{
		shield_short = tp->query_armour(W_LEFT)->short();
    	}

	if(!strlen(how[0]))
    	{
    		 
         write("You start to"+how[1]+" tap your " + weapon_short + " on your " +
         	shield_short + ".\n");     
         allbb(" starts to"+how[1]+" tap " + HIS_HER(TP) + " " + 
         	weapon_short + " on " + HIS_HER(TP) + " " + shield_short + "."); 
         return 1;    
        }
        notify_fail("Tap how?\n"); 
        return 0;	
}


mapping
query_cmdlist()
{
    return ([
    		//  Commands
    		"mhelp"   : "mhelp",
                "mleave"  : "mleave",    
                "mlist"	  : "mlist",
                "spear"   : "mspear",
                "interloc": "join_wall",
                "prepare" : "activate_wall",
                "stand"   : "deactivate_wall",
                "unloc"   : "leave_wall",
                "shield"  : "shield_me",
              "shieldwall": "check_wall",
                 "reset": "reset_shield",
    
    		//  Emotes    
    		"mchange" : "mchange",
    		"mcircle" : "mcircle",
    		"mcircle2": "mcircle2",
    		"mcrouch" : "mcrouch",
    		"mdraw"   : "mdraw",
    		"mfondle" : "mfondle",
    		"mgreet"  : "mgreet",
    		"mgrip"   : "mgrip",
    		"mhalt"   : "mhalt",
    		"minspect": "minspect",
    		"mknuckle": "mknuckle",
    		"mlean"   : "mlean",
		"mlower"  : "mlower",
		"mplant"  : "mplant",
		"mpolish" : "mpolish",
                "mtap" 	  : "mtap",
            ]);
}
