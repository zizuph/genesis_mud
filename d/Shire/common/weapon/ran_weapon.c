inherit "/std/weapon";
inherit "/d/Immortal/rogon/open/message";

#include "/sys/stdproperties.h"
#include "/sys/formulas.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"

/********************************************************************/

/** name, adj, base_hit, base_pen, **/

#define W_1H_CHANCE ({ 5, 21, 23, 43, 45, 49, 50, 57, 69, 73, 77, 79, 86, 98, 100 })
     
/********************************************************************/

int rnd(mixed *list) {
  int i,r;
  r = random(100);
  for(i=0;i<sizeof(list);i++)
    if(r<list[i]) return i;
}

void create_weapon() { 
  int r; 
  mixed *wep;

  wep = 

({ 
    "sword", "bastard",  24,  32,   W_SWORD, W_ANYH,  W_SLASH | W_BLUDGEON,
    "This is a finely curved and balanced blade so to give a perfect\n"+
      "slash and a bludgeon hit.\n",
    "broadsword",    0,  24,  30,   W_SWORD, W_ANYH,  W_SLASH | W_BLUDGEON,
    "This is a heavy slashing sword.\n",
    "cutlass",	     0,  30,  22,   W_SWORD, W_ANYH,  W_SLASH | W_IMPALE,
    "A cutlass is an impaling and slashing sword often used by pirates.\n",
    "dagger",        0,  12,  14,   W_KNIFE, W_ANYH, W_IMPALE,
    "This is a knife used for fighting.\n",
    "dirk",          0,  13,  16,   W_KNIFE, W_ANYH, W_IMPALE,
    "This is a kind of a dagger, a knife used for fighting.\n",
    "falchion",      0,  14,  16,   W_KNIFE, W_ANYH, W_IMPALE,
    "A falchion is a kind of a dagger.\n",
    "foil",	     0,  32,  21,   W_SWORD, W_ANYH,  W_IMPALE,
    "A foil is a weapon used in fencing.\n",
    "handaxe",       0,  12,  17,   W_AXE,   W_ANYH, W_IMPALE | W_BLUDGEON,
    "This is a simple axe used for killing.\n",
    "longsword",     0,  24,  30,   W_SWORD, W_ANYH,  W_SLASH | W_BLUDGEON,
    "This is a basic sword.\n",
    "gauche",	"main",  12,  14,   W_KNIFE, W_LEFT,   W_IMPALE,
    "This is a left handed only dagger.\n",
    "rapier",	     0,  27,  10,   W_SWORD, W_RIGHT,  W_IMPALE,
    "A rapier is a fencing weapon.\n",
    "sabre",         0,  23,  30,   W_SWORD, W_RIGHT,  W_SLASH | W_IMPALE, 
    "A slashing sword used by arabs. Wery good design.\n",
    "scimitar",      0,  17,  20,   W_SWORD, W_ANYH, W_SLASH | W_BLUDGEON,
    "A slashing sword.\n",
    "sword",   "short",  20,  17,   W_SWORD, W_ANYH, W_IMPALE | W_SLASH,
    "A small thrusting sword.\n",
    "tomahawk",      0,  20,   9,    W_AXE,   W_ANYH, W_IMPALE | W_BLUDGEON, 
    "A tomahawk is a indian type of waraxe.\n" 
});
     
  r = rnd(W_1H_CHANCE);
  
  set_name(wep[8*r]);
  if(strlen(wep[8*r+1])>0) 
     set_adj(wep[8*r+1]);
  set_hit(wep[8*r+2]);
  set_pen(wep[8*r+3]);
  set_wt(wep[8*r+4]);
  set_hands(wep[8*r+5]);
  set_dt(wep[8*r+6]);
  set_short( (strlen(wep[8*r+1])>0 ? wep[8*r+1]+" " : "") + wep[8*r] );
  set_long(wep[8*r+7]);
}

did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit, int dam)
{
    object tp = query_wielded();
    return message(tp, enemy, dt, hdesc, phurt);
}

/*
 * This should be recoverable, but then one should be sure that
 * the same weapon is recovered, and not a random new one...
 * It will look a bit strange at login, but it will work.
 */
/* Commented out by Dunstable to allow saving of Character files ;)
string query_recover() {
    string settings;

    settings = query_name() + "=" + query_adj() + "=" + query_hit() + "="
             + query_pen() + "=" + query_wt() + "=" + query_hands() + "="
	     + query_dt() + "=" + query_short() + "=" + query_long() + "|";

    return MASTER + ":" + settings + query_wep_recover();
}

void init_recover(string arg) {
    string name, adj, short, long, rest;
    int hit, pen, wt, hands, dt;

    sscanf(arg, "%s=%s=%d=%d=%d=%d=%d=%s=%s|%s", name, adj, hit, pen, wt,
	   hands, dt, short, long, rest);

    set_name(name);
    set_adj(adj);
    set_hit(hit);
    set_pen(pen);
    set_wt(wt);
    set_hands(hands);
    set_dt(dt);
    set_short(short);
    set_long(long);

    init_wep_recover(rest);
}
*/
