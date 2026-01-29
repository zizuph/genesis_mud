// randweap.c Lots of weapons in single file
// Made by Boriska@Genesis July 1994

inherit "/std/weapon";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>

void configure_me ();

// possible weapon types to pick randomly from
int *w_types = ({ W_SWORD, W_POLEARM, W_AXE, W_KNIFE, W_CLUB });

int w_types_len = sizeof(w_types);

// possible names for weapons 
string  *sword_names = ({"sword", "longsword", "shortsword"});

string *polearm_names = ({"halberd", "glaive", "fauchard"});

string *axe_names = ({ "axe" });

string *knife_names = ({ "knife", "dagger", "dirk" });

string *club_names = ({ "mace", "flail", "club", "warhammer", "morningstar"});

mixed *names = ({ sword_names, polearm_names, axe_names,
		   knife_names, club_names });
		   
int *name_len = ({ sizeof (sword_names), sizeof (polearm_names),
		    sizeof(axe_names),	   sizeof(knife_names),
		    sizeof (club_names) });

string  *sword_adj = ({"steel", "rusty", "curved", "bastard" });

string *polearm_adj = ({"heavy", "steel", "bronze"});

string *axe_adj = ({ "heavy", "nasty", "iron" });

string *knife_adj = ({ "curved", "dull", "wicked" });

string *club_adj = ({ "nasty", "spiked", "huge", "horrible"});

mixed *adjs = ({ sword_adj, polearm_adj, axe_adj,
		   knife_adj, club_adj });
		   
int *adj_len = ({ sizeof (sword_adj), sizeof (polearm_adj),
		    sizeof(axe_adj),	   sizeof(knife_adj),
		    sizeof (club_adj) });

// damage types
int *dts = ({ W_IMPALE | W_SLASH, W_IMPALE, W_SLASH, W_IMPALE, W_BLUDGEON });

int type = type, subtype, adj_index;

create_weapon ()
{
  set_name ("weapon");
  set_short ("weapon");  // needed for correct weapon name when recovering it
    
  type = random (w_types_len);
  subtype = random (name_len[type] );
  adj_index = random(adj_len[type]);
  
  set_hit(17+random(5));
  set_pen (17 +random(5));
  set_hands ( W_ANYH);
  
  // make knives lighter
  if ( type == W_KNIFE )
    {
      add_prop (OBJ_I_WEIGHT, 5432);
      add_prop (OBJ_I_VOLUME, 4321);
    }
  else
    {
      add_prop (OBJ_I_WEIGHT, 10123);
      add_prop (OBJ_I_VOLUME, 8765 );
    }
  
  // make it worse
  set_corroded (1);
  configure_me ();
}

void
configure_me ()
{
  string name, adj;
  
  adj = adjs[type][adj_index];
  name = names[type][subtype];
  
  set_name (name);
  set_short (adj + " " + name);
  set_adj (adj);

  set_long (
   "This " + adj + " " + name + " has a look of neglect and long careless\n" +
    "usage about it. It lost its sharpness and gathered a lot of\n" +
    "dirt being thrown away in a heap of other weapons.\n"
	    );
	    
  set_wt (w_types[type] );
  set_dt (dts[type]);
}

string
query_recover()
{
  
  return MASTER + ":" + query_wep_recover() +
    sprintf ("hjhj#%d#%d#%d", type, subtype, adj_index);
}

void
init_recover(string arg)
{
  string foo;
  
  sscanf ( arg, "%shjhj#%d#%d#%d%s", foo, type, subtype, adj_index, foo);
  configure_me ();  
  init_wep_recover(arg);
}


