/*
* Created by: 
* Date: 
*
* File: /d/Cirath/chukel/wep/cg_shield.c
* Comments: Updated by Luther Oct. 2001
*/
inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include "defs.h"

int wt,ws;

string
query_weapon_name()
{
  if (wt == 0) return "sword";
  if (wt == 1) return "axe";
  if (wt == 2) return "polearm";
  if (wt == 3) return "warhammer";

  return "gatling";
}

string
query_weapon_good()
{
  if (ws < 20) return "fair";
  if (ws < 25) return "usable";
  if (ws < 30) return "good";
  return "excellent";
}

string
query_weapon_desc()
{
  string wep,good;
  wep = query_weapon_name();
  good = query_weapon_good();

  return "This is a cirathian made "+wep+" that are primaly used by "+
         "the guards that protects the cities and trade-routes in "+
         "Cirath. The "+wep+" looks like a "+good+" weapon.";
}

int
set_weapon_props()
{
  int hand;

  if (wt == 2)
  {
    set_wt(W_POLEARM);
    set_dt(W_BLUDGEON | W_IMPALE);
    add_prop(OBJ_I_WEIGHT, 10000 + random(5000));
    add_prop(OBJ_I_VOLUME, 10000 + random(2500));
    set_hands(W_BOTH);
  }
  else
  {
    if (wt == 0)
    {
      set_wt(W_SWORD);
      set_dt(W_SLASH | W_IMPALE);
    }
    else if (wt == 1)
    {
      set_wt(W_AXE);
      set_dt(W_SLASH | W_IMPALE);
    }
    else if (wt == 3)
    {
      set_wt(W_CLUB);
      set_dt(W_BLUDGEON);
    }

    hand = random(3);
    if (hand == 0)      set_hands(W_ANYH);
    else if (hand == 1) set_hands(W_LEFT);
    else if (hand == 2) set_hands(W_RIGHT);
    else               set_hands(W_BOTH);

    add_prop(OBJ_I_WEIGHT, 5000 + random(2500));
    add_prop(OBJ_I_VOLUME, 2500 + random(2500));
  }

  set_hit(ws);
  set_pen(ws);

  return 1;
}

void
create_weapon()
{
  string str,str2,desc;

  wt = random(4);
  ws = random(25)+10;

  str  = query_weapon_name();
  str2 = query_weapon_good();
  desc = query_weapon_desc();

  set_name(str);
  set_short(str2+" cirathian "+str);
  set_long(break_string(desc+"\n",60));

  set_adj("cirathian");
  add_adj(str2);

  set_weapon_props();
}
