 /*
  * A mink npc based on the pheasant from Shire, which in 
  * turn is based on the rabbit from Gondor.
  * This npc will return a pelt when killed.
  * -- Finwe, October 2007
  */

inherit "/std/creature";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/std/combat/unarmed";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Faerun/defs.h"

/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  0
#define A_LPAW  1
#define A_RPAW  2
#define A_LCLAW 3
#define A_RCLAW 4

#define H_HEAD  0
#define H_BODY  1
#define H_LEGS  2

create_creature()
{
    if (!IS_CLONE) return;
    set_name("mink");
    add_name("animal");
    set_race_name("mink");

    set_adj("wild");
    set_adj("brown");
    set_short("wild brown mink");
    set_long("This is a "+query_short()+" and a member of the weasel family. It has a slender, arched body, with a long neck, short legs, and a bushy tail. The fur is thick and shiny and is a rich brown all over the body, except for a white throat patch.\n");

    set_alignment(0);
// sets base stats, STR, DEX, CON, etc
    set_stats(({10+random(8),
                10+random(6),
                10+random(5),
                10+random(5),
                10+random(10),
                10+random(5)}));

// sets the gender. G_MALE, G_FEMALE or G_NEUTER
    set_gender(random(2));
// give the npc some skills to defend itself
    set_skill(SS_UNARM_COMBAT,20+random(10));
    set_skill(SS_DEFENCE,20+random(10));
    set_skill(SS_PARRY, 20+random(10));
    set_skill(SS_BLIND_COMBAT, 5+random(10));
// defines how often it randomly moves in heartbeats/seconds
    set_random_move(5);
  
    add_prop(CONT_I_WEIGHT,4500+random(2500));
    add_prop(CONT_I_VOLUME,TO->query_prop(CONT_I_WEIGHT)*75/100);
// defines what the animal does when first met.  
    seq_new("do_first");
    seq_addfirst("do_first",({"@@arm_me","blink","emote digs in the dirt, looking for something to eat."}));
// defines what to clone when killed
    add_leftover("/d/Faerun/examples/obj/mink_pelt", "pelt", 1, 0, 1, 1);
}

arm_me()
{
    seteuid(getuid(TO));
// defines how the npc moves
    set_m_out("scurries");
    set_m_in("scurries in");
}

/*
 * Here we add attacks and hitlocations:
 *     add_attack(int wchit, int wcpen, int damtype, int prcuse, int id)
 *     add_hitloc(int *ac, int prchit, string desc, int id)
 *
 * *ac == ({ ac-impale, ac-slash, ac-bludgeon })
 */
public void
cr_configure()
{
// defines what body part to attack with and how much damage is done
// defines the hit damage, the pen damage, what damage type, % this part is used, and the 'body part' used
    add_attack(5+random(5),5+random(5),W_IMPALE,30,A_BITE);
    add_attack(5+random(5),5+random(5),W_SLASH,20,A_LPAW);
    add_attack(5+random(5),5+random(5),W_SLASH,20,A_RPAW);
    add_attack(5+random(5),5+random(5),W_SLASH,15,A_LCLAW);
    add_attack(5+random(5),5+random(5),W_SLASH,15,A_RCLAW);

// defines what body parts that can be hit
    add_hitloc(({5+random(5),5+random(5),5+random(5)}),20,"head",H_HEAD);
    add_hitloc(({5+random(5),5+random(5),5+random(5)}),50,"body",H_BODY);
    add_hitloc(({5+random(5),5+random(5),5+random(5)}),30,"legs",H_LEGS);
}

/*
 * Give description of each attack. We could also redefine the entire
 * hitdescription by redefining 'cr_did_hit'
 */
public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
        case A_BITE:return "jaw";
        case A_LPAW:return "left paw";
        case A_RPAW:return "right paw";
        case A_LCLAW:return "left claw";
        case A_RCLAW:return "right claw";
    }
    return "mind"; /* should never occur */
}

query_combat_file()
{
  return "/std/combat/cplain";
}
