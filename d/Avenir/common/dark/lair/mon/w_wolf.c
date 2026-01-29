// Winged Wolf   (/d/Avenir/common/dark/mon/w_wolf.c)
// Creator:      Grace   Apr 1995
// Updates:      Boriska: heal_hp in mesmer() tuned after hp formula change
//               Lilith  20 Jul 96:  added cut_leftover feather knife.
// Purpose:      For Avenir Unterdark
// todo: should breathe fire, answer questions
// make tongue a cut-leftover that can heal?

inherit "/d/Avenir/inherit/creature";

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include "/d/Avenir/common/common.h"
#define E      environment

#define A_BITE   TS_HEAD 
#define A_LCLAW  TS_LHAND
#define A_RCLAW  TS_RHAND
#define A_TAIL   TS_RFOOT
#define A_FEA    (TS_RARM | TS_LARM)

#define H_HEAD   TS_HEAD
#define H_BODY   TS_TORSO
#define H_WING   (TS_RARM | TS_LARM)
#define H_LFQ    TS_LFOOT
#define H_RHQ    TS_RFOOT

void
create_creature()
{
    set_name("winged wolf");
    set_pname("winged wolves");
    add_name(({"wolfie","marchosias", "_winged_wolf"}));
    set_race_name("wolf");
    set_adj("winged");
    set_short("winged wolf");
    set_pshort("winged wolves");
    set_long("This wolf is twice the size of any other you have seen. "+
	"Its fur is a golden brown colour and its yellow eyes glow "+
      "with their own fierce light. Most extraordinary though, are "+
	"the wings which rise from the creature's back. They are "+
	"irridescent and rainbow-hued, casting coloured shards "+
	"of light about the room.\nDespite the wolf's beauty, there "+
      "is about it an aura of malevolence.\n");
   
/*              str, con, dex, int, wis, dis           */
    set_stats(({ 70,  70,  70, 100, 100,  70}));
   
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_UNARM_COMBAT, 90);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_AWARENESS, 90);

    set_alignment(0);
    set_knight_prestige(100);                                                                                                 

    set_restrain_path(L2);
    set_monster_home(L2 + "n5");
               
    set_cact_time(6);
	add_cact("@@do_heal");

    set_act_time(4);
    	add_act("emote bares its teeth in a menacing growl.");	
	add_act("emote raises its hackles and stares balefully at you.");
	add_act("snarl all");
	add_act("emote seems to mock you with silent laughter.");
	add_act("emote shrugs, its golden-brown coat flowing over "+
		"rippling muscles.");
 	add_act("emote pads restlessly around the room.");
	add_act("emote unfolds its wings and flaps them agitatedly.");
        add_cact("emote licks its chops and looks hungrily at you.");
 
    set_attack_unarmed(A_BITE,   35, 35,   W_IMPALE,  20, "jaws");
    set_attack_unarmed(A_LCLAW,  25,  25,    W_SLASH,  40, "left paw");
    set_attack_unarmed(A_RCLAW,  25,  25,    W_SLASH,  40, "right paw");
    set_attack_unarmed(A_TAIL,   20, 20,    W_BLUDGEON,  10, "tail");
    set_attack_unarmed(A_FEA,    60, 60,    W_SLASH,  10, "wing-tip");
   
    set_hitloc_unarmed(H_HEAD, ({ 70 }), 10, "head");
    set_hitloc_unarmed(H_BODY, ({ 90 }), 40, "body");
    set_hitloc_unarmed(H_WING, ({ 90 }), 10, "wing");
    set_hitloc_unarmed(H_LFQ,  ({ 70 }), 20, "left foreleg");
    set_hitloc_unarmed(H_RHQ,  ({ 70 }), 20, "right hind-quarter");
   
    add_prop(LIVE_I_SEE_DARK, 90);
    add_prop(OBJ_I_RES_FIRE, 40 + random(25));
    add_prop(OBJ_I_RES_POISON, 75);
    add_prop(OBJ_I_LIGHT, 5);
    add_prop(NPC_I_NO_LOOKS, 1);
 
    add_leftover("/d/Avenir/common/dark/obj/f_knife", "feather",1, "", 0,0);
}

int
query_knight_prestige() { return 100; }

int
cr_did_hit(int aid, string hdesc, int phurt, object enemy, int dt, int phit)
{
// use milan's bleeding wound?   
   if (aid == A_FEA) 
   {
       tell_object(enemy, "One of the wolf's wing-tips "+
      		"slashes you, leaving a gaping wound!\n");
   }

   if (aid == A_TAIL)
   {
       tell_object(enemy, "The wolf's tail whips around "+
                "and strikes you with such force that you "+
                "are unable to breathe!\n");
       enemy->add_attack_delay(5);	
   }   
   return 0;
}

do_heal()
{
    TO->heal_hp(random(40) + 150);
    tell_room(ENV(TO), "The winged wolf licks at one of its wounds.\nThe " +
		"wolf's wound heals before your eyes!\n");
    return 1;
}

   
/*
 *   Special abilities and attacks below
 */
int
mesmer(object victim)
{
    object enemy;
    int num;
    mixed *wep;   

    enemy = TO->query_attack();
    num = random(100) + (enemy->query_stat(SS_DIS)) -
         (TO->query_stat(SS_WIS)/2);
    if(num < 100)
        {
        enemy->catch_msg("The winged wolf stares at you with fiercely "+
		"compelling eyes!\nYour eyes are drawn to those of "+
		"the wolf.\nThe glowing yellow orbs seem "+
		"to delve into your innermost self, searing your soul!\n");
	  tell_room(ENV(TO), "The winged wolf stares at " + QCTNAME(enemy) +
		" with fiercly compelling eyes!\n" + QCTNAME(enemy) + 
 		" looks like " + enemy->query_pronoun() + " has "+
                "been scared witless.\n", enemy);
	  enemy->add_panic(random(15));
           wep = enemy->query_weapon(-1);
        if (wep == ({ }))
        { 
            enemy->command("cringe");        
            enemy->stop_fight(TO);
            TO->stop_fight(enemy);
        }
        else
        enemy->commang("scream");
        enemy->command("unwield all");
        return 1;
    }

    enemy->catch_msg("The winged wolf tries to compel you to meet its "+
		"eyes.\n");
    tell_room(ENV(TO), "The winged wolf tries to compel " +
	      QCTNAME(enemy) + " to meet its eyes.\n", enemy);
}


int
special_attack(object victim)
{
    if (E(victim) != E(TO) || victim->query_ghost())
      {
	  TO->stop_fight(victim);
	  return 1;
      }

    switch (random(10))
      {
	case 0: mesmer(victim);
	        return 0;
	case 3: mesmer(victim);
	        return 0;
	case 7: mesmer(victim);
	        return 0;
	default: 
      }
    return 0;
}
