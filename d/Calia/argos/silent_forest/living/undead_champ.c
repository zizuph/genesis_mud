/* 
 * undead_champ.c
 * Baldacin@Genesis, Sep 2003
 *
 * 2007-07-31 - Cotillion
 * - This monster was very underpowered for the item quality it protected
 *   he has been improved.
 * 2015-12-06 - Petros
 * - Added a property to indicate on the player when they actually killed
 *   the undead champion.
 * 2017-07-06 - Jaacar
 * - Added check to do_die to make sure a player actually killed the undead
 *   champion and not something strange (like poison).
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/action";
inherit "/std/act/asking";
#include "/d/Genesis/gems/gem.h"
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <poison_types.h>
#include "../ldefs.h"

#define A_CLAWS 0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1
#define H_ARMS 2
#define H_LEGS 3

#define SPEC_PEN 550 /* Pen for the special attack */

void
create_creature()
{
    object gem, gem2, gem3, ob;
    int i, sz;
    string *equipment = ({"o_chainmail.c","o_helmet","o_shield","c_mantle","o_greaves" });
    
    set_name("undead");
    add_name("undead_champion");
    set_race_name("champion");
    set_adj(({"nefarious","undead"}));
    set_short("nefarious undead champion");    
    set_long("This nefarious undead champion, the spawn of death, "+
      "looks like something coming from your worst nightmare. "+
      "It is quite obvious that you should stay as far away from him "+
      "as possible - It is a hideous monster.\n");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_SEE_DARK, 4);
    add_prop(LIVE_I_UNDEAD, (85 + random(10)));
    add_prop(LIVE_I_QUICKNESS, 100);
    add_prop(LIVE_I_NO_CORPSE, 1);

    set_alignment(-650);
    set_gender(G_NEUTER);

    set_stats(({180 + random(5),     
                190 + random(5),     
                190 + random(5),     
                150 + random(5),     
                150 + random(5),     
                185 + random(5)}));  

    set_skill(SS_UNARM_COMBAT, 100 + random(15));
    set_skill(SS_BLIND_COMBAT,  85 + random(15));
    set_skill(SS_DEFENCE,       95 + random(10));
    set_skill(SS_AWARENESS,     60);

    set_attack_unarmed(A_CLAWS, 40, 40, W_SLASH, 30, "claws");
    set_attack_unarmed(A_LCLAW, 40, 40, W_SLASH, 35, "left claw");
    set_attack_unarmed(A_RCLAW, 40, 40, W_SLASH, 35, "right claw");
    
    set_hitloc_unarmed(H_HEAD, 80, 20, "head");
    set_hitloc_unarmed(H_BODY, 80, 40, "body");
    set_hitloc_unarmed(H_ARMS, 80, 20, "arms");
    set_hitloc_unarmed(H_LEGS, 80, 20, "legs");
    
    setuid();
    seteuid(getuid());
    gem  = RANDOM_GEM_BY_RARITY(GEM_VERY_RARE);
    gem2 = RANDOM_GEM_BY_RARITY(GEM_SLIGHTLY_COMMON);
    gem3 = RANDOM_GEM_BY_RARITY(GEM_SLIGHTLY_COMMON);
    gem->move(TO, 1);
    gem2->move(TO, 1);
    gem3->move(TO, 1);   
    
    for (i = 0, sz = sizeof(equipment); i < sz ; i++)
    {
        ob = clone_object(SFEQDIR + equipment[i]);
        ob->move(TO, 1);        
    }
    
    TO->command("wear all");
    set_default_answer(VBFC_ME("do_answer"));
    
}

int query_max_hp()
{
    return ::query_max_hp() * 3;
}

string
do_answer()
{
    command("glare "+TP->query_name());
    return "";
}

int
special_attack(object enemy)
{
   mixed* hitres;
   string how;
   object pois;

   if (random(3)) return 0;   

   hitres = enemy->hit_me(SPEC_PEN, W_SLASH, TO, -1);
   how = "completely misses";

   if (hitres[0] >  0) how = "barely hits";
   if (hitres[0] > 15) how = "lightly hit";
   if (hitres[0] > 30) how = "barely scratch";
   if (hitres[0] > 50) how = "wounds";
   if (hitres[0] > 75) how = "heavily wounds";

   enemy->catch_msg(QCTNAME(TO)+" tries to slash you with its "+
     "claws!\n");
   enemy->catch_msg(QCTPNAME(TO)+" attack "+how+" you.\n");
   
   enemy->tell_watcher(QCTNAME(TO) +" tries to slash "+QTNAME(enemy)+
     " with its claws!\n");
   enemy->tell_watcher(QCTPNAME(TO)+" attack "+how+" "+QTNAME(enemy)+".\n");

   if (hitres[0] > 70)
   {   
      pois = clone_object("/std/poison_effect");
      if(pois)
      {       
           pois->set_time(150);
           pois->set_interval(25);
           pois->set_strength(65);
           pois->set_damage(({POISON_HP, 90, POISON_FATIGUE, 90}));
           pois->move(enemy);
           pois->start_poison();
       }
   }
   if(enemy->query_hp() <= 0)
       enemy->do_die(TO);
   return 1;
}

do_die(object killer)
{
	if (killer->query_real_name() != 0)
	{
	    object *armours = TO->query_armour(-1);
	
	    string invert = "";
	
	    // Set the property to indicate when the player actually killed
	    // the undead champion. If it's after the last reset_room time,
	    // then they can access the treasure room.
	    killer->add_prop(LIVE_I_KILLED_UNDEAD_CHAMP, time());
	    
	    if (sizeof(armours))
	    {
	        write("As you strike the final blow to the champion, a bright "+
		      "light begins to glow from within its obsidian armours. The "+
		      "light grows with such intensity and heat, tiny cracks begin "+
		      "to form on the surface of the armours who then, suddenly "+
		      "evaporates into tiny flakes of dust before your eyes. "+
		      "Where once was the darkened suit of a damned, now lies a "+
		      "flawless crystal clear suit.\n");
		say("As "+QTNAME(killer)+" strike the final blow to the champion "+
	            "a bright light begins to glow from within its obsidian armours. "+
		    "The light grows with such intensity and heat, tiny cracks "+
		    "begin to form on the surface of the armours who then, suddenly "+
		    "evaporates into tiny flakes of dust before your eyes. "+
		    "Where once was the darkened suit of a damned, now lies a "+
		    "flawless crystal clear suit.\n", killer);
	
	        for (int i = 0;i < sizeof(armours);i++)
		{
		    invert = armours[i]->query_inverted();
		    
		    if(strlen(invert))
	            {
			armours[i]->remove_object();
	                clone_object(invert)->move(TO, 1);
	            }
	 	}
	    }
	
	    LOGFILE("kills", capitalize(killer->query_real_name()) +
		    " killed the undead champion.\n");
	    ::do_die(killer);
    }
}


