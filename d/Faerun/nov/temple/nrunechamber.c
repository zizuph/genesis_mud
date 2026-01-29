#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include "../nov.h"

inherit NOV_DIR +"temple/std_room";

mapping token_spells = ([ ]);

 
void
create_nov_room()
{
                   
    set_name("In a large rune-covered cylindrical chamber");
    add_name( ({ "room", "hall", "corridor", "chamber" }) );

    set_short("In a large rune-covered cylindrical chamber");
    set_long("You are in a large rune-covered cylindrical chamber. The " +
    "sounds of your footsteps echo on the bare black walls, floating up " +  
    "towards the dome-shaped ceiling. You notice thousands of series of " +
    "magical runes engraved into the tar-black walls, glowing in eerie " +
    "green light which is cast on the cold floor. The depths of the domed " +
    "ceiling are lost in the dim light.\n" +
    "@@query_rune_strings@@");

    add_exit(NOV_DIR + "temple/nmagic",   "west");

}

string
query_rune_strings()
{
	string A,B,C,D,E,F,G,H,I,J,K,L,M,N;
	
	A = "";
	B = "";
        C = "";
        D = "";
	E = "";
        F = "";
        G = "";
	H = "";
        I = "";
        J = "";
	K = "";
        L = "";
        M = "";
        N = "";
	
	if (this_player()->query_prop(RUNE1))
	{
		A = "A skull-shaped rune glows fiercly.\n";
	}
	
	if (this_player()->query_prop(RUNE2))
	{
		B = "A shield-shaped rune glows fiercly.\n";
	}
	
	if (this_player()->query_prop(RUNE3))
	{
		C = "An eye-shaded rune glows fiercly\n";
	}
	
	if (this_player()->query_prop(RUNE4))
	{
		D = "A lightning-shaped rune glows fiercly.\n";
	}
	
	if (this_player()->query_prop(RUNE5))
	{
		E = "A ghost-shaped rune glows fiercly.\n";
	}
	
	if (this_player()->query_prop(RUNE6))
	{
		F = "An bird-shaped rune glows fiercly\n";
	}
	
	
	if (this_player()->query_prop(RUNE7))
	{
		G = "A pyramide-shaped rune glows fiercly.\n";
	}
	
	if (this_player()->query_prop(RUNE8))
	{
		H = "A tear-shaped rune glows fiercly.\n";
	}
	
	if (this_player()->query_prop(RUNE9))
	{
		I = "A spear-shaped rune glows fiercly\n";
	}
	
	if (this_player()->query_prop(RUNE10))
	{
		J = "A fire-shaped rune glows fiercly.\n";
	}
	
	if (this_player()->query_prop(RUNE11))
	{
		K = "A maelstrom-shaped rune glows fiercly.\n";
	}
	
	if (this_player()->query_prop(RUNE12))
	{
		L = "A rock-shaped rune glows fiercly\n";
	}
	
	if (this_player()->query_prop(RUNE13))
	{
		M = "A spiral-shaped rune glows fiercly.\n";
	}
	
	if (this_player()->query_prop(RUNE14))
	{
		N = "A square-shaped rune glows fiercly\n";
	}
	
	return A+B+C+D+E+F+G+H+I+J+K+L+M+N;
}


void
unlock_trial(int level, object pl)
{

    object borb = present("_novtoken", pl);
    string *known_spells = ({ });
    string *a_spell = SPELL_LIST[level];
    string spell, *new_spells = ({ }), js, log;
    int i, j;
    setuid();
    seteuid(getuid());
    
     
    if (!objectp(borb))
    {
        pl->catch_tell("Nothing special happens.\n");
        return;
    }

    token_spells = restore_map(NOV_DIR +"log/token_spells");
    if (known_spells = token_spells[pl->query_real_name()])
        a_spell -= known_spells;
    else known_spells = ({ });
    j = sizeof(a_spell) - 1;
    if (!sizeof(a_spell))
    {
        pl->catch_tell("Nothing particulary happens.\n");
        
        return;
    }
    
    
    
    spell = a_spell[random(sizeof(a_spell))];

    
    new_spells = known_spells; 
    new_spells += ({ spell });
    
    switch(j)
      {
      case 0:
        js = "no more spells";
        break;
      case 1:
        js = "one more spell";
        break;
      default:
        js = LANG_WNUM(j) + " more spells";
      }

    pl->catch_tell("As you touch the rune, you receive a weak magical " +
    "jolt, empowering you with the ability to memorize and use "+spell+".\n"); 
                   //"There are "+js+" to unlock in this trial.\n");

    token_spells[pl->query_real_name()] = new_spells;
    
    save_map(token_spells, NOV_DIR +"log/token_spells");
    borb->setup_my_spells(pl);
    
    
   // log = sprintf("%s - %s unlocked " +
   // "the spell %s.\n", ctime(time()), this_player()->query_name(), spell);
   // log_file(BANEDEAD_DIR +"log/bane_spells_log", log, -1);

}

int
rune_burn()
{
      write("Suddently, as you touch the rune, a " +
      "jolt of positive energy lances through your body!\n");
      say(QCTNAME(this_player()) + " suddently screams when a " +
      "bolt of positive energy lances out of a " +
      "rune and through "+this_player()->query_possessive()+"'s body!\n");
			
      this_player()->heal_hp(-1000);

      if (this_player()->query_hp() <= 0)
      {
       this_player()->do_die(this_object());
       return 1;
      }
 
    return 1;
}

int
do_touch(string str)
{

	
	        if (str == "skull-shaped rune" && this_player()->query_prop(RUNE1))
		{
			this_object()->unlock_trial(1, this_player());
			this_player()->remove_prop(RUNE1);
			return 1;
	        }
	
	        if (str == "shield-shaped rune" && this_player()->query_prop(RUNE2))
		{
			this_object()->unlock_trial(2, this_player());
			this_player()->remove_prop(RUNE2);
			return 1;
	        }
	
	        if (str == "eye-shaped rune" && this_player()->query_prop(RUNE3))
		{
			this_object()->unlock_trial(3, this_player());
			this_player()->remove_prop(RUNE3);
			return 1;
	        }
	
	        if (str == "lightning-shaped rune" && this_player()->query_prop(RUNE4))
		{
			this_object()->unlock_trial(4, this_player());
			this_player()->remove_prop(RUNE4);
			return 1;
	        }
	
	        if (str == "ghost-shaped rune" && this_player()->query_prop(RUNE5))
		{
			this_object()->unlock_trial(5, this_player());
			this_player()->remove_prop(RUNE5);
			return 1;
	        }
	
	        if (str == "bird-shaped rune" && this_player()->query_prop(RUNE6))
		{
			this_object()->unlock_trial(6, this_player());
			this_player()->remove_prop(RUNE6);
			return 1;
	        }
	
	        if (str == "pyramide-shaped rune" && this_player()->query_prop(RUNE7))
		{
			this_object()->unlock_trial(7, this_player());
			this_player()->remove_prop(RUNE7);
			return 1;
	        }
	
	        if (str == "tear-shaped rune" && this_player()->query_prop(RUNE8))
		{
			this_object()->unlock_trial(8, this_player());
			this_player()->remove_prop(RUNE8);
			return 1;
	        }
	
	        if (str == "spear-shaped rune" && this_player()->query_prop(RUNE9))
		{
			this_object()->unlock_trial(9, this_player());
			this_player()->remove_prop(RUNE9);
			return 1;
	        }
	
	        if (str == "fire-shaped rune" && this_player()->query_prop(RUNE10))
		{
			this_object()->unlock_trial(10, this_player());
			this_player()->remove_prop(RUNE10);
			return 1;
	        }
	
	        if (str == "maelstrom-shaped rune" && this_player()->query_prop(RUNE11))
		{
			this_object()->unlock_trial(11, this_player());
			this_player()->remove_prop(RUNE11);
			return 1;
	        }
	
	        if (str == "rock-shaped rune" && this_player()->query_prop(RUNE12))
		{
			this_object()->unlock_trial(12, this_player());
			this_player()->remove_prop(RUNE12);
			return 1;
	        }
	
		if (str == "spiral-shaped rune" && this_player()->query_prop(RUNE13))
		{
			this_object()->unlock_trial(13, this_player());
			this_player()->remove_prop(RUNE13);
			return 1;
	        }
	        

		if (str == "square-shaped rune" && this_player()->query_prop(RUNE14))
		{
			this_player()->remove_prop(RUNE14);
			this_object()->unlock_trial(14, this_player());
			return 1;
	        }
	
	
	write("Touch what?\n");
	return 1;
}



void init()
{
 add_action(do_touch,"touch");
 
 ::init();
}
