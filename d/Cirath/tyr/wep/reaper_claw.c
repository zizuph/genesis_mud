#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include "/d/Cirath/ridge/arm/defs.h"
#include "/std/combat/combat.h"
#include <formulas.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <composite.h>

#define FIX_EUID         { setuid(); seteuid(getuid()); }
#define HIT_BONUS 7
#define PEN_BONUS 7

// saves unarmed attack bonus 
private int bonus;

int hand = 0;

void
create_armour()
{
  set_name ("claw");
  set_pname("claws");
  set_short("kank's claw");
  set_pshort("kank's claws");

  set_ac(5); 
  set_af(this_object());

  add_prop(OBJ_I_WEIGHT, 1000);
  add_prop(OBJ_I_VOLUME, 800);
  add_prop(OBJ_I_VALUE, 1000); 
}


void
left() 
{
	set_at(A_L_HAND);
  	set_long("Its obvious where this strange weapon got its "
		+"name from.  "
		+"Three massive claws stretch out from the hard "
		+"chitinous shell that snaps seamlessly around "
		+"your wrist.  Your thumb fits into one of the "
		+"three claws, while two fingers fit into each "
		+"of the other two claws.  The claws themselves "
		+"initially look line they are made of obsidian, "
		+"but upon further inspection, they are skillfully "
		+"crafted black steel.  Ancient runes cover the "
		+"claws and gauntlet itself, occasionally "
		+"flashing with some fell power. It can be worn on "
           	+"left hand.\n");  	
        add_item(({"runes","ancient runes"}),
		"Strange indecipherable characters in some "
		+"ancient tongue blanket the bizarre gauntlet.  "
		+"From time to time, they seem to ripple with "
		+"hidden power.\n");
        hand = 0;
}

void
right() 
{
	set_at(A_R_HAND);
  	set_long("Its obvious where this strange weapon got its "
		+"name from.  "
		+"Three massive claws stretch out from the hard "
		+"chitinous shell that snaps seamlessly around "
		+"your wrist.  Your thumb fits into one of the "
		+"three claws, while two fingers fit into each "
		+"of the other two claws.  The claws themselves "
		+"initially look line they are made of obsidian, "
		+"but upon further inspection, they are skillfully "
		+"crafted black steel.  Ancient runes cover the "
		+"claws and gauntlet itself, occasionally "
		+"flashing with some fell power. It can be worn on "
           	+"right hand.\n");  	
        add_item(({"runes","ancient runes"}),
		"Strange indecipherable characters in some "
		+"ancient tongue blanket the bizarre gauntlet.  "
		+"From time to time, they seem to ripple with "
		+"hidden power.\n");
        hand = 1;
}


int
query_hand()
{
    return hand;
}

public mixed
wear(object arm)
{
    int pen, hit, uskill;
    object player = environment(this_object());
    object co = player->query_combat_object();

    uskill = player->query_skill(SS_UNARM_COMBAT);
    pen = W_HAND_PEN + F_UNARMED_PEN(uskill, (this_player()->query_stat(SS_STR) + this_player()->query_stat(SS_DIS)));
    hit = W_HAND_HIT + F_UNARMED_HIT(uskill, (this_player()->query_stat(SS_DEX) * 2));
        
    pen = pen + PEN_BONUS;
    hit = hit + HIT_BONUS;

    
//    bonus = F_BONUS(this_player()->query_skill(SS_UNARM_COMBAT));
//    this_player()->catch_msg(message(bonus));
    player->catch_msg("You wear the claw of kank "+
      "on your " + (query_hand() == 0 ? "left" : "right") +
      " fist.\n");
    tell_room(environment(this_player()),
            QCTNAME(this_player()) + " wears the claw of kank on " +
            this_player()->query_possessive() +
            (query_at() == A_R_HAND ? " right" : " left") + " fist.\n", this_player());
    
    if (!player->query_vamp_option(1 << 9))
    {
        co->cb_add_attack(hit, pen, W_SLASH, 25, (hand == 1 ? W_RIGHT : W_LEFT),
        uskill + 6);
        co->cb_modify_procuse();
    }
    else
    {
    	if (this_object()->query_hand() == 1)
    	{
    	   player->rclaw_me(W_SLASH,HIT_BONUS,PEN_BONUS);
    	}
    	else 
    	{
           player->lclaw_me(W_SLASH,HIT_BONUS,PEN_BONUS);
        }
    
    }

    return 1;

}

public mixed
remove(object arm)
{
    object player = query_worn();
    object co = player->query_combat_object();
    int pen, hit, uskill;

    uskill = player->query_skill(SS_UNARM_COMBAT);
    pen = W_HAND_PEN + F_UNARMED_PEN(uskill, (this_player()->query_stat(SS_STR) + this_player()->query_stat(SS_DIS)));
    hit = W_HAND_HIT + F_UNARMED_HIT(uskill, (this_player()->query_stat(SS_DEX) * 2));

    if (!player->query_vamp_option(1 << 9))
    {
       co->cb_add_attack(hit,pen, W_SLASH, 25, (hand == 1 ? W_RIGHT : W_LEFT),
       uskill + 6);
       co->cb_modify_procuse();
    }
    else
    {
    	if (this_object()->query_hand() == 1)
    	{
    	   player->rclaw_me(0,0,0);
    	}
    	else if (this_object()->query_hand() == 0)
    	{
           player->lclaw_me(0,0,0);
        }
    }
    player->catch_msg("You remove the claw of kank "+
      "from your " + (query_hand() == 0 ? "left" : "right") +
      " fist.\n");
    say(QCTNAME(player) +" removes the claw of kank "+
      "from "+ player->query_possessive() +" " +
      (query_hand() == 0 ? "left" : "right") + " fist.\n");
    
    return 1;
}


public mixed
vampire_update()
{
    int pen, hit, uskill;
    object player = environment(this_object());
    object co = player->query_combat_object();

    uskill = player->query_skill(SS_UNARM_COMBAT);
    pen = W_HAND_PEN + F_UNARMED_PEN(uskill, (this_player()->query_stat(SS_STR) + this_player()->query_stat(SS_DIS)));
    hit = W_HAND_HIT + F_UNARMED_HIT(uskill, (this_player()->query_stat(SS_DEX) * 2));
        
    pen = pen + PEN_BONUS;
    hit = hit + HIT_BONUS;

      if (!player->query_vamp_option(1 << 9))
    {
        co->cb_add_attack(hit, pen, W_SLASH, 25, (hand == 1 ? W_RIGHT : W_LEFT),
        uskill + 6);
        co->cb_modify_procuse();
    }
    else
    {
    	if (this_object()->query_hand() == 1)
    	{
    	   player->rclaw_me(W_SLASH,HIT_BONUS,PEN_BONUS);
    	}
    	else 
    	{
           player->lclaw_me(W_SLASH,HIT_BONUS,PEN_BONUS);
        }
    
    }

    return 1;

}

int
got_hit(int hid, int ph, object att, int dt, int dam)    
{
	int ini, res, pen;
	object me = ENV(TO);
	mixed* hitresult;
	string how;

	::got_hit(hid, ph, att, dt, dam);
//	if(random(4)) return 0;
	// if(TP->query_skill(SS_UNARM_COMBAT) < 80) return 0;
	// if(TP->query_stat(3) < 136) return 0;
	
	ini = TP->query_base_stat(SS_INT) + random(TP->query_base_stat(SS_INT));
	res = att->query_magic_res(MAGIC_I_RES_ELECTRICITY);	
 	pen = ini * (100 - res) /100;
	hitresult = att->hit_me(pen, MAGIC_DT, me, -1);


	how = "barely missing you";
	if (hitresult[0] > 0) how = "just catching some skin with its sharp teeth";
	if (hitresult[0] > 2) how = "drawing blood with its sharp teeth";
	if (hitresult[0] > 5) how = "tearing chunks with its sharp teeth";
	if (hitresult[0] > 9) how = "tearing flesh from the bone";
	if (hitresult[0] > 14) how = "ripping flesh to pieces with its teeth";
	if (hitresult[0] > 20) how = "feasting on flesh";

	if(att->query_hp()<= 0) 
	{
		wearer->catch_msg("With an eerie sound, your claw of kank unleashes "+
			"a serie of electrical discharges on "+QCTNAME(att)+".\n"); 
		wearer->tell_watcher("With an eerie sound, "+QCTNAME(wearer)+"'s claw of kank unleashes "+
			"a serie of electrical discharges all on "+QCTNAME(att)+".\n", wearer, att);
		att->catch_msg("With an eerie sound, "+QCTNAME(wearer)+"'s claw of kank unleashes "+
			"a serie of electrical discharges all over your body.\n" 
			+"You feel your internal organs burning.\n");
		att->do_die(me);
		return 1;
	}

	wearer->catch_msg("With an eerie sound, your claw of kank unleashes "+
		"a serie of electrical discharges on "+QCTNAME(att)+".\n"); 
	wearer->tell_watcher("With an eerie sound, "+QCTNAME(wearer)+"'s claw of kank unleashes "+
		"a serie of electrical discharges all on "+QCTNAME(att)+".\n", wearer, att);
	att->catch_msg("With an eerie sound, "+QCTNAME(wearer)+"'s claw of kank unleashes "+
		"a serie of electrical discharges all over your body.\n");

	return 1;
}




/*
private string
message(int bonus) {
  switch (bonus) {
  case 1:
    return "Your feel a little weird wearing the claw.\n";
  case 2:
    return "Your feel like a big bully.\n";
  case 32:
    return "Your feel like an assassin ready to surprise someone.\n";
  case 4:
    return "You feel you are able to cut open anyone who messes with you.\n";
  case 5:
    return "No foe can stand against you, carrying your claw of kank " +
      "in a deadly grip.\n";
  default:
    return "You wear the claw of kank.\n";
  }
}
*/



void
init_recover(string arg) {
  string foo;
  int hand;
  
  sscanf(arg, "%shjhj#%d%s", foo, hand, foo);
  init_arm_recover(arg);
}
     

string
query_recover() {
  return MASTER + ":" + query_arm_recover() + sprintf("hjhj#%d", query_at());
}


