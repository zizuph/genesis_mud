/* Leech, a magical scimitar wielded by /d/Shire/mountain/npc/hzzz
 * See wizinfo and id_info for more detailed info.
 * 18 June 1994 -Mayhem
 *
 * Mod:  Increased penalties for failure to control.
 * Mod:  Allowed dulling of blade
 * Mod:  Increased time between messages, alarm is now removed if 
 *       Leech is broken or leaves environment without being unwielded.
 *    29 June 1994 -Mayhem
 *
 * Mod:  Leech remembers the last person to master it, does not require
 *       remastering from that person if it is unwielded for some reason.
 *    31 Dec 1994 -Mayhem
 *
 * Mod:   Made magebane's extra damage formula conform with
 *        the AoB's wishes.
 *    24 July 1995 -Dunstable
 *
 * Mod: Leech has lower hit/pen for non-masters, higher for masters.
 *    25 Feb 1996  -Mayhem
 *
 * Mod:  Fixed Leech so it now uses the query_option instead of the 
 *       query_blood to filter out who sees the leech hit or not.
 *    15 July 1996  -Igneous
 *
 * Mod: Made the leech Keepable using /lib/keep
 *    13 December 1996 -Igneous
 *
 * Mod:  A few changes...  The leech remembers it's master over a
 *       reboot... i.e leech_master variable is in the recover routines.
 *       Leech makes sure you attack someone if you know them.
 *       If you fail a test the wielder can not drop nor unwield
 *       The magebane, until they pass the next test.
 *       Also added the OBJ_I_ALIGN prop to the leech as well.
 *    22 January 1997 -Igneous
 *
 * Mod:  While changing query_race_name to query_race in some of the functions
 *       I changed the leech so it no longer only attacks players, it now will
 *       attack players and npcs if they are of the type the leech hates.
 *       Also the will of the leech overcomes any fear the wielder might have 
 *       of attacking that target, when it tells a player to attack something.
 *       I.e. attack_object is called.
 *    2  Feb. 1997 -Igneous
 *
 * Mod:  General bug fixes.
 *       Also added some debuging code while I was at it ;)
 *     8 May, 1997 -Igneous
 *
 *    Last change, honest *grin* after finally ridding this of all known
 *    bugs, I redefiend stat_object in the leech so it returns the 
 *    leech_master varibale as well as adding the pragma strict_types
 *    6 July, 1997 -Igneous
 *
 * Mod:  Added support for the Gag miss option, hopefully I'm done
 *       doing modifications on this accursed thing ;-)
 *    22 Oct, 1997  -Igneous
 */

#pragma strict_types
inherit "/std/weapon";
inherit "/lib/keep";

#include <options.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <filter_funs.h>
#include <tasks.h>
#include "/d/Shire/common/defs.h" 

#define HIT                 45
#define PEN                 32
#define LEECH_MIN_SKILL     51
#define LEECH_URGE_COST     50
#define MANA_LOSS_FAIL      -125
#define FAT_LOSS_FAIL       -75
#define MANA_LOSS_WIN       -25
#define FAT_LOSS_WIN        -40
#define TEST_LIMIT          (15-(MENT_STATS(TP)/60))
#define TIME_BETWEEN_TESTS  200
#define IS_NPC_MAGE         query_names() == "mage"
#define IS_NPC_MAGE2        query_names() == "wizard"
#define LEECH_ALIGN         -450

// Debuging Defines
#define DEBUG_LOG "debug/leech"
#undef DEBUG_LOG

#ifdef DEBUG_LOG
#define DEBUG(s)  log_file(DEBUG_LOG, ctime(time()) + " "+ s +"\n", 25000)
#else
#define DEBUG(s)
#endif
#define ERROR(s)  log_file("debug/leech", ctime(time()) + " " + s + "\n")
// End of Debuging defines :)

//  Prototypes
void leech_urges();
void leech_welcome();
void leech_msg();
void leech_attack();
void do_switch();
void mage_drop();
void easy_win();
void avg_win();
void hard_win();

int passed_test, hits, mana_accum, alarm_id2, alarm_id, accum, no_more_tests;
int switch_alarm;
string leech_master;

void 
create_weapon()
{
    set_name("leech");
    add_name(({"sword","scimitar","magebane"}));
    add_name("_shire_magebane");
    set_adj(({"sharp","black","blackened","jagged","wavy"}));
    set_short("jagged black scimitar");
    set_long("A sharp, blackened scimitar with a jagged, wavy blade "+
      "and hide-wrapped hilt. The blade is forged of an unknown "+
      "steel alloy, blackened to eliminate all reflections. The hide "+
      "wrap on the hilt is still covered with numerous bristles from "+
      "the boar it came from. Set in the hilt is a dark red jewel that "+
      "seems to pulse slightly as you look at it.\n");
    set_default_weapon(HIT,PEN,W_SWORD,W_SLASH|W_IMPALE,W_NONE,TO);
    set_pm(({-3,3,0}));
    set_likely_dull(4);
    set_likely_corr(1);
    set_likely_break(0);
    add_prop(OBJ_M_NO_BUY, 1);
    add_prop(OBJ_I_ALIGN, LEECH_ALIGN);
    add_prop(OBJ_M_NO_DROP,"@@leech_test_drop");
    add_prop(OBJ_I_WEIGHT,F_WEIGHT_DEFAULT_WEAPON(HIT,PEN)+random(1501));
    add_prop(OBJ_I_VOLUME,F_VOLUME_WEAPON);
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT,PEN)+random(201));
    add_prop(MAGIC_AM_MAGIC,({78,"enchantment"}));
    add_prop(OBJ_I_IS_MAGIC_WEAPON,1);
    add_prop(MAGIC_AM_ID_INFO,({
	BSN("The "+short()+" appears to be strongly magical."),1,
	BSN("The jewel in the hilt of the "+short()+" seems to draw "+
	  "in magical energy."),45,
	BSN("The "+short()+" was forged ages ago by the greatest of "+
	  "the orcish smiths with the aid of the maia Sauron. They "+
	  "created Leech with one purpose in mind: to kill mages."),67,
	BSN("Accordingly, Leech will not even tolerate the touch of a "+
	  "mage, and will force such would-be-users to drop it."),74,
	BSN("Leech stores the energy it drains, and releases the energy in "+
	  "a violent burst when it can no longer contain the energy."),89,
	BSN("Leech possesses a will of its own, and is capable of forcing "+
	  "those of weaker will to do its bidding!"),95}));
    add_prop(OBJ_S_WIZINFO,"The "+short()+" drains and stores a "+
      "random (10+random(31)) amount of mana from whatever it hits, until "+
      "the victim has 0 mana, at which point it stops draining. In "+
      "addition when the stored amount of energy exceeds a certain number "+
      "(100+random(26)), it releases this energy, blasting the current "+
      "enemy with a burst of energy equal to double the amount of damage "+
      "done by the weapon that hit, effectively quadrupling damage for "+
      "one blow once every 4 to 13 hits. Only those who are learning "+
      "sword as part of their occupation will be able to wield Leech "+
      "(sword > 50). Leech has a special hatred of mages. "+
      "Thusly, members of a mage guild (lay or occ) will suffer "+    
      "damage and be forced to drop Leech if they should attempt to wield "+
      "it. They will also suffer triple the extra damage from the special "+
      "attack. Finally, Leech will occassionally attempt to assert its "+
      "will upon the wielder. Those with weak mental facilities and "+
      "little discipline will be forced to attack someone they may not "+
      "wish to normally.  Last updated: 8 April 1996.\n"+
      "The jewel that can be gotten from this scimitar, essentially "+
      "breaking it is a quest item for the Shire mage quest.\n"); 
    add_item(({"jewel","dark jewel","red jewel","dark red jewel"}),
      "@@jewel_desc");
    add_item("setting","The jewel's setting seems to be very solid indeed. "+
      "It would take some strength to pry the dark red jewel from its home.\n");

    setuid(); seteuid(getuid());
}


string 
jewel_desc()
{
    if ((MENT_STATS(TP) - (TP->query_intoxicated()/2)) < 200 + random(51))
    {
	/*
	TP->eat_food(-(query_stuffed()/2));
	*/
	say(QCTNAME(TP)+" wrenches "+HIS_HER(TP)+" eyes away from "+
	  "whatever "+HE_SHE(TP)+" was looking at, "+
	  "and proceeds to lose part of "+HIS_HER(TP)+" dinner.\n");
	return "The pulsing, shifting jewel seems to draw part of "+
	"your very soul into its inner depths.  With a start, "+
	"you wrench your gaze away, but not before "+
	"becoming so nauseated you lose some of your "+
	"dinner.\n";
    }
    return "The dark red jewel appears to be quite valuable, but "+
    "also an integral part of the weapon, with no gaps or weaknesses "+
    "visible in its setting.  The jewel pulses and shifts within "+
    "the hilt, and for just a second, you can almost feel "+
    "it calling to you.\n";
}

void
init()
{
    ::init();
    add_action("do_pry","pry");
    add_action("do_pry","pull");

}

int
do_pry(string str)
{
    FIXEUID;

    if (!str) 
    { 
	return 0; 
    }
    if (str != "jewel from scimitar")
    {
	notify_fail("Pry what ?\n");
	return 0;
    }
    if (!passed_test)
    {
	notify_fail("You hear a laughing voice say: 'Fool I am the master "+
	  "here, how dare you try and remove me!\n");
	return 0;
    }
    if (switch_alarm)
    {
	notify_fail("But the jewel has already been removed!\n");
	return 0;
    }
    if (TP->query_stat(SS_DIS) < 80 + random(30))
    {
	write("You tug at the jewel but it won't budge from its seat.\n");
	TP->add_mana(-100);
	write("You feel a slight drain as the jewel resists your force.\n");
	return 1;
    }
    TP->command("unwield _shire_magebane");
    write("You free your hands to get good leverage on the jewel.\n");
    write("You tug with all your might and nothing happens.\n");
    switch_alarm = set_alarm(5.0,0.0,&do_switch());
    return 1;

}

void
do_switch()
{
    object brokenleech, jewel;

    write("You hear a small sigh, followed by a distinct popping sound.\n"+
      "It seems to come from the jagged black scimitar.\n");
    write("The dark red jewel comes loose and tumbles harmlessly into "+
      "your hand.\n");
    say(QCTNAME(TP)+ " pulls the dark red jewel from its place on the jagged "+
      "black scimitar with a sharp popping sound.\n");
    TP->add_prop("_i_got_the_leech_jewel",1);

    brokenleech = clone_object(GREEN_DIR + "wep/ruined_leech");
    brokenleech->move(ENV(TO));
    jewel = clone_object(GREEN_DIR + "obj/jewel");
    jewel->move(ENV(TO));
    set_alarm(0.1,0.0, &remove_object());
    return;
}

string 
query_accum()
{
    return "Current power level of the "+short()+" is "+accum+".";
}


int 
set_leech_master(string str)
{
    leech_master = str;
    return 1;
}


string 
query_leech_master()
{
    return "Current master of the "+short()+" is "+CAP(leech_master)+".";
}


int 
mage_drop()
{
    TP->command("drop _shire_magebane");
    return 1;
}


void
leech_welcome()
{
    write("A humble voice announces: 'Greetings "+CAP(leech_master)+ 
      ", my master.'\n");
}


mixed 
wield(object wep)
{
    if (TP->IS_LAY_MAGE || TP->IS_OCC_MAGE)
    {
	TP->heal_hp(-TP->query_max_hp()/9);
	TP->add_mana(-TP->query_max_mana()/10);
	if (TP->query_hp() <= 0)
	    TP->do_die(TO);
	else
	    set_alarm(1.0,0.0, &mage_drop());
	SAY(" is suddenly bathed in an eerie ruby glow that seethes and "+
	  "burns its way through "+HIS_HER(TP)+" body.");
	return "A piercing voice shreds your thoughts as it screams: "+
	"Infidel! I shall kill you for this sacrilage! How dare you "+
	"even attempt to use me!? If you ever try it again I will "+
	"seek you out and send you into the Darkness!\n"+
	"For now, I will content myself with some of your lifeforce.\n";
    }
    if (TP->query_skill(SS_WEP_SWORD) < LEECH_MIN_SKILL)
    {
	return "A mocking voice echos in your head: 'You dare try to "+
	"wield me, you buffoon?! Give me to someone who knows how to "+
	"use me properly, now!'\n";
    }
    WRITEN("You wrap your hand around the hilt of the "+short()+".");
    SAY(" wields the "+short()+".");
    passed_test = 1; // Aren't under the leechs control.. yet *grin*
    accum = 0;
    no_more_tests = 0;
    if (TP->query_race() == "orc")
    {
	// Orc mas this weapon mastered
	set_default_weapon(HIT+10, PEN+10, W_SWORD,W_SLASH|W_IMPALE,W_NONE,TO);
	TP->update_weapon(TO);
	return 1;
    }
    alarm_id = set_alarm(60.0,60.0, &leech_msg());
    if (TP->query_real_name() == leech_master)
    {
	set_default_weapon(HIT+10,PEN+10,W_SWORD,W_SLASH|W_IMPALE,W_NONE,TO);
	TP->update_weapon(TO);
	set_alarm(5.0,0.0, &leech_welcome());
	return 1;
    } 
    alarm_id2 = set_alarm(100.0,itof(TIME_BETWEEN_TESTS), &leech_urges());
    return 1;
}


void 
leech_msg()
{
    if (!interactive(query_wielded()))
    {
	return;
    }
    if (!objectp(query_wielded()))
    {
	ERROR("Leech_msg() was called with no one wielding "+
	  "the scimitar.");
	return;
    }
    if (query_wielded()->query_attack())
	return;

    if (TO->query_prop(OBJ_I_BROKEN)) 
    {
	remove_alarm(alarm_id);
	remove_alarm(alarm_id2);
	return;
    }

    switch(random(7))
    {
    case 0:
	WRITEN("A comforting voice whispers to you: 'Soon we will "+
	  "slay another foul mage!'");
	break;
    case 1:
	WRITEN("A hissing voice pleads: 'Feed me! I hunger!'");
	break;
    case 2:
	WRITEN("A rumbling voice echoes in your head: 'Kill "+
	  "the mages, kill them all before they kill you!'");
	break;
    case 3:
	WRITEN("The "+short()+" announces: 'Do not fear, my master. I "+
	  "will make you strong and then we shall destroy your "+
	  "enemies completely.'");  
	break;
    case 4:
	WRITEN("A comforting voice whispers: 'All will fall before you "+
	  "as long as I am with you!'");
	break;
    case 5:
	WRITEN("An outraged voice shouts: 'How I despise those pompous "+
	  "Valar and their foul, spineless followers.'");
	break;
    case 6:
	WRITEN("A pleasant voice soothes: 'You are the greatest "+
	  "master to ever hold me. All shall fall before m.. you! "+
	  "Yet I am starving. Appease my hunger and I shall serve "+
	  "you well!'");
	break;
    }
}

void 
leech_attack()
{
    object *livings, *karr;
    object victim, me;

    me = query_wielded();

    livings = FILTER_LIVE(all_inventory(ENV(me))) - ({me});
    livings = FILTER_CAN_SEE(livings, me);
    karr = filter(livings, &operator(==)("elf") @ &->query_race());

    if (!sizeof(karr))
	karr = filter(livings, &operator(==)("human") @ &->query_race());
    if (!sizeof(karr))
	karr = filter(livings, &operator(==)("dwarf") @ &->query_race());
    if (!sizeof(karr)) 
    {
	WRITEN("A sad voice murmurs: 'There is nothing here worth "+
	  "feeding upon. Feed me soon, or pay the ultimate price!'");
	return;
    }

    victim = karr[random(sizeof(karr))];

    if (victim->query_race()=="elf")
    {
	WRITEN("A sinister voice says to you: 'Kill that elf, I must "+
	  "be fed!'");
    }
    if (victim->query_race()=="dwarf")
    {
	WRITEN("A domineering voice commands: 'Kill that dwarf, I despise "+
	  "dwarves!'");
    }
    if (victim->query_race()=="human")
    {
	WRITEN("A quiet voice whispers insidiously into your ear: '"+
	  "Slay the human, appease my hunger!'");
    }

    if (victim->query_prop(OBJ_M_NO_ATTACK) 
      || ENV(me)->query_prop(ROOM_M_NO_ATTACK))
	return;

    //  No dis check needed to see if player can attack, the will of the leech
    //  controlls the wielder to attack things at it's command

    me->catch_msg("Unable to control yourself you attack "+
      QTNAME(victim)+"!\n");
    victim->catch_msg(QCTNAME(me)+" attacks you!\n");
    tell_room(ENV(me),QCTNAME(me)+" attacks "+QTNAME(victim)+"!\n",
      ({me,victim}));
    me->attack_object(victim);   

    DEBUG("Leech commands "+me->query_name()+" to attack "+
      victim->query_name()+"!");
}


void 
leech_urges()
{
    object wielder = query_wielded();
    int test, mentals, intox;

    // Link dead players shouldn't master or attack things
    if (!interactive(wielder))
    {
	return;
    }
    if (!objectp(wielder))
    {
	ERROR("Urge was called with no one wielding the scimitar.");
	return;
    }
    if (wielder->query_attack())
	return;

    if (TO->query_prop(OBJ_I_BROKEN)) 
    {
	remove_alarm(alarm_id);
	remove_alarm(alarm_id2);
	return;
    }

    accum -= LEECH_URGE_COST;

    mentals = MENT_STATS(wielder);
    intox   = wielder->query_intoxicated() / 2;
    test = (mentals - intox) - (200 + random(201));

    DEBUG("Urge test result on "+wielder->query_name()+
      " (MENTALS: "+mentals+"  INTOX:  "+intox+")  was "+test);

    if (test < 0) 
    {
	write("You feel a strong urge coming from the "+short()+".\n"+
	  "You muster all your willpower and try to resist.\n"+
	  "However, the "+short()+" wins, leaving you exhausted "+
	  "and the "+short()+" in control.\n");
	SAY(" seems to be involved in some internal struggle that "+
	  "leaves "+HIM_HER(wielder)+" tired, sweaty, and glassy eyed.");
	wielder->add_fatigue(FAT_LOSS_FAIL);
	wielder->add_mana(MANA_LOSS_FAIL);
	passed_test = 0;
	leech_attack();
	return;
    }
    if (no_more_tests > TEST_LIMIT)
    {
	write("You feel a strong urge coming from the "+short()+".\n"+ 
	  "You defeat it easily, and feel the will of "+
	  "the "+short()+" retreat.  You feel refreshed.\n"+
	  "A voice hisses: 'You've won, for now....'\n");
	say(QCTNAME(wielder)+" emerges from a brief internal struggle "+
	  "looking refreshed and happy.\n");
	set_default_weapon(HIT+10,PEN+10,W_SWORD,W_SLASH|W_IMPALE,W_NONE,TO);
	wielder->update_weapon(TO);
	wielder->add_mana(mana_accum);
	leech_master = wielder->query_real_name();
	mana_accum = 0;
	passed_test = 1;
	remove_alarm(alarm_id2);

	DEBUG("Leech mastered by "+wielder->query_name());

	return;
    }
    write("You feel a strong urge coming from the "+short()+".\n"+
      "You muster all your willpower, and try to resist.\n"+
      "With a final, draining effort, you beat back the urge "+
      "and retain control of your body.\n");
    SAY(" seems to be involved in some internal struggle that "+
      "leaves "+HIM_HER(wielder)+" somewhat tired and sweaty.");
    wielder->add_fatigue(FAT_LOSS_WIN);
    wielder->add_mana(MANA_LOSS_WIN);
    mana_accum -= MANA_LOSS_WIN;
    passed_test = 1;
    no_more_tests++;
    return;
}

void 
leave_env(object from, object to)
{
    ::leave_env();
    remove_alarm(alarm_id);
    remove_alarm(alarm_id2);
    set_default_weapon(HIT,PEN,W_SWORD,W_SLASH|W_IMPALE,W_NONE,TO);
}


void 
farewell_msg()
{
    if (objectp(TP))
	tell_room(ENV(TP),"You hear a bloodcurdling scream from somewhere "+
	  "nearby.\n");
}


mixed 
leech_test_drop()
{
    object wielder;

    wielder = query_wielded();

    if (!objectp(wielder))
	return 0;

    if (wielder->query_hp() <= 0)
    {
	wielder->catch_msg("Your lifeless fingers relax their grip on the "+
	  short()+".\n");
	tell_room(ENV(wielder),QCTNAME(wielder)+" relaxes "+HIS_HER(wielder)+
	  " grip on the "+short()+" in death.\n",wielder);
	return 0;
    }  
    if (!passed_test && !wielder->query_wiz_level())
    {
	return "A scathing voice penetrates your mind: 'Weak willed fool! "+
	"I am the master here.  I will decide when I am done with you!'\n";
    }
    return 0;
}


int 
unwield()
{
    object wielder = query_wielded();

    if (wielder->query_hp() <= 0) 
	return 1;
    if (!passed_test && !wielder->query_wiz_level())
    { 
	wielder->catch_msg("A scathing voice penetrates your mind: 'Weak "+
	  "willed fool!  I am the master here.\nI will decide when I am "+
	  "done with you!'\n");
	tell_room(ENV(wielder),QCTNAME(wielder)+" struggles to release "+
	  HIS_HER(wielder)+" grip on the "+short()+", but fails.\n",wielder);
	return -1;
    }
    remove_alarm(alarm_id);
    remove_alarm(alarm_id2);
    wielder->catch_msg("You release your grip upon the "+short()+".\n");
    say(QCTNAME(wielder)+" unwields the "+short()+".\n");
    set_alarm(itof(30+random(46)),0.0,"farewell_msg");
    passed_test = 1;
    return 1;
}

int 
burn_me(object enemy, int dam) 
{
    int res;
    object wielder;
    wielder = query_wielded();
    res = enemy->query_magic_res(MAGIC_I_RES_MAGIC);
    dam = (dam - res) + 100;

    if (enemy->IS_NPC_MAGE || enemy->IS_NPC_MAGE2 || 
      enemy->IS_LAY_MAGE || enemy->IS_OCC_MAGE)
    {
	dam = dam*3;
    }
    if (dam < 1)
    {
	if (!wielder->query_option(OPT_GAG_MISSES))
	    wielder->catch_msg("A pulse of blood-red energy leaps "+
	      "from the "+short()+", but misses "+QTNAME(enemy)+".\n");
	wielder->tell_watcher_miss("A pulse of blood-red energy narrowly "+
	  "misses "+QTNAME(enemy)+".\n",enemy);
	if (!enemy->query_option(OPT_GAG_MISSES))
	    enemy->catch_msg("A pulse of blood-red energy leaps from the "+ 
	      short()+" , but misses you.\n");
	return 1;
    }
    enemy->heal_hp(-dam);


    if (enemy->query_hp() <= 0) 
    {
	wielder->catch_msg(QCTNAME(enemy)+" is engulfed in an "+
	  "explosion of blood-red light from the "+short()+".\n");
	enemy->catch_msg("You are engulfed in a flash of blood-red light "+
	  "that burns your entire body from the "+short()+".\n");
	wielder->tell_watcher(QCTNAME(enemy)+" is completely engulfed by an "+
	  "eruption of blood-red power from the "+short()+".\n",enemy);
	return 1;
    }
    if (enemy->IS_NPC_MAGE || enemy->IS_NPC_MAGE2 || 
      enemy->IS_LAY_MAGE || enemy->IS_OCC_MAGE)
    {
	enemy->catch_msg("The "+short()+" seems to sing with delight "+
	  "as it burns you horribly with a bolt of blood-red energy.\n");
	wielder->catch_msg("Your "+short()+" practically hums with delight "+
	  "as it burns "+QTNAME(enemy)+" with a bolt of blood-red "+
	  "energy.\n");
	wielder->tell_watcher(QCTNAME(enemy)+" gets severly burned as a "+
	  "bolt of blood-red energy slams into "+HIS_HER(enemy)+
	  " body.\n",enemy);
	return 1;
    }

    enemy->catch_msg("A bolt of blood-red energy leaps from the "+short()+
      " and burns you badly!\n");
    wielder->catch_msg(QCTNAME(enemy)+" is burnt by the energy surge "+
      "from the "+short()+".\n");
    wielder->tell_watcher(QCTNAME(enemy)+" is briefly illuminated in blood-red "+
      "light as a bolt of energy slams into "+HIS_HER(enemy)+
      " body.\n",enemy);
    return 1;
}


int 
drain_me(object enemy, int dam) 
{
    int res, drained, amount;
    object wielder;

    wielder = query_wielded();
    res = enemy->query_magic_res(MAGIC_I_RES_DEATH);                    
    amount = random(31) + 10;
    drained = amount - random((res*amount/100)+1);

    if (drained < 1 || enemy->query_mana() < drained)
    {  
	enemy->catch_msg("The jewel on the "+short()+" pulses, but nothing "+   
	  "seems to happen.\n");
	wielder->catch_msg("The jewel on the "+short()+" pulses, but "+   
	  "nothing seems to happen.\n");
	return 1;
    }

    if (accum>100+random(26))
    {
	accum = 0;
	burn_me(enemy,dam);
	return 1;
    }

    if (enemy->query_hp() <= 0)
    {
	wielder->catch_msg("The jewel in the hilt of the "+short()+" flares "+
	  "a brilliant red as it sucks the life from your opponent.\n");
	enemy->catch_msg("The jewel in the hilt of the "+short()+" "+
	  "flashes bright red as you feel your life draining away.\n");
	drained = drained*2;
	return 1;
    }
    enemy->add_mana(-drained);
    wielder->catch_msg("The jewel on the "+short()+" pulses brighter as "+
      "your blow connects.\n");
    enemy->catch_msg("The jewel on the "+short()+" pulses brighter, and "+
      "you feel drained.\n");
    accum += drained;

    return 1;
}


void 
easy_win()
{
    object wielder = query_wielded();

    switch(random(4))
    {
    case 0:
	wielder->catch_msg("A voice hisses in your head: 'Oh mighty "+
	  "slayer of flies and toads, perhaps you might make "+
	  "the effort to kill something worth feeding upon next "+
	  "time?'\n");
	break;
    case 1:
	wielder->catch_msg("A voice pierces your thoughts: 'Perhaps "+
	  "next time you will be lucky enough to find a worthy "+
	  "opponent, oh Master.'\n");
	break;
    case 2:
	wielder->catch_msg("A scathing voice rips through your thoughts: "+
	  "'It is a sign of a true warrior to kill babies and corpses. "+
	  "Next time can we try something alive, I hunger!'\n");
	break;
    case 3:
	wielder->catch_msg("A pleasant voice murmurs: 'Well done Master. "+
	  "At this rate, you will be killing weeds and gnats in no "+
	  "time.'\n");
	break;
    }
}


void 
avg_win()
{
    object wielder = query_wielded();

    switch(random(3))
    {
    case 0:
	wielder->catch_msg("A pleasing voice soothes you: 'Well done "+
	  "my Master.  I feel the power coursing in me, but I need more! "+
	  "Give me more!'\n");
	break;
    case 1:
	wielder->catch_msg("A dull voice pleads: 'Let us find "+
	  "something more powerful, that did little to "+
	  "fill me!'\n");
	break;
    case 2:
	wielder->catch_msg("A voice boasts: 'See, already you grow "+
	  "more powerful!  All shall fall before you, strong or weak.  "+
	  "The stronger they are, the richer you shall be, however, "+
	  "so do not hesitate!'\n");
	break;
    }
}


void 
hard_win()
{
    object wielder = query_wielded();

    switch(random(3))
    {
    case 0:
	wielder->catch_msg("A pleased-sounding voice whispers: "+
	  "'Excellent work my master.  Now you have shown your true "+
	  "power.'\n");
	break;
    case 1:
	wielder->catch_msg("A lilting voice says: 'Ah, I can feel "+
	  "the power coursing through me!  More, give me more!'\n");
	break;
    case 2:
	wielder->catch_msg("A smug voice booms: 'At last, a kill "+
	  "worthy of my abilities.  Let us find other victims, for "+
	  "I hunger for more sweet power.'\n");
	break; 
    }
}


public mixed 
did_hit(int aid,string hdesc,int phurt,object enemy,int dt,int phit,int dam)
{
    object wielder = query_wielded();

    switch(phurt)
    {
    case -1:
	if (!wielder->query_option(OPT_GAG_MISSES))
	    wielder->catch_msg("You swing the "+short()+" harmlessly "+
	      "through the air.\n");
	if (!enemy->query_option(OPT_GAG_MISSES))
	    enemy->catch_msg(QCTNAME(wielder)+" swings the "+short()+ 
	      " harmlessly through the space near you.\n");
	wielder->tell_watcher_miss(QCTNAME(wielder)+" swings the "+short()+
	  " at "+QTNAME(enemy)+", but misses.\n",enemy);
	break;
    case 0:
	if (!wielder->query_option(OPT_GAG_MISSES))
	    wielder->catch_msg("You narrowly miss "+QTNAME(enemy)+
	      " with your "+short()+".\n");
	if (!enemy->query_option(OPT_GAG_MISSES))
	    enemy->catch_msg(QCTNAME(wielder)+" narrowly misses you "+ 
	      "with the "+short()+".\n");
	wielder->tell_watcher_miss(QCTNAME(wielder)+" swings the "+short()+
	  " at "+QTNAME(enemy)+" and narrowly misses.\n",enemy);
	break;
    case 1..5:
	wielder->catch_msg("You tear a shallow wound into the "+
	  hdesc+" of the "+enemy->query_race_name()+" with "+
	  "the "+short()+".\n");
	enemy->catch_msg("You feel a fresh wound open on your "+hdesc+
	  " as the "+short()+" tears into you.\n");
	wielder->tell_watcher(QCTNAME(wielder)+" tears a shallow wound "+
	  "into the "+hdesc+" of "+QTNAME(enemy)+" with the "+short()+
	  ".\n",enemy);
	break;
    case 6..10:
	wielder->catch_msg("You tear small chunks of flesh out "+
	  "of the "+hdesc+" of the "+enemy->query_race_name()+
	  " with the "+short()+".\n");
	enemy->catch_msg("You lose small chunks of flesh as the "+short()+
	  " tears into your "+hdesc+".\n");
	wielder->tell_watcher(QCTNAME(wielder)+" tears small chunks of "+
	  "flesh out of the "+hdesc+" of "+QTNAME(enemy)+" with the "+
	  short()+".\n",enemy);
	break;
    case 11..20:
	wielder->catch_msg("Your "+short()+" rips into the "+hdesc+
	  " of "+QTNAME(enemy)+", shredding flesh as it goes.\n");
	enemy->catch_msg("The flesh of your "+hdesc+" is shredded as the "+
	  short()+" rips into it.\n");
	wielder->tell_watcher(QCTNAME(wielder)+" shreds the flesh on "+
	  "the "+hdesc+" of "+QTNAME(enemy)+" with "+
	  HIS_HER(wielder)+" "+short()+".\n",enemy);
	break;
    case 21..40:
	wielder->catch_msg("Your "+short()+" tears a deep wound "+
	  "into the "+hdesc+" of the "+enemy->query_race_name()+".\n");
	enemy->catch_msg(QCTNAME(wielder)+" tears a deep "+
	  "wound into your "+hdesc+" with "+HIS_HER(wielder)+
	  " "+short()+".\n");
	wielder->tell_watcher(QCTNAME(wielder)+" tears a deep wound into "+
	  "the "+hdesc+" of "+QTNAME(enemy)+" with the "+short()+
	  ".\n",enemy);
	break;
    case 41..60:
	wielder->catch_msg("Your "+short()+" tears large "+
	  "chunks of flesh from the "+hdesc+" of the "+
	  enemy->query_race_name()+".\n");
	enemy->catch_msg(QCTNAME(wielder)+" tears large chunks of "+
	  "flesh from your "+hdesc+" with "+HIS_HER(wielder)+
	  " "+short()+".\n");
	wielder->tell_watcher(QCTNAME(wielder)+" tears large chunks of "+
	  "flesh from the "+hdesc+" of "+QTNAME(enemy)+" with the "+
	  short()+".\n",enemy);
	break;
    case 61..80:
	wielder->catch_msg("Your "+short()+" leaves nothing but "+
	  "ribbons of flesh hanging from the "+hdesc+" of "+
	  "the "+enemy->query_race_name()+".\n");
	enemy->catch_msg(QCTNAME(wielder)+" reduces the "+
	  "flesh of your "+hdesc+" to mere ribbons with "+
	  HIS_HER(wielder)+" "+short()+".\n");
	wielder->tell_watcher(QCTNAME(wielder)+" reduces the flesh "+
	  "of the "+hdesc+" of "+QTNAME(enemy)+" to ribbons with the "+
	  short()+".\n",enemy);
	break;
    case 81..90:
	wielder->catch_msg("Your "+short()+" almost tore "+
	  "through the "+hdesc+" of the "+enemy->query_race_name()+".\n");
	enemy->catch_msg("The "+short()+" almost tore right through "+
	  "your "+hdesc+".\n");
	wielder->tell_watcher("The "+short()+" wielded by "+QTNAME(wielder)+
	  " almost tore through the "+hdesc+" of "+QTNAME(enemy)+
	  ".\n",enemy);
	break;
    default:
	wielder->catch_msg("Shards of bone fly everywhere as "+
	  "your "+short()+" completely destroys the "+hdesc+" of the "+
	  enemy->query_race_name()+".\n");
	enemy->catch_msg("Your "+hdesc+" shatters when the "+short()+
	  " bites into it, sending splinters of bone flying everywhere.\n");
	wielder->tell_watcher("You duck to avoid shards of bone as the "+short()+
	  " wielded by "+QTNAME(wielder)+" completely shatters "+
	  "the "+hdesc+" of "+QTNAME(enemy)+".\n",enemy);
	if (enemy->query_hp() <= 0)
	{
	    if (enemy->query_average_stat() < wielder->query_average_stat()-30)
		set_alarm(1.0,0.0,&easy_win());
	    if (enemy->query_average_stat() > wielder->query_average_stat()-29
	      && enemy->query_average_stat() < wielder->query_average_stat()+29)
		set_alarm(1.0,0.0,&avg_win());
	    if (enemy->query_average_stat() > wielder->query_average_stat()-30)
		set_alarm(1.0,0.0,&hard_win());
	}
	break;
    }
    hits++;
    if (F_WEAPON_CONDITION_DULL(hits, query_pen(), query_likely_dull()))
    {
	hits = 0;
	set_dull(query_dull()+1);
    }
    if (phurt > 0)
    {
	drain_me(enemy,dam/3);
    }
    return 1;
}

string
query_recover()
{
    if (!leech_master)
	leech_master = " ";
    return MASTER + ":" +  query_wep_recover() + query_keep_recover() +
    "&&" + leech_master;
}

void
init_recover(string arg)
{
    string *a = explode(arg,"&&");

    set_leech_master(a[1]);
    init_wep_recover(a[0]);
    init_keep_recover(a[0]);
}

string
stat_object()
{
    string stat_string;

    stat_string = ::stat_object();

    stat_string += query_leech_master() + "\n";

    return stat_string;
}
