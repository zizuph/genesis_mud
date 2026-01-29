inherit "/std/weapon";

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <filter_funs.h>
#include <files.h>
#include <wa_types.h>






#define WEPSWORD ({"rapier", "broadsword", "longsword","cutlass",})
#define ADJSWORD ({"heavy", "sharp", "malicious", "cruel", "blunted"})
#define ADJ2SWORD ({"jagged", "blunted", "serrated"})
#define WEPNAMESWORD ({"'HONOR'","'VALOR'","'BRAZEN'","'BOLD'"})

#define WEPAXE ({"battleaxe", "handaxe", "cleaver"})
#define ADJAXE ({"heavy", "sharp", "malicious", "cruel", })
#define ADJ2AXE ({"jagged", "blunted","serrated",})
#define WEPNAMEAXE ({"'ANGER'","'RAGE'","'FURY'",})

void
create_weapon()
{
	int A;

	A = random(5);
	
    string wepsword = one_of_list(WEPSWORD);
    string adjsword = one_of_list(ADJSWORD);
    string adj2sword = one_of_list(ADJ2SWORD);
	string wepnamesword = one_of_list(WEPNAMESWORD);
	
    string wepaxe = one_of_list(WEPAXE);
    string adjaxe = one_of_list(ADJAXE);
    string adj2axe = one_of_list(ADJ2AXE);
	string wepnameaxe = one_of_list(WEPNAMEAXE);
   
   
   
	if(A < 2)
	{	
    set_name(({wepsword})); 
    add_name(({"sword"}));
    set_short(adjsword+" "+adj2sword+" "+wepsword); 
    set_long("This "+adjsword+" "+wepsword+" "+"has seen "
		    +"its way through lots of combat. It appears that you "
            +"could use its "+adj2sword+" edge to deal some damage. "
            +"Inscribed into the weapon is the word: "+wepnamesword+"\n");
	
    set_adj(({"adj"}));
    add_adj(({"adj2"}));
    set_wt(W_SWORD);           
    set_dt(W_SLASH | W_IMPALE); 
    set_hands(W_ANYH);
    set_hit(10);
    set_pen(10);
    }
	else
	{
	    string wepaxe = one_of_list(WEPAXE);
	    string adjaxe = one_of_list(ADJAXE);
	    string adj2axe = one_of_list(ADJ2AXE);
   
	    set_name(({wepaxe})); 
	    add_name(({"axe"}));
	    set_short(adjaxe+" "+adj2axe+" "+wepaxe); 
	    set_long("This "+adjaxe+" "+wepaxe+" "+"has seen its way "
	            +"through lots of combat. It appears that you "
	            +"could use its "+adj2axe+" edge to deal some damage. "
				+"Inscribed into the weapon is the word: "+wepnameaxe+"\n");
	    set_adj(({"adj"}));
	    add_adj(({"adj2"}));
	    set_wt(W_AXE);           
	    set_dt(W_SLASH | W_IMPALE); 
	    set_hands(W_ANYH);
	    set_hit(10);
	    set_pen(10);
	}

}