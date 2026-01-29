/*  /d/Emerald/south_shore/obj/scale.c
 *
 *  Special scale for Demerga. This shield allows players to 
 *  deal some extra damage by slamming it into their enemy.
 *
 *  Created 9.3.2022 by Velith
 *  Special is from /d/Gondor/arnor/armour/targa.c
 */
inherit "/std/armour";
inherit "/lib/keep.c";
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <formulas.h>
#include "/d/Gondor/defs.h"

void
create_armour()
{
    set_name("scale");
    add_name("shield");
	set_pname("scales");
    add_adj("transparent");
    set_short("transparent scale");
    set_long("This transparent scale was obtained from the tail "
             + "of an aquatic creature. It bears beautiful resemblance "
             + "to a large piece of polished crystal. The ends of this "
             + "oblong piece taper up to two points that arch gracefully "
             + "outward, sharp enough to harm a foe in battle. Peering "
             + "through the transparency, you notice a mysterious "
             + "white-blue substance swirling around the inside. The "
             + "scale seems to be quite strong despite its delicate "
             + "qualities. A gentle blue glow draws your attention "
             + "to the lines of mystifying runes carved along the "
             + "side of the scale.\n");
    add_item( ({ "substance", "substances", "iridescent substance", "iridescence" }),
             "A thin fluid swirls around the inside of this shield. "
             + "Its color shifts through the rainbow spectrum when you move "
             + "into the sunlight, but quickly becomes a light silvery shade as "
             + "you step back into the shade.\n");
    add_item( ({ "points", "point", "spikes", "spike"  }),
             "The ends of this scale are remarkably fine, although you see "
             + "no evidence of purposeful sharpening. The spikes point outward, "
             + "as if towards an invisible enemy.\n");
    add_item(({"glowing runes","runes"}),"@@read_runes");
    add_cmd_item(({"runes","glowing runes"}),"read","@@read_runes2");
    
    set_at(A_SHIELD);
    set_ac(46);
    set_keep(1);
    set_am(({ 0, 1, -1}));
    
    add_prop(OBJ_I_VOLUME,  650);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VALUE,F_VALUE_ARMOUR(21) + random(100));
}

int
read_runes2()
{
    if(TP->query_skill(SS_LANGUAGE) < 40)
    {
        this_player()->add_mana(-random(10) - 10);
        write("After studying the runes for a "
              + "while, you give up trying to understand the "
	          + "delicate swirls. This ancient language has "
	          + "long been lost to time, and is ultimately "
	          + "indecipherable to you.\n");
        return 1;
    }
    write("You study the runes closely. "
          + "After a couple minutes, the runes start glowing "
          + "a teal color, and the writing begins to waver. "
          + "The runes shift into an ancient aquatic language! "
          + "You manage to make out parts of an ancient "
          + "myth, reading: \n"
          + "'4# m#llenia ago, the aq#tic dw#llers of th# deep "
          + "ret#eated to the l#nd. T#e true nat#re of their fears "
          + "l#es beneat# the w#ves, tho#gh non# sin#e that time h#ve"
          + "d#red inv#stiga## t## wate#s.'\n");
    return 1;
}

string
read_runes()
{
    if(TP->query_skill(SS_LANGUAGE) < 50)
    {
        this_player()->add_mana(-random(10) - 10);
        return "After studying the runes for a "
            + "while, you give up trying to understand the "
            + "elaborate swirls. This ancient language has "
            + "clearly long been lost to time, and is ultimately "
            + "indecipherable to you.\n";
    }
    return "You study the runes closely. "
        + "A few moments later, the runes begin glow with "
        + "a soft blue light, and the writing begins to waver. "
        + "You manage to make out parts of an ancient myth: \n"
        + "## m#llenia ago, the aq#tic dw#llers of th# deep "
        + "ret#eated to the l#nd. T#e true nat#re of their f##rs "
        + "l#es beneat# the w#ves, tho#gh no## sin#e that time h#ve"
        + "d#red inv#stiga## t## wate#s.";
}

int *
query_shield_slots()
{
    return (::query_shield_slots() + ({ A_BODY }) );
}

varargs int
got_hit(int hid, int ph, object att, int dt, int dam)
{
    object tp = query_worn();
    int points = 100 + random(100);
    string * attacks = ({"impale", "stab", "slash",
                         "cut", "jab", "skewer" });
    string attack = attacks[random(sizeof(attacks))];
    
    if (random(100) > 80 && objectp(tp))
    {
		find_living("velith")->catch_msg("DEBUG: got_hit called.\n");
		mixed* result = att->hit_me(points, W_SLASH, att, -1);
        mixed* damage = result[0];
		string damage_lvl;
		
		if (damage >= 0)
			damage_lvl = "just barely scrape";
		if (damage > 15)
			damage_lvl = "slightly nick";
		if (damage > 25)
			damage_lvl = "deeply slash";
		if (damage > 50)
			damage_lvl = "brutally gouge";
		if (damage > 75)
			damage_lvl = "rip flesh from";
	    
	    tp->catch_msg("You deftly dodge " + QTPNAME(att) + " attack "
                      + "and flip the translucent scale up, allowing "
		              + "the sharp spikes to " + damage_lvl + " "
                      + QTPNAME(att) + " " + result[1] + ".\n");
        tell_room(environment(tp), "The translucent spikes "
                  + damage_lvl + " " + QTPNAME(att) + " " + result[1] + " as "
		          + QTNAME(tp) + " deflects " + QTPNAME(att) + " attack!\n", 
				  ({tp, att}));
        att->catch_msg(QTNAME(tp) + " dodges the attack and lunges "
                       + "forward, letting the translucent scale "
					   + damage_lvl + " your " + result[1] + "!\n"); 
        
        if (att->query_hp() <= 0)
        {
            att->do_die(tp);
        }
    }
    return (::got_hit(hid, ph, att, dt, dam));
}
