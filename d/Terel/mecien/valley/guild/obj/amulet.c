/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
/*
 * /d/Terel/mecien/valley/guild/obj/amulet.c
 *
 * The mystic guild object.
 *
 * Probably by Mecien ;-)
 *
 * Revision history:
 * /Mercade, August 8th 1994, added query_recover.
 */
inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP              this_player()
#define TO              this_object()
#define ETO             environment(TO)
#define ETP             environment(TP)
#define EN environment

int invoked = 0;

public int
query_value()
{
    return 0;
}

public string 
query_auto_load()
{
    if (!ETO || !living(ETO)) return "";

    if (MEMBER(ETO) || T_WIZ(ETO))
        return MASTER;
    else
        return "";
}

/*
 * Function name: query_recover
 * Description  : Since all armours are recoverable by default now, we
 *                do not want this one to be recoverable. /Mercade
 * Returns      : 0 - always.
 */
string
query_recover()
{
    return 0;
}

public string
long_desc()
{
    if (MEMBER(TP))
	return "This heavy golden amulet, inscribed with a circle of twelve "
        + "runes surrounding a perfectly clear crystal, symbolizes "
        + "devotion to the ancient Ways. On the back, in the mystic "
        + "language, are these words: 'Glorify the ancients often; invoke them "
        + "when you must.'\n";
    else
        return "This heavy golden amulet, inscribed with a circle of "
	+ "twelve runes surrounding an blood-red stone, seems to burn in "
	+ "your grasp. You sense that the wisest course of action would be "
	+ "to have it destroyed at once. On the back are some indecipherable "
	+ "squiggles.\n";
}

public void
create_armour()
{
    set_name("amulet");
    add_name(MYSTIC_AMULET);
    set_adj("ancient");
    set_adj("mystic");
    add_adj("golden");
    set_short("amulet of the Ancients");
    set_long("@@long_desc@@");
    set_ac(4);
    set_am(({ 0, 0, 0}));
    add_prop(OBJ_I_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(MYSTIC_ARMOUR, 1);
    set_at(A_NECK);
}

public void
wear_amulet(object who)
{
    if (!who || !MEMBER(who)) return;
    
    if (who) who->wear_arm(TO);
}

public void
init()
{
    ::init();
    
    if (ETO != TP) return;
    
    if (!MEMBER(TP) && !T_WIZ(TP))
    {
	write("The amulet of the Ancients bursts into flame, " +
	      "and is rapidly consumed.\n");
	remove_object();
	return;
    }
    set_alarm(2.0, -1.0, &wear_amulet(TP));
    add_action("do_invoke", "invoke");
                                        /* 130001 contains the # of the */
    					/* ancient player is tied to. */
    switch(TP->query_skill(ENTRANCE_QUEST))
    {
	case 1:	
	    add_action("emote1", "glorify"); 	     
	    break;	
	case 2:
	    add_action("emote2", "glorify");
	    break;
	case 3:
	    add_action("emote3", "glorify");
	    break;
	case 4:
	    add_action("emote4", "glorify");
	    break;
	case 5:
	    add_action("emote5", "glorify");
	    break;
	case 6:
	    add_action("emote6", "glorify");
	    break;
	case 7:
	    add_action("emote7", "glorify");
	    break;
	case 8:
	    add_action("emote8", "glorify");
	    break;
	case 9:
	    add_action("emote9", "glorify");
	    break;
	case 10:
	    add_action("emote10", "glorify");
	    break;
	case 11:
	    add_action("emote11", "glorify");
	    break;
	case 12:
	    add_action("emote12", "glorify");
	    break;
    }
}

public int
gcheck(string str)
{
    if (!str) return 0;
    if (query_worn() != TP) return 0;
    if (lower_case(str) == "ancients") return 1;
    if (lower_case(str) == "the ancients") return 1;
    return 0;
}

int
emote1(string str)
{
    notify_fail("Glorify whom?\n");
    if (!gcheck(str)) return 0;
    
    write("The air seems to grow warm all about you.\n");
    say(QCTNAME(TP)+" radiates a bright vigorous light.\n");
    set_alarm(2.0, -1.0, "sun", TP);
    return 1;
}

int
emote2(string str)
{
    notify_fail("Glorify whom?\n");
    if (!gcheck(str)) return 0;
    
    write("A mysterious tingling passes through you.\n");
    say(QCTNAME(TP)+" is surrounded by an aura of moonlight.\n");
   set_alarm(2.0, -1.0, "moon", TP);
    return 1;
}

int
emote3(string str)
{
    notify_fail("Glorify whom?\n");
    if (!gcheck(str)) return 0;
    
    tell_room(ETP, "Bright flashes of light sparkle all about.\n");
    write("You gaze upwards and contemplate the celestial depths.\n");
    say(QCTNAME(TP)+" loses himself in the cosmic depths.\n");
    return 1;
}

int
emote4(string str)
{
    notify_fail("Glorify whom?\n");
    if (!gcheck(str)) return 0;
    
    tell_room(ETP, "A simple breeze passes over, a haunting voice lingering.\n");
    write("From within the breeze a haunting melody echos, " +
          "resonating deep within you.\n");
    say(QCTNAME(TP)+" seems to speak to the wind.\n");
    return 1;
}

int
emote5(string str)
{
    notify_fail("Glorify whom?\n");
    if (!gcheck(str)) return 0;
    
    write("The ancient peace of the forests wells up within you..\n");
    say(QCTNAME(TP)+" is entranced by some distant, idyllic peace.\n");
    set_alarm(2.0, -1.0, "green", TP);
    return 1;
}

int
emote6(string str)
{
    notify_fail("Glorify whom?\n");
    if (!gcheck(str)) return 0;
    
    tell_room(ETP, "A thick cloud of moisture fills the air, " +
              "then condenses and disappears.");
    write("The cool wetness of the clouds bathes and refreshes you.\n");
    say(QCTNAME(TP) + " raises " + TP->query_possessive() +
        " hands upwards to form a sign of praise.\n");
    return 1;
}

int
emote7(string str)
{
    notify_fail("Glorify whom?\n");
    if (!gcheck(str)) return 0;
    
    tell_room(ETP, "A sudden blast of trumpets and peal of bells " +
              "shakes the very ground beneath you.\n");
    write("An austere power grips you.\n");
    say(QCTNAME(TP)+" is caught up in the music, rapturous.\n");
    return 1;
}

int
emote8(string str)
{
    notify_fail("Glorify whom?\n");
    if (!gcheck(str)) return 0;
    
    write("You feel at one with the mysteries of the universe.\n");
    say(QCTNAME(TP)+" meditates on the mysteries of the universe.\n");
    set_alarm(2.0, -1.0, "universe", TP);
    return 1;
}

int
emote9(string str)
{
    notify_fail("Glorify whom?\n");
    if (!gcheck(str)) return 0;
    
    tell_room(ETP, "The earth trembles beneath you.\n");
    write("The might of the Ancients passes through you; " +
          "you feel a bit shaken.\n");
    say(QCTNAME(TP) + " is shaken by some mysterious power.\n");
  set_alarm(2.0, -1.0, "gold", TP);
    return 1;
}

int
emote10(string str)
{
    notify_fail("Glorify whom?\n");
    if (!gcheck(str)) return 0;
    
    tell_room(ETP, "A darkness appears, like a cloud, " +
              "from which ominous voices echo forth.\n");
    write("The spirits of the past haunt you with their " +
          "long silent voices.\n");
    say(QCTNAME(TP) + " speaks to the voices. " +
        capitalize(TP->query_pronoun()) + " trembles in the midst of " +
        "the darkness.\n");
    return 1;
}

int
emote11(string str)
{
    notify_fail("Glorify whom?\n");
    if (!gcheck(str)) return 0;
    
    write("You are filled with a fiery spirit of charity.\n");
    say(QCTNAME(TP)+" looks to be filled with some divine virtue.\n");
   set_alarm(2.0, -1.0, "charity", TP);
    return 1;
}

int
emote12(string str)
{
    notify_fail("Glorify whom?\n");
    if (!gcheck(str)) return 0;
    
    tell_room(ETP, "A shadow rises over this place, a dark " +
              "voyager from eternity.\n");
    write("A doom unfolds about you, a power that eats away at " +
          "your very existance.\n");
    say(QCTNAME(TP)+" despairs, the weight of doom upon " +
        TP->query_possessive() + " shoulders.\n");
    return 1;
}

public void
all_gone(object ob)
{
    tell_room(ob, "The ancient presence has departed; all that remains "
     + "is an empty feeling, as if a vital portion of your being had been "
     + "replaced by a hollow void.\n");
    invoked = 0;
    ob->remove_prop("mystic_presence");
}

public void
almost_gone(object ob)
{
    tell_room(ob, "You sense that the ancient presence is " +
              "almost gone.\n");
    set_alarm(5.0, -1.0, &all_gone(ob));
}

public void
half_gone(object ob)
{
    tell_room(ob, "You sense that the ancient presence is receeding.\n");
    set_alarm(25.0, -1.0, &almost_gone(ob));
}

public int
do_invoke(string str)
{
   notify_fail("Invoke what?\n");
   if (!str) return 0;
   if (member_array(lower_case(str),
                    ({"amulet", "ancients", "the ancients"})) < 0)
       return 0;
   
   if (query_worn() != TP)
       return 0;
   
   if (invoked) {
       write("Your amulet is too fiery!\n");
       return 1;
   }
   
   if (ETP->query_prop("mystic_presence"))
	write("Why invoke what is right before you? An ancient presence "
	+ "is close by; its nearness seems to warm you as the sun warms "
	+ "the upturned face.\n");
   else {
	write("You kneel down and invoke the presence of the Ancients. In "
	+ "the Old Tongue you speak the mystic words, and as you pronounce the "
	+ "hallowed syllables your voice begins to resonate with power. The air "
	+ "starts to swirl; as you intone the final words you sense the entrance "
	+ "of a Presence whose very age defies reckoning. You rise again, spent from "
	+ "the invocation, but the Ancient One is still close by, and the very nearness "
	+ "fills your heart with joy.\n");
	say(QCTNAME(TP)+" kneels down and begins to speak softly. "
	+ "Gradually "+TP->query_possessive()+" voice begins to grow in power and "
	+ "the strange words, spoken in an ancient tongue unknown to you, resonate "
	+ "deep within the very fibre of your being. The air starts to swirl, and "
	+ "suddenly you sense nearby a Presence, so old as to defy the very concept "
	+ "of age.\n");
	invoked = 1;
        set_alarm(30.0, -1.0, &half_gone(ETP));
        ETP->add_prop("mystic_presence", 1);
    }
    return 1;
}

sun(object who){
tell_room(EN(who), "A warmth and brightness, like the sun itself, shines down upon this place.\n");
}

moon(object who){
 tell_room(EN(who), "A circle of bright lights rises over this places, radiating a bluish light, while a sound of bells echoes in the distance.\n");
}

green(object who){
tell_room(EN(who), "A thick green mist fills this place for a moment, alluring, a sense of vitality within it.\n");
}

universe(object who){
tell_room(EN(who), "A darkness descends upon this place, then golden runes appear within the air, radiating a tingling energy, yet remaining unknown.\n");
}

gold(object who){
tell_room(EN(who), "A golden haze streams through this place, touching you with a mighty strength.\n");
}

charity(object who){
tell_room(EN(who), "Your heart is touched by a mysterious force, compelling you to a life of charity, it burns fiery within you.\n");
}


