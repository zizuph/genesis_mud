// -*-C++-*-
// file name:   ~Avenir/common/dark/mon/worm_tail.c
// creator(s):  Boriska, descriptions by Grace.
// last update: Boriska, Mar 24 1995
// purpose:     Part of worm NPC
// note:        Should be cloned and handled by master_worm object.
// bug(s):
// to-do:     

inherit "/d/Avenir/common/dark/mon/worm_part";
inherit "/d/Genesis/specials/npc/stat_based_specials";

#include <const.h>
#include <money.h>
#include "/d/Avenir/common/dark/dark.h"
#include "/d/Avenir/include/worm.h"

#define A_SKIN 0
#define A_TAIL 1

#define H_FLESH 0
#define H_ORIFICE 1
#define H_SEGMENT 2

#define RAND 125+random(50)

static object to = this_object();

void
create_creature ()
{
    if ( !IS_CLONE )
	return;

    set_name ("tail");
    add_name ("worm");
    set_short ("worm tail");
    add_adj ("mottled");
    set_race_name ("worm tail");
    set_long( 
      "You're not sure, but you think this is the tail-end of one of\n" +
      "the giant omnvivorous worms known to live in these tunnels.\n"+ 
      "The impact of it's tremendous size on your senses causes a\n"+ 
      "tendril of panic to cloud your mind. Each segment is the length\n"+ 
      "and breadth of a tall man. The final segment narrows to form an\n"+
      "orifice the size of your head.\n"
    );

    set_stats ( ({RAND, RAND, 150, RAND, RAND, RAND}) );
    set_skill (SS_DEFENCE, 100);
    set_skill (SS_UNARM_COMBAT, 100);

    set_gender (G_NEUTER);
    set_aggressive (1);

    set_arrive ("The tail of a huge worm sleathers in the room!\n");
    set_depart ("The worm tail sleathers away.\n");

    set_hitloc_unarmed ( H_FLESH,  20, 10,
      "a soft fleshy place between the rings");
    set_hitloc_unarmed ( H_ORIFICE,  35, 20, "orifice" );
    set_hitloc_unarmed ( H_SEGMENT,  40, 70, "scaled segment" );

    set_attack_unarmed ( A_SKIN, 70, 40, W_SLASH,    70, "hard skin");
    set_attack_unarmed ( A_TAIL, 80, 40, W_BLUDGEON, 50, "tail");

    add_prop (NPC_I_NO_RUN_AWAY, 1); // only master_worm can move
    add_prop (CONT_I_WEIGHT, 654321);
    add_prop (CONT_I_VOLUME, 543210);

    add_leftover ( LEFT_OBJ, TAIL_LEFTOVER, 1, 0 ,0, 1);
    // Note : all worm parts contain the same leftover object
    // with different features based on organ name.
    // Make sure that second argument is processed properly
    // in SKIN code.

    // give it funny sum of money
    MONEY_MAKE_CC(5)->move(to);
    MONEY_MAKE_SC(4)->move(to);
    MONEY_MAKE_GC(3)->move(to);
    MONEY_MAKE_PC(2)->move(to);    
}

// special attack stuff...
// throw funny things from our ... back end
static string *verbs = ({
  "ejects",
  "discharges",
  "flings",
  "evacuates",
  "excretes"
});

int verb_len = sizeof (verbs);

static string *attack = ({
  "Medallion of Calia swarms around ",
  "Necklace of the Kaheda Order utters 'hiya' and flies to ",
  "Gladiator's heavy breath charges into a brave attack on ",
  "Traveller's walking stick quickly travels the space between worm and ",
  "Silver fork flows in the air, emitting deafening cacophony at ",
  "Undead skull sneaks close, aiming for neck, and savagely bites ",
  "Elven finger with golden ring on it runs wildly to ",
  "Star-shaped brooch scratches the ground throwing a pile of sand on ",
  "Medal of Paladine kicks ",
  "Ancient runed staff chants mysterious words, waving at ",
  "Torn black hooded robe darts out hissing dangerously at ",
});

static mixed *damage = ({
  ({"The medallion of Calia dealt ", " a devastating blow!\n"}),
  ({"The necklace hit ", " in the stomach!\n"}),
  ({"The heavy breath brings ", " to the verge of collapse!\n"}),
  ({"The stick hits ", " and reminds that the last travel starts soon.\n" }),
  ({"The silver fork emits loud and clear sound as it strikes ",
    " in the head!\n"}),
  ({"The savaging skull turns ", " into a walking corpse!\n" }),
  ({"The elven finger pokes ", " in the eye!\n"}),
  ({"The star-shaped brooch has blinded ", " completely!\n" }),
  ({"The medal of Paladine hit ", " like hurricane!\n" }),
  ({"The ancient staff did something to ",
    " leaving everybody puzzled about what exactly it was.\n"}),
  ({"The black poisonous liquid is squeezed out of the robe, covering ",
    " with dark cloud!\n"}), 
});

static int attacks = sizeof (attack );
// please keep the size of all arrays above the same

int
special_attack (object victim)
{
    int att;
    object ob;

    if ( victim->query_prop (OBJ_M_NO_ATTACK) || random (10) ) 
	return 0;

    att = random (attacks);

    say ("Worm " + verbs[random(verb_len)] +
      " something from the tip of its tail!\n");

    // Choose power of hit based on mob stat size.
    mixed* hitresult = do_stat_based_attack(TO, victim, W_BLUDGEON);
	
	// The attack was evaded
	if (intp(hitresult))
		return 1;

    tell_watcher ( attack[att] + QNAME(victim) + "!\n", to, victim);
    victim->catch_msg ( attack[att] + "you!\n");

    ob = clone_object(OBJ + "dummy_token");
    ob->configure(att);
    ob->move(environment());

    tell_watcher ( damage[att][0] + QNAME(victim) + damage[att][1], to, victim);
    victim->catch_msg (damage[att][0] + "you" + damage[att][1]);

    if (victim->query_hp() < 0 )
	victim->do_die(); 
    return 0;
}


void
aggressive_attack (object ob)
{
    if (member_array (ob, query_enemy (-1) ) < 0 ) {
	write ("Something big swirls in the air above your head...\n");
	::aggressive_attack (ob);
    }
}
