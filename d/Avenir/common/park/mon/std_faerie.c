// file name:	std_faerie.c
// creator(s):	Ilyian (23 March, 1995)
// last update: 26 April (put in friend helper)
//		Denis, May'97: Obsolete code update,
//			       recoded the way they assist each other.
// purpose:
// note:
// bug(s):
// to-do: 

# pragma strict_types

# include "/d/Avenir/include/defs.h"
# include "/d/Avenir/include/paths.h"
# include <formulas.h>
# include <cmdparse.h>
# include <macros.h>
# include <ss_types.h>
# include <wa_types.h>
# include <stdproperties.h>

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/std/act/domove";
inherit "/std/act/action";

# define A_WINGS 0
# define A_RHAND 1
# define A_LHAND 2
# define A_BITE 3
# define A_RFOOT 4
# define A_LFOOT 5

# define H_HEAD 0
# define H_BODY 1
# define H_LEGS 2
# define H_WINGS 3

# define FAERIE_ID	"_Avenir_park_faerie"

string *randadj = ({"blue-eyed","lovely","voluptous","tiny",
                    "silver-winged","nimble","lithe",
                    "beautiful","blonde-haired","quick","translucent",
                    "young","child","energetic","jovial","ivory-skinned",
                    "long-armed","tender","white","seductive","soft-voiced",
                    "sinuous","bright","long-legged","miniscule","small",
                    "cheerful","sad","plaintive","enigmatic"});

void
create_creature()
{
    set_name("faerie");
    add_name(FAERIE_ID);
    set_race_name("faerie");
    set_gender(G_FEMALE);
    set_adj(randadj[random(sizeof(randadj))]);
    set_long("This miniscule creature looks just like a perfectly-" +
             "formed elven woman with silvery insect wings. She " +
             "flits around happily, landing on flowers. She is a " +
             "creature of light, for whom evil has no meaning.\n");

    set_alarm(1.0, 0.0, &set_m_in("flits in."));
    set_alarm(1.0, 0.0, &set_m_out("flits"));
    set_alignment(300);

    add_prop(CONT_I_WEIGHT, 50);
    add_prop(CONT_I_VOLUME, 30);
    add_prop(LIVE_I_QUICKNESS, 100);  //fast little critters
    add_prop(NPC_I_NO_FEAR, 1);
    NEVERKNOWN;

    set_stats(({ 2,70,30,30,90,90 }));

    set_skill(SS_UNARM_COMBAT, 20);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_SNEAK, 60);
    set_skill(SS_HIDE, 60);
    set_skill(SS_AWARENESS, 85);
    set_skill(SS_BLIND_COMBAT, 93);

    set_attack_unarmed(A_WINGS,3,3,W_BLUDGEON,10,"wings");
    set_attack_unarmed(A_RHAND,3,3,W_BLUDGEON,10,"right hand");
    set_attack_unarmed(A_LHAND,3,3,W_BLUDGEON,10,"left hand");
    set_attack_unarmed(A_BITE,5,8,W_IMPALE,50,"bite");
    set_attack_unarmed(A_RFOOT,3,3,W_BLUDGEON,10,"right foot");
    set_attack_unarmed(A_LFOOT,3,3,W_BLUDGEON,10,"left foot");

    set_hitloc_unarmed(H_HEAD, 70, 2,"head");
    set_hitloc_unarmed(H_BODY, 95 , 60,"body");
    set_hitloc_unarmed(H_LEGS, 90 , 30,"legs");
    set_hitloc_unarmed(H_WINGS, 75 , 8,"wings");

    set_cact_time(10);
    add_cact("emote screams in a high pitched voice.");
    add_cact("glare enemy");
    add_cact("growl angr enemy");
    add_cact("emote waves her wings in irritation.");
    add_cact("whine soft");
    add_cact("fume");
    add_cact("point enemy");
    add_cact("shap enemy");
    add_cact("pout .");
    add_cact("emote utters a loud exclamation in a lost language.");

    set_act_time(5);
    add_act("giggle merrily");
    add_act("stretch");
    add_act("emote flits around your head.");
    add_act("emote stretches her wings and yawns.");
    add_act("emote lands on a flower and wraps herself in a petal.");
    add_act("kiss elf");
    add_act("tickle goblin");
    add_act("tickle second goblin");
    add_act("kiss second elf");
    add_act("nibble dwarf");
    add_act("nibble second dwarf");
    add_act("peer human");
    add_act("peer second human");
    add_act("smile warm hobbits");
    add_act("smile cute");
    add_act("hiccup");
    add_act("laugh happily");
    add_act("emote rubs her eyes and smiles tiredly.");
    add_act("emote sings a sad song in a forgotten language.");
    add_act("emote flits around happily.");
    add_act("emote sings in a high, lilting voice.");
    add_act("emote blinks.");
    add_act("emote flies right into you and then falls to the " +
            "ground, giggling in surprise.");
    add_act("gasp");
    add_act("tackle faerie");
    add_act("tickle second faerie");
    add_act("kiss third faerie");
    add_act("startle fourth faerie");
    add_act("emote vanishes behind some flowers, and then " +
            "appears on the other side again.");
    add_act("fondle fifth faerie.");
    add_act("whisper faerie Nshisk mirtoosh nlush!");
    add_act("whisper second faerie Mashun blishton! " +
            "Blishton... Sybarus amforsh.");
    add_act("whisper third faeire Empism Tepisch san " +
            "wasrisng: ArchausofinDomisnus");
    add_act("whisper fourth faerie AmoMahi! AmoMahi!");
    add_act("whisper fifth faerie Sheenshkul Kazz " +
            "istun Goldberry! Melfish...");
    add_act("whisper sixth faerie Borisstok lishenfir maskintuk!");
    add_act("hide");
    add_act("twinkle");
    add_act("laugh softly");
    add_act("search here");
    add_act("track");

    add_leftover(PK + "obj/faerie_wing", "wing", 2,0, 0,0);
}

static void
do_attack(object who)
{
   if (present(who, environment()))
   {
       command("kill " + who->query_real_name());
       command("scream");
   }
}

public void
faerie_help_out(object attacker)
{
    if (!query_attack() && random(2))
        set_alarm(itof(random(6) + 2), 0.0, &do_attack(attacker));
}

public void
attacked_by(object who)
{
    filter(all_inventory(ENV(TO)), &->id(FAERIE_ID))->faerie_help_out(who);
}
