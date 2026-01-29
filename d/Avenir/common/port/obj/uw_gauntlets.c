 // file name:    ~Avenir/common/port/obj/uw_gauntlets.c
 // creator(s):    Glinda june -95
 // last update:   Lilith, Mar 1999 - modified remove();
 //                Cirion, Feb 1996 - fixed it up a bit.
 //                Casca, Jan 2000 - fixed it up a bit more.
 //                Cotillion 2015-02-14:  LIVE_I_QUICKNESS 80 -> 60 (max) 
 //                Lilith, Oct 2021: converting to unarmed enhancer code.
 //                 removed anti-undead code from 30 years ago. The game 
 //                 has changed immensely since they were first made.
 //                Lilith, Nov 2021 fix line 115 to damage = max (0
 //                 because negative would end up healing mana.
 //                Lilith, Mar 2022: wearing down fast, changed likely 
 //                 break and likely cond to negative values per Arman.
 // purpose:       One of the treasures that can be found in the wreck.
 // note:          They can not be worn if you have resistance
 // 		   to either air or life or magic.
 // bug(s):
 // to-do:

inherit "/d/Avenir/inherit/unarmed_enhancer";
inherit "/lib/commands";
inherit "/lib/keep";

#include "/d/Avenir/common/common.h"
#include <wa_types.h>
#include <stdproperties.h>

private static int energy;

void 
create_unarmed_enhancer()
{
    set_short("pair of golden gauntlets");
    set_pshort("pairs of golden gauntlets");
    set_name("gauntlets");
    set_pname("gauntlets");
    add_name(({"pair", "gloves", "armour"}));
    add_pname(({"pairs", "armours"}));
    set_adj(({"gold","golden","magical"}));
    set_long ("This pair of gauntlets looks like a real treasure. "+
        "Each moulded glove is quite ornate, with sparkling jewels "+
        "set within the patterns of delicate lines etched into the "+
        "gold. You marvel over the beautiful craftmanship.\n");

    add_item(({"pattern","patterns","etchings","lines"}),"@@pattern@@");

    set_default_enhancer(48, 48, W_BLUDGEON, 17, A_HANDS | A_ARMS, 
        ({ 1, 2, -3}), this_object());

    add_prop(MAGIC_AM_MAGIC, ({ 35, "life", 27, "air" }));
    add_prop(OBJ_I_RES_WATER, 40); // So they don't rust!
    add_prop(MAGIC_I_RES_WATER, 40);
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO,
        ({ "    Beyond ancient are these, old as time\n", 5,
           "    Old as the gold from whence they came.\n", 15 , 
           "    Vibrant with Life and hard as Earth\n", 25 ,
           "    Enchanted to resist Water and wear\n", 35 ,
           "    Speed dost thou gain from the element Air.\n", 55 }));

    add_prop( OBJ_S_WIZINFO, 
        "Adds quickness to the player who wears them, "
        +"dependant on the wisdom, MAGIC_I_RES_LIFE, "
        +"and MAGIC_I_RES_AIR of the player, with "
        +"a possible range from 35 - 60.\n");
    add_prop(OBJ_I_VALUE,  2300);
    add_prop(OBJ_I_WEIGHT, 2100);
    add_prop(OBJ_I_VOLUME, 2000);  //including the space in which your arm fits

/*	
 *  Lilith, Feb 2022: Getting feedback from unarmed fighters that these
 *                    boots are wearing down very fast--because they are
 *                    both taking hits and enhancing hits.  I'm going to
 *                    try setting these to negatives to see how it goes.
 *         Arman gave ok to set values very very negative on 3/3/2022
 */
	set_likely_break(-1000); 
	set_likely_cond(-1000);

}

string 
pattern()
{
    if (TP->query_magic_res(MAGIC_I_RES_LIFE) ||
        TP->query_magic_res(MAGIC_I_RES_AIR))
    {
        TP->heal_hp(-200);
        return "The pattern seems to weave in and out of "
            +"your vision.\nYou feel an intense pain in "
            +"your chest!\n";
    }

    switch(energy)
    {
        default:
            return "The patterns are delicate and very "
               +"elegant. You find them pleasing to "
               +"the eye.\n";   break;
        case 35 .. 40:
            return "The patterns seem to dance in some "
               +"strange pattern that eludes the eye.\n";   break;
        case 41 .. 45:
            return "The patterns seem to almost weave in and "
               +"out of your vision, as if they were "
               +"alive.\n";  break;
        case 46 .. 54:
            return "Like eerie and tiny snakes, the "
               +"patterns are moving along the "
               +"gauntlets like quicksilver.\n";  break;
        case 55 .. 60:
            return "The patterns move with a life of their "
               +"own, weaving in and out of each "
               +"other like tiny snake, making the gauntlets "
               +"glimmer with strange reflections.\n";  break;
    }
}

mixed       
wear(object ob)
{
    int prev, damage;

     if (wearer->query_magic_res(MAGIC_I_RES_LIFE) > 0 ||
        wearer->query_magic_res(MAGIC_I_RES_AIR)  > 0 ||
        wearer->query_magic_res(MAGIC_I_RES_MAGIC) > 0 )
    {
		// changed to max to make sure it does go negative and heal mana.
        damage = max(0, wearer->query_magic_res(MAGIC_I_RES_AIR)   +
                 wearer->query_magic_res(MAGIC_I_RES_LIFE)  +
                 wearer->query_magic_res(MAGIC_I_RES_MAGIC));
        wearer->add_mana(-damage);
        wearer->catch_tell("Something within you resists the "+ short()
            +".\nYou feel your mental energy drain away.\n");
        return -1;
    }

    if (energy)
    {
        // This should never happen!
        wearer->catch_tell("Something prevents you from "+
	    "wearing the "+short()+".\n");
        return -1;
    }

	prev = wearer->query_prop(LIVE_I_QUICKNESS);
	energy = 15 +                                       // 15
	    wearer->query_magic_res(MAGIC_I_RES_DEATH) / 10 +   // 0 - 10
	    wearer->query_magic_res(MAGIC_I_RES_EARTH) / 10 +   // 0 - 10
	    wearer->query_stat(SS_WIS) / 25;                    // 0 - 4(+)

	if ((TP->query_skill(SS_UNARM_COMBAT) > 50))
	    energy += wearer->query_skill(SS_UNARM_COMBAT) / 4;
		// Total range from 15 - 64(+)

	// Now bound it:
	if (energy < 15) energy = 15;
	if (energy > 60) energy = 60;
	if ((TP->query_skill(SS_UNARM_COMBAT) < 50) && (energy > 60))
	    energy = 60;

	wearer->add_prop(LIVE_I_QUICKNESS, prev + energy);

    switch(energy)
    {
        case 0:
            wearer->catch_tell("You pull the "+short()+" over your arms and "
                +"hands, a single coursing throb pulses up your arms then "+
		"fades.\n"); break;
        case 41 .. 45:
            wearer->catch_tell("As you pull the "+short()+" over your arms and "
                +"hands, a feeling of speed and power nearly overwhelms "
                +"you.\n"); break;
        case 46 .. 50:
            wearer->catch_tell("A shudder runs through your arms as you "
                +"pull the "+short()+" over your arms and hands.\n"
                +"A feeling of great energy runs through you.\n"); break;
        case 51 .. 70:
            wearer->catch_tell("You are overcome with a sense of euphoria as "
                +"you don the "+short()+" over your arms and "
                +"hands.\nYou feel an almost divine energy coursing "
                +"through you.\n");   break;
        default:
            wearer->catch_tell("You feel a sudden energy overwhelm you as you "
                +"pull the "+short()+" over your arms and hands.\n");
            break;
    }

    say(QCTNAME(wearer)+" slides "+LANG_ASHORT(TO)+" on over "+
        POSSESS(wearer)+" hands and arms.\n");

    return 1;
}

mixed
remove(object obj)
{
    object owner = query_worn();

    if (owner && energy)
    {
	int prev = owner->query_prop(LIVE_I_QUICKNESS);

	if (!(prev - energy))
	    owner->remove_prop(LIVE_I_QUICKNESS);
	else
           owner->add_prop(LIVE_I_QUICKNESS, prev - energy);
    }

    owner->catch_tell("You feel the energy in your body "+
	"fade away as you remove the gauntlets.\n");
    tell_room(environment(owner), QCTNAME(owner) +" slides off "+
	LANG_THESHORT(TO)+".\n", owner); 

    energy = 0;
    return 1;
}
