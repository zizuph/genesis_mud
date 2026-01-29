/*
    /doc/examples/mobiles/tiger1.c

    JnA 920111

    A sample creature 

       This creature uses no tools for fighting. 
       It defines its own combat interface entirely.

    This is a rather tough beast. You need on average 30 or more in your
    stats to handle it. You also need wc30 weapon with skills to match.

*/

inherit "/std/creature";

inherit "/std/act/domove";
inherit "/std/act/action";

#include <wa_types.h>
#include <ss_types.h>

create_creature()
{
    set_name("tiger"); 
    set_race_name("tiger");
    set_short("black tiger");
    set_adj(({"black", "vicious" }));
    set_long("It look very vicious!\n");

    /* str, con, dex, int, wis, dis
    */
    set_stats(({ 90, 30, 80, 20, 5, 75}));

    set_skill(SS_DEFENCE, 30);
    set_skill(SS_SWIM, 80);

}

/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

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
    add_attack(20, 30, W_IMPALE, 40, A_BITE);
    add_attack(40, 20, W_SLASH, 30, A_LCLAW);
    add_attack(40, 20, W_SLASH, 30, A_RCLAW);

    add_hitloc( ({ 15, 25, 20 }), 20, "head", H_HEAD);
    add_hitloc( ({ 10, 15, 30 }), 80, "body", H_BODY);
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
    case A_BITE:return "jaws";
    case A_LCLAW:return "left paw";
    case A_RCLAW:return "right paw";
    }
    return "mind"; /* should never occur */
}

