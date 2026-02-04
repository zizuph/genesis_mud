/*
    /doc/examples/mobiles/tiger1.c

    JnA 920111

    A sample creature 

       This creature uses no tools for fighting. 
       It defines its own combat interface entirely.

    This is a rather tough beast. You need on average 30 or more in your
    stats to handle it. You also need wc30 weapon with skills to match.

*/
/* Modified and *toned-down* for dormouse.c by Azireon, 8/15/92 
 * "All generations shall call me blessed"  Assumption 1992 */

inherit "/std/creature";

inherit "/std/act/domove";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Terel/common/terel_defs.h"

create_creature()
{
    if(!IS_CLONE)
        return;

    set_name("dormouse");
    add_name("mouse");
    set_pname("dormice");
    set_race_name("dormouse");
    set_adj(color());

    set_long(break_string(
      "This nervous little mouse is probably searching for food.  " +
      "Its eyes and nose are twitching frantically.\n", 70) );

    enable_commands();

    set_act_time(random(10));
    add_act("@@sniff");
    add_act("@@scurry");
    add_act("@@squeak");
    add_act( ({ "w", "e", "n", "s", "ne", "nw", "se", "sw" }) );

    set_m_in("scurries toward you.");
    set_m_out("scurries away");

    set_cact_time(2);
    add_cact("@@run");
    add_cact("@@freeze");

    /* str, con, dex, int, wis, dis
    */
    set_stats( ({ 15, 20, 10, 5, 5, 10 }) );

    set_hp(400);

    set_whimpy(1);  /* Will run--it's WEAK! */
}

/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  0

#define H_HEAD 0
#define H_BODY 1

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
    add_attack(5, 10, W_IMPALE, 15, A_BITE);

    add_hitloc( ({ 20, 10, 5 }), 80, "head", H_HEAD);
    add_hitloc( ({ 20, 10, 5 }), 20, "body", H_BODY);
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
    case A_BITE:return "tiny teeth";
    }
    return "mind"; /* should never occur */
}

color()
{
    string *colors;
    colors = ({"white", "black", "tan", "spotted",
                "albino", "brown", "speckled"});
    return colors[random(sizeof(colors))];
}

sniff()
{
    tell_room(environment(this_object()), "The mouse sniffs about " +
      "timidly, its whiskers bobbing.\n");
}

scurry()
{
    tell_room(environment(this_object()), "The mouse scurries about, " +
      "obviously frightened by something.\n");
}

squeak()
{
    tell_room(environment(this_object()), "The mouse squeaks " +
      "timorously.\n");
}

run()
{
    tell_room(environment(this_object()), "Terrified, the mouse " +
      "tries to scurry away!\n");
}

freeze()
{
    tell_room(environment(this_object()), "Because the mouse is so " +
      "petrified, it freezes defensively in place!\n");
}
